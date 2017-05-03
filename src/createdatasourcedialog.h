#ifndef CREATEDATASOURCEDIALOG_H
#define CREATEDATASOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateDataSourceDialog;
}

//==============================================================================
// Create Data Source Dialog Class
//==============================================================================
class CreateDataSourceDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit CreateDataSourceDialog(QWidget* aParent = NULL);

    // Reset
    void reset();

    // Get Data Source Name
    QString dataSourceName();

    // Destructor
    ~CreateDataSourceDialog();

private: // Data
    // UI
    Ui::CreateDataSourceDialog* ui;
};

#endif // CREATEDATASOURCEDIALOG_H
