#ifndef CREATEVIEWDIALOG_H
#define CREATEVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class CreateViewDialog;
}

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Create View Dialog
//==============================================================================
class CreateViewDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit CreateViewDialog(QWidget* aParent = NULL);

    // Get View Name
    QString viewName();
    // Get View Width
    int viewWidth();
    // Get View Height
    int viewHeight();

    // Destructor
    ~CreateViewDialog();

private slots:
    // On View Name Text Editor Text Changed Slot
    void on_viewNameEdit_textChanged(const QString& arg1);

private: // Data
    // UI
    Ui::CreateViewDialog* ui;
};

#endif // CREATEVIEWDIALOG_H
