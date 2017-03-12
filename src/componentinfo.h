#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
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

    // Name
    Q_PROPERTY(QString componentName READ componentName NOTIFY componentNameChanged)
    // Type
    Q_PROPERTY(QString componentType READ componentType NOTIFY componentTypeChanged)
    // Category
    Q_PROPERTY(QString componentCategory READ componentCategory NOTIFY componentCategoryChanged)
    // Base
    Q_PROPERTY(QString componentBase READ componentBase NOTIFY componentBaseChanged)
    // Parent
    Q_PROPERTY(ComponentInfo* componentParent READ componentParent WRITE setComponentParent NOTIFY componentParentChanged)
    // Prototype
    Q_PROPERTY(bool protoType READ protoType NOTIFY protoTypeChanged)
    // Focused
    Q_PROPERTY(bool focused READ focused WRITE setFocused NOTIFY focusedChanged)
    // Is Root
    Q_PROPERTY(bool isRoot READ isRoot WRITE setIsRoot NOTIFY isRootChanged)
    // Info Path
    Q_PROPERTY(QString infoPath READ infoPath NOTIFY infoPathChanged)
    // Source Path
    Q_PROPERTY(QString sourcePath READ sourcePath NOTIFY sourcePathChanged)
    // ID
    Q_PROPERTY(QString componentID READ componentID NOTIFY componentIDChanged)
    // Object Name
    Q_PROPERTY(QString componentObjectName READ componentObjectName WRITE setComponentObjectName NOTIFY componentObjectNameChanged)
    // Pos
    Q_PROPERTY(QString posX READ posX NOTIFY posXChanged)
    Q_PROPERTY(QString posY READ posY NOTIFY posYChanged)
    Q_PROPERTY(QString posZ READ posZ NOTIFY posZChanged)
    // Size
    Q_PROPERTY(QString width READ width NOTIFY widthChanged)
    Q_PROPERTY(QString height READ height NOTIFY heightChanged)

    // Dynamic Properties
    Q_PROPERTY(QList<QByteArray> dynamicProperties READ dynamicProperties NOTIFY dynamicPropertiesChanged)

    // Anchors

    // States

    // Transitions


public:
    // Create Component From QML File
    static ComponentInfo* fromQML(const QString& aFilePath, ProjectModel* aProject);
    // Create Component From Component Info File
    static ComponentInfo* fromInfoFile(const QString& aFilePath, ProjectModel* aProject);

    // Clone Component Info
    Q_INVOKABLE ComponentInfo* clone();

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

    // Get Component Category
    QString componentCategory();
    // Set Component Category
    void setComponentCategory(const QString& aCategory);

    // Get Component Base Name
    QString componentBase();
    // Set Component Base Name
    void setComponentBase(const QString& aBaseName);

    // Get Component Parent
    ComponentInfo* componentParent();
    // Set Component Parent
    void setComponentParent(ComponentInfo* aParent);

    // Get Focused State
    bool focused();
    // Set Focused State
    void setFocused(const bool& aFocused);

    // Get Is Root
    bool isRoot();
    // Set Is Root
    void setIsRoot(const bool& aRoot);

    // Get QML Source Path
    QString sourcePath();

    // Get Component Info Path
    QString infoPath();

    // Get Component ID
    QString componentID();

    // Get Object Name
    QString componentObjectName();

    // Get Pos X
    QString posX();
    // Get Pos Y
    QString posY();
    // Get Pos Z
    QString posZ();

    // Get Width
    QString width();
    // Get Height
    QString height();

    // Signals

    // Anchors

    // States

    // Transitions

    // Get Properties
    QStringList componentProperties();

    // Get Dynamic Properties
    QList<QByteArray> dynamicProperties();

    // Get Component Hierarchy
    QStringList hierarchy();

    // Set Parent
    void setParent(ComponentInfo* aParent);

    // Get Component Property
    QVariant componentProperty(const QString& aName);
    // Set Component Property
    void setComponentProperty(const QString& aName, const QVariant& aValue);
    // Remove Own Property
    void removeProperty(const QString& aName);

    // Add State
    void addState(const QString& aName);
    // Remove State
    void removeState(const QString& aName);

    // Add Property Change
    void addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QVariant& aValue, const int& aIndex = -1);
    // Remove Property Change
    void removePropertyChange(const int& aIndex);

    // Add Transition
    void addTransition(const QString& aStateFrom, const QString& aStateTo);
    // Remove Transition
    void removeTransition(const int& aIndex);

    // Add Property Action
    void addPropertyAction(const QString& aStateFrom, const QString& aStateTo, const QString& aTarget, const QString& aProperty, const QVariant& aValue, const int& aIndex = -1);
    // Remove Property Action
    void removePropertyAction(const int& aIndex);

    // Add Property Animation
    void addPropertyAnimation(const QString& aStateFrom, const QString& aStateTo, const QString& aTarget, const QString& aProperty, const QVariant& aFrom, const QVariant& aTo, const int& aIndex = -1);
    // Remove Property Animation
    void removePropertyAnimation(const int& aIndex);

    // Add Child
    Q_INVOKABLE void addChild(ComponentInfo* aChild);
    // Remove Child
    Q_INVOKABLE void removeChild(ComponentInfo* aChild, const bool& aDelete = true);

    // Export To QML
    void exportToQML(const QString& aFilePath);

    // Get JSON Object
    QJsonObject toJSONObject();
    // Get JSON Content/Sting
    QByteArray toJSONContent();

    // Set Up From JSON Object
    void fromJSONObject(const QJsonObject& aObject);
    // Set Up Component From JSON Content/String
    void fromJSON(const QByteArray& aContent);

    // Request Close
    Q_INVOKABLE void requestClose();

    // Destructor
    ~ComponentInfo();

