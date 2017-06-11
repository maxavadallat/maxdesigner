#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QJsonObject>

class ComponentInfo;
class BaseComponentsModel;
class ComponentsModel;
class ViewsModel;
class DataSourcesModel;
class PropertiesController;
class SettingsController;

//==============================================================================
// Project Model
//==============================================================================
class ProjectModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString projectName READ projectName NOTIFY projectNameChanged)
    Q_PROPERTY(QString projectDir READ projectDir NOTIFY projectDirChanged)
    Q_PROPERTY(QString projectFilePath READ absoluteProjectFilePath NOTIFY projectFilePathChanged)

    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY screenHeightChanged)

    Q_PROPERTY(QString dashboard READ dashboard WRITE setDashboard NOTIFY dashboardChanged)

    Q_PROPERTY(QString assetsDir READ assetsDir NOTIFY assetsDirChanged)
    Q_PROPERTY(QString baseComponentsDir READ baseComponentsDir NOTIFY baseComponentsDirChanged)
    Q_PROPERTY(QString componentsDir READ componentsDir NOTIFY componentsDirChanged)
    Q_PROPERTY(QString viewsDir READ viewsDir NOTIFY viewsDirChanged)
    Q_PROPERTY(QString dataSourcesDir READ dataSourcesDir NOTIFY dataSourcesDirChanged)

    Q_PROPERTY(QString liveTempDir READ liveTempDir NOTIFY liveTempDirChanged)

    Q_PROPERTY(QStringList importPaths READ importPaths NOTIFY importPathsChanged)
    Q_PROPERTY(QStringList pluginPaths READ pluginPaths NOTIFY pluginPathsChanged)

    Q_PROPERTY(PropertiesController* propertiesController READ propertiesController NOTIFY propertiesControllerChanged)

    Q_PROPERTY(BaseComponentsModel* baseComponentsModel READ baseComponentsModel NOTIFY baseComponentsModelChanged)
    Q_PROPERTY(ComponentsModel* componentsModel READ componentsModel NOTIFY componentsModelChanged)
    Q_PROPERTY(ViewsModel* viewsModel READ viewsModel NOTIFY viewsModelChanged)
    Q_PROPERTY(DataSourcesModel* dataSourcesModel READ dataSourcesModel NOTIFY dataSourcesModelChanged)

    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

    //Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent NOTIFY currentComponentChanged)

