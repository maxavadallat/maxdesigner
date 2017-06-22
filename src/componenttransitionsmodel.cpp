#include <QDebug>
#include <QJsonObject>
#include <QQmlEngine>

#include "componenttransitionsmodel.h"
#include "componentinfo.h"
#include "constants.h"
#include "projectmodel.h"
#include "basecomponentsmodel.h"
#include "componentsmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentTransitionsModel::ComponentTransitionsModel(ComponentInfo* aComponent, ProjectModel* aProjectModel, AnimationComponentsModel* aAnimComponents, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProject(aProjectModel)
    , mAnimComponents(aAnimComponents)
    , mComponent(aComponent)
    , mNewTransition(NULL)
    , mCurrentTransition(NULL)
    , mSelectedIndex(-1)
    , mDirty(false)
{
    qDebug() << "ComponentTransitionsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentTransitionsModel::init()
{
    // Load Component Transitions
    loadComponentTransitions();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransitionsModel::clear()
{
    // Check Count
    if (rowCount() > 0) {
        qDebug() << "ComponentTransitionsModel::clear";

        // Begin Reset model
        beginResetModel();

        // Iterate Through Transitions
        while (mTransitions.count() > 0) {
            // Delete Last
            delete mTransitions.takeLast();
        }

        // End Reset Model
        endResetModel();

//        // Emit Transitions Count Changed Signal
//        emit transitionsCountChanged(mTransitions.count());
    }
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
        //qDebug() << "ComponentTransitionsModel::setCurrentComponent - aComponent: " << (aComponent ? aComponent->mName : "NULL");

        // Save Component Transtions For Previous Component
        saveComponentTransitions();
        // Clear
        clear();
        // Discard New Transition
        discardNewTransition();

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
// Select Transition
//==============================================================================
ComponentTransition* ComponentTransitionsModel::selectTransition(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Set Selected Index
        mSelectedIndex = aIndex;
        // Get Transition
        ComponentTransition* transition = mTransitions[aIndex];
        // Set Current Transition
        setCurrentTransition(transition);

        return transition;
    }

    return NULL;
}

//==============================================================================
// Create New Transition
//==============================================================================
ComponentTransition* ComponentTransitionsModel::createNewTransition()
{
    // Reset Selected Index
    mSelectedIndex = -1;

    // Check New Transition
    if (!mNewTransition) {
        qDebug() << "ComponentTransitionsModel::createNewTransition";

        // Create New Transition
        mNewTransition = new ComponentTransition("", "", this);
        // Set Current Transition
        setCurrentTransition(mNewTransition);

    } else {
        qWarning() << "ComponentTransitionsModel::createNewTransition - NEW TRANSITION ALREADY CREATED!!";
    }

    return mNewTransition;
}

//==============================================================================
// Discard New Transition
//==============================================================================
void ComponentTransitionsModel::discardNewTransition()
{
    // Check New Transition
    if (mNewTransition) {
        qDebug() << "ComponentTransitionsModel::discardNewTransition";

        // Check Current Transition
        if (mCurrentTransition != NULL && mCurrentTransition == mNewTransition) {
            // Reset Current Transition
            setCurrentTransition(NULL);
        }

        // Delete New Transition
        delete mNewTransition;
        mNewTransition = NULL;
    }
}

//==============================================================================
// Append Transition
//==============================================================================
void ComponentTransitionsModel::appendTransition(ComponentTransition* aTransition)
{
    // Check Transition
    if (aTransition) {
        qDebug() << "ComponentTransitionsModel::appendTransition - from: " << aTransition->fromState() << " - to: " << aTransition->toState();

        // Connect Dirty Changed Signal
        connect(aTransition, SIGNAL(dirtyChanged(bool)), this, SLOT(componentTransitionDirtyChanged(bool)));

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Transition
        mTransitions << aTransition;
        // End Insert Rows
        endInsertRows();

        // Set Dirty
        setDirty(true);

        // Check Transition
        if (mNewTransition == aTransition) {
            // Reset New Transition
            mNewTransition = NULL;
        }
    }
}

//==============================================================================
// Load Component Transitions
//==============================================================================
void ComponentTransitionsModel::loadComponentTransitions()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // Get Transitions Count
    int tCount = mComponent->mTransitions.count();

    // Check Count
    if (tCount > 0) {
        qDebug() << "ComponentTransitionsModel::loadComponentTransitions";

        // Begin Reset model
        beginResetModel();

        // Iterate Through Transtions
        for (int i=0; i<tCount; i++) {
            // Creste New Transition
            ComponentTransition* newtransition = ComponentTransition::fromJSONObject(this, mComponent->mTransitions[i].toObject());
            // Connect Dirty Changed Signal
            connect(newtransition, SIGNAL(dirtyChanged(bool)), this, SLOT(componentTransitionDirtyChanged(bool)));
            // Append Transition
            mTransitions << newtransition;
        }

        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Save Component Transitions
//==============================================================================
void ComponentTransitionsModel::saveComponentTransitions()
{
    // Check Component
    if (mComponent && mDirty) {
        qDebug() << "ComponentTransitionsModel::saveComponentTransitions";

        // Set Transiions
        mComponent->mTransitions = toJSONArray();

        // Set Component's Dirty State
        mComponent->setDirty(true);

        // Reset Dirty State
        setDirty(false);
    }
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentTransitionsModel::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        qDebug() << "ComponentTransitionsModel::setDirty - aDirty: " << aDirty;

        // Set Dirty State
        mDirty = aDirty;

        // ...

        // Save Component Transitions
        saveComponentTransitions();
    }
}

//==============================================================================
// Add Transition
//==============================================================================
void ComponentTransitionsModel::addTransition(const QString& aFrom, const QString& aTo)
{
    // Create New Transition
    ComponentTransition* newTransition = new ComponentTransition(aFrom, aTo, this);

    qDebug() << "ComponentTransitionsModel::addTransition - aFrom: " << aFrom << " - aTo: " << aTo;

    appendTransition(newTransition);
}

//==============================================================================
// Remove Transition
//==============================================================================
void ComponentTransitionsModel::removeTransition(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentTransitionsModel::removeTransition - aIndex: " << aIndex;

        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Take Transition
        ComponentTransition* takenTransition = mTransitions.takeAt(aIndex);
        // Delete Transition
        delete takenTransition;
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Update Selected Transition
//==============================================================================
void ComponentTransitionsModel::updateSelectedTransition()
{
    // Check Selected Index
    if (mSelectedIndex >= 0 && mSelectedIndex < rowCount()) {

        // Get Selected State
        ComponentTransition* componentTransition = mTransitions[mSelectedIndex];

        // Check Selected State
        if (componentTransition && componentTransition->mDirty) {
            // Emit Data Changed Signal
            emit dataChanged(index(mSelectedIndex), index(mSelectedIndex));

            // Reset Dirty State
            componentTransition->setDirty(false);

            // Set Dirty State -> Save Component States
            setDirty(true);

            // ...
        }
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

    qDebug() << "ComponentTransitionsModel::toJSONArray - tmCount: " << tmCount;

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
        // Set Selected Transition Index
        mSelectedIndex = aIndex;

        return mTransitions[aIndex];
    }

    return NULL;
}

//==============================================================================
// Move Transition
//==============================================================================
void ComponentTransitionsModel::moveTransition(const int& aIndex, const int& aTarget)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentTransitionsModel::moveTransition - aIndex: " << aIndex << " - aTarget: " << aTarget;

        // Move Transition
        mTransitions.move(aIndex, aTarget);
    }
}

//==============================================================================
// Component Transition Dirty State Changed
//==============================================================================
void ComponentTransitionsModel::componentTransitionDirtyChanged(const bool& aDirty)
{
    // Check Dirty State
    if (aDirty) {
        qDebug() << "ComponentTransitionsModel::componentTransitionDirtyChanged";

        // Get Sender Component Transition
        ComponentTransition* componentTransition = static_cast<ComponentTransition*>(sender());
        // Check Sender
        if (componentTransition) {

            // Update Selected Transition
            updateSelectedTransition();

            // Set Dirty
            setDirty(true);


            // ...

            // Reset Dirty
            //componentTransition->setDirty(false);
        }
    }
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
        // Get Transition
        ComponentTransition* transition = mTransitions[tmRow];
        // Switch Role
        switch (role) {
            case ETMRFromState:     return transition->fromState();
            case ETMRToState:       return transition->toState();
            case ETMRNodesCount:    return transition->nodesCount();

            // ...
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentTransitionsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    // Set Up Role Names
    rNames[ETMRFromState]   = "tmFrom";
    rNames[ETMRToState]     = "tmTo";
    rNames[ETMRNodesCount]  = "tmNodesCount";

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

    // Discard New Transition
    discardNewTransition();

    // ...

    qDebug() << "ComponentTransitionsModel deleted.";
}










//==============================================================================
// From JSON Object
//==============================================================================
ComponentTransition* ComponentTransition::fromJSONObject(ComponentTransitionsModel* aModel, const QJsonObject& aObject)
{
    // Init New Compoennt Transition
    ComponentTransition* newTransition = new ComponentTransition(aObject[JSON_KEY_COMPONENT_TRANSITION_FROM].toString(),
                                                                 aObject[JSON_KEY_COMPONENT_TRANSITION_TO].toString(),
                                                                 aModel);

    // Read Transition Nodes
    newTransition->readNodes(aObject[JSON_KEY_COMPONENT_TRANSITION_NODES].toArray());

    return newTransition;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentTransition::ComponentTransition(const QString& aFromState, const QString& aToState, ComponentTransitionsModel* aModel, QObject* aParent)
    : QObject(aParent)
    , mModel(aModel)
    , mProject(mModel ? mModel->mProject : NULL)
    , mFromState(aFromState)
    , mToState(aToState)
    , mNewNode(NULL)
    , mDirty(false)
{
    qDebug() << "ComponentTransition created.";

    // Set Ownership
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

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
        qDebug() << "ComponentTransition::setFromState - aFromState: " << aFromState;
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
        qDebug() << "ComponentTransition::setToState - aToState: " << aToState;
        // Set To State
        mToState = aToState;
        // Emit To State changed Signal
        emit toStateChanged(mToState);
    }
}

//==============================================================================
// Get Node Count
//==============================================================================
int ComponentTransition::nodesCount()
{
    return mNodes.count();
}

//==============================================================================
// Create New Node
//==============================================================================
ComponentInfo* ComponentTransition::createNewNode(const QString& aComponentName)
{
    // Check Transitions Model
    if (!mModel) {
        qWarning() << "ComponentTransition::createNewNode - NO TRANSITIONS MODEL!!";
        return NULL;
    }

    // Check New Node
    if (!mNewNode) {
        qDebug() << "ComponentTransition::createNewNode - aComponentName: " << aComponentName;
        // Create New Node
        mNewNode = mModel->mAnimComponents->cloneAnimation(aComponentName);
        // Set Transition Parent
        mNewNode->mTransitionParent = this;
        // Set Current Node
        mCurrentNode = mNewNode;

    } else {
        qWarning() << "ComponentTransition::createNewNode - ALREADY HAVE A NEW NODE!!";
    }

    return mNewNode;
}

//==============================================================================
// Discard New Node
//==============================================================================
void ComponentTransition::discardNewNode()
{
    // Check New Node
    if (mNewNode) {
        qDebug() << "ComponentTransition::discardNewNode";

        // Delete New Node
        delete mNewNode;
        mNewNode = NULL;
    }
}

//==============================================================================
// Select Transition Node
//==============================================================================
ComponentInfo* ComponentTransition::selectNode(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mNodes.count()) {
        // Set Current Node
        mCurrentNode = mNodes[aIndex];

        return mCurrentNode;
    }

    return NULL;
}

//==============================================================================
// Get Node By Index
//==============================================================================
ComponentInfo* ComponentTransition::getNode(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mNodes.count()) {
        return mNodes[aIndex];
    }

    return NULL;
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentTransition::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Check If Empty
    if (!mFromState.isEmpty()) {
        // Set From State
        newJSONObject[JSON_KEY_COMPONENT_TRANSITION_FROM] = mFromState;
    }

    // Check If Empty
    if (!mToState.isEmpty()) {
        // Set To State
        newJSONObject[JSON_KEY_COMPONENT_TRANSITION_TO] = mToState;
    }

    // Get Nodes Count
    int nCount = mNodes.count();

    // Check Nodes Count
    if (nCount > 0) {
        // Init New JSON Array
        QJsonArray newNodesArray;

        // Iterate Through Nodes
        for (int i=0; i<nCount; i++) {
            // Append Node
            newNodesArray << mNodes[i]->toJSONObject();
        }

        // Set Nodes Array
        newJSONObject[JSON_KEY_COMPONENT_TRANSITION_NODES] = newNodesArray;
    }

    return newJSONObject;
}

