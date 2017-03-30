#include "componentfunctionsmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentFunctionsModel::ComponentFunctionsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentFunctionsModel::init()
{
    // Load Compoennt Functions
    loadComponentFunctions();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentFunctionsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Iterate Through Functions
    while (mFunctions.count() > 0) {
        // Delete Last
        delete mFunctions.takeLast();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Functions
//==============================================================================
void ComponentFunctionsModel::loadComponentFunctions()
{
    // Clear
    clear();

    // ...
}

//==============================================================================
// Save Component Functions
//==============================================================================
void ComponentFunctionsModel::saveComponentFunctions()
{
    // ...
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentFunctionsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentFunctionsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Functions
        loadComponentFunctions();
    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentFunctionsModel::rowCount(const QModelIndex& ) const
{
    return mFunctions.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentFunctionsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int fmRow = index.row();

    // Check Row
    if (fmRow >= 0 && fmRow < rowCount()) {
        // Switch Role
        switch (role) {
            default:
            case FMRNameRole:   return mFunctions[fmRow]->functionName();
            case FMRParamsRole: return mFunctions[fmRow]->functionParameters();
            case FMRSoureRole:  return mFunctions[fmRow]->functionSource();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentFunctionsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    rNames[FMRNameRole]     = "fName";
    rNames[FMRParamsRole]   = "fParams";
    rNames[FMRSoureRole]    = "fSource";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentFunctionsModel::~ComponentFunctionsModel()
{
    // Clear
    clear();

    // ...
}

















//==============================================================================
// Constructor
//==============================================================================
ComponentFunction::ComponentFunction(QObject* aParent)
    : QObject(aParent)
{

}

//==============================================================================
// Get Function Name
//==============================================================================
QString ComponentFunction::functionName()
{
    return mName;
}

//==============================================================================
// Set Function Name
//==============================================================================
void ComponentFunction::setFunctionName(const QString& aFunctionName)
{
    // Check Function Name
    if (mName != aFunctionName) {
        // Set Name
        mName = aFunctionName;
        // Emit Function Name Changed Signal
        emit functionNameChanged(mName);
    }
}

//==============================================================================
// Get Function Parameters
//==============================================================================
QStringList ComponentFunction::functionParameters()
{
    return mParameters;
}

//==============================================================================
// Set Function Parameters
//==============================================================================
void ComponentFunction::setFunctionParameters(const QStringList& aParameters)
{
    // Check Parameters
    if (mParameters != aParameters) {
        // Set Parameters
        mParameters = aParameters;
        // Emit Parameters Changed Signal
        emit functionParametersChanged(mParameters);
    }
}

//==============================================================================
// Get Function Source
//==============================================================================
QString ComponentFunction::functionSource()
{
    return mSource;
}

//==============================================================================
// Set Function Source
//==============================================================================
void ComponentFunction::setFunctionSource(const QString& aSource)
{
    // Check Source
    if (mSource != aSource) {
        // Set Source
        mSource = aSource;
        // Emit Source Changed Signal
        emit functionSourceChanged(mSource);
    }
}

//==============================================================================
// Insert Parameter
//==============================================================================
void ComponentFunction::insertParameter(const int& aIndex, const QString& aParameter)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mParameters.count()) {
        // Insert
        mParameters.insert(aIndex, aParameter);
        // Emit Parameters Changed
        emit functionParametersChanged(mParameters);
    } else {
        // Append
        appendParameter(aParameter);
    }
}

//==============================================================================
// Append Parameter
//==============================================================================
void ComponentFunction::appendParameter(const QString& aParameter)
{
    // Append Parameter
    mParameters << aParameter;
    // Emit Parameters Changed
    emit functionParametersChanged(mParameters);
}

//==============================================================================
// Remove Parameter
//==============================================================================
void ComponentFunction::removeParameter(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mParameters.count()) {
        // Remove Parameter
        mParameters.removeAt(aIndex);
        // Emit Parameters Changed
        emit functionParametersChanged(mParameters);
    }
}

//==============================================================================
// Export To JSON Object
//==============================================================================
QJsonObject ComponentFunction::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentFunction::~ComponentFunction()
{
    // ...
}
