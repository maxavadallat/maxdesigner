#include "src/infodialog.h"
#include "ui_infodialog.h"

//==============================================================================
// Constructor
//==============================================================================
InfoDialog::InfoDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::InfoDialog)
{
    // Setup UI
    ui->setupUi(this);
}

//==============================================================================
// Set Information Text
//==============================================================================
void InfoDialog::setInfoText(const QString& aText)
{
    ui->infoTextLabel->setText(aText);
}

//==============================================================================
// Destructor
//==============================================================================
InfoDialog::~InfoDialog()
{
    // Delete UI
    delete ui;
}
