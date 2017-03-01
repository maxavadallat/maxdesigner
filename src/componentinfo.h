#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QString>

class ProjectModel;
class MainWindow;
class QMLParser;

//==============================================================================
// Component Info Class
//==============================================================================
class ComponentInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool protoType READ protoType NOTIFY protoTypeChanged)

    Q_PROPERTY(QString componentName READ componentName WRITE setComponentName NOTIFY componentNameChanged)
    Q_PROPERTY(QString componentType READ componentType WRITE setComponentType NOTIFY componentTypeChanged)
    Q_PROPERTY(QString componentBase READ componentBase WRITE setComponentBase NOTIFY componentBaseChanged)

    Q_PROPERTY(bool focused READ focused WRITE setFocused NOTIFY focusedChanged)

    Q_PROPERTY(QString sourcePath READ sourcePath NOTIFY sourcePathChanged)

public:
    // Create Component From QML File
    static ComponentInfo* fromQML(const QString& aFilePath, ProjectModel* aProject);

    // Create Component From Component Info File
    static ComponentInfo* fromInfoFile(const QString& aFilePath, ProjectModel* aProject);

    // Clone Component Info
    ComponentInfo* clone();

    // Get Prototype
    bool protoType();

    // Get Component Name
    QString componentName();
    // Set Component Name
    void setComponentName(const QString& aName);

    // Get Component Type
    QString componentType();
    // Set Component Type
    void setComponentType(const QString& aType);

    // Get Component Base Name
    QString componentBase();
    // Set Component Base Name
    void setComponentBase(const QString& aBaseName);

    // Get Focused State
    bool focused();
    // Set Focused State
    void setFocused(const bool& aFocused);

    // Get QML Source Path
    QString sourcePath();

    // Get Component Hierarchy
    QStringList hierarchy();

    // Set Parent
    void setParent(ComponentInfo* aParent);

    // Add Own Propery
    void addProperty(const QString& aName, const QVariant& aValue);
    // Remove Own Property
    void removeProperty(const QString& aName);

    // Get Property
    QVariant property(const QString& aName);
    // Set Property
    void setProperty(const QString& aName, const QVariant& aValue);

    // Add Child
    void addChild(ComponentInfo* aChild);
    // Remove Child
    void removeChild(ComponentInfo* aChild, const bool& aDelete = true);

    // Export To QML
    void exportToQML(const QString& aFilePath);

    // Get JSON Content/Sting
    QByteArray toJSON();

    // Set Up Component From JSON Content/String
    void fromJSON(const QByteArray& aContent);

    // Destructor
    ~ComponentInfo();

signals:
    // Prototype Changed Signal
    void protoTypeChanged(const bool& aProtoType);
    // Component Name Changed Signal
    void componentNameChanged(const QString& aName);
    // Component Type Changed Signal
    void componentTypeChanged(const QString& aType);
    // Component Base Name Changed
    void componentBaseChanged(const QString& aBaseName);
    // Focused State Changed Signal
    void focusedChanged(const bool& aFocused);
    // Source Path Changed Signal
    void sourcePathChanged(const QString& aPath);

protected:
    friend class ProjectModel;
    friend class MainWindow;
    friend class QMLParser;

    // Constructor
    explicit ComponentInfo(const QString& aName, const QString& aType, ProjectModel* aProject = NULL, const QString& aBaseName = "", QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();
    // Load
    void load(const QString& aFilePath = "");
    // Save
    void save(const QString& aFilePath = "");

    // Set QML Source Path
    void setSourcePath(const QString& aPath);

private: // Data
    // Project Model
    ProjectModel*           mProject;

    // Component Info File Path
    QString                 mInfoPath;
    // QML File Path
    QString                 mQMLPath;

    // ProtoType
    bool                    mProtoType;

    // Name
    QString                 mName;
    // Type
    QString                 mType;
    // Base Component Name
    QString                 mBaseName;

    // Focused State
    bool                    mFocused;

    // Own Properties
    QJsonObject             mOwnProperties;
    // Properties
    QJsonObject             mProperties;

    // Base Component Info
    ComponentInfo*          mBase;

    // Parent Component Info
    ComponentInfo*          mParent;
    // Children
    QList<ComponentInfo*>   mChildren;
};

#endif // COMPONENTINFO_H