public:
    // Constructor
    explicit ProjectModel(PropertiesController* aPropertiesController, QObject* aParent = NULL);

    // Init New Project
    bool initProject(const QString& aName, const QString& aDir);
    // Load Project
    bool loadProject(const QString& aFileName);
    // Save Project
    bool saveProject(const QString& aFileName = "");
    // Close Project
    void closeProject(const bool& aSave = true);

    // Save All Components
    void saveAllComponents();

    // Get Absolute Project Path
    QString absoluteProjectPath();
    // Get Absolute Project File Path
    QString absoluteProjectFilePath();

    // Create Base Component
    ComponentInfo* createBaseComponent(const QString& aName,
                                       const QString& aBaseName,
                                       const QString& aCategory,
                                       const bool& aBuiltIn,
                                       const int& aWidth = -1,
                                       const int& aHeight = -1);
    // Create Component
    ComponentInfo* createComponent(const QString& aName,
                                   const QString& aBaseName,
                                   const QString& aCategory,
                                   const int& aWidth = -1,
                                   const int& aHeight = -1);
    // Create View
    ComponentInfo* createView(const QString& aName,
                              const QString& aBaseName,
                              const int& aWidth,
                              const int& aHeight);

    // Create Data Source
    ComponentInfo* createDataSource(const QString& aName, const QString& aBaseName = "");

    // Get Project Name
    QString projectName();
    // Set Project Name
    void setProjectName(const QString& aName);

    // Get Project Dir
    QString projectDir();
    // Set Project Dir
    void setProjectDir(const QString& aDir);

    // Get Project Screen Width
    int screenWidth();
    // Set Project Screen Width
    void setScreenWidth(const int& aWidth);

    // Get Project Screen Height
    int screenHeight();
    // Set Project Screen Height
    void setScreenHeight(const int& aHeight);

    // Get Dashboard Image
    QString dashboard();
    // Set Dashboard Image
    void setDashboard(const QString& aDashImage);

    // Get Assets Dir
    QString assetsDir();
    // Set Assets Dir
    void setAssetsDir(const QString& aImagesDir);

    // Get Base Components Dir
    QString baseComponentsDir();
    // Set Base Components Dir
    void setBaseComponentsDir(const QString& aBaseComponentsDir);

    // Get Compoennts Dir
    QString componentsDir();
    // Set Compoennts Dir
    void setComponentsDir(const QString& aComponentsDir);

    // Get Views Dir
    QString viewsDir();
    // Set Views Dir
    void setViewsDir(const QString& aViewsDir);

    // Get Data Sources Dir
    QString dataSourcesDir();
    // Set Data Sources Dir
    void setDataSourcesDir(const QString& aDataSourcesDir);

    // Get Live Temp Dir
    QString liveTempDir();

    // Get Import Paths
    QStringList importPaths();
    // Add Import Path
    void addImportPath(const QString& aPath);
    // Remove Import Path
    void removeImportPath(const int& aIndex);
    // Set Import Paths
    void setImportPaths(const QStringList& aImportPaths);

    // Get Plugin Paths
    QStringList pluginPaths();
    // Add Plugin Path
    void addPluginPath(const QString& aPath);
    // Remove Plugin Path
    void removePluginPath(const int& aIndex);
    // Set Plugin Paths
    void setPluginPaths(const QStringList& aPluginPaths);

    // Get Filtered Properties
    QStringList filteredProperties();
    // Get Filtered Property Changes
    QStringList filteredPropertyChanges();

    // Get Properties Controller
    PropertiesController* propertiesController();

    // Get Base Component Model
    BaseComponentsModel* baseComponentsModel();
    // Get Components Model
    ComponentsModel* componentsModel();
    // Get Views Model
    ViewsModel* viewsModel();
    // Get Data Sources Model
    DataSourcesModel* dataSourcesModel();

    // Get Busy State
    bool busy();
    // Set Busy State
    void setBusy(const bool& aBusy);

    // Get Component By Name
    Q_INVOKABLE ComponentInfo* getComponentByName(const QString& aName, const QString& aType = "", const bool& aPreload = false);
    // Get Component By File Path
    Q_INVOKABLE ComponentInfo* getComponentByPath(const QString& aFilePath);

    // Generate Live Code
    Q_INVOKABLE QString generateLiveCode(ComponentInfo* aComponent, const bool& aGenerateChildren = false);
    // Generate Component Code For Live
    Q_INVOKABLE QString generateComponentCode(ComponentInfo* aComponent, const bool& aGenerateChildren = false);
    // Generate Data Source Component Live Code
    Q_INVOKABLE QString generateDataSourceLiveCode(ComponentInfo* aComponent);
    // Delete Live Code
    Q_INVOKABLE void removeLiveCode(const QString& aName);
    // Remove Live Temp File
    Q_INVOKABLE void removeLiveTempFile(const QString& aFileName);
    // Clear All Files From Live Temp Dir
    Q_INVOKABLE void clearLiveTemp();

    // Destructor
    ~ProjectModel();

