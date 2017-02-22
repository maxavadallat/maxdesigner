#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingscontroler.h"
#include "preferencesdialog.h"
#include "confirmdialog.h"
#include "infodialog.h"
#include "aboutdialog.h"

#include "projectpropertiesdialog.h"

#include "basecomponentsmodel.h"
#include "componentslistmodel.h"
#include "viewslistmodel.h"
#include "openfilesmodel.h"

#include "recentprojectsmodel.h"

#include "projectmodel.h"

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

    // Open Project
    Q_INVOKABLE void openProject(const QString& aFilePath);

    // Destructor
    ~MainWindow();

private:
    // Init
    void init();
    // restore UI
    void restoreUI();

    // Launch Preferences
    void launchPreferences();
    // Launch Create New Project
    void launchCreateNewProject();
    // Launch Open Project
    void launchOpenProject();

    // ...

    // Create New Project
    void createNewProject();
    // Create New Component
    void createNewComponent();
    // Create New View
    void createNewView();

    // ...

    // Update Project
    void updateProject();
    // Update View
    void updateView();
    // Update Component
    void updateComponent();

    // Add Import Path
    void addImportPath(const QString& aDirPath);
    // Remove Import Path
    void removeImportPath(const QString& aDirPath);

    // Add Plugin Path
    void addPluginPath(const QString& aDirPath);
    // Remove Plugin Path
    void removePluginPath(const QString& aDirPath);

private slots:
    // Action About Triggered Slot
    void on_actionAbout_triggered();
    // Action Preferences Triggered Slot
    void on_actionPreferences_triggered();
    // Action Create New Project Triggered Slot
    void on_actionCreateNewProject_triggered();
    // Action Quit Triggered Slot
    void on_actionQuit_triggered();

    void on_actionOpenFileOrProject_triggered();

protected: // from QMainWindow

    // Key Release Event
    virtual void keyReleaseEvent(QKeyEvent* aEvent);

private:
    // UI
    Ui::MainWindow*             ui;

    // Settings
    SettingsControler*          mSettings;

    // Base Components List Model
    BaseComponentsModel*        mBaseComponents;
    // Components List Model
    ComponentsListModel*        mComponents;
    // Views List Model
    ViewsListModel*             mViews;
    // Open Files List Model
    OpenFilesModel*             mOpenfiles;

    // Recent Projects Model
    RecentProjectsModel*        mRecentProjects;

    // Preferences Dialog
    PreferencesDialog*          mPreferencesDialog;
    // Project Properties Dialog
    ProjectPropertiesDialog*    mProjectPropertiesDiaog;

    // Project Model
    ProjectModel*               mProjectModel;
};

#endif // MAINWINDOW_H
