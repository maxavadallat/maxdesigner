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
#include "createdatasourcedialog.h"
#include "livewindow.h"
#include "assetbrowserwindow.h"

#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "viewsmodel.h"
#include "datasourcesmodel.h"

#include "minimizedcomponents.h"

#include "projecttreemodel.h"
#include "openfilesmodel.h"
#include "recentprojectsmodel.h"

#include "componentcategorymodel.h"

#include "componentimportsmodel.h"
#include "componentanchorsmodel.h"
#include "componentownpropertiesmodel.h"
#include "componentownpropertiesfilter.h"
#include "componentpropertiesmodel.h"
#include "componentsignalsmodel.h"
#include "componentslotsmodel.h"
#include "componentstatesmodel.h"
#include "componenttransitionsmodel.h"
#include "componentfunctionsmodel.h"
#include "componentsfilter.h"

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
    , mOpenFiles(NULL)

    , mRecentProjects(NULL)

    , mAboutDialog(NULL)
    , mInfoDialog(NULL)
    , mConfirmDialog(NULL)

    , mPreferencesDialog(NULL)
    , mProjectPropertiesDiaog(NULL)
    , mCreateComponentDialog(NULL)
    , mCreateViewDialog(NULL)
    , mCreateDataSourceDialog(NULL)
    , mLiveWindow(NULL)
    , mAssetBrowser(NULL)

    , mPropertiesController(NULL)

    , mProjectModel(NULL)

    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mViews(NULL)
    , mCategories(NULL)
    , mAnimationComponents(NULL)

    , mCurrentComponent(NULL)
    , mScreenShotMode(false)
{
    qDebug() << "MainWindow created.";

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
    //qDebug() << "MainWindow::init";

//    // Check Event Filter
//    if (!mEventFilter) {
//        // Create Event Filter
//        mEventFilter = new DesignerEventFilter();
//    }

//    // Install Event Filter
//    installEventFilter(mEventFilter);

    // Check Project Tree Model
    if (!mProjectTreeModel) {
        // Create Project Tree Model
        mProjectTreeModel = new ProjectTreeModel();
    }

    // Check Open File Model
    if (!mOpenFiles) {
        // Create Open Files Model
        mOpenFiles = new OpenFilesModel();

        // Connect Signals
        connect(mOpenFiles, SIGNAL(fileOpened(QString)), this, SLOT(fileOpened(QString)));
        connect(mOpenFiles, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)));
        connect(mOpenFiles, SIGNAL(fileClosed(QString)), this, SLOT(fileClosed(QString)));
        connect(mOpenFiles, SIGNAL(componentOpened(ComponentInfo*)), this, SLOT(componentOpened(ComponentInfo*)));
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

    // Check Animation Components Model
    if (!mAnimationComponents) {
        // Create Animation Components Model
        mAnimationComponents = new AnimationComponentsModel(NULL);

        // Emit Animation Components Model Changed Signal
        emit animationsModelChanged(mAnimationComponents);
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
    ctx->setContextProperty(MODEL_NAME_OPEN_FILES, mOpenFiles);
    // Set Context Properties - Recent Projects List Model
    ctx->setContextProperty(MODEL_NAME_RECENT_PROJECTS, mRecentProjects);

    // Check Minimized Components Model

    // ...

    // Check Properties Controller
    if (!mPropertiesController) {
        // Create Properties Controller
        mPropertiesController = new PropertiesController();

        // Connect Signals
        connect(mPropertiesController, SIGNAL(focusedComponentChanged(ComponentInfo*)), this, SLOT(setCurrentComponent(ComponentInfo*)));

        // ...
    }

    // Set Context Properties - Properties Controller
    ctx->setContextProperty(DEFAULT_PROPERTIES_CONTROLLER, mPropertiesController);

    // ...

    // Register Component - Base Components Model
    qmlRegisterUncreatableType<BaseComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_BASECOMPONENTS_MODEL, "");
    // Register Component - Components Model
    qmlRegisterUncreatableType<ComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENTS_MODEL, "");
    // Register Component - Views Model
    qmlRegisterUncreatableType<ViewsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_VIEWS_MODEL, "");
    // Register Component - Data Sources Model
    qmlRegisterUncreatableType<DataSourcesModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_DATASOURCES_MODEL, "");

    // Register Component - Project Model
    qmlRegisterUncreatableType<ProjectModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_PROJECT_MODEL, "");
    // Register Component - Component Info
    qmlRegisterUncreatableType<ComponentInfo>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO, "");

    // Register Type - File Sort Filter Proxy
    qmlRegisterType<DesignerFileSortProxy>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_FILE_SORT_FILTER);

    // Register Type - Own Properties Filter
    qmlRegisterType<ComponentOwnPropertiesFilter>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_OWN_COMPONENTS_FILTER);

    // Register Components - Filter
    qmlRegisterType<ComponentsFilter>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_FILTER);

    // Register Component - Imports Model
    qmlRegisterUncreatableType<ComponentImportsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_IMPORTS_MODEL, "");

    // Register Component - Own Properties Model
    qmlRegisterUncreatableType<ComponentOwnPropertiesModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_OWN_PROPERTIES_MODEL, "");
    // Register Component - Properties Model
    qmlRegisterUncreatableType<ComponentPropertiesModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_PROPERTIES_MODEL, "");

    // Register Component - Anchors Model
    qmlRegisterUncreatableType<ComponentAnchorsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_ANCHORS_MODEL, "");

    // Register Component - Signals Model
    qmlRegisterUncreatableType<ComponentSignalsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_SIGNALS_MODEL, "");
    // Register Component - Signal
    qmlRegisterUncreatableType<ComponentSignal>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_SIGNAL, "");

    // Register Component - Slots Model
    qmlRegisterUncreatableType<ComponentSlotsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_SLOTS_MODEL, "");
    // Register Component - Slot
    qmlRegisterUncreatableType<ComponentSlot>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_SLOT, "");

    // Register Component - Functions Model
    qmlRegisterUncreatableType<ComponentFunctionsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_FUNCTIONS_MODEL, "");
    // Register Component - Function
    qmlRegisterUncreatableType<ComponentFunction>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_FUNCTION, "");

    // Register Component - States Model
    qmlRegisterUncreatableType<ComponentStatesModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_STATES_MODEL, "");
    // Register Component - State
    qmlRegisterUncreatableType<ComponentState>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_STATE, "");
    // Register Component - Property Change
    qmlRegisterUncreatableType<ComponentPropertyChange>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_PROPERTY_CHANGE, "");

    // Register Component - Transitions Model
    qmlRegisterUncreatableType<ComponentTransitionsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENTS_TRANSITIONS_MODEL, "");
    // Register Component - Transition
    qmlRegisterUncreatableType<ComponentTransition>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_COMPONENT_TRANSITION, "");

    // Register Component - Animation Components Model
    qmlRegisterUncreatableType<AnimationComponentsModel>(DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS, 0, 1, DEFAULT_MAIN_QML_ANIMATION_COMPONENTS_MODEL, "");


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
    qDebug() << "MainWindow::restoreUI";
    // Grab Keyboard Focus
    //grabKeyboard();

    //installEventFilter();

    // Check Settings
    if (mSettings) {
        // Restore Window State
        Qt::WindowState lastState = (Qt::WindowState)(mSettings->mainWindowState());
        // Check Last State
        if (lastState == Qt::WindowMaximized) {
            // Set Window State
            setWindowState(lastState);
        }
    }
}