//==============================================================================
// Read Nodes
//==============================================================================
void ComponentTransition::readNodes(const QJsonArray& aNodes)
{
    // Check Nodes Array Count
    if (!aNodes.isEmpty() && mProject) {
        // Get Nodes Count
        int nCount = aNodes.count();

        qDebug() << "ComponentTransition::readNodes - nCount: " << nCount;

        // Iterate Through Nodes Array
        for (int i=0; i<nCount; i++) {
            // Get Node Object
            QJsonObject nodeObject = aNodes[i].toObject();
            // Get Node Name
            QString nodeName = nodeObject.value(JSON_KEY_COMPONENT_NAME).toString();
            // Get Node Type
            QString nodeType = nodeObject.value(JSON_KEY_COMPONENT_TYPE).toString();

            qDebug() << "ComponentTransition::readNodes - nodeName: " << nodeName << " - nodeType: " << nodeType;

            // Find Node Component
            ComponentInfo* newNodeInfo = mProject->getComponentByName(nodeName, nodeType);
            // Check Node Component
            if (newNodeInfo) {
                // Clone Component
                newNodeInfo = newNodeInfo->clone();
                // Set Transition Parent
                newNodeInfo->mTransitionParent = this;
                // Load From JSON
                newNodeInfo->fromJSONObject(nodeObject, true);
            }

            // Append To Nodes
            mNodes << newNodeInfo;

            // Emit Nodes Count Changed
            emit nodeCountChanged(mNodes.count());

            // ...
        }
    }
}