signals:
    // Prototype Changed Signal
    void protoTypeChanged(const bool& aProtoType);
    // Component Name Changed Signal
    void componentNameChanged(const QString& aName);
    // Component Type Changed Signal
    void componentTypeChanged(const QString& aType);
    // Component Category Changed Signal
    void componentCategoryChanged(const QString& aCategory);
    // Component Base Name Changed
    void componentBaseChanged(const QString& aBaseName);
    // Component Parent Changed Signal
    void componentParentChanged(ComponentInfo* aParent);
    // Info Path Changed Signal
    void infoPathChanged(const QString& aInfoPath);
    // Focused State Changed Signal
    void focusedChanged(const bool& aFocused);
    // Is Root changed Signal
    void isRootChanged(const bool& aRoot);
    // Source Path Changed Signal
    void sourcePathChanged(const QString& aPath);

    // Component ID Changed Signal
    void componentIDChanged(const QString& aID);
    // Object Name Changed Signal
    void componentObjectNameChanged(const QString& aObjectName);

    // Pos X Changed  Signal
    void posXChanged(const QString& aPosX);
    // Pos Y Changed Signal
    void posYChanged(const QString aPosY);
    // Pos Z Changed Signal
    void posZChanged(const QString aPosZ);
    // Width Changed Signal
    void widthChanged(const QString& aWidth);
    // Height Changed Signal
    void heightChanged(const QString& aHeight);

    // Signals

    // Anchors

    // States

    // Transitions

    // Dynamic Properties Changed
    void dynamicPropertiesChanged();

    // Request Close Container Signal
    void requestContainerClose();

    // ...

//protected:
public:
    friend class ProjectModel;
    friend class MainWindow;
    friend class QMLParser;
    friend class PropertiesController;

    // Constructor
    explicit ComponentInfo(const QString& aName,
                           const QString& aType,
                           const QString& aCategory,
                           ProjectModel* aProject,
                           const QString& aBaseName = "",
                           QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();
    // Clear Children
    void clearChildren();

    // Load
    void load(const QString& aFilePath = "");
    // Save
    void save(const QString& aFilePath = "");

    // Set QML Source Path
    void setSourcePath(const QString& aPath);
    // Set Info Path
    void setInfoPath(const QString& aInfoPath);

    // Set Component ID
    void setComponentID(const QString& aID);
    // Set Object Name
    void setComponentObjectName(const QString& aObjectName);

    // Set Pos X
    void setPosX(const QString& aPosX);
    // Set Pos Y
    void setPosY(const QString& aPosY);
    // Set Pos Z
    void setPosZ(const QString& aPosZ);

    // Set Width
    void setWidth(const QString& aWidth);
    // Set Height
    void setHeight(const QString& aHeight);

    // Signals

    // Anchors

    // States

    // Transitions

    // Set Dirty State
    void setDirty(const bool& aDirty);

protected slots:
    // Base Components Dir Changed Slot
    void baseComponentsDirChanged(const QString& aBaseComponentsDir);
    // Components Dir Changed Slot
    void componentsDirChanged(const QString& aComponentsDir);
    // Views Dir Changed Slot
    void viewsDirChanged(const QString& aViewsDir);

private: // Data
    // Project Model
    ProjectModel*           mProject;

    // ProtoType
    bool                    mProtoType;

    // Dirty
    bool                    mDirty;

    // Component Info File Path
    QString                 mInfoPath;
    // QML File Path
    QString                 mQMLPath;

    // Name
    QString                 mName;
    // Type
    QString                 mType;
    // Category
    QString                 mCategory;
    // Base Component Name
    QString                 mBaseName;

    // Focused State
    bool                    mFocused;
    // Is Root
    bool                    mIsRoot;

    // Base Component Info
    ComponentInfo*          mBase;
    // Parent Component Info
    ComponentInfo*          mParent;

    // Children
    QList<ComponentInfo*>   mChildren;

    // Own Properties
    QJsonObject             mOwnProperties;
    // Properties
    QJsonObject             mProperties;

    // Signals
    QJsonArray              mSignals;
    // States
    QJsonArray              mStates;
    // Transitions
    QJsonArray              mTransitions;

};

#endif // COMPONENTINFO_H
