#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QList>
#include <QString>

class ProjectModel;
class PropertiesController;
class BaseComponentsModel;
class ComponentsModel;
class ViewsModel;
class DataSourcesModel;
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
    // Component Tag
    Q_PROPERTY(QString componentTag READ componentTag WRITE setComponentTag NOTIFY componentTagChanged)
    // Category
    Q_PROPERTY(QString componentCategory READ componentCategory NOTIFY componentCategoryChanged)
    // Base
    Q_PROPERTY(QString componentBase READ componentBase NOTIFY componentBaseChanged)
    // Parent
    Q_PROPERTY(ComponentInfo* componentParent READ componentParent WRITE setComponentParent NOTIFY componentParentChanged)
    // Component Path
    Q_PROPERTY(QString componentPath READ componentPath NOTIFY componentPathChanged)
    // QML Container
    Q_PROPERTY(QObject* componentContainer READ componentContainer WRITE setComponentContainer NOTIFY componentContainerChanged)
    // Prototype
    Q_PROPERTY(bool protoType READ protoType NOTIFY protoTypeChanged)
    // Focused
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)
    // Is Root
    Q_PROPERTY(bool isRoot READ isRoot NOTIFY isRootChanged)
    // Built In
    Q_PROPERTY(bool builtIn READ builtIn NOTIFY builtInChanged)
    // Child Count
    Q_PROPERTY(int childCount READ childCount NOTIFY childCountChanged)
    // Child Depth
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)

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

    // Left Anchor Target
    Q_PROPERTY(QString anchorsLeft READ anchorsLeft NOTIFY anchorsLeftChanged)
    // Right Anchor Target
    Q_PROPERTY(QString anchorsRight READ anchorsRight NOTIFY anchorsRightChanged)
    // Top Anchor Target
    Q_PROPERTY(QString anchorsTop READ anchorsTop NOTIFY anchorsTopChanged)
    // Bottom Anchor Target
    Q_PROPERTY(QString anchorsBottom READ anchorsBottom NOTIFY anchorsBottomChanged)

    // Fill Target
    Q_PROPERTY(QString anchorsFill READ anchorsFill NOTIFY anchorsFillChanged)
    // CenterIn Target
    Q_PROPERTY(QString anchorsCenterIn READ anchorsCenterIn NOTIFY anchorsCenterInChanged)
    // Horizontal Center Target
    Q_PROPERTY(QString horizontalCenter READ horizontalCenter NOTIFY anchorsHorizontalCenterChanged)
    // Vertical Center Target
    Q_PROPERTY(QString verticalCenter READ verticalCenter NOTIFY anchorsVerticalCenterChanged)

    // Margins
    Q_PROPERTY(QString anchorsMargins READ anchorsMargins NOTIFY anchorsMarginsChanged)

    // Left Margin
    Q_PROPERTY(QString anchorsLeftMargin READ anchorsLeftMargin NOTIFY anchorsLeftMarginChanged)
    // Right Margin
    Q_PROPERTY(QString anchorsRightMargin READ anchorsRightMargin NOTIFY anchorsRightMarginChanged)
    // Top Margin
    Q_PROPERTY(QString anchorsTopMargin READ anchorsTopMargin NOTIFY anchorsTopMarginChanged)
    // Bottom Margin
    Q_PROPERTY(QString anchorsBottomMargin READ anchorsBottomMargin NOTIFY anchorsBottomMarginChanged)

    // Horizontal Center Offset
    Q_PROPERTY(QString anchorsHorizontalOffset READ anchorsHorizontalOffset NOTIFY anchorsHorizontalOffsetChanged)
    // Vertical Center Offset
    Q_PROPERTY(QString anchorsVerticalOffset READ anchorsVerticalOffset NOTIFY anchorsVerticalOffsetChanged)


    Q_PROPERTY(bool useImplictSize READ useImplictSize WRITE setUseImplictSize NOTIFY useImplictSizeChanged)

    Q_PROPERTY(bool layerVisible READ layerVisible WRITE setLayerVisible NOTIFY layerVisibleChanged)

    Q_PROPERTY(bool dirty READ getDirty NOTIFY dirtyChanged)

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
        EPTQtObjectList,
        EPTEnum,
        EPTAlias
    };

    Q_ENUM(EPropertyType)

