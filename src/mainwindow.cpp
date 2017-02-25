#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "projectmodel.h"
#include "componentinfo.h"

#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
MainWindow::MainWindow(QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::MainWindow)
    , mSettings(SettingsControler::getInstance())

    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mViews(NULL)

    , mOpenfiles(NULL)
    , mRecentProjects(NULL)

    , mPreferencesDialog(NULL)
    , mProjectPropertiesDiaog(NULL)

    , mProjectModel(NULL)
{
    // Setup UI
    ui->setupUi(this);

    // Init
    init();

    // Restore UI
    restoreUI();
}

//==============================================================================
// Init
//==============================================================================
void MainWindow::init()
{
    // Check Open File Model
    if (!mOpenfiles) {
        // Create Open Files Model
        mOpenfiles = new OpenFilesModel();
    }

    // Check Recent Projects Model
    if (!mRecentProjects) {
        // Create Recent Projects Model
        mRecentProjects = new RecentProjectsModel();
    }

    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();

    // Set Context Properties - Main Controller
    ctx->setContextProperty(DEFAULT_MAIN_CONTROLLER_NAME, this);

    // Set Context Properties - Settings
    ctx->setContextProperty(DEFAULT_GLOBAL_SETTINGS_CONTROLLER, mSettings);

//    // Set Context Properties - Base Components List Model
//    ctx->setContextProperty(DEFAULT_BASE_COMPONENTS_MODEL_NAME, mBaseComponents);
//    // Set Context Properties - Components List Model
//    ctx->setContextProperty(DEFAULT_COMPONENTS_MODEL_NAME, mComponents);
//    // Set Context Properties - Views List Model
//    ctx->setContextProperty(DEFAULT_VIEWS_MODEL_NAME, mViews);

    // Set Context Properties - Open Files List Model
    ctx->setContextProperty(DEFAULT_OPEN_FILES_MODEL_NAME, mOpenfiles);
    // Set Context Properties - Recent Projects List Model
    ctx->setContextProperty(DEFAULT_OPEN_RECENT_PROJECTS_MODEL_NAME, mRecentProjects);

    // ...

    // Register Project Model
    qmlRegisterUncreatableType<ProjectModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_PROJECT_MODEL, "");
    // Register Component Info
    qmlRegisterUncreatableType<ComponentInfo>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO, "");

    // Register Base Components Model
    qmlRegisterUncreatableType<BaseComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_BASECOMPONENTS_MODEL, "");
    // Register Components Model
    qmlRegisterUncreatableType<ComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENTS_MODEL, "");
    // Register Views Model
    qmlRegisterUncreatableType<ViewsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO, "");

    // Get Engine
    //QQmlEngine* engine = ui->mainQuickWidget->engine();

    // Set Resize Mode
    ui->mainQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

//    // Register Singleton Type
//    qmlRegisterSingletonType(QUrl("qrc:///qml/Style.qml"), "utils", 0, 1, "Style");

    // Set Source
    ui->mainQuickWidget->setSource(QUrl(DEFAULT_MAIN_QMLFILE_URL));

    // ...

    // Set Focuse Policy
    ui->mainQuickWidget->setFocusPolicy(Qt::StrongFocus);

    // ...
}

//==============================================================================
// restore UI
//==============================================================================
void MainWindow::restoreUI()
{
    // Grab Keyboard Focus
    grabKeyboard();
}

//==============================================================================
// Get Current Project
//==============================================================================
ProjectModel* MainWindow::currentProject()
{
    return mProjectModel;
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* MainWindow::currentComponent()
{
    return mCurrentComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void MainWindow::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mCurrentComponent != aComponent) {
        // Set Current Component
        mCurrentComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mCurrentComponent);
    }
}

//==============================================================================
// Open Project
//==============================================================================
void MainWindow::openProject(const QString& aFilePath)
{
    // Check Project Model
    if (!mProjectModel) {
        // Create Project Model
        mProjectModel = new ProjectModel();
    }

    // Load Project
    if (mProjectModel->loadProject(aFilePath)) {
        // Store recent Project
        mRecentProjects->storeRecentProject(aFilePath);

        // Enable Save Project Menu Item
        ui->actionSaveProject->setEnabled(true);
        // Enable Save As Project Menu Item
        ui->actionSaveProjectAs->setEnabled(true);
        // Enable Project Properties Menu Item
        ui->actionProjectProperties->setEnabled(true);
        // Enable Close Project Menu Item
        ui->actionCloseProject->setEnabled(true);

        // Emit Current Project Changed Signal
        emit currentProjectChanged(mProjectModel);
    }

    // ...
}