//==============================================================================
// Take Screen Shot
//==============================================================================
void MainWindow::takeScreenShot()
{
//    // Check Current Project & Current Component
//    if (mProjectModel && mCurrentComponent && mCurrentComponent->componentType() == COMPONENT_TYPE_VIEW) {
//        qDebug() << "MainWindow::takeScreenShot";

//        // Set Screen Shot Mode
//        setScreenShotMode(true);

//        // Grab Fram Buffer
//        QImage ssImage = ui->mainQuickWidget->grabFramebuffer();

//        // Reset Screen Shot Mode
//        setScreenShotMode(false);

//        // ...

//    }
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

        // Check Current Component
        if (mCurrentComponent) {
            // Disconnect Signals

            // Disonnect Dirty Changed Signal
            disconnect(mCurrentComponent, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));

            // ...
        }

        // Set Current Component
        mCurrentComponent = aComponent;

        // Check Current Component
        if (mCurrentComponent) {

            //qDebug() << "MainWindow::setCurrentComponent - mName: " << mCurrentComponent->componentName();

            // Connect Signals
            // Connect Dirty Changed Signal
            connect(mCurrentComponent, SIGNAL(dirtyChanged(bool)), this, SLOT(componentDirtyChanged(bool)));

            // ...

            // Check If Is Root
            if (mCurrentComponent->isRoot()) {
                // Set Go Live Enabled State
                ui->actionGoLive->setEnabled(true);
            }

            // Check Current Component
            if (mCurrentComponent->getDirty()) {
                // Set Save Component Action Enabled
                ui->actionSaveComponent->setEnabled(true);
                // Set Save All Components Action Enabled
                ui->actionSaveAllComponents->setEnabled(true);
            }

            // ...

        } else {
            // Set Save Component Action Enabled
            ui->actionSaveComponent->setEnabled(false);
            // Set Go Live Enabled State
            ui->actionGoLive->setEnabled(false);
        }
    }
}

//==============================================================================
// Component Dirty State Changed Slot
//==============================================================================
void MainWindow::componentDirtyChanged(const bool& aDirty)
{
    Q_UNUSED(aDirty);

    // Get Sender Component
    ComponentInfo* senderComponent = static_cast<ComponentInfo*>(sender());
    // Check Sender Component
    if (senderComponent) {
        //qDebug() << "MainWindow::componentDirtyChanged - mName: " << senderComponent->mName << " - aDirty: " << aDirty;

        // Check Current Component
        if (senderComponent->getDirty()) {
            // Set Save Component Action Enabled
            ui->actionSaveComponent->setEnabled(true);
            // Set Save All Components Action Enabled
            ui->actionSaveAllComponents->setEnabled(true);
        } else {
            // Set Save Component Action Enabled
            ui->actionSaveComponent->setEnabled(false);
            // Set Save All Components Action Enabled
            //ui->actionSaveAllComponents->setEnabled(false);
        }
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
// Get Data Sources Model
//==============================================================================
DataSourcesModel* MainWindow::dataSourcesModel()
{
    return mProjectModel ? mProjectModel->dataSourcesModel() : NULL;
}

//==============================================================================
// Animation components Model
//==============================================================================
AnimationComponentsModel* MainWindow::animationsModel()
{
    return mAnimationComponents;
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
    //qDebug() << "MainWindow::openProject - aFilePath: " << aFilePath;

    // Check Open Fies Model
    if (mOpenFiles) {
        // Close Project
        mOpenFiles->closeProject();
    }

    // Check Project Model
    if (!mProjectModel) {
        // Create Project Model
        mProjectModel = new ProjectModel(mPropertiesController);

        // Connect Signal
        connect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
        connect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
        connect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));
        connect(mProjectModel, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)), this, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)));

    }

    // Load Project
    if (mProjectModel->loadProject(aFilePath)) {
        // Store recent Project
        mRecentProjects->storeRecentProject(aFilePath);

        // Set Window Title
        setWindowTitle(QString("Max Designer - %1").arg(mProjectModel->projectName()));

        // Add Live Temp To Import Paths
        addImportPath(mProjectModel->liveTempDir());

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
        // Set Enabled Create New Data Source Menu Item
        ui->actionCreateNewDataSource->setEnabled(true);
        // Set Component Names Visible Menu Item
        ui->actionShowComponentNames->setEnabled(true);
        // Set Show Borders Enabled
        ui->actionShowBorders->setEnabled(true);
        // Set Go Live Action Enabled
        ui->actionGoLive->setEnabled(true);
        // Set Show Asset Browser Action Enabled
        ui->actionShowAssetBrowser->setEnabled(true);
        // Set Toggle Project Pane Shown Enabled
        ui->actionToggleProjectPane->setEnabled(true);
        // Set Toggle Properties Pane Shown Enabled
        ui->actionTogglePropertiesPane->setEnabled(true);

        // Add Impor Path To Main Quick Widget
        ui->mainQuickWidget->engine()->addImportPath(mProjectModel->liveTempDir());

        // ...

        // Check Properties Controller
        if (mPropertiesController) {
            // Set Current Project
            mPropertiesController->setCurrentProject(mProjectModel);
        }

        // Check Project Tree Model
        if (mProjectTreeModel) {
            // Set Current Path
            mProjectTreeModel->setCurrentPath(mProjectModel->projectDir());
        }

        // Check Open Fies Model
        if (mOpenFiles) {
            // Set Project Model
            mOpenFiles->setProjectModel(mProjectModel);
        }

        // Check Animation Components Model
        if (mAnimationComponents) {
            // Set Current Project
            mAnimationComponents->setCurrentProject(mProjectModel);
        }

        // Set Properties Controller
        mProjectModel->setPropertiesController(mPropertiesController);

        // Emit Current Project Changed Signal
        emit currentProjectChanged(mProjectModel);

        // ...

    } else {
        qWarning() << "MainWindow::openProject - aFilePath: " << aFilePath << " - ERROR LOADING PROJECT";
    }
}

