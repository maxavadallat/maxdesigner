#include <QDebug>

#include "createviewdialog.h"
#include "ui_createviewdialog.h"
#include "projectmodel.h"
#include "componentinfo.h"


//==============================================================================
// Constructor
//==============================================================================
CreateViewDialog::CreateViewDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::CreateViewDialog)
{
    ui->setupUi(this);
}

//==============================================================================
// Get View Name
//==============================================================================
QString CreateViewDialog::viewName()
{
    return ui->viewNameEdit->text();
}

//==============================================================================
// Get View Width
//==============================================================================
int CreateViewDialog::viewWidth()
{
    return ui->widthEdit->text().toInt();
}

//==============================================================================
// Get View Height
//==============================================================================
int CreateViewDialog::viewHeight()
{
    return ui->heightEdit->text().toInt();
}

//==============================================================================
// On View Name Text Editor Text Changed Slot
//==============================================================================
void CreateViewDialog::on_viewNameEdit_textChanged(const QString& arg1)
{
    Q_UNUSED(arg1);

    // Check View Name
}

//==============================================================================
// Destructor
//==============================================================================
CreateViewDialog::~CreateViewDialog()
{
    // Delete UI
    delete ui;
}

