#ifndef COMPONENTPROPERTIESDIALOG_H
#define COMPONENTPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class ComponentPropertiesDialog;
}

//==============================================================================
// Component Properties Dialog
//==============================================================================
class ComponentPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit ComponentPropertiesDialog(QWidget* aParent = NULL);
    // Destructor
    ~ComponentPropertiesDialog();

private:
    // UI
    Ui::ComponentPropertiesDialog *ui;
};

#endif // COMPONENTPROPERTIESDIALOG_H
