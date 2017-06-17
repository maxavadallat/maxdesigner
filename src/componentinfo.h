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
class LiveWindow;

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
    Q_PROPERTY(QObject* componentHandler READ componentHandler WRITE setComponentHandler NOTIFY componentContainerChanged)
    // Prototype
    Q_PROPERTY(bool protoType READ protoType NOTIFY protoTypeChanged)
    // Focused
    Q_PROPERTY(bool focused READ focused NOTIFY focusedChanged)
    // Closing
    Q_PROPERTY(bool closing READ closing WRITE setClosing NOTIFY closingChanged)
    // Is Root
    Q_PROPERTY(bool isRoot READ isRoot NOTIFY isRootChanged)
    // Built In
    Q_PROPERTY(bool builtIn READ builtIn NOTIFY builtInChanged)
    // Children Loaded
    Q_PROPERTY(bool childrenLoaded READ childrenLoaded NOTIFY childrenLoadedChanged)
    // Animations Loaded
    Q_PROPERTY(bool animationsLoaded READ animationsLoaded NOTIFY animationsLoadedChanged)
    // Behaviors Loaded
    Q_PROPERTY(bool behaviorsLoaded READ behaviorsLoaded NOTIFY behaviorsLoadedChanged)
    // Child Count
    Q_PROPERTY(int childCount READ childCount NOTIFY childCountChanged)
    // Animation Count
    Q_PROPERTY(int animsCount READ animsCount NOTIFY animsCountChanged)
    // Behaviors Count
    Q_PROPERTY(int behaviorsCount READ behaviorsCount NOTIFY behaviorsCountChanged)
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

    Q_PROPERTY(bool useIPosX READ useIPosX WRITE setUseIPosX NOTIFY useIPosXChanged)
    Q_PROPERTY(bool useIPosY READ useIPosY WRITE setUseIPosY NOTIFY useIPosYChanged)
    Q_PROPERTY(bool useIWidth READ useIWidth WRITE setUseIWidth NOTIFY useIWidthChanged)
    Q_PROPERTY(bool useIHeight READ useIHeight WRITE setUseIHeight NOTIFY useIHeightChanged)

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

    // Layer/Component Visible
    Q_PROPERTY(bool layerVisible READ layerVisible WRITE setLayerVisible NOTIFY layerVisibleChanged)

    // Component State
    Q_PROPERTY(QString componentState READ componentState WRITE setComponentState NOTIFY componentStateChanged)

    // Component Dirty
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
    QObject* componentHandler();
    // Set QML Component Handler
    void setComponentHandler(QObject* aContainer);

    // Get Focused State
    bool focused();
    // Set Focused State
    void setFocused(const bool& aFocused);

    // Get Closing State
    bool closing();
    // Set Closing State
    void setClosing(const bool& aClosing);

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
    // Set Pos X
    Q_INVOKABLE void setPosX(const QString& aPosX);

    // Get Pos Y
    QString posY();
    // Set Pos Y
    Q_INVOKABLE void setPosY(const QString& aPosY);

    // Get Pos Z
    QString posZ();

    // Get Width
    QString width();
    // Set Width
    Q_INVOKABLE void setWidth(const QString& aWidth);

    // Get Height
    QString height();
    // Set Height
    Q_INVOKABLE void setHeight(const QString& aHeight);

    // Get Use Implicit Pos X
    bool useIPosX();
    // Set Use Implicit Pos X
    void setUseIPosX(const bool& aUseIPosX);

    // Get Use Implicit Pos Y
    bool useIPosY();
    // Set Use Implicit Pos Y
    void setUseIPosY(const bool& aUseIPosY);

    // Get Use Implicit Width
    bool useIWidth();
    // Set Use Implicit Width
    void setUseIWidth(const bool& aUseIWidth);

    // Get Use Implicit Height
    bool useIHeight();
    // Set Use Implicit Height
    void setUseIHeight(const bool& aUseIHeight);

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

    // Reset Anchors
    Q_INVOKABLE void resetAnchors();

    // Get Layer Visible
    bool layerVisible();
    // Set Layer Visible
    void setLayerVisible(const bool& aLayerVisible);

    // Get Component State
    QString componentState();
    // Get Component State
    void setComponentState(const QString& aState);

    // Get Own Property Keys
    Q_INVOKABLE QStringList componentOwnPropertyKeys();

    // Get All Inherited Property Keys
    Q_INVOKABLE QStringList inheritedPropertyKeys();

    // Get Proto Type Keys
    Q_INVOKABLE QStringList protoTypeKeys();

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
    Q_INVOKABLE QVariant propertyValue(const QString& aName, const bool& aRaw = false);

    // Get Property Is Formula or Binding for Value
    Q_INVOKABLE bool propertyIsFormula(const QString& aName);

    // Get Children Loaded
    bool childrenLoaded();
    // Animations Loaded
    bool animationsLoaded();
    // Behaviors Loaded
    bool behaviorsLoaded();

    // Load Children
    Q_INVOKABLE void loadChildren();
    // Load Animations
    Q_INVOKABLE void loadAnimations();
    // Load BEhaviors
    Q_INVOKABLE void loadBehaviors();

    // Get Child Count
    int childCount();
    // Animations Count
    int animsCount();
    // Behaviors Count
    int behaviorsCount();
    // Child Depth
    int depth();

    // Get Child Info
    Q_INVOKABLE ComponentInfo* childInfo(const int& aIndex);
    // Get Child Info By Child Index Map
    Q_INVOKABLE ComponentInfo* childInfo(const QString& aMap);
    // Get Anim Info
    Q_INVOKABLE ComponentInfo* animInfo(const int& aIndex);

    // Add Child
    Q_INVOKABLE void addChild(ComponentInfo* aChild, const bool& aLoadChildren = false);
    // Insert Child
    Q_INVOKABLE void insertChild(const int& aIndex, ComponentInfo* aChild, const bool& aMove);
    // Take Child Component
    Q_INVOKABLE ComponentInfo* takeChild(const int& aIndex, const bool& aMove);
    // Take Animation
    Q_INVOKABLE ComponentInfo* takeAnimation(const int& aIndex, const bool& aMove);
    // Take Child Component
    Q_INVOKABLE int takeChild(ComponentInfo* aChildInfo);
    // Take Animation Component
    Q_INVOKABLE int takeAnimation(ComponentInfo* aChildInfo);
    // Remove Child
    Q_INVOKABLE void removeChild(ComponentInfo* aChild, const bool& aDelete = true);
    // Move Child
    Q_INVOKABLE void moveChild(const int& aIndex, const int& aTargetIndex);
    // Move Child
    Q_INVOKABLE void moveChild(ComponentInfo* aChildInfo, const int& aIndex, ComponentInfo* aTargetChildInfo, const int& aTargetIndex);

    // Move Animation
    Q_INVOKABLE void moveAnimation(const int& aIndex, const int& aTargetIndex);
    // Move Animation
    Q_INVOKABLE void moveAnimation(ComponentInfo* aChildInfo, const int& aIndex, ComponentInfo* aTargetChildInfo, const int& aTargetIndex);

    // Remove/Delete From Parent
    Q_INVOKABLE void removeFromParent();
    // Take From Parent
    Q_INVOKABLE int takeFromParent();
    // Request Close
    Q_INVOKABLE void requestClose();

    // Set Object ID
    Q_INVOKABLE void setChildObjectID(QObject* aObject, const QString& aID);
    // Clear Object ID
    Q_INVOKABLE void clearObjectID(const QString& aID);
    // Get Child Object By ID
    Q_INVOKABLE QObject* getChildObject(const QString& aID);
    // Generate Live Code
    Q_INVOKABLE QString generateLiveCode(const bool& aLiveRoot = true, const bool& aGenerateChildren = true, const QString& aIndent = "", const bool& aComponentCode = false);
    // Generate Component Code
    Q_INVOKABLE QString generateComponentCode(const bool& aGenerateChildren = true);
    // Generate Data Source Live Code
    Q_INVOKABLE QString generateDataSourceLiveCode();

    // Get Layout Base
    Q_INVOKABLE QString layoutBase();

    // Get Global Child Index Map
    Q_INVOKABLE QString getGlobalChildIndexMap();

    // Find Root Component
    Q_INVOKABLE ComponentInfo* findRoot(ComponentInfo* aComponent);

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
    // Closing State Changed Signal
    void closingChanged(const bool& aClosing);
    // Is Root changed Signal
    void isRootChanged(const bool& aRoot);
    // Built In Changed Signal
    void builtInChanged(const bool& aBuiltIn);

    // Children Loaded Changed Signal
    void childrenLoadedChanged(const bool& aChildrenLoaded);
    // Animations Loaded Changed
    void animationsLoadedChanged(const bool& aAnimsLoaded);
    // Behaviorss Loaded Changed
    void behaviorsLoadedChanged(const bool& aAnimsLoaded);

    // Child Count Changed Signal
    void childCountChanged(const int& aCount);
    // Animations Count Changed
    void animsCountChanged(const int& aCount);
    // Behaviors Count Changed
    void behaviorsCountChanged(const int& aCount);

    // Child Depth Changed Signal
    void depthChanged(const int& aDepth);

    // Child About To Be Removed Signal
    void childAboutToBeRemoved(ComponentInfo* aChild);
    // Animation Is About To Be Removed
    void animationAboutToBeRemoved(ComponentInfo* aChild);
    // Behavior
    void behaviorAboutToBeRemoved(ComponentInfo* aChild);

    // Child Added Signal
    void childAdded(const int& aIndex);
    // Child Moved Signal
    void childMoved(ComponentInfo* aParentComponent, const int& aIndex, ComponentInfo* aTargetComponent, const int& aTargetIndex);
    // Child Removed Signal
    void childRemoved(const int& aIndex);

    // Animation Added Signal
    void animationAdded(const int& aIndex);
    // Animation Moved Signal
    void animationMoved(ComponentInfo* aParentComponent, const int& aIndex, ComponentInfo* aTargetComponent, const int& aTargetIndex);
    // Animations Removed Signal
    void animationRemoved(const int& aIndex);

    // Behavior Added Signal
    void behaviorAdded(const int& aIndex);
    // Behavior Moved Signal
    void behaviorMoved(ComponentInfo* aParentComponent, const int& aIndex, ComponentInfo* aTargetComponent, const int& aTargetIndex);
    // Behaviors Removed Signal
    void behaviorRemoved(const int& aIndex);

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

    // Use Implicit Pos X Changed Signal
    void useIPosXChanged(const bool& aUseIPosX);
    // Use Implicit Pos Y Changed Signal
    void useIPosYChanged(const bool& aUseIPosY);
    // Use Implicit Width Changed Signal
    void useIWidthChanged(const bool& aUseIWidth);
    // Use Implicit Height Changed Signal
    void useIHeightChanged(const bool& aUseIHeight);

    // Layer Visible Changed Signal
    void layerVisibleChanged(const bool& aLayerVisible);
    // Use Implicit Size Changed Signal
    void useImplictSizeChanged(const bool& aUseImplicitSize);

    // Component State Changed Signal
    void componentStateChanged(const QString& aState);

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

    // Components ID Map Has Changed
    void componentIDMapChanged();

    // Need Refresh Live Code Signal
    void needRefresh();

    // ...

