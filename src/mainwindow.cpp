#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    // Check Base Components Model
    if (!mBaseComponents) {
        // Create Base Components Model
        mBaseComponents = new BaseComponentsModel();
    }

    // Check Components Model
    if (!mComponents) {
        // Create Components Model
        mComponents = new ComponentsListModel();
    }

    // Check Views Model
    if (!mViews) {
        // Create Views Model
        mViews = new ViewsListModel();
    }

    // Check Open File Model
    if (!mOpenfiles) {
        // Create Open Files Model
        mOpenfiles = new OpenFilesModel();
    }


    // Set Context Properties
    QQmlContext* ctx = ui->mainQuickWidget->rootContext();

    // Set Context Properties - Main Controller
    ctx->setContextProperty(DEFAULT_MAIN_CONTROLLER_NAME, this);

    // Set Context Properties - Settings
    ctx->setContextProperty(DEFAULT_GLOBAL_SETTINGS_CONTROLLER, mSettings);

    // Set Context Properties - Base Components List Model
    ctx->setContextProperty(DEFAULT_BASE_COMPONENTS_MODEL_NAME, mBaseComponents);
    // Set Context Properties - Components List Model
    ctx->setContextProperty(DEFAULT_COMPONENTS_MODEL_NAME, mComponents);
    // Set Context Properties - Views List Model
    ctx->setContextProperty(DEFAULT_VIEWS_MODEL_NAME, mViews);
    // Set Context Properties - Open Files List Model
    ctx->setContextProperty(DEFAULT_OPEN_FILE_MODEL_NAME, mOpenfiles);

    // Set Global Settings Controller
    //ctx->setContextProperty(DEFAULT_GLOBAL_SETTINGS_CONTROLLER, settings);

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
// Destructor
//==============================================================================
MainWindow::~MainWindow()
{
    // Delete UI
    delete ui->mainQuickWidget;
    delete ui;

    // Release Settings
    mSettings->release();

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

    if (mOpenfiles) {
        delete mOpenfiles;
        mOpenfiles = NULL;
    }

    // ...
}



