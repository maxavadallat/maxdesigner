#include <QJsonDocument>
#include <QJsonArray>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

#include "projectmodel.h"
#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "componentinfo.h"
#include "viewsmodel.h"
#include "datasourcesmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ProjectModel::ProjectModel(QObject* parent)
    : QObject(parent)
    , mName("")
    , mDirty(false)
    , mPropertiesController(NULL)
    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mViews(NULL)
    , mDataSources(NULL)
{
    qDebug() << "ProjectModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ProjectModel::init()
{
    // ...
}

//==============================================================================
// Set Project Properties Dirty State
//==============================================================================
void ProjectModel::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        // Set Dirty State
        mDirty = aDirty;
        // Emit Properties Dirty State Changed Signal
        emit dirtyChanged(mDirty);
    }
}

//==============================================================================
// Create Base Components Model
//==============================================================================
void ProjectModel::createBaseComponentsModel()
{
    // Check Base Compoennts Model
    if (!mBaseComponents) {
        // Create Base Compoennts Model
        BaseComponentsModel* newModel = new BaseComponentsModel(this);
        // Set Base Components Model
        setBaseComponentsModel(newModel);
    }

    // Load Base Components
    mBaseComponents->loadBaseComponents();
}

//==============================================================================
// Create Components Model
//==============================================================================
void ProjectModel::createComponentsModel()
{
    // Check Components Model
    if (!mComponents) {
        // Create New Components Model
        ComponentsModel* newModel = new ComponentsModel(this);
        // Set Components Model
        setComponentsModel(newModel);
    }

    // Load Components
    mComponents->loadComponents();
}

//==============================================================================
// Create Views Model
//==============================================================================
void ProjectModel::createViewsModel()
{
    // Check Views Model
    if (!mViews) {
        // Create New Views Model
        ViewsModel* newModel = new ViewsModel(this);
        // Set Views Model
        setViewsModel(newModel);
    }

    // Load Views
    mViews->loadViews();
}

//==============================================================================
// Create Data Sources Model
//==============================================================================
void ProjectModel::createDataSourcesModel()
{
    // Check Data Sources Model
    if (!mDataSources) {
        // Create New Data Sources Model
        DataSourcesModel* newModel = new DataSourcesModel(this);
        // Set Data Sources Model
        setDataSourcesModel(newModel);
    }

    // Load Data Sources
    mDataSources->loadDataSources();
}

//==============================================================================
// Set Properties Controller
//==============================================================================
void ProjectModel::setPropertiesController(PropertiesController* aController)
{
    // Check Properties Controller
    if (mPropertiesController != aController) {
        // Set Properties Contorller
        mPropertiesController = aController;
        // Emit Properties Controller Changed Signal
        emit propertiesControllerChanged(mPropertiesController);
    }
}

//==============================================================================
// Set Base Components Model
//==============================================================================
void ProjectModel::setBaseComponentsModel(BaseComponentsModel* aBaseComponents)
{
    // Check Base Components Model
    if (mBaseComponents != aBaseComponents) {
        // Set Base Components Model
        mBaseComponents = aBaseComponents;
        // Emit Base Compoennts Model Changed Signal
        emit baseComponentsModelChanged(mBaseComponents);
    }
}

//==============================================================================
// Set Components Model
//==============================================================================
void ProjectModel::setComponentsModel(ComponentsModel* aComponents)
{
    // Check Components Model
    if (mComponents != aComponents) {
        // Set Components Model
        mComponents = aComponents;
        // Emit Compoennts Model Changed Signal
        emit componentsModelChanged(mComponents);
    }
}

//==============================================================================
// Set Views Model
//==============================================================================
void ProjectModel::setViewsModel(ViewsModel* aViews)
{
    // Check Views Model
    if (mViews != aViews) {
        // Set Views Model
        mViews = aViews;
        // Emit Views Model Changed Signal
        emit viewsModelChanged(mViews);
    }
}

//==============================================================================
// Set Data Sources Model
//==============================================================================
void ProjectModel::setDataSourcesModel(DataSourcesModel* aDataSources)
{
    // Check Data Sources
    if (mDataSources != aDataSources) {
        // Set Data Sources
        mDataSources = aDataSources;
        // Emit Data Sources Changed Signal
        emit dataSourcesModelChanged(mDataSources);
    }
}

