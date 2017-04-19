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
    , mNewFunction(false)
    , mDirty(false)
    , mSelectedIndex(-1)
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
// Set Dirty
//==============================================================================
void ComponentFunctionsModel::setDirty(const bool& aDirty)
{
    // Check If Dirty
    if (mDirty != aDirty) {
        // Set Dirty
        mDirty = aDirty;
    }
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
        qDebug() << "ComponentFunctionsModel::loadComponentFunctions";
        // Get Functions Count
        int fCount = mComponent->mFunctions.count();
        // Iterate Through Component Function
        for (int i=0; i<fCount; i++) {
            // Append Function
            appendFunction(ComponentFunction::fromJSONObject(this, mComponent->mFunctions[i].toObject()));
        }
    }

    // Set Dirty
    setDirty(false);
}

//==============================================================================
// Save Component Functions
//==============================================================================
void ComponentFunctionsModel::saveComponentFunctions()
{
    // Check Compoennt
    if (mComponent && mDirty) {
        qDebug() << "ComponentFunctionsModel::saveComponentFunctions";
        // Set Functions
        mComponent->mFunctions = toJSONArray();
        // Set Component Dirty
        mComponent->setDirty(true);
        // Set Dirty
        setDirty(false);
    }
}

//==============================================================================
// Clear Component Functions
//==============================================================================
void ComponentFunctionsModel::clearComponentFunctions()
{
    // Check Component
    if (mComponent) {
        qDebug() << "ComponentFunctionsModel::clearComponentFunctions";
        // Iterate Through Functions
        while (mComponent->mFunctions.count() > 0) {
            // Remove Last
            mComponent->mFunctions.removeLast();
        }

        // Set Component Dirty
        mComponent->setDirty(true);
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
// Add Function
//==============================================================================
void ComponentFunctionsModel::addFunction(const QString& aName, const QStringList& aParameters, const QString& aSource)
{
    // Check Function
    if (functionValid(aName)) {
        qDebug() << "ComponentFunctionsModel::addFunction - aName: " << aName;
        // Append Function
        appendFunction(new ComponentFunction(this, aName, aSource, aParameters));
    }
}

//==============================================================================
// Remove Function
//==============================================================================
void ComponentFunctionsModel::removeFunction(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentFunctionsModel::removeFunction - aIndex: " << aIndex;
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Function
        delete mFunctions.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Rename Function
//==============================================================================
void ComponentFunctionsModel::renameFunction(const int& aIndex, const QString& aName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() && functionValid(aName)) {
        qDebug() << "ComponentFunctionsModel::renameFunction - aIndex: " << aIndex;
        // Set Function Name
        mFunctions[aIndex]->mName = aName;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Check If Function Valid
//==============================================================================
bool ComponentFunctionsModel::functionValid(const QString& aName)
{
    // Check Function Name
    if (!aName.isEmpty()) {
        // Check If New Funtion
        if (mNewFunction) {
            // Get Functions Count
            int fCount = mFunctions.count();
            // Iterate Through Functions
            for (int i=0; i<fCount; i++) {
                // Check Function Name
                if (mFunctions[i]->mName == aName) {
                    return false;
                }
            }
        } else {
            // ...
        }

        return true;
    }

    return false;
}

//==============================================================================
// Create New Function
//==============================================================================
ComponentFunction* ComponentFunctionsModel::createNewFunction()
{
    qDebug() << "ComponentFunctionsModel::createNewFunction";

    // Set New Function
    mNewFunction = true;

    // Create New Empty Function
    return new ComponentFunction(this, "", "");
}

//==============================================================================
// Select Function
//==============================================================================
ComponentFunction* ComponentFunctionsModel::selectFunction(const int& aIndex)
{
    // Check index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentFunctionsModel::selectFunction - aIndex: " << aIndex;
        // Set New Function
        mNewFunction = false;
        // Set Selected Function Index
        mSelectedIndex = aIndex;

        return mFunctions[aIndex];
    }

    return NULL;
}

//==============================================================================
// Append Function
//==============================================================================
void ComponentFunctionsModel::appendFunction(ComponentFunction* aFunction)
{
    // Check Function
    if (aFunction) {
        qDebug() << "ComponentFunctionsModel::appendFunction - mName: " << aFunction->mName;
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Function
        mFunctions << aFunction;
        // End Insert Rows
        endInsertRows();
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Discard New Function
//==============================================================================
void ComponentFunctionsModel::discardNewFunction(ComponentFunction* aFunction)
{
    // Check Signal
    if (aFunction) {
        qDebug() << "ComponentFunctionsModel::discardNewFunction";
        // Reset New Function
        mNewFunction = false;
        // Delete New Function
        delete aFunction;
    }
}

//==============================================================================
// Update Selected Function
//==============================================================================
void ComponentFunctionsModel::updateSelectedFunction(const bool& aDoneEdit)
{
    // Check Selected Index
    if (mSelectedIndex != -1) {
        qDebug() << "ComponentFunctionsModel::updateSelectedSignal - mSelectedIndex: " << mSelectedIndex;

        // ...

        // Emit Data Changed Signal
        emit dataChanged(index(mSelectedIndex), index(mSelectedIndex));

        // Check If Done Editing
        if (aDoneEdit) {
            // Reset Selected index
            mSelectedIndex = -1;
        }
    }
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
ComponentFunction* ComponentFunction::fromJSONObject(ComponentFunctionsModel* aModel, const QJsonObject& aObject)
{
    ComponentFunction* newFunction = new ComponentFunction(aModel,
                                                           aObject[JSON_KEY_COMPONENT_FUNCTION_NAME].toString(),
                                                           aObject[JSON_KEY_COMPONENT_FUNCTION_SOURCE].toString(),
                                                           aObject[JSON_KEY_COMPONENT_FUNCTION_PARAMETERS].toString().split(",", QString::SkipEmptyParts));

    return newFunction;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentFunction::ComponentFunction(ComponentFunctionsModel* aModel,
                                     const QString& aName,
                                     const QString& aSource,
                                     const QStringList& aParameters,
                                     QObject* aParent)
    : QObject(aParent)
    , mModel(aModel)
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
        qDebug() << "ComponentFunction::setFunctionName - aFunctionName: " << aFunctionName;
        // Set Name
        mName = aFunctionName;
        // Emit Function Name Changed Signal
        emit functionNameChanged(mName);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
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
        qDebug() << "ComponentFunction::setFunctionParameters - aParameters: " << aParameters;
        // Set Parameters
        mParameters = aParameters;
        // Emit Parameters Changed Signal
        emit functionParametersChanged(mParameters);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
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
        qDebug() << "ComponentFunction::setFunctionSource - aSource: " << aSource;
        // Set Source
        mSource = aSource;
        // Emit Source Changed Signal
        emit functionSourceChanged(mSource);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
    }
}

//==============================================================================
// Insert Parameter
//==============================================================================
void ComponentFunction::insertFunctionParameter(const int& aIndex, const QString& aParameter)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mParameters.count() && mParameters.indexOf(aParameter) < 0) {
        qDebug() << "ComponentFunction::insertFunctionParameter - aParameter: " << aParameter << " - aIndex: " << aIndex;
        // Insert
        mParameters.insert(aIndex, aParameter);
        // Emit Parameters Changed
        emit functionParametersChanged(mParameters);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
    } else {
        // Append
        appendFunctionParameter(aParameter);
    }
}

//==============================================================================
// Append Parameter
//==============================================================================
void ComponentFunction::appendFunctionParameter(const QString& aParameter)
{
    // Check Parameter
    if (mParameters.indexOf(aParameter) < 0) {
        qDebug() << "ComponentFunction::appendFunctionParameter - aParameter: " << aParameter;
        // Append Parameter
        mParameters << aParameter;
        // Emit Parameters Changed
        emit functionParametersChanged(mParameters);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
    }
}

//==============================================================================
// Remove Parameter
//==============================================================================
void ComponentFunction::removeFunctionParameter(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mParameters.count()) {
        qDebug() << "ComponentFunction::removeFunctionParameter - aIndex: " << aIndex;
        // Remove Parameter
        mParameters.removeAt(aIndex);
        // Emit Parameters Changed
        emit functionParametersChanged(mParameters);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Function
        mModel->updateSelectedFunction(false);
    }
}

//==============================================================================
// Check If Parameter Valid
//==============================================================================
bool ComponentFunction::parameterValid(const QString& aParameter, const bool& aNewParameter)
{
    // Check Parameter
    if (!aParameter.isEmpty()) {
        // Check New Parameter
        if (aNewParameter) {
            return (mParameters.indexOf(aParameter) < 0);
        }

        return true;
    }

    return false;
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
    // Check Parameters
    if (mParameters.count() > 0) {
        newJSONObject[JSON_KEY_COMPONENT_FUNCTION_PARAMETERS] = mParameters.join(',');
    }
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
