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

//==============================================================================
// Constructor
//==============================================================================
LiveWindow::LiveWindow(QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::LiveWindow)
    , mSettings(SettingsController::getInstance())
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
    // ...

    // Restore UI
    restoreUI();
}

//==============================================================================
// Restore UI
//==============================================================================
void LiveWindow::restoreUI()
{
    // ...
}

//==============================================================================
// Setup Live
//==============================================================================
void LiveWindow::setupLive()
{
    // Generate Live Code

    // Set Up QML Context

    // Set QML Source

}

//==============================================================================
// Shut Down Live
//==============================================================================
void LiveWindow::shutDown()
{
    // Clear QML Context
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
    }
}

//==============================================================================
// Action Close Triggered Slot
//==============================================================================
void LiveWindow::on_actionClose_triggered()
{
    // Shut Down
    shutDown();

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