//==============================================================================
// Launch Preferences
//==============================================================================
void MainWindow::launchPreferences()
{
    // Check Preferences Dialog
    if (!mPreferencesDialog) {
        // Create Preferences Dialog
        mPreferencesDialog = new PreferencesDialog();
    }

    // Exec Preferences Dialog
    mPreferencesDialog->exec();
}

//==============================================================================
// Launch Create New Project
//==============================================================================
void MainWindow::launchCreateNewProject()
{
    qDebug() << "MainWindow::launchCreateNewProject";

    // Check Project Properties Dialog
    if (!mProjectPropertiesDiaog) {
        // Create Project Properties Dialog
        mProjectPropertiesDiaog = new ProjectPropertiesDialog();
    }

    // Set Defaults For Project Properties

    // reset
    mProjectPropertiesDiaog->reset();

    // Set Project Name
    mProjectPropertiesDiaog->setProjectName(DEFAULT_PROJECT_NAME);
    // Set Project dir
    mProjectPropertiesDiaog->setProjectDir(QDir::homePath());

    // Set Main QML File
    //mProjectPropertiesDiaog->setMainQMLFile(QDir::homePath() + "/" + newProjectName + "/qml/main.qml");
    // Set QML dir
    //mProjectPropertiesDiaog->setQMLDir(QDir::homePath() + "/" + newProjectName + "/qml");
    // Set JS Dir
    //mProjectPropertiesDiaog->setJSDir(QDir::homePath() + "/" + newProjectName + "/qml");
    // Set Images Dir
    //mProjectPropertiesDiaog->setImagesDir(QDir::homePath() + "/" + newProjectName + "/qml");
    // Set Components Dir
    //mProjectPropertiesDiaog->setComponentsDir(QDir::homePath() + "/" + newProjectName + "/components");
    // Set Views Dir
    //mProjectPropertiesDiaog->setViewsDir(QDir::homePath() + "/" + newProjectName + "/views");

    // Release Keyboard Focus
    releaseKeyboard();

    // Exec Dialog
    if (mProjectPropertiesDiaog->exec()) {
        // Create New Project
        createNewProject();
    }

    // Grab Keyboard Focus
    grabKeyboard();
}

//==============================================================================
// Launch Open Project
//==============================================================================
void MainWindow::launchOpenProject()
{
    // Release Keyboard Focus
    releaseKeyboard();

    // Init File Open Dialog
    QFileDialog fileOpenDialog;

    // Set Directory
    fileOpenDialog.setDirectory(QDir::homePath());

    // Exec File Open Dialog
    if (fileOpenDialog.exec()) {
        // Open Project
        openProject(fileOpenDialog.selectedFiles()[0]);
    }

    // Grab Keyboard Focus
    grabKeyboard();
}

//==============================================================================
// Launch Save Project As
//==============================================================================
void MainWindow::launchSaveProjectAs()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Release Keyboard Focus
    releaseKeyboard();

    // Init File Open Dialog
    QFileDialog fileOpenDialog;

    // Set Directory
    fileOpenDialog.setDirectory(mProjectModel->projectDir());

    // Exec File Open Dialog
    if (fileOpenDialog.exec()) {
        // Save Project
        saveProject(fileOpenDialog.selectedFiles()[0]);
    }

    // Grab Keyboard Focus
    grabKeyboard();

}