public:
    // Create Component From Component Info File
    static ComponentInfo* fromInfoFile(const QString& aFilePath, ProjectModel* aProject, const bool aCreateChildren = true);

    // Clone Component Info
    Q_INVOKABLE ComponentInfo* clone();

    // Get Prototype
    bool protoType();

    // Get Dirty
    bool getDirty();

    // Get Component Name
    QString componentName();
    // Set Component Name
    void setComponentName(const QString& aName);

    // Get Component Type
    QString componentType();
    // Set Component Type
    void setComponentType(const QString& aType);

    // Component Tag
    QString componentTag();
    // Set Component Tag
    void setComponentTag(const QString& aTag);

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

    // Component Path
    QString componentPath();

    // Get QML Container
    QObject* componentContainer();
    // Set QML Container
    void setComponentContainer(QObject* aContainer);

    // Get Focused State
    bool focused();
    // Set Focused State
    void setFocused(const bool& aFocused);

    // Get Is Root
    bool isRoot();
    // Set Is Root
    void setIsRoot(const bool& aRoot);

    // Built In
    bool builtIn();
    // Set Built In
    void setBuiltIn(const bool& aBuiltIn);

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

    // Left Anchor Target
    QString anchorsLeft();
    // Right Anchor Target
    QString anchorsRight();
    // Top Anchor Target
    QString anchorsTop();
    // Bottom Anchor Target
    QString anchorsBottom();

    // Fill Target
    QString anchorsFill();
    // CenterIn Target
    QString anchorsCenterIn();
    // Horizontal Center Target
    QString horizontalCenter();
    // Vertical Center Target
    QString verticalCenter();

    // Margins
    QString anchorsMargins();

    // Left Margin
    QString anchorsLeftMargin();
    // Right Margin
    QString anchorsRightMargin();
    // Top Margin
    QString anchorsTopMargin();
    // Bottom Margin
    QString anchorsBottomMargin();

    // Horizontal Center Offset
    QString anchorsHorizontalOffset();
    // Vertical Center Offset
    QString anchorsVerticalOffset();

    // Get Layer Visible
    bool layerVisible();
    // Set Layer Visible
    void setLayerVisible(const bool& aLayerVisible);

    // Get Use Implicit Size
    bool useImplictSize();
    // Set Use Implicit Size
    void setUseImplictSize(const bool& aUseImplicitSize);

    // Get Own Property Keys
    Q_INVOKABLE QStringList componentOwnPropertyKeys();

    // Get All Inherited Property Keys
    Q_INVOKABLE QStringList inheritedPropertyKeys();

    // Get Component Hierarchy
    Q_INVOKABLE QStringList hierarchy();

    // Get Child Component ID List
    Q_INVOKABLE QStringList idList();

    // Get Component Property
    QVariant componentProperty(const QString& aName);

    // Check If Has Property
    Q_INVOKABLE bool hasProperty(const QString& aName);

    // Get Property Type & Value
    Q_INVOKABLE QString propertyTypeAndValue(const QString& aName);

    // Get Property Type
    Q_INVOKABLE QString propertyType(const QString& aName);

    // Get Property Enum Values
    Q_INVOKABLE QStringList propertyEnums(const QString& aName);

    // Get Property Value
    Q_INVOKABLE QVariant propertyValue(const QString& aName);

    // Get Child Count
    int childCount();
    // Child Depth
    int depth();

    // Get Child Info
    Q_INVOKABLE ComponentInfo* childInfo(const int& aIndex);

    // Add Child
    Q_INVOKABLE void addChild(ComponentInfo* aChild);
    // Insert Child
    Q_INVOKABLE void insertChild(const int& aIndex, ComponentInfo* aChild);
    // Take Child Info
    Q_INVOKABLE ComponentInfo* takeChild(const int& aIndex);
    // Remove Child
    Q_INVOKABLE void removeChild(ComponentInfo* aChild, const bool& aDelete = true);
    // Move Child
    Q_INVOKABLE void moveChild(const int& aIndex, const int& aTargetIndex);

    // Remove/Delete From Parent
    Q_INVOKABLE void removeFromParent();
    // Request Close
    Q_INVOKABLE void requestClose();

    // Set Object ID
    Q_INVOKABLE void setChildObjectID(QObject* aObject, const QString& aID);
    // Clear Object ID
    Q_INVOKABLE void clearObjectID(const QString& aID);
    // Get Child Object By ID
    Q_INVOKABLE QObject* getChildObject(const QString& aID);

    // Generate Live Code
    Q_INVOKABLE QString generateLiveCode(const bool& aLiveRoot = true, const bool& aGenerateChildren = true);

    // Destructor
    ~ComponentInfo();

