#include "src/confirmdialog.h"
#include "ui_confirmdialog.h"

//==============================================================================
// Constructor
//==============================================================================
ConfirmDialog::ConfirmDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmDialog)
{
    // Setup UI
    ui->setupUi(this);
}

//==============================================================================
// Set Confirmation Text
//==============================================================================
void ConfirmDialog::setConfirmationText(const QString& aText)
{
    ui->confirmTextLabel->setText(aText);
}

//==============================================================================
// Set Confirmation Icon
//==============================================================================
void ConfirmDialog::setConfirmationIcon(const QString& aIcon)
{
    ui->confirmIcon->setPixmap(QPixmap(aIcon));
}

//==============================================================================
// Destructor
//==============================================================================
ConfirmDialog::~ConfirmDialog()
{
    // Delete UI
    delete ui;
}
