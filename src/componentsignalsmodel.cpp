#include <QDebug>

#include "componentsignalsmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentSignalsModel::ComponentSignalsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentSignalsModel::init()
{
    // Load Component Signals

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentSignalsModel::clear(const bool& aEndReset)
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Signals
    while (mSignals.count() > 0) {
        // Delete Last
        delete mSignals.takeLast();
    }

    // Check End Reset
    if (aEndReset) {
        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Load Component Signals
//==============================================================================
void ComponentSignalsModel::loadComponentSignals()
{
    // Clear
    clear();

    // Check Component
    if (mComponent) {
        // Get Signals Count
        int sCount = mComponent->mSignals.count();

        // Iterate Through Signals
        for (int i=0; i<sCount; i++) {
            // Append Signal
            appendSignal(ComponentSignal::fromJSONObject(mComponent->mSignals[i].toObject()));
        }
    }
}

//==============================================================================
// Save Component Signals
//==============================================================================
void ComponentSignalsModel::saveComponentSignals()
{
    // Check Current Component
    if (mComponent) {
        // Set Signals
        mComponent->mSignals = toJSONArray();
    }
}

//==============================================================================
// Clear Component Signals
//==============================================================================
void ComponentSignalsModel::clearComponentSignals()
{
    // Check Component
    if (mComponent) {
        // Iterate Through Signals
        while (mComponent->mSignals.count() > 0) {
            // Remove Last
            mComponent->mSignals.removeLast();
        }
    }
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentSignalsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentSignalsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Save Previous Component Signals
        saveComponentSignals();
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load New Component Signals
        loadComponentSignals();
    }
}


//==============================================================================
// Add Signal
//==============================================================================
void ComponentSignalsModel::addSignal(const QString& aName, const QStringList& aParameters)
{
    // Check If Signal Valid
    if (signalValid(aName)) {
        // Append New Signal
        appendSignal(new ComponentSignal(aName, aParameters));
    }
}

//==============================================================================
// Append Signal
//==============================================================================
void ComponentSignalsModel::appendSignal(ComponentSignal* aSignal)
{
    // Check Signal
    if (aSignal) {
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Signal
        mSignals << aSignal;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Remove Signal
//==============================================================================
void ComponentSignalsModel::removeSignal(const QString& aName)
{
    // Get Signals Count
    int sCount = mSignals.count();
    // Iterate Through Signals
    for (int i=0; i<sCount; i++) {
        // Get Signal
        ComponentSignal* cSignal = mSignals[i];
        // Check Signal
        if (cSignal && cSignal->mName == aName) {
            // Begin Remove rows
            beginRemoveRows(QModelIndex(), i, i);
            // Remove Signal
            delete mSignals.takeAt(i);
            // End Remove Rows
            endRemoveRows();

            return;
        }
    }
}

//==============================================================================
// Remove Signal
//==============================================================================
void ComponentSignalsModel::removeSignal(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Signal
        delete mSignals.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Rename Signal
//==============================================================================
void ComponentSignalsModel::renameSignal(const int& aIndex, const QString& aName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() && signalValid(aName)) {
        // Set Signal Name
        mSignals[aIndex]->mName = aName;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Check If Signal Valid
//==============================================================================
bool ComponentSignalsModel::signalValid(const QString& aName)
{
    // Check Signal Name
    if (!aName.isEmpty()) {
        // Get Signals Count
        int sCount = rowCount();
        // Iterate Through Signals
        for (int i=0; i<sCount; i++) {
            // Check Signal Name
            if (mSignals[i]->mName == aName) {
                return false;
            }
        }

        return true;
    }

    return false;
}

//==============================================================================
// Create New Signal
//==============================================================================
ComponentSignal* ComponentSignalsModel::createNewSignal()
{
    return new ComponentSignal("");
}

//==============================================================================
// Get/Select Signal
//==============================================================================
ComponentSignal* ComponentSignalsModel::selectSignal(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mSignals[aIndex];
    }

    return NULL;
}

//==============================================================================
// Discard New Signal
//==============================================================================
void ComponentSignalsModel::discardNewSignal(ComponentSignal* aSignal)
{
    // Check Signal
    if (aSignal) {
        // Delete Signal
        delete aSignal;
    }
}

//==============================================================================
// To JSON Array
//==============================================================================
QJsonArray ComponentSignalsModel::toJSONArray()
{
    // Init New Array
    QJsonArray newArray;

    // Get Signals Count
    int sCount = mSignals.count();
    // Iterate Through Signals
    for (int i=0; i<sCount; i++) {
        // Get Signal
        ComponentSignal* cSignal = mSignals[i];
        // Append To Array
        newArray << cSignal->toJSONObject();
    }

    // ...

    return newArray;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentSignalsModel::rowCount(const QModelIndex& ) const
{
    return mSignals.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentSignalsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int smRow = index.row();

    // Check Index
    if (smRow >= 0 && smRow < rowCount()) {
        // Switch Role
        switch (role) {
            case ESMRName:          return mSignals[smRow]->signalName();
            case ESMRParameters:    return mSignals[smRow]->signalParameters();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentSignalsModel::roleNames() const
{
    QHash<int, QByteArray> rNames;

    rNames[ESMRName]        = "signalName";
    rNames[ESMRParameters]  = "signalParameters";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSignalsModel::~ComponentSignalsModel()
{
    // Clear
    clear();

    // ...
}












//==============================================================================
// From JSON Object
//==============================================================================
ComponentSignal* ComponentSignal::fromJSONObject(const QJsonObject& aObject)
{
    // Create New Signal
    ComponentSignal* newSignal = new ComponentSignal(aObject[JSON_KEY_COMPONENT_SIGNAL_NAME].toString(),
                                                     aObject[JSON_KEY_COMPONENT_SIGNAL_PARAMETERS].toString().split(","));

    // ...

    return newSignal;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentSignal::ComponentSignal(const QString& aName, const QStringList& aParameters, QObject* aParent)
    : QObject(aParent)
    , mName(aName)
    , mParameters(aParameters)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentSignal::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentSignal::clear()
{
    // Clear Parameters
    mParameters.clear();
}

//==============================================================================
// Get Signal Name
//==============================================================================
QString ComponentSignal::signalName()
{
    return mName;
}

//==============================================================================
// Set Signal Name
//==============================================================================
void ComponentSignal::setSignalName(const QString& aName)
{
    // Check Signal Name
    if (mName != aName) {
        // Set Signal Name
        mName = aName;
        // Emit Signal Name Changed Signal
        emit signalNameChanged(mName);
    }
}

//==============================================================================
// Get Signal Parameters
//==============================================================================
QStringList ComponentSignal::signalParameters()
{
    return mParameters;
}

//==============================================================================
// Set Signal Parameters
//==============================================================================
void ComponentSignal::setSignalParameters(const QStringList& aParameters)
{
    // Check Signal Parameters
    if (mParameters != aParameters) {
        // Set Parameters
        mParameters = aParameters;
        // Emit Signal Parameters Changed Signal
        emit signalParametersChanged(mParameters);
    }
}

//==============================================================================
// Add Signal Parameter
//==============================================================================
void ComponentSignal::addSignalParameter(const QString& aParameter)
{
    // Check Parameters
    if (mParameters.indexOf(aParameter) < 0) {
        // Add Parameter
        mParameters << aParameter;
        // Emit Signal Parameters Changed Signal
        emit signalParametersChanged(mParameters);
    }
}

//==============================================================================
// Remove Signal Parameter
//==============================================================================
void ComponentSignal::removeSignalParameter(const int& aIndex)
{
    // Check Parameters
    if (aIndex >= 0 && aIndex < mParameters.count()) {
        // Remove Parameter
        mParameters.removeAt(aIndex);
        // Emit Signal Parameters Changed Signal
        emit signalParametersChanged(mParameters);
    }
}

//==============================================================================
// Check If Parameter Valid
//==============================================================================
bool ComponentSignal::parameterValid(const QString& aParameter)
{
    // Check Parameter
    if (!aParameter.isEmpty()) {
        return (mParameters.indexOf(aParameter) < 0);
    }

    return false;
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentSignal::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newObject;

    // Set Signal Name
    newObject[JSON_KEY_COMPONENT_SIGNAL_NAME] = mName;
    // Set Parameters
    newObject[JSON_KEY_COMPONENT_SIGNAL_PARAMETERS] = mParameters.join(',');

    return newObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSignal::~ComponentSignal()
{
    // Clear
    clear();
}
