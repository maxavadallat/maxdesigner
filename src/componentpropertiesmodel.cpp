#include <QDebug>
#include "componentpropertiesmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertiesModel::ComponentPropertiesModel(QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(NULL)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentPropertiesModel::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentPropertiesModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentPropertiesModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentPropertiesModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Save Component Properties

        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Properties

    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentPropertiesModel::rowCount(const QModelIndex& ) const
{

    return 0;
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentPropertiesModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentPropertiesModel::roleNames() const
{
    // Init New Role Names
    QHash<int, QByteArray> rNames;

    // ...

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentPropertiesModel::~ComponentPropertiesModel()
{
    // Clear
    clear();

    // ...
}