//==============================================================================
// Open Component
//==============================================================================
void MainWindow::openComponent(ComponentInfo* aComponent)
{
    // Check Open Files Model
    if (mOpenFiles) {
        // Open Component
        mOpenFiles->openComponent(aComponent);
    }
}

//==============================================================================
// Launch About
//==============================================================================
void MainWindow::launchAbout()
{
    // Check About Dialog
    if (!mAboutDialog) {
        // Create About Dialog
        mAboutDialog = new AboutDialog();
    }

    // Exec Dialog
    mAboutDialog->exec();
}

//==============================================================================
// Launch Info Dialog
//==============================================================================
void MainWindow::launchInfoDialog(const QString& aText)
{
    // Check Info Dialog
    if (!mInfoDialog) {
        // Create Info Dialog
        mInfoDialog = new InfoDialog();
    }

    // Set Info Text
    mInfoDialog->setInfoText(aText);
    // Exec
    mInfoDialog->exec();
}

//==============================================================================
// Launch Confirm Dialog
//==============================================================================
bool MainWindow::launchConfirmDialog(const QString& aText, const QString& aIcon)
{
    // Check Confirm Dialog
    if (!mConfirmDialog) {
        // Create Info Dialog
        mConfirmDialog = new ConfirmDialog();
    }

    // Set Confirm Text
    mConfirmDialog->setConfirmationText(aText);
    // Check Icon
    if (!aIcon.isEmpty()) {
        // Set Confirmation Icon
        mConfirmDialog->setConfirmationIcon(aIcon);
    }

    // Exec Confirm Dialog
    return mConfirmDialog->exec();
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

    // Exec Dialog
    if (mProjectPropertiesDiaog->exec()) {
        // Create New Project
        createNewProject();
    }

    // Check Open Files Model
    if (mOpenFiles && mProjectModel) {
        // Close File
        mOpenFiles->closeFile(mProjectModel->absoluteProjectFilePath());
    }
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

    // Set Screen Width
    mProjectPropertiesDiaog->setScreenWidth(mProjectModel->screenWidth());
    // Set Screen Height
    mProjectPropertiesDiaog->setScreenHeight(mProjectModel->screenHeight());

    // Set Dashboard Image
    mProjectPropertiesDiaog->setDashboardPath(mProjectModel->dashboard());

    // Set QML Directory
    mProjectPropertiesDiaog->setDataSourcesDir(mProjectModel->dataSourcesDir());
    // Set Main QML File
    mProjectPropertiesDiaog->setBaseComponentsDir(mProjectModel->baseComponentsDir());

    // Set Assets Directory
    mProjectPropertiesDiaog->setAssetsDir(mProjectModel->assetsDir());

    // Set Components Directory
    mProjectPropertiesDiaog->setComponentsDir(mProjectModel->componentsDir());
    // Set Views Directory
    mProjectPropertiesDiaog->setViewsDir(mProjectModel->viewsDir());

    // Set Import Paths
    mProjectPropertiesDiaog->setImportPaths(mProjectModel->importPaths());
    // Set Plugin Paths
    mProjectPropertiesDiaog->setPluginPaths(mProjectModel->pluginPaths());

    // Get Last Project Path
    QString lastProjectPath = mProjectModel->absoluteProjectFilePath();

    // Exec Dialog
    if (mProjectPropertiesDiaog->exec()) {
        // Set Project Properties
        updateProject();
    }

    // Check Open Files Model
    if (mOpenFiles) {
        // Close File
        mOpenFiles->closeFile(lastProjectPath);
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
    // Set Built In Visibility
    mCreateComponentDialog->setBuiltInVisibility(true);

    // Exec Dialog
    if (mCreateComponentDialog->exec()) {
        // Create Base Component
        createNewComponent(mCreateComponentDialog->componentName(),
                           COMPONENT_TYPE_BASECOMPONENT,
                           mCreateComponentDialog->componentBaseName(),
                           mCreateComponentDialog->componentCategory(),
                           mCreateComponentDialog->componentBuiltIn(),
                           DEFAULT_COMPONENT_WIDTH,
                           DEFAULT_COMPONENT_HEIGHT);
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
    // Set Built In Visibility
    mCreateComponentDialog->setBuiltInVisibility(false);

    // Exec Dialog
    if (mCreateComponentDialog->exec()) {
        // Create New Component
        createNewComponent(mCreateComponentDialog->componentName(),
                           COMPONENT_TYPE_COMPONENT,
                           mCreateComponentDialog->componentBaseName(),
                           mCreateComponentDialog->componentCategory(),
                           false,
                           DEFAULT_COMPONENT_WIDTH,
                           DEFAULT_COMPONENT_HEIGHT);
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
        // Create New View Component
        createNewComponent(mCreateViewDialog->viewName(),
                           COMPONENT_TYPE_VIEW,
                           mCreateViewDialog->viewBaseName(),
                           COMPONENT_CATEGORY_VISUAL,
                           false,
                           mCreateViewDialog->viewWidth(),
                           mCreateViewDialog->viewHeight());
    }

    // ...

    // Grab Keyboard Focus
    //grabKeyboard();
}

//==============================================================================
// Launch Create Data Source
//==============================================================================
void MainWindow::launchCreateDataSource()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    // Check Create Data Source Dialog
    if (!mCreateDataSourceDialog) {
        // Create Data Source Dialog
        mCreateDataSourceDialog = new CreateDataSourceDialog();
    }

    // Reset Dialog
    mCreateDataSourceDialog->reset();

    // Exec Dialog
    if (mCreateDataSourceDialog->exec()) {
        // Create New Data Source Component
        createNewComponent(mCreateDataSourceDialog->dataSourceName(), COMPONENT_TYPE_DATASOURCE, "QtObject", COMPONENT_CATEGORY_NONVISUAL, false);
    }
}

//==============================================================================
// Launch Generate Sources
//==============================================================================
void MainWindow::launchGenerateSources()
{
    qDebug() << "MainWindow::launchGenerateSources";

    // ...
}

//==============================================================================
// Launch Live Window
//==============================================================================
void MainWindow::launchLiveWindow()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    if (!mPropertiesController) {
        return;
    }

    // Check Live Window
    if (!mLiveWindow) {
        // Create Live Window
        mLiveWindow = new LiveWindow(mProjectModel, this);

        // Conenct Signal
        connect(mLiveWindow, SIGNAL(liveViewClosed()), this, SLOT(liveViewClosed()));

        // Check Properties Controller
        if (mPropertiesController) {
            // Set Component
            mLiveWindow->setComponent(mPropertiesController->focusedComponent());
            // Connect Signals
            connect(mPropertiesController, SIGNAL(focusedComponentChanged(ComponentInfo*)), mLiveWindow, SLOT(setComponent(ComponentInfo*)));
        }
    }

    // ...

    // Show Live Window
    mLiveWindow->show();
}

