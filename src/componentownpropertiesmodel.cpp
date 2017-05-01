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
ComponentOwnPropertiesModel::ComponentOwnPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, ComponentInfo* aDerivedComponent, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mProject(aProject)
    , mDerivedComponent(aDerivedComponent)
{
//    qDebug() << "ComponentOwnPropertiesModel created for " << (mComponent ? mComponent->mName : "NULL")
//             << " - aDerivedComponent: " << (mDerivedComponent ? mDerivedComponent->mName : "NULL");

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentOwnPropertiesModel::init()
{
    // Load Component Properties
    loadComponentProperties();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentOwnPropertiesModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Check Keys Count
    if (mKeys.count() > 0) {
        //qDebug() << "ComponentOwnPropertiesModel::clear - mKeys: " << mKeys;
        // Clear Keys
        mKeys.clear();
    } else {
        //qDebug() << "ComponentOwnPropertiesModel::clear - NO KEYS!";
    }

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load Component Properties
//==============================================================================
void ComponentOwnPropertiesModel::loadComponentProperties()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    //qDebug() << "ComponentOwnPropertiesModel::loadComponentProperties - mComponent: " << mComponent->mName;

    // Begin Reset Model
    beginResetModel();

    // Generate Merged Keys
    generateOwnPropertyKeys();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Generate Own Property Keys
//==============================================================================
void ComponentOwnPropertiesModel::generateOwnPropertyKeys()
{
    // Check Component
    if (!mComponent) {
        return;
    }

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

    //qDebug() << "ComponentOwnPropertiesModel::generateOwnPropertyKeys - mComponent: " << mComponent->mName << " - mKeys: " << mKeys;
}

//==============================================================================
// Refresh Property For Inherited Property Set
//==============================================================================
void ComponentOwnPropertiesModel::refreshProperty(const QString& aName)
{
    // Check Name
    if (aName.isEmpty() || !mComponent) {
        return;
    }

    // Get Property Key Index
    int pkIndex = mKeys.indexOf(aName);

    // Check Property Key Index
    if (pkIndex >= 0) {
        //qDebug() << "ComponentOwnPropertiesModel::refreshProperty - aName: " << aName;
        // Emit Data Changed Signal
        emit dataChanged(index(pkIndex), index(pkIndex));
    }
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
        //qDebug() << "ComponentOwnPropertiesModel::setCurrentComponent - aComponent: " << (aComponent ? aComponent->mName : "NULL");

        // Clear
        clear();

        // Set Current Component
        mComponent = aComponent;

        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);

        // Load Component Properties
        loadComponentProperties();
    }
}

//==============================================================================
// Get Component Property Name By Index
//==============================================================================
QString ComponentOwnPropertiesModel::componentPropertyName(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        return mKeys[aIndex];
    }

    return "";
}

//==============================================================================
// Add Own Property
//==============================================================================
bool ComponentOwnPropertiesModel::addComponentProperty(const QString& aName, const int& aType, const QVariant& aDefault)
{
    // Check Component
    if (!mComponent) {
        return false;
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

        // Set Dirty
        mComponent->setDirty(true);
        // Emit Own Proerty Added Signal
        emit ownPropertyAdded(aName);

        // Generate Merged Keys
        generateOwnPropertyKeys();
        // Get Key Index
        kIndex = mKeys.indexOf(aName);
        // Begin Insert Rows
        beginInsertRows(QModelIndex(), kIndex, kIndex);
        // ...
        // End Insert Rows
        endInsertRows();

        return true;

    } else {
        qDebug() << "ComponentOwnPropertiesModel::addComponentProperty - aName: " << aName << " - ALREADY HAS PROPERTY";
    }

    return false;
}

//==============================================================================
// Set Component Property Value
//==============================================================================
void ComponentOwnPropertiesModel::setComponentProperty(const int& aIndex, const QVariant& aValue)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Get Component Property Key
        QString cpKey = mKeys[aIndex];
        // Set Component Property
        setComponentProperty(cpKey, aValue);
    }
}

//==============================================================================
// Get Component Own Property Value
//==============================================================================
QVariant ComponentOwnPropertiesModel::componentPropertyValue(const QString& aName)
{
    // Check Component
    if (!mComponent) {
        return QVariant();
    }

    // Has Key
    bool hasKey = (mComponent->mOwnProperties.keys().indexOf(aName) >= 0);
    // Get Type & Value
    QString opTypeAndValue = mComponent->mOwnProperties.value(aName).toString();

    // Chekc If Has Key
    if (!hasKey && !mComponent->mIsProtoType && mComponent->mProtoType) {
        // Get ProtoType Type & Value
        opTypeAndValue = mComponent->mProtoType->mOwnProperties.value(aName).toString();
    }

    // Get Value Elements
    QStringList valueElements = opTypeAndValue.split(":");

    return valueElements.count() > 1 ? valueElements[1] : valueElements[0];
}

//==============================================================================
// Update Own Property
//==============================================================================
void ComponentOwnPropertiesModel::updateComponentProperty(const int& aIndex, const QString& aName, const int& aType, const QVariant& aDefault)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        // Get Component Property Key
        QString cpKey = mKeys[aIndex];

        // Check Key
        if (cpKey == aName) {
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

            // Set Dirty
            mComponent->setDirty(true);
            // Emit Property Updated
            emit ownPropertyUpdated(aName, aType, aDefault);
            // Emit Data Changed
            emit dataChanged(index(aIndex), index(aIndex));

            // ...

        } else {
            // Remove Component Property
            removeComponentProperty(cpKey);
            // Add Component Property
            addComponentProperty(aName, aType, aDefault);
        }
    }
}

