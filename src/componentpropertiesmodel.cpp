#include <QDebug>

#include "componentpropertiesmodel.h"
#include "componentownpropertiesmodel.h"
#include "componentinfo.h"
#include "mainwindow.h"
#include "projectmodel.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentPropertiesModel::ComponentPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, QObject* aParent)
    : QAbstractListModel(aParent)
    , mComponent(aComponent)
    , mProject(aProject)
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
    // Chekc Hierarchy
    if (mHierarchy.count() > 0) {
        // Begin Reset Model
        beginResetModel();
        // Clear
        mHierarchy.clear();
        // End Reset Model
        endResetModel();
    }
}

//==============================================================================
// Load Component Properties
//==============================================================================
void ComponentPropertiesModel::loadComponentProperties()
{
    // Clear
    clear();

    // Check Component
    if (!mComponent) {
        return;
    }

    // Build Hierarchy
    addComponentToHierarchy(mComponent->mBaseName);
}

//==============================================================================
// Add Component To Hierarchy
//==============================================================================
void ComponentPropertiesModel::addComponentToHierarchy(const QString& aBaseName)
{
    // Check Project Model
    if (!mProject) {
        qWarning() << "ComponentPropertiesModel::addComponentToHierarchy - NO PROJECT!!";
        return;
    }

    // Check Component Base Name
    if (!aBaseName.isEmpty()) {
        // Get Component
        ComponentInfo* baseComponent = mProject->getComponentByName(aBaseName);
        // Check Base Component
        if (baseComponent) {
            // Get Filtered Own Property Keys
            QStringList pKeys = baseComponent->mOwnProperties.keys();
            // Check Filtered Property Keys
            if (pKeys.count() > 0) {
                // Begin Insert Rows
                beginInsertRows(QModelIndex(), rowCount(), rowCount());
                // Append To Hierarchy
                mHierarchy << baseComponent;
                // End Insert Rows
                endInsertRows();
            }
            // Recursively Add Base Component's Base Component
            addComponentToHierarchy(baseComponent->mBaseName);
        }
    }
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
// Get Component Property Name By Index
//==============================================================================
QString ComponentPropertiesModel::componentPropertyName(const QString& aBaseName, const int& aIndex)
{

    return "";
}

//==============================================================================
// Set Component Own Property Value
//==============================================================================
bool ComponentPropertiesModel::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    qDebug() << "ComponentPropertiesModel::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // ...

    return false;
}

//==============================================================================
// Clear Component Property
//==============================================================================
bool ComponentPropertiesModel::clearComponentProperty(const QString& aName)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    qDebug() << "ComponentPropertiesModel::clearComponentProperty - aName: " << aName;

    // Check Property Keys
    if (mComponent->mProperties.keys().indexOf(aName) >= 0) {

        // Remove Key
        mComponent->mProperties.remove(aName);


        return true;
    }

    // ...

    return false;
}

//==============================================================================
// Get Component Property List
//==============================================================================
QAbstractListModel* ComponentPropertiesModel::componentPropertyList(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {

    }

    return NULL;
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
