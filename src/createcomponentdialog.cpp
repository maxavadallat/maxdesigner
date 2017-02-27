#include <QDebug>

#include "createcomponentdialog.h"
#include "ui_createcomponentdialog.h"
#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
DefineBaseComponentDialog::DefineBaseComponentDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::CreateComponentDialog)
    , mBaseComponents(NULL)
{
    ui->setupUi(this);
}

//==============================================================================
// Set Base Compoennts List Model
//==============================================================================
void DefineBaseComponentDialog::setBaseComponentsModel(BaseComponentsModel* aModel)
{
    // Set Base Compoennts Model
    mBaseComponents = aModel;

    // Set Model For Base Components Drop Down Combo Box
    ui->baseTypeComboBox->setModel(mBaseComponents);
}

//==============================================================================
// Set Components Model
//==============================================================================
void DefineBaseComponentDialog::setComponentsModel(ComponentsModel* aModel)
{
    // Set Components Model
    mComponents = aModel;

    // Set Model For Components Drop Down Combo Box
    ui->componentTypeComboBox->setModel(mComponents);
}

//==============================================================================
// Get Base Component Name
//==============================================================================
QString DefineBaseComponentDialog::componentName()
{
    return ui->componentNameEdit->text();
}

//==============================================================================
// Get Base Component Base Class Name
//==============================================================================
QString DefineBaseComponentDialog::componentBaseName()
{
    return ui->baseTypeTab->currentIndex() == 0 ? ui->baseTypeComboBox->currentText() : ui->componentTypeComboBox->currentText();
}

//==============================================================================
// On Component Name Edit Text Changed Slot
//==============================================================================
void DefineBaseComponentDialog::on_componentNameEdit_textChanged(const QString& arg1)
{
    // Check Component Name

    // ...
}

//==============================================================================
// Destructor
//==============================================================================
DefineBaseComponentDialog::~DefineBaseComponentDialog()
{
    // Delete UI
    delete ui;
}

