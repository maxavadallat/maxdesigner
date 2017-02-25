#include "designerapplication.h"

//==============================================================================
// Constructor
//==============================================================================
DesignerApplication::DesignerApplication(int& argc, char** argv)
    : QApplication(argc, argv)
    , mMainWindow(NULL)
{
}

//==============================================================================
// Get Main Window
//==============================================================================
MainWindow* DesignerApplication::mainWindow()
{
    return mMainWindow;
}

//==============================================================================
// Set Main Window
//==============================================================================
void DesignerApplication::setMainWindow(MainWindow* aMainWindow)
{
    mMainWindow = aMainWindow;
}
