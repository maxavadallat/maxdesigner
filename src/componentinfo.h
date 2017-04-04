#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QList>
#include <QString>

class ProjectModel;
class BaseComponentsModel;
class ComponentsModel;
class ViewsModel;
class MainWindow;
class QMLParser;

class ComponentImportsModel;
class ComponentAnchorsModel;
class ComponentPropertiesModel;
class ComponentOwnPropertiesModel;
class ComponentSignalsModel;
class ComponentSlotsModel;
class ComponentStatesModel;
class ComponentTransitionsModel;
class ComponentFunctionsModel;

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

    // Anchors

    // Signals

    // Slots

    // Functions

    // States

    // Transitions

public:
    // Property Type
    enum class EPropertyType {
        EPTString   = 0,
        EPTBool,
        EPTInt,
        EPTDouble,
        EPTReal,
        EPTVar,
        EPTQtObject,
        EPTQtObjectList
    };

    Q_ENUM(EPropertyType)

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

    // Set Left Anchor
    void setAnchorLeft(const QString& aLeft);
    // Set Left Anchor Margin
    void setAnchorLeftMargin(const int& aMargin);

    // Set Right Anchor
    void setAnchorRight(const QString& aRight);
    // Set Right Anchor Margin
    void setAnchorRightMargin(const int& aMargin);

    // Set Top Anchor
    void setAnchorTop(const QString& aTop);
    // Set Top Anchor Margin
    void setAnchorTopMargin(const int& aMargin);

    // Set Bottom Anchor
    void setAnchorBottom(const QString& aBottom);
    // Set Bottom Anchor Margin
    void setAnchorBottomMargin(const int& aMargin);

    // Set Fill Anchor
    void setAnchorFill(const QString& aFill);
    // Set Anchor Margins
    void setAnchorMargins(const int& aMargin);

    // Set Center In Anchor
    void setAnchorCenterIn(const QString& aCenterIn);

    // Set Horizontal Center Anchor
    void setAnchorHorizontalCenter(const QString& aHorizontalCenter);
    // Set Horizontal Center Anchor Offset
    void setAnchorHorizontalCenterOffset(const QString& aHorizontalCenterOffset);

    // Set Vertical Center Anchor
    void setAnchorVerticalCenter(const QString& aVerticalCenter);
    // Set Vertical Center Anchor Offset
    void setAnchorVerticalCenterOffset(const QString& aVerticalCenterOffset);


    // Get Properties
    QStringList componentProperties();

    // Get Component Hierarchy
    QStringList hierarchy();

    // Get Component Property
    QVariant componentProperty(const QString& aName);
    // Add Own Property
    void addComponentOwnProperty(const QString& aName, const EPropertyType& aType = EPropertyType::EPTString, const QVariant& aDefault = QVariant());
    // Set Component Property
    void setComponentProperty(const QString& aName, const QVariant& aValue);
    // Remove Own Property
    void removeComponentProperty(const QString& aName);
    // Clear Component Property
    void clearComponentProperty(const QString& aName);

    // Check If Has Property
    Q_INVOKABLE bool hasProperty(const QString& aName);

    // Add Import
    void addImport(const QString& aImport);
    // Remove Import
    void removeImport(const QString& aImport);
    // Remove Import
    void removeImport(const int& aIndex);

    // Add Signal
    void addSignal(const QString& aName, const QStringList& aParameters = QStringList());
    // Remove Signal
    void removeSignal(const QString& aName);
    // Remove Signal
    void removeSignal(const int& aIndex);

    // Add Slot
    void addSlot(const QString& aName, const QString& aSource = "");
    // Remove Slot
    void removeSlot(const QString& aName);
    // Remove Slot
    void removeSlot(const int& aIndex);

    // Add Function
    void addFunction(const QString& aName, const QStringList& aParameters = QStringList(), const QString& aSource = "");
    // Remove Function
    void removeFunction(const QString& aName);
    // Remove Function
    void removeFunction(const int& aIndex);

    // Add State
    void addState(const QString& aName, const QString& aWhen = "");
    // Remove State
    void removeState(const QString& aName);
    // Remove State
    void removeState(const int& aIndex);

    // Add Property Change
    void addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QVariant& aValue);
    // Remove Property Change
    void removePropertyChange(const QString& aStateName, const int& aIndex);

    // Add Transition
    void addTransition(const QString& aStateFrom, const QString& aStateTo);
    // Remove Transition
    void removeTransition(const int& aIndex);
//    // Remove Transition
//    void removeTransition(const QString& aStateFrom, const QString& aStateTo);

//    // Add Parallel Animation
//    void addPrallelAnimation(const QString& aStateFrom, const QString& aStateTo);
//    // Add Sequential Animation
//    void addSequentialAnimation(const QString& aStateFrom, const QString& aStateTo);
//    // Add Property Action
//    void addPropertyAction(const QString& aStateFrom, const QString& aStateTo, const QString& aTarget, const QString& aProperty, const QVariant& aValue, const int& aIndex = -1);
//    // Add Property Animation
//    void addPropertyAnimation(const QString& aStateFrom, const QString& aStateTo, const QString& aTarget, const QString& aProperty, const QVariant& aFrom, const QVariant& aTo, const int& aIndex = -1);
//    // Add Pause Animation
//    void addPauseAnimation(const QString& aStateFrom, const QString& aStateTo, const int& aDuration);
//    // Add Sctipt Action
//    void addScriptAction(const QString& aStateFrom, const QString& aStateTo, const QString& aScript);

