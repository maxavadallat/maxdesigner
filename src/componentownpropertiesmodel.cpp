#include <QDebug>
#include <QJsonObject>
#include <QStringList>

#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "constants.h"
#include "projectmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentOwnPropertiesModel::ComponentOwnPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mProject(aProject)
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
//        // Connect Signals
//        connect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
//        connect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
//        connect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
    }

    // Load Component Properties
    loadComponentProperties();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentOwnPropertiesModel::clear(const bool& aEndReset)
{
    // Begin Reset Model
    beginResetModel();
    // Clear Keys
    mKeys.clear();

    // Check End Reset Flag
    if (aEndReset) {
        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Load Component Properties
//==============================================================================
void ComponentOwnPropertiesModel::loadComponentProperties()
{
    // Clear
    clear(false);

    // Check Component
    if (mComponent && mProject) {
        // Generate Merged Keys
        generateMergedKeys();
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Generate Merged Keys
//==============================================================================
void ComponentOwnPropertiesModel::generateMergedKeys()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    qDebug() << "ComponentOwnPropertiesModel::generateMergedKeys - mName: " << mComponent->mName;
    // Set Keys
    mKeys = mComponent->mOwnProperties.keys();

    // Check If Prototype
    if (!mComponent->mIsProtoType) {
//        // Get/Update ProtoType
//        mComponent->mProtoType = mProject->getComponentByName(mComponent->mName, mComponent->mType);
        // Add Prototype Keys
        mKeys += (mComponent->mProtoType ? mComponent->mProtoType->mOwnProperties.keys() : QStringList());
        // Remove Duplicates
        mKeys.removeDuplicates();
    }
}

/*
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
// Own Property Updated
//==============================================================================
void ComponentOwnPropertiesModel::propertyUpdated(const int& aIndex)
{
    // Emit Data Changed Signal

    // ...
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
*/

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
//        // Check Current Component
//        if (mComponent) {
//            // Disconnect Signals
//            disconnect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
//            disconnect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
//            disconnect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
//        }

//        // Begin Reset Model
//        beginResetModel();

        qDebug() << "ComponentOwnPropertiesModel::setCurrentComponent - aComponent: " << (aComponent ? aComponent->mName : "NULL");

        // Set Current Component
        mComponent = aComponent;

//        // End Reset Model
//        endResetModel();

//        // Check Current Component
//        if (mComponent) {
//            // Connect Signals
//            connect(mComponent, SIGNAL(ownPropertiesUpdated()), this, SLOT(propertiesUpdated()));
//            connect(mComponent, SIGNAL(ownPropertyAdded(int)), this, SLOT(propertyAdded(int)));
//            connect(mComponent, SIGNAL(ownPropertyRemoved(int)), this, SLOT(propertyRemoved(int)));
//        }

        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Properties
        loadComponentProperties();
    }
}


//==============================================================================
// Add Own Property
//==============================================================================
void ComponentOwnPropertiesModel::addComponentProperty(const QString& aName, const int& aType, const QVariant& aDefault)
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // Get Key Index
    int kIndex = mKeys.indexOf(aName);

    // Check Index
    if (kIndex < 0) {
        qDebug() << "ComponentOwnPropertiesModel::addComponentProperty - aName: " << aName << " - aType: " << aType << " - aDefault: " << aDefault;

        // Switch Type
        switch ((ComponentInfo::EPropertyType)aType) {
            default:
            case ComponentInfo::EPropertyType::EPTString:          mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTBool:            mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTInt:             mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_INT).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTDouble:          mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTReal:            mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTVar:             mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTQtObject:        mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT).arg(aDefault.toString()); break;
            case ComponentInfo::EPropertyType::EPTQtObjectList:    mComponent->mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST).arg(aDefault.toString()); break;
            break;
        }

        // Check If Prototype
        if (mComponent->mIsProtoType) {
            // Set Dirty
            mComponent->setDirty(true);
        }

        // Generate Merged Keys
        generateMergedKeys();

        // Get Key Index
        kIndex = mKeys.indexOf(aName);

        // Begin Insert Rows
        beginInsertRows(QModelIndex(), kIndex, kIndex);
        // End Insert Rows
        endInsertRows();

    } else {
        qDebug() << "ComponentOwnPropertiesModel::addComponentProperty - aName: " << aName << " - ALREADY HAS PROPERTY";
    }
}

