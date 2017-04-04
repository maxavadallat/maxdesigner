#include <QDebug>

#include "componentimportsmodel.h"
#include "componentinfo.h"
#include "propertiescontroller.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentImportsModel::ComponentImportsModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentImportsModel::init()
{
    // Load Compoennt Imports
    loadComponentImports();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentImportsModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear
    mImports.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Imports
//==============================================================================
void ComponentImportsModel::loadComponentImports()
{
    // Clear
    clear();

    // ...
}

//==============================================================================
// Save Component Imports
//==============================================================================
void ComponentImportsModel::saveComponentImports()
{
    // ...
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentImportsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentImportsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Imports
        loadComponentImports();
    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentImportsModel::rowCount(const QModelIndex& ) const
{
    return mImports.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentImportsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int imRow = index.row();

    // Check Row
    if (imRow >= 0 && imRow < rowCount()) {
        // Switch Role
        switch (role) {
            default:
            case IMRNameRole:   return mImports[imRow];
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentImportsModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    rNames[IMRNameRole]     = "importName";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentImportsModel::~ComponentImportsModel()
{
    // Clear
    clear();

    // ...
}