//==============================================================================
// Launch Asset Browser Window
//==============================================================================
void MainWindow::launchAssetBrowser()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    if (!mPropertiesController) {
        return;
    }

    // Check Asset Browser
    if (!mAssetBrowser) {
        // Create Asset Browser Window
        mAssetBrowser = new AssetBrowserWindow(this, mProjectModel);

        // Conenct Signal
        connect(mAssetBrowser, SIGNAL(assetBrowserClosed()), this, SLOT(assetBrowserClosed()));
        connect(mAssetBrowser, SIGNAL(assetSelected(QString)), this, SIGNAL(assetSelected(QString)));

        // ...
    }

    // Show Asset Browser Window
    mAssetBrowser->show();
}

//==============================================================================
// Clear Component Cache
//==============================================================================
void MainWindow::clearQMLComponentCache()
{
    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    qDebug() << "MainWindow::clearQMLComponentCache";

    // Get Root QML Context
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        // Clear Component Cache
        engine->clearComponentCache();
    }
}

//==============================================================================
// Toggle Show Tracers
//==============================================================================
void MainWindow::toggleShowTracers()
{
    // Check Settings
    if (mSettings) {
        // Set Show Tracers
        mSettings->setTracerVisible(!mSettings->tracerVisible());
    }
}

//==============================================================================
// Toggle Show Borders
//==============================================================================
void MainWindow::toggleShowBorders()
{
    // Check Settings
    if (mSettings) {
        // Set Show Borders
        mSettings->setBorderVisible(!mSettings->borderVisible());
    }
}

//==============================================================================
// Toggle Show Component Names
//==============================================================================
void MainWindow::toggleShowComponentNames()
{
    // Check Settings
    if (mSettings) {
        // Set Show Component Names Visible
        mSettings->setComponentNamesVisible(!mSettings->componentNamesVisible());
    }
}

//==============================================================================
// Toggle Slow Motion
//==============================================================================
void MainWindow::toggleSlowMotion()
{
    // Check Settings
    if (mSettings) {
        // Set Slow Motion
        mSettings->setSlowMotion(!mSettings->slowMotion());
    }
}

//==============================================================================
// Create New Project
//==============================================================================
void MainWindow::createNewProject()
{
    // Check Project Model
    if (!mProjectModel) {
        // Create Project Model
        mProjectModel = new ProjectModel(mPropertiesController);
        // Connect Signal
        connect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
        connect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
        connect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));
        connect(mProjectModel, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)), this, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)));
    }

    // Get Screen Width
    int sWidth = mProjectPropertiesDiaog->screenWidth();
    // Get Screen Height
    int sHeight = mProjectPropertiesDiaog->screenHeight();

    qDebug() << "MainWindow::createNewProject - sWidth: " << sWidth << " - sHeight: " << sHeight;

    // Set Project Name
    if (mProjectModel->initProject(mProjectPropertiesDiaog->projectName(), mProjectPropertiesDiaog->projectDir(), sWidth, sHeight)) {

        // Update Project
        updateProject();

        // Save Project
        saveProject();

        // ...

        // Set Window Title
        setWindowTitle(QString("Max Designer - %1").arg(mProjectModel->projectName()));

        // Add Import Path
        addImportPath(mProjectModel->liveTempDir());

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
        // Set Enabled Create New Data Source Menu Item
        ui->actionCreateNewDataSource->setEnabled(true);
        // Set Component Names Visible Menu Item
        ui->actionShowComponentNames->setEnabled(true);
        // Set Show Borders Enabled
        ui->actionShowBorders->setEnabled(true);
        // Set Go Live Action Enabled
        ui->actionGoLive->setEnabled(true);
        // Set Show Asset Browser Action Enabled
        ui->actionShowAssetBrowser->setEnabled(true);
        // Set Toggle Project Pane Shown Enabled
        ui->actionToggleProjectPane->setEnabled(true);
        // Set Toggle Properties Pane Shown Enabled
        ui->actionTogglePropertiesPane->setEnabled(true);

        // Check Project Tree Model
        if (mProjectTreeModel) {
            // Set Current Path
            mProjectTreeModel->setCurrentPath(mProjectModel->projectDir());
        }

        // Check Open Fies Model
        if (mOpenFiles) {
            // Set Current Project
            mOpenFiles->setProjectModel(mProjectModel);
        }

        // Check Animation Components Model
        if (mAnimationComponents) {
            // Set Current Project
            mAnimationComponents->setCurrentProject(mProjectModel);
        }

        // Emit Current Project chnged Signal
        emit currentProjectChanged(mProjectModel);
    }
}