//==============================================================================
// Update Components And Children
//==============================================================================
void ProjectModel::updateBaseComponents()
{
    qDebug() << "ProjectModel::updateBaseComponents";

    // Base Components
    if (mBaseComponents) {
        // Update Base Components
        mBaseComponents->updateBaseComponents();
    }

    // Components
    if (mComponents) {
        // Update Base Components
        mComponents->updateBaseComponents();
    }

    // Views
    if (mViews) {
        // Update Base Components
        mViews->updateBaseComponents();
    }

    // ...
}

//==============================================================================
// Init New Project
//==============================================================================
bool ProjectModel::initProject(const QString& aName, const QString& aDir)
{
    // Check Name
    if (!aName.isEmpty() && !aDir.isEmpty()) {
        qDebug() << "ProjectModel::initProject - aName: " << aName << " - aDir: " << aDir;

        // Set Project Name
        setProjectName(aName);
        // Set Project Dir
        setProjectDir(aDir + "/" + aName);

        // Set Base Components Dir
        setBaseComponentsDir(projectDir() + "/" + DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME);
        // Set Components Dir
        setComponentsDir(projectDir() + "/" + DEFAULT_PROJECT_COMPONENTS_DIR_NAME);
        // Set Views Dir
        setViewsDir(projectDir() + "/" + DEFAULT_PROJECT_VIEWS_DIR_NAME);
        // Set Data Sources Dir
        setDataSourcesDir(projectDir() + "/" + DEFAULT_PROJECT_DATASOURCES_DIR_NAME);
        // Set Assets Dir
        setAssetsDir(projectDir() + "/" + DEFAULT_PROJECT_ASSETS_DIR_NAME);

        // Init Project Dir
        QString pDirPath(projectDir());
        // Init Project Dir
        QDir pDir(pDirPath);

        // Check If Dir Exists and Create
        if (!pDir.exists() && !pDir.mkpath(pDirPath)) {
            qWarning() << "ProjectModel::initProject - path: " << pDirPath << " - ERROR CREATING PATH!!";

            return false;
        }

        // Create Live Temp Dir
        if (!pDir.exists(DEFAULT_PROJECT_LIVE_TEMP_DIR_NAME) && !pDir.mkdir(DEFAULT_PROJECT_LIVE_TEMP_DIR_NAME)) {
            qWarning() << "ProjectModel::initProject - livetemp: " << DEFAULT_PROJECT_LIVE_TEMP_DIR_NAME << " - ERROR CREATING PATH!!";

            return false;
        }

        // Create Base Components Model
        createBaseComponentsModel();
        // Create Components Model
        createComponentsModel();
        // Create Views Model
        createViewsModel();
        // Create Data Sources Model
        createDataSourcesModel();

        // ...

        return true;
    }

    return false;
}

//==============================================================================
// Load Project
//==============================================================================
bool ProjectModel::loadProject(const QString& aFileName)
{
    // Init JSON File
    QFile jsonFile(aFileName);

    // Open File For Reading
    if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ProjectModel::loadProject - aFileName: " << aFileName;
        // Init JSON Content
        QString jsonContent;
        // Read All
        jsonContent = jsonFile.readAll();
        // Close File
        jsonFile.close();

        // Init JSON Document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent.toUtf8());
        // Set Properties
        mProperties = jsonDoc.object();

        // Emit Changes
        emit projectNameChanged(projectName());
        emit projectDirChanged(projectDir());
        emit assetsDirChanged(assetsDir());
        emit baseComponentsDirChanged(baseComponentsDir());
        emit componentsDirChanged(componentsDir());
        emit viewsDirChanged(viewsDir());
        emit dataSourcesDirChanged(dataSourcesDir());
        emit importPathsChanged(importPaths());
        emit pluginPathsChanged(pluginPaths());

        // ...

        // Create Base Components Model
        createBaseComponentsModel();
        // Create Components Model
        createComponentsModel();
        // Create Views Model
        createViewsModel();
        // Create Data Sources Model
        createDataSourcesModel();

        // Update Base Components
        updateBaseComponents();

        //qDebug() << "ProjectModel::loadProject - aFileName: " << aFileName << " - DONE.";

        // Emit Project Loaded Signal
        emit projectLoaded();

        return true;
    }

    qWarning() << "ProjectModel::loadProject - aFileName: " << aFileName << " - ERROR LOADING PROJECT!";

    return false;
}

