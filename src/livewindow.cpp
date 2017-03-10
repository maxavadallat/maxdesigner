#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>

#include "livewindow.h"
#include "ui_livewindow.h"
#include "mainwindow.h"
#include "settingscontroller.h"
#include "settingskeys.h"
#include "constants.h"

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
// Destructor
//==============================================================================
LiveWindow::~LiveWindow()
{
    // Delete Live Widget
    delete ui->quickLiveWidget;
    // Delete UI
    delete ui;

    // Release Settings
    mSettings->release();

    // ...

    qDebug() << "LiveWindow deleted.";
}