//==============================================================================
// Create New Component
//==============================================================================
void MainWindow::createNewComponent(const QString& aName,
                                    const QString& aType,
                                    const QString& aBase,
                                    const QString& aCategory,
                                    const bool& aBuiltIn,
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

        // Init Component Width
        int cWidth = aCategory == "Animation" ? DEFAULT_ANIMATION_WIDTH : aWidth;
        int cHeight = aCategory == "Animation" ? DEFAULT_ANIMATION_HEIGHT : aHeight;

        // Check Type
        if (aType == COMPONENT_TYPE_BASECOMPONENT) {

            // Create New Base Component
            newComponent = mProjectModel->createBaseComponent(aName, aBase, aCategory, aBuiltIn, cWidth, cHeight);

        } else if (aType == COMPONENT_TYPE_COMPONENT) {

            // Create New Component
            newComponent = mProjectModel->createComponent(aName, aBase, aCategory, cWidth, cHeight);

        } else if (aType == COMPONENT_TYPE_VIEW) {

            // Create New View
            newComponent = mProjectModel->createView(aName, aBase, cWidth, cHeight);

        } else if (aType == COMPONENT_TYPE_DATASOURCE) {

            // Create New Data Source
            newComponent = mProjectModel->createDataSource(aName, "QtObject");

        } else {
            qWarning() << "MainWindow::createNewComponent - UNSUPPORTED COMPONENT TYPE!";
            return;
        }

        // Check New Component
        if (!newComponent) {
            qWarning() << "MainWindow::createNewComponent - NULL NEW COMPONENT!";
            return;
        }

        // Save New Component
        newComponent->save();

        // Open Component
        if (mOpenFiles) {
            // Open Component
            mOpenFiles->openComponent(newComponent);
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
        //qWarning() << "MainWindow::saveProject - NO PROJECT MODEL!";
        return;
    }

    //qDebug() << "MainWindow::saveProject - aFilePath: " << aFilePath;

    // Save Project
    if (mProjectModel->saveProject(aFilePath) && mRecentProjects) {
        // Store Recent
        mRecentProjects->storeRecentProject(mProjectModel->absoluteProjectFilePath());
    }

//    // Check Open Fies Model
//    if (mOpenFiles) {
//        // Close Current Project
//        mOpenFiles->closeProject();
//    }
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

    // Get Root Component
    ComponentInfo* rootComponent = mCurrentComponent->findRoot(mCurrentComponent);

    qDebug() << "MainWindow::saveComponent - rootComponent: " << rootComponent->componentName();

    // Save Current Component
    rootComponent->save(aFilePath);
}

//==============================================================================
// Save All Component
//==============================================================================
void MainWindow::saveAllComponents()
{
    // Check Project Model
    if (!mProjectModel) {
        qWarning() << "MainWindow::saveComponent - NO PROJECT MODEL!";
        return;
    }

    // Save All Components
    mProjectModel->saveAllComponents();

    // Set Action Save Component Enabled State
    ui->actionSaveComponent->setEnabled(false);
    // Set Action Save All Components Enabled State
    ui->actionSaveAllComponents->setEnabled(false);
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

    //qDebug() << "MainWindow::updateProject";

    // Set Properties Controller
    mProjectModel->setPropertiesController(mPropertiesController);

    // Set Screen Width
    mProjectModel->setScreenWidth(mProjectPropertiesDiaog->screenWidth());
    // Set Screen Height
    mProjectModel->setScreenHeight(mProjectPropertiesDiaog->screenHeight());

    // Set Dashboard Image
    mProjectModel->setDashboard(mProjectPropertiesDiaog->dashboardPath());

    // Set Base Components Dir
    mProjectModel->setBaseComponentsDir(mProjectPropertiesDiaog->baseComponentsDir());
    // Set Data Sources Dir
    mProjectModel->setDataSourcesDir(mProjectPropertiesDiaog->dataSourcesDir());
    // Set Components Dir
    mProjectModel->setComponentsDir(mProjectPropertiesDiaog->componentsDir());
    // Set Views Dir
    mProjectModel->setViewsDir(mProjectPropertiesDiaog->viewsDir());
    // Set Images Dir
    mProjectModel->setAssetsDir(mProjectPropertiesDiaog->assetsDir());

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

    // ...
}