//==============================================================================
// Save Project
//==============================================================================
bool ProjectModel::saveProject(const QString& aFileName)
{
    // Check Dirty Properties
    if (!mDirty) {
        return true;
    }

    // Init Save File Name
    QString saveFileName(aFileName);

    // Check File Name
    if (saveFileName.isEmpty()) {
        // Set Save File Name
        saveFileName = absoluteProjectFilePath();
    }

    qDebug() << "ProjectModel::saveProject - saveFileName: " << saveFileName;

    // Init Project File Info
    QFileInfo pfInfo(saveFileName);
    // Get Project File Absolute Path
    QString pfaPath = pfInfo.absolutePath();

    // Init Temp Dir
    QDir tempDir;

    // Try to Make Path
    if (!QFileInfo::exists(pfaPath) && !tempDir.mkpath(pfaPath)) {
        qWarning() << "ProjectModel::saveProject - pfaPath: " << pfaPath << " - ERROR CREATING PROJECT PATH!";
    }

    // Init JSON File
    QFile jsonFile(saveFileName);
    // Open File For Reading
    if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream textStream(&jsonFile);
        // Init JSON Document
        QJsonDocument jsonDocument(mProperties);
        // Write Document To Text Stream
        textStream << jsonDocument.toJson();
        // Flush
        textStream.flush();
        // Close File
        jsonFile.close();

        // Reset Dirty Properties
        setDirty(false);

        return true;
    }

    qWarning() << "ProjectModel::saveProject - saveFileName: " << saveFileName << " - ERROR SAVING PROJECT!";

    return false;
}

//==============================================================================
// Close Project
//==============================================================================
void ProjectModel::closeProject(const bool& aSave)
{
    //qDebug() << "ProjectModel::closeProject - aSave: " << aSave;

    // Check Save
    if (aSave) {
        // Save Project
        saveProject();
    }

    // Check Base Components Model
    if (mBaseComponents) {
        // Delete Base Components Model
        delete mBaseComponents;
        mBaseComponents = NULL;
        // Set Base Components Model
        setBaseComponentsModel(mBaseComponents);
    }

    // Check Components Model
    if (mComponents) {
        // Delete Components Model
        delete mComponents;
        mComponents = NULL;
        // Set Components Model
        setComponentsModel(mComponents);
    }

    // Check Views Model
    if (mViews) {
        // Delete Views Model
        delete mViews;
        mViews = NULL;
        // Set Views Model
        setViewsModel(mViews);
    }

    // Check Data Sources
    if (mDataSources) {
        // Delete Data Sources Model
        delete mDataSources;
        mDataSources = NULL;
        // Set Data Sources
        setDataSourcesModel(mDataSources);
    }
}

//==============================================================================
// Save All Components
//==============================================================================
void ProjectModel::saveAllComponents()
{
    qDebug() << "ProjectModel::saveAllComponents" ;

    // Check Base Components Model
    if (mBaseComponents) {
        // Save All Components
        mBaseComponents->saveAllComponents();
    }

    // Check Components Model
    if (mComponents) {
        // Save All Components
        mComponents->saveAllComponents();
    }

    // Check Views Model
    if (mViews) {
        // Save All Components
        mViews->saveAllComponents();
    }

    // Check Data Sources
    if (mDataSources) {
        // Save All Components
        mDataSources->saveAllComponents();
    }
}

//==============================================================================
// Get Absolute Project Path
//==============================================================================
QString ProjectModel::absoluteProjectPath()
{
    return  mProperties[JSON_KEY_PROJECT_DIR].toString();
}

//==============================================================================
// Get Absolute Project File Path
//==============================================================================
QString ProjectModel::absoluteProjectFilePath()
{
    // Init Absolute Project File Path
    QString apfPath = "";

    // Set Save File Name
    apfPath += mProperties[JSON_KEY_PROJECT_DIR].toString() + "/";
    apfPath += (mProperties[JSON_KEY_PROJECT_NAME].toString() + "." + DEFAULT_JSON_SUFFIX);

    return apfPath;
}

