#include "src/qmleditorwindow.h"
#include "ui_qmleditorwindow.h"

//==============================================================================
// Constructor
//==============================================================================
QMLEditorWindow::QMLEditorWindow(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::QMLEditorWindow)
{
    ui->setupUi(this);
}

//==============================================================================
// Destructor
//==============================================================================
QMLEditorWindow::~QMLEditorWindow()
{
    delete ui;
}
