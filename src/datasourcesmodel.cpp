#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "datasourcesmodel.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
DataSourcesModel::DataSourcesModel(ProjectModel* aProjectModel, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProjectModel(aProjectModel)
    , mDataSourcesDir(mProjectModel ? mProjectModel->dataSourcesDir() : "")
{
    qDebug() << "DataSourcesModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void DataSourcesModel::init()
{
    // Load Data Sources
    //loadDataSources();
}

//==============================================================================
// Clear
//==============================================================================
void DataSourcesModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Get Keys Count
    int dskCount = rowCount();

    //qDebug() << "DataSourcesModel::clear - count: " << bckCount;

    // Iterate Thru Keys
    for (int i=0; i<dskCount; i++) {
        // Get Data Source Info
        ComponentInfo* component = mDataSources[mDataSources.keys()[i]];
        // Delete Component
        delete component;
    }

    // Clear
    mDataSources.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Data Sources
//==============================================================================
void DataSourcesModel::loadDataSources()
{
    // Check Data Sources Dir
    if (mDataSourcesDir.isEmpty()) {
        return;
    }

    //qDebug() << "DataSourcesModel::loadDataSources - mDataSourcesDir: " << mDataSourcesDir;

    // Init Info Filter
    QString infoFilter = QString("*.%1").arg(DEFAULT_JSON_SUFFIX);

    // Init Data Sources Dir Iterator
    QDirIterator dsIterator(mDataSourcesDir, QStringList(infoFilter), QDir::Files | QDir::NoDotAndDotDot);

    // Iterate Through Data Sources Dir
    while (dsIterator.hasNext()) {
        // Get Next Item
        dsIterator.next();
        // Get Item NAme
        QString itemName = dsIterator.fileInfo().baseName();

        //qDebug() << "DataSourcesModel::loadDataSources - itemName: " << itemName;

        // Check If Component HAs Been Already Loaded
        if (mDataSources.keys().indexOf(itemName) < 0) {
            // Get Item Path
            QString itemPath = dsIterator.filePath();
            //qDebug() << "DataSourcesModel::loadDataSources - itemPath: " << itemPath;
            // Create Data Source
            ComponentInfo* newComponent = ComponentInfo::fromInfoFile(itemPath, mProjectModel, false);
            // Add Data Source
            addDataSource(newComponent, false);
        } else {
            qDebug() << "DataSourcesModel::loadDataSources - itemName: " << itemName << " - Component Already Added.";
        }
    }

    // Update Live Data Sources QML Dir
    updateLiveDataSourcesQMLDir();
}

//==============================================================================
// Update Base Components
//==============================================================================
void DataSourcesModel::updateBaseComponents()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Get Data Sources Count
    int dsCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<dsCount; i++) {
        // Get Component
        ComponentInfo* component = getDataSourceByIndex(i);
        // Check Base Name
        if (component && !component->mBaseName.isEmpty() && !component->mBase) {
            //qDebug() << "DataSourcesModel::updateBaseComponents - name: " << component->mName;
            // Set Base Component
            component->setBaseComponent(mProjectModel->getComponentByName(component->mBaseName));
        }
    }
}

//==============================================================================
// Save All Components
//==============================================================================
void DataSourcesModel::saveAllComponents()
{
    // Get Components Count
    int dsCount = rowCount();
    // Iterate Through Data Sources Components
    for (int i=0; i<dsCount; i++) {
        // Get Component
        ComponentInfo* dataSource = mDataSources.value(mDataSources.keys()[i]);
        // Save
        dataSource->save();
    }
}

//==============================================================================
// Clear All Children
//==============================================================================
void DataSourcesModel::clearAllChildren(const bool& aClosing)
{
    // Get Base Components Count
    int bcCount = rowCount();
    // Iterate Through Base Components
    for (int i=0; i<bcCount; i++) {
        // Get Component
        ComponentInfo* component = mDataSources.value(mDataSources.keys()[i]);
        // Check Closing
        if (aClosing) {
            // Set Closing State
            component->setClosing(aClosing);
        }
        // Clear Children
        component->clearChildren();
    }
}

//==============================================================================
// Update Live Data Sources QML Dir
//==============================================================================
bool DataSourcesModel::updateLiveDataSourcesQMLDir()
{
    // Check Project Model
    if (!mProjectModel)  {
        return false;
    }

    // Init Live Data Sources QML Dir File Name
    QString ldsQMLDirFileName = QString("%1/%2/qmldir").arg(mProjectModel->liveTempDir()).arg(DEFAULT_PROJECT_DATASOURCES_DIR_NAME);
    // Init Live Data Sources QML Dir File
    QFile ldsQMLDirFile(ldsQMLDirFileName);

    // Open Live Data Sources QML Dir File
    if (ldsQMLDirFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream textStream(&ldsQMLDirFile);
        // Init Content
        QString content = "";
        // Get Data Sources Count
        int dsCount = rowCount();
        // Iterate Through Data Sources
        for (int i=0; i<dsCount; i++) {
            // Add Data Source
            content += QString("singleton %1 0.1 %1.qml\n").arg(mDataSources.keys()[i]);
        }

        // Add To Text Stream
        textStream << content;
        // Flush Text Stream
        textStream.flush();
        // Close Live Data Sources QMLDir  File
        ldsQMLDirFile.close();

        return true;
    }

    return false;
}

