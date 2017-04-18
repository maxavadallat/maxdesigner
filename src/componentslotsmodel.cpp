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
void ComponentSlotsModel::clear(const bool& aEndReset)
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

        // Check End Reset Model
        if (aEndReset) {
            // End Reset Model
            endResetModel();
        }
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
        // Get Slots Count
        int sCount = mComponent->mSlots.count();
        // Iterate Through Component Slots
        for (int i=0; i<sCount; i++) {
            // Append Slot
            appendSlot(ComponentSlot::fromJSONObject(mComponent->mSlots[i].toObject()));
        }
    }
}

//==============================================================================
// Save Component Slots
//==============================================================================
void ComponentSlotsModel::saveComponentSlots()
{
    // Clear Compoennt SLots
    clearComponentSlots();

    // Check Component
    if (mComponent) {
        // Set Component Slots
        mComponent->mSlots = toJSONArray();
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
// Append Slot
//==============================================================================
void ComponentSlotsModel::appendSlot(ComponentSlot* aSlot)
{
    // Check Slot
    if (aSlot) {
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        // Append Slot
        mSlots << aSlot;
        // End Insert Rows
        endInsertRows();
    }
}

//==============================================================================
// Add Slot
//==============================================================================
void ComponentSlotsModel::addSlot(const QString& aName, const QString& aSource)
{
    // Check If Slot Valid
    if (slotValid(aName)) {
        appendSlot(new ComponentSlot(aName, aSource));
    }
}

//==============================================================================
// Remove Slot
//==============================================================================
void ComponentSlotsModel::removeSlot(const QString& aName)
{
    // Get Slots Count
    int sCount = mSlots.count();

    // Iterate Through Slots
    for (int i=0; i<sCount; i++) {
        // Get Slot
        ComponentSlot* cSlot = mSlots[i];
        // Check Slot Name
        if (cSlot->mName == aName) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), i, i);
            // Delete SLot
            delete mSlots.takeAt(i);
            // End Remove Rows
            endRemoveRows();

            return;
        }
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
// Update Source
//==============================================================================
void ComponentSlotsModel::updateSlotSource(const QString& aName, const QString& aSource)
{
    // Get Slots Count
    int sCount = mSlots.count();

    // Iterate Through Slots
    for (int i=0; i<sCount; i++) {
        // Get Slot
        ComponentSlot* cSlot = mSlots[i];
        // Check Slot Name
        if (cSlot->mName == aName) {
            // Set Slot Source
            cSlot->mSource = aSource;

            // Emit Data Changed Signal
            emit dataChanged(index(i), index(i));

            return;
        }
    }
}

//==============================================================================
// Update Source
//==============================================================================
void ComponentSlotsModel::updateSlotSource(const int& aIndex, const QString& aSource)
{
    // Check Index
    if (aIndex >- 0 && aIndex < mSlots.count()) {
        // Set Source
        mSlots[aIndex]->mSource = aSource;
        // Emit Data Changed Signal
        emit dataChanged(index(aIndex), index(aIndex));
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
ComponentSlot* ComponentSlot::fromJSONObject(const QJsonObject& aObject)
{
    ComponentSlot* newSlot = new ComponentSlot(aObject[JSON_KEY_COMPONENT_SLOT_NAME].toString(),
                                               aObject[JSON_KEY_COMPONENT_SLOT_SOURCE].toString());

    return newSlot;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentSlot::ComponentSlot(const QString& aName, const QString& aSource, QObject* aParent)
    : QObject(aParent)
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
    }
}

//==============================================================================
// Export To JSON Object
//==============================================================================
QJsonObject ComponentSlot::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newJSONObject;

    // ...

    return newJSONObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentSlot::~ComponentSlot()
{
    // ...
}
