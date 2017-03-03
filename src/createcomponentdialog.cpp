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
CreateComponentDialog::CreateComponentDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::CreateComponentDialog)
    , mBaseComponents(NULL)
{
    ui->setupUi(this);
}

//==============================================================================
// Set Base Compoennts List Model
//==============================================================================
void CreateComponentDialog::setBaseComponentsModel(BaseComponentsModel* aModel)
{
    // Set Base Compoennts Model
    mBaseComponents = aModel;

    // Set Model For Base Components Drop Down Combo Box
    ui->baseTypeComboBox->setModel(mBaseComponents);
}

//==============================================================================
// Set Components Model
//==============================================================================
void CreateComponentDialog::setComponentsModel(ComponentsModel* aModel)
{
    // Set Components Model
    mComponents = aModel;

    // Set Model For Components Drop Down Combo Box
    ui->componentTypeComboBox->setModel(mComponents);
}

//==============================================================================
// Get Base Component Name
//==============================================================================
QString CreateComponentDialog::componentName()
{
    return ui->componentNameEdit->text();
}

//==============================================================================
// Get Base Component Base Class Name
//==============================================================================
QString CreateComponentDialog::componentBaseName()
{
    return ui->baseTypeTab->currentIndex() == 0 ? ui->baseTypeComboBox->currentText() : ui->componentTypeComboBox->currentText();
}

//==============================================================================
// On Component Name Edit Text Changed Slot
//==============================================================================
void CreateComponentDialog::on_componentNameEdit_textChanged(const QString& arg1)
{
    // Check Component Name

    // ...
}

//==============================================================================
// Destructor
//==============================================================================
CreateComponentDialog::~CreateComponentDialog()
{
    // Delete UI
    delete ui;
}

