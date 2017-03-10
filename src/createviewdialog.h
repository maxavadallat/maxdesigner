#ifndef CREATEVIEWDIALOG_H
#define CREATEVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class CreateViewDialog;
}

class ProjectModel;
class ComponentInfo;
class BaseComponentsModel;
class ComponentsModel;
class ViewsModel;

//==============================================================================
// Create View Dialog
//==============================================================================
class CreateViewDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit CreateViewDialog(QWidget* aParent = NULL);

    // Set Base Compoennts List Model
    void setBaseComponentsModel(BaseComponentsModel* aModel);
    // Set Components Model
    void setComponentsModel(ComponentsModel* aModel);

    // Get View Name
    QString viewName();
    // Get View Base Name
    QString viewBaseName();

    // Get View Width
    int viewWidth();
    // Get View Height
    int viewHeight();

    // Reset
    void reset();

    // Destructor
    ~CreateViewDialog();

private slots:
    // On View Name Text Editor Text Changed Slot
    void on_viewNameEdit_textChanged(const QString& arg1);
    // Base Type Combo Box Current index Changed Slot
    void on_baseTypeComboBox_currentIndexChanged(int index);
    // Base Type Combo Box Current Index Changed Slot
    void on_componentTypeComboBox_currentIndexChanged(int index);


private: // Data
    // UI
    Ui::CreateViewDialog*   ui;

    // Base Components Model
    BaseComponentsModel*    mBaseComponents;
    // Components Model
    ComponentsModel*        mComponents;
};

#endif // CREATEVIEWDIALOG_H