//==============================================================================
// Remove Property
//==============================================================================
void ComponentOwnPropertiesModel::removeComponentProperty(const QString& aName)
{
    // Check Component
    if (!mComponent) {
        return;
    }

    qDebug() << "ComponentInfo::removeProperty - aName: " << aName;

    // Get Key Index
    int kIndex = mKeys.indexOf(aName);

    // Check Key Index
    if (kIndex >= 0) {
        // Get Prototype Key Index
        int popkIndex = mComponent->mProtoType ? mComponent->mProtoType->mOwnProperties.keys().indexOf(aName) : -1;

        // Not Found In Prototype -> Own Property
        if (popkIndex < 0) {

            // Get Own Property Key
            int opkIndex = mComponent->mOwnProperties.keys().indexOf(aName);

            // Check Own Property Key Index
            if (opkIndex >= 0) {
                // Begin Remove Rows
                beginRemoveRows(QModelIndex(), kIndex, kIndex);

                // Remove Key
                mComponent->mOwnProperties.remove(aName);

                // Generate Merged Keys
                generateMergedKeys();

                // End Remove Rows
                endRemoveRows();
            }
        }
    }
}

//==============================================================================
// Set Component Own Property Value
//==============================================================================
bool ComponentOwnPropertiesModel::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    qDebug() << "ComponentOwnPropertiesModel::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // Get Key Index
    int kIndex = mKeys.indexOf(aName);

    // Check Key Index
    if (kIndex >= 0) {

    } else {

    }

//    // Check If Prototype
//    if (mComponent->mIsProtoType) {

//    } else {

//    }

    // ...

    return false;
}

//==============================================================================
// Clear Component Property
//==============================================================================
bool ComponentOwnPropertiesModel::clearComponentProperty(const QString& aName)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    qDebug() << "ComponentOwnPropertiesModel::clearComponentProperty - aName: " << aName;

    // Get Key Index
    int kIndex = mKeys.indexOf(aName);

    // Check If Prototype
    if (!mComponent->mIsProtoType && kIndex >= 0) {

        // Get Own Property Key
        int opkIndex = mComponent->mOwnProperties.keys().indexOf(aName);

        // Check Own Property Key Index
        if (opkIndex >= 0) {
            // Remove Key
            mComponent->mOwnProperties.remove(aName);

//            // Generate Merged Keys
//            generateMergedKeys();

            // Emit Data Changed Signal
            emit dataChanged(index(kIndex), index(kIndex));

            return true;
        }
    }

    return false;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentOwnPropertiesModel::rowCount(const QModelIndex&) const
{
    return mKeys.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentOwnPropertiesModel::data(const QModelIndex& index, int role) const
{
    // Check Component
    if (!mComponent || !mProject) {
        return QVariant();
    }

    // Get Row
    int copRow = index.row();

    // Check Row
    if (copRow >= 0 && copRow < rowCount()) {
        // Get Key
        QString opKey = mKeys[copRow];

        // Get Own Property Key Index
        int opkIndex = mComponent->mOwnProperties.keys().indexOf(opKey);

        // Init Type & Value
        QString opTypeAndValue = "";
        // Init Property Is Prototype
        bool opProtoType = false;

        // Check Own Property Key Index
        if (opkIndex >= 0) {
            // Get Own Property Type & Value
            opTypeAndValue = mComponent->mOwnProperties.value(opKey).toString();
        } else {
            // Get Own Property Type & Value
            opTypeAndValue = mComponent->mProtoType ? mComponent->mProtoType->mOwnProperties.value(opKey).toString() : "";
            // Set Property Is Prototype
            opProtoType = true;
        }

        // Check Own Property Type And Value
        if (!opTypeAndValue.isEmpty()) {
            // Get Type/Value Split
            QStringList tvList = opTypeAndValue.split(":");
            // Get Type
            QString opType = tvList[0];
            // Get Value
            QString opValue = tvList[1];

            // Switch Role
            switch (role) {
                default:
                case PropertyNameRole:      return opKey;
                case PropertyTypeRole:      return opType;
                case PropertyValueRole:     return opValue;
                case PropertyIsFormula:     return false;
                case PropertyIsProto:       return opProtoType;
            }
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
    rNames[PropertyIsFormula] = "pIsFormula";
    rNames[PropertyIsProto]   = "pIsProto";

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
