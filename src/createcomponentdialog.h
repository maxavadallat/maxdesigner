#ifndef CREATECOMPONENTDIALOG_H
#define CREATECOMPONENTDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QAbstractListModel>

namespace Ui {
class CreateComponentDialog;
}

class ProjectModel;
class ComponentInfo;
class BaseComponentsModel;
class ComponentsModel;
class ComponentCategoryModel;

//==============================================================================
// Create Component Dialog Class
//==============================================================================
class CreateComponentDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit CreateComponentDialog(QWidget* aParent = NULL);

    // Set Base Compoennts List Model
    void setBaseComponentsModel(BaseComponentsModel* aModel);
    // Set Components Model
    void setComponentsModel(ComponentsModel* aModel);
    // Set Categories Model
    void setCategoriesModel(ComponentCategoryModel* aModel);

    // Get Component Name
    QString componentName();
    // Get Component Categroy
    QString componentCategory();
    // Get Component Base Class Name
    QString componentBaseName();

    // Set Component Category
    void setComponentCategory(const QString& aCategory);

    // Reset
    void reset();

    // Destructor
    ~CreateComponentDialog();

private slots:
    // On Component Name Edit Text Changed Slot
    void on_componentNameEdit_textChanged(const QString& arg1);

private:
    // UI
    Ui::CreateComponentDialog*  ui;

    // Base Compoennts List Model
    BaseComponentsModel*            mBaseComponents;
    // Components Model
    ComponentsModel*                mComponents;
    // Components Category Model
    ComponentCategoryModel*         mCategories;
};






#endif // CREATECOMPONENTDIALOG_H
