#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>

#include "basecomponentsmodel.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
BaseComponentsModel::BaseComponentsModel(ProjectModel* aProjectModel, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProjectModel(aProjectModel)
    , mBaseComponentsDir(mProjectModel ? mProjectModel->baseComponentsDir() : "")
{
    qDebug() << "BaseComponentsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void BaseComponentsModel::init()
{
    // Load Base Components
    //loadBaseComponents();
}

//==============================================================================
// Clear
//==============================================================================
void BaseComponentsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Get Keys Count
    int bckCount = rowCount();

    //qDebug() << "BaseComponentsModel::clear - count: " << bckCount;

    // Iterate Thru Keys
    for (int i=0; i<bckCount; i++) {
        // Get Component Info
        ComponentInfo* component = mBaseComponents[mBaseComponents.keys()[i]];
        // Delete Component
        delete component;
    }

    // Clear
    mBaseComponents.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Update Components
//==============================================================================
void BaseComponentsModel::updateBaseComponents()
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
            //qDebug() << "BaseComponentsModel::updateBaseComponents - name: " << component->mName;

            // Set Base Component
            component->setBaseComponent(mProjectModel->getComponentByName(component->mBaseName));

            //qDebug() << "BaseComponentsModel::updateBaseComponents - mName: " << component->mName << " -> " << (component->mBase ? component->mBase->mName : "NULL");
        }
    }
}

//==============================================================================
// Save All Components
//==============================================================================
void BaseComponentsModel::saveAllComponents()
{
    // Get Base Components Count
    int bcCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<bcCount; i++) {
        // Get Component
        ComponentInfo* baseComponent = mBaseComponents.value(mBaseComponents.keys()[i]);
        // Save
        baseComponent->save();
    }
}

//==============================================================================
// Clear All Children
//==============================================================================
void BaseComponentsModel::clearAllChildren(const bool& aClosing)
{
    // Get Base Components Count
    int bcCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<bcCount; i++) {
        // Get Component
        ComponentInfo* baseComponent = mBaseComponents.value(mBaseComponents.keys()[i]);
        // Check Closing State
        if (aClosing) {
            // Set Closing State
            baseComponent->setClosing(aClosing);
        }
        // Clear Children
        baseComponent->clearChildren();
    }
}

//==============================================================================
// Component Dirty State Changed Slot
//==============================================================================
void BaseComponentsModel::componentDirtyChanged(const bool& aDirty)
{
    Q_UNUSED(aDirty);

    // Get Sender Component
    ComponentInfo* senderComponent = static_cast<ComponentInfo*>(sender());
    // Check Sender Component
    if (senderComponent) {
        //qDebug() << "BaseComponentsModel::componentDirtyChanged - mName: " << senderComponent->mName << " - aDirty: " << aDirty;
        // Get Component Index
        int bcIndex = mBaseComponents.keys().indexOf(senderComponent->mName);
        // Check Component Index
        if (bcIndex >= 0) {
            // Emit Data Changed Signal
            emit dataChanged(index(bcIndex), index(bcIndex));
        }
    }
}

//==============================================================================
// Load Base Components
//==============================================================================
void BaseComponentsModel::loadBaseComponents()
{
    // Check Base Components Dir
    if (mBaseComponentsDir.isEmpty()) {
        return;
    }

    //qDebug() << "BaseComponentsModel::loadBaseComponents - mBaseComponentsDir: " << mBaseComponentsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Base Components Dir Iterator
    QDirIterator bcIterator(mBaseComponentsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Base Components Dir
    while (bcIterator.hasNext()) {
        // Get Next Item
        bcIterator.next();
        // Get Item NAme
        QString itemName = bcIterator.fileInfo().baseName();

        //qDebug() << "BaseComponentsModel::loadBaseComponents - itemName: " << itemName;

        // Check If Component HAs Been Already Loaded
        if (mBaseComponents.keys().indexOf(itemName) < 0) {
            // Get Item Path
            QString itemPath = bcIterator.filePath();
            //qDebug() << "BaseComponentsModel::loadBaseComponents - itemPath: " << itemPath;
            // Create Base Component
            ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel, false);
            // Add Base Component
            addBaseComponent(newComponent);

        } else {
            qDebug() << "BaseComponentsModel::loadBaseComponents - itemName: " << itemName << " - Component Already Added.";
        }
    }
}

//==============================================================================
// Set Base Components Dir
//==============================================================================
void BaseComponentsModel::setBaseComponentsDir(const QString& aDirPath)
{
    // Check Base Compoents Dir
    if (mBaseComponentsDir != aDirPath) {
        // Set Base Components Dir
        mBaseComponentsDir = aDirPath;
        // Clear
        clear();
        // Load Base Components
        loadBaseComponents();
    }
}