//==============================================================================
// Clear Component Property, Reset To Default/Base Component Value
//==============================================================================
void ComponentOwnPropertiesModel::clearComponentProperty(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentOwnPropertiesModel::clearComponentProperty - aIndex: " << aIndex;
        // Get Key
        QString cpKey = mKeys[aIndex];
        // Clear Component Property
        clearComponentProperty(cpKey);
    }
}

//==============================================================================
// Remove Property
//==============================================================================
void ComponentOwnPropertiesModel::removeComponentProperty(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentOwnPropertiesModel::removeComponentProperty - aIndex: " << aIndex;
        // Get Key
        QString cpKey = mKeys[aIndex];
        // Remove Component Property
        removeComponentProperty(cpKey);
    }
}

//==============================================================================
// Check If Property Name Valid For Addition Or Update
//==============================================================================
bool ComponentOwnPropertiesModel::propertyValid(const QString& aName, const bool& aNewProperty)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    // Check Name
    if (aName.isEmpty()) {
        return false;
    }

    // Check If New Property
    if (aNewProperty) {
        // Check Property Keys
        if (mKeys.indexOf(aName) >= 0) {
            return false;
        }
    } else {

        // ...

    }

    return true;
}

//==============================================================================
// Check IF Has Property
//==============================================================================
bool ComponentOwnPropertiesModel::hasProperty(const QString& aName)
{
    // Check Component
    if (mComponent) {
        return (mComponent->mOwnProperties.keys().indexOf(aName) >= 0);
    }

    return false;
}

//==============================================================================
// Remove Property
//==============================================================================
bool ComponentOwnPropertiesModel::removeComponentProperty(const QString& aName)
{
    // Check Component
    if (mComponent && mComponent->mIsProtoType && !aName.isEmpty() && mComponent->mOwnProperties.keys().indexOf(aName) >= 0) {
        qDebug() << "ComponentOwnPropertiesModel::removeComponentProperty - aName: " << aName;
        // Remove Key
        mComponent->mOwnProperties.remove(aName);
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Property Removed Signal
        emit ownPropertyRemoved(aName);
        // Get Key Index
        int cpkIndex = mKeys.indexOf(aName);
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), cpkIndex, cpkIndex);
        // Generate Own Property Keys
        generateOwnPropertyKeys();
        // End Remove Rows
        endRemoveRows();

        return true;
    }

    return false;
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

    // Get Key Index
    int cpkIndex = mKeys.indexOf(aName);

    // Check Key Index
    if (cpkIndex < 0) {
        return false;
    }

    qDebug() << "ComponentOwnPropertiesModel::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // Check If ProtoType
    if (mComponent->mIsProtoType) {
        // Get Property Type And Value
        QString cpTypeAndValue = mComponent->mOwnProperties[aName].toString();
        // Get Type And Value Elements
        QStringList cpElements = cpTypeAndValue.split(":", QString::KeepEmptyParts);
        // Update Value
        cpElements[1] = aValue.toString();
        // Set Component Own Property
        mComponent->mOwnProperties[aName] = cpElements.join(":");

    } else {
        // Set Component Property Value
        mComponent->mOwnProperties[aName] = aValue.toString();
    }

    // Set Component Dirty
    mComponent->setDirty(true);
    // Emit Component Property Changed
    emit mComponent->componentPropertyChanged(aName, aValue);
    // Emit Component Property Value Changed
    emit ownPropertyValueChanged(aName, aValue);
    // Emit Data Changed Signal
    emit dataChanged(index(cpkIndex), index(cpkIndex));

    return true;
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
            // Set Component Dirty
            mComponent->setDirty(true);

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

    // Get Row Index
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

        // Get Inherited Property Index
        int ipkIndex = mDerivedComponent ? mDerivedComponent->mProperties.keys().indexOf(opKey) : -1;
        // Init Using Base Property
        bool opBase = (ipkIndex < 0);

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
            QStringList tvElements = opTypeAndValue.split(":");
            // Get Type
            QString opType = tvElements.count() > 1 ? tvElements[0] : "";
            // Init Property Value
            QString opValue = "";

            // Check Own Property Base
            if (opBase) {
                // Set Own Property Value
                opValue = tvElements.count() > 1 ? tvElements[1] : tvElements[0];
            } else {
                // Set Own Property Value Value
                opValue = mDerivedComponent->mProperties.value(opKey).toString();
            }

            // Get Formula
            bool opFormula = (opValue.indexOf("{") >= 0 && opValue.indexOf("}") >= 1);
            // Get Property Bind
            bool opBind = false;

            //qDebug() << "ComponentOwnPropertiesModel::data - opKey: " << opKey << " - opValue: " << opValue << " - opBase: " << opBase;

            // Switch Role
            switch (role) {
                default:
                case PropertyNameRole:      return opKey;
                case PropertyTypeRole:      return opType;
                case PropertyValueRole:     return opValue;
                case PropertyIsBind:        return opBind;
                case PropertyIsFormula:     return opFormula;
                case PropertyIsProto:       return opProtoType;
                case PropertyIsBase:        return opBase;
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
    rNames[PropertyIsBind]    = "pIsBind";
    rNames[PropertyIsFormula] = "pIsFormula";
    rNames[PropertyIsProto]   = "pIsProto";
    rNames[PropertyIsBase]    = "pIsBase";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentOwnPropertiesModel::~ComponentOwnPropertiesModel()
{
    // Clear
    clear();

    //qDebug() << "ComponentOwnPropertiesModel deleted.";
}