//==============================================================================
// Launch Project
//==============================================================================
void MainWindow::launchProjectProperties()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Release Keyboard Focus
    releaseKeyboard();

    // Check Project Properties Dialog
    if (!mProjectPropertiesDiaog) {
        // Create Project Properties Dialog
        mProjectPropertiesDiaog = new ProjectPropertiesDialog();
    }

    // reset Project Properties
    mProjectPropertiesDiaog->reset();

    // Set Up Project Properties Dialog
    mProjectPropertiesDiaog->setNewProject(false);

    // Set Project Name
    mProjectPropertiesDiaog->setProjectName(mProjectModel->projectName());
    // Set Project Dir
    mProjectPropertiesDiaog->setProjectDir(mProjectModel->projectDir());
    // Set Main QML File
    mProjectPropertiesDiaog->setMainQMLFile(mProjectModel->mainQMLFile());
    // Set QML Directory
    mProjectPropertiesDiaog->setQMLDir(mProjectModel->qmlDir());
    // Set JS Directory
    mProjectPropertiesDiaog->setJSDir(mProjectModel->jsDir());
    // Set Images Directory
    mProjectPropertiesDiaog->setImagesDir(mProjectModel->imagesDir());
    // Set Components Directory
    mProjectPropertiesDiaog->setComponentsDir(mProjectModel->componentsDir());
    // Set Views Directory
    mProjectPropertiesDiaog->setViewsDir(mProjectModel->viewsDir());

    // Set Import Paths
    mProjectPropertiesDiaog->setImportPaths(mProjectModel->importPaths());
    // Set Plugin Paths
    mProjectPropertiesDiaog->setPluginPaths(mProjectModel->pluginPaths());

    // Exec Dialog
    if (mProjectPropertiesDiaog->exec()) {
        // Set Project Properties

    }

    // Grab Keyboard Focus
    grabKeyboard();
}

//==============================================================================
// Create New Project
//==============================================================================
void MainWindow::createNewProject()
{
    qDebug() << "MainWindow::createNewProject";

    // Check Project Model
    if (!mProjectModel) {
        // Create Project Model
        mProjectModel = new ProjectModel();
    }

    // Set Project Name
    mProjectModel->initProject(mProjectPropertiesDiaog->projectName(), mProjectPropertiesDiaog->projectDir());
    // Set Base Components Dir
    mProjectModel->setBaseComponentsDir(mProjectPropertiesDiaog->projectDir() + "/" + DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME);

    // Enable Save Project Menu Item
    ui->actionSaveProject->setEnabled(true);
    // Enable Save As Project Menu Item
    ui->actionSaveProjectAs->setEnabled(true);
    // Enable Project Properties Menu Item
    ui->actionProjectProperties->setEnabled(true);
    // Enable Close Project Menu Item
    ui->actionCloseProject->setEnabled(true);

    // Emit Current Project chnged Signal
    emit currentProjectChanged(mProjectModel);
}

//==============================================================================
// Create New Component
//==============================================================================
void MainWindow::createNewComponent()
{

}

//==============================================================================
// Create New View
//==============================================================================
void MainWindow::createNewView()
{

}

//==============================================================================
// Save Project
//==============================================================================
void MainWindow::saveProject(const QString& aFilePath)
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Save Project
    if (mProjectModel->saveProject(aFilePath)) {
        // Store Recent
        //mRecentProjects->storeRecentProject();
    }
}

// ...

//==============================================================================
// Update Project
//==============================================================================
void MainWindow::updateProject()
{

}

//==============================================================================
// Update View
//==============================================================================
void MainWindow::updateView()
{

}

//==============================================================================
// Update Component
//==============================================================================
void MainWindow::updateComponent()
{

}

//==============================================================================
// Close Project
//==============================================================================
void MainWindow::closeProject()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Save Project
    mProjectModel->saveProject();

    // Emit Current Project Changed Signal
    emit currentProjectChanged(NULL);

    // Delete Project Model
    delete mProjectModel;
    mProjectModel = NULL;

    // ...

    // Enable Save Project Menu Item
    ui->actionSaveProject->setEnabled(true);
    // Enable Save As Project Menu Item
    ui->actionSaveProjectAs->setEnabled(true);
    // Enable Project Properties Menu Item
    ui->actionProjectProperties->setEnabled(true);
    // Enable Close Project Menu Item
    ui->actionCloseProject->setEnabled(true);
}

//==============================================================================
// Close View
//==============================================================================
void MainWindow::closeView()
{

}

//==============================================================================
// Add Import Path To Main QML Widget
//==============================================================================
void MainWindow::addImportPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx->engine();

    // Add Import Path
    engine->addImportPath(aDirPath);
}

