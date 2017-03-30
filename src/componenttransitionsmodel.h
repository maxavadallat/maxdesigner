#ifndef COMPONENTTRANSITIONSMODEL_H
#define COMPONENTTRANSITIONSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>

class ComponentInfo;
class ComponentTransition;
class ComponentPropertyAction;
class ComponentPropertyAnimation;
class ComponentTransitionNode;

class PropertiesController;

//==============================================================================
// Component Transitions Node Type
//==============================================================================
enum ETransitionType {
    ETTUnknown                  = 0,
    ETTParallelAnimation,
    ETTSequentialAnimation,
    ETTPauseAnimation,
    ETTPropertyAction,
    ETTScripAction,
    ETTPropertyAnimation
};

//==============================================================================
// Component Transitions Model
//==============================================================================
class ComponentTransitionsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)
    Q_PROPERTY(ComponentTransition* currentTransition READ currentTransition WRITE setCurrentTransition NOTIFY currentTransitionChanged)
    Q_PROPERTY(ComponentTransitionNode* currentTransitionNode READ currentTransitionNode WRITE setCurrentTransitionNode NOTIFY currentTransitionNodeChanged)

public:
    // Add Transition
    void addTransition(const QString& aFrom, const QString& aTo);
    // Set Transition
    void setTransition(const int& aIndex, const QString& aFrom, const QString& aTo);
    // Remove Transition
    void removeTransition(const int& aIndex);

    // Add Sequential Animation Root Item
    void addSequentialAnimationRoot(const int& aIndex);
    // Add Parallel Animation Root Item
    void addParallelAnimationRoot(const int& aIndex);

    // Remove Transtion Root Item
    void removeTransitionRoot(const int& aIndex);

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Current Transition
    ComponentTransition* currentTransition();
    // Set Current Transition
    void setCurrentTransition(ComponentTransition* aTransition);

    // Get Current Node
    ComponentTransitionNode* currentTransitionNode();
    // Set Current Node
    void setCurrentTransitionNode(ComponentTransitionNode* aNode);

    // To JSON Array
    QJsonArray toJSONArray();

    // Get Transition
    Q_INVOKABLE ComponentTransition* getTransition(const int& aIndex);

    // Destructor
    ~ComponentTransitionsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);
    // Current Transition Changed
    void currentTransitionChanged(ComponentTransition* aTransition);
    // Current Transition Node Changed
    void currentTransitionNodeChanged(ComponentTransitionNode* aNode);

protected:
    friend class ComponentInfo;
    friend class PropertiesController;

    // Constructor
    explicit ComponentTransitionsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();
    // Load Component Transitions
    void loadComponentTransitions();
    // Save Component Transitions
    void saveComponentTransitions();

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
        ETMRToState
    };

protected: // Data
    friend class ComponentTransitionNode;

    // Component Info
    ComponentInfo*                  mComponent;
    // Transitions List
    QList<ComponentTransition*>     mTransitions;
    // Current Transition
    ComponentTransition*            mCurrentTransition;
    // Current Transition Node
    ComponentTransitionNode*        mCurrentTransitionNode;
    // Transition Node Type Map
    QMap<QString, ETransitionType>  mNodeTypeMap;
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
    // Current Node
    Q_PROPERTY(ComponentTransitionNode* currentNode READ currentNode WRITE setCurrentNode NOTIFY currentNodeChanged)

public:
    // From JSON Object
    static ComponentTransition* fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject);
    // Constructor
    explicit ComponentTransition(const QString& aFromState, const QString& aToState, QObject* aParent = NULL);

    // Get From State
    QString fromState();
    // Set From State
    void setFromState(const QString& aFromState);

    // Get To State
    QString toState();
    // Set To State
    void setToState(const QString& aToState);

    // Get Current Node
    ComponentTransitionNode* currentNode();
    // Set Current Node
    void setCurrentNode(ComponentTransitionNode* aNode);

    // To JSON Object
    QJsonObject toJSONObject();

    // Destructor
    ~ComponentTransition();

protected:
    friend class ComponentTransitionsModel;

    // Clear
    void clear();

signals:
    // From State Changed Signal
    void fromStateChanged(const QString& aFromState);
    // To State Changed Signal
    void toStateChanged(const QString& aToState);
    // Current Node changed Signal
    void currentNodeChanged(ComponentTransitionNode* aNode);

