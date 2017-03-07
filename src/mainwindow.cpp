#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "designereventfilter.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "propertiescontroller.h"
#include "designerimageprovider.h"
#include "designerfilesortproxy.h"
#include "settingscontroller.h"
#include "preferencesdialog.h"
#include "confirmdialog.h"
#include "infodialog.h"
#include "aboutdialog.h"

#include "projectpropertiesdialog.h"
#include "createcomponentdialog.h"
#include "createviewdialog.h"

#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "viewsmodel.h"

#include "projectitemmodel.h"
#include "openfilesmodel.h"
#include "recentprojectsmodel.h"

#include "componentcategorymodel.h"

#include "settingskeys.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
MainWindow::MainWindow(QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::MainWindow)
    , mSettings(SettingsController::getInstance())
    , mEventFilter(NULL)

    , mProjectTreeModel(NULL)
    , mOpenfiles(NULL)

    , mRecentProjects(NULL)

    , mPreferencesDialog(NULL)
    , mProjectPropertiesDiaog(NULL)
    , mCreateComponentDialog(NULL)
    , mCreateViewDialog(NULL)

    , mPropertiesController(NULL)

    , mProjectModel(NULL)

    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mViews(NULL)
    , mCategories(NULL)

    , mCurrentComponent(NULL)
    , mScreenShotMode(false)
{
    // Setup UI
    ui->setupUi(this);

    qDebug() << "MainWindow created.";

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
    // Check Event Filter
    if (!mEventFilter) {
        // Create Event Filter
        mEventFilter = new DesignerEventFilter();
    }

    // Install Event Filter
    //installEventFilter(mEventFilter);

    // Check Project Tree Model
    if (!mProjectTreeModel) {
        // Create Project Tree Model
        mProjectTreeModel = new ProjectTreeModel();
    }

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

    // Check Component Categories Model
    if (!mCategories) {
        // Create Component Categories Model
        mCategories = new ComponentCategoryModel();
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

    // Set Context Properties - Project Tree Model
    ctx->setContextProperty(MODEL_NAME_PROJECT_TREE, mProjectTreeModel);
    // Set Context Properties - Open Files List Model
    ctx->setContextProperty(MODEL_NAME_OPEN_FILES, mOpenfiles);
    // Set Context Properties - Recent Projects List Model
    ctx->setContextProperty(MODEL_NAME_RECENT_PROJECTS, mRecentProjects);

    // Check Properties Controller
    if (!mPropertiesController) {
        // Create Properties Controller
        mPropertiesController = new PropertiesController();
    }

    // Set Context Properties - Properties Controller
    ctx->setContextProperty(DEFAULT_PROPERTIES_CONTROLLER, mPropertiesController);

    // ...

    // Register Base Components Model
    qmlRegisterUncreatableType<BaseComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_BASECOMPONENTS_MODEL, "");
    // Register Components Model
    qmlRegisterUncreatableType<ComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENTS_MODEL, "");
    // Register Views Model
    qmlRegisterUncreatableType<ViewsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_VIEWS_MODEL, "");

    // Register Project Model
    qmlRegisterUncreatableType<ProjectModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_PROJECT_MODEL, "");
    // Register Component Info
    qmlRegisterUncreatableType<ComponentInfo>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO, "");

    // Register File Sort Filter Proxy
    qmlRegisterType<DesignerFileSortProxy>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_FILE_SORT_FILTER);

    // Get Engine
    QQmlEngine* engine = ui->mainQuickWidget->engine();

//    // Create New Image Provider
//    DesignerImageProvider* newImageProvider = new DesignerImageProvider();

    // Add Image Provider
    engine->addImageProvider(QLatin1String(DEFAULT_IMAGE_PROVIDER_ID), new DesignerImageProvider());

    // Set Resize Mode
    ui->mainQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

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
    //grabKeyboard();

    //installEventFilter();
}

//==============================================================================
// Take Screen Shot
//==============================================================================
void MainWindow::takeScreenShot()
{
    // Check Current Project & Current Component
    if (mProjectModel && mCurrentComponent && mCurrentComponent->componentType() == COMPONENT_TYPE_VIEW) {
        qDebug() << "MainWindow::takeScreenShot";

        // Set Screen Shot Mode
        setScreenShotMode(true);

        // Grab Fram Buffer
        QImage ssImage = ui->mainQuickWidget->grabFramebuffer();

        // Reset Screen Shot Mode
        setScreenShotMode(false);



        // ...


    }
}

