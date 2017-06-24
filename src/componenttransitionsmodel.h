#ifndef COMPONENTTRANSITIONSMODEL_H
#define COMPONENTTRANSITIONSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>

class ComponentInfo;
class ComponentTransition;
class PropertiesController;
class ProjectModel;
class BaseComponentsModel;
class ComponentsModel;
class MainWindow;
class AnimationComponentsModel;

//==============================================================================
// Component Transitions Model
//==============================================================================
class ComponentTransitionsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)
    Q_PROPERTY(ComponentTransition* currentTransition READ currentTransition WRITE setCurrentTransition NOTIFY currentTransitionChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Current Transition
    ComponentTransition* currentTransition();
    // Set Current Transition
    void setCurrentTransition(ComponentTransition* aTransition);

    // Select Transition
    Q_INVOKABLE ComponentTransition* selectTransition(const int& aIndex);

    // Create New Transition
    Q_INVOKABLE ComponentTransition* createNewTransition();
    // Discard New Transition
    Q_INVOKABLE void discardNewTransition();

    // Append Transition
    Q_INVOKABLE void appendTransition(ComponentTransition* aTransition);

    // Get Transition
    Q_INVOKABLE ComponentTransition* getTransition(const int& aIndex);
    // Move Transition
    Q_INVOKABLE void moveTransition(const int& aIndex, const int& aTarget);
    // Remove Transition
    Q_INVOKABLE void removeTransition(const int& aIndex);

    // Update Selected Transition
    Q_INVOKABLE void updateSelectedTransition();

    // Validate Transition
    Q_INVOKABLE bool validateTransition(const QString& aFromState, const QString& aToState);

    // Add Transition
    void addTransition(const QString& aFrom, const QString& aTo);

    // Destructor
    ~ComponentTransitionsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);
    // Current Transition Changed
    void currentTransitionChanged(ComponentTransition* aTransition);

protected:
    friend class ComponentInfo;
    friend class PropertiesController;

    // Constructor
    explicit ComponentTransitionsModel(ComponentInfo* aComponent, ProjectModel* aProjectModel, AnimationComponentsModel* aAnimComponents, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // To JSON Array
    QJsonArray toJSONArray();

    // Load Component Transitions
    void loadComponentTransitions();
    // Save Component Transitions
    void saveComponentTransitions();

    // Reset Transitions Dirty State
    void resetTransitionsDirtyState();

    // Set Dirty State
    void setDirty(const bool& aDirty);

protected slots:
    // Component Transition Dirty State Changed
    void componentTransitionDirtyChanged(const bool& aDirty);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

public:
    // Transitions Model Roles
    enum TMRoles {
        ETMRFromState   =   Qt::UserRole + 1,
        ETMRToState,
        ETMRNodesCount
    };

protected: // Data
    friend class ComponentTransition;

    // Project Model
    ProjectModel*                   mProject;
    // Animation Components Model
    AnimationComponentsModel*       mAnimComponents;
    // Component Info
    ComponentInfo*                  mComponent;
    // Transitions List
    QList<ComponentTransition*>     mTransitions;
    // New Transition
    ComponentTransition*            mNewTransition;
    // Current Transition
    ComponentTransition*            mCurrentTransition;
    // Selected Transition Index
    int                             mSelectedIndex;
    // Dirty State
    bool                            mDirty;
};









//==============================================================================
// Component Transition Class
//==============================================================================
class ComponentTransition : public QObject
{
    Q_OBJECT

    // From State
    Q_PROPERTY(QString fromState READ fromState WRITE setFromState NOTIFY fromStateChanged)
    // To State
    Q_PROPERTY(QString toState READ toState WRITE setToState NOTIFY toStateChanged)
    // Nodes Count
    Q_PROPERTY(int nodesCount READ nodesCount NOTIFY nodeCountChanged)

public:
    // From JSON Object
    static ComponentTransition* fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject);

    // Get From State
    QString fromState();
    // Set From State
    void setFromState(const QString& aFromState);

    // Get To State
    QString toState();
    // Set To State
    void setToState(const QString& aToState);

    // Get Node Count
    Q_INVOKABLE int nodesCount();

    // Create New Node
    Q_INVOKABLE ComponentInfo* createNewNode(const QString& aComponentName, ComponentInfo* aParentNode = NULL);
    // Discard New Node
    Q_INVOKABLE void discardNewNode();

    // Select Transition Node
    Q_INVOKABLE ComponentInfo* selectNode(const int& aIndex);

    // Get Node By Index
    Q_INVOKABLE ComponentInfo* getNode(const int& aIndex);

    // Append Node
    Q_INVOKABLE void appendNode(ComponentInfo* aNode, ComponentInfo* aParentNode = NULL);
    // Insert Node
    Q_INVOKABLE void insertNode(const int& aIndex, ComponentInfo* aNode, ComponentInfo* aParentNode = NULL);
    // Move Node
    Q_INVOKABLE void moveNode(const int& aIndex, const int& aTargetIndex);
    // Move Node
    Q_INVOKABLE void moveNode(ComponentInfo* aParentNode, const int& aIndex, ComponentInfo* aTargetNode, const int& aTargetIndex);
    // Remove Node By Index
    Q_INVOKABLE void removeNode(ComponentInfo* aParentNode, const int& aIndex);
    // Remove Node By Component Info
    Q_INVOKABLE void removeNode(ComponentInfo* aNode);

    // Clear Transition
    Q_INVOKABLE void clearTransition();

    // Destructor
    ~ComponentTransition();

