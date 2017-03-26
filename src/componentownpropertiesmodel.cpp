#include <QDebug>
#include <QJsonObject>

#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentOwnPropertiesModel::ComponentOwnPropertiesModel(QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(NULL)
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
        // Begin Reset Model
        beginResetModel();
        // Set Current Component
        mComponent = aComponent;
        // End Reset Model
        endResetModel();
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
        // Get Type/Value Split
        QStringList rtvList = mComponent->mOwnProperties[rKey].toString().split(":");
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
