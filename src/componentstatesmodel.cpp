#include <QDebug>
#include <QQmlEngine>

#include "componentstatesmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentStatesModel::ComponentStatesModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mNewState(NULL)
    , mDirty(false)
    , mSelectedIndex(-1)
{
    qDebug() << "ComponentStatesModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentStatesModel::init()
{
    //qDebug() << "ComponentStatesModel::init";
    // Load Component States
    loadComponentStates();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentStatesModel::clear()
{
    //qDebug() << "ComponentStatesModel::clear";
    // Begin Reset Model
    beginResetModel();

    // Iterate Through States
    while (mStates.count() > 0) {
        // Delete Last
        delete mStates.takeLast();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component States
//==============================================================================
void ComponentStatesModel::loadComponentStates()
{
    // Check Compoent Info
    if (!mComponent) {
        return;
    }

    //qDebug() << "ComponentStatesModel::loadComponentStates - name: " << mComponent->mName;

    // Begin Reset Model
    beginResetModel();

    // Get States Count
    int csCount = mComponent->mStates.count();

    // Iterate Through States
    for (int i=0; i<csCount; i++) {
        // Create New Component State
        ComponentState* newState = ComponentState::fromJSONObject(mComponent->mStates[i].toObject(), this);
        // Connect Signals
        connect(newState, SIGNAL(dirtyStateChanged(bool)), this, SLOT(componentStateDirtyChanged(bool)));
        // Append State
        mStates << newState;
    }

    // End Reset Model
    endResetModel();

    // Reset Dirty State
    setDirty(false);
}

//==============================================================================
// Save Component States
//==============================================================================
void ComponentStatesModel::saveComponentStates()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // Check Dirty State
    if (mDirty) {
        qDebug() <<  "ComponentStatesModel::saveComponentStates";

        // Set Component States
        mComponent->mStates = toJSONArray();
        // Set Dirty State
        mComponent->setDirty(true);

        // Reset Dirty State
        setDirty(false);
    }
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentStatesModel::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        //qDebug() << "ComponentStatesModel::setDirty - aDirty: " << aDirty;

        // Set Dirty
        mDirty = aDirty;

        // ...

        // Save Component States // TODO: Double Check If This is OK
        saveComponentStates();
    }
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentStatesModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentStatesModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Save Component States
        saveComponentStates();

        // Clear
        clear();

        //qDebug() << "ComponentStatesModel::setCurrentComponent - mName: " << (aComponent ? aComponent->mName : "NULL");

        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component States
        loadComponentStates();
    }
}

//==============================================================================
// Create New Empty State
//==============================================================================
ComponentState* ComponentStatesModel::createNewState()
{
    //qDebug() << "ComponentStatesModel::createNewState";

    // Check New State
    if (mNewState == NULL) {
        // Create new Empty State
        mNewState = new ComponentState("", "", this);
    }

    return mNewState;
}

//==============================================================================
// Discard New State
//==============================================================================
void ComponentStatesModel::discardNewState()
{
    // Check New State
    if (mNewState != NULL) {
        //qDebug() << "ComponentStatesModel::discardNewState";

        // Delete New State
        delete mNewState;
        // Reset New State
        mNewState = NULL;
    }
}

//==============================================================================
// Append State
//==============================================================================
void ComponentStatesModel::appendState(ComponentState* aState)
{
    // Check State
    if (aState) {
        // Connect Signals
        connect(aState, SIGNAL(dirtyStateChanged(bool)), this, SLOT(componentStateDirtyChanged(bool)));

        // Begin Insert rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        // Append To States
        mStates << aState;

        // End Insert Rows
        endInsertRows();

        // Check State
        if (aState == mNewState) {
            // Reset New State
            mNewState = NULL;
        }

        // Set Dirty State
        setDirty(true);

    }
}

//==============================================================================
// Add An Empty State
//==============================================================================
void ComponentStatesModel::addState(const QString& aStateName, const QString& aWhen)
{
    // Check Name
    if (!aStateName.isEmpty()) {
        //qDebug() << "ComponentStatesModel::addState - aStateName: " << aStateName << " - aWhen: " << aWhen;
        // Create New State
        ComponentState* newState = new ComponentState(aStateName, aWhen, this);
        // Connect Signals
        connect(newState, SIGNAL(dirtyStateChanged(bool)), this, SLOT(componentStateDirtyChanged(bool)));

        // Begin Insert rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append To States
        mStates << newState;
        // End Insert Rows
        endInsertRows();

        // Set Dirty State
        setDirty(true);
    }
}

//==============================================================================
// Set State Name
//==============================================================================
void ComponentStatesModel::setStateName(const int& aIndex, const QString& aStateName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        //qDebug() << "ComponentStatesModel::setStateName - aIndex: " << aIndex << " - aStateName: " << aStateName;
        // Set State Name
        mStates[aIndex]->setStateName(aStateName);
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
        // Set Dirty State
        setDirty(true);
    }
}

