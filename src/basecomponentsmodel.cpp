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
    loadBaseComponents();
}

//==============================================================================
// Clear
//==============================================================================
void BaseComponentsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Base Component List
    while (mBaseComponentList.count() > 0) {
        // Delete Last
        delete mBaseComponentList.takeLast();
    }
    // End Reset Model
    endResetModel();
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

    qDebug() << "BaseComponentsModel::loadBaseComponents - mBaseComponentsDir: " << mBaseComponentsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Base Components Dir Iterator
    QDirIterator bcIterator(mBaseComponentsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Base Components Dir
    while (bcIterator.hasNext()) {
        // Get Next Item
        bcIterator.next();
        // Get Item Path
        QString itemPath = bcIterator.filePath();

        qDebug() << "BaseComponentsModel::loadBaseComponents - itemPath: " << itemPath;

        // Create Base Component
        ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel);
        // Add Base Component
        addBaseComponent(newComponent);
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
void BaseComponentsModel::addBaseComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (aComponent) {
        // Get Base Components Count
        int bcCount = mBaseComponentList.count();
        // Get Index Of Component
        int bcIndex = mBaseComponentList.indexOf(aComponent);
        // Check Base Component Index
        if (bcIndex < 0) {
            // Begin Insert Rows
            beginInsertRows(QModelIndex(), bcCount, bcCount);
            // Iterate Thur Base Components
            for (int i=0; i<bcCount; i++) {

            }
            // Append Base Component
            mBaseComponentList << aComponent;
            // End Insert Rows
            endInsertRows();
        }
    }
}

//==============================================================================
// Remove Base Compoennt
//==============================================================================
void BaseComponentsModel::removeBaseComponent(ComponentInfo* aComponent, const bool& aDelete)
{
    // Check Component
    if (aComponent) {
        // Get Base Components Count
        int bcCount = mBaseComponentList.count();
        // Get Index Of Component
        int bcIndex = mBaseComponentList.indexOf(aComponent);
        // Check Base Component Index
        if (bcIndex >= 0 && bcIndex < bcCount) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), bcIndex, bcIndex);
            // Check Deletion
            if (aDelete) {
                // Delete Item
                delete mBaseComponentList.takeAt(bcIndex);
            } else {
                // Remove Item
                mBaseComponentList.removeAt(bcIndex);
            }
            // End Remove Rows
            endRemoveRows();
        }
    }
}

//==============================================================================
// Set Base Component
//==============================================================================
void BaseComponentsModel::setBaseComponent(const int& aIndex, ComponentInfo* aComponent)
{
    // Check Component
    if (aComponent) {
        // Get Base Components Count
        int bcCount = mBaseComponentList.count();
        // Check Index
        if (aIndex >= 0 && aIndex < bcCount) {
            // Set Component Info
            mBaseComponentList[aIndex] = aComponent;
            // Emit Data Changed
            emit dataChanged(index(aIndex), index(aIndex));
        }
    }
}

//==============================================================================
// Get Component Index By Name
//==============================================================================
int BaseComponentsModel::getComponentIndex(const QString& aName)
{
    // Get Components Count
    int cCount = mBaseComponentList.count();
    // Iterate Through Components
    for (int i=0; i<cCount; i++) {
        // Get Component Info
        ComponentInfo* component = mBaseComponentList[i];
        // Check Component Name
        if (component->componentName() == aName) {
            return i;
        }
    }

    return -1;
}

//==============================================================================
// Get Component By Name
//==============================================================================
ComponentInfo* BaseComponentsModel::getComponent(const QString& aName)
{
    // Get Components Count
    int cCount = mBaseComponentList.count();
    // Iterate Through Components
    for (int i=0; i<cCount; i++) {
        // Get Component Info
        ComponentInfo* component = mBaseComponentList[i];
        // Check Component Name
        if (component->componentName() == aName) {
            return component;
        }
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int BaseComponentsModel::rowCount(const QModelIndex& ) const
{
    return mBaseComponentList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant BaseComponentsModel::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int row = index.row();
    // Check Row
    if (row >= 0 && row < mBaseComponentList.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case ComponentNameRole: return mBaseComponentList[row]->componentName();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> BaseComponentsModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Set Role Names
    rNames[ComponentNameRole] = "componentName";

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