//==============================================================================
// Create Base Component
//==============================================================================
ComponentInfo* ProjectModel::createBaseComponent(const QString& aName,
                                                 const QString& aBaseName,
                                                 const QString& aCategory,
                                                 const bool& aBuiltIn,
                                                 const int& aWidth,
                                                 const int& aHeight)
{
    // Check Base Components
    if (!mBaseComponents) {
        return NULL;
    }

    // Get Component Info
    ComponentInfo* cInfo = mBaseComponents->getComponent(aName);
    // Check Component Info
    if (cInfo) {
        //qDebug() << "ProjectModel::createBaseComponent - aName: " << aName << " - COMPONENT ALREADY EXISTS!";
        return cInfo;
    }

    //qDebug() << "ProjectModel::createBaseComponent - aName: " << aName << " - aBaseName: " << aBaseName << " - aCategory: " << aCategory;

    // Create New Component
    ComponentInfo* newComponent = new ComponentInfo(aName, COMPONENT_TYPE_BASECOMPONENT, aCategory, this, aBaseName, aBuiltIn);

    // Check Width & Height
    if (aWidth > 0 && aHeight > 0) {
        // Set Width & Height
        newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH, aWidth);
        newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT, aHeight);
    }

    // Add To Base Components
    mBaseComponents->addBaseComponent(newComponent);

    // Emit Base Compoennt Created Signal
    emit baseComponentCreated(newComponent, aWidth, aHeight);

    return newComponent;
}

//==============================================================================
// Create Component
//==============================================================================
ComponentInfo* ProjectModel::createComponent(const QString& aName, const QString& aBaseName, const QString& aCategory, const int& aWidth, const int& aHeight)
{
    // Check Components
    if (!mComponents) {
        return NULL;
    }

    // Get Component Info
    ComponentInfo* cInfo = mComponents->getComponent(aName);
    // Check Component Info
    if (cInfo) {
        //qDebug() << "ProjectModel::createComponent - aName: " << aName << " - COMPONENT ALREADY EXISTS!";
        return cInfo;
    }

    //qDebug() << "ProjectModel::createComponent - aName: " << aName << " - aBaseName: " << aBaseName << " - aCategory: " << aCategory;

    // Create New Component
    ComponentInfo* newComponent = new ComponentInfo(aName, COMPONENT_TYPE_COMPONENT, aCategory, this, aBaseName);

    // Check Width & Height
    if (aWidth > 0 && aHeight > 0) {
        // Set Width & Height
        newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH, aWidth);
        newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT, aHeight);
    }

    // Add To Components
    mComponents->addComponent(newComponent);

    // Emit Component Created Signal
    emit componentCreated(newComponent, aWidth, aHeight);

    return newComponent;
}

//==============================================================================
// Create View
//==============================================================================
ComponentInfo* ProjectModel::createView(const QString& aName, const QString& aBaseName, const int& aWidth, const int& aHeight)
{
    // Check Views Model
    if (!mViews) {
        return NULL;
    }

    // Get Component Info
    ComponentInfo* cInfo = mViews->getView(aName);
    // Check Component Info
    if (cInfo) {
        //qDebug() << "ProjectModel::createView - aName: " << aName << " - VIEW ALREADY EXISTS!";
        return cInfo;
    }

    //qDebug() << "ProjectModel::createView - aName: " << aName << " - aBaseName: " << aBaseName;

    // Create New Component
    ComponentInfo* newComponent = new ComponentInfo(aName, COMPONENT_TYPE_VIEW, COMPONENT_CATEGORY_VISUAL, this, aBaseName);

    // Set Width & Height
    newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH, aWidth);
    newComponent->setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT, aHeight);

    // Add To Views
    mViews->addView(newComponent);

    // Emit View Created Signal
    emit viewCreated(newComponent, aWidth, aHeight);

    return newComponent;
}

//==============================================================================
// Create Data Source
//==============================================================================
ComponentInfo* ProjectModel::createDataSource(const QString& aName, const QString& aBaseName)
{
    // Check Data Sources Model
    if (!mDataSources) {
        return NULL;
    }

    // Get Data Source
    ComponentInfo* dataSource = mDataSources->getDataSource(aName);
    // Check Data Source
    if (dataSource) {
        return dataSource;
    }

    // Create New Data Source Component
    ComponentInfo* newComponent = new ComponentInfo(aName, COMPONENT_TYPE_DATASOURCE, COMPONENT_CATEGORY_NONVISUAL, this, aBaseName);

    // Add Data Source
    mDataSources->addDataSource(newComponent);

    // Emit Data Source Created Signal
    emit dataSourceCreated(newComponent);

    return newComponent;
}