signals:
    // Prototype Changed Signal
    void protoTypeChanged(const bool& aProtoType);
    // Component Name Changed Signal
    void componentNameChanged(const QString& aName);
    // Component Type Changed Signal
    void componentTypeChanged(const QString& aType);
    // Component Tag Changed Signal
    void componentTagChanged(const QString& aTag);
    // Component Category Changed Signal
    void componentCategoryChanged(const QString& aCategory);
    // Component Base Name Changed
    void componentBaseChanged(const QString& aBaseName);
    // Component Parent Changed Signal
    void componentParentChanged(ComponentInfo* aParent);
    // Component Path Changed Signal
    void componentPathChanged(const QString& aPath);
    // Component Container Changed Signal
    void componentContainerChanged(QObject* aContainer);
    // Info Path Changed Signal
    void infoPathChanged(const QString& aInfoPath);
    // Focused State Changed Signal
    void focusedChanged(const bool& aFocused);
    // Is Root changed Signal
    void isRootChanged(const bool& aRoot);
    // Built In Changed Signal
    void builtInChanged(const bool& aBuiltIn);

    // Child Count Changed Signal
    void childCountChanged(const int& aCount);
    // Child Depth Changed Signal
    void depthChanged(const int& aDepth);

    // Child About To Be Removed Signal
    void childAboutToBeRemoved(ComponentInfo* aChild);

    // Child Added Signal
    void childAdded(const int& aIndex);
    // Child Moved Signal
    void childMoved(const int& aIndex, const int& aTarget);
    // Child Removed Signal
    void childRemoved(const int& aIndex);

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

    // Layer Visible Changed Signal
    void layerVisibleChanged(const bool& aLayerVisible);
    // Use Implicit Size Changed Signal
    void useImplictSizeChanged(const bool& aUseImplicitSize);

    // Dirty Changed Signal
    void dirtyChanged(const bool& aDirty);

    // Imports

    // Import Added Signal
    void importAdded(const int& aIndex);
    // Import Removed Signal
    void importRemoved(const int& aIndex);

    // Anchors

    // Left Anchor Changed Signal
    void anchorsLeftChanged(const QString& aLeft);
    // Left Anchor Margin Changed Signal
    void anchorsLeftMarginChanged(const QString& aMargin);

    // Right Anchor Changed Signal
    void anchorsRightChanged(const QString& aRight);
    // Right Anchor Margin Changed Signal
    void anchorsRightMarginChanged(const QString& aMargin);

    // Top Anchor Changed Signal
    void anchorsTopChanged(const QString& aTop);
    // Top Anchor Margin Changed Signal
    void anchorsTopMarginChanged(const QString& aMargin);

    // Bottom Anchor Changed Signal
    void anchorsBottomChanged(const QString& aBottom);
    // Bottom Anchor Margin Changed Signal
    void anchorsBottomMarginChanged(const QString& aMargin);

    // Anchor Margin Changed Signal
    void anchorsMarginsChanged(const QString& aMargins);

    // Fill Anchor Changed Signal
    void anchorsFillChanged(const QString& aFill);

    // Center Anchor Changed Signal
    void anchorsCenterInChanged(const QString& aCenterIn);

    // Horizontal Center Anchor Changed Signal
    void anchorsHorizontalCenterChanged(const QString& aHorizontalCenter);
    // Vertical Center Anchor Changed Signal
    void anchorsVerticalCenterChanged(const QString& aVerticalCenter);

    // Horizontal Center Anchor Offset Changed Signal
    void anchorsHorizontalOffsetChanged(const QString& aOffset);
    // Vertical Center Anchor Offset Changed Signal
    void anchorsVerticalOffsetChanged(const QString& aOffset);

    // Component Property Changed Signal
    void componentPropertyChanged(const QString& aName, const QVariant& aValue);

    // Own Property Added Signal
    void ownPropertyAdded(const QString& aName);
    // Own Property Removed Signal
    void ownPropertyRemoved(const QString& aName);

    // Property Updated Signal
    void propertyUpdated(const QString& aName);

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
    // State Updated
    void stateUpdated(const int& aIndex);

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
    friend class DataSourcesModel;
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
                           const bool& aProtoType = true,
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
    bool load(const QString& aFilePath = "", const bool aCreateChildren = true);
    // Save
    bool save(const QString& aFilePath = "");

    // Get JSON Object
    QJsonObject toJSONObject(const bool& aChild = false);
    // Get JSON Content/Sting
    QByteArray toJSONContent();

    // Set Up From JSON Object
    void fromJSONObject(const QJsonObject& aObject, const bool aCreateChildren = true);
    // Set Up Component From JSON Content/String
    void fromJSON(const QByteArray& aContent, const bool aCreateChildren = true);

    // Set QML Source Path
    void setSourcePath(const QString& aPath);
    // Set Info Path
    void setInfoPath(const QString& aInfoPath);

    // Set Component ID
    void setComponentID(const QString& aID);
    // Set Object Name
    void setComponentObjectName(const QString& aObjectName);

    // Set Component Property - SIMPLE!!!
    void setComponentProperty(const QString& aName, const QVariant& aValue);

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

    // Set Dirty State
    void setDirty(const bool& aDirty);

    // Set Proto Type
    void setProtoType(ComponentInfo* aProtoTypw);

    // Find Root Component
    ComponentInfo* findRoot(ComponentInfo* aComponent);

    // Generate Component ID
    QString liveCodeGenerateID(const bool& aLiveRoot = true);
    // Format Imports
    QString liveCodeFormatImports(const bool& aLiveRoot = true);
    // Format Component Name
    QString liveCodeFormatName(const QString& aIndent = "");
    // Format ID
    QString liveCodeFormatID(const QString& aCID, const QString& aIndent = "");
    // Fromat Object Name
    QString liveCodeFormatObjectName(const QString& aIndent = "");
    // Format Positions
    QString liveCodeFormatPosition(const QString& aIndent = "");
    // Format Size
    QString liveCodeFormatSize(const QString& aIndent = "");
    // Format Anchors
    QString liveCodeFormatAnchors(const QString& aIndent = "");
    // Format Own Properties
    QString liveCodeFormatOwnProperties(QStringList& aOPHooks, QStringList& aEnumHooks, const QString& aID, const QStringList& aFPKeys, const QString& aIndent = "");
    // Format Properties
    QString liveCodeFormatInheritedProperties(QStringList& aPHooks, QStringList& aEnumHooks, const QString& aID, const QStringList& aFPKeys, const QString& aIndent = "");
    // Format Signals
    QString liveCodeFormatSignals(const QStringList& aOPKeys, const QStringList& pKeys, const QString& aIndent = "");
    // Format Slots
    QString liveCodeFormatSlots(const QString& aIndent = "");
    // Format Functions
    QString liveCodeFormatFunctions(const QStringList& aOPHooks, const QStringList& aPHooks, const QStringList& aEnumHooks, const QString& aIndent = "");
    // Format Children
    QString liveCodeFormatChildren(const bool& aGenerateChildren, const QString& aIndent = "");
    // Format States
    QString liveCodeFormatStates(const QString& aIndent = "");
    // Format Transitions
    QString liveCodeFormatTransitions(const QString& aIndent = "");
    // Generate Enum Value Live Code Cases
    QStringList liveCodeGenerateEnumValueCases(const QStringList& aEnumValues);

