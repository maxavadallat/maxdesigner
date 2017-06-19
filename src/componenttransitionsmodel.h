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

//==============================================================================
// Component Transitions Model
//==============================================================================
class ComponentTransitionsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)
    Q_PROPERTY(ComponentTransition* currentTransition READ currentTransition WRITE setCurrentTransition NOTIFY currentTransitionChanged)
//    Q_PROPERTY(int transitionsCount READ transitionsCount WRITE setTransitionsCount NOTIFY transitionsCountChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Current Transition
    ComponentTransition* currentTransition();
    // Set Current Transition
    void setCurrentTransition(ComponentTransition* aTransition);

//    // Get TRansitions Count
//    int transitionsCount();

    // Select Transition
    Q_INVOKABLE void selectTransition(const int& aIndex);

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

    // Add Transition
    void addTransition(const QString& aFrom, const QString& aTo);

    // Destructor
    ~ComponentTransitionsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);
    // Current Transition Changed
    void currentTransitionChanged(ComponentTransition* aTransition);
//    // Transitions Count Changed Signal
//    void transitionsCountChanged(const int& aCount);

protected:
    friend class ComponentInfo;
    friend class PropertiesController;

    // Constructor
    explicit ComponentTransitionsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

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

    // Set Dirty State
    void setDirty(const bool& aDirty);

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
    friend class ComponentTransitionNode;

    // Component Info
    ComponentInfo*                  mComponent;
    // Transitions List
    QList<ComponentTransition*>     mTransitions;
    // New Transition
    ComponentTransition*            mNewTransition;
    // Current Transition
    ComponentTransition*            mCurrentTransition;
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
    Q_INVOKABLE ComponentInfo* createNewNode(const QString& aComponentName);
    // Discard New Node
    Q_INVOKABLE void discardNewNode();
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
    // Remove Node
    Q_INVOKABLE void removeNode(const int& aIndex);

    // Destructor
    ~ComponentTransition();

protected:
    friend class ComponentTransitionsModel;

    // Constructor
    explicit ComponentTransition(const QString& aFromState, const QString& aToState, ComponentTransitionsModel* aModel, QObject* aParent = NULL);

    // Clear
    void clear();

    // To JSON Object
    QJsonObject toJSONObject();

    // Read Nodes
    void readNodes(const QJsonArray& aNodes);

signals:
    // From State Changed Signal
    void fromStateChanged(const QString& aFromState);
    // To State Changed Signal
    void toStateChanged(const QString& aToState);
    // Node Count Changed Signal
    void nodeCountChanged(const int& aCount);

protected: // Data
    friend class ComponentTransitionsModel;

    // Transitions Model
    ComponentTransitionsModel*      mModel;
    // From State
    QString                         mFromState;
    // To State
    QString                         mToState;
    // Transition Nodes
    QList<ComponentInfo*>           mNodes;
    // New Transition Node
    ComponentInfo*                  mNewNode;
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

    // get Animation Component Name By Index
    Q_INVOKABLE QString getNameByIndex(const int& aIndex);

    // Destructor
    ~AnimationComponentsModel();

signals:
    // Project Model Changed Signal
    void currentProjectChanged(ProjectModel* aProjectModel);
    // Item Added
    void itemAdded(const int& aIndex);
    // Item Removed
    void itemRemoved(const int& aIndex);

protected:
    friend class MainWindow;
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