signals:
    // From State Changed Signal
    void fromStateChanged(const QString& aFromState);
    // To State Changed Signal
    void toStateChanged(const QString& aToState);
    // Node Count Changed Signal
    void nodeCountChanged(const int& aCount);
    // Dirty State Changed Signal
    void dirtyChanged(const bool& aDirty);

    // Node Added
    void nodeAdded(ComponentInfo* aParentNode, const int& aIndex);
    // Node Moved
    void nodeMoved(ComponentInfo* aParentNode, const int& aIndex, ComponentInfo* aTargetNode, const int& aTargetIndex);
    // Node Removed
    void nodeRemoved(ComponentInfo* aParentNode, const int& aIndex);

protected:
    friend class ComponentInfo;
    friend class ComponentTransitionsModel;

    // Constructor
    explicit ComponentTransition(const QString& aFromState, const QString& aToState, ComponentTransitionsModel* aModel, QObject* aParent = NULL);

    // Clear
    void clear();

    // Set Dirty State
    void setDirty(const bool& aDirty);

    // To JSON Object
    QJsonObject toJSONObject();

    // Read Nodes
    void readNodes(const QJsonArray& aNodes);

protected: // Data
    friend class ComponentTransitionsModel;

    // Transitions Model
    ComponentTransitionsModel*      mModel;
    // Project Model
    ProjectModel*                   mProject;
    // From State
    QString                         mFromState;
    // To State
    QString                         mToState;
    // Transition Nodes
    QList<ComponentInfo*>           mNodes;
    // New Transition Node
    ComponentInfo*                  mNewNode;
    // Current Transition Node
    ComponentInfo*                  mCurrentNode;
    // Dirty State
    bool                            mDirty;
};












//==============================================================================
// Animation Components List Model
//==============================================================================
class AnimationComponentsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* currentProject READ currentProject WRITE setCurrentProject NOTIFY currentProjectChanged)

public:

    // Get Current Project
    ProjectModel* currentProject();
    // Set Current Project
    void setCurrentProject(ProjectModel* aProjectModel);

    // Get Animation Component Name By Index
    Q_INVOKABLE QString getNameByIndex(const int& aIndex);

    // Clone Animation Component By Index
    Q_INVOKABLE ComponentInfo* cloneAnimation(const int& aIndex);
    // Clone Animation Component By Name
    Q_INVOKABLE ComponentInfo* cloneAnimation(const QString& aName);

    // Destructor
    ~AnimationComponentsModel();

signals:
    // Project Model Changed Signal
    void currentProjectChanged(ProjectModel* aProjectModel);
    // Item Added
    void itemAdded(const int& aIndex);
    // Item Removed
    void itemRemoved(const int& aIndex);
    // Animation Components Cleared
    void animationComponentsCleared();

protected:
    friend class PropertiesController;
    // Constructor
    explicit AnimationComponentsModel(ProjectModel* aProject, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

    // Connect Model Signals
    void connectModelSignals();
    // Disconnect Model Signals
    void disconnectModelSignals();

    // Collect Animation Components
    void collectAnimationComponents();

protected slots:
    // Component Created Slot
    void componentCreated(ComponentInfo* aComponent, const int& aWidth, const int& aHeight);
    // Component Added Slot
    void componentAdded(ComponentInfo* aComponent);
    // Component About To Be Removed Slot
    void componentAboutToBeRemoved(ComponentInfo* aComponent);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

public:
    // Transitions Model Roles
    enum ACMRoles {
        EACMRComponentName   =   Qt::UserRole + 1,
    };

protected:
    // Project Model
    ProjectModel*           mProject;
    // Base Components Model
    BaseComponentsModel*    mBaseComponents;
    // Components Model
    ComponentsModel*        mComponents;
    // Animation Components List
    QList<ComponentInfo*>   mAnimationComponents;
};


#endif // COMPONENTTRANSITIONSMODEL_H
