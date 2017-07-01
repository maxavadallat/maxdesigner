#include <QDebug>

#include "flowwindow.h"
#include "ui_flowwindow.h"
#include "settingscontroller.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
FlowWindow::FlowWindow(ProjectModel* aProject, MainWindow* aMainWindow, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlowWindow)
    , mSettings(SettingsController::getInstance())
    , mMainWindow(aMainWindow)
    , mProject(aProject)
{
    qDebug() << "FlowWindow created.";

    // Setup UI
    ui->setupUi(this);

    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void FlowWindow::init()
{
    qDebug() << "FlowWindow::init";

    // ...

    // Restore UI
    restoreUI();
}

//==============================================================================
// Restore UI
//==============================================================================
void FlowWindow::restoreUI()
{
    qDebug() << "FlowWindow::restoreUI";

}

//==============================================================================
// Show Event
//==============================================================================
void FlowWindow::showEvent(QShowEvent* aShowEvent)
{
    QMainWindow::showEvent(aShowEvent);

    // ...

}

//==============================================================================
// Close Event
//==============================================================================
void FlowWindow::closeEvent(QCloseEvent* aCloseEvent)
{
    QMainWindow::closeEvent(aCloseEvent);

    // Emit Flow View Closed Signal
    emit flowViewClosed();

    // ...
}

//==============================================================================
// Shut Down Live
//==============================================================================
void FlowWindow::shutDown()
{
    qDebug() << "FlowWindow::shutDown";

    // ...
}

//==============================================================================
// On Actin Close Triggered Slot
//==============================================================================
void FlowWindow::on_actionClose_triggered()
{
    qDebug() << "FlowWindow::on_actionClose_triggered";

    // ...

    // Normalize Window
    showNormal();
    // Close
    close();
}

//==============================================================================
// Destructor
//==============================================================================
FlowWindow::~FlowWindow()
{
    // Shut Down
    shutDown();


    // ...

    // Delete Quick Widget First
    delete ui->flowQuickWidget;
    // Delete UI
    delete ui;

    qDebug() << "FlowWindow deleted.";
}

