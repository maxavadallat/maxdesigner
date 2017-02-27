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

    // Init Base Components Dir Iterator
    QDirIterator bcIterator(mBaseComponentsDir, QStringList(DEFAULT_JSON_SUFFIX), QDir::Files | QDir::NoDotAndDotDot);

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
            case Qt::UserRole:
            case ComponentNameRole: return mBaseComponentList[row]->property(JSON_KEY_COMPONENT_NAME).toString();
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
}





















/*
//==============================================================================
// Constructor
//==============================================================================
BaseComponentInfo::BaseComponentInfo(const QString& aName, QObject* aParent)
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
void BaseComponentInfo::init()
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
        qWarning() << "BaseComponentInfo::init - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Get Component Name
//==============================================================================
QString BaseComponentInfo::name()
{
    return mName;
}

//==============================================================================
// Save Info
//==============================================================================
void BaseComponentInfo::save()
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
        qWarning() << "BaseComponentInfo::save - FILE OPEN ERROR - mName: " << mName;
    }
}

//==============================================================================
// Destructor
//==============================================================================
BaseComponentInfo::~BaseComponentInfo()
{
    // ...
}
*/
