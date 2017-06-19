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
ComponentTransitionsModel::ComponentTransitionsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mNewTransition(NULL)
    , mCurrentTransition(NULL)
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
void ComponentTransitionsModel::selectTransition(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Get Transition
        ComponentTransition* transition = mTransitions[aIndex];
        // Set Current Transition
        setCurrentTransition(transition);
    }
}

//==============================================================================
// Create New Transition
//==============================================================================
ComponentTransition* ComponentTransitionsModel::createNewTransition()
{
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

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        mTransitions << aTransition;
        // End Insert Rows
        endInsertRows();

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
            // Append Transition
            mTransitions << ComponentTransition::fromJSONObject(this, mComponent->mTransitions[i].toObject());
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
        // Set Dirty State
        mDirty = aDirty;

        // Check Current Component
        if (mComponent && mDirty) {
            // Set Dirty
            mComponent->setDirty(true);
        }
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

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // Append Transition
    mTransitions << newTransition;
    // End Insert Rows
    endInsertRows();
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
        // Delete Transition
        delete mTransitions.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
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
    , mFromState(aFromState)
    , mToState(aToState)
    , mNewNode(NULL)
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
// Get Node Count
//==============================================================================
int ComponentTransition::nodesCount()
{
    return mNodes.count();
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
// Create New Node
//==============================================================================
ComponentInfo* ComponentTransition::createNewNode(const QString& aComponentName)
{
    // Check New Node
    if (!mNewNode) {
        qDebug() << "ComponentTransition::createNewNode - aComponentName: " << aComponentName;

        // ...

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
        // Delete New Node
        delete mNewNode;
        mNewNode = NULL;
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentTransition::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Check From State
    if (!mFromState.isNull()) {
        // Check If Empty
        if (mFromState.isEmpty()) {
            // Set From State
            setFromState(QString("\"\""));
        }

        // Set From State
        newJSONObject[JSON_KEY_COMPONENT_TRANSITION_FROM] = mFromState;
    }

    // Check To State
    if (!mToState.isNull()) {
        // Check If Empty
        if (mToState.isEmpty()) {
            // Set To State
            setToState(QString("\"\""));
        }

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
    if (!aNodes.isEmpty()) {

        // ...

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

    // Check Parent Node
    if (aParentNode) {
        // Append Node
        aParentNode->addChild(aNode);
    } else {
        // Append Node
        mNodes << aNode;

        // Emit Nodes Count Changed Signal
        emit nodeCountChanged(mNodes.count());
    }
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
}

//==============================================================================
// Move Node
//==============================================================================
void ComponentTransition::moveNode(ComponentInfo* aParentNode, const int& aIndex, ComponentInfo* aTargetNode, const int& aTargetIndex)
{
    qDebug() << "ComponentTransition::moveNode - aParentNode: " << aParentNode << " - aIndex: " << aIndex << " - aTargetNode: " << aTargetNode << " - aTargetIndex: " << aTargetIndex;

    // ...
}

//==============================================================================
// Remove Node
//==============================================================================
void ComponentTransition::removeNode(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mNodes.count()) {
        // Remove Node
        delete mNodes.takeAt(aIndex);

        // Emit Nodes Count Changed Signal
        emit nodeCountChanged(mNodes.count());
    }
}

//==============================================================================
// Clear
//==============================================================================
void ComponentTransition::clear()
{
    // Iterate Through Nodes
    while (mNodes.count() > 0) {
        // Delete Last
        delete mNodes.takeLast();
    }

    // Emit Nodes Count Changed Signal
    emit nodeCountChanged(mNodes.count());
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
    // Begin Reset Model
    beginResetModel();
    // Clear Anim Components
    mAnimationComponents.clear();
    // End Reset Model
    endResetModel();
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
