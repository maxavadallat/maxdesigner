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
    , mNewSignal(false)
    , mDirty(false)
    , mSelectedIndex(-1)
{
    qDebug() << "ComponentSignalsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentSignalsModel::init()
{
    // Load Component Signals
    loadComponentSignals();

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
// Set Dirty
//==============================================================================
void ComponentSignalsModel::setDirty(const bool& aDirty)
{
    // Check Dirty
    if (mDirty != aDirty) {
        // Set Dirty
        mDirty = aDirty;
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
        qDebug() << "ComponentSignalsModel::loadComponentSignals - mName: " << mComponent->mName;

        // Get Signals Count
        int sCount = mComponent->mSignals.count();
        // Iterate Through Signals
        for (int i=0; i<sCount; i++) {
            // Append Signal
            appendSignal(ComponentSignal::fromJSONObject(this, mComponent->mSignals[i].toObject()));
        }

        // Set Dirty
        setDirty(false);
    }
}

//==============================================================================
// Save Component Signals
//==============================================================================
void ComponentSignalsModel::saveComponentSignals()
{
    // Check Current Component
    if (mComponent && mDirty) {
        qDebug() << "ComponentSignalsModel::saveComponentSignals - mName: " << mComponent->mName;
        // Set Component Signals
        mComponent->mSignals = toJSONArray();
        // Set Dirty
        mComponent->setDirty(true);
        // Set Dirty
        setDirty(false);
    }
}

//==============================================================================
// Clear Component Signals
//==============================================================================
void ComponentSignalsModel::clearComponentSignals()
{
    // Check Component
    if (mComponent) {
        qDebug() << "ComponentSignalsModel::clearComponentSignals - mName: " << mComponent->mName;
        // Iterate Through Signals
        while (mComponent->mSignals.count() > 0) {
            // Remove Last
            mComponent->mSignals.removeLast();
        }
        // Set Dirty
        mComponent->setDirty(true);
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
        qDebug() << "ComponentSignalsModel::setCurrentComponent - mName: " << (aComponent ? aComponent->mName : "NULL");

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
        qDebug() << "ComponentSignalsModel::addSignal - aName: " << aName << " - aParameters: " << aParameters;
        // Append New Signal
        appendSignal(new ComponentSignal(this, aName, aParameters));
    }
}

//==============================================================================
// Remove Signal
//==============================================================================
void ComponentSignalsModel::removeSignal(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentSignalsModel::removeSignal - aIndex: " << aIndex;
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Delete Signal
        delete mSignals.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Rename Signal
//==============================================================================
void ComponentSignalsModel::renameSignal(const int& aIndex, const QString& aName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() && signalValid(aName)) {
        qDebug() << "ComponentSignalsModel::renameSignal - aName: " << aName;
        // Set Signal Name
        mSignals[aIndex]->mName = aName;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Check If Signal Valid
//==============================================================================
bool ComponentSignalsModel::signalValid(const QString& aName)
{
    // Check Signal Name
    if (!aName.isEmpty()) {
        // Check New Signal
        if (mNewSignal) {
            // Get Signals Count
            int sCount = rowCount();
            // Iterate Through Signals
            for (int i=0; i<sCount; i++) {
                // Check Signal Name
                if (mSignals[i]->mName == aName) {
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
// Create New Signal
//==============================================================================
ComponentSignal* ComponentSignalsModel::createNewSignal()
{
    qDebug() << "ComponentSignalsModel::createNewSignal";
    // Set New Signal
    mNewSignal = true;
    // Create New Empty Signal
    return new ComponentSignal(this, "");
}

//==============================================================================
// Get/Select Signal
//==============================================================================
ComponentSignal* ComponentSignalsModel::selectSignal(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentSignalsModel::selectSignal - aIndex: " << aIndex;

        // Reset New Signal
        mNewSignal = false;
        // Set Selected Index
        mSelectedIndex = aIndex;

        return mSignals[aIndex];
    }

    return NULL;
}

//==============================================================================
// Append Signal
//==============================================================================
void ComponentSignalsModel::appendSignal(ComponentSignal* aSignal)
{
    // Check Signal
    if (aSignal) {
        qDebug() << "ComponentSignalsModel::appendSignal - aSignal: " << aSignal->mName;

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Signal
        mSignals << aSignal;
        // End Insert Rows
        endInsertRows();

        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Discard New Signal
//==============================================================================
void ComponentSignalsModel::discardNewSignal(ComponentSignal* aSignal)
{
    // Check Signal
    if (aSignal) {
        qDebug() << "ComponentSignalsModel::discardNewSignal";
        // Delete Signal
        delete aSignal;
        // Reset New Signal
        mNewSignal = false;
    }
}

//==============================================================================
// Update Selected Signal
//==============================================================================
void ComponentSignalsModel::updateSelectedSignal(const bool& aDoneEdit)
{
    // Check Selected Index
    if (mSelectedIndex != -1) {
        qDebug() << "ComponentSignalsModel::updateSelectedSignal - mSelectedIndex: " << mSelectedIndex;

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

    qDebug() << "ComponentSignalsModel deleted.";
}












//==============================================================================
// From JSON Object
//==============================================================================
ComponentSignal* ComponentSignal::fromJSONObject(ComponentSignalsModel* aModel, const QJsonObject& aObject)
{
    // Create New Signal
    ComponentSignal* newSignal = new ComponentSignal(aModel,
                                                     aObject[JSON_KEY_COMPONENT_SIGNAL_NAME].toString(),
                                                     aObject[JSON_KEY_COMPONENT_SIGNAL_PARAMETERS].toString().split(",", QString::SkipEmptyParts));

    return newSignal;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentSignal::ComponentSignal(ComponentSignalsModel* aModel, const QString& aName, const QStringList& aParameters, QObject* aParent)
    : QObject(aParent)
    , mModel(aModel)
    , mName(aName)
    , mParameters(aParameters)
    , mNewParameter(false)
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
        // Set Model Dirty
        mModel->setDirty(true);
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
        // Set Model Dirty
        mModel->setDirty(true);
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
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Signal
        mModel->updateSelectedSignal(false);
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
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Signal
        mModel->updateSelectedSignal(false);
    }
}

//==============================================================================
// Update Signal Parameter
//==============================================================================
void ComponentSignal::updateSignalParameter(const int& aIndex, const QString& aParameter)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mParameters.count() && mParameters[aIndex] != aParameter) {
        // Set Parameter
        mParameters[aIndex] = aParameter;
        // Emit Signal Parameters Changed Signal
        emit signalParametersChanged(mParameters);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Signal
        mModel->updateSelectedSignal(false);
    }
}

//==============================================================================
// Check If Parameter Valid
//==============================================================================
bool ComponentSignal::parameterValid(const QString& aParameter, const bool& aNewParameter)
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
// To JSON Object
//==============================================================================
QJsonObject ComponentSignal::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newObject;

    // Set Signal Name
    newObject[JSON_KEY_COMPONENT_SIGNAL_NAME] = mName;

    // Check Parameters
    if (mParameters.count() > 0) {
        // Set Parameters
        newObject[JSON_KEY_COMPONENT_SIGNAL_PARAMETERS] = mParameters.join(',');
    }

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
