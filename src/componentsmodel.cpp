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

    // Init Components Dir Iterator
    QDirIterator cIterator(mComponentsDir, QStringList(DEFAULT_JSON_SUFFIX), QDir::Files | QDir::NoDotAndDotDot);

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
            case ComponentNameRole: return mComponentList[row]->property(JSON_KEY_COMPONENT_NAME).toString();
        }
    }

    return "";
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
}


















/*
//==============================================================================
// Constructor
//==============================================================================
ComponentInfo::ComponentInfo(const QString& aName, QObject* aParent)
    : QObject(aParent)
    , mName(aName)
{
    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void ComponentInfo::init()
{
    // Init JSON File
    QFile infoFile(mName);

    // Open File
    if (infoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read All
        QString infoText = infoFile.readAll();
        // Close File
        infoFile.close();
        // Init JSON Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(infoText.toUtf8());
        // Set JSON Object
        mInfo = jsonDoc.object();
    } else {
        qWarning() << "ComponentInfo::init - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Get Component Name
//==============================================================================
QString ComponentInfo::name()
{
    return mName;
}

//==============================================================================
// Save Info
//==============================================================================
void ComponentInfo::save()
{
    // Init Info File
    QFile infoFile(mName);

    // Open File For Save
    if (infoFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init JSON Document
        QJsonDocument jsonDoc(mInfo);
        // Init JSON Text
        QString infoText = jsonDoc.toJson();
        // Init Text Stream
        QTextStream textStream(&infoFile);
        // Write Info Text
        textStream << infoText;
        // Flush
        textStream.flush();
        // Close File
        infoFile.close();
    } else {
        qWarning() << "ComponentInfo::save - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentInfo::~ComponentInfo()
{
    // ...
}
*/
