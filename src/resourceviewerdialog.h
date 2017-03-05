#ifndef RESOURCEVIEWERDIALOG_H
#define RESOURCEVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class ResourceViewerDialog;
}

//==============================================================================
// Resource Viewer Dialog Class
//==============================================================================
class ResourceViewerDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit ResourceViewerDialog(QWidget* aParent = NULL);
    // Destructor
    ~ResourceViewerDialog();

private:
    // Init
    void init();

private:
    // UI
    Ui::ResourceViewerDialog*   ui;
};

#endif // RESOURCEVIEWERDIALOG_H
