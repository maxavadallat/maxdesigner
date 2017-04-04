#include <QDebug>

#include "createviewdialog.h"
#include "ui_createviewdialog.h"
#include "projectmodel.h"
#include "basecomponentsmodel.h"
#include "componentsmodel.h"
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
// Set Base Compoennts List Model
//==============================================================================
void CreateViewDialog::setBaseComponentsModel(BaseComponentsModel* aModel)
{
    // Set Base Components Model
    mBaseComponents = aModel;
    // Set Combo Box Model
    ui->baseTypeComboBox->setModel(mBaseComponents);
}

//==============================================================================
// Set Components Model
//==============================================================================
void CreateViewDialog::setComponentsModel(ComponentsModel* aModel)
{
    // Set Components Model
    mComponents = aModel;
    // Set Combo Box Model
    ui->componentTypeComboBox->setModel(mComponents);
}

//==============================================================================
// Get View Name
//==============================================================================
QString CreateViewDialog::viewName()
{
    return ui->viewNameEdit->text();
}

//==============================================================================
// Get View Base Name
//==============================================================================
QString CreateViewDialog::viewBaseName()
{
    return ui->baseTypeTab->currentIndex() == 0 ? ui->baseTypeComboBox->currentText() : ui->componentTypeComboBox->currentText();
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
// Reset
//==============================================================================
void CreateViewDialog::reset()
{
    ui->viewNameEdit->clear();
    ui->viewNameEdit->setFocus();

    ui->widthEdit->clear();
    ui->heightEdit->clear();

    ui->baseTypeTab->setCurrentIndex(0);

    ui->baseTypeComboBox->setCurrentText("");
    ui->baseTypeComboBox->setCurrentIndex(-1);

    ui->componentTypeComboBox->setCurrentText("");
    ui->componentTypeComboBox->setCurrentIndex(-1);

    // ...
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
// Base Type Combo Box Current index Changed Slot
//==============================================================================
void CreateViewDialog::on_baseTypeComboBox_currentIndexChanged(int index)
{
    // Set Current Text
    ui->baseTypeComboBox->setCurrentText(mBaseComponents->data(mBaseComponents->index(index)).toString());
}

//==============================================================================
// Base Type Combo Box Current Index Changed Slot
//==============================================================================
void CreateViewDialog::on_componentTypeComboBox_currentIndexChanged(int index)
{
    // Set Current Text
    ui->componentTypeComboBox->setCurrentText(mComponents->data(mComponents->index(index)).toString());
}

//==============================================================================
// Destructor
//==============================================================================
CreateViewDialog::~CreateViewDialog()
{
    // Delete UI
    delete ui;
}

