#include <QDebug>
#include <QJsonObject>

#include "componenttransitionsmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentTransitionsModel::ComponentTransitionsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentTransitionsModel::init()
{
    // Set Up Transition Node Type Map
    mNodeTypeMap[""]                                        = ETTUnknown;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_PARALLEL]  = ETTParallelAnimation;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_SQUENTIAL] = ETTSequentialAnimation;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_PAUSE]     = ETTPauseAnimation;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_ACTION]    = ETTPropertyAction;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_SCRIPT]    = ETTScripAction;
    mNodeTypeMap[JSON_VALUE_TRANSITION_NODE_TYPE_ANIMATION] = ETTPropertyAnimation;

    // Load Component Transitions
    loadComponentTransitions();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransitionsModel::clear()
{
    // Begin Reset model
    beginResetModel();

    // Iterate Through Transitions
    while (mTransitions.count() > 0) {
        // Delete Last
        delete mTransitions.takeLast();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Transitions
//==============================================================================
void ComponentTransitionsModel::loadComponentTransitions()
{
    // Clear
    clear();

    // Check Component
    if (mComponent) {

        // ...

    }
}

//==============================================================================
// Save Component Transitions
//==============================================================================
void ComponentTransitionsModel::saveComponentTransitions()
{
    // Check Component
    if (mComponent) {
        // Set Transiions
        mComponent->mTransitions = toJSONArray();
    }
}

//==============================================================================
// Add Transition
//==============================================================================
void ComponentTransitionsModel::addTransition(const QString& aFrom, const QString& aTo)
{
    // Create New Transition
    ComponentTransition* newTransition = new ComponentTransition(aFrom, aTo);
    // Begin Insert Rows
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // Append Transition
    mTransitions << newTransition;
    // End Insert Rows
    endInsertRows();
}

//==============================================================================
// Set Transition
//==============================================================================
void ComponentTransitionsModel::setTransition(const int& aIndex, const QString& aFrom, const QString& aTo)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Set Transition
        mTransitions[aIndex]->setFromState(aFrom);
        mTransitions[aIndex]->setToState(aTo);
    }
}

//==============================================================================
// Remove Transition
//==============================================================================
void ComponentTransitionsModel::removeTransition(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Transition
        delete mTransitions.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Remvoe Transitions
//==============================================================================
void ComponentTransitionsModel::removeTransition(ComponentTransition* aTransition)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // Iterate Through Transitions
    for (int i=0; mTransitions.count(); i++) {
        // Check Transitions
        if (mTransitions[i] == aTransition) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), i, i);
            // Delete Transition
            delete mTransitions.takeAt(i);
            // End Remove Rows
            endRemoveRows();
        }
    }
}

