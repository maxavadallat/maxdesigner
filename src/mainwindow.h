#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingscontroler.h"
#include "preferencesdialog.h"
#include "confirmdialog.h"
#include "infodialog.h"
#include "aboutdialog.h"

#include "basecomponentsmodel.h"
#include "componentslistmodel.h"
#include "viewslistmodel.h"
#include "openfilesmodel.h"


namespace Ui {
class MainWindow;
}

//==============================================================================
// Main Window Class
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit MainWindow(QWidget* aParent = NULL);
    // Destructor
    ~MainWindow();

protected:
    // Init
    void init();
    // restore UI
    void restoreUI();

private slots:
    // Action About Triggered Slot
    void on_actionAbout_triggered();
    // Action Preferences Triggered Slot
    void on_actionPreferences_triggered();
    // Action Quit Triggered Slot
    void on_actionQuit_triggered();

private:
    // UI
    Ui::MainWindow*         ui;

    // Settings
    SettingsControler*      mSettings;

    // Base Components List Model
    BaseComponentsModel*    mBaseComponents;
    // Components List Model
    ComponentsListModel*    mComponents;
    // Views List Model
    ViewsListModel*         mViews;
    // Open Files List Model
    OpenFilesModel*         mOpenfiles;
};

#endif // MAINWINDOW_H
