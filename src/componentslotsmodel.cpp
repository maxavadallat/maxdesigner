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
void ComponentSlotsModel::clear()
{
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

//==============================================================================
// Load Component Slots
//==============================================================================
void ComponentSlotsModel::loadComponentSlots()
{
    // Clear
    clear();

    // ...
}

//==============================================================================
// Save Component Slots
//==============================================================================
void ComponentSlotsModel::saveComponentSlots()
{
    // ...
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
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Slots
        loadComponentSlots();
    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentSlotsModel::rowCount(const QModelIndex& ) const
{
    return mSlots.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentSlotsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int fmRow = index.row();

    // Check Row
    if (fmRow >= 0 && fmRow < rowCount()) {
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
// Destructor
//==============================================================================
ComponentSlotsModel::~ComponentSlotsModel()
{
    // Clear
    clear();

    // ...
}

















//==============================================================================
// Constructor
//==============================================================================
ComponentSlot::ComponentSlot(QObject* aParent)
    : QObject(aParent)
    , mName("")
    , mSource("")
{

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