//==============================================================================
// Get Project Name
//==============================================================================
QString ProjectModel::projectName()
{
    return mProperties[JSON_KEY_PROJECT_NAME].toString();
}

//==============================================================================
// Set Project Name
//==============================================================================
void ProjectModel::setProjectName(const QString& aName)
{
    // Check Name
    if (aName != projectName()) {
        //qDebug() << "ProjectModel::setProjectName - aName: " << aName;
        // Set Project Name
        mProperties[JSON_KEY_PROJECT_NAME] = aName;
        // Emit Project Name Changed
        emit projectNameChanged(mProperties[JSON_KEY_PROJECT_NAME].toString());
        // Emit Project File Path Changed Signal
        emit projectFilePathChanged(absoluteProjectFilePath());
        // Emit Live Temp Dir Changed
        emit liveTempDirChanged(liveTempDir());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Project Dir
//==============================================================================
QString ProjectModel::projectDir()
{
    return mProperties[JSON_KEY_PROJECT_DIR].toString();
}

//==============================================================================
// Set Project Dir
//==============================================================================
void ProjectModel::setProjectDir(const QString& aDir)
{
    // Check Dir
    if (aDir != projectDir()) {
        //qDebug() << "ProjectModel::setProjectDir - aDir: " << aDir;
        // Set Project Dir
        mProperties[JSON_KEY_PROJECT_DIR] = aDir;
        // Emit Project Dir Changed
        emit projectDirChanged(mProperties[JSON_KEY_PROJECT_DIR].toString());
        // Emit Project File Path Changed Signal
        emit projectFilePathChanged(absoluteProjectFilePath());
        // Emit Live Temp Dir Changed
        emit liveTempDirChanged(liveTempDir());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Project Screen Width
//==============================================================================
int ProjectModel::screenWidth()
{
    return mProperties[JSON_KEY_PROJECT_SCREEN_WIDTH].toInt();
}

//==============================================================================
// Set Project Screen Width
//==============================================================================
void ProjectModel::setScreenWidth(const int& aWidth)
{
    // Check Screen Width
    if (aWidth != screenWidth()) {
        // Set Screen Width
        mProperties[JSON_KEY_PROJECT_SCREEN_WIDTH] = aWidth;
        // Emit Screen Width Changed Signal
        emit screenWidthChanged(screenWidth());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Project Screen Height
//==============================================================================
int ProjectModel::screenHeight()
{
    return mProperties[JSON_KEY_PROJECT_SCREEN_HEIGHT].toInt();
}

//==============================================================================
// Set Project Screen Height
//==============================================================================
void ProjectModel::setScreenHeight(const int& aHeight)
{
    // Check Screen Height
    if (aHeight != screenHeight()) {
        // Set Screen Height
        mProperties[JSON_KEY_PROJECT_SCREEN_HEIGHT] = aHeight;
        // Emit Screen Height changed Signal
        emit screenHeightChanged(screenHeight());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Assets Dir
//==============================================================================
QString ProjectModel::assetsDir()
{
    return mProperties[JSON_KEY_PROJECT_ASSETS_DIR].toString();
}

//==============================================================================
// Set Images Dir
//==============================================================================
void ProjectModel::setAssetsDir(const QString& aImagesDir)
{
    // Check Images Dir
    if (aImagesDir != assetsDir()) {
        // Set Images Dir
        mProperties[JSON_KEY_PROJECT_ASSETS_DIR] = aImagesDir;
        // Emit Images Dir Changed Signal
        emit assetsDirChanged(mProperties[JSON_KEY_PROJECT_ASSETS_DIR].toString());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
 // Get Base Components Dir
//==============================================================================
QString ProjectModel::baseComponentsDir()
{
    return mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR].toString();
}

//==============================================================================
// Set Base Components Dir
//==============================================================================
void ProjectModel::setBaseComponentsDir(const QString& aBaseComponentsDir)
{
    // Check Base Components Dir
    if (aBaseComponentsDir != baseComponentsDir()) {
        //qDebug() << "ProjectModel::setBaseComponentsDir - aBaseComponentsDir: " << aBaseComponentsDir;
        // Set Base Components Dir
        mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR] = aBaseComponentsDir;

        // Check Base Components Model
        if (mBaseComponents) {
            // Set Base Components Dir
            mBaseComponents->setBaseComponentsDir(aBaseComponentsDir);
        }

        // Emit Base Components Dir Changed Signal
        emit baseComponentsDirChanged(mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR].toString());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Compoennts Dir
//==============================================================================
QString ProjectModel::componentsDir()
{
    return mProperties[JSON_KEY_PROJECT_COMPONENTS_DIR].toString();
}

//==============================================================================
// Set Compoennts Dir
//==============================================================================
void ProjectModel::setComponentsDir(const QString& aComponentsDir)
{
    // Check Components Dir
    if (aComponentsDir != componentsDir()) {
        // Set Components Dir
        mProperties[JSON_KEY_PROJECT_COMPONENTS_DIR] = aComponentsDir;

        // Check Components Model
        if (mComponents) {
            // Set Components Dir
            mComponents->setComponentsDir(aComponentsDir);
        }

        // Emit Components Dir Changed Signal
        emit componentsDirChanged(mProperties[JSON_KEY_PROJECT_COMPONENTS_DIR].toString());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Views Dir
//==============================================================================
QString ProjectModel::viewsDir()
{
    return mProperties[JSON_KEY_PROJECT_VIEWS_DIR].toString();
}

//==============================================================================
// Set Views Dir
//==============================================================================
void ProjectModel::setViewsDir(const QString& aViewsDir)
{
    // Check Views Dir
    if (aViewsDir != viewsDir()) {
        // Set Views Dir
        mProperties[JSON_KEY_PROJECT_VIEWS_DIR] = aViewsDir;

        // Check Views Model
        if (mViews) {
            // Set Views Dir
            mViews->setViewsDir(aViewsDir);
        }

        // Emit Views Dir Changed Signal
        emit viewsDirChanged(mProperties[JSON_KEY_PROJECT_VIEWS_DIR].toString());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Data Sources Dir
//==============================================================================
QString ProjectModel::dataSourcesDir()
{
    return mProperties[JSON_KEY_PROJECT_DATASOURCES_DIR].toString();
}

//==============================================================================
// Set Data Sources Dir
//==============================================================================
void ProjectModel::setDataSourcesDir(const QString& aDataSourcesDir)
{
    // Check Views Dir
    if (aDataSourcesDir != dataSourcesDir()) {
        // Set Views Dir
        mProperties[JSON_KEY_PROJECT_DATASOURCES_DIR] = aDataSourcesDir;

        // Check Data Sources Model
        if (mDataSources) {
            // Set Set Data Sources Dir
            mDataSources->setDataSourcesDir(aDataSourcesDir);
        }

        // Emit Data Sources Dir Changed Signal
        emit dataSourcesDirChanged(mProperties[JSON_KEY_PROJECT_DATASOURCES_DIR].toString());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Get Live Temp Dir
//==============================================================================
QString ProjectModel::liveTempDir()
{
    return QString("%1/%2").arg(mProperties[JSON_KEY_PROJECT_DIR].toString()).arg(DEFAULT_PROJECT_LIVE_TEMP_DIR_NAME);
}

//==============================================================================
// Get Import Paths
//==============================================================================
QStringList ProjectModel::importPaths()
{
    // Init Import Paths
    QStringList iPaths;
    // Get JSON Array
    QJsonArray array = mProperties[JSON_KEY_PROJECT_IMPORT_PATHS].toArray();

    // Iterate Thru JSON Array
    for (int i=0; i < array.size(); i++) {
        // Append Item to String List
        iPaths << array[i].toString();
    }

    return iPaths;
}

//==============================================================================
// Add Import Path
//==============================================================================
void ProjectModel::addImportPath(const QString& aPath)
{
    // Take JSON Array
    QJsonArray jsonArray = mProperties.take(JSON_KEY_PROJECT_IMPORT_PATHS).toArray();

    // Init New JSON Value
    QJsonValue jsonValue(aPath);

    // Check Import Path
    if (!jsonArray.contains(jsonValue)) {
        // Append To JSON Array
        jsonArray << jsonValue;
        // Set Import Paths
        mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = jsonArray;
        // Emit Import Path Added Signal
        emit importPathAdded(aPath);
        // Emit Import Paths Changed Signal
        emit importPathsChanged(importPaths());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Remove Import Path
//==============================================================================
void ProjectModel::removeImportPath(const int& aIndex)
{
    // Take JSON Array
    QJsonArray jsonArray = mProperties.take(JSON_KEY_PROJECT_IMPORT_PATHS).toArray();

    // Check Index
    if (aIndex >= 0 && aIndex < jsonArray.size()) {
        // Get Import Path
        QString rImportPath = jsonArray[aIndex].toString();
        // Remove Value At Index
        jsonArray.removeAt(aIndex);
        // Set Import Paths
        mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = jsonArray;
        // Emit Import Path Removed Signal
        emit importPathRemoved(rImportPath);
        // Emit Import Paths Changed Signal
        emit importPathsChanged(importPaths());
        // Set Dirty Properties
        setDirty(true);
    } else {
        // Set Import Paths
        mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = jsonArray;
    }
}

//==============================================================================
// Set Import Paths
//==============================================================================
void ProjectModel::setImportPaths(const QStringList& aImportPaths)
{
    // Set Import Paths
    mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = QJsonArray::fromStringList(aImportPaths);
    // Set Dirty Properties
    setDirty(true);
}

//==============================================================================
// Get Plugin Paths
//==============================================================================
QStringList ProjectModel::pluginPaths()
{
    // Init Plugin Paths
    QStringList pPaths;

    // Get JSON Array
    QJsonArray array = mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS].toArray();

    // Iterate Thru JSON Array
    for (int i=0; i < array.size(); i++) {
        // Append Item to String List
        pPaths << array[i].toString();
    }

    return pPaths;
}

//==============================================================================
// Add Plugin Path
//==============================================================================
void ProjectModel::addPluginPath(const QString& aPath)
{
    // Take JSON Array
    QJsonArray jsonArray = mProperties.take(JSON_KEY_PROJECT_PLUGIN_PATHS).toArray();

    // Init New JSON Value
    QJsonValue jsonValue(aPath);

    // Check Import Path
    if (!jsonArray.contains(jsonValue)) {
        // Append To JSON Array
        jsonArray << jsonValue;
        // Set Plugin Paths
        mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS] = jsonArray;
        // Emit Plugin Path Added Signal
        emit pluginPathAdded(aPath);
        // Emit Plugin Paths Changed Signal
        emit pluginPathsChanged(pluginPaths());
        // Set Dirty Properties
        setDirty(true);
    }
}

//==============================================================================
// Remove Plugin Path
//==============================================================================
void ProjectModel::removePluginPath(const int& aIndex)
{
    // Take JSON Array
    QJsonArray jsonArray = mProperties.take(JSON_KEY_PROJECT_PLUGIN_PATHS).toArray();

    // Check Index
    if (aIndex >= 0 && aIndex < jsonArray.size()) {
        // Get Plugin Path
        QString rPluginPath = jsonArray[aIndex].toString();
        // Remove Value At Index
        jsonArray.removeAt(aIndex);
        // Set Plugin Paths
        mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS] = jsonArray;
        // Emit Plugin Path Removed Signal
        emit pluginPathRemoved(rPluginPath);
        // Emit Import Paths Changed Signal
        emit pluginPathsChanged(importPaths());
        // Set Dirty Properties
        setDirty(true);
    } else {
        // Set Plugin Paths
        mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS] = jsonArray;
    }
}

//==============================================================================
// Set Plugin Paths
//==============================================================================
void ProjectModel::setPluginPaths(const QStringList& aPluginPaths)
{
    // Set Plugin Paths
    mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS] = QJsonArray::fromStringList(aPluginPaths);
    // Set Dirty Properties
    setDirty(true);
}

//==============================================================================
// Get Properties Controller
//==============================================================================
PropertiesController* ProjectModel::propertiesController()
{
    return mPropertiesController;
}

//==============================================================================
// Get Base Component Model
//==============================================================================
BaseComponentsModel* ProjectModel::baseComponentsModel()
{
    return mBaseComponents;
}

//==============================================================================
// Get Components Model
//==============================================================================
ComponentsModel* ProjectModel::componentsModel()
{
    return mComponents;
}

//==============================================================================
// Get Views Model
//==============================================================================
ViewsModel* ProjectModel::viewsModel()
{
    return mViews;
}

//==============================================================================
// Get Data Sources Model
//==============================================================================
DataSourcesModel* ProjectModel::dataSourcesModel()
{
    return mDataSources;
}

//==============================================================================
// Get Component By Name
//==============================================================================
ComponentInfo* ProjectModel::getComponentByName(const QString& aName, const QString& aType, const bool& aPreload)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    //qDebug() << "ProjectModel::getComponentByName - aName: " << aName << " - aType: " << aType;

    // Init Component Info
    ComponentInfo* cInfo = NULL;

    // Check Base Components Model & Type
    if (mBaseComponents && ((aType == COMPONENT_TYPE_BASECOMPONENT) || (aType == ""))) {
        // Get Component Info
        cInfo = mBaseComponents->getComponent(aName, aPreload);
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check Components Model & Type
    if (mComponents && ((aType == COMPONENT_TYPE_COMPONENT) || (aType == ""))) {
        // Get Component Info
        cInfo = mComponents->getComponent(aName, aPreload);
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check Views Model & Type
    if (mViews && ((aType == COMPONENT_TYPE_VIEW) || (aType == ""))) {
        // Get Component Info
        cInfo = mViews->getView(aName, aPreload);
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check Data Sources
    if (mDataSources && ((aType == COMPONENT_TYPE_DATASOURCE) || (aType == ""))) {
        // Get Data Source
        cInfo = mDataSources->getDataSource(aName, aPreload);
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    return cInfo;
}

//==============================================================================
// Get Component By File Path
//==============================================================================
ComponentInfo* ProjectModel::getComponentByPath(const QString& aFilePath)
{
    // Check Name
    if (aFilePath.isEmpty()) {
        return NULL;
    }

    // Init File Info
    QFileInfo cFileInfo(aFilePath);

    // Check Suffix
    if (cFileInfo.suffix() != DEFAULT_JSON_SUFFIX) {
        // Not a Component
        return NULL;
    }

    //qDebug() << "ProjectModel::getComponentByPath - aFilePath: " << aFilePath;

    // Init Component Info
    ComponentInfo* cInfo = NULL;

    // Check For Base Compoennts
    if (mBaseComponents && cFileInfo.absolutePath() == mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR].toString()) {
        // Get Component Info
        cInfo = mBaseComponents->getComponent(cFileInfo.baseName());
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check For Compoennts
    if (mComponents && cFileInfo.absolutePath() == mProperties[JSON_KEY_PROJECT_COMPONENTS_DIR].toString()) {
        // Get Component Info
        cInfo = mComponents->getComponent(cFileInfo.baseName());
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check For Compoennts
    if (mViews && cFileInfo.absolutePath() == mProperties[JSON_KEY_PROJECT_VIEWS_DIR].toString()) {
        // Get Component Info
        cInfo = mViews->getView(cFileInfo.baseName());
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // Check For Compoennts
    if (mDataSources && cFileInfo.absolutePath() == mProperties[JSON_KEY_PROJECT_DATASOURCES_DIR].toString()) {
        // Get Component Info
        cInfo = mDataSources->getDataSource(cFileInfo.baseName());
        // Check Component Info
        if (cInfo) {
            return cInfo;
        }
    }

    // ...

    return cInfo;
}

//==============================================================================
// Generate Live Code
//==============================================================================
QString ProjectModel::generateLiveCode(const QString& aName, const QString& aContent)
{
    // Check Content
    if (aContent.isEmpty() || aName.isEmpty()) {
        return "";
    }

    qDebug() << "ProjectModel::generateLiveCode - aName: " << aName;

    // Init Live Code File Name
    QString fileName = QString("%1/%2Live.%3").arg(liveTempDir()).arg(aName).arg(DEFAULT_QML_SUFFIX);

    // Init Live Code File
    QFile liveFile(fileName);

    // Open File
    if (liveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream liveStream(&liveFile);

        // Write Content
        liveStream << aContent;

        // Close File
        liveFile.close();

        return fileName;
    }

    // ...

    return "";
}

//==============================================================================
// Delete Live Code
//==============================================================================
void ProjectModel::removeLiveCode(const QString& aName)
{
    // Chekc Name
    if (aName.isEmpty()) {
        return;
    }

    qDebug() << "ProjectModel::removeLiveCode - aName: " << aName;

    // Init Live Code File Name
    QString fileName = QString("%1/%2Live.%3").arg(liveTempDir()).arg(aName).arg(DEFAULT_QML_SUFFIX);

    // Init Live Code File
    QFile liveFile(fileName);

    // Check If File Exists
    if (liveFile.exists()) {
        // Remove File
        liveFile.remove();
    }
}

//==============================================================================
// Destructor
//==============================================================================
ProjectModel::~ProjectModel()
{
    // Close Project
    closeProject();

    qDebug() << "ProjectModel deleted.";
}