//    // Remove Transition Node
//    void removeTransitionNode(const QString& aStateFrom, const QString& aStateTo, const int& aIndex);
//    // Mode Transition Node
//    void moveTransitionNode(const QString& aStateFrom, const QString& aStateTo, const int& aFrom, const int& aTo);

    // Add Child
    Q_INVOKABLE void addChild(ComponentInfo* aChild);
    // Remove Child
    Q_INVOKABLE void removeChild(ComponentInfo* aChild, const bool& aDelete = true);

    // Export To QML
    void exportToQML(const QString& aFilePath);

    // Request Close
    Q_INVOKABLE void requestClose();

    // Generate Live Code
    QString generateLiveCode();

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

    // Imports

    // Import Added Signal
    void importAdded(const int& aIndex);
    // Import Removed Signal
    void importRemoved(const int& aIndex);

    // Anchors

    // Left Anchor Changed Signal
    void anchorLeftChanged(const QString& aLeft);
    // Left Anchor Margin Changed Signal
    void anchorLeftMarginChanged(const QString& aMargin);

    // Right Anchor Changed Signal
    void anchorRightChanged(const QString& aRight);
    // Right Anchor Margin Changed Signal
    void anchorRightMarginChanged(const QString& aMargin);

    // Top Anchor Changed Signal
    void anchorTopChanged(const QString& aTop);
    // Top Anchor Margin Changed Signal
    void anchorTopMarginChanged(const QString& aMargin);

    // Bottom Anchor Changed Signal
    void anchorBottomChanged(const QString& aBottom);
    // Bottom Anchor Margin Changed Signal
    void anchorBottomMarginChanged(const QString& aMargin);

    // Fill Anchor Changed Signal
    void anchorFillChanged(const QString& aFill);
    // Fill Anchor Margin Changed Signal
    void anchorFillMarginChanged(const QString& aMargin);

    // Center Anchor Changed Signal
    void anchorCenterInChanged(const QString& aCenterIn);

    // Horizontal Center Anchor Changed Signal
    void anchorHorizontalCenterChanged(const QString& aLeft);
    // Vertical Center Anchor Changed Signal
    void anchorVerticalCenterChanged(const QString& aLeft);

    // Horizontal Center Anchor Offset Changed Signal
    void anchorHorizontalCenterOffsetChanged(const QString& aOffset);
    // Vertical Center Anchor Offset Changed Signal
    void anchorVerticalCenterOfsetChanged(const QString& aOffset);

    // Component Property Changed Signal
    void componentPropertyChanged(const QString& aName, const QVariant& aValue);

    // Own Property Added Signal
    void ownPropertyAdded(const int& aIndex);
    // Own Property Removed Signal
    void ownPropertyRemoved(const int& aIndex);

    // Own Properties Updated Signal
    void ownPropertiesUpdated();

    // Signals

    // Component Signal Added Signal
    void signalAdded(const int& aIndex);
    // Component Signal Removed Signal
    void signalRemoved(const int& aIndex);

    // Slots

    // Component Slot Added Signal
    void slotAdded(const int& aIndex);
    // Component Slot Removed Signal
    void slotRemoved(const int& aIndex);

    // Functions

    // Component Function Added Signal
    void functionAdded(const int& aIndex);
    // Component Function Removed Signal
    void functionRemoved(const int& aIndex);

    // States

    // State Added
    void stateAdded(const int& aIndex);
    // State Removed
    void stateRemoved(const int& aIndex);

    // Transitions

    // Transition Added
    void transitionAdded(const int& aIndex);
    // Transition Removed
    void transitionRemoved(const int& aIndex);


    // Dynamic Properties Changed
    void dynamicPropertiesChanged();
    // Request Close Container Signal
    void requestContainerClose();

    // ...

protected:
    friend class ProjectModel;
    friend class BaseComponentsModel;
    friend class ComponentsModel;
    friend class ViewsModel;
    friend class MainWindow;
    friend class QMLParser;
    friend class PropertiesController;

    // Constructor
    explicit ComponentInfo(const QString& aName,
                           const QString& aType,
                           const QString& aCategory,
                           ProjectModel* aProject,
                           const QString& aBaseName = "",
                           const bool& aBuiltIn = false,
                           QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();
    // Clear Children
    void clearChildren();
    // Clear ID Map
    void clearIDMap();

    // Load
    void load(const QString& aFilePath = "");
    // Save
    void save(const QString& aFilePath = "");

    // Get JSON Object
    QJsonObject toJSONObject();
    // Get JSON Content/Sting
    QByteArray toJSONContent();

    // Set Up From JSON Object
    void fromJSONObject(const QJsonObject& aObject);
    // Set Up Component From JSON Content/String
    void fromJSON(const QByteArray& aContent);

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

protected: // Data
    friend class ComponentAnchorsModel;
    friend class ComponentSignalsModel;
    friend class ComponentStatesModel;
    friend class ComponentTransitionsModel;
    friend class ComponentPropertiesModel;
    friend class ComponentOwnPropertiesModel;
    friend class ComponentFunctionsModel;

    // Project Model
    ProjectModel*           mProject;

    // ProtoType
    bool                    mProtoType;
    // Dirty
    bool                    mDirty;
    // Built In
    bool                    mBuiltIn;

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

    // Groupped
    bool                    mGroupped;

    // Base Component Info
    ComponentInfo*          mBase;
    // Parent Component Info
    ComponentInfo*          mParent;

    // Children
    QList<ComponentInfo*>   mChildren;

    // Component Id Map
    QMap<QString, QObject*> mIDMap;

    // Own Properties
    QJsonObject             mOwnProperties;
    // Properties
    QJsonObject             mProperties;
    // Signals
    QJsonArray              mSignals;
    // Slots
    QJsonArray              mSlots;
    // States
    QJsonArray              mStates;
    // Transitions
    QJsonArray              mTransitions;
    // Functions
    QJsonArray              mFunctions;
    // Imports
    QJsonArray              mImports;
};

#endif // COMPONENTINFO_H
