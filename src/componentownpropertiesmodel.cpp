#include <QDebug>
#include <QJsonObject>

#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentOwnPropertiesModel::ComponentOwnPropertiesModel(ComponentInfo* aComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
{
    qDebug() << "ComponentOwnPropertiesModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentOwnPropertiesModel::init()
{
    // Check Current Component
    if (mComponent) {
        // Connect Signals
        connect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
        connect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
        connect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
    }

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentOwnPropertiesModel::clear()
{
    // ...
}

//==============================================================================
// Own Property Added Slot
//==============================================================================
void ComponentOwnPropertiesModel::propertyAdded(const int& aIndex)
{
    // Begin Inser Rows
    beginInsertRows(QModelIndex(), aIndex, aIndex);

    // ...

    // End Insert Rows
    endInsertRows();
}

//==============================================================================
// Own Property Removed Slot
//==============================================================================
void ComponentOwnPropertiesModel::propertyRemoved(const int& aIndex)
{
    // Begin Remove Rows
    beginRemoveRows(QModelIndex(), aIndex, aIndex);

    // ...

    // End Remove Rows
    endRemoveRows();
}

//==============================================================================
// Properties Updated Slot
//==============================================================================
void ComponentOwnPropertiesModel::propertiesUpdated()
{
    //qDebug() << "ComponentOwnPropertiesModel::propertiesUpdated";

    // Begin Reset Model
    beginResetModel();

    // ...

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentOwnPropertiesModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentOwnPropertiesModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Check Current Component
        if (mComponent) {
            // Disconnect Signals
            disconnect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
            disconnect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
            disconnect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
        }

        // Begin Reset Model
        beginResetModel();
        // Set Current Component
        mComponent = aComponent;
        // End Reset Model
        endResetModel();

        // Check Current Component
        if (mComponent) {
            // Connect Signals
            connect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
            connect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
            connect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
        }

        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
    }
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentOwnPropertiesModel::rowCount(const QModelIndex&) const
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mOwnProperties.keys().count();
    }

    return 0;
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentOwnPropertiesModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int copRow = index.row();

    // Check Row
    if (copRow >= 0 && copRow < rowCount() && mComponent) {
        // Get Key
        QString rKey = mComponent->mOwnProperties.keys()[copRow];
        // Get Type & Value
        QString rTypeValue =  mComponent->mOwnProperties[rKey].toString();
        // Get Type/Value Split
        QStringList rtvList = rTypeValue.split(":");
        // Get Type
        QString rType = rtvList[0];
        // Get Value
        QString rValue = rtvList[1];

        // Switch Role
        switch (role) {
            default:
            case PropertyNameRole:      return rKey;
            case PropertyTypeRole:      return rType;
            case PropertyValueRole:     return rValue;
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> ComponentOwnPropertiesModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    rNames[PropertyNameRole]  = "pName";
    rNames[PropertyTypeRole]  = "pType";
    rNames[PropertyValueRole] = "pValue";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentOwnPropertiesModel::~ComponentOwnPropertiesModel()
{
    // Clear
    clear();

    qDebug() << "ComponentOwnPropertiesModel deleted.";
}