//==============================================================================
// Clear State
//==============================================================================
void ComponentStatesModel::clearState(const QString& aStateName)
{
    //qDebug() << "ComponentStatesModel::clearState - aStateName: " << aStateName;
    // Get Count
    int sCount = rowCount();
    // Iterate Through States
    for (int i=0; i<sCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];
        // Check Name
        if (cState->stateName() == aStateName) {
            // Clear State
            cState->clearState();
            // Emit Data Changed Signal
            emit dataChanged(index(i), index(i));
            // Set Dirty State
            setDirty(true);

            return;
        }
    }
}

//==============================================================================
// Remove State by Name
//==============================================================================
void ComponentStatesModel::removeState(const QString& aStateName)
{
    // Get Count
    int sCount = rowCount();
    // Iterate Through States
    for (int i=0; i<sCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];
        // Check Name
        if (cState->stateName() == aStateName) {
            //qDebug() << "ComponentStatesModel::removeState - aStateName: " << aStateName;
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), i, i);
            // Delete State
            delete mStates.takeAt(i);
            // End Remove Rows
            endRemoveRows();

            // Set Dirty State
            setDirty(true);

            return;
        }
    }
}

//==============================================================================
// Remove State by Index
//==============================================================================
void ComponentStatesModel::removeState(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        //qDebug() << "ComponentStatesModel::removeState - aIndex: " << aIndex;
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete State
        delete mStates.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();

        // Set Dirty State
        setDirty(true);
    }
}

//==============================================================================
// Add Property Change
//==============================================================================
void ComponentStatesModel::addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QString& aValue)
{
    // Get Count
    int smCount = rowCount();

    // Iterate Through States
    for (int i=0; i<smCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];
        // Check Name
        if (cState->stateName() == aStateName) {
            // Create New Property Change
            ComponentPropertyChange* newPropertyChange = new ComponentPropertyChange(aTarget, aProperty, aValue, cState);
            // Add Property Change
            cState->appendPropertyChange(newPropertyChange);
            // Emit Data Changed Signal
            emit dataChanged(index(i), index(i));

            // Set Dirty State
            setDirty(true);
        }
    }
}

//==============================================================================
// Set Property Change
//==============================================================================
void ComponentStatesModel::setPropertyChange(const QString& aStateName, const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue)
{
    // Get Count
    int smCount = rowCount();

    // Iterate Through States
    for (int i=0; i<smCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];
        // Check Name
        if (cState->stateName() == aStateName) {
            // Set Property Change
            cState->setPropertyChange(aIndex, aTarget, aProperty, aValue);
            // Emit Data Changed Signal
            emit dataChanged(index(i), index(i));

            // Set Dirty State
            setDirty(true);

            return;
        }
    }
}

//==============================================================================
// Remove Property Change
//==============================================================================
void ComponentStatesModel::removePropertyChange(const QString& aStateName, const int& aIndex)
{
    // Get Count
    int smCount = rowCount();

    // Iterate Through States
    for (int i=0; i<smCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];

        // Check Name
        if (cState->stateName() == aStateName) {
            // Remove Property change
            cState->removePropertyChange(aIndex);
            // Emit Data Changed Signal
            emit dataChanged(index(i), index(i));

            // Set Dirty State
            setDirty(true);

            return;
        }
    }
}

//==============================================================================
// To JSON Array
//==============================================================================
QJsonArray ComponentStatesModel::toJSONArray()
{
    // Init New JSON Array
    QJsonArray newJSONArray;

    // Get Count
    int smCount = rowCount();

    // Iterate Through States
    for (int i=0; i<smCount; i++) {
        // Append State
        newJSONArray << mStates[i]->toJSONObject();
    }

    return newJSONArray;
}

//==============================================================================
// Component State Dirty Changed
//==============================================================================
void ComponentStatesModel::componentStateDirtyChanged(const bool& aDirty)
{
    // Check Dirty State
    if (aDirty) {
        // Get Sender Component State
        ComponentState* componentState = static_cast<ComponentState*>(sender());
        // Check Sender
        if (componentState) {
            // Set Dirty
            setDirty(true);

            // ...

            // Reset Dirty
            componentState->setDirty(false);
        }
    }
}

