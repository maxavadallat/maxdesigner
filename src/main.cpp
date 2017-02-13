
#include <QDebug>
#include <QImage>
#include <QApplication>
#include "mainwindow.h"

//==============================================================================
// Main
//==============================================================================
int main(int argc, char *argv[])
{
    // Main Application
    QApplication a(argc, argv);
    // Main Window
    MainWindow w;
    // Show Main Window
    w.show();
    // Exec Main Event Loop
    return a.exec();
}
