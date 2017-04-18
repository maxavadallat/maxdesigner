#include <QDebug>
#include <QJsonObject>

#include "componentstatesmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentStatesModel::ComponentStatesModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentStatesModel::init()
{
    // Load Component States
    loadComponentStates();
}

//==============================================================================
// Clear
//==============================================================================
void ComponentStatesModel::clear()
{
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
    // Clear
    clear();

    // Check Compoent Info
    if (!mComponent) {
        return;
    }

    //qDebug() << "ComponentStatesModel::loadComponentStates - name: " << mComponent->mName;

    // Begin Reset Model
    beginResetModel();

    // ...

    // End Reset Model
    endResetModel();
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

    // ...
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
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load Component States
        loadComponentStates();
    }
}

//==============================================================================
// Add State
//==============================================================================
void ComponentStatesModel::addState(const QString& aStateName, const QString& aWhen)
{
    // Check Name
    if (!aStateName.isEmpty()) {
        // Create New State
        ComponentState* newState = new ComponentState(aStateName, aWhen);

        // Begin Insert rows
        beginInsertRows(QModelIndex(), rowCount() - 1, rowCount() -1);
        // Append To States
        mStates << newState;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Set State Name
//==============================================================================
void ComponentStatesModel::setStateName(const int& aIndex, const QString& aStateName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Set State Name
        mStates[aIndex]->setStateName(aStateName);
        // Emit Data Changed
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Clear State
//==============================================================================
void ComponentStatesModel::clearState(const QString& aStateName)
{
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

            return;
        }
    }
}

//==============================================================================
// Remove State
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
            // Delete State
            delete mStates.takeAt(i);

            return;
        }
    }
}

//==============================================================================
// Remove State
//==============================================================================
void ComponentStatesModel::removeState(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Delete State
        delete mStates.takeAt(aIndex);
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
            ComponentPropertyChange* newPropertyChange = new ComponentPropertyChange(aTarget, aProperty, aValue);
            // Add Property Change
            cState->appendPropertyChange(newPropertyChange);
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

            // Emit Data Changed
            //emit dataChanged(index(i), index(i));

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

            // Emit Data Changed
            //emit dataChanged(index(i), index(i));

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
        return mStates[aIndex];
    }

    return NULL;
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
            //case ESMRChanges:   return mStates[smRow];
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
}






//==============================================================================
// From JSON Object
//==============================================================================
ComponentState* ComponentState::fromJSONObject(const QJsonObject& aObject)
{
    // Init New Component State
    ComponentState* newComponentState = new ComponentState(aObject[JSON_KEY_COMPONENT_STATE_NAME].toString());

    // ...

    return newComponentState;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentState::ComponentState(const QString& aName, const QString& aWhen, QObject* aParent)
    : QAbstractListModel(aParent)
    , mName(aName)
    , mWhen(aWhen)
{
    // ...
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

    // Append Property Change
    mPropertyChanges << aPropertyChange;
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
        // Insert
        mPropertyChanges.insert(aIndex, aPropertyChange);
    } else {
        // Append Property Change
        mPropertyChanges << aPropertyChange;
    }
}

//==============================================================================
// Remove Property Change
//==============================================================================
void ComponentState::removePropertyChange(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Delete Property Change
        delete mPropertyChanges.takeAt(aIndex);
    }
}

//==============================================================================
// Set Property Change
//==============================================================================
void ComponentState::setPropertyChange(const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        mPropertyChanges[aIndex]->setPropertyChangeTarget(aTarget);
        mPropertyChanges[aIndex]->setPropertyChangeProperty(aProperty);
        mPropertyChanges[aIndex]->setPropertyChangeValue(aValue);
    }
}

//==============================================================================
// Clear State
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
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentState::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Set Up Data

    // ...

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
            case ESMRTarget:    mPropertyChanges[pcRow]->propertyChangeTarget();
            case ESMRProperty:  mPropertyChanges[pcRow]->propertyChangeProperty();
            case ESMRValue:     mPropertyChanges[pcRow]->propertyChangeValue();
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
ComponentPropertyChange* ComponentPropertyChange::fromJSONObject(const QJsonObject& aObject)
{
    // Create New Component Property Change
    ComponentPropertyChange* newPropertyChange = new ComponentPropertyChange(aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET].toString(),
                                                                             aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY].toString(),
                                                                             aObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE].toString());



    return newPropertyChange;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertyChange::ComponentPropertyChange(const QString& aTarget,
                                                 const QString& aProperty,
                                                 const QString& aValue,
                                                 QObject* aParent)
    : QObject(aParent)
    , mTarget(aTarget)
    , mProperty(aProperty)
    , mValue(aValue)
{
    // ...
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
        // Set Target
        mTarget = aTarget;
        // Emit Target changed Signal
        emit propertyChangeTargetChanged(mTarget);
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
        // Set Property
        mProperty = aProperty;
        // Emit Property Changed Signal
        emit propertyChangePropertyChanged(mProperty);
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
        // Set Value
        mValue = aValue;
        // Emit Value Changed Signal
        emit propertyChangeValueChanged(mValue);
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertyChange::~ComponentPropertyChange()
{
    // ...
}

