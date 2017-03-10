#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class SettingsController;
class PreferencesDialog;
class ConfirmDialog;
class InfoDialog;
class AboutDialog;
class ProjctPropertiesDialog;
class DesignerEventFilter;
class ProjectModel;
class BaseComponentsModel;
class ComponentsModel;
class ViewsModel;
class ComponentCategoryModel;
class ComponentInfo;
class PropertiesController;
class ProjectTreeModel;
class OpenFilesModel;
class RecentProjectsModel;
class ProjectPropertiesDialog;
class CreateComponentDialog;
class CreateViewDialog;
class LiveWindow;

//==============================================================================
// Main Window Class
//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* currentProject READ currentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

    Q_PROPERTY(BaseComponentsModel* baseComponentsModel READ baseComponentsModel NOTIFY baseComponentsModelChanged)
    Q_PROPERTY(ComponentsModel* componentsModel READ componentsModel NOTIFY componentsModelChanged)
    Q_PROPERTY(ViewsModel* viewsModel READ viewsModel NOTIFY viewsModelChanged)

    Q_PROPERTY(bool screenshotMode READ screenshotMode NOTIFY screenshotModeChanged)

public:
    // Constructor
    explicit MainWindow(QWidget* aParent = NULL);

    // Get Current Project
    ProjectModel* currentProject();

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Base Components Model
    BaseComponentsModel* baseComponentsModel();
    // Get Components Model
    ComponentsModel* componentsModel();
    // Get Views Model
    ViewsModel* viewsModel();

    // Get Screen Shot Mode
    bool screenshotMode();

    // Open Project
    Q_INVOKABLE void openProject(const QString& aFilePath);

    // Open Component
    Q_INVOKABLE void openComponent(ComponentInfo* aComponent);

    // Destructor
    ~MainWindow();

signals:
    // Current Project Changed Signal
    void currentProjectChanged(ProjectModel* aProject);
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aCOmponent);

    // Base Components Model Changed Signal
    void baseComponentsModelChanged(BaseComponentsModel* aBaseComponents);
    // Components Model Changed Signal
    void componentsModelChanged(ComponentsModel* aComponents);
    // Views Model Changed Signal
    void viewsModelChanged(ViewsModel* aViews);

    // Screen Shot Mode Changed Signal
    void screenshotModeChanged(const bool& aScreenShotMode);

    // Component Opened Signal
    void componentOpened(ComponentInfo* aComponent);

    // Proto Type Selected Signal
    void protoTypeSelected(ComponentInfo* aComponent);

private:
    // Init
    void init();
    // restore UI
    void restoreUI();

    // Take Screen Shot
    void takeScreenShot();
    // Toggle Designer Mode
    void toggleDesignerMode();

    // Set Screen Shot Mode
    void setScreenShotMode(const bool& aScreenShotMode);

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
    void createNewComponent(const QString& aName,
                            const QString& aType,
                            const QString& aBase,
                            const QString& aCategory,
                            const int& aWidth = 0,
                            const int& aHeight = 0);

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

    // Import Path Added Slot
    void importPathAdded(const QString& aImportPath);
    // Import Path Removed Slot
    void importPathRemoved(const QString& aImportPath);
    // Import Paths Changed Slot
    void importPathsChanged(const QStringList& aImportPaths);

    // Plugin Path Added Slot
    void pluginPathAdded(const QString& aPluginPath);
    // Plugin Path Removed Slot
    void pluginPathRemoved(const QString& aPluginPath);
    // Plugin Paths Changed Slot
    void pluginPathsChanged(const QStringList& aPluginPaths);

    // Base Component Created Slot
    void baseComponentCreated(ComponentInfo* aComponent);
    // Component Created Slot
    void componentCreated(ComponentInfo* aComponent);
    // View Creaeted Slot
    void viewCreated(ComponentInfo* aComponent);


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
    // Action View Screenshot Triggered Slot
    void on_actionScreenshot_triggered();
    // Action Switch Mode Triggered Slot
    void on_actionSwitchMode_triggered();
    // Action Edit Component Triggered Slot
    void on_actionEditComponent_triggered();
    // Action Edit View Triggered Slot
    void on_actionEditView_triggered();
    // Action Close Component Triggered Slot
    void on_actionCloseComponent_triggered();

    // ...

    // Action Quit Triggered Slot
    void on_actionQuit_triggered();

protected: // from QMainWindow

    // Key Release Event
    virtual void keyReleaseEvent(QKeyEvent* aEvent);

    // Event
    virtual bool event(QEvent* aEvent);

private:
    // UI
    Ui::MainWindow*             ui;

    // Settings
    SettingsController*         mSettings;

    // Event Filter
    DesignerEventFilter*        mEventFilter;

    // Project Tree Model
    ProjectTreeModel*           mProjectTreeModel;

    // Open Files List Model
    OpenFilesModel*             mOpenfiles;

    // Recent Projects Model
    RecentProjectsModel*        mRecentProjects;

    // Preferences Dialog
    PreferencesDialog*          mPreferencesDialog;
    // Project Properties Dialog
    ProjectPropertiesDialog*    mProjectPropertiesDiaog;
    // Create Component Dialog
    CreateComponentDialog*      mCreateComponentDialog;
    // Create View Dialog
    CreateViewDialog*           mCreateViewDialog;
    // Live Window
    LiveWindow*                 mLiveWindow;

    // Properties Controller
    PropertiesController*       mPropertiesController;

    // Project Model
    ProjectModel*               mProjectModel;
    // Base Components List Model
    BaseComponentsModel*        mBaseComponents;
    // Components List Model
    ComponentsModel*            mComponents;
    // Views List Model
    ViewsModel*                 mViews;

    // Components Categories Model
    ComponentCategoryModel*     mCategories;

    // Current Component
    ComponentInfo*              mCurrentComponent;

    // Screen Shot Mode
    bool                        mScreenShotMode;
};

#endif // MAINWINDOW_H