//==============================================================================
// Close Project
//==============================================================================
void MainWindow::closeProject()
{
    // Save
    saveAllComponents();

    // Check Open Fies Model
    if (mOpenFiles) {
        // Close Current Project
        mOpenFiles->closeProject();
    }

    // Check Animation Components Model
    if (mAnimationComponents) {
        // Set Current Project
        mAnimationComponents->setCurrentProject(NULL);
    }

    // Check Live Window
    if (mLiveWindow) {
        // Connect Signals
        disconnect(mPropertiesController, SIGNAL(focusedComponentChanged(ComponentInfo*)), mLiveWindow, SLOT(setComponent(ComponentInfo*)));
    }

    // Check Properties Controller
    if (mPropertiesController) {
        // Reset Focused Component
        mPropertiesController->setFocusedComponent(NULL);
        // Set Current Project
        mPropertiesController->setCurrentProject(NULL);
    }

    // Check Project Model
    if (!mProjectModel) {
        return;
    }

    qDebug() << "MainWindow::closeProject";

    // Remove Import Path
    removeImportPath(mProjectModel->liveTempDir());

    // Save Project
    saveProject();

    // Save Project
    //mProjectModel->saveProject();

    disconnect(mProjectModel, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)), this, SIGNAL(baseComponentsModelChanged(BaseComponentsModel*)));
    disconnect(mProjectModel, SIGNAL(componentsModelChanged(ComponentsModel*)), this, SIGNAL(componentsModelChanged(ComponentsModel*)));
    disconnect(mProjectModel, SIGNAL(viewsModelChanged(ViewsModel*)), this, SIGNAL(viewsModelChanged(ViewsModel*)));
    disconnect(mProjectModel, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)), this, SIGNAL(dataSourcesModelChanged(DataSourcesModel*)));

    // Check Project Tree Model
    if (mProjectTreeModel) {
        // Set Current Path
        //mProjectTreeModel->setCurrentPath(QDir::homePath());
    }

    // Delete Project Model
    delete mProjectModel;
    mProjectModel = NULL;

    // Emit Current Project Changed Signal
    emit currentProjectChanged(mProjectModel);

    // ...

    // Set Window Title
    setWindowTitle(QString("Max Designer"));

    // Set Menu Items Enabled State
    ui->actionProjectProperties->setEnabled(false);
    ui->actionCloseProject->setEnabled(false);
    ui->actionDefineBaseComponent->setEnabled(false);
    ui->actionCreateComponent->setEnabled(false);
    ui->actionCreateView->setEnabled(false);
    ui->actionShowComponentNames->setEnabled(false);
    ui->actionShowBorders->setEnabled(false);
    ui->actionSaveComponent->setEnabled(false);
    ui->actionSaveAllComponents->setEnabled(false);
    ui->actionCloseComponent->setEnabled(false);
    ui->actionCloseAllComponents->setEnabled(false);
    ui->actionEditComponent->setEnabled(false);
    ui->actionEditView->setEnabled(false);
    ui->actionCreateNewDataSource->setEnabled(false);
    ui->actionRemoveComponent->setEnabled(false);
    ui->actionRemoveView->setEnabled(false);
    ui->actionRenameComponent->setEnabled(false);
    ui->actionRenameView->setEnabled(false);
    ui->actionGoLive->setEnabled(false);
    ui->actionShowAssetBrowser->setEnabled(false);
    ui->actionToggleProjectPane->setEnabled(false);
    ui->actionTogglePropertiesPane->setEnabled(false);

    // ...
}

//==============================================================================
// Close View
//==============================================================================
void MainWindow::closeComponent()
{
    qDebug() << "MainWindow::closeComponent";

    // Save Component
    saveComponent();

    // Check Current Component
    if (mCurrentComponent) {
        // Set Closing State
        mCurrentComponent->setClosing(true);
        // Clear Children
        mCurrentComponent->clearChildren();
    }

    // Check Properties Controller
    if (mPropertiesController) {
        // Check Focused Component
        if (mPropertiesController->focusedComponent()) {
            // Reset Focused Component
            mPropertiesController->setFocusedComponent(NULL);
        }
    }

    // Check Open Files Model
    if (mOpenFiles) {
        // Close Focused File
        mOpenFiles->closeFocusedFile();
    }
}

//==============================================================================
// Close All Component
//==============================================================================
void MainWindow::closeAllComponents()
{
    qDebug() << "MainWindow::closeAllComponents";

    // Save All Components
    saveAllComponents();

    // Check Properties Controller
    if (mPropertiesController) {
        // Check Focused Component
        if (mPropertiesController->focusedComponent()) {
            // Reset Focused Component
            mPropertiesController->setFocusedComponent(NULL);
        }
    }

    // Check Project Model
    if (mProjectModel) {
        // Clear All Children
        mProjectModel->clearAllChildren(true);
    }

    // Check Open Files Model
    if (mOpenFiles) {
        // Close All Files
        mOpenFiles->closeAllFiles();
    }
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
        //qDebug() << "MainWindow::removeComponent - aName: " << aName;

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
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        //qDebug() << "MainWindow::addImportPath - aDirPath: " << aDirPath;

        // Add Import Path
        engine->addImportPath(aDirPath);

        //qDebug() << "#### ipl: " << engine->importPathList();
    }
}

//==============================================================================
// Remove Import Path From Main QML Widget
//==============================================================================
void MainWindow::removeImportPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        // Get Import Path List
        QStringList ipList = engine->importPathList();
        // Get Index Of Import Path
        int ipIndex = ipList.indexOf(aDirPath);
        // Check Import Path Index
        if (ipIndex >= 0) {
            //qDebug() << "MainWindow::removeImportPath - aDirPath: " << aDirPath;

            // Remove Import Path
            ipList.removeAt(ipIndex);
            // Set Import Path List
            engine->setImportPathList(ipList);
        }
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
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        //qDebug() << "MainWindow::addPluginPath - aDirPath: " << aDirPath;

        // Add Plugin Path
        engine->addPluginPath(aDirPath);
    }
}

