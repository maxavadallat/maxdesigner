#include <QDebug>

#include "datasourcewindow.h"
#include "ui_datasourcewindow.h"
#include "settingscontroller.h"
#include "livewindow.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
DataSourceWindow::DataSourceWindow(LiveWindow* aLiveWindow, ProjectModel* aProjectModel, QWidget* aParent)
    : QMainWindow(aParent)
    , ui(new Ui::DataSourceWindow)
    , mLiveWindow(aLiveWindow)
    , mProject(aProjectModel)
    , mSettings(SettingsController::getInstance())
{
    // Setup UI
    ui->setupUi(this);

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void DataSourceWindow::init()
{

    // Restore UI
    restoreUI();
}

//==============================================================================
// Restore UI
//==============================================================================
void DataSourceWindow::restoreUI()
{

}

//==============================================================================
// Shut Down
//==============================================================================
void DataSourceWindow::shutDown()
{
    // Release Settings
    mSettings->release();

    // ...
}

//==============================================================================
// Add DataSource To Control
//==============================================================================
void DataSourceWindow::addDataSource(const QString& aName)
{
    // Check Name
    if (!aName.isEmpty()) {

    }
}

//==============================================================================
// Remove Data Source From Controleld Data Sources
//==============================================================================
void DataSourceWindow::removeDataSource(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mDataSources.count()) {

    }
}

//==============================================================================
// Clear Controlled Data Sources
//==============================================================================
void DataSourceWindow::clearDataSources()
{

}

//==============================================================================
// Destructor
//==============================================================================
DataSourceWindow::~DataSourceWindow()
{
    // Shut Down
    shutDown();

    // Delete Data Source Window Quick Widget
    delete ui->dataSourceQuickWidget;
    // Delte UI
    delete ui;
}
