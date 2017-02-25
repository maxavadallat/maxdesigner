#ifndef DESIGNERAPPLICATION_H
#define DESIGNERAPPLICATION_H

#include <QApplication>
#include <QObject>

class MainWindow;

//==============================================================================
// Designer Application
//==============================================================================
class DesignerApplication : public QApplication
{
    Q_OBJECT

public:
    // Constructor
    DesignerApplication(int& argc, char** argv);

    // Get Main Window
    MainWindow* mainWindow();
    // Set Main Window
    void setMainWindow(MainWindow* aMainWindow);

private: // Data
    // Main Window
    MainWindow*     mMainWindow;
};

#endif // DESIGNERAPPLICATION_H