//==============================================================================
// Toggle Designer Mode
//==============================================================================
void MainWindow::toggleDesignerMode()
{
    // Check Designer Mode
    if (mSettings->designerMode() == SETTINGS_VALUE_DESIGNER_MODE_DESIGNER) {
        // Set Designer Mode
        mSettings->setDesignerMode(SETTINGS_VALUE_DESIGNER_MODE_DEVELOPER);
    } else {
        // Set Designer Mode
        mSettings->setDesignerMode(SETTINGS_VALUE_DESIGNER_MODE_DESIGNER);
    }
}

//==============================================================================
// Set Screen Shot Mode
//==============================================================================
void MainWindow::setScreenShotMode(const bool& aScreenShotMode)
{
    // Check Screen Shot Mode
    if (mScreenShotMode != aScreenShotMode) {
        // Set Screen Shot Mode
        mScreenShotMode = aScreenShotMode;
        // Emit Screen Shot Mode Changed Signal
        emit screenshotModeChanged(mScreenShotMode);
    }
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
// Get Base Components Model
//==============================================================================
BaseComponentsModel* MainWindow::baseComponentsModel()
{
    return mProjectModel ? mProjectModel->baseComponentsModel() : NULL;
}

//==============================================================================
// Get Components Model
//==============================================================================
ComponentsModel* MainWindow::componentsModel()
{
    return mProjectModel ? mProjectModel->componentsModel() : NULL;
}

//==============================================================================
// Get Views Model
//==============================================================================
ViewsModel* MainWindow::viewsModel()
{
    return mProjectModel ? mProjectModel->viewsModel() : NULL;
}

//==============================================================================
// Get Screen Shot Mode
//==============================================================================
bool MainWindow::screenshotMode()
{
    return mScreenShotMode;
}

//==============================================================================
// Open Project
//==============================================================================
void MainWindow::openProject(const QString& aFilePath)
{
    qDebug() << "MainWindow::openProject - aFilePath: " << aFilePath;

    // Check Project Model
    if (!mProjectModel) {
        // Create Project Model
        mProjectModel = new ProjectModel();

        // Connect Signal
        connect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
        connect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
        connect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));

        connect(mProjectModel, SIGNAL(baseComponentCreated(ComponentInfo*)), this, SLOT(baseComponentCreated(ComponentInfo*)));
        connect(mProjectModel, SIGNAL(componentCreated(ComponentInfo*)), this, SLOT(componentCreated(ComponentInfo*)));
        connect(mProjectModel, SIGNAL(viewCreated(ComponentInfo*)), this, SLOT(viewCreated(ComponentInfo*)));
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
        // Set Enable Define Base Components Menu
        ui->actionDefineBaseComponent->setEnabled(true);
        // Set Enable Create Component Menu Item
        ui->actionCreateComponent->setEnabled(true);
        // Set Enable Create View Menu Item
        ui->actionCreateView->setEnabled(true);

        // ...

        // Emit Current Project Changed Signal
        emit currentProjectChanged(mProjectModel);

        // ...

    } else {
        qWarning() << "MainWindow::openProject - aFilePath: " << aFilePath << " - ERROR LOADING PROJECT";
    }
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
    //qDebug() << "MainWindow::launchCreateNewProject";

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
    //releaseKeyboard();

    // Exec Dialog
    if (mProjectPropertiesDiaog->exec()) {
        // Create New Project
        createNewProject();
    }

    // Grab Keyboard Focus
    //grabKeyboard();
}

//==============================================================================
// Launch Open Project
//==============================================================================
void MainWindow::launchOpenProject()
{
    // Release Keyboard Focus
    //releaseKeyboard();

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
    //grabKeyboard();
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
    //releaseKeyboard();

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
    //grabKeyboard();
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
    //releaseKeyboard();

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
    //mProjectPropertiesDiaog->setProjectDir(mProjectModel->projectDir());
    // Set QML Directory
    mProjectPropertiesDiaog->setQMLDir(mProjectModel->qmlDir());
    // Set Main QML File
    mProjectPropertiesDiaog->setMainQMLFile(mProjectModel->mainQMLFile());
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
        updateProject();
    }

    // Grab Keyboard Focus
    //grabKeyboard();
}

