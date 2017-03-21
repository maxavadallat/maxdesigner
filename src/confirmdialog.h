#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDialog;
}

//==============================================================================
// Confirmation Dialog Class
//==============================================================================
class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit ConfirmDialog(QWidget* aParent = NULL);

    // Set Confirmation Text
    void setConfirmationText(const QString& aText);
    // Set Confirmation Icon
    void setConfirmationIcon(const QString& aIcon);

    // Destructor
    ~ConfirmDialog();

private:
    // UI
    Ui::ConfirmDialog*  ui;
};

#endif // CONFIRMDIALOG_H
