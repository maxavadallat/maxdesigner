#include "src/projectpropertiesdialog.h"
#include "ui_projectpropertiesdialog.h"

//==============================================================================
// Constructor
//==============================================================================
ProjectPropertiesDialog::ProjectPropertiesDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::ProjectPropertiesDialog)
{
    ui->setupUi(this);
}

//==============================================================================
// Destructor
//==============================================================================
ProjectPropertiesDialog::~ProjectPropertiesDialog()
{
    delete ui;
}