//==============================================================================
// Launch Define Base Component
//==============================================================================
void MainWindow::launchDefineBaseComponent()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Release Keyboard Focus
    //releaseKeyboard();

    // Check Define Base Component Dialog
    if (!mCreateComponentDialog) {
        // Create Create Component Dialog
        mCreateComponentDialog = new CreateComponentDialog();

        // Set Base Components Model
        mCreateComponentDialog->setBaseComponentsModel(mProjectModel->baseComponentsModel());
        // Set Components Model
        mCreateComponentDialog->setComponentsModel(mProjectModel->componentsModel());
        // Set Categories Model
        mCreateComponentDialog->setCategoriesModel(mCategories);
    }

    // Reset Dialog
    mCreateComponentDialog->reset();

    // Exec Dialog
    if (mCreateComponentDialog->exec()) {
        // Create Base Component
        createNewComponent(mCreateComponentDialog->componentName(),
                           COMPONENT_TYPE_BASECOMPONENT,
                           mCreateComponentDialog->componentBaseName(),
                           mCreateComponentDialog->componentCategory());
    }

    // Grab Keyboard Focus
    //grabKeyboard();
}

//==============================================================================
// Launch Create Component
//==============================================================================
void MainWindow::launchCreateComponent()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Release Keyboard Focus
    //releaseKeyboard();

    // Check Create Component Dialog
    if (!mCreateComponentDialog) {
        // Create Create Component Dialog
        mCreateComponentDialog = new CreateComponentDialog();

        // Set Base Components Model
        mCreateComponentDialog->setBaseComponentsModel(mProjectModel->baseComponentsModel());
        // Set Components Model
        mCreateComponentDialog->setComponentsModel(mProjectModel->componentsModel());
        // Set Categories Model
        mCreateComponentDialog->setCategoriesModel(mCategories);
    }

    // Reset Dialog
    mCreateComponentDialog->reset();

    // Exec Dialog
    if (mCreateComponentDialog->exec()) {
        // Create Base Component
        createNewComponent(mCreateComponentDialog->componentName(),
                           COMPONENT_TYPE_COMPONENT,
                           mCreateComponentDialog->componentBaseName(),
                           mCreateComponentDialog->componentCategory());
    }

    // ...

    // Grab Keyboard Focus
    //grabKeyboard();
}

//==============================================================================
// Launch Create View
//==============================================================================
void MainWindow::launchCreateView()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Check Create View Dialog
    if (!mCreateViewDialog) {
        // Create View Dialog
        mCreateViewDialog = new CreateViewDialog();
        // Set Base Components Model
        mCreateViewDialog->setBaseComponentsModel(mProjectModel->baseComponentsModel());
        // Set Components Model
        mCreateViewDialog->setComponentsModel(mProjectModel->componentsModel());
    }

    // Reset Dialog
    mCreateViewDialog->reset();

    // Release Keyboard Focus
    //releaseKeyboard();

    // Exec Create View Dialog
    if (mCreateViewDialog->exec()) {
        // Create Base Component
        createNewComponent(mCreateViewDialog->viewName(),
                           COMPONENT_TYPE_VIEW,
                           mCreateViewDialog->viewBaseName(),
                           COMPONENT_CATEGORY_VISUAL);
    }

    // ...

    // Grab Keyboard Focus
    //grabKeyboard();
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
        // Connect Signal
        connect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
        connect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
        connect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));

        connect(mProjectModel, SIGNAL(baseComponentCreated(ComponentInfo*)), this, SLOT(baseComponentCreated(ComponentInfo*)));
        connect(mProjectModel, SIGNAL(componentCreated(ComponentInfo*)), this, SLOT(componentCreated(ComponentInfo*)));
        connect(mProjectModel, SIGNAL(viewCreated(ComponentInfo*)), this, SLOT(viewCreated(ComponentInfo*)));
    }

    // Set Project Name
    mProjectModel->initProject(mProjectPropertiesDiaog->projectName(), mProjectPropertiesDiaog->projectDir());

    // Update Project
    updateProject();

    // ...

    // Enable Save Project Menu Item
    ui->actionSaveProject->setEnabled(true);
    // Enable Save As Project Menu Item
    ui->actionSaveProjectAs->setEnabled(true);
    // Enable Project Properties Menu Item
    ui->actionProjectProperties->setEnabled(true);
    // Enable Close Project Menu Item
    ui->actionCloseProject->setEnabled(true);
    // Set Enable Define Base Components Menu
    ui->actionDefineBaseComponent->setEnabled(true);
    // Set Enable Create Component Menu Item
    ui->actionCreateComponent->setEnabled(true);
    // Set Enable Create View Menu Item
    ui->actionCreateView->setEnabled(true);

    // Emit Current Project chnged Signal
    emit currentProjectChanged(mProjectModel);
}