//==============================================================================
// Remove Plugin Path From Mqin QML Widget
//==============================================================================
void MainWindow::removePluginPath(const QString& aDirPath)
{
    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();
    // Get Engine
    QQmlEngine* engine = ctx ? ctx->engine() : NULL;

    // Check Engine
    if (engine) {
        // Get Plugin Path List
        QStringList ppList = engine->pluginPathList();
        // Get Index Of Plugin Path
        int ppIndex = ppList.indexOf(aDirPath);
        // Check Import Path Index
        if (ppIndex >= 0) {
            //qDebug() << "MainWindow::removePluginPath - aDirPath: " << aDirPath;

            // Remove Import Path
            ppList.removeAt(ppIndex);
            // Set Plugin Path List
            engine->setPluginPathList(ppList);
        }
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
        //qDebug() << "MainWindow::importPathAdded - aImportPath: " << aImportPath;
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
            //qDebug() << "MainWindow::importPathRemoved - aImportPath: " << aImportPath;
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
        //qDebug() << "MainWindow::importPathsChanged - aImportPaths: " << aImportPaths;
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
        //qDebug() << "MainWindow::pluginPathAdded - aPluginPath: " << aPluginPath;
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
            //qDebug() << "MainWindow::pluginPathRemoved - aPluginPath: " << aPluginPath;
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
        //qDebug() << "MainWindow::pluginPathsChanged - aPluginPaths: " << aPluginPaths;
        // Set Plugin Paths
        engine->setPluginPathList(aPluginPaths);
    }
}

//==============================================================================
// Base Component Created Slot
//==============================================================================
void MainWindow::baseComponentCreated(ComponentInfo* )
{
    //qDebug() << "MainWindow::baseComponentCreated - aComponent: " << aComponent;

    // ...
}

//==============================================================================
// Component Created Slot
//==============================================================================
void MainWindow::componentCreated(ComponentInfo* )
{
    //qDebug() << "MainWindow::componentCreated - aComponent: " << aComponent;

    // ...
}

//==============================================================================
// View Creaeted Slot
//==============================================================================
void MainWindow::viewCreated(ComponentInfo* )
{
    //qDebug() << "MainWindow::viewCreated - aComponent: " << aComponent;

    // ...
}

//==============================================================================
// Data Source Created Slot
//==============================================================================
void MainWindow::dataSourceCreated(ComponentInfo* )
{
    // ...
}

//==============================================================================
// File Opened Slot
//==============================================================================
void MainWindow::fileOpened(const QString& aFilePath)
{
    //qDebug() << "MainWindow::fileOpened - aFilePath: " << aFilePath;

    // Check Project Model
    if (mProjectModel) {
        // Check Project Model Path
        if (mProjectModel->absoluteProjectFilePath() == aFilePath) {
            // Launch Project Properties
            launchProjectProperties();
        }
    }

    // Check Open Files Model
    if (mOpenFiles && mOpenFiles->rowCount() > 0) {
        // Set Menu Items Enabled State
        ui->actionCloseAllComponents->setEnabled(true);
        ui->actionCloseComponent->setEnabled(true);
    }
}

//==============================================================================
// File Selected Slot
//==============================================================================
void MainWindow::fileSelected(const QString& aFilePath)
{
    //qDebug() << "MainWindow::fileSelected - aFilePath: " << aFilePath;

    // Check Project Model
    if (mProjectModel) {
        // Check Project Model Path
        if (mProjectModel->absoluteProjectFilePath() == aFilePath) {
            // Launch Project Properties
            launchProjectProperties();
        }
    }
}

//==============================================================================
// File Closed Slot
//==============================================================================
void MainWindow::fileClosed(const QString& )
{
    //qDebug() << "MainWindow::fileClosed - aFilePath: " << aFilePath;

    // Check Open Files Model
    if (!mOpenFiles || mOpenFiles->rowCount() == 0) {
        // Set Menu Items Enabled State
        ui->actionCloseAllComponents->setEnabled(false);
        ui->actionCloseComponent->setEnabled(false);
    }
}

//==============================================================================
// Component Opened Slot
//==============================================================================
void MainWindow::componentOpened(ComponentInfo* )
{
    //qDebug() << "MainWindow::componentOpened - aComponent: " << (aComponent ? aComponent->componentName() : "NULL!");

    // Check Open Files Model
    if (mOpenFiles && mOpenFiles->rowCount() > 0) {
        // Set Menu Items Enabled State
        ui->actionCloseAllComponents->setEnabled(true);
        ui->actionCloseComponent->setEnabled(true);
    }
}

//==============================================================================
// Live View Closed Slot
//==============================================================================
void MainWindow::liveViewClosed()
{
    qDebug() << "MainWindow::liveViewClosed";

    // Check Live Window
    if (mLiveWindow) {
        // Disconenct Signal
        disconnect(mLiveWindow, SIGNAL(liveViewClosed()), this, SLOT(liveViewClosed()));
        // Delete Live Window
        delete mLiveWindow;
        mLiveWindow = NULL;
    }
}

//==============================================================================
// Asset Browser Window Closed Slot
//==============================================================================
void MainWindow::assetBrowserClosed()
{
    qDebug() << "MainWindow::assetBrowserClosed";

    // Check Asset Browser
    if (mAssetBrowser) {

//        // Disconenct Signals
//        disconnect(mAssetBrowser, SIGNAL(assetBrowserClosed()), this, SLOT(assetBrowserClosed()));
//        disconnect(mAssetBrowser, SIGNAL(assetSelected(QString)), this, SIGNAL(assetSelected(QString)));

//        // ...

//        // Delete Asset Browser
//        delete mAssetBrowser;
//        mAssetBrowser = NULL;
    }
}

//==============================================================================
// Action About Triggered Slot
//==============================================================================
void MainWindow::on_actionAbout_triggered()
{
    // Launch About
    launchAbout();
}

