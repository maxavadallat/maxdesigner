
#include <QDebug>
#include <QApplication>

#include "designerapplication.h"
#include "mainwindow.h"
#include "constants.h"

//==============================================================================
// Main
//==============================================================================
int main(int argc, char* argv[])
{
    // Main Application
    DesignerApplication app(argc, argv);

    // Set Application Name
    app.setApplicationName(DEFAULT_APPLICATION_NAME);
    // Set Organization Name
    app.setOrganizationName(DEFAULT_ORGANIZATION_NAME);
    // Set Organization Domain
    app.setOrganizationDomain(DEFAULT_ORGANIZATION_DOMAIN);

    // Main Window
    MainWindow w;
    // Set Main Window
    app.setMainWindow(&w);
    // Show Main Window
    w.show();

    // Exec Main Event Loop
    return app.exec();
}