protected: // Data
    // Transition Items
    ComponentTransitionNode*    mTransitionRoot;
    // Current Node
    ComponentTransitionNode*    mCurrentNode;

    // From State
    QString                     mFromState;
    // To State
    QString                     mToState;
};







//==============================================================================
// Component Transitin Item Node Base
//==============================================================================
class ComponentTransitionNode  : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    // From JSON Object
    static ComponentTransitionNode* fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject);
    // Constructor
    explicit ComponentTransitionNode(const ETransitionType& aType, QObject* aParent = NULL);

    // Get Count
    int count();

    // Get Child
    ComponentTransitionNode* child(const int& aIndex);

    // Append Child
    void appendChild(ComponentTransitionNode* aChild);
    // Insert Child
    void insertChild(const int& aIndex, ComponentTransitionNode* aChild);
    // Remove Child
    void removeChild(const int& aIndex);

    // Clear
    virtual void clear();
    // To JSON Object
    virtual QJsonObject toJSONObject();

    // Destructor
    ~ComponentTransitionNode();

signals:
    // Count Changed Signal
    void countChanged(const int& aCount);

protected: // Data
    // Transition Type
    ETransitionType                     mType;
    // Children
    QList<ComponentTransitionNode*>     mChildren;
};






//==============================================================================
// Component Parallel Animation
//==============================================================================
class ComponentParallelAnimation : public ComponentTransitionNode
{
    Q_OBJECT

public:
    // From JSON Object
    static ComponentParallelAnimation* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentParallelAnimation(QObject* aParent = NULL);
    // To JSON Object
    virtual QJsonObject toJSONObject();
    // Destructor
    ~ComponentParallelAnimation();
};







//==============================================================================
// Component Sequential Animation
//==============================================================================
class ComponentSequentialAnimation : public ComponentTransitionNode
{
    Q_OBJECT

public:
    // From JSON Object
    static ComponentSequentialAnimation* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentSequentialAnimation(QObject* aParent = NULL);
    // To JSON Object
    virtual QJsonObject toJSONObject();
    // Destructor
    ~ComponentSequentialAnimation();
};







//==============================================================================
// Component Pause Animation
//==============================================================================
class ComponentPauseAnimation : public ComponentTransitionNode
{
    Q_OBJECT

    // Duration
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    // From JSON Object
    static ComponentPauseAnimation* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentPauseAnimation(QObject* aParent = NULL);

    // Get Duration
    int duration();
    // Set Duration
    void setDuration(const int& aDuration);

    // To JSON Object
    virtual QJsonObject toJSONObject();

    // Destructor
    ~ComponentPauseAnimation();

signals:
    // Duration Changed Signal
    void durationChanged(const int& aDuration);

protected: // Data
    // Duration
    int     mDuration;
};







//==============================================================================
// Component Property Action
//==============================================================================
class ComponentPropertyAction : public ComponentTransitionNode
{
    Q_OBJECT

    // Target
    Q_PROPERTY(QString propertyActionTarget READ propertyActionTarget WRITE setPropertyActionTarget NOTIFY propertyActionTargetChanged)
    // Property
    Q_PROPERTY(QString propertyActionProperty READ propertyActionProperty WRITE setPropertyActionProperty NOTIFY propertyActionPropertyChanged)
    // Value
    Q_PROPERTY(QString propertyActionValue READ propertyActionValue WRITE setPropertyActionValue NOTIFY propertyActionValueChanged)

public:
    // From JSON Object
    static ComponentPropertyAction* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentPropertyAction(QObject* aParent = NULL);

    // Get Target
    QString propertyActionTarget();
    // Set Target
    void setPropertyActionTarget(const QString& aTarget);

    // Get Property
    QString propertyActionProperty();
    // Set Property
    void setPropertyActionProperty(const QString& aProperty);

    // Get Value
    QString propertyActionValue();
    // Set Value
    void setPropertyActionValue(const QString& aValue);

    // To JSON Object
    virtual QJsonObject toJSONObject();

