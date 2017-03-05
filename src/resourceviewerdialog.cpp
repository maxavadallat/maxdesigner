#include <QDebug>

#include "resourceviewerdialog.h"
#include "ui_resourceviewerdialog.h"

//==============================================================================
// Constructor
//==============================================================================
ResourceViewerDialog::ResourceViewerDialog(QWidget* aParent)
    : QDialog(aParent)
    , ui(new Ui::ResourceViewerDialog)
{
    ui->setupUi(this);
}

//==============================================================================
// Init
//==============================================================================
void ResourceViewerDialog::init()
{

}

//==============================================================================
// Destructor
//==============================================================================
ResourceViewerDialog::~ResourceViewerDialog()
{
    delete ui;
}
