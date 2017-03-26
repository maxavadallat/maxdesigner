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
void ComponentSignalsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Signals
    while (mSignals.count() > 0) {
        // Delete Last
        delete mSignals.takeLast();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Signals
//==============================================================================
void ComponentSignalsModel::loadComponentSignals(const QJsonArray& aArray)
{
    // Clear
    clear();

    // Get Array Count
    int csCount = aArray.count();

    // Iterate Through Array
    for (int i=0; i<csCount; i++) {
        // Append Signal
        appendSignal(ComponentSignal::fromJSONObject(aArray[i].toObject()));
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
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Signals

    }
}

//==============================================================================
// Append Signal
//==============================================================================
void ComponentSignalsModel::appendSignal(ComponentSignal* aSignal)
{
    // Check Signal
    if (!aSignal) {
        return;
    }

    // Get Index
    int sIndex = mSignals.indexOf(aSignal);
    // Check Idnex
    if (sIndex >= 0) {
        return;
    }

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // Append Signal
    mSignals << aSignal;
    // End Insert Rows
    endInsertRows();
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
// To JSON Array
//==============================================================================
QJsonArray ComponentSignalsModel::toJSONArray()
{
    // Init New Array
    QJsonArray newArray;

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
// To JSON Object
//==============================================================================
QJsonObject ComponentSignal::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newObject;

    // ...

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
