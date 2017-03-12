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
    loadComponents();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Components List
    while (mComponentList.count() > 0) {
        // Delete Item
        delete mComponentList.takeLast();
    }

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

    qDebug() << "ComponentsModel::loadComponents - mComponentsDir: " << mComponentsDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Components Dir Iterator
    QDirIterator cIterator(mComponentsDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Components Dir
    while (cIterator.hasNext()) {
        // Get Next Item
        cIterator.next();
        // Get Item Path
        QString itemPath = cIterator.filePath();

        qDebug() << "ComponentsModel::loadComponents - itemPath: " << itemPath;

        // Create New Component Info
        ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel);
        // Add Component
        addComponent(newComponent);
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
void ComponentsModel::addComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (aComponent) {
        // Get Components Count
        int cCount = mComponentList.count();
        // Get Index Of Component
        int cIndex = mComponentList.indexOf(aComponent);
        // Check Component Index
        if (cIndex < 0) {
            // Begin Insert Rows
            beginInsertRows(QModelIndex(), cCount, cCount);
            // Append Component
            mComponentList << aComponent;
            // End Insert Rows
            endInsertRows();
        }
    }
}

//==============================================================================
// Remove Compoennt
//==============================================================================
void ComponentsModel::removeComponent(ComponentInfo* aComponent, const bool& aDelete)
{
    // Check Component
    if (aComponent) {
        // Get Components Count
        int cCount = mComponentList.count();
        // Get Index Of Component
        int cIndex = mComponentList.indexOf(aComponent);
        // Check Component Index
        if (cIndex >= 0 && cIndex < cCount) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), cIndex, cIndex);
            // Check Deletion
            if (aDelete) {
                // Delete Item
                delete mComponentList.takeAt(cIndex);
            } else {
                // Remove Item
                mComponentList.removeAt(cIndex);
            }
            // End Remove Rows
            endRemoveRows();
        }
    }
}

//==============================================================================
// Get Component Index By Name
//==============================================================================
int ComponentsModel::getComponentIndex(const QString& aName)
{
    // Get Components Count
    int cCount = mComponentList.count();
    // Iterate Through Components
    for (int i=0; i<cCount; i++) {
        // Get Component Info
        ComponentInfo* component = mComponentList[i];
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
ComponentInfo* ComponentsModel::getComponent(const QString& aName)
{
    // Get Components Count
    int cCount = mComponentList.count();
    // Iterate Through Components
    for (int i=0; i<cCount; i++) {
        // Get Component Info
        ComponentInfo* component = mComponentList[i];
        // Check Component Name
        if (component->componentName() == aName) {
            return component;
        }
    }

    return NULL;
}

//==============================================================================
// Get Compoennt By Index
//==============================================================================
ComponentInfo* ComponentsModel::getComponentByIndex(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mComponentList.count()) {
        return mComponentList[aIndex];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentsModel::rowCount(const QModelIndex& ) const
{
    return mComponentList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentsModel::data(const QModelIndex& index, int role) const
{
    // Ger Row
    int row = index.row();

    // Check Row
    if (row >= 0 && row < mComponentList.count()) {
        // Switch Role
        switch (role) {
            case Qt::DisplayRole:
            case Qt::UserRole:
            case ComponentNameRole: return mComponentList[row]->componentName();
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
    rNames[ComponentNameRole] = "componentName";

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

