#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingscontroler.h"
#include "preferencesdialog.h"
#include "confirmdialog.h"
#include "infodialog.h"
#include "aboutdialog.h"

#include "projectpropertiesdialog.h"
#include "createcomponentdialog.h"

#include "basecomponentsmodel.h"
#include "componentsmodel.h"
#include "viewsmodel.h"
#include "openfilesmodel.h"

#include "recentprojectsmodel.h"

namespace Ui {
class MainWindow;
}

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Main Window Class
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* currentProject READ currentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Constructor
    explicit MainWindow(QWidget* aParent = NULL);

    // Get Current Project
    ProjectModel* currentProject();

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Open Project
    Q_INVOKABLE void openProject(const QString& aFilePath);

    // Destructor
    ~MainWindow();

signals:
    // Current Project Changed Signal
    void currentProjectChanged(ProjectModel* aProject);
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aCOmponent);

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
    // Launch Save Project As
    void launchSaveProjectAs();
    // Launch Project
    void launchProjectProperties();
    // Launch Define Base Component
    void launchDefineBaseComponent();
    // Launch Create Component
    void launchCreateComponent();
    // Launch Create View
    void launchCreateView();

    // ...

    // Create New Project
    void createNewProject();
    // Create New Component
    void createNewComponent(const QString& aName, const QString& aType = "");

    // Save Project
    void saveProject(const QString& aFilePath = "");
    // Save Component
    void saveComponent(const QString& aFilePath = "");

    // ...

    // Update Project
    void updateProject();
    // Update Component
    void updateComponent();

    // Close Project
    void closeProject();
    // Close Component
    void closeComponent();

    // Remove Component By Name
    void removeComponent(const QString& aName);

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
    // Action Open Project Triggered Slot
    void on_actionOpenFileOrProject_triggered();
    // Action Save Project Triggered Slot
    void on_actionSaveProject_triggered();
    // Action Save Project As Triggered Slot
    void on_actionSaveProjectAs_triggered();
    // Action Project Properties Triggered Slot
    void on_actionProjectProperties_triggered();
    // Action Close Project Triggered Slot
    void on_actionCloseProject_triggered();
    // Action Define Base Component Triggered Slot
    void on_actionDefineBaseComponent_triggered();
    // Action Create Component Triggered Slot
    void on_actionCreateComponent_triggered();
    // Action Create View Triggered Slot
    void on_actionCreateView_triggered();
    // Action Remove Component Triggered Slot
    void on_actionRemoveComponent_triggered();
    // Action Remove View Triggered Slot
    void on_actionRemoveView_triggered();

    // ...

    // Action Quit Triggered Slot
    void on_actionQuit_triggered();

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
    ComponentsModel*            mComponents;
    // Views List Model
    ViewsModel*                 mViews;
    // Open Files List Model
    OpenFilesModel*             mOpenfiles;

    // Recent Projects Model
    RecentProjectsModel*        mRecentProjects;

    // Preferences Dialog
    PreferencesDialog*          mPreferencesDialog;
    // Project Properties Dialog
    ProjectPropertiesDialog*    mProjectPropertiesDiaog;
    // Define Base Component Dialog
    DefineBaseComponentDialog*  mDefineBaseComponentDialog;

    // Project Model
    ProjectModel*               mProjectModel;

    // Current Component
    ComponentInfo*              mCurrentComponent;
};

#endif // MAINWINDOW_H
