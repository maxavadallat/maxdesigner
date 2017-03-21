#include "src/aboutdialog.h"
#include "ui_aboutdialog.h"

//==============================================================================
// Constructor
//==============================================================================
AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    // Setup UI
    ui->setupUi(this);
}

//==============================================================================
// Destructor
//==============================================================================
AboutDialog::~AboutDialog()
{
    // Delete UI
    delete ui;
}

