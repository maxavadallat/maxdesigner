#include <QDebug>
#include <QJsonObject>
#include <QStringList>

#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "constants.h"
#include "projectmodel.h"
#include "utils.h"

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

    // Get Own Property Keys
    mKeys = mComponent->componentOwnPropertyKeys();
/*
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
*/

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
bool ComponentOwnPropertiesModel::addComponentProperty(const QString& aName,
                                                       const int& aType,
                                                       const QString& aMin,
                                                       const QString& aMax,
                                                       const QString& aEnumValues,
                                                       const QVariant& aDefaultValue,
                                                       const bool& aReadOnly,
                                                       const bool& aDefaultAlias)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    // Check If Has Property
    if (mComponent->hasProperty(aName)) {
        return false;
    }

    // Get Key Index
    int kIndex = mKeys.indexOf(aName);

    // Check Index
    if (kIndex < 0) {
        qDebug() << "ComponentOwnPropertiesModel::addComponentProperty - aName: " << aName << " - aType: " << aType << " - aDefault: " << aDefaultValue;

        // Switch Type
        switch ((ComponentInfo::EPropertyType)aType) {
            default:
            case ComponentInfo::EPropertyType::EPTString:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING, aDefaultValue.toString(), "", "", "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTBool:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL, aDefaultValue.toString(), "", "", "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTInt:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_INT, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTDouble:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTReal:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTVar:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR, aDefaultValue.toString(), "", "", "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTQtObject:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT, aDefaultValue.toString(), "", "", "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTQtObjectList:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST, aDefaultValue.toString(), "", "", "", aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTEnum:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM, aDefaultValue.toString(), "", "", aEnumValues, aReadOnly);
            break;
            case ComponentInfo::EPropertyType::EPTAlias:
                mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ALIAS, aDefaultValue.toString(), "", "", "", aReadOnly, aDefaultAlias);
            break;
        }

        // Set Dirty
        mComponent->setDirty(true);

        // Emit Component's Own Property Added Signal
        emit mComponent->ownPropertyAdded(aName);

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
void ComponentOwnPropertiesModel::updateComponentProperty(const int& aIndex,
                                                          const QString& aName,
                                                          const int& aType,
                                                          const QString& aMin,
                                                          const QString& aMax,
                                                          const QString& aEnumValues,
                                                          const QVariant& aDefault)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {
        qDebug() << "ComponentOwnPropertiesModel::updateComponentProperty - aIndex: " << aIndex;
        // Remove Component Property
        removeComponentProperty(aName);
        // Add Component Property
        addComponentProperty(aName, aType, aMin, aMax, aEnumValues, aDefault);
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
        return (mKeys.indexOf(aName) >= 0);
        //return (mComponent->mOwnProperties.keys().indexOf(aName) >= 0);
    }

    return false;
}

