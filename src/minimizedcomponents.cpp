#include "src/minimizedcomponents.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
MinimizedComponents::MinimizedComponents(QObject* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void MinimizedComponents::init()
{

}

//==============================================================================
// Clear
//==============================================================================
void MinimizedComponents::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear Minimized Compoennts
    mMinimizedComponents.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Add Compoennt
//==============================================================================
void MinimizedComponents::addComponent(ComponentInfo* aComponent)
{
    // Begin Insert Rows
    beginInsertRows(QModelIndex(), mMinimizedComponents.count(), mMinimizedComponents.count());
    // Append Component
    mMinimizedComponents << aComponent;
    // End Insert Rows
    endInsertRows();
}

//==============================================================================
// Remove Component
//==============================================================================
void MinimizedComponents::removeComponent(ComponentInfo* aComponent)
{
    // Get Index Of Compoennt
    int cIndex = mMinimizedComponents.indexOf(aComponent);
    // Check Component Index
    if (cIndex >= 0) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), cIndex, cIndex);
        // Remove Component
        mMinimizedComponents.removeAt(cIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Row Count
//==============================================================================
int MinimizedComponents::rowCount(const QModelIndex& ) const
{
    return mMinimizedComponents.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant MinimizedComponents::data(const QModelIndex& index, int role) const
{
    // Get Ro
    int row = index.row();
    // Check Row
    if (row >= 0 && row < mMinimizedComponents.count()) {
        // Switch Role
        switch (role) {
            case ComponentNameRole:  return mMinimizedComponents[row]->componentName();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> MinimizedComponents::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Set Role Names
    rNames[ComponentNameRole] = "componentName";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
MinimizedComponents::~MinimizedComponents()
{
    // Clear
    clear();
}