//==============================================================================
// Get State By Name
//==============================================================================
ComponentState* ComponentStatesModel::getState(const QString& aStateName)
{
    // Get Count
    int smCount = rowCount();
    // Iterate Through States
    for (int i=0; i<smCount; i++) {
        // Get State
        ComponentState* cState = mStates[i];
        // Check Name
        if (cState->stateName() == aStateName) {
            // Set Selected Index
            mSelectedIndex = i;

            return cState;
        }
    }

    return NULL;
}

//==============================================================================
// Get State By Index
//==============================================================================
ComponentState* ComponentStatesModel::getState(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Set Selected Index
        mSelectedIndex = aIndex;

        return mStates[aIndex];
    }

    return NULL;
}

//==============================================================================
// Update Selected State
//==============================================================================
void ComponentStatesModel::updateSelectedState()
{
    // Check Selected Index
    if (mSelectedIndex >= 0 && mSelectedIndex < rowCount()) {

        // Get Selected State
        ComponentState* componentState = mStates[mSelectedIndex];

        // Check Selected State
        if (componentState && componentState->mDirty) {
            // Emit Data Changed Signal
            emit dataChanged(index(mSelectedIndex), index(mSelectedIndex));

            // Set Dirty State -> Save Component States
            setDirty(true);

            // ...
        }
    }
}