//==============================================================================
// Remove Property
//==============================================================================
bool ComponentOwnPropertiesModel::removeComponentProperty(const QString& aName)
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

    // Check Component
    if (mComponent->mIsProtoType && !aName.isEmpty()) {

        qDebug() << "ComponentOwnPropertiesModel::removeComponentProperty - aName: " << aName;

        // Remove Key
        mComponent->mOwnProperties.remove(aName);
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Component's Property Removed Signal
        emit mComponent->ownPropertyRemoved(aName);
        // Emit Property Removed Signal
        emit ownPropertyRemoved(aName);

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

//    // Check If ProtoType
//    if (mComponent->mIsProtoType) {
//        // Get Property Type And Value
//        QString cpTypeAndValue = mComponent->mOwnProperties[aName].toString();

//        // Get Type
//        QString pType = Utils::parseType(cpTypeAndValue);
//        // Get Min
//        QString pMin = Utils::parseMinValue(cpTypeAndValue);
//        // Get Max
//        QString pMax = Utils::parseMaxValue(cpTypeAndValue);
//        // Get Enum Values
//        QString pEnums = Utils::parseEnumValuesToString(cpTypeAndValue);

//        // Set Component Own Property
//        mComponent->mOwnProperties[aName] = Utils::composeTypeAndValue(pType, aValue.toString(), pMin, pMax, pEnums);

//    } else {
//        // Set Component Property Value
//        mComponent->mOwnProperties[aName] = aValue.toString();
//    }

//    // Set Component Dirty
//    mComponent->setDirty(true);

//    // Emit Component Property Changed
//    emit mComponent->componentPropertyChanged(aName, aValue);
//    // Emit Component Property Value Changed
//    emit ownPropertyValueChanged(aName, aValue);

    if (mDerivedComponent && mDerivedComponent->setComponentProperty(aName, aValue)) {
        // Emit Data Changed Signal
        emit dataChanged(index(cpkIndex), index(cpkIndex));

        return true;
    }

    // Set Component Property
    if (mComponent->setComponentProperty(aName, aValue)) {
        // Emit Data Changed Signal
        emit dataChanged(index(cpkIndex), index(cpkIndex));

        return true;
    }

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

    // Get Key Index
    int cpkIndex = mKeys.indexOf(aName);

    // Check Key Index
    if (cpkIndex < 0) {
        return false;
    }

    qDebug() << "ComponentOwnPropertiesModel::clearComponentProperty - aName: " << aName;

    // Init Component For Clear Property
    ComponentInfo* component = mDerivedComponent ? mDerivedComponent : mComponent;

    // Check If Prototype
    if (!component->mIsProtoType) {
        // Get Property Keys Index
        int pkIndex = component->mProperties.keys().indexOf(aName);

        // Check Property Key Index
        if (pkIndex >= 0) {
            // Remov Property
            component->mProperties.remove(aName);
            // Set Dirty
            component->setDirty(true);
            // Emit Component Property Changed
            emit component->componentPropertyChanged(aName, component->componentProperty(aName));
            // Emit Data Changed Signal
            emit dataChanged(index(cpkIndex), index(cpkIndex));

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

        // Init Type & Value
        QString opTypeAndValue = mDerivedComponent ? mDerivedComponent->propertyTypeAndValue(opKey) : mComponent->propertyTypeAndValue(opKey);

        // Init Derived Component Key Index
        int dcpkIndex = mDerivedComponent ? mDerivedComponent->mProperties.keys().indexOf(opKey) : -1;

        // Init Using Base Property Vaue
        bool opBase = (dcpkIndex == -1);

        // Init Read Only
        bool opReadOnly = false;
        // Init Default Alias
        bool opDefaultAlias = false;

        // Get Type
        QString opType = Utils::parseType(opTypeAndValue, opReadOnly, opDefaultAlias, true);

        // Get Formula
        bool opFormula = Utils::hasFormula(opTypeAndValue) >= 0;

        // Get Property Bind
        bool opBind = Utils::hasBinding(opTypeAndValue) >= 0;

        // Get Enum Values
        QString opEnumValues = Utils::parseEnumValuesToString(opTypeAndValue);

        // Get Inherited Property Key Index
        int ipkIndex = mComponent->mProperties.keys().indexOf(opKey);
        // Get Own Property Key Index
        int opkIndex = mComponent->mOwnProperties.keys().indexOf(opKey);

        // Init Component Is a Prototype
        bool opProtoType = mComponent->mIsProtoType;

        // Init Using Prototype Property Value
        bool opUseProto = mComponent->mIsProtoType ? false : (opkIndex == -1);
        //bool opUseProto = mComponent->mIsProtoType ? false : (ipkIndex == -1);

        // Init Property Value
        QString opValue = "";

        // Check Derived Component Property Key Index
        if (dcpkIndex >= 0) {
            // Set Property Value
            opValue = mDerivedComponent->mProperties.value(opKey).toString();

        // Check Inherited Property Key Index
        } else if (ipkIndex >= 0) {
            // Set Property Value
            opValue = mComponent->mProperties.value(opKey).toString();

        } else {

            // Set Property Value
            opValue = Utils::parseValue(opTypeAndValue);
        }

        // TODO: Handle Bindings And Formulas Better!!

        // ...

        // Switch Role
        switch (role) {
            default:
            case PropertyNameRole:      return opKey;
            case PropertyTypeRole:      return opType;
            case PropertyEnumsRole:     return opEnumValues;
            case PropertyValueRole:     return opValue;
            case PropertyReadOnlyRole:  return opReadOnly;
            case PropertyDefaultRole:   return opDefaultAlias;
            case PropertyIsBind:        return opBind;
            case PropertyIsFormula:     return opFormula;
            case PropertyIsProto:       return opProtoType;
            case PropertyUseProto:      return opUseProto;
            case PropertyIsBase:        return opBase;
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

    rNames[PropertyNameRole]     = "pName";
    rNames[PropertyTypeRole]     = "pType";
    rNames[PropertyEnumsRole]    = "pEnums";
    rNames[PropertyValueRole]    = "pValue";
    rNames[PropertyReadOnlyRole] = "pReadOnly";
    rNames[PropertyDefaultRole]  = "pDefault";
    rNames[PropertyIsBind]       = "pIsBind";
    rNames[PropertyIsFormula]    = "pIsFormula";
    rNames[PropertyIsProto]      = "pIsProto";
    rNames[PropertyUseProto]     = "pUseProto";
    rNames[PropertyIsBase]       = "pIsBase";

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
