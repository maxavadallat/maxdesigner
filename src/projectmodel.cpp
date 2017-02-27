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
#include "viewsmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ProjectModel::ProjectModel(QObject* parent)
    : QObject(parent)
    , mName("")
    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mViews(NULL)
    , mCurrentComponent(NULL)
{
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
// Create QML Project
//==============================================================================
void ProjectModel::createQMLProject()
{
    // ...
}

//==============================================================================
// Load QML Project File
//==============================================================================
void ProjectModel::loadQMLProject(const QString& aFileName)
{
    Q_UNUSED(aFileName);

    // ...
}

//==============================================================================
// Save QML Project
//==============================================================================
void ProjectModel::saveQMLProject()
{
    // ...
}

//==============================================================================
// Create/Register Base Components
//==============================================================================
void ProjectModel::createBaseComponents()
{
    // Item

    // Rectangle

    // Image

    // BorderImage

}

//==============================================================================
// Init New Project
//==============================================================================
void ProjectModel::initProject(const QString& aName, const QString& aDir)
{
    // Check Name
    if (!aName.isEmpty() && !aDir.isEmpty()) {
        // Set Project Name
        setProjectName(aName);
        // Set Project Dir
        setProjectDir(aDir);

        // ...
    }
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
        emit mainQMLFileChanged(mainQMLFile());
        emit qmlDirChanged(qmlDir());
        emit jsDirChanged(jsDir());
        emit imagesDirChanged(imagesDir());
        emit baseComponentsDirChanged(baseComponentsDir());
        emit componentsDirChanged(componentsDir());
        emit viewsDirChanged(viewsDir());
        emit importPathsChanged(importPaths());
        emit pluginPathsChanged(pluginPaths());

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
    // Check Save
    if (aSave) {
        // Save Project
        saveProject();
    }
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
    apfPath += mProperties[JSON_KEY_PROJECT_NAME].toString() + "/";
    apfPath += (mProperties[JSON_KEY_PROJECT_NAME].toString() + "." + DEFAULT_JSON_SUFFIX);

    return apfPath;
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
        // Set Project Name
        mProperties[JSON_KEY_PROJECT_NAME] = aName;
        // Emit Project Name Changed
        emit projectNameChanged(mProperties[JSON_KEY_PROJECT_NAME].toString());
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
        // Set Project Dir
        mProperties[JSON_KEY_PROJECT_DIR] = aDir;
        // Emit Project Dir Changed
        emit projectDirChanged(mProperties[JSON_KEY_PROJECT_DIR].toString());
    }
}

//==============================================================================
// Get Main QML File
//==============================================================================
QString ProjectModel::mainQMLFile()
{
    return mProperties[JSON_KEY_PROJECT_MAIN_QML].toString();
}

//==============================================================================
// Set Main QML File
//==============================================================================
void ProjectModel::setMainQMLFile(const QString& aQMLFile)
{
    // Check QML File
    if (aQMLFile != mainQMLFile()) {
        // Set Main QML File
        mProperties[JSON_KEY_PROJECT_MAIN_QML] = aQMLFile;
        // Emit Main QML File Changed Signal
        emit mainQMLFileChanged(mProperties[JSON_KEY_PROJECT_MAIN_QML].toString());
    }
}

//==============================================================================
// Get QML Dir
//==============================================================================
QString ProjectModel::qmlDir()
{
    return mProperties[JSON_KEY_PROJECT_QML_DIR].toString();
}

//==============================================================================
// Set QML Dir
//==============================================================================
void ProjectModel::setQmlDir(const QString& aQMLDir)
{
    // Check QML Dir
    if (aQMLDir != qmlDir()) {
        // Set QML Dir
        mProperties[JSON_KEY_PROJECT_QML_DIR] = aQMLDir;
        // Emit QML Dir Changed Signal
        emit qmlDirChanged(mProperties[JSON_KEY_PROJECT_QML_DIR].toString());
    }
}