protected:
    friend class OpenFilesModel;
    friend class ProjectModel;
    friend class BaseComponentsModel;
    friend class ComponentsModel;
    friend class ViewsModel;
    friend class DataSourcesModel;
    friend class MainWindow;
    friend class LiveWindow;
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
    // Clear ID Map
    void clearIDMap();
    // Clear Children
    void clearChildren();
    // Clear Animations
    void clearAnimations();
    // Clear Behaviors
    void clearBehaviors();

    // Init Info Path
    bool initInfoPath();

    // Load
    bool load(const QString& aFilePath = "", const bool aCreateChildren = true);
    // Save
    bool save(const QString& aFilePath = "");

    // Save Children
    void saveChildren();
    // Save Animations
    void saveAnimations();
    // Save Behaviors
    void saveBehaviors();

    // Set Children Loaded
    void setChildrenLoaded(const bool& aChildrenLoaded);
    // Set Animations Loaded
    void setAnimationsLoaded(const bool& aAnimationsLoaded);
    // Set Behaviors Loaded
    void setBehaviorsLoaded(const bool& aBehaviorsLoaded);

    // Save Live data Source
    bool saveLiveDataSource();

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

    // Add Own Property
    bool addComponentProperty(const QString& aName,
                              const ComponentInfo::EPropertyType& aType = ComponentInfo::EPropertyType::EPTString,
                              const QString& aMin = "",
                              const QString& aMax = "",
                              const QString& aEnumValues = "",
                              const QVariant& aDefaultValue = QVariant(),
                              const bool& aReadOnly = false,
                              const bool& aDefaultAlias = false);

    // Remove Property
    void removeComponentProperty(const QString& aName);

    // Set Component Property - SIMPLE!!!
    bool setComponentProperty(const QString& aName, const QVariant& aValue);

    // Set Pos Z
    void setPosZ(const QString& aPosZ);

    // Set Dirty State
    void setDirty(const bool& aDirty);

    // Set ProtoType Component
    void setProtoType(ComponentInfo* aProtoType);
    // Set Base Component
    void setBaseComponent(ComponentInfo* aBase);

    // Get Index
    int getChildIndex();

    // Generate Component ID
    QString liveCodeGenerateID(const bool& aLiveRoot = true);
    // Format Imports
    QString liveCodeFormatImports();
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
    QString liveCodeFormatOwnProperties(QStringList& aOPHooks,
                                        QStringList& aEnumHooks,
                                        QStringList& aPCHookList,
                                        const QString& aID,
                                        const QStringList& aFPKeys,
                                        const QString& aIndent = "",
                                        const bool& aComponentCode = false);
    // Format Properties
    QString liveCodeFormatInheritedProperties(QStringList& aPHooks,
                                              QStringList& aEnumHooks,
                                              QStringList& aPCHookList,
                                              const QString& aID,
                                              const QStringList& aFPKeys,
                                              const QString& aIndent = "",
                                              const bool& aComponentCode = false);
    // Format Signals
    QString liveCodeFormatSignals(const QString& aIndent = "");
    // Format Slots
    QString liveCodeFormatSlots(const QStringList& aPCHookList = QStringList(),
                                const QString& aIndent = "",
                                const bool& aComponentCode = false);
    // Format Hooks
    QString liveCodeFormatHooks(const QStringList& aOPHooks,
                                const QStringList& aPHooks,
                                const QStringList& aEnumHooks,
                                const QString& aIndent = "");
    // Format Functions
    QString liveCodeFormatFunctions(const QString& aIndent = "");
    // Format Children
    QString liveCodeFormatChildren(const QString& aIndent = "", const bool& aComponentCode = false);
    // Format Animations
    QString liveCodeFormatAnimations(const QString& aIndent = "", const bool& aComponentCode = false);
    // Format Behaviors
    QString liveCodeFormatBehaviors(const QString& aIndent = "", const bool& aComponentCode = false);
    // Format States
    QString liveCodeFormatState(const int& aIndex, const QString& aIndent = "");
    // Format States
    QString liveCodeFormatStates(const QString& aIndent = "");
    // Format Transition
    QString liveCodeFormatTransition(const int& aIndex, const QString& aIndent = "");
    // Format Transitions
    QString liveCodeFormatTransitions(const QString& aIndent = "");
    // Generate Enum Value Live Code Cases
    QStringList liveCodeGenerateEnumValueCases(const QStringList& aEnumValues, const QString& aIndent = "");

    // Inc Reference Count
    void incRefCount();
    // Release Ref Count From Child
    void releaseRef();

