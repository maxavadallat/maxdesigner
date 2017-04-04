#include <QDebug>

#include "componentownpropertiesfilter.h"
#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentOwnPropertiesFilter::ComponentOwnPropertiesFilter(QObject* aParent)
    : QSortFilterProxyModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentOwnPropertiesFilter::init()
{
    // Set Dynamic Sort Filter
    setDynamicSortFilter(true);

    // Connect Signals
    connect(this, &QAbstractProxyModel::sourceModelChanged, this, &ComponentOwnPropertiesFilter::updateRoles);
    connect(this, &QAbstractItemModel::modelReset, this, &ComponentOwnPropertiesFilter::updateRoles);

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentOwnPropertiesFilter::clear()
{
    mFilteredNames.clear();
}

//==============================================================================
// Update Roles
//==============================================================================
void ComponentOwnPropertiesFilter::updateRoles()
{
    // Set Filter Role
    setFilterRole((int)ComponentOwnPropertiesModel::OPMRoles::PropertyNameRole);
}

//==============================================================================
// Get Filtered Names
//==============================================================================
QStringList ComponentOwnPropertiesFilter::filteredNames()
{
    return mFilteredNames;
}

//==============================================================================
// Set Filtered Names
//==============================================================================
void ComponentOwnPropertiesFilter::setFilteredNames(const QStringList& aFilteredNames)
{
    // Check Filtered Names
    if (mFilteredNames != aFilteredNames) {
        // Set Filtered Names
        mFilteredNames = aFilteredNames;
        // Emit Filtered Names Changed Signal
        emit filteredNamesChanged(mFilteredNames);
        // Update Roles
        updateRoles();
    }
}

//==============================================================================
// Get Source Index
//==============================================================================
int ComponentOwnPropertiesFilter::getSourceIndex(const int& aIndex)
{
    return mapToSource(index(aIndex, 0)).row();
}

//==============================================================================
// Filter Accepts Row
//==============================================================================
bool ComponentOwnPropertiesFilter::filterAcceptsRow(int sourceRow, const QModelIndex& aParentIndex) const
{
    // Get Index
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, aParentIndex);
    // Get Data
    QVariant sourceData = sourceModel()->data(sourceIndex);

    // Check Data
    if (mFilteredNames.indexOf(sourceData.toString()) >= 0) {
        return false;
    }

    return true;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentOwnPropertiesFilter::~ComponentOwnPropertiesFilter()
{
    // Clear
    clear();
}