//==============================================================================
// Add Base Component
//==============================================================================
bool BaseComponentsModel::addBaseComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (aComponent) {
        // Get Component Name
        QString cName = aComponent->mName;

        // Get Base Component
        ComponentInfo* component = mBaseComponents.value(cName);

        // Check Component
        if (component) {
            qWarning() << "BaseComponentsModel::addBaseComponent - name: " << cName << " - ALREADY EXITS!";
            return false;
        }

        //qDebug() << "BaseComponentsModel::addBaseComponent - name: " << cName;

        // Add Base Component To Base Component Map
        mBaseComponents[cName] = aComponent;

        // Connect Dirty Changed Signal
        connect(aComponent, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));

        // Get New Key Index
        int newIndex = mBaseComponents.keys().indexOf(cName);

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), newIndex, newIndex);

        // End Insert Rows
        endInsertRows();

        return true;
    }

    return false;
}

//==============================================================================
// Remove Base Component
//==============================================================================
bool BaseComponentsModel::removeBaseComponent(const int& aIndex)
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
        QString bcKey = mBaseComponents.keys()[aIndex];
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Key
        mBaseComponents.remove(bcKey);
        // Disconnect Dirty Changed Signal
        connect(component, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));
        // Delete Component
        delete component;
        // Delete Component Info File
        if (!ciFile.remove()) {
            qWarning() << "BaseComponentsModel::removeBaseComponent - ERROR REMOVING FILE!";
        }
        // End Remove Rows
        endRemoveRows();

        return true;
    }

    return false;
}

//==============================================================================
// Remove Base Component
//==============================================================================
bool BaseComponentsModel::removeBaseComponent(const QString& aName)
{
    // Check Component Name
    if (aName.isEmpty()) {
        return false;
    }

    // ...

    return false;
}

//==============================================================================
// Get Component Index By Name
//==============================================================================
int BaseComponentsModel::getComponentIndex(const QString& aName)
{
    return mBaseComponents.keys().indexOf(aName);
}

//==============================================================================
// Get Component By Name
//==============================================================================
ComponentInfo* BaseComponentsModel::getComponent(const QString& aName, const bool& aPreload)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    // Get Base Component Info
    ComponentInfo* bcInfo = mBaseComponents.value(aName);

    // Check Base Component Info
    if (bcInfo) {
        return bcInfo;
    }

    // Check Preload
    if (aPreload) {
        // Get Full File Path
        QString bcFilePath = QString("%1/%2.%3").arg(mBaseComponentsDir).arg(aName).arg(DEFAULT_JSON_SUFFIX);

        qDebug() << "BaseComponentsModel::getComponent - bcFilePath: " << bcFilePath << " - Trying to Load...";

        // Try To Load Component From Info File
        bcInfo = ComponentInfo::fromInfoFile(bcFilePath, mProjectModel, false);

        // Check Base Component Info
        if (bcInfo) {
            // Add Base Component
            addBaseComponent(bcInfo);
        }
    }

    return bcInfo;
}

//==============================================================================
// Get Compoennt By Index
//==============================================================================
ComponentInfo* BaseComponentsModel::getComponentByIndex(const int& aIndex)
{
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mBaseComponents[mBaseComponents.keys()[aIndex]];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int BaseComponentsModel::rowCount(const QModelIndex& ) const
{
    //qDebug() << "BaseComponentsModel::rowCount - keys: " << mBaseComponents.keys();
    return mBaseComponents.keys().count();
}

//==============================================================================
// Data
//==============================================================================
QVariant BaseComponentsModel::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int bcRow = index.row();

    // Check Row
    if (bcRow >= 0 && bcRow < rowCount()) {
        // Get Component Info
        ComponentInfo* component = mBaseComponents[mBaseComponents.keys()[bcRow]];

        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case EBCRName:          return component->mName;
            case EBCRBuiltIn:       return component->mBuiltIn;
            case EBCRDirty:         return component->mDirty;
            case EBCRVisual:        return (component->mCategory != COMPONENT_CATEGORY_NONVISUAL);
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> BaseComponentsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    // Set Role Names
    rNames[EBCRName]    = "cName";
    rNames[EBCRBuiltIn] = "cBuiltIn";
    rNames[EBCRDirty]   = "cDirty";
    rNames[EBCRVisual]  = "cVisual";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
BaseComponentsModel::~BaseComponentsModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "BaseComponentsModel deleted.";
}