//==============================================================================
// Create New Component
//==============================================================================
void MainWindow::createNewComponent(const QString& aName,
                                    const QString& aType,
                                    const QString& aBase,
                                    const QString& aCategory,
                                    const int& aWidth,
                                    const int& aHeight)
{
    // Check Project Model
    if (!mProjectModel) {
        qWarning() << "MainWindow::createNewComponent - NO PROJECT MODEL!";
        return;
    }

    // Check Name
    if (!aName.isEmpty()) {
        qDebug() << "MainWindow::createNewComponent - aName: " << aName << " - aType: " << aType << " - aBase: " << aBase << " - aCategory: " << aCategory;

        // Init New Component
        ComponentInfo* newComponent = NULL;

        // Check Type
        if (aType == COMPONENT_TYPE_BASECOMPONENT) {

            // Create New Base Component
            newComponent = mProjectModel->createBaseComponent(aName, aBase, aCategory);

        } else if (aType == COMPONENT_TYPE_COMPONENT) {

            // Create New Component
            newComponent = mProjectModel->createComponent(aName, aBase, aCategory);

        } else if (aType == COMPONENT_TYPE_VIEW) {

            // Create New View
            newComponent = mProjectModel->createView(aName, aBase, aWidth, aHeight);

        } else {
            qWarning() << "MainWindow::createNewComponent - UNSUPPORTED COMPONENT TYPE!";
        }
    } else {
        qWarning() << "MainWindow::createNewComponent - EMPTY COMPONENT NAME!";
    }
}

//==============================================================================
// Save Project
//==============================================================================
void MainWindow::saveProject(const QString& aFilePath)
{
    // Check Project Model
    if (!mProjectModel) {
        qWarning() << "MainWindow::saveProject - NO PROJECT MODEL!";
        return;
    }

    qDebug() << "MainWindow::saveProject - aFilePath: " << aFilePath;

    // Save Project
    if (mProjectModel->saveProject(aFilePath)) {
        // Store Recent
        mRecentProjects->storeRecentProject(mProjectModel->absoluteProjectFilePath());
    }
}

//==============================================================================
// Save Current Component
//==============================================================================
void MainWindow::saveComponent(const QString& aFilePath)
{
    // Check Project Model
    if (!mProjectModel) {
        qWarning() << "MainWindow::saveComponent - NO PROJECT MODEL!";
        return;
    }

    // Check Current Component
    if (!mCurrentComponent) {
        qWarning() << "MainWindow::saveComponent - NO CURRENT COMPONENT!";
        return;
    }

    // Save Current Component
    mCurrentComponent->save(aFilePath);
}

// ...

//==============================================================================
// Update Project
//==============================================================================
void MainWindow::updateProject()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Set Main QML File
    mProjectModel->setMainQMLFile(mProjectPropertiesDiaog->mainQMLFile());
    // Set QML Dir
    mProjectModel->setQmlDir(mProjectPropertiesDiaog->qmlDir());
    // Set JS Dir
    mProjectModel->setJsDir(mProjectPropertiesDiaog->jsDir());
    // Set Images Dir
    mProjectModel->setImagesDir(mProjectPropertiesDiaog->imagesDir());
    // Set Components Dir
    mProjectModel->setComponentsDir(mProjectPropertiesDiaog->componentsDir());
    // Set Views Dir
    mProjectModel->setViewsDir(mProjectPropertiesDiaog->viewsDir());

    // Set Import Paths
    mProjectModel->setImportPaths(mProjectPropertiesDiaog->importPaths());
    // Set Plugin Paths
    mProjectModel->setPluginPaths(mProjectPropertiesDiaog->pluginPaths());
}

