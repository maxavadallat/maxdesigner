#include <QDebug>
#include <QJsonDocument>
#include <QDirIterator>

#include "componentsmodel.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentsModel::ComponentsModel(ProjectModel* aProjectModel, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProjectModel(aProjectModel)
    , mComponentsDir(mProjectModel ? mProjectModel->componentsDir() : "")
{
    qDebug() << "ComponentsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentsModel::init()
{
    // Load Components
    //loadComponents();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Get Keys Count
    int bckCount = rowCount();

    //qDebug() << "ComponentsModel::clear - count: " << bckCount;

    // Iterate Thru Keys
    for (int i=0; i<bckCount; i++) {
        // Get Component Info
        ComponentInfo* component = mComponents[mComponents.keys()[i]];
        // Delete Component
        delete component;
    }

    // Clear
    mComponents.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Components
//==============================================================================
void ComponentsModel::loadComponents()
{
    // Check Components Dir
    if (mComponentsDir.isEmpty()) {
        return;
    }

    //qDebug() << "ComponentsModel::loadComponents - mComponentsDir: " << mComponentsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Components Dir Iterator
    QDirIterator cIterator(mComponentsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Components Dir
    while (cIterator.hasNext()) {
        // Get Next Item
        cIterator.next();
        // Get Item NAme
        QString itemName = cIterator.fileInfo().baseName();
        // Check If Component HAs Been Already Loaded
        if (mComponents.keys().indexOf(itemName) < 0) {
            // Get Item Path
            QString itemPath = cIterator.filePath();
            //qDebug() << "ComponentsModel::loadComponents - itemPath: " << itemPath;
            // Create New Component Info
            ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel);
            // Add Component
            addComponent(newComponent);
        } else {
            qDebug() << "ComponentsModel::loadComponents - itemName: " << itemName << " - Component Already Added.";
        }
    }
}

//==============================================================================
// Update Components
//==============================================================================
void ComponentsModel::updateBaseComponents()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Get Base Components Count
    int bcCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<bcCount; i++) {
        // Get Component
        ComponentInfo* component = getComponentByIndex(i);
        // Check Base Name
        if (component && !component->mBaseName.isEmpty() && !component->mBase) {
            //qDebug() << "ComponentsModel::updateBaseComponents - name: " << component->mName;
            // Set Base Component
            component->mBase = mProjectModel->getComponentByName(component->mBaseName);
        }
    }
}

//==============================================================================
// Set Components Dir
//==============================================================================
void ComponentsModel::setComponentsDir(const QString& aDirPath)
{
    // Check Components Dir
    if (mComponentsDir != aDirPath) {
        // Set Componens Dir
        mComponentsDir = aDirPath;
        // Clear
        clear();
        // Load Components
        loadComponents();
    }
}

//==============================================================================
// Add Component
//==============================================================================
bool ComponentsModel::addComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (aComponent) {
        // Get Component Name
        QString cName = aComponent->mName;

        // Check Base Component
        ComponentInfo* component = mComponents.value(cName);

        // Check Component
        if (component) {
            qWarning() << "ComponentsModel::addBaseComponent - name: " << cName << " - ALREADY EXITS!";
            return false;
        }

        //qDebug() << "ComponentsModel::addComponent - name: " << cName;

        // Add Base Component To Base Component Map
        mComponents[cName] = aComponent;
        // Get New Key Index
        int newIndex = mComponents.keys().indexOf(cName);

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), newIndex, newIndex);

        // End Insert Rows
        endInsertRows();

        return true;
    }

    return false;
}

//==============================================================================
// Remove Component
//==============================================================================
bool ComponentsModel::removeComponent(const int& aIndex)
{
    // Get Base Components Count
    int bcCount = rowCount();
    // Check Index
    if (aIndex >= 0 && aIndex < bcCount) {
        // Get Component
        ComponentInfo* component = getComponentByIndex(aIndex);
        // Get Info File
        QFile ciFile(component->mInfoPath);
        // Get Key
        QString bcKey = mComponents.keys()[aIndex];
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Key
        mComponents.remove(bcKey);
        // Delete Component
        delete component;
        // Delete Component Info File
        if (!ciFile.remove()) {
            qWarning() << "ComponentsModel::removeBaseComponent - ERROR REMOVING FILE!";
        }
        // End Remove Rows
        endRemoveRows();

        return true;
    }

    return false;
}

//==============================================================================
// Get Component Index By Name
//==============================================================================
int ComponentsModel::getComponentIndex(const QString& aName)
{
    return mComponents.keys().indexOf(aName);
}

//==============================================================================
// Get Component By Name
//==============================================================================
ComponentInfo* ComponentsModel::getComponent(const QString& aName, const bool& aPreload)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    // Get Component Info
    ComponentInfo* cInfo = mComponents.value(aName);

    // Check Component Info
    if (cInfo) {
        return cInfo;
    }

    // Check Preload
    if (aPreload) {
        // Get Full File Path
        QString cFilePath = QString("%1/%2.%3").arg(mComponentsDir).arg(aName).arg(DEFAULT_JSON_SUFFIX);

        qDebug() << "ComponentsModel::getComponent - cFilePath: " << cFilePath << " - Trying to Load...";

        // Try To Load Component From Info File
        cInfo = ComponentInfo::fromInfoFile(cFilePath, mProjectModel);

        // Check Component Info
        if (cInfo) {
            // Add Component
            addComponent(cInfo);
        }
    }

    return cInfo;
}

//==============================================================================
// Get Compoennt By Index
//==============================================================================
ComponentInfo* ComponentsModel::getComponentByIndex(const int& aIndex)
{
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mComponents[mComponents.keys()[aIndex]];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentsModel::rowCount(const QModelIndex& ) const
{
    return mComponents.keys().count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentsModel::data(const QModelIndex& index, int role) const
{
    // Ger Row
    int cRow = index.row();

    // Check Row
    if (cRow >= 0 && cRow < rowCount()) {
        // Get Component Info
        ComponentInfo* component = mComponents[mComponents.keys()[cRow]];
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case ECRName:   return component->mName;
            case ECRDirty:  return component->mDirty;
            case ECRVisual: return (component->mCategory != COMPONENT_CATEGORY_NONVISUAL);
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> ComponentsModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Set Role Names
    rNames[ECRName]     = "cName";
    rNames[ECRDirty]    = "cDirty";
    rNames[ECRVisual]   = "cVisual";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentsModel::~ComponentsModel()
{
    // Clear
    clear();

    qDebug() << "ComponentsModel deleted.";
}

