#ifndef PROJECTPROPERTIESDIALOG_H
#define PROJECTPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class ProjectPropertiesDialog;
}

//==============================================================================
// Project Properties Dialog
//==============================================================================
class ProjectPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit ProjectPropertiesDialog(QWidget* aParent = NULL);
    // Destructor
    ~ProjectPropertiesDialog();

private:
    // UI
    Ui::ProjectPropertiesDialog*    ui;
};

#endif // PROJECTPROPERTIESDIALOG_H