signals:
    // Project Name Changed Signal
    void projectNameChanged(const QString& aName);
    // Poject Dir Changed Signal
    void projectDirChanged(const QString& aDir);
    // Project File Path Changed
    void projectFilePathChanged(const QString& aFilePath);
    // Project Screen Width Changed Signal
    void screenWidthChanged(const int& aWidth);
    // Project Screen Height Changed Signal
    void screenHeightChanged(const int& aHeight);
    // Dashboard Image Changed Signal
    void dashboardChanged(const QString& aDashImage);
    // Assets Dir Changed Signal
    void assetsDirChanged(const QString& aImagesDir);
    // Base Components Dir Changed Signal
    void baseComponentsDirChanged(const QString& aBaseComponentsDir);
    // Components Dir Changed Signal
    void componentsDirChanged(const QString& aComponentsDir);
    // Views Dir Changed Signal
    void viewsDirChanged(const QString& aViewsDir);
    // Data Sources Dir Changed Signal
    void dataSourcesDirChanged(const QString& aDataSourcesDir);
    // Live Temp Dir Changed Signal
    void liveTempDirChanged(const QString& aLiveTempDir);
    // Import Paths Changed Signal
    void importPathsChanged(const QStringList& aImportPaths);
    // Import Path Added Signal
    void importPathAdded(const QString& aImportPath);
    // Import Path Removed Signal
    void importPathRemoved(const QString& aImportPath);
    // Plugin Paths Changed Signal
    void pluginPathsChanged(const QStringList& aPluginPaths);
    // Plugin Path Added Signal
    void pluginPathAdded(const QString& aPluginPath);
    // Plugin Path Removed Signal
    void pluginPathRemoved(const QString& aPluginPath);

    // Properties Controller Changed Signal
    void propertiesControllerChanged(PropertiesController* aController);

    // Base Components Model Changed Signal
    void baseComponentsModelChanged(BaseComponentsModel* aBaseComponents);
    // Components Model Changed Signal
    void componentsModelChanged(ComponentsModel* aComponents);
    // Views Model Changed Signal
    void viewsModelChanged(ViewsModel* aViews);
    // Data Sources Model Changed Signal
    void dataSourcesModelChanged(DataSourcesModel* aDataSources);

    // Base Component Created Signal
    void baseComponentCreated(ComponentInfo* aComponent, const int& aWidth, const int& aHeight);
    // Component Created Signal
    void componentCreated(ComponentInfo* aComponent, const int& aWidth, const int& aHeight);
    // View Creaeted Signal
    void viewCreated(ComponentInfo* aComponent, const int& aWidth, const int& aHeight);
    // Data Source Created
    void dataSourceCreated(ComponentInfo* aComponent);

    // Busy State Changed Signal
    void busyChanged(const bool& aBusy);

    // Project Loaded Signal
    void projectLoaded();

    // Project Properties Dirty State changed Signal
    void dirtyChanged(const bool& aDirty);

protected:
    friend class MainWindow;
    friend class PropertiesController;
    // Init
    void init();

    // Set Project Properties Dirty State
    void setDirty(const bool& aDirty);

    // Create Base Components Model
    void createBaseComponentsModel();
    // Create Components Model
    void createComponentsModel();
    // Create Views Model
    void createViewsModel();
    // Create Data Sources Model
    void createDataSourcesModel();

    // Create Initial Components
    void createInitialComponents();

    // Set Properties Controller
    void setPropertiesController(PropertiesController* aController);

    // Set Base Components Model
    void setBaseComponentsModel(BaseComponentsModel* aBaseComponents);
    // Set Components Model
    void setComponentsModel(ComponentsModel* aComponents);
    // Set Views Model
    void setViewsModel(ViewsModel* aViews);
    // Set Data Sources Model
    void setDataSourcesModel(DataSourcesModel* aDataSources);

    // Update Base Components
    void updateBaseComponents();

    // Clear All Children
    void clearAllChildren(const bool& aClosing = false);

    // Generate Root ID From Name
    QString generateID(const QString& aName);

private: // Data
    // Project File Name
    QString                 mName;
    // Project Properties
    QJsonObject             mProperties;
    // Dirty Properties
    bool                    mDirty;
    // Properties Controller
    PropertiesController*   mPropertiesController;
    // Base Components
    BaseComponentsModel*    mBaseComponents;
    // Components
    ComponentsModel*        mComponents;
    // Views
    ViewsModel*             mViews;
    // Data Sources Model
    DataSourcesModel*       mDataSources;
    // Busy State
    bool                    mBusy;
};

#endif // PROJECTMODEL_H