//==============================================================================
// Add Parallel Animation Node
//==============================================================================
void ComponentTransitionsModel::addParallelAnimation(ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Add Sequential Animation Node
//==============================================================================
void ComponentTransitionsModel::addSequentialAnimation(ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Add Pause Animation Node
//==============================================================================
void ComponentTransitionsModel::addPauseAnimation(const QString& aDuration, ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Add Property Animation Node
//==============================================================================
void ComponentTransitionsModel::addPropertyAnimation(const QString& aTarget,
                                                     const QString& aProperty,
                                                     const QString& aFrom,
                                                     const QString& aTo,
                                                     const QString& aDuration,
                                                     const QString& aEasing,
                                                     ComponentTransition* aTransition,
                                                     ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Add Property Action Node
//==============================================================================
void ComponentTransitionsModel::addPropertyAction(const QString& aTarget,
                                                  const QString& aProperty,
                                                  const QString& aValue,
                                                  ComponentTransition* aTransition,
                                                  ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Add Script Action Node
//==============================================================================
void ComponentTransitionsModel::addScriptAction(const QString& aScript,
                                                ComponentTransition* aTransition,
                                                ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Remove Transition Node
//==============================================================================
void ComponentTransitionsModel::removeTransitionNode(ComponentTransition* aTransition,
                                                     ComponentTransitionNode* aNode,
                                                     ComponentTransitionNode* aParentNode)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...
}

//==============================================================================
// Move Transition Node
//==============================================================================
void ComponentTransitionsModel::moveTransitionNode(ComponentTransition* aTransition,
                                                   ComponentTransitionNode* aNode,
                                                   ComponentTransitionNode* aTargetNode,
                                                   const int& aTargetIndex)
{
    // Check Transition
    if (!aTransition) {
        return;
    }

    // ...

}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentTransitionsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentTransitionsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Compoennt Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Transitions
        loadComponentTransitions();
    }
}

//==============================================================================
// Get Current Transition
//==============================================================================
ComponentTransition* ComponentTransitionsModel::currentTransition()
{
    return mCurrentTransition;
}

//==============================================================================
// Set Current Transition
//==============================================================================
void ComponentTransitionsModel::setCurrentTransition(ComponentTransition* aTransition)
{
    // Check Current Transition
    if (mCurrentTransition != aTransition) {
        // Set Current Transition
        mCurrentTransition = aTransition;
        // Emit Current Transition Changed Signal
        emit currentTransitionChanged(mCurrentTransition);
    }
}

//==============================================================================
// Get Current Node
//==============================================================================
ComponentTransitionNode* ComponentTransitionsModel::currentTransitionNode()
{
    return mCurrentTransitionNode;
}

//==============================================================================
// Set Current Node
//==============================================================================
void ComponentTransitionsModel::setCurrentTransitionNode(ComponentTransitionNode* aNode)
{
    // Check Current Transition Node
    if (mCurrentTransitionNode != aNode) {
        // Set Current Transition Node
        mCurrentTransitionNode = aNode;
        // Emit Current Transition Node Changed Signal
        emit currentTransitionNodeChanged(mCurrentTransitionNode);
    }
}

//==============================================================================
// To JSON Array
//==============================================================================
QJsonArray ComponentTransitionsModel::toJSONArray()
{
    // Init New JSON Array
    QJsonArray newJSONArray;

    // Get Count
    int tmCount = mTransitions.count();

    // Iterate Through Transitions
    for (int i=0; i<tmCount; i++) {
        // Push To JSON Array
        newJSONArray << mTransitions[i]->toJSONObject();
    }

    return newJSONArray;
}

//==============================================================================
// Get Transition
//==============================================================================
ComponentTransition* ComponentTransitionsModel::getTransition(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mTransitions[aIndex];
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentTransitionsModel::rowCount(const QModelIndex& ) const
{
    return mTransitions.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentTransitionsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int tmRow = index.row();
    // Check Row
    if (tmRow >= 0 && tmRow < rowCount()) {
        // Switch Role
        switch (role) {

        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentTransitionsModel::roleNames() const
{
    QHash<int, QByteArray> rNames;

    // ...

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentTransitionsModel::~ComponentTransitionsModel()
{
    // Clear
    clear();

    // ...
}










//==============================================================================
// From JSON Object
//==============================================================================
ComponentTransition* ComponentTransition::fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject)
{
    // Init New Compoennt Transition
    ComponentTransition* newTransition = new ComponentTransition(aObject[JSON_KEY_COMPONENT_TRANSITION_FROM].toString(),
                                                                 aObject[JSON_KEY_COMPONENT_TRANSITION_TO].toString());

    // Read Transition Nodes
    newTransition->readNodes(aObject[JSON_KEY_COMPONENT_TRANSITION_NODES].toArray());

    return newTransition;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentTransition::ComponentTransition(const QString& aFromState, const QString& aToState, QObject* aParent)
    : QObject(aParent)
    , mCurrentNode(NULL)
    , mFromState(aFromState)
    , mToState(aToState)
{
    // ...
}

//==============================================================================
// Get From State
//==============================================================================
QString ComponentTransition::fromState()
{
    return mFromState;
}

//==============================================================================
// Set From State
//==============================================================================
void ComponentTransition::setFromState(const QString& aFromState)
{
    // Check From State
    if (mFromState != aFromState) {
        // Set From State
        mFromState = aFromState;
        // Emit From State Changed Signal
        emit fromStateChanged(mFromState);
    }
}

//==============================================================================
// Get To State
//==============================================================================
QString ComponentTransition::toState()
{
    return mToState;
}

//==============================================================================
// Set To State
//==============================================================================
void ComponentTransition::setToState(const QString& aToState)
{
    // Check to State
    if (mToState != aToState) {
        // Set To State
        mToState = aToState;
        // Emit To State changed Signal
        emit toStateChanged(mToState);
    }
}

//==============================================================================
// Get Current Node
//==============================================================================
ComponentTransitionNode* ComponentTransition::currentNode()
{
    return mCurrentNode;
}

//==============================================================================
// Set Current Node
//==============================================================================
void ComponentTransition::setCurrentNode(ComponentTransitionNode* aNode)
{
    // Check Current Node
    if (mCurrentNode != aNode) {
        // Set Current Node
        mCurrentNode = aNode;
        // Emit Current Node Changed Signal
        emit currentNodeChanged(mCurrentNode);
    }
}

//==============================================================================
// Get Node Count
//==============================================================================
int ComponentTransition::nodeCount()
{
    return mNodes.count();
}

//==============================================================================
// Get Node By Index
//==============================================================================
ComponentTransitionNode* ComponentTransition::nodeByIndex(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mNodes.count()) {
        return mNodes[aIndex];
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentTransition::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Read Nodes
//==============================================================================
void ComponentTransition::readNodes(const QJsonArray& aNodes)
{
    // Check Nodes Array Count
    if (!aNodes.isEmpty()) {

        // ...

    }
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransition::clear()
{
    // Set Current Node
    setCurrentNode(NULL);

    // Iterate Through Nodes
    while (mNodes.count() > 0) {
        // Delete Last
        delete mNodes.takeLast();
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentTransition::~ComponentTransition()
{
    // Clear
    clear();

    // ...
}






//==============================================================================
// From JSON Object
//==============================================================================
ComponentTransitionNode* ComponentTransitionNode::fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject)
{
    // Check Model
    if (!aModel) {
        return NULL;
    }

    // Get Transitin Node Type
    ETransitionType tnType = aModel->mNodeTypeMap[aObject[JSON_KEY_COMPONENT_TRANSITION_NODE_TYPE].toString()];
    // Check Transition Node Type
    if (tnType == ETTUnknown) {
        return NULL;
    }

    // Init New Transition Node
    ComponentTransitionNode* newTransitionNode = NULL;

    // Switch Type
    switch (tnType) {
        case ETTParallelAnimation:      newTransitionNode = ComponentParallelAnimation::fromJSONObject(aObject); break;
        case ETTSequentialAnimation:    newTransitionNode = ComponentSequentialAnimation::fromJSONObject(aObject); break;
        case ETTPauseAnimation:         newTransitionNode = ComponentPauseAnimation::fromJSONObject(aObject); break;
        case ETTPropertyAction:         newTransitionNode = ComponentPropertyAction::fromJSONObject(aObject); break;
        case ETTScripAction:            newTransitionNode = ComponentScriptAction::fromJSONObject(aObject); break;
        case ETTPropertyAnimation:      newTransitionNode = ComponentPropertyAnimation::fromJSONObject(aObject); break;
        default: return newTransitionNode;
    }

    // Get Children Array
    QJsonArray childrenArray = aObject[JSON_KEY_COMPONENT_TRANSITION_NODE_CHILDREN].toArray();

    // Get Array Count
    int caCount = childrenArray.count();

    // Iterate Through Children Array
    for (int i=0; i<caCount; i++) {
        // Create New Child
        ComponentTransitionNode* newChild = ComponentTransitionNode::fromJSONObject(aModel, childrenArray[i].toObject());
        // Append Child
        newTransitionNode->appendChild(newChild);
    }

    return newTransitionNode;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentTransitionNode::ComponentTransitionNode(const ETransitionType& aType, QObject* aParent)
    : QObject(aParent)
    , mType(aType)
{
    // ...
}

//==============================================================================
// Get Count
//==============================================================================
int ComponentTransitionNode::count()
{
    return mChildren.count();
}

//==============================================================================
// Get Child
//==============================================================================
ComponentTransitionNode* ComponentTransitionNode::child(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mChildren.count()) {
        return mChildren[aIndex];
    }

    return NULL;
}

//==============================================================================
// Append Child
//==============================================================================
void ComponentTransitionNode::appendChild(ComponentTransitionNode* aChild)
{
    // Check Child Node
    if (mChildren.indexOf(aChild) >= 0) {
        return;
    }

    // Append Child
    mChildren << aChild;
}

//==============================================================================
// Insert Child
//==============================================================================
void ComponentTransitionNode::insertChild(const int& aIndex, ComponentTransitionNode* aChild)
{
    // Check Child Node
    if (mChildren.indexOf(aChild) >= 0) {
        return;
    }

    // Check Index
    if (aIndex >= 0 && aIndex < mChildren.count()) {
        // Insert Child
        mChildren.insert(aIndex, aChild);
    } else {
        // Append Child
        mChildren << aChild;
    }
}

//==============================================================================
// Remove Child
//==============================================================================
void ComponentTransitionNode::removeChild(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mChildren.count()) {
        // Delete Child
        delete mChildren.takeAt(aIndex);
    }
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransitionNode::clear()
{
    // Iterate Thru Children
    while (mChildren.count() > 0) {
        // Delete Last
        delete mChildren.takeLast();
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentTransitionNode::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newObject;

    // ...

    return newObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentTransitionNode::~ComponentTransitionNode()
{
    // Clear
    clear();

    // ...
}









//==============================================================================
// From JSON Object
//==============================================================================
ComponentParallelAnimation* ComponentParallelAnimation::fromJSONObject(const QJsonObject& aObject)
{
    Q_UNUSED(aObject);

    // Create New Component Parallel Animations
    ComponentParallelAnimation* newParallelAnimation = new ComponentParallelAnimation();

    // ...

    return newParallelAnimation;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentParallelAnimation::ComponentParallelAnimation(QObject* aParent)
    : ComponentTransitionNode(ETTParallelAnimation, aParent)
{

}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentParallelAnimation::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentParallelAnimation::~ComponentParallelAnimation()
{

}










//==============================================================================
// From JSON Object
//==============================================================================
ComponentSequentialAnimation* ComponentSequentialAnimation::fromJSONObject(const QJsonObject& aObject)
{
    Q_UNUSED(aObject);

    // Init New Sequential Animation
    ComponentSequentialAnimation* newSequentialAnimation = new ComponentSequentialAnimation();

    // ...

    return newSequentialAnimation;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentSequentialAnimation::ComponentSequentialAnimation(QObject* aParent)
    : ComponentTransitionNode(ETTSequentialAnimation, aParent)
{

}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentSequentialAnimation::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSequentialAnimation::~ComponentSequentialAnimation()
{

}







//==============================================================================
// From JSON Object
//==============================================================================
ComponentPauseAnimation* ComponentPauseAnimation::fromJSONObject(const QJsonObject& aObject)
{
    // Create New Pause Animation
    ComponentPauseAnimation* newPauseAnimation = new ComponentPauseAnimation();

    // Set Duration
    newPauseAnimation->setDuration(aObject[JSON_KEY_COMPONENT_TRANSITION_PAUSE_DURATION].toInt());

    return newPauseAnimation;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentPauseAnimation::ComponentPauseAnimation(QObject* aParent)
    : ComponentTransitionNode(ETTPauseAnimation, aParent)
    , mDuration(0)
{
    // ...
}

//==============================================================================
// Get Duration
//==============================================================================
int ComponentPauseAnimation::duration()
{
    return mDuration;
}

//==============================================================================
// Set Duration
//==============================================================================
void ComponentPauseAnimation::setDuration(const int& aDuration)
{
    // Check Duration
    if (mDuration != aDuration) {
        // Set Duration
        mDuration = aDuration;
        // Emit Duration Changed
        emit durationChanged(mDuration);
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentPauseAnimation::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPauseAnimation::~ComponentPauseAnimation()
{
    // ...
}









//==============================================================================
// From JSON Object
//==============================================================================
ComponentPropertyAction* ComponentPropertyAction::fromJSONObject(const QJsonObject& aObject)
{
    // Create New Property Action
    ComponentPropertyAction* newPropertyAction = new ComponentPropertyAction();

    // Set Target
    newPropertyAction->setPropertyActionTarget(aObject[JSON_KEY_COMPONENT_TRANSITION_PACTION_TARGET].toString());
    // Set Property
    newPropertyAction->setPropertyActionProperty(aObject[JSON_KEY_COMPONENT_TRANSITION_PACTION_PROPERTY].toString());
    // Set Value
    newPropertyAction->setPropertyActionValue(aObject[JSON_KEY_COMPONENT_TRANSITION_PACTION_VALUE].toString());

    return newPropertyAction;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertyAction::ComponentPropertyAction(QObject* aParent)
    : ComponentTransitionNode(ETTPropertyAction, aParent)
    , mTarget("")
    , mProperty("")
    , mValue("")
{
    // ...
}

//==============================================================================
// Get Target
//==============================================================================
QString ComponentPropertyAction::propertyActionTarget()
{
    return mTarget;
}

//==============================================================================
// Set Target
//==============================================================================
void ComponentPropertyAction::setPropertyActionTarget(const QString& aTarget)
{
    // Check Target
    if (mTarget != aTarget) {
        // Set Target
        mTarget = aTarget;
        // Emit Target Changed
        emit propertyActionTargetChanged(mTarget);
    }
}

//==============================================================================
// Get Property
//==============================================================================
QString ComponentPropertyAction::propertyActionProperty()
{
    return mProperty;
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentPropertyAction::setPropertyActionProperty(const QString& aProperty)
{
    // Check Property
    if (mProperty != aProperty) {
        // Set Property
        mProperty = aProperty;
        // Emit Property Changed Signal
        emit propertyActionPropertyChanged(mProperty);
    }
}

//==============================================================================
// Get Value
//==============================================================================
QString ComponentPropertyAction::propertyActionValue()
{
    return mValue;
}

//==============================================================================
// Set Value
//==============================================================================
void ComponentPropertyAction::setPropertyActionValue(const QString& aValue)
{
    // Check Value
    if (mValue != aValue) {
        // Set Value
        mValue = aValue;
        // Emit Value Changed Signal
        emit propertyActionValueChanged(mValue);
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentPropertyAction::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertyAction::~ComponentPropertyAction()
{
    // ...
}







//==============================================================================
// From JSON Object
//==============================================================================
ComponentScriptAction* ComponentScriptAction::fromJSONObject(const QJsonObject& aObject)
{
    // Create New Script Action
    ComponentScriptAction* newScriptAction = new ComponentScriptAction();

    // Set Script
    newScriptAction->setScript(aObject[JSON_KEY_COMPONENT_TRANSITION_SACTION_SCRIPT].toString());

    return newScriptAction;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentScriptAction::ComponentScriptAction(QObject* aParent)
    : ComponentTransitionNode(ETTScripAction, aParent)
    , mScript("")
{
    // ...
}

//==============================================================================
// Get Script
//==============================================================================
QString ComponentScriptAction::script()
{
    return mScript;
}

//==============================================================================
// Set Script
//==============================================================================
void ComponentScriptAction::setScript(const QString& aScript)
{
    // Check Script
    if (mScript != aScript) {
        // Set Script
        mScript = aScript;
        // Emit Script Changed Signal
        emit scriptChanged(mScript);
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentScriptAction::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentScriptAction::~ComponentScriptAction()
{
    // ...
}






//==============================================================================
// From JSON Object
//==============================================================================
ComponentPropertyAnimation* ComponentPropertyAnimation::fromJSONObject(const QJsonObject& aObject)
{
    // Init New Property Animation
    ComponentPropertyAnimation* newPropertyAnimation = new ComponentPropertyAnimation();

    // Set Target
    newPropertyAnimation->setPropertyAnimationTarget(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_TARGET].toString());
    // Set Property
    newPropertyAnimation->setPropertyAnimationProperty(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_PROPERTY].toString());
    // Set Value From
    newPropertyAnimation->setValueFrom(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_VALUEFROM].toString());
    // Set Value To
    newPropertyAnimation->setValueTo(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_VALUETO].toString());
    // Set Duration
    newPropertyAnimation->setDuration(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_DURATION].toString());
    // Set Easing Type
    newPropertyAnimation->setEasingType(aObject[JSON_KEY_COMPONENT_TRANSITION_PANIMATION_ETYPE].toString());

    return newPropertyAnimation;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertyAnimation::ComponentPropertyAnimation(QObject* aParent)
    : ComponentTransitionNode(ETTPropertyAnimation, aParent)
    , mTarget("")
    , mProperty("")
    , mValueFrom("")
    , mValueTo("")
    , mDuration("")
    , mEasingType("")
{
    // ...
}

//==============================================================================
// Get Base
//==============================================================================
QString ComponentPropertyAnimation::base()
{
    return mBase;
}

//==============================================================================
// Set Base
//==============================================================================
void ComponentPropertyAnimation::setBase(const QString& aBase)
{
    // Check Base
    if (mBase != aBase) {
        // Set Base
        mBase = aBase;
        // Emit Property Animation Base Changed Signal
        emit baseChanged(mBase);
    }
}

//==============================================================================
// Get Target
//==============================================================================
QString ComponentPropertyAnimation::propertyAnimationTarget()
{
    return mTarget;
}

//==============================================================================
// Set Target
//==============================================================================
void ComponentPropertyAnimation::setPropertyAnimationTarget(const QString& aTarget)
{
    // Check Target
    if (mTarget != aTarget) {
        // Set Target
        mTarget = aTarget;
        // Emit Target Changed Signal
        emit propertyAnimationTargetChanged(mTarget);
    }
}

//==============================================================================
// Get Property
//==============================================================================
QString ComponentPropertyAnimation::propertyAnimationProperty()
{
    return mProperty;
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentPropertyAnimation::setPropertyAnimationProperty(const QString& aProperty)
{
    // Check Property
    if (mProperty != aProperty) {
        // Set Property
        mProperty = aProperty;
        // Emit Property Changed Signal
        emit propertyAnimationPropertyChanged(mProperty);
    }
}

//==============================================================================
// Get Value From
//==============================================================================
QString ComponentPropertyAnimation::valueFrom()
{
    return mValueFrom;
}

//==============================================================================
// Set Value From
//==============================================================================
void ComponentPropertyAnimation::setValueFrom(const QString& aValueFrom)
{
    // Check Value From
    if (mValueFrom != aValueFrom) {
        // Set Value From
        mValueFrom = aValueFrom;
        // Emit Value From Changed Signal
        emit valueFromChanged(mValueFrom);
    }
}

//==============================================================================
// Get Value To
//==============================================================================
QString ComponentPropertyAnimation::valueTo()
{
    return mValueTo;
}

//==============================================================================
// Set Value To
//==============================================================================
void ComponentPropertyAnimation::setValueTo(const QString& aValueTo)
{
    // Check Value To
    if (mValueTo != aValueTo) {
        // Set Value To
        mValueTo = aValueTo;
        // Emit Value To Changed Signal
        emit valueToChanged(mValueTo);
    }
}

//==============================================================================
// Get Duration
//==============================================================================
QString ComponentPropertyAnimation::duration()
{
    return mDuration;
}

//==============================================================================
// Set Duration
//==============================================================================
void ComponentPropertyAnimation::setDuration(const QString& aDuration)
{
    // Check Duration
    if (mDuration != aDuration) {
        // Set Duration
        mDuration = aDuration;
        // Emit Duration Change Signal
        emit durationChanged(mDuration);
    }
}

//==============================================================================
// Get Easing Type
//==============================================================================
QString ComponentPropertyAnimation::easingType()
{
    return mEasingType;
}

//==============================================================================
// Set Easing Type
//==============================================================================
void ComponentPropertyAnimation::setEasingType(const QString& aEasingType)
{
    // Check Easing Type
    if (mEasingType != aEasingType) {
        // Set Easing Type
        mEasingType = aEasingType;
        // Emit Easing Type Changed Signal
        emit easingTypeChanged(mEasingType);
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentPropertyAnimation::toJSONObject()
{
    QJsonObject newObject;

    // ...

    return newObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertyAnimation::~ComponentPropertyAnimation()
{
    // ...
}