//==============================================================================
// Append Node
//==============================================================================
void ComponentTransition::appendNode(ComponentInfo* aNode, ComponentInfo* aParentNode)
{
    // Check Node
    if (!aNode) {
        return;
    }

    qDebug() << "ComponentTransition::appendNode - mName: " << aNode->mName;

    // Check Parent Node
    if (aParentNode) {
        // Append Node
        aParentNode->addChild(aNode);

        // Emit Node Added Signal
        emit nodeAdded(aParentNode, aParentNode->animsCount() - 1);

    } else {
        // Append Node
        mNodes << aNode;

        // Emit Nodes Count Changed Signal
        emit nodeCountChanged(mNodes.count());

        // Emit Node Added Signal
        emit nodeAdded(NULL, mNodes.count() - 1);
    }

    // Check New Node
    if (mNewNode == aNode) {
        // Reset New Node
        mNewNode = NULL;
    }

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Insert Node
//==============================================================================
void ComponentTransition::insertNode(const int& aIndex, ComponentInfo* aNode, ComponentInfo* aParentNode)
{
    // Check Node
    if (!aNode) {
        return;
    }

    qDebug() << "ComponentTransition::insertNode - aIndex: " << aIndex << " - mName: " << aNode->mName;

    // Check Parent Node
    if (aParentNode) {
        // Insert Node
        aParentNode->insertChild(aIndex, aNode, false);
    } else {
        // Check Index
        if (aIndex >= 0 && aIndex < mNodes.count()) {
            // Insert Node
            mNodes.insert(aIndex, aNode);
        } else {
            // Append Node
            mNodes << aNode;
        }

        // Emit Nodes Count Changed Signal
        emit nodeCountChanged(mNodes.count());

        // Set Dirty
        setDirty(true);
    }

    // Check New Node
    if (mNewNode == aNode) {
        // Reset New Node
        mNewNode = NULL;
    }
}

//==============================================================================
// Move Node
//==============================================================================
void ComponentTransition::moveNode(const int& aIndex, const int& aTargetIndex)
{
    qDebug() << "ComponentTransition::moveNode - aIndex: " << aIndex << " - aTargetIndex: " << aTargetIndex;

    // Check Index

    // ...

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Move Node
//==============================================================================
void ComponentTransition::moveNode(ComponentInfo* aParentNode, const int& aIndex, ComponentInfo* aTargetNode, const int& aTargetIndex)
{
    qDebug() << "ComponentTransition::moveNode - aParentNode: " << aParentNode << " - aIndex: " << aIndex << " - aTargetNode: " << aTargetNode << " - aTargetIndex: " << aTargetIndex;

    // ...

    // Set Dirty
    setDirty(true);
    // Emit Node Moved Signal
    emit nodeMoved(aParentNode, aIndex, aTargetNode, aTargetIndex);
}

//==============================================================================
// Remove Node
//==============================================================================
void ComponentTransition::removeNode(ComponentInfo* aParentNode, const int& aIndex)
{
    // Check Parent Node
    if (aParentNode) {
        // Get Parent Node Anims Count
        int aCount = aParentNode->animsCount();
        // Check Index
        if (aIndex >= 0 && aIndex < aCount) {
            // Remove Child
            aParentNode->removeAnimation(aIndex);
            // Set Dirty
            setDirty(true);
            // Emit Node Removed Signal
            emit nodeRemoved(aParentNode, aIndex);
        }

    } else {
        // Check Index
        if (aIndex >= 0 && aIndex < mNodes.count()) {
            qDebug() << "ComponentTransition::removeNode - aIndex: " << aIndex;
            // Remove Node
            delete mNodes.takeAt(aIndex);
            // Emit Nodes Count Changed Signal
            emit nodeCountChanged(mNodes.count());
            // Set Dirty
            setDirty(true);
            // Emit Node Removed
            emit nodeRemoved(NULL, aIndex);
        }
    }
}

//==============================================================================
// Remove Node By Component Info
//==============================================================================
void ComponentTransition::removeNode(ComponentInfo* aNode)
{
    // Check Node
    if (aNode) {
        // Get Node Index
        int anIndex = mNodes.indexOf(aNode);
        // Check Index
        if (anIndex >= 0) {
            qDebug() << "ComponentTransition::removeNode - anIndex: " << anIndex;
            // Remove Node
            delete mNodes.takeAt(anIndex);
            // Emit Nodes Count Changed Signal
            emit nodeCountChanged(mNodes.count());
            // Set Dirty
            setDirty(true);
            // Emit Node Removed
            emit nodeRemoved(NULL, anIndex);
        }
    }
}

//==============================================================================
// Clear Transition
//==============================================================================
void ComponentTransition::clearTransition()
{
    qDebug() << "ComponentTransition::clearTransition";
    // Reset From State
    setFromState("");
    // Reset To State
    setToState("");
    // Clear
    clear();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransition::clear()
{
    // Check Nodes Count
    if (mNodes.count() > 0) {
        qDebug() << "ComponentTransition::clear";
        // Iterate Through Nodes
        while (mNodes.count() > 0) {
            // Delete Last
            delete mNodes.takeLast();
        }

        // Emit Nodes Count Changed Signal
        emit nodeCountChanged(mNodes.count());
    }
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentTransition::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        // Set Dirty State
        mDirty = aDirty;
        // Emit Dirty State changed Signal
        emit dirtyChanged(mDirty);
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentTransition::~ComponentTransition()
{
    // Discard New Node
    discardNewNode();

    // Clear
    clear();

    // ...

    qDebug() << "ComponentTransition deleted.";
}

















//==============================================================================
// Constructor
//==============================================================================
AnimationComponentsModel::AnimationComponentsModel(ProjectModel* aProject, QObject* aParent)
    : QAbstractListModel(aParent)
    , mProject(aProject)
    , mBaseComponents(mProject ? mProject->baseComponentsModel() : NULL)
    , mComponents(mProject ? mProject->componentsModel() : NULL)
{
    qDebug() << "AnimationComponentsModel created.";

    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void AnimationComponentsModel::init()
{
    // Collect Animation Components
    collectAnimationComponents();

    // Connect Project Signals
    connectModelSignals();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void AnimationComponentsModel::clear()
{
    // Check Count
    if (mAnimationComponents.count() > 0) {
        qDebug() << "AnimationComponentsModel::clear";
        // Begin Reset Model
        beginResetModel();
        // Clear Anim Components
        mAnimationComponents.clear();
        // End Reset Model
        endResetModel();

        // Emit Animation Components Cleared
        emit animationComponentsCleared();
    }
}

//==============================================================================
// Connect Model Signals
//==============================================================================
void AnimationComponentsModel::connectModelSignals()
{
    // Check Project Model
    if (!mProject) {
        //qWarning() << "AnimationComponentsModel::connectModelSignals - NO PROJECT MODEL IS SET!!";
        return;
    }

    qDebug() << "AnimationComponentsModel::connectModelSignals";

    // Check Base Compoennts
    if (mBaseComponents) {
        // Connect Signals
        connect(mBaseComponents, SIGNAL(baseComponentAdded(ComponentInfo*)), this, SLOT(componentAdded(ComponentInfo*)));
        connect(mBaseComponents, SIGNAL(baseComponentAboutToBeRemoved(ComponentInfo*)), this, SLOT(componentAboutToBeRemoved(ComponentInfo*)));
    }

    // Check Components
    if (mComponents) {
        // Connect Signals
        connect(mComponents, SIGNAL(componentAdded(ComponentInfo*)), this, SLOT(componentAdded(ComponentInfo*)));
        connect(mComponents, SIGNAL(componentAboutToBeRemoved(ComponentInfo*)), this, SLOT(componentAboutToBeRemoved(ComponentInfo*)));
    }

    // ...
}

//==============================================================================
// Disconnect Model Signals
//==============================================================================
void AnimationComponentsModel::disconnectModelSignals()
{
    // Check Project Model
    if (!mProject) {
        return;
    }

    qDebug() << "AnimationComponentsModel::disconnectModelSignals";

    // Check Base Compoennts
    if (mBaseComponents) {
        // Disconnect Signals
        disconnect(mBaseComponents, SIGNAL(baseComponentAdded(ComponentInfo*)), this, SLOT(componentAdded(ComponentInfo*)));
        disconnect(mBaseComponents, SIGNAL(baseComponentAboutToBeRemoved(ComponentInfo*)), this, SLOT(componentAboutToBeRemoved(ComponentInfo*)));
    }

    // Check Components
    if (mComponents) {
        // Disconnect Signals
        disconnect(mComponents, SIGNAL(componentAdded(ComponentInfo*)), this, SLOT(componentAdded(ComponentInfo*)));
        disconnect(mComponents, SIGNAL(componentAboutToBeRemoved(ComponentInfo*)), this, SLOT(componentAboutToBeRemoved(ComponentInfo*)));
    }

    // ...
}

//==============================================================================
// Collect Animation Components
//==============================================================================
void AnimationComponentsModel::collectAnimationComponents()
{
    // Check Project Model
    if (!mProject) {
        //qWarning() << "AnimationComponentsModel::collectAnimationComponents - NO PROJECT MODEL IS SET!!";
        return;
    }

    qDebug() << "AnimationComponentsModel::collectAnimationComponents";

    // Check Base Components Model
    if (mBaseComponents) {
        // Get Row Count
        int bcCount = mBaseComponents->rowCount();
        // Iterate Through Base Compoennts
        for (int i=0; i<bcCount; i++) {
            // Append Compoennt
            componentAdded(mBaseComponents->getComponentByIndex(i));
        }

    } else {
        qWarning() << "AnimationComponentsModel::collectAnimationComponents - NO BASE COMPONENTS MODEL!!";
    }

    // Check Components Model
    if (mComponents) {

        // Get Row Count
        int cCount = mComponents->rowCount();
        // Iterate Through Base Compoennts
        for (int i=0; i<cCount; i++) {
            // Append Compoennt
            componentAdded(mComponents->getComponentByIndex(i));
        }

    } else {
        qWarning() << "AnimationComponentsModel::collectAnimationComponents - NO COMPONENTS MODEL!!";
    }

    // ...
}

//==============================================================================
// Get Current Project
//==============================================================================
ProjectModel* AnimationComponentsModel::currentProject()
{
    return mProject;
}

//==============================================================================
// Set Current Project
//==============================================================================
void AnimationComponentsModel::setCurrentProject(ProjectModel* aProjectModel)
{
    // Check Current Project
    if (mProject != aProjectModel) {
        //qDebug() << "AnimationComponentsModel::setCurrentProject - aProjectModel: " << aProjectModel;

        // Disconnect Modl Signals
        disconnectModelSignals();
        // Clear
        clear();
        // Set Current Project
        mProject = aProjectModel;

        // Set Base Components
        mBaseComponents = mProject ? mProject->baseComponentsModel() : NULL;
        // Set Components Model
        mComponents = mProject ? mProject->componentsModel() : NULL;

        // Emit Current Project changed Signal
        emit currentProjectChanged(mProject);
        // Collect Animation Components
        collectAnimationComponents();
        // Connect Model Signals
        connectModelSignals();
    }
}

//==============================================================================
// Get Animation Component Name By Index
//==============================================================================
QString AnimationComponentsModel::getNameByIndex(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mAnimationComponents[aIndex]->mName;
    }

    return "";
}

//==============================================================================
// Clone Animation Component By Index
//==============================================================================
ComponentInfo* AnimationComponentsModel::cloneAnimation(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "AnimationComponentsModel::cloneAnimation - aIndex: " << aIndex;
        // Clone Animation
        return mAnimationComponents[aIndex]->clone();
    }

    return NULL;
}

//==============================================================================
// Clone Animation Component By Name
//==============================================================================
ComponentInfo* AnimationComponentsModel::cloneAnimation(const QString& aName)
{
    // Check Name
    if (aName.isEmpty()) {
        return NULL;
    }

    qDebug() << "AnimationComponentsModel::cloneAnimation - aName: " << aName;

    // Get Animation Component Count
    int acCount = rowCount();

    for (int i=0; i<acCount; i++) {
        // Get Animation Component
        ComponentInfo* animComponent = mAnimationComponents[i];
        // Check Component Name
        if (animComponent->mName == aName) {
            return animComponent->clone();
        }
    }

    return NULL;
}

//==============================================================================
// Component Created Slot
//==============================================================================
void AnimationComponentsModel::componentCreated(ComponentInfo* aComponent, const int& , const int& )
{
    // Check Component
    if (aComponent && aComponent->mCategory == "Animation") {
        qDebug() << "AnimationComponentsModel::componentCreated - mName: " << aComponent->mName;

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append To Animation Components
        mAnimationComponents << aComponent;
        // End Insert Rows
        endInsertRows();

        // Amit Item Added Signal
        emit itemAdded(rowCount() - 1);
    }
}

//==============================================================================
// Component Added Slot
//==============================================================================
void AnimationComponentsModel::componentAdded(ComponentInfo* aComponent)
{
    // Check Component - Filter Animations
    if (aComponent && aComponent->mCategory == "Animation" && aComponent->mName != "Animation") {
        qDebug() << "AnimationComponentsModel::componentAdded - mName: " << aComponent->mName;

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append To Animation Components
        mAnimationComponents << aComponent;
        // End Insert Rows
        endInsertRows();

        // Amit Item Added Signal
        emit itemAdded(rowCount() - 1);
    }
}

//==============================================================================
// Component About To Be Removed Slot
//==============================================================================
void AnimationComponentsModel::componentAboutToBeRemoved(ComponentInfo* aComponent)
{
    // Check Component - Filter Animations
    if (aComponent && aComponent->mCategory == "Animation") {
        qDebug() << "AnimationComponentsModel::componentCreated - mName: " << aComponent->mName;

        // Get Index
        int acIndex = mAnimationComponents.indexOf(aComponent);

        // Check Index
        if (acIndex >= 0 && acIndex < rowCount()) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), acIndex, acIndex);
            // Remove From Animation Components
            mAnimationComponents.removeAt(acIndex);
            // End Remove Rows
            endRemoveRows();

            // Emit Item Removed Signal
            emit itemRemoved(acIndex);

        } else {
            qWarning() << "AnimationComponentsModel::componentAboutToBeRemoved - Animations WAS NOT ADDED!!!";
        }
    }
}

//==============================================================================
// Row Count
//==============================================================================
int AnimationComponentsModel::rowCount(const QModelIndex& ) const
{
    return mAnimationComponents.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant AnimationComponentsModel::data(const QModelIndex& index, int role) const
{
    // Get Row Index
    int acmRow = index.row();
    // Check Row Index
    if (acmRow >= 0 && acmRow < rowCount()) {
        // Switch Role
        switch (role) {
            case EACMRComponentName: return mAnimationComponents[acmRow]->mName;
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> AnimationComponentsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    // Set Up Role Names
    rNames[EACMRComponentName]   = "acmName";

    // ...

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
AnimationComponentsModel::~AnimationComponentsModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "AnimationComponentsModel deleted.";
}
