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

//==============================================================================
// Constructor
//==============================================================================
LiveWindow::LiveWindow(ProjectModel* aProject, QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::LiveWindow)
    , mSettings(SettingsController::getInstance())
    , mProjectModel(aProject)
    , mComponent(NULL)
    , mLiveFileName("")
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

    // Set QML Source
    ui->quickLiveWidget->setSource(QUrl(DEFAULT_LIVE_QMLFILE_URL));

    // Set Resize Mode
    ui->quickLiveWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Check Project Model
    if (mProjectModel) {
        // Set Imports Path

        // ...

        // Set Plugins Path

        // ...
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

    // ...
}

//==============================================================================
// Setup Live
//==============================================================================
void LiveWindow::setupLive()
{
    // Check Current Component
    if (mProjectModel && mComponent) {

        qDebug() << "LiveWindow::setupLive";

        // Generate Live Code For Base Components
        mLiveFileName = mProjectModel->generateLiveCode(mComponent->componentName(), mComponent->generateLiveCode());

        // Generate Live Code For Base Components
        generateLiveCodeForBaseComponents();

        // ...
    }
}

//==============================================================================
// Shut Down Live
//==============================================================================
void LiveWindow::shutDown()
{
    qDebug() << "LiveWindow::shutDown";

    // Emit Clear Content Signal
    emit clearContent();

    // ...

}

//==============================================================================
// Set Content
//==============================================================================
void LiveWindow::setLiveContent()
{
    // Check Live File Name
    if (!mLiveFileName.isEmpty()) {
        qDebug() << "LiveWindow::setLiveContent";

        // Emit Load Content Signal
        emit loadContent(QString("%1%2").arg(DEFAULT_FILE_URL_PREFIX).arg(mLiveFileName));

        // ...
    }
}

//==============================================================================
// Generate Live Code For Base Components
//==============================================================================
void LiveWindow::generateLiveCodeForBaseComponents()
{
    // Check Currnt Component
    if (mComponent) {
        qDebug() << "LiveWindow::generateLiveCodeForBaseComponents";

        // ...

    }
}

//==============================================================================
// Set Component
//==============================================================================
void LiveWindow::setComponent(ComponentInfo* aComponent)
{
    // Check Component
    if (mComponent != aComponent) {
        // Shut Down
        shutDown();
        // Set Component
        mComponent = aComponent;
        // Setup Live
        setupLive();

        // Check If Window Shown
        if (isVisible()) {
            // Set Live Content
            setLiveContent();
        }
    }
}

//==============================================================================
// Show Event
//==============================================================================
void LiveWindow::showEvent(QShowEvent* aShowEvent)
{
    QMainWindow::showEvent(aShowEvent);

    // Set Live Content
    setLiveContent();
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
    // Set Live Content
    setLiveContent();
}

//==============================================================================
// Action Close Triggered Slot
//==============================================================================
void LiveWindow::on_actionClose_triggered()
{

    // ...

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