//==============================================================================
// Update Component
//==============================================================================
void MainWindow::updateComponent()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

}

//==============================================================================
// Close Project
//==============================================================================
void MainWindow::closeProject()
{
    // Save Project
    saveProject();

    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    qDebug() << "MainWindow::closeProject";

    // Save Project
    //mProjectModel->saveProject();

    disconnect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
    disconnect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
    disconnect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));

    disconnect(mProjectModel, SIGNAL(baseComponentCreated(ComponentInfo*)), this, SLOT(baseComponentCreated(ComponentInfo*)));
    disconnect(mProjectModel, SIGNAL(componentCreated(ComponentInfo*)), this, SLOT(componentCreated(ComponentInfo*)));
    disconnect(mProjectModel, SIGNAL(viewCreated(ComponentInfo*)), this, SLOT(viewCreated(ComponentInfo*)));

    // Delete Project Model
    delete mProjectModel;
    mProjectModel = NULL;

    // Emit Current Project Changed Signal
    emit currentProjectChanged(mProjectModel);

    // ...

    // Set Enable Save Project Menu Item
    ui->actionSaveProject->setEnabled(false);
    // Set Enable Save As Project Menu Item
    ui->actionSaveProjectAs->setEnabled(false);
    // Set Enable Project Properties Menu Item
    ui->actionProjectProperties->setEnabled(false);
    // Set Enable Close Project Menu Item
    ui->actionCloseProject->setEnabled(false);

    // Set Enable Define Base Components Menu
    ui->actionDefineBaseComponent->setEnabled(false);
    // Set Enable Create Component Menu Item
    ui->actionCreateComponent->setEnabled(false);
    // Set Enable Create View Menu Item
    ui->actionCreateView->setEnabled(false);

    // ...
}

//==============================================================================
// Close View
//==============================================================================
void MainWindow::closeComponent()
{
    qDebug() << "MainWindow::closeComponent";

    // ...
}

//==============================================================================
// Remove Component By Name
//==============================================================================
void MainWindow::removeComponent(const QString& aName)
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Check Name
    if (!aName.isEmpty()) {
        qDebug() << "MainWindow::removeComponent - aName: " << aName;

        // ...
    }
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
// Import Path Added Slot
//==============================================================================
void MainWindow::importPathAdded(const QString& aImportPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        qDebug() << "MainWindow::importPathAdded - aImportPath: " << aImportPath;

        // Add Import Path
        engine->addImportPath(aImportPath);
    }
}

//==============================================================================
// Import Path Removed Slot
//==============================================================================
void MainWindow::importPathRemoved(const QString& aImportPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        // Get Import Path List
        QStringList ipList = engine->importPathList();
        // Get Import Path Index
        int ipIndex = ipList.indexOf(aImportPath);
        // Check Import Path Index
        if (ipIndex >= 0) {
            qDebug() << "MainWindow::importPathRemoved - aImportPath: " << aImportPath;
            // Remove Import Path
            ipList.removeAt(ipIndex);
            // Set Import Path List
            engine->setImportPathList(ipList);
        }
    }
}

//==============================================================================
// Import Paths Changed Slot
//==============================================================================
void MainWindow::importPathsChanged(const QStringList& aImportPaths)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        qDebug() << "MainWindow::importPathsChanged - aImportPaths: " << aImportPaths;
        // Set Import Paths
        engine->setImportPathList(aImportPaths);
    }
}

//==============================================================================
// Plugin Path Added Slot
//==============================================================================
void MainWindow::pluginPathAdded(const QString& aPluginPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        qDebug() << "MainWindow::pluginPathAdded - aPluginPath: " << aPluginPath;
        // Add Plugin Path
        engine->addPluginPath(aPluginPath);
    }
}

//==============================================================================
// Plugin Path Removed Slot
//==============================================================================
void MainWindow::pluginPathRemoved(const QString& aPluginPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        // Get Plugin Path List
        QStringList ppList = engine->importPathList();
        // Get Import Path Index
        int ppIndex = ppList.indexOf(aPluginPath);
        // Check Import Path Index
        if (ppIndex >= 0) {
            qDebug() << "MainWindow::pluginPathRemoved - aPluginPath: " << aPluginPath;
            // Remove Import Path
            ppList.removeAt(ppIndex);
            // Set Plugin Path List
            engine->setPluginPathList(ppList);
        }
    }
}