//==============================================================================
// Remove Import Path From Main QML Widget
//==============================================================================
void MainWindow::removeImportPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx->engine();

    // Get Import Path List
    QStringList ipList = engine->importPathList();
    // Get Index Of Import Path
    int ipIndex = ipList.indexOf(aDirPath);
    // Check Import Path Index
    if (ipIndex >= 0) {
        // Remove Import Path
        ipList.removeAt(ipIndex);
        // Set Import Path List
        engine->setImportPathList(ipList);
    }
}

//==============================================================================
// Add Plugin Path to Main QML Widget
//==============================================================================
void MainWindow::addPluginPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx->engine();

    // Add Plugin Path
    engine->addPluginPath(aDirPath);
}

//==============================================================================
// Remove Plugin Path From Mqin QML Widget
//==============================================================================
void MainWindow::removePluginPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx->engine();

    // Get Plugin Path List
    QStringList ppList = engine->pluginPathList();
    // Get Index Of Plugin Path
    int ppIndex = ppList.indexOf(aDirPath);
    // Check Import Path Index
    if (ppIndex >= 0) {
        // Remove Import Path
        ppList.removeAt(ppIndex);
        // Set Plugin Path List
        engine->setPluginPathList(ppList);
    }
}

//==============================================================================
// Action About Triggered Slot
//==============================================================================
void MainWindow::on_actionAbout_triggered()
{
    // Show About
}

//==============================================================================
// Action Preferences Triggered Slot
//==============================================================================
void MainWindow::on_actionPreferences_triggered()
{
    // Show Preferences
    launchPreferences();
}

//==============================================================================
// Action Create New Project Triggered Slot
//==============================================================================
void MainWindow::on_actionCreateNewProject_triggered()
{
    // Launch Create New Project
    launchCreateNewProject();
}

//==============================================================================
// Action Open Project Triggered Slot
//==============================================================================
void MainWindow::on_actionOpenFileOrProject_triggered()
{
    // Launch Open Project
    launchOpenProject();
}

//==============================================================================
// Action Save Project Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveProject_triggered()
{
    // Save Project
    saveProject();
}

//==============================================================================
// Action Save Project As Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveProjectAs_triggered()
{
    // Launch Save Project As
    launchSaveProjectAs();
}

//==============================================================================
// Action Project Properties Triggered Slot
//==============================================================================
void MainWindow::on_actionProjectProperties_triggered()
{
    // Launch Project Properties
    launchProjectProperties();
}

//==============================================================================
// Action Close Project Triggered Slot
//==============================================================================
void MainWindow::on_actionCloseProject_triggered()
{
    // Close Project
    closeProject();
}

// ...

//==============================================================================
// Action Quit Triggered Slot
//==============================================================================
void MainWindow::on_actionQuit_triggered()
{
    // Quit Application
    qApp->quit();
}

//==============================================================================
// Key Release Event
//==============================================================================
void MainWindow::keyReleaseEvent(QKeyEvent* aEvent)
{
    QMainWindow::keyReleaseEvent(aEvent);

    // Check Event
    if (aEvent) {
        // Switch Key
        switch (aEvent->key()) {
            case Qt::Key_T:
                // Check Settings
                if (mSettings) {
                    // Toggle Tracer Visibility
                    mSettings->setTracerVisible(!mSettings->tracerVisible());
                }
            break;

            // ...

            default:
                //qDebug() << "MainWindow::keyReleaseEvent - key: " << aEvent->key();
            break;
        }
    }
}

//==============================================================================
// Destructor
//==============================================================================
MainWindow::~MainWindow()
{
    // Delete UI
    delete ui->mainQuickWidget;
    delete ui;

    // Release Settings
    mSettings->release();


    if (mOpenfiles) {
        delete mOpenfiles;
        mOpenfiles = NULL;
    }

    if (mRecentProjects) {
        delete mRecentProjects;
        mRecentProjects = NULL;
    }

    // ...

    if (mPreferencesDialog) {
        delete mPreferencesDialog;
        mPreferencesDialog = NULL;
    }

    if (mProjectPropertiesDiaog) {
        delete mProjectPropertiesDiaog;
        mProjectPropertiesDiaog = NULL;
    }

    // ...

    if (mProjectModel) {
        delete mProjectModel;
        mProjectModel = NULL;
    }

    // ...
}



