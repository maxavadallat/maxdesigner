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

//==============================================================================
// Project Model
//==============================================================================
class ProjectModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(QString projectDir READ projectDir WRITE setProjectDir NOTIFY projectDirChanged)
    Q_PROPERTY(QString mainQMLFile READ mainQMLFile WRITE setMainQMLFile NOTIFY mainQMLFileChanged)
    Q_PROPERTY(QString qmlDir READ qmlDir WRITE setQmlDir NOTIFY qmlDirChanged)
    Q_PROPERTY(QString jsDir READ jsDir WRITE setJsDir NOTIFY jsDirChanged)
    Q_PROPERTY(QString imagesDir READ imagesDir WRITE setImagesDir NOTIFY imagesDirChanged)
    Q_PROPERTY(QString baseComponentsDir READ baseComponentsDir WRITE setBaseComponentsDir NOTIFY baseComponentsDirChanged)
    Q_PROPERTY(QString componentsDir READ componentsDir WRITE setComponentsDir NOTIFY componentsDirChanged)
    Q_PROPERTY(QString viewsDir READ viewsDir WRITE setViewsDir NOTIFY viewsDirChanged)
    Q_PROPERTY(QStringList importPaths READ importPaths NOTIFY importPathsChanged)
    Q_PROPERTY(QStringList pluginPaths READ pluginPaths NOTIFY pluginPathsChanged)

    Q_PROPERTY(BaseComponentsModel* baseComponentsModel READ baseComponentsModel NOTIFY baseComponentsModelChanged)
    Q_PROPERTY(ComponentsModel* componentsModel READ componentsModel NOTIFY componentsModelChanged)
    Q_PROPERTY(ViewsModel* viewsModel READ viewsModel NOTIFY viewsModelChanged)

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent NOTIFY currentComponentChanged)

public:

    // Constructor
    explicit ProjectModel(QObject* aParent = NULL);

    // Init New Project
    void initProject(const QString& aName, const QString& aDir);
    // Load Project
    bool loadProject(const QString& aFileName);
    // Save Project
    bool saveProject(const QString& aFileName = "");
    // Close Project
    void closeProject(const bool& aSave = true);

    // Get Absolute Project File Path
    QString absoluteProjectFilePath();

    // Get Project Name
    QString projectName();
    // Set Project Name
    void setProjectName(const QString& aName);

    // Get Project Dir
    QString projectDir();
    // Set Project Dir
    void setProjectDir(const QString& aDir);

    // Get Main QML File
    QString mainQMLFile();
    // Set Main QML File
    void setMainQMLFile(const QString& aQMLFile);

    // Get QML Dir
    QString qmlDir();
    // Set QML Dir
    void setQmlDir(const QString& aQMLDir);

    // Get JS Dir
    QString jsDir();
    // Set JS Dir
    void setJsDir(const QString& aJSDir);

    // Get Images Dir
    QString imagesDir();
    // Set Images Dir
    void setImagesDir(const QString& aImagesDir);

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

    // Get Base Component Model
    BaseComponentsModel* baseComponentsModel();
    // Get Components Model
    ComponentsModel* componentsModel();
    // Get Views Model
    ViewsModel* viewsModel();

    // Get Current Component
    ComponentInfo* currentComponent();

    // Get Component By Name
    ComponentInfo* getComponentByName(const QString& aName);

    // Destructor
    ~ProjectModel();

signals:
    // Project Name Changed Signal
    void projectNameChanged(const QString& aName);
    // Poject Dir Changed Signal
    void projectDirChanged(const QString& aDir);
    // Main QML File Changed Signal
    void mainQMLFileChanged(const QString& aQMLFile);
    // QML Dir Changed Signal
    void qmlDirChanged(const QString& aQMLDir);
    // JS Dir Changed Signal
    void jsDirChanged(const QString& aJSDir);
    // Images Dir Changed Signal
    void imagesDirChanged(const QString& aImagesDir);
    // Base Components Dir Changed Signal
    void baseComponentsDirChanged(const QString& aBaseComponentsDir);
    // Components Dir Changed Signal
    void componentsDirChanged(const QString& aComponentsDir);
    // Views Dir Changed Signal
    void viewsDirChanged(const QString& aViewsDir);
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

    // Base Components Model Changed Signal
    void baseComponentsModelChanged();
    // Components Model Changed Signal
    void componentsModelChanged();
    // Views Model Changed Signal
    void viewsModelChanged();

    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

private:
    // Init
    void init();

    // Create QML Project
    void createQMLProject();
    // Load QML Project File
    void loadQMLProject(const QString& aFileName);
    // Save QML Project
    void saveQMLProject();

    // Create/register Base Components
    void createBaseComponents();

private: // Data

    // Project File Name
    QString                 mName;
    // Project Properties
    QJsonObject             mProperties;
    // Dirty Properties
    bool                    mDirty;
    // Base Components
    BaseComponentsModel*    mBaseComponents;
    // Components
    ComponentsModel*        mComponents;
    // Views
    ViewsModel*             mViews;
    // Current Compoennt
    ComponentInfo*          mCurrentComponent;
};

#endif // PROJECTMODEL_H
