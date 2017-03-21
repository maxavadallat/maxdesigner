#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

//==============================================================================
// Confirmation Dialog Class
//==============================================================================
class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit InfoDialog(QWidget* aParent = NULL);

    // Set Information Text
    void setInfoText(const QString& aText);

    // Destructor
    ~InfoDialog();

private:
    // UI
    Ui::InfoDialog*     ui;
};

#endif // INFODIALOG_H
