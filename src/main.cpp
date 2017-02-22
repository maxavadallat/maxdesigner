
#include <QDebug>
#include <QImage>
#include <QApplication>

#include "mainwindow.h"
#include "constants.h"

//==============================================================================
// Main
//==============================================================================
int main(int argc, char *argv[])
{
    // Main Application
    QApplication app(argc, argv);

    // Set Application Name
    app.setApplicationName(DEFAULT_APPLICATION_NAME);
    // Set Organization Name
    app.setOrganizationName(DEFAULT_ORGANIZATION_NAME);
    // Set Organization Domain
    app.setOrganizationDomain(DEFAULT_ORGANIZATION_DOMAIN);

    // Main Window
    MainWindow w;
    // Show Main Window
    w.show();
    // Exec Main Event Loop
    return app.exec();
}