//==============================================================================
// Action Preferences Triggered Slot
//==============================================================================
void MainWindow::on_actionPreferences_triggered()
{
    // Launch Preferences
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
// Action Save Component Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveComponent_triggered()
{
    // Save Component
    saveComponent();
}

//==============================================================================
// Action Save All Components Triggered Slot
//==============================================================================
void MainWindow::on_actionSaveAllComponents_triggered()
{
    // Save All Components
    saveAllComponents();
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
// Action Edit Component Triggered Slot
//==============================================================================
void MainWindow::on_actionEditComponent_triggered()
{
    // ...
}

//==============================================================================
// Action Edit View Triggered Slot
//==============================================================================
void MainWindow::on_actionEditView_triggered()
{
    // ...
}

//==============================================================================
// Action Create New Data Source Triggered Slot
//==============================================================================
void MainWindow::on_actionCreateNewDataSource_triggered()
{
    // Launch Create Data Source
    launchCreateDataSource();
}

//==============================================================================
// Action Close Component Triggered Slot
//==============================================================================
void MainWindow::on_actionCloseComponent_triggered()
{
    // Close And Save Component
    closeComponent();
}

//==============================================================================
// Action Close All Components Triggered Slot
//==============================================================================
void MainWindow::on_actionCloseAllComponents_triggered()
{
    // Close All Components
    closeAllComponents();
}

//==============================================================================
// Action Go Live Triggered Slot
//==============================================================================
void MainWindow::on_actionGoLive_triggered()
{
    // Launch Live Window
    launchLiveWindow();
}

//==============================================================================
// Action Show Tracers Triggered Slot
//==============================================================================
void MainWindow::on_actionShowTracers_triggered()
{
    // Toggle Show Tracers
    toggleShowTracers();
}

//==============================================================================
// Action Show Borders Triggere Slot
//==============================================================================
void MainWindow::on_actionShowBorders_triggered()
{
    // Toggle Show Borders
    toggleShowBorders();
}

//==============================================================================
// Action Show Component Names Triggered Slot
//==============================================================================
void MainWindow::on_actionShowComponentNames_triggered()
{
    // Toggle Show Component Names
    toggleShowComponentNames();
}

//==============================================================================
// Action Slow Motion Triggered Slot
//==============================================================================
void MainWindow::on_actionSlowMotion_triggered()
{
    // Toggle Slow Motion
    toggleSlowMotion();
}

//==============================================================================
// On Show Asset Browser Action Triggered Slot
//==============================================================================
void MainWindow::on_actionShowAssetBrowser_triggered()
{
    // Launch Asset Browswr
    launchAssetBrowser();
}

//==============================================================================
// On Generate Sources Action triggered Slot
//==============================================================================
void MainWindow::on_actionGenerateSources_triggered()
{
    // Launch Generate Sources
    launchGenerateSources();
}

//==============================================================================
// On Toggle Project Pane Action Triggered SLot
//==============================================================================
void MainWindow::on_actionToggleProjectPane_triggered()
{
    // Emit Toggle Project Pane Shown Signal
    emit toggleProjectPaneShown();
}

//==============================================================================
// On Toggle Properties Pane Action Triggered SLot
//==============================================================================
void MainWindow::on_actionTogglePropertiesPane_triggered()
{
    // Emit Toggle Properties Pane Shown Signal
    emit togglePropertiesPaneShown();
}

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
// Event
//==============================================================================
bool MainWindow::event(QEvent* aEvent)
{
    // Check Event
    if (aEvent) {
        // Switch Event Type
        switch (aEvent->type()) {
            case QEvent::WindowStateChange: {
                // Get Window State Change Event
                //QWindowStateChangeEvent* wsChangeEvent = static_cast<QWindowStateChangeEvent*>(aEvent);
                //qDebug() << "MainWindow::event - oldState: " << wsChangeEvent->oldState() << " - windowState: " << windowState();
                // Check Settings
                if (mSettings) {
                    // Store Main Window State
                    mSettings->setMainWindowState((int)windowState());
                }
            } break;

            default:
            break;
        }
    }

    // Parent's Event
    return QMainWindow::event(aEvent);
}

//==============================================================================
// Destructor
//==============================================================================
MainWindow::~MainWindow()
{
    // Close Project
    closeProject();

    // Clear QML Component Cache
    clearQMLComponentCache();

    // Release Settings
    mSettings->release();

    if (mEventFilter) {
        delete mEventFilter;
        mEventFilter = NULL;
    }

    // Check Properties Controller
    if (mPropertiesController) {
        // Disconnect Signals
        disconnect(mPropertiesController, SIGNAL(focusedComponentChanged(ComponentInfo*)), this, SLOT(setCurrentComponent(ComponentInfo*)));

        delete mPropertiesController;
        mPropertiesController = NULL;
    }


    if (mProjectTreeModel) {
        delete mProjectTreeModel;
        mProjectTreeModel = NULL;
    }

    if (mOpenFiles) {
        delete mOpenFiles;
        mOpenFiles = NULL;
    }

    if (mRecentProjects) {
        delete mRecentProjects;
        mRecentProjects = NULL;
    }

    if (mCategories) {
        delete mCategories;
        mCategories = NULL;
    }

    if (mAnimationComponents) {
        delete mAnimationComponents;
        mAnimationComponents = NULL;
    }

    // ...

    if (mAboutDialog) {
        delete mAboutDialog;
        mAboutDialog = NULL;
    }

    if (mInfoDialog) {
        delete mInfoDialog;
        mInfoDialog = NULL;
    }

    if (mConfirmDialog) {
        delete mConfirmDialog;
        mConfirmDialog = NULL;
    }

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

    if (mCreateComponentDialog) {
        delete mCreateComponentDialog;
        mCreateComponentDialog = NULL;
    }

    if (mCreateViewDialog) {
        delete mCreateViewDialog;
        mCreateViewDialog = NULL;
    }

    if (mCreateDataSourceDialog) {
        delete mCreateDataSourceDialog;
        mCreateDataSourceDialog = NULL;
    }

    if (mLiveWindow) {
        delete mLiveWindow;
        mLiveWindow = NULL;
    }

    if (mAssetBrowser) {
        delete mAssetBrowser;
        mAssetBrowser = NULL;
    }

    // Delete Main Quick Widget
    delete ui->mainQuickWidget;
    // Delete UI
    delete ui;

    // ...

    qDebug() << "MainWindow deleted.";
}


