#include <QDebug>

#include "componentpropertiesmodel.h"
#include "componentownpropertiesmodel.h"
#include "componentinfo.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertiesModel::ComponentPropertiesModel(QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(NULL)
{
    qDebug() << "ComponentPropertiesModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentPropertiesModel::init()
{
    // Load Component Properties
    loadComponentProperties();

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
    mHierarchy.clear();
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Properties
//==============================================================================
void ComponentPropertiesModel::loadComponentProperties()
{
    // Clear
    clear();

    // ...
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
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load Component Properties
        loadComponentProperties();
    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentPropertiesModel::rowCount(const QModelIndex& ) const
{
    return mHierarchy.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentPropertiesModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int pmRow = index.row();

    // Check Row
    if (pmRow >= 0 && pmRow < rowCount()) {
        // Switch Role
        switch (role) {
            default:
            case ESMRBaseName:  return mHierarchy[pmRow]->componentName();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentPropertiesModel::roleNames() const
{
    // Init New Role Names
    QHash<int, QByteArray> rNames;

    // Set Up Role Names
    rNames[ESMRBaseName]    = "baseName";

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

    qDebug() << "ComponentPropertiesModel deleted.";
}
