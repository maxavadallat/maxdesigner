#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>

#include "livewindow.h"
#include "ui_livewindow.h"
#include "mainwindow.h"
#include "settingscontroller.h"
#include "settingskeys.h"
#include "constants.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "propertiescontroller.h"

//==============================================================================
// Constructor
//==============================================================================
LiveWindow::LiveWindow(ProjectModel* aProject, MainWindow* aMainWindow, QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::LiveWindow)
    , mSettings(SettingsController::getInstance())
    , mMainWindow(aMainWindow)
    , mProjectModel(aProject)
    , mPropertiesController(aProject ? aProject->propertiesController() : NULL)
    , mComponent(NULL)
    , mLiveFileName("")
    , mBusy(false)
{
    qDebug() << "LiveWindow created.";

    // Setup UI
    ui->setupUi(this);

    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void LiveWindow::init()
{
    // Set Context Properties
    QQmlContext* ctx = ui->quickLiveWidget->rootContext();

    // Set Context Properties - Live Controller
    ctx->setContextProperty(DEFAULT_LIVE_CONTROLLER_NAME, this);

    // Set Context Properties - Settings
    ctx->setContextProperty(DEFAULT_GLOBAL_SETTINGS_CONTROLLER, mSettings);

    // Set Context Properties - Properties Controller
    ctx->setContextProperty(DEFAULT_PROPERTIES_CONTROLLER, mPropertiesController);

    // Set QML Source
    ui->quickLiveWidget->setSource(QUrl(DEFAULT_LIVE_QMLFILE_URL));

    // Set Resize Mode
    ui->quickLiveWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Check Project Model
    if (mProjectModel) {
        // Connect Signals
        connect(mProjectModel, SIGNAL(screenWidthChanged(int)), this, SIGNAL(screenWidthChanged(int)));
        connect(mProjectModel, SIGNAL(screenHeightChanged(int)), this, SIGNAL(screenHeightChanged(int)));

        // Set Imports Path

        // Get Engine
        QQmlEngine* engine = ctx ? ctx->engine() : NULL;

        // Check Engine
        if (engine) {
            // Add Import Path
            engine->addImportPath(mProjectModel->liveTempDir());
        }

        // ...

        // Set Plugins Path

        // ...
    }

    // Check Properties Controller
    if (mPropertiesController) {
        // Connect Signals
        connect(mPropertiesController, SIGNAL(focusedComponentChanged(ComponentInfo*)), this, SLOT(setComponent(ComponentInfo*)));
    }

    // ...

    // Restore UI
    restoreUI();
}

//==============================================================================
// Restore UI
//==============================================================================
void LiveWindow::restoreUI()
{
    // Set Size

    // Set Focuse Policy
    ui->quickLiveWidget->setFocusPolicy(Qt::StrongFocus);

    // Resize To Project Screen Size
    //resize(screenWidth(), screenHeight() + 22);

    // Init Meu Bar Height
    int menuBarHeight = 22;

//    // Set Geometry
//    setGeometry((mMainWindow->width() - screenWidth()) / 2 + mMainWindow->x(),
//                (mMainWindow->height() - screenHeight() + menuBarHeight) / 2 + menuBarHeight / 2 + mMainWindow->y(),
//                screenWidth(),
//                screenHeight() + menuBarHeight);

    // Set Always On top
    setWindowFlags(Qt::WindowStaysOnTopHint);

    // ...
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* LiveWindow::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Get Live Main File Name
//==============================================================================
QString LiveWindow::liveMain()
{
    return mLiveFileName;
}

//==============================================================================
// Set Live Main File Name
//==============================================================================
void LiveWindow::setLiveMain(const QString& aLiveMain)
{
    // Check Live Main
    if (mLiveFileName != aLiveMain) {
        // Set Live Main
        mLiveFileName = aLiveMain;
        // Emit Live Main File Changed Signal
        emit liveMainChanged(mLiveFileName);
    }
}

//==============================================================================
// Get Screen Width
//==============================================================================
int LiveWindow::screenWidth()
{
    // Get Screen Width
    int sw = mProjectModel ? mProjectModel->screenWidth() : 640;

    return sw;
}

//==============================================================================
// Get Screen height
//==============================================================================
int LiveWindow::screenHeight()
{
    // Get Screen Height
    int sh = mProjectModel ? mProjectModel->screenHeight() : 480;

    return sh;
}

//==============================================================================
// Get Busy State
//==============================================================================
bool LiveWindow::busy()
{
    return mBusy;
}

//==============================================================================
// Setup Live
//==============================================================================
void LiveWindow::setupLive()
{
    // Check Current Component
    if (mProjectModel && mComponent) {

        qDebug() << "LiveWindow::setupLive";

        // Generate Live Code
        QString newMainLive = mProjectModel->generateLiveCode(mComponent, true);

        // Set Live Main
        setLiveMain(newMainLive);

        // ...
    }
}

//==============================================================================
// Shut Down Live
//==============================================================================
void LiveWindow::shutDown()
{
    qDebug() << "LiveWindow::shutDown";

    // Reset Live Main
    setLiveMain("");

    // Emit Clear Content Signal
    emit clearContent();

    // ...

}

//==============================================================================
// Toggle Show Dashboard
//==============================================================================
void LiveWindow::toggleDashBoard()
{
    // Toggle Show Dashboard
    mSettings->setShowDashboard(!mSettings->showDashboard());
}

//==============================================================================
// Set Busy State
//==============================================================================
void LiveWindow::setBusy(const bool& aBusy)
{
    // Check Busy State
    if (mBusy != aBusy) {
        // Set Busy State
        mBusy = aBusy;
        // Emit Busy State Changed Signal
        emit busyChanged(mBusy);
    }
}

//==============================================================================
// Set Component
//==============================================================================
void LiveWindow::setComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (mComponent != aComponent) {
        // Set Busy
        setBusy(true);
        // Shut Down
        shutDown();
        // Set Component
        mComponent = aComponent;

        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Check Component
        if (mComponent /*&& mComponent->isRoot()*/) {
            // Setup Live
            setupLive();
        } else {
            // Shut Down
            shutDown();
        }

        // Reset Busy State
        setBusy(false);
    }
}

//==============================================================================
// Show Event
//==============================================================================
void LiveWindow::showEvent(QShowEvent* aShowEvent)
{
    QMainWindow::showEvent(aShowEvent);

}

//==============================================================================
// Close Event
//==============================================================================
void LiveWindow::closeEvent(QCloseEvent* aCloseEvent)
{
    QMainWindow::closeEvent(aCloseEvent);

    // Shut Down
    shutDown();

    qDebug() << "LiveWindow::closeEvent - windowSize: " << size();

    // Save Size

    // ...

    // Emit Live View Closed Signal
    emit liveViewClosed();
}

//==============================================================================
// Component Updated Slot
//==============================================================================
void LiveWindow::componentUpdated()
{
    qDebug() << "LiveWindow::componentUpdated";

    // Shut Down
    shutDown();
    // Set up Live
    setupLive();
}

//==============================================================================
// On Action Show Dashboard Triggered Slot
//==============================================================================
void LiveWindow::on_actionShowDashboard_triggered()
{
    // Toggle Dashboard
    toggleDashBoard();
}

//==============================================================================
// Action Close Triggered Slot
//==============================================================================
void LiveWindow::on_actionClose_triggered()
{

    // ...

    // Normalize Window
    showNormal();
    // Close
    close();
}

//==============================================================================
// Destructor
//==============================================================================
LiveWindow::~LiveWindow()
{
    // Shut Down
    shutDown();

    // Delete Live Widget
    delete ui->quickLiveWidget;
    // Delete UI
    delete ui;

    // Release Settings
    mSettings->release();

    // ...

    qDebug() << "LiveWindow deleted.";
}

