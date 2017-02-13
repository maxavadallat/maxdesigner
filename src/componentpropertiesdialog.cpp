#include "src/componentpropertiesdialog.h"
#include "ui_componentpropertiesdialog.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertiesDialog::ComponentPropertiesDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::ComponentPropertiesDialog)
{
    ui->setupUi(this);
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertiesDialog::~ComponentPropertiesDialog()
{
    delete ui;
}