//==============================================================================
// Get JS Dir
//==============================================================================
QString ProjectModel::jsDir()
{
    return mProperties[JSON_KEY_PROJECT_JS_DIR].toString();
}

//==============================================================================
// Set JS Dir
//==============================================================================
void ProjectModel::setJsDir(const QString& aJSDir)
{
    // Check JS Dir
    if (aJSDir != jsDir()) {
        // Set JS Dir
        mProperties[JSON_KEY_PROJECT_JS_DIR] = aJSDir;
        // Emit JS Dir Changed Signal
        emit jsDirChanged(mProperties[JSON_KEY_PROJECT_JS_DIR].toString());
    }
}

//==============================================================================
// Get Images Dir
//==============================================================================
QString ProjectModel::imagesDir()
{
    return mProperties[JSON_KEY_PROJECT_IMAGES_DIR].toString();
}

//==============================================================================
// Set Images Dir
//==============================================================================
void ProjectModel::setImagesDir(const QString& aImagesDir)
{
    // Check Images Dir
    if (aImagesDir != imagesDir()) {
        // Set Images Dir
        mProperties[JSON_KEY_PROJECT_IMAGES_DIR] = aImagesDir;
        // Emit Images Dir Changed Signal
        emit imagesDirChanged(mProperties[JSON_KEY_PROJECT_IMAGES_DIR].toString());
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
        // Set Base Components Dir
        mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR] = aBaseComponentsDir;
        // Emit Base Components Dir Changed Signal
        emit baseComponentsDirChanged(mProperties[JSON_KEY_PROJECT_BASECOMPONENTS_DIR].toString());
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
        // Emit Components Dir Changed Signal
        emit componentsDirChanged(mProperties[JSON_KEY_PROJECT_COMPONENTS_DIR].toString());
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
        // Emit Views Dir Changed Signal
        emit viewsDirChanged(mProperties[JSON_KEY_PROJECT_VIEWS_DIR].toString());
    }
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

/*
//==============================================================================
// Set Import Paths
//==============================================================================
void ProjectModel::setImportPaths(const QStringList& aImportPaths)
{
    // Set Import Paths
    mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = aImportPaths;
    // Emit Import Paths Changed Signal


//    for (int i=0; i<aImportPaths.count(); i++) {
//        // Init JSON Array
//        QJsonArray jsonArray;
//        // Add Item
//        jsonArray << aImportPaths[i];
//        // Add Import Paath
//        mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = jsonArray;
//        // Emit Import Paths Changed Signal
//        emit importPathsChanged(aImportPaths);
//    }
}
*/

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
        // Emit Import Paths Changed Signal
        emit importPathsChanged(importPaths());
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
        // Remove Value At Index
        jsonArray.removeAt(aIndex);
        // Set Import Paths
        mProperties[JSON_KEY_PROJECT_IMPORT_PATHS] = jsonArray;
        // Emit Import Paths Changed Signal
        emit importPathsChanged(importPaths());
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
        // Emit Plugin Paths Changed Signal
        emit pluginPathsChanged(pluginPaths());
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
        // Remove Value At Index
        jsonArray.removeAt(aIndex);
        // Set Plugin Paths
        mProperties[JSON_KEY_PROJECT_PLUGIN_PATHS] = jsonArray;
        // Emit Import Paths Changed Signal
        emit pluginPathsChanged(importPaths());
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
// Get Current Component
//==============================================================================
ComponentInfo* ProjectModel::currentComponent()
{
    return mCurrentComponent;
}

//==============================================================================
// Get Component By Name
//==============================================================================
ComponentInfo* ProjectModel::getComponentByName(const QString& aName)
{
    Q_UNUSED(aName);

    return NULL;
}

//==============================================================================
// Destructor
//==============================================================================
ProjectModel::~ProjectModel()
{
    closeProject();

    if (mBaseComponents) {
        delete mBaseComponents;
        mBaseComponents = NULL;
    }

    if (mComponents) {
        delete mComponents;
        mComponents = NULL;
    }

    if (mViews) {
        delete mViews;
        mViews = NULL;
    }

    // ...
}
