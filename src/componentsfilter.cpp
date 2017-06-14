#include <QDebug>

#include "componentsfilter.h"
#include "settingscontroller.h"
#include "constants.h"


//==============================================================================
// Constructor
//==============================================================================
ComponentsFilter::ComponentsFilter(QObject* aParent)
    : QSortFilterProxyModel(aParent)
{
    // Init
    init();

    // ...
}

//==============================================================================
// Init
//==============================================================================
void ComponentsFilter::init()
{
    // Set Dynamic Sort Filter
    setDynamicSortFilter(true);

    // Connect Signals
    connect(this, &QAbstractProxyModel::sourceModelChanged, this, &ComponentsFilter::updateRoles);
    connect(this, &QAbstractItemModel::modelReset, this, &ComponentsFilter::updateRoles);

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentsFilter::clear()
{
    // Clear Filtered Components
    mFilteredComponents.clear();
}

//==============================================================================
// Get Filtered Components
//==============================================================================
QStringList ComponentsFilter::filteredComponents()
{
    return mFilteredComponents;
}

//==============================================================================
// Set Filtered Components
//==============================================================================
void ComponentsFilter::setFilteredComponents(const QStringList& aFilteredComponents)
{
    // Check Filtered Components
    if (mFilteredComponents != aFilteredComponents) {
        // Set Filtered Components
        mFilteredComponents = aFilteredComponents;
        // Emit Filtered Components Changed Signal
        emit filteredComponentsChanged(mFilteredComponents);
        // Update Roles
        updateRoles();
    }
}

//==============================================================================
// Get Filtered Types
//==============================================================================
QStringList ComponentsFilter::filteredTypes()
{
    return mFilteredTypes;
}

//==============================================================================
// Set Filtered Types
//==============================================================================
void ComponentsFilter::setFilteredTypes(const QStringList& aFilteredTypes)
{
    // Check Filtered Types
    if (mFilteredTypes != aFilteredTypes) {
        // Set Filtered Types
        mFilteredTypes = aFilteredTypes;
        // Emit Filtered Types Changed Signal
        emit filteredTypesChanged(mFilteredTypes);
        // Update Roles
        updateRoles();
    }
}

//==============================================================================
// Get Source Index
//==============================================================================
int ComponentsFilter::getSourceIndex(const int& aIndex)
{
    return mapToSource(index(aIndex, 0)).row();
}

//==============================================================================
// Filter Accepts Row
//==============================================================================
bool ComponentsFilter::filterAcceptsRow(int sourceRow, const QModelIndex& aParentIndex) const
{
    // Get Index
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, aParentIndex);
    // Get Data
    QVariant sourceData = sourceModel()->data(sourceIndex, Qt::UserRole + 1);

    // Check Data
    if (mFilteredComponents.indexOf(sourceData.toString()) >= 0) {
        return false;
    }

    // ...

    return true;
}

//==============================================================================
// Update Roles
//==============================================================================
void ComponentsFilter::updateRoles()
{
    // Set Filter Role
    setFilterRole((int)Qt::UserRole + 1);
}

//==============================================================================
// Destructor
//==============================================================================
ComponentsFilter::~ComponentsFilter()
{
    // Clear
    clear();

    // ...
}
