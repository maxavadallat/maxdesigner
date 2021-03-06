#include <QDebug>

#include "createcomponentdialog.h"
#include "ui_createcomponentdialog.h"
#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "componentcategorymodel.h"
#include "projectmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
CreateComponentDialog::CreateComponentDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::CreateComponentDialog)
    , mBaseComponents(NULL)
    , mComponents(NULL)
    , mCategories(NULL)
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
// Set Categories Model
//==============================================================================
void CreateComponentDialog::setCategoriesModel(ComponentCategoryModel* aModel)
{
    // Set Categories Model
    mCategories = aModel;
    // Set Categories Combo Box Model
    ui->categoryComboBox->setModel(mCategories);
}

//==============================================================================
// Get Base Component Name
//==============================================================================
QString CreateComponentDialog::componentName()
{
    return ui->componentNameEdit->text();
}

//==============================================================================
// Get Component Categroy
//==============================================================================
QString CreateComponentDialog::componentCategory()
{
    return ui->categoryComboBox->currentText();
}

//==============================================================================
// Get Base Component Base Class Name
//==============================================================================
QString CreateComponentDialog::componentBaseName()
{
    QVariant cBase = "";

    // Check Base Type Tab
    if (ui->baseTypeTab->currentIndex() == 0) {
        cBase = ui->baseTypeComboBox->itemData(ui->baseTypeComboBox->currentIndex());
    } else {
        cBase = ui->componentTypeComboBox->itemData(ui->componentTypeComboBox->currentIndex());
    }

    return cBase.toString();
}

//==============================================================================
// Component Built In
//==============================================================================
bool CreateComponentDialog::componentBuiltIn()
{
    return ui->buildInCheckBox->isChecked();
}

//==============================================================================
// Set Component Category
//==============================================================================
void CreateComponentDialog::setComponentCategory(const QString& aCategory)
{
    // Check Categories Model
    if (mCategories) {
        // Get Index
        int cIndex = mCategories->getIndex(aCategory);
        // Check Index
        if (cIndex >= 0) {
            // Set Current Index
            ui->categoryComboBox->setCurrentIndex(cIndex);
        }
    }
}

//==============================================================================
// Set Built-in Visibility
//==============================================================================
void CreateComponentDialog::setBuiltInVisibility(const bool& aVisible)
{
    ui->buildInCheckBox->setVisible(aVisible);
}

//==============================================================================
// Reset
//==============================================================================
void CreateComponentDialog::reset()
{
    // Clear Name Edit
    ui->componentNameEdit->clear();
    // Set Focus
    ui->componentNameEdit->setFocus();
    // Set Component's Tab Index
    ui->baseTypeTab->setCurrentIndex(0);
    // Set Current Index
    ui->baseTypeComboBox->setCurrentIndex(0);
    // Set Current Text
    ui->baseTypeComboBox->setCurrentText(mBaseComponents->data(mBaseComponents->index(0)).toString());
    // Set Current Index
    ui->componentTypeComboBox->setCurrentIndex(0);
    // Set Current Text
    ui->componentTypeComboBox->setCurrentText(mComponents->data(mComponents->index(0)).toString());
    //ui->componentTypeComboBox->setCurrentText("");
    ui->categoryComboBox->setCurrentIndex(0);
    // Set Current Text
    ui->categoryComboBox->setCurrentText(ui->categoryComboBox->itemData(0).toString());
    // Reset Checked
    ui->buildInCheckBox->setChecked(false);
}

//==============================================================================
// On Component Name Edit Text Changed Slot
//==============================================================================
void CreateComponentDialog::on_componentNameEdit_textChanged(const QString& arg1)
{
    // Check Component Name
    if (!arg1.isEmpty()) {

        // Get Main Window

        // ...

    }
}

//==============================================================================
// Base Type Compo Box Current Index Changed Slot
//==============================================================================
void CreateComponentDialog::on_baseTypeComboBox_currentIndexChanged(int index)
{
    // Set Current Text
    ui->baseTypeComboBox->setCurrentText(mBaseComponents->data(mBaseComponents->index(index)).toString());
}

//==============================================================================
// Base Type Compo Box Current Index Changed Slot
//==============================================================================
void CreateComponentDialog::on_componentTypeComboBox_currentIndexChanged(int index)
{
    // Set Current Text
    ui->componentTypeComboBox->setCurrentText(mComponents->data(mComponents->index(index)).toString());
}

//==============================================================================
// Destructor
//==============================================================================
CreateComponentDialog::~CreateComponentDialog()
{
    // Delete UI
    delete ui;
}