protected slots:
    // Base Components Dir Changed Slot
    void baseComponentsDirChanged(const QString& aBaseComponentsDir);
    // Components Dir Changed Slot
    void componentsDirChanged(const QString& aComponentsDir);
    // Views Dir Changed Slot
    void viewsDirChanged(const QString& aViewsDir);
    // Data Sources Dir Changed Slot
    void dataSourcesDirChanged(const QString& aDataSourcesDir);

protected: // Data
    friend class ComponentImportsModel;
    friend class ComponentAnchorsModel;
    friend class ComponentOwnPropertiesModel;
    friend class ComponentPropertiesModel;
    friend class ComponentSignalsModel;
    friend class ComponentSlotsModel;
    friend class ComponentStatesModel;
    friend class ComponentTransitionsModel;
    friend class ComponentFunctionsModel;

    // Project Model
    ProjectModel*           mProject;

    // ProtoType
    bool                    mIsProtoType;
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
    // Tag
    QString                 mTag;
    // Category
    QString                 mCategory;
    // Base Component Name
    QString                 mBaseName;

    // Use Implicit Size
    bool                    mImplicitSize;

    // Focused State
    bool                    mFocused;
    // Layer Visible
    bool                    mLayerVisible;
    // Is Root
    bool                    mIsRoot;

    // Groupped
    bool                    mGroupped;

    // QML Container Object
    QObject*                mContainer;

    // Base Component Info
    ComponentInfo*          mBase;
    // Parent Component Info
    ComponentInfo*          mParent;
    // Prototype Component
    ComponentInfo*          mProtoType;

    // Children
    QList<ComponentInfo*>   mChildren;

    // Component Id Map
    QMap<QString, QObject*> mIDMap;

    // Own Properties
    QJsonObject             mOwnProperties;
    // Anchors
    QJsonObject             mAnchors;
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