    // Destructor
    ~ComponentPropertyAction();

signals:
    // Property Action Target changed Signal
    void propertyActionTargetChanged(const QString& aTarget);
    // Property Action Property Changed Signal
    void propertyActionPropertyChanged(const QString& aProperty);
    // Property Action Value Changed Signal
    void propertyActionValueChanged(const QString& aValue);

protected: // Data
    // Target
    QString     mTarget;
    // Property
    QString     mProperty;
    // Value
    QString     mValue;
};








//==============================================================================
// Component Script Action
//==============================================================================
class ComponentScriptAction : public ComponentTransitionNode
{
    Q_OBJECT

    // Script
    Q_PROPERTY(QString script READ script WRITE setScript NOTIFY scriptChanged)

public:
    // From JSON Object
    static ComponentScriptAction* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentScriptAction(QObject* aParent = NULL);

    // Get Script
    QString script();
    // Set Script
    void setScript(const QString& aScript);

    // To JSON Object
    virtual QJsonObject toJSONObject();

    // Destructor
    ~ComponentScriptAction();

signals:
    // Script Action Script Changed Signal
    void scriptChanged(const QString& aScript);

protected: // Data
    // Script
    QString     mScript;
};






//==============================================================================
// Component Property Animation
//==============================================================================
class ComponentPropertyAnimation : public ComponentTransitionNode
{
    Q_OBJECT

    // Base Type
    Q_PROPERTY(QString base READ base WRITE setBase NOTIFY baseChanged)
    // Target
    Q_PROPERTY(QString propertyAnimationTarget READ propertyAnimationTarget WRITE setPropertyAnimationTarget NOTIFY propertyAnimationTargetChanged)
    // Property
    Q_PROPERTY(QString propertyAnimationProperty READ propertyAnimationProperty WRITE setPropertyAnimationProperty NOTIFY propertyAnimationPropertyChanged)
    // From
    Q_PROPERTY(QString valueFrom READ valueFrom WRITE setValueFrom NOTIFY valueFromChanged)
    // To
    Q_PROPERTY(QString valueTo READ valueTo WRITE setValueTo NOTIFY valueToChanged)
    // Duration
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged)
    // Easing Type
    Q_PROPERTY(QString easingType READ easingType WRITE setEasingType NOTIFY easingTypeChanged)

    // Curve
    // Amplitude

public:
    // From JSON Object
    static ComponentPropertyAnimation* fromJSONObject(const QJsonObject& aObject);
    // Constructor
    explicit ComponentPropertyAnimation(QObject* aParent = NULL);

    // Get Base
    QString base();
    // Set Base
    void setBase(const QString& aBase);

    // Get Target
    QString propertyAnimationTarget();
    // Set Target
    void setPropertyAnimationTarget(const QString& aTarget);

    // Get Property
    QString propertyAnimationProperty();
    // Set Property
    void setPropertyAnimationProperty(const QString& aProperty);

    // Get Value From
    QString valueFrom();
    // Set Value From
    void setValueFrom(const QString& aValueFrom);

    // Get Value To
    QString valueTo();
    // Set Value To
    void setValueTo(const QString& aValueTo);

    // Get Duration
    QString duration();
    // Set Duration
    void setDuration(const QString& aDuration);

    // Get Easing Type
    QString easingType();
    // Set Easing Type
    void setEasingType(const QString& aEasingType);

    // To JSON Object
    virtual QJsonObject toJSONObject();

    // Destructor
    ~ComponentPropertyAnimation();

signals:
    // Base Type Changed Signal
    void baseChanged(const QString& aBase);
    // Target Changed Signal
    void propertyAnimationTargetChanged(const QString& aTarget);
    // Property Changed Signal
    void propertyAnimationPropertyChanged(const QString& aProperty);
    // Value From Changed Signal
    void valueFromChanged(const QString& aValueFrom);
    // Value To Changed Signal
    void valueToChanged(const QString& aValueTo);
    // Duration Changed Signal
    void durationChanged(const QString& aDuration);
    // Easing Type Changed Signal
    void easingTypeChanged(const QString& aEasingType);

protected: // Data
    // Base
    QString         mBase;
    // Target
    QString         mTarget;
    // Property
    QString         mProperty;
    // Value From
    QString         mValueFrom;
    // Value To
    QString         mValueTo;
    // Duration
    QString         mDuration;
    // Easing Type
    QString         mEasingType;
};

#endif // COMPONENTTRANSITIONSMODEL_H
