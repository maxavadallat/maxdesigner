#ifndef QMLEDITORWINDOW_H
#define QMLEDITORWINDOW_H

#include <QDialog>

namespace Ui {
class QMLEditorWindow;
}

//==============================================================================
// QML Editor Window Class
//==============================================================================
class QMLEditorWindow : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit QMLEditorWindow(QWidget* aParent = NULL);
    // Destructor
    ~QMLEditorWindow();

private:
    Ui::QMLEditorWindow *ui;
};

#endif // QMLEDITORWINDOW_H