//==============================================================================
// Plugin Paths Changed Slot
//==============================================================================
void MainWindow::pluginPathsChanged(const QStringList& aPluginPaths)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        qDebug() << "MainWindow::pluginPathsChanged - aPluginPaths: " << aPluginPaths;
        // Set Plugin Paths
        engine->setPluginPathList(aPluginPaths);
    }
}

//==============================================================================
// Base Component Created Slot
//==============================================================================
void MainWindow::baseComponentCreated(ComponentInfo* aComponent)
{
    qDebug() << "MainWindow::baseComponentCreated - aComponent: " << aComponent;

    // ...
}

//==============================================================================
// Component Created Slot
//==============================================================================
void MainWindow::componentCreated(ComponentInfo* aComponent)
{
    qDebug() << "MainWindow::componentCreated - aComponent: " << aComponent;

    // ...
}

//==============================================================================
// View Creaeted Slot
//==============================================================================
void MainWindow::viewCreated(ComponentInfo* aComponent)
{
    qDebug() << "MainWindow::viewCreated - aComponent: " << aComponent;

    // ...
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

//==============================================================================
// Action Define Base Component Triggered Slot
//==============================================================================
void MainWindow::on_actionDefineBaseComponent_triggered()
{
    // Launch Create Base Component
    launchDefineBaseComponent();
}

//==============================================================================
// Action Create Component Triggered Slot
//==============================================================================
void MainWindow::on_actionCreateComponent_triggered()
{
    // Launch Create New Component
    launchCreateComponent();
}

//==============================================================================
// Action Create View Triggered Slot
//==============================================================================
void MainWindow::on_actionCreateView_triggered()
{
    // Launch Create New View
    launchCreateView();
}

//==============================================================================
// Action Remove Component Triggered Slot
//==============================================================================
void MainWindow::on_actionRemoveComponent_triggered()
{
    // Check Current Component
    if (mCurrentComponent) {
        // Remove Component
        removeComponent(mCurrentComponent->componentName());
    }
}

//==============================================================================
// Action Remove View Triggered Slot
//==============================================================================
void MainWindow::on_actionRemoveView_triggered()
{
    // Check Current Component
    if (mCurrentComponent) {
        // Remove Component
        removeComponent(mCurrentComponent->componentName());
    }
}

//==============================================================================
// Action View Screenshot Triggered Slot
//==============================================================================
void MainWindow::on_actionScreenshot_triggered()
{
    // Take Screen Shot
    takeScreenShot();
}

//==============================================================================
// Action Switch Mode Triggered Slot
//==============================================================================
void MainWindow::on_actionSwitchMode_triggered()
{
    // Toggle Designer Mode
    toggleDesignerMode();
}

//==============================================================================
// Action Save Compoennt Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveComponent_triggered()
{

}

//==============================================================================
// Action Save View Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveView_triggered()
{

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

    // Close Project
    closeProject();

//    if (mProjectModel) {
//        delete mProjectModel;
//        mProjectModel = NULL;
//    }

    if (mEventFilter) {
        delete mEventFilter;
        mEventFilter = NULL;
    }

    if (mProjectTreeModel) {
        delete mProjectTreeModel;
        mProjectTreeModel = NULL;
    }

    if (mOpenfiles) {
        delete mOpenfiles;
        mOpenfiles = NULL;
    }

    if (mRecentProjects) {
        delete mRecentProjects;
        mRecentProjects = NULL;
    }

    if (mCategories) {
        delete mCategories;
        mCategories = NULL;
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

    if (mCreateComponentDialog) {
        delete mCreateComponentDialog;
        mCreateComponentDialog = NULL;
    }

    if (mPropertiesController) {
        delete mPropertiesController;
        mPropertiesController = NULL;
    }

    if (mCreateComponentDialog) {
        delete mCreateComponentDialog;
        mCreateComponentDialog = NULL;
    }

    if (mCreateViewDialog) {
        delete mCreateViewDialog;
        mCreateViewDialog = NULL;
    }

    // ...

    qDebug() << "MainWindow deleted.";
}


