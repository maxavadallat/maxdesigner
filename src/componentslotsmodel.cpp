#include <QDebug>

#include "componentslotsmodel.h"
#include "componentinfo.h"
#include "propertiescontroller.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentSlotsModel::ComponentSlotsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mNewSlot(false)
    , mDirty(false)
    , mSelectedIndex(-1)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentSlotsModel::init()
{
    // Load Compoennt Slots
    loadComponentSlots();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentSlotsModel::clear()
{
    // Check Component
    if (mComponent) {
        // Begin Reset Model
        beginResetModel();

        // Iterate Through Slots
        while (mSlots.count() > 0) {
            // Delete Last
            delete mSlots.takeLast();
        }

        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Set Dirty
//==============================================================================
void ComponentSlotsModel::setDirty(const bool& aDirty)
{
    // Check Dirty
    if (mDirty != aDirty) {
        // Set Dirty
        mDirty = aDirty;
    }
}

//==============================================================================
// Load Component Slots
//==============================================================================
void ComponentSlotsModel::loadComponentSlots()
{
    // Clear
    clear();

    // Check Component
    if (mComponent) {
        qDebug() << "ComponentSlotsModel::loadComponentSlots - mName: " << mComponent->mName;
        // Get Slots Count
        int sCount = mComponent->mSlots.count();
        // Iterate Through Component Slots
        for (int i=0; i<sCount; i++) {
            // Append Slot
            appendSlot(ComponentSlot::fromJSONObject(this, mComponent->mSlots[i].toObject()));
        }
    }

    // Set Dirty
    setDirty(false);
}

//==============================================================================
// Save Component Slots
//==============================================================================
void ComponentSlotsModel::saveComponentSlots()
{
    // Check Component
    if (mComponent && mDirty) {
        qDebug() << "ComponentSlotsModel::saveComponentSlots - mName: " << mComponent->mName;
        // Set Component Slots
        mComponent->mSlots = toJSONArray();
        // Set Component Dirty
        mComponent->setDirty(true);
        // Reset Dirty
        setDirty(false);
    }
}

//==============================================================================
// Clear Component Slots
//==============================================================================
void ComponentSlotsModel::clearComponentSlots()
{
    // Check Compoennt
    if (!mComponent) {
        return;
    }

    qDebug() << "ComponentSlotsModel::clearComponentSlots - mName: " << mComponent->mName;

    // Iterate Through Component Slots
    while (mComponent->mSlots.count() > 0) {
        // Remove Last
        mComponent->mSlots.removeLast();
    }
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentSlotsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentSlotsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Save Previous Component Slots
        saveComponentSlots();
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load New Component Slots
        loadComponentSlots();
    }
}

//==============================================================================
// Add Slot
//==============================================================================
void ComponentSlotsModel::addSlot(const QString& aName, const QString& aSource)
{
    // Check If Slot Valid
    if (slotValid(aName)) {
        qDebug() << "ComponentSlotsModel::addSlot - aName: " << aName;
        // Append Slot
        appendSlot(new ComponentSlot(this, aName, aSource));
    }
}

//==============================================================================
// Remove Slot
//==============================================================================
void ComponentSlotsModel::removeSlot(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mSlots.count()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Slot
        delete mSlots.takeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Rename Slot
//==============================================================================
void ComponentSlotsModel::renameSlot(const int& aIndex, const QString& aName)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount() && slotValid(aName)) {
        // Set Slot Name
        mSlots[aIndex]->mName = aName;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Is Slot Valie
//==============================================================================
bool ComponentSlotsModel::slotValid(const QString& aName)
{
    if (!aName.isEmpty()) {
        // Get Slots Count
        int sCount = rowCount();

        // Iterate Through Slots
        for (int i=0; i<sCount; i++) {
            // Check Slot Name
            if (mSlots[i]->mName == aName) {
                return false;
            }
        }

        return true;
    }

    return false;
}

//==============================================================================
// Create New Slot To Add
//==============================================================================
ComponentSlot* ComponentSlotsModel::createNewSlot()
{
    qDebug() << "ComponentSlotsModel::createNewSlot";
    // Set New Slot
    mNewSlot = true;
    // Create New Empty Slot
    return new ComponentSlot(this, "", "");
}

//==============================================================================
// Get/Select Slot For Editing
//==============================================================================
ComponentSlot* ComponentSlotsModel::selectSlot(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentSlotsModel::selectSlot - aIndex: " << aIndex;
        // Set New Slot
        mNewSlot = false;
        // Set Selected Index
        mSelectedIndex = aIndex;

        return mSlots[aIndex];
    }

    return NULL;
}

//==============================================================================
// Append Slot
//==============================================================================
void ComponentSlotsModel::appendSlot(ComponentSlot* aSlot)
{
    // Check Slot
    if (aSlot) {
        qDebug() << "ComponentSlotsModel::appendSlot - mName: " << aSlot->mName;
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Slot
        mSlots << aSlot;
        // End Insert Rows
        endInsertRows();
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Discard New Slot
//==============================================================================
void ComponentSlotsModel::discardNewSlot(ComponentSlot* aSlot)
{
    // Check Slot
    if (aSlot) {
        // Delete Slot
        delete aSlot;
        // Reset New Slot
        mNewSlot = false;
    }
}

//==============================================================================
// Update Selected Slot
//==============================================================================
void ComponentSlotsModel::updateSelectedSlot(const bool& aDoneEdit)
{
    // Check Selected Index
    if (mSelectedIndex != -1) {
        qDebug() << "ComponentSlotsModel::updateSelectedSlot - mSelectedIndex: " << mSelectedIndex;

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
// Row Count
//==============================================================================
int ComponentSlotsModel::rowCount(const QModelIndex& ) const
{
    return mComponent ? mComponent->mSlots.count() : 0;
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentSlotsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int fmRow = index.row();

    // Check Row
    if (mComponent && fmRow >= 0 && fmRow < rowCount()) {
        // Switch Role
        switch (role) {
            default:
            case SMRNameRole:   return mSlots[fmRow]->slotName();
            case SMRSoureRole:  return mSlots[fmRow]->slotSource();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentSlotsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    rNames[SMRNameRole]     = "slotName";
    rNames[SMRSoureRole]    = "slotSource";

    return rNames;
}

//==============================================================================
// To JSON Array
//==============================================================================
QJsonArray ComponentSlotsModel::toJSONArray()
{
    // Init New Array
    QJsonArray newArray;

    // Get Slots Count
    int sCount = mSlots.count();
    // Iterate Through Signals
    for (int i=0; i<sCount; i++) {
        // Append To Array
        newArray << mSlots[i]->toJSONObject();
    }

    return newArray;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSlotsModel::~ComponentSlotsModel()
{
    // Clear
    clear();

    // ...
}
















//==============================================================================
// From JSON Object
//==============================================================================
ComponentSlot* ComponentSlot::fromJSONObject(ComponentSlotsModel* aModel, const QJsonObject& aObject)
{
    ComponentSlot* newSlot = new ComponentSlot(aModel,
                                               aObject[JSON_KEY_COMPONENT_SLOT_NAME].toString(),
                                               aObject[JSON_KEY_COMPONENT_SLOT_SOURCE].toString());

    return newSlot;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentSlot::ComponentSlot(ComponentSlotsModel* aModel, const QString& aName, const QString& aSource, QObject* aParent)
    : QObject(aParent)
    , mModel(aModel)
    , mName(aName)
    , mSource(aSource)
{
    // ...
}

//==============================================================================
// Get Slot Name
//==============================================================================
QString ComponentSlot::slotName()
{
    return mName;
}

//==============================================================================
// Set Slot Name
//==============================================================================
void ComponentSlot::setSlotName(const QString& aSlotName)
{
    // Check Slot Name
    if (mName != aSlotName) {
        // Set Name
        mName = aSlotName;
        // Emit Slot Name Changed Signal
        emit slotNameChanged(mName);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Slot
        mModel->updateSelectedSlot(false);
    }
}

//==============================================================================
// Get Slot Source
//==============================================================================
QString ComponentSlot::slotSource()
{
    return mSource;
}

//==============================================================================
// Set Slot Source
//==============================================================================
void ComponentSlot::setSlotSource(const QString& aSource)
{
    // Check Source
    if (mSource != aSource) {
        // Set Source
        mSource = aSource;
        // Emit Source Changed Signal
        emit slotSourceChanged(mSource);
        // Set Model Dirty
        mModel->setDirty(true);
        // Update Selected Slot
        mModel->updateSelectedSlot(false);
    }
}

//==============================================================================
// Export To JSON Object
//==============================================================================
QJsonObject ComponentSlot::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // Set Up New JSON Object
    newJSONObject[JSON_KEY_COMPONENT_SLOT_NAME] = mName;
    newJSONObject[JSON_KEY_COMPONENT_SLOT_SOURCE] = mSource;

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSlot::~ComponentSlot()
{
    // ...
}