//==============================================================================
// Check If State Valid
//==============================================================================
bool ComponentStatesModel::stateValid(const QString& aName, const bool& aNewState)
{
    // Check Name
    if (aName.isEmpty()) {
        return false;
    }

    // Check New State
    if (aNewState) {
        // Get State By Name
        ComponentState* componentState = getState(aName);
        // Check State
        if (componentState) {
            // Already Exists
            return false;
        }
    }

    // ...

    return true;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentStatesModel::rowCount(const QModelIndex&) const
{
    return mStates.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentStatesModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int smRow = index.row();

    // Check Row
    if (smRow >= 0 && smRow < rowCount()) {
        // Switch Role
        switch (role) {
            case ESMRName:      return mStates[smRow]->stateName();
            case ESMRWhen:      return mStates[smRow]->stateWhen();
            case ESMRChanges:   return (mStates[smRow]->rowCount() > 0 ? "{...}" : "");
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentStatesModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    rNames[ESMRName]    = "stateName";
    rNames[ESMRWhen]    = "stateWhen";
    rNames[ESMRChanges] = "stateChanges";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentStatesModel::~ComponentStatesModel()
{
    // Clear
    clear();

    // ...

    //qDebug() << "ComponentStatesModel deleted.";
}






//==============================================================================
// From JSON Object
//==============================================================================
ComponentState* ComponentState::fromJSONObject(const QJsonObject& aObject, ComponentStatesModel* aModel)
{
    // Init New Component State
    ComponentState* newComponentState = new ComponentState(aObject[JSON_KEY_COMPONENT_STATE_NAME].toString(),
                                                           aObject[JSON_KEY_COMPONENT_STATE_WHEN].toString(),
                                                           aModel);

    // Get Property Changes Array
    QJsonArray pcJSONArray = aObject[JSON_KEY_COMPONENT_STATE_PROPERTY_CHANGES].toArray();
    // Get Count
    int pcCount = pcJSONArray.count();
    // Iterate Through Property Changes
    for (int i=0; i<pcCount; i++) {
        // Append Property Change
        newComponentState->appendPropertyChange(ComponentPropertyChange::fromJSONObject(pcJSONArray[i].toObject(), newComponentState));
    }

    return newComponentState;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentState::ComponentState(const QString& aName, const QString& aWhen, ComponentStatesModel* aModel, QObject* aParent)
    : QAbstractListModel(aParent)
    , mStatesModel(aModel)
    , mName(aName)
    , mWhen(aWhen)
    , mNewPropertyChange(NULL)
    , mDirty(false)
    , mSelectedIndex(-1)
{
    // Set Ownership
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    // ...
}

//==============================================================================
// Create New Property Change
//==============================================================================
ComponentPropertyChange* ComponentState::createNewPropertyChange()
{
    // Reset Selected Index
    mSelectedIndex = -1;

    // Check New Property Change
    if (mNewPropertyChange == NULL) {
        // Create New Empty Property Change
        mNewPropertyChange = new ComponentPropertyChange("", "", "", this);
    }

    return mNewPropertyChange;
}

//==============================================================================
// Discard New Property Change
//==============================================================================
void ComponentState::discardNewPropertyChange()
{
    // Check New Property Change
    if (mNewPropertyChange != NULL) {
        // Delete New Property Change
        delete mNewPropertyChange;
        // Reset New Property Change
        mNewPropertyChange = NULL;
    }
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentState::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        //qDebug() << "ComponentState::setDirty - aDirty: " << aDirty;
        // Set Dirty State
        mDirty = aDirty;
        // Emit Dirty State Changed Signal
        //emit dirtyStateChanged(mDirty);
    }
}

//==============================================================================
// Get Property Change by Index
//==============================================================================
ComponentPropertyChange* ComponentState::getPropertyChange(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {

        // Set Selected Index
        mSelectedIndex = aIndex;

        return mPropertyChanges[aIndex];
    }

    return NULL;
}

//==============================================================================
// Update Selected Property Change
//==============================================================================
void ComponentState::updateSelectedPropertyChange()
{
    // Check Selected Index
    if (mSelectedIndex >= 0 && mSelectedIndex < rowCount()) {
        //qDebug() << "ComponentState::updateSelectedPropertyChange - mSelectedIndex: " << mSelectedIndex;

        // Get Property Change
        ComponentPropertyChange* propertyChange = mPropertyChanges[mSelectedIndex];

        // Check Property Change Dirty State
        if (propertyChange && propertyChange->mDirty) {
            // Emit Data Changed Signal
            emit dataChanged(index(mSelectedIndex), index(mSelectedIndex));
            // Set Dirty
            setDirty(true);

            // ...
        }
    }
}

//==============================================================================
// Get State Name
//==============================================================================
QString ComponentState::stateName()
{
    return mName;
}

//==============================================================================
// Set State Name
//==============================================================================
void ComponentState::setStateName(const QString& aName)
{
    // Check Name
    if (mName != aName) {
        // Set Name
        mName = aName;
        // Emit State Name Changed Signal
        emit stateNameChanged(mName);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get When Trigger
//==============================================================================
QString ComponentState::stateWhen()
{
    return mWhen;
}

//==============================================================================
// Set When Trigger
//==============================================================================
void ComponentState::setStateWhen(const QString& aWhen)
{
    // Check State When Trigger
    if (mWhen != aWhen) {
        // Set When Trigger
        mWhen = aWhen;
        // Emit State When Trigger Changed Signal
        emit stateWhenChanged(mWhen);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Has Children
//==============================================================================
bool ComponentState::hasPropertyChanges()
{
    return mPropertyChanges.count() > 0;
}

//==============================================================================
// Append Property Change
//==============================================================================
void ComponentState::appendPropertyChange(ComponentPropertyChange* aPropertyChange)
{
    // Get Index
    int pcIndex = mPropertyChanges.indexOf(aPropertyChange);
    // Check Index
    if (pcIndex >= 0) {
        // Already Added
        return;
    }

    //qDebug() << "ComponentState::appendPropertyChange";

    // Check New Property Change
    if (mNewPropertyChange == aPropertyChange) {
        // Reset New Property Change
        mNewPropertyChange = NULL;
    }

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // Append Property Change
    mPropertyChanges << aPropertyChange;
    // End Insert Rows
    endInsertRows();

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Insert Property Change
//==============================================================================
void ComponentState::insertPropertyChange(const int& aIndex, ComponentPropertyChange* aPropertyChange)
{
    // Get Index
    int pcIndex = mPropertyChanges.indexOf(aPropertyChange);
    // Check Index
    if (pcIndex >= 0) {
        // Already Added
        return;
    }

    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() - 1) {
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), aIndex, aIndex);
        // Insert
        mPropertyChanges.insert(aIndex, aPropertyChange);
    } else {
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Property Change
        mPropertyChanges << aPropertyChange;
    }

    // End Insert Rows
    endInsertRows();

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Remove Property Change
//==============================================================================
void ComponentState::removePropertyChange(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Property Change
        delete mPropertyChanges.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();

        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Set Property Change
//==============================================================================
void ComponentState::setPropertyChange(const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Set Property Change
        mPropertyChanges[aIndex]->setPropertyChangeTarget(aTarget);
        mPropertyChanges[aIndex]->setPropertyChangeProperty(aProperty);
        mPropertyChanges[aIndex]->setPropertyChangeValue(aValue);

        // Emit Data Changed
        emit dataChanged(index(aIndex), index(aIndex));

        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Clear State - Clear Property Changes
//==============================================================================
void ComponentState::clearState()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Property Changes
    while (mPropertyChanges.count() > 0) {
        // Delete Last
        delete mPropertyChanges.takeLast();
    }

    // End Reset Model
    endResetModel();

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentState::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Set Up Data
    newJSONObject[JSON_KEY_COMPONENT_STATE_NAME] = mName;

    // Check When
    if (!mWhen.isEmpty()) {
        // Set When
        newJSONObject[JSON_KEY_COMPONENT_STATE_WHEN] = mWhen;
    }

    QJsonArray newPCJSONArray;

    // Get Property Changes Count
    int pcCount = rowCount();

    // Check Property Changes Count
    if (pcCount > 0) {
        // Iterate Through Property Changes
        for (int i=0; i<pcCount; i++) {
            // Get Property Change
            ComponentPropertyChange* propertyChange = mPropertyChanges[i];
            // Add Property Change
            newPCJSONArray << propertyChange->toJSONObject();
        }

        // Set Property Changes
        newJSONObject[JSON_KEY_COMPONENT_STATE_PROPERTY_CHANGES] = newPCJSONArray;
    }

    return newJSONObject;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentState::rowCount(const QModelIndex& ) const
{
    return mPropertyChanges.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentState::data(const QModelIndex& index, int role) const
{
    // Get Row
    int pcRow = index.row();

    // Check Row
    if (pcRow >= 0 && pcRow < rowCount()) {
        // Switch Role
        switch (role) {
            case ESMRTarget:    return mPropertyChanges[pcRow]->mTarget;
            case ESMRProperty:  return mPropertyChanges[pcRow]->mProperty;
            case ESMRValue:     return mPropertyChanges[pcRow]->mValue;
        }
    }

    // ...

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentState::roleNames() const
{
    // Init New Role Names
    QHash<int, QByteArray> rNames;

    rNames[ESMRTarget]      = "pcTarget";
    rNames[ESMRProperty]    = "pcProperty";
    rNames[ESMRValue]       = "pcValue";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentState::~ComponentState()
{
    // Clear State
    clearState();

    // ...
}







//==============================================================================
// From JSON Object
//==============================================================================
ComponentPropertyChange* ComponentPropertyChange::fromJSONObject(const QJsonObject& aObject, ComponentState* aState)
{
    // Create New Component Property Change
    ComponentPropertyChange* newPropertyChange = new ComponentPropertyChange(aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET].toString(),
                                                                             aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY].toString(),
                                                                             aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE].toString(),
                                                                             aState);



    return newPropertyChange;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertyChange::ComponentPropertyChange(const QString& aTarget,
                                                 const QString& aProperty,
                                                 const QString& aValue,
                                                 ComponentState* aState,
                                                 QObject* aParent)
    : QObject(aParent)
    , mState(aState)
    , mTarget(aTarget)
    , mProperty(aProperty)
    , mValue(aValue)
    , mDirty(false)
{
    // Set Ownership
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    // ...
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentPropertyChange::setDirty(const bool& aDirty)
{
    // Check Dirty State
    if (mDirty != aDirty) {
        // Set Dirty State
        mDirty = aDirty;

        // ...
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentPropertyChange::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Set Up New JSON Object
    newJSONObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET] = mTarget;
    newJSONObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY] = mProperty;
    newJSONObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE] = mValue;

    return newJSONObject;
}

//==============================================================================
// Get Target
//==============================================================================
QString ComponentPropertyChange::propertyChangeTarget()
{
    return mTarget;
}

//==============================================================================
// Set Target
//==============================================================================
void ComponentPropertyChange::setPropertyChangeTarget(const QString& aTarget)
{
    // Check Target
    if (mTarget != aTarget) {
        //qDebug() << "ComponentPropertyChange::setPropertyChangeTarget - aTarget: " << aTarget;
        // Set Target
        mTarget = aTarget;
        // Emit Target changed Signal
        emit propertyChangeTargetChanged(mTarget);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Property
//==============================================================================
QString ComponentPropertyChange::propertyChangeProperty()
{
    return mProperty;
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentPropertyChange::setPropertyChangeProperty(const QString& aProperty)
{
    // Check Property
    if (mProperty != aProperty) {
        //qDebug() << "ComponentPropertyChange::setPropertyChangeProperty - aProperty: " << aProperty;
        // Set Property
        mProperty = aProperty;
        // Emit Property Changed Signal
        emit propertyChangePropertyChanged(mProperty);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Value
//==============================================================================
QString ComponentPropertyChange::propertyChangeValue()
{
    return mValue;
}

//==============================================================================
// Set Value
//==============================================================================
void ComponentPropertyChange::setPropertyChangeValue(const QString& aValue)
{
    // Check Value
    if (mValue != aValue) {
        //qDebug() << "ComponentPropertyChange::setPropertyChangeValue - aValue: " << aValue;
        // Set Value
        mValue = aValue;
        // Emit Value Changed Signal
        emit propertyChangeValueChanged(mValue);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertyChange::~ComponentPropertyChange()
{
    // ...
}

