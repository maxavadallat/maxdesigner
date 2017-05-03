#include "src/createdatasourcedialog.h"
#include "ui_createdatasourcedialog.h"

//==============================================================================
// Constructor
//==============================================================================
CreateDataSourceDialog::CreateDataSourceDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::CreateDataSourceDialog)
{
    // Setup UI
    ui->setupUi(this);
}


//==============================================================================
// Reset
//==============================================================================
void CreateDataSourceDialog::reset()
{
    ui->dataSourceNameEdit->clear();
}

//==============================================================================
// Get Data Source Name
//==============================================================================
QString CreateDataSourceDialog::dataSourceName()
{
    return ui->dataSourceNameEdit->text();
}

//==============================================================================
// Destructor
//==============================================================================
CreateDataSourceDialog::~CreateDataSourceDialog()
{
    // Delete UI
    delete ui;
}