//==============================================================================
// Component Dirty State Changed Slot
//==============================================================================
void DataSourcesModel::componentDirtyChanged(const bool& aDirty)
{
    Q_UNUSED(aDirty);

    // Get Sender Component
    ComponentInfo* senderComponent = static_cast<ComponentInfo*>(sender());
    // Check Sender Component
    if (senderComponent) {
        //qDebug() << "DataSourcesModel::componentDirtyChanged - mName: " << senderComponent->mName << " - aDirty: " << aDirty;
        // Get Component Index
        int dsIndex = mDataSources.keys().indexOf(senderComponent->mName);
        // Check Component Index
        if (dsIndex >= 0) {
            // Emit Data Changed Signal
            emit dataChanged(index(dsIndex), index(dsIndex));
        }
    }
}

//==============================================================================
// Set Data Sources Dir
//==============================================================================
void DataSourcesModel::setDataSourcesDir(const QString& aDirPath)
{
    // Check Data Sources Dir
    if (mDataSourcesDir != aDirPath) {
        // Set Data Sources Dir
        mDataSourcesDir = aDirPath;
        // Clear
        clear();
        // Load Data Sources
        loadDataSources();
    }
}

//==============================================================================
// Add Data Source
//==============================================================================
bool DataSourcesModel::addDataSource(ComponentInfo* aDataSource, const bool& aUpdateLiveQMLDir)
{
    // Check Data Source
    if (aDataSource) {
        // Get Data Source Name
        QString dsName = aDataSource->mName;

        // Get Data Source
        ComponentInfo* component = mDataSources.value(dsName);

        // Check Component
        if (component) {
            qWarning() << "DataSourcesModel::addDataSource - name: " << dsName << " - ALREADY EXITS!";
            return false;
        }

        //qDebug() << "DataSourcesModel::addDataSource - name: " << cName;

        // Add Data Source To Data Source Map
        mDataSources[dsName] = aDataSource;

        // Connect Dirty Changed Signal
        connect(aDataSource, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));

        // Get New Key Index
        int newIndex = mDataSources.keys().indexOf(dsName);

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), newIndex, newIndex);

        // End Insert Rows
        endInsertRows();

        // Check Update Live QML Dir
        if (aUpdateLiveQMLDir) {
            // Update Live Data Sources QML Dir
            updateLiveDataSourcesQMLDir();
        }

        return true;
    }

    return false;
}

//==============================================================================
// Remove Data Source
//==============================================================================
bool DataSourcesModel::removeDataSource(const int& aIndex, const bool& aUpdateLiveQMLDir)
{
    // Get Data Sources Count
    int dsCount = rowCount();

    // Check Index
    if (aIndex >= 0 && aIndex < dsCount) {
        // Get Component
        ComponentInfo* component = getDataSourceByIndex(aIndex);
        // Get Info File
        QFile dsiFile(component->mInfoPath);
        // Get Key
        QString dsKey = mDataSources.keys()[aIndex];
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Key
        mDataSources.remove(dsKey);
        // Disonnect Dirty Changed Signal
        connect(component, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));
        // Delete Component
        delete component;
        // Delete Data Source Info File
        if (!dsiFile.remove()) {
            qWarning() << "DataSourcesModel::removeDataSource - ERROR REMOVING FILE!";
        }
        // End Remove Rows
        endRemoveRows();

        // Check Update Live QML Dir
        if (aUpdateLiveQMLDir) {
            // Update Live Data Sources QML Dir
            updateLiveDataSourcesQMLDir();
        }

        return true;
    }

    return false;
}

//==============================================================================
// Get Data Source Index By Name
//==============================================================================
int DataSourcesModel::getDataSourceIndex(const QString& aName)
{
    return mDataSources.keys().indexOf(aName);
}

//==============================================================================
// Get Data Source By Name
//==============================================================================
ComponentInfo* DataSourcesModel::getDataSource(const QString& aName, const bool& aPreload)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    // Get Data Source Info
    ComponentInfo* dsInfo = mDataSources.value(aName);

    // Check Data Source Info
    if (dsInfo) {
        return dsInfo;
    }

    // Check Preload
    if (aPreload) {
        // Get Full File Path
        QString dsFilePath = QString("%1/%2.%3").arg(mDataSourcesDir).arg(aName).arg(DEFAULT_JSON_SUFFIX);

        qDebug() << "DataSourcesModel::getDataSource - dsFilePath: " << dsFilePath << " - Trying to Load...";

        // Try To Load Component From Info File
        dsInfo = ComponentInfo::fromInfoFile(dsFilePath, mProjectModel, false);

        // Check Data Source Info
        if (dsInfo) {
            // Add Data Source
            addDataSource(dsInfo);
        }
    }

    return dsInfo;
}

//==============================================================================
// Get Data Source By Index
//==============================================================================
ComponentInfo* DataSourcesModel::getDataSourceByIndex(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mDataSources[mDataSources.keys()[aIndex]];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int DataSourcesModel::rowCount(const QModelIndex&) const
{
    return mDataSources.keys().count();
}

//==============================================================================
// Data
//==============================================================================
QVariant DataSourcesModel::data(const QModelIndex& index, int role) const
{
    // Get Data Source Row
    int dsRow = index.row();

    // Check Data Source Row
    if (dsRow >= 0 && dsRow < rowCount()) {
        // Get Data Source
        ComponentInfo* dataSource = mDataSources[mDataSources.keys()[dsRow]];
        // Switch Role
        switch (role) {
            default:
            case EDSRName:  return dataSource->mName;
            case EDSRDirty: return dataSource->mDirty;
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> DataSourcesModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    // Set Role Names
    rNames[EDSRName]    = "dsName";
    rNames[EDSRDirty]   = "dsDirty";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
DataSourcesModel::~DataSourcesModel()
{
    // Clear
    clear();

    qDebug() << "DataSourcesModel deleted.";
}
