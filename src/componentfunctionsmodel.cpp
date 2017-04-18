#include <QDebug>

#include "componentfunctionsmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentFunctionsModel::ComponentFunctionsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    qDebug() << "ComponentFunctionsModel created.";

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

    // Check Component
    if (mComponent) {
        // Get Functions Count
        int fCount = mComponent->mFunctions.count();
        // Iterate Through Component Function
        for (int i=0; i<fCount; i++) {
            // Append Function
            appendFunction(ComponentFunction::fromJSONObject(mComponent->mFunctions[i].toObject()));
        }
    }
}

//==============================================================================
// Save Component Functions
//==============================================================================
void ComponentFunctionsModel::saveComponentFunctions()
{
    // Check Compoennt
    if (mComponent) {
        // Set Functions
        mComponent->mFunctions = toJSONArray();
    }
}

//==============================================================================
// Clear Component Functions
//==============================================================================
void ComponentFunctionsModel::clearComponentFunctions()
{
    // Iterate Through Functions
    while (mComponent && mComponent->mFunctions.count() > 0) {
        // Remove Last
        mComponent->mFunctions.removeLast();
    }
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
        // Save Previous Component Functions
        saveComponentFunctions();
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load Component Functions
        loadComponentFunctions();
    }
}

//==============================================================================
// Append Function
//==============================================================================
void ComponentFunctionsModel::appendFunction(ComponentFunction* aFunction)
{
    // Check Function
    if (aFunction) {
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Function
        mFunctions << aFunction;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Add Function
//==============================================================================
void ComponentFunctionsModel::addFunction(const QString& aName, const QStringList& aParameters, const QString& aSource)
{
    // Check Function
    if (functionValid(aName)) {
        // Append Function
        appendFunction(new ComponentFunction(aName, aSource, aParameters));
    }
}

//==============================================================================
// Remove Function
//==============================================================================
void ComponentFunctionsModel::removeFunction(const QString& aName)
{
    // Get Functions Count
    int fCount = mFunctions.count();

    // Iterate Through Functions
    for (int i=0; i<fCount; i++) {
        // Get Function
        ComponentFunction* cFunction = mFunctions[i];
        // Check Function Name
        if (cFunction->mName == aName) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), i, i);
            // Delete Function
            delete mFunctions.takeAt(i);
            // End Remove Rows
            endRemoveRows();

            return;
        }
    }
}

//==============================================================================
// Remove Function
//==============================================================================
void ComponentFunctionsModel::removeFunction(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mFunctions.count()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Function
        delete mFunctions.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Rename Function
//==============================================================================
void ComponentFunctionsModel::renameFunction(const int& aIndex, const QString& aName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() && functionValid(aName)) {
        // Set Function Name
        mFunctions[aIndex]->mName = aName;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
    }
}

//==============================================================================
// Check If Function Valid
//==============================================================================
bool ComponentFunctionsModel::functionValid(const QString& aName)
{
    // Check Function Name
    if (!aName.isEmpty()) {
        // Get Functions Count
        int fCount = mFunctions.count();
        // Iterate Through Functions
        for (int i=0; i<fCount; i++) {
            // Check Function Name
            if (mFunctions[i]->mName == aName) {
                return false;
            }
        }

        return true;
    }

    return false;
}

//==============================================================================
// To JSON Array
//==============================================================================
QJsonArray ComponentFunctionsModel::toJSONArray()
{
    // Init New JSON Array
    QJsonArray newArray;

    // Get Functions Count
    int fCount = mFunctions.count();
    // Iterate Through Functions
    for (int i=0; i<fCount; i++) {
        // Get Function
        ComponentFunction* cFunction = mFunctions[i];
        // Append Functions
        newArray << cFunction->toJSONObject();
    }

    return newArray;
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

    qDebug() << "ComponentFunctionsModel deleted.";
}















//==============================================================================
// From JSON Object
//==============================================================================
ComponentFunction* ComponentFunction::fromJSONObject(const QJsonObject& aObject)
{
    ComponentFunction* newFunction = new ComponentFunction(aObject[JSON_KEY_COMPONENT_FUNCTION_NAME].toString(),
                                                           aObject[JSON_KEY_COMPONENT_FUNCTION_SOURCE].toString(),
                                                           aObject[JSON_KEY_COMPONENT_FUNCTION_PARAMETERS].toString().split(","));

    return newFunction;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentFunction::ComponentFunction(const QString& aName, const QString& aSource, const QStringList& aParameters, QObject* aParent)
    : QObject(aParent)
    , mName(aName)
    , mParameters(aParameters)
    , mSource(aSource)
{
    // ...
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

    // Set UP JSON Object
    newJSONObject[JSON_KEY_COMPONENT_FUNCTION_NAME] = mName;
    newJSONObject[JSON_KEY_COMPONENT_FUNCTION_PARAMETERS] = mParameters.join(',');
    newJSONObject[JSON_KEY_COMPONENT_FUNCTION_SOURCE] = mSource;

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentFunction::~ComponentFunction()
{
    // Clear Parameters
    mParameters.clear();

    // ...
}
