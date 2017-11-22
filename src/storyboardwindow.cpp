#include <QDebug>

#include "storyboardwindow.h"
#include "ui_storyboardwindow.h"
#include "settingscontroller.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
StoryBoardWindow::StoryBoardWindow(ProjectModel* aProject, MainWindow* aMainWindow, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StoryBoardWindow)
    , mSettings(SettingsController::getInstance())
    , mMainWindow(aMainWindow)
    , mProject(aProject)
{
    qDebug() << "StoryBoardWindow created.";

    // Setup UI
    ui->setupUi(this);

    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void StoryBoardWindow::init()
{
    qDebug() << "StoryBoardWindow::init";

    // ...

    // Restore UI
    restoreUI();
}

//==============================================================================
// Restore UI
//==============================================================================
void StoryBoardWindow::restoreUI()
{
    qDebug() << "StoryBoardWindow::restoreUI";

    setWindowTitle("Story Board");

    // ...
}

//==============================================================================
// Show Event
//==============================================================================
void StoryBoardWindow::showEvent(QShowEvent* aShowEvent)
{
    QMainWindow::showEvent(aShowEvent);

    // ...

}

//==============================================================================
// Close Event
//==============================================================================
void StoryBoardWindow::closeEvent(QCloseEvent* aCloseEvent)
{
    QMainWindow::closeEvent(aCloseEvent);

    // Emit Story Board Window Closed Signal
    emit storyBoardWindowClosed();

    // ...
}

//==============================================================================
// Shut Down Live
//==============================================================================
void StoryBoardWindow::shutDown()
{
    qDebug() << "StoryBoardWindow::shutDown";

    // ...
}

//==============================================================================
// On Actin Close Triggered Slot
//==============================================================================
void StoryBoardWindow::on_actionClose_triggered()
{
    qDebug() << "StoryBoardWindow::on_actionClose_triggered";

    // ...

    // Normalize Window
    showNormal();
    // Close
    close();
}

//==============================================================================
// Destructor
//==============================================================================
StoryBoardWindow::~StoryBoardWindow()
{
    // Shut Down
    shutDown();


    // ...

    // Delete Quick Widget First
    delete ui->flowQuickWidget;
    // Delete UI
    delete ui;

    qDebug() << "StoryBoardWindow deleted.";
}