protected slots:
    // Base Components Dir Changed Slot
    void baseComponentsDirChanged(const QString& aBaseComponentsDir);
    // Components Dir Changed Slot
    void componentsDirChanged(const QString& aComponentsDir);
    // Views Dir Changed Slot
    void viewsDirChanged(const QString& aViewsDir);
    // Data Sources Dir Changed Slot
    void dataSourcesDirChanged(const QString& aDataSourcesDir);
    // Handle Base Property Changes
    void handleBasePropertyChanges(const QString& aName, const QVariant& aValue);

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
    // Locked For Editing
    bool                    mLocked;

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

    // Use Implicit Pos X
    bool                    mImplicitPosX;
    // Use Implicit Pos Y
    bool                    mImplicitPosY;
    // Use Implicit Width
    bool                    mImplicitWidth;
    // Use Implicit Height
    bool                    mImplicitHeight;

    // Focused State
    bool                    mFocused;
    // Closing State
    bool                    mClosing;
    // Layer Visible
    bool                    mLayerVisible;
    // Is Root
    bool                    mIsRoot;

    // Groupped
    bool                    mGroupped;

    // Children Loaded
    bool                    mChildrenLoaded;
    // Animations Loaded
    bool                    mAnimationsLoaded;
    // Behaviors Loaded
    bool                    mBehaviorsLoaded;

    // Reference Count For Children
    int                     mRefCount;

    // QML Handler Object
    QObject*                mComponentHandler;

    // Base Component Info
    ComponentInfo*          mBase;
    // Parent Component Info
    ComponentInfo*          mParent;
    // Prototype Component
    ComponentInfo*          mProtoType;

    // Children
    QList<ComponentInfo*>   mChildComponents;
    // Animations
    QList<ComponentInfo*>   mAnimationComponents;
    // Behaviors
    QList<ComponentInfo*>   mBehaviorComponents;

    // Component Id Map
    QMap<QString, QObject*> mIDMap;

    // Imports
    QJsonArray              mImports;
    // Anchors
    QJsonObject             mAnchors;
    // Own Properties
    QJsonObject             mOwnProperties;
    // Properties
    QJsonObject             mProperties;
    // Behaviors
    QJsonArray              mBehaviors;
    // Signals
    QJsonArray              mSignals;
    // Slots
    QJsonArray              mSlots;
    // Functions
    QJsonArray              mFunctions;
    // Children
    QJsonArray              mChildren;
    // Animations
    QJsonArray              mAnimations;
    // States
    QJsonArray              mStates;
    // Transitions
    QJsonArray              mTransitions;
};

#endif // COMPONENTINFO_H
