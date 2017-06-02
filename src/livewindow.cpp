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
LiveWindow::LiveWindow(ProjectModel* aProject, QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::LiveWindow)
    , mSettings(SettingsController::getInstance())
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

    // resize To Project Screen Size
    resize(screenWidth(), screenHeight() + 30);

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
    return mProjectModel ? mProjectModel->screenWidth() : 640;
}

//==============================================================================
// Get Screen height
//==============================================================================
int LiveWindow::screenHeight()
{
    return mProjectModel ? mProjectModel->screenHeight() : 480;
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

        // Generate Live Code For Base Components
        generateLiveCodeForBaseComponents(mComponent);

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

    // Emit Clear Content Signal
    emit clearContent();

    // ...

}

//==============================================================================
// Set Content
//==============================================================================
void LiveWindow::setLiveContent()
{
//    // Check Live File Name
//    if (!mLiveFileName.isEmpty()) {
//        qDebug() << "LiveWindow::setLiveContent";

//        // Emit Load Content Signal
//        emit loadContent(QString("%1%2").arg(DEFAULT_FILE_URL_PREFIX).arg(mLiveFileName));

//        // ...
//    }
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
// Generate Live Code For Base Components
//==============================================================================
void LiveWindow::generateLiveCodeForBaseComponents(ComponentInfo* aComponent)
{
    // Check Component
    if (!aComponent) {
        return;
    }

    qDebug() << "LiveWindow::generateLiveCodeForBaseComponents - mName: " << aComponent->componentName();

    // Check Base
    if (aComponent->mBase && !aComponent->mBuiltIn) {
        // Generate Clean Live Code For Base
        generateLiveCodeForBaseComponents(aComponent->mBase);
    }

    // Check If Component Built in
    if (!aComponent->mBuiltIn) {
        // Generate Clean Live Code For Component

    }

    // Get Child Count
    int cCount = aComponent->childCount();

    // Iterate Through Childrent
    for (int i=0; i<cCount; i++) {
        // Generate Clean Live Code For Child
        generateLiveCodeForBaseComponents(aComponent->childInfo(i));
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
        if (mComponent && mComponent->isRoot()) {
            // Setup Live
            setupLive();

//            // Check If Window Shown
//            if (isVisible()) {
//                // Set Live Content
//                setLiveContent();
//            }
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

