#include <QQmlEngine>
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
    qDebug() << "ComponentPropertiesModel created for " << (mComponent ? mComponent->mName : "NULL");

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
    // Clear Component Properties
    clearComponentProperties();

    // ...
}

//==============================================================================
// Load Component Properties
//==============================================================================
void ComponentPropertiesModel::loadComponentProperties()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    qDebug() << "ComponentPropertiesModel::loadComponentProperties - mComponent: " << mComponent->mName;

    // Build Hierarchy
    addComponentToHierarchy(mComponent->mBaseName);
}

//==============================================================================
// Clear Component Properties
//==============================================================================
void ComponentPropertiesModel::clearComponentProperties()
{
    // Chekc Hierarchy
    if (mBaseComponentProperties.count() > 0) {
        qDebug() << "ComponentPropertiesModel::clearComponentProperties - keys: " << mBaseComponentProperties.keys();

        // Begin Reset Model
        beginResetModel();

        // Get Keys Count
        int kCount = mBaseComponentProperties.keys().count();

        // Iterate Through Keys
        for (int i=0; i<kCount; i++) {
            // Get Base Component Model
            ComponentOwnPropertiesModel* bcopModel = mBaseComponentProperties.value(mBaseComponentProperties.keys()[i]);
            // Check Model
            if (bcopModel) {

                try {

                    // Check Component
                    if (bcopModel->mComponent) {
                        //qDebug() << "ComponentPropertiesModel::clearComponentProperties - mComponent: " << bcopModel->mComponent->mName;
                        // ...
                    }
                    // Delete Model
                    delete bcopModel;

                } catch (std::exception& exception) {
                    qCritical() << "ComponentPropertiesModel::clearComponentProperties - exception: " << exception.what();
                }
            }
        }

        // Clear Keys
        mBaseComponentProperties.clear();

        // End Reset Model
        endResetModel();
    }
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
            qDebug() << "ComponentPropertiesModel::addComponentToHierarchy - aBaseName: " << aBaseName;

            // Get Filtered Own Property Keys
            QStringList pKeys = baseComponent->mOwnProperties.keys();

            // Check Filtered Property Keys
            if (pKeys.count() > 0 && mBaseComponentProperties.keys().indexOf(aBaseName) < 0) {
                // Begin Insert Rows
                beginInsertRows(QModelIndex(), rowCount(), rowCount());
                // Create New Component Own Properties Model
                ComponentOwnPropertiesModel* newBCOPModel = new ComponentOwnPropertiesModel(baseComponent, mProject, mComponent);
                // Set Ownership
                QQmlEngine::setObjectOwnership(newBCOPModel, QQmlEngine::CppOwnership);
                // Set Base Component Own Properties Model
                mBaseComponentProperties[aBaseName] = newBCOPModel;
                // End Insert Rows
                endInsertRows();
            } else {
                //qDebug() << "ComponentPropertiesModel::addComponentToHierarchy - aBaseName: " << aBaseName << " - SKIPPING.";
            }

            // Recursively Add Base Component's Base Component
            addComponentToHierarchy(baseComponent->mBaseName);

        } else {
            qWarning() << "ComponentPropertiesModel::addComponentToHierarchy - aBaseName: " << aBaseName << " - COMPONENT NOT FOUND!!";
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
        // Clear
        clear();
        // Set Current Component
        mComponent = aComponent;
        // Load Component Properties
        loadComponentProperties();
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
    }
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

    //qDebug() << "ComponentPropertiesModel::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // Get Base Components Count
    int bcCount = rowCount();

    // Go Thru Hieararchy
    for (int i=0; i<bcCount; i++) {
        // Get Base Component's Own Property Model
        ComponentOwnPropertiesModel* bcopModel = mBaseComponentProperties.value(mBaseComponentProperties.keys()[i]);
        // Check Model
        if (bcopModel) {
            // Check If Has Property
            if (bcopModel->hasProperty(aName)) {
                //qDebug() << "ComponentPropertiesModel::setComponentProperty - mComponent: " <<  mComponent->mName << " - aName: " << aName << " - aValue: " << aValue;
                // Set Component Property
                mComponent->mProperties[aName] = aValue.toString();
                // Set Component Dirty
                mComponent->setDirty(true);
                // Refresh Base Component Own Properties Model
                bcopModel->refreshProperty(aName);

                return true;
            }
        }
    }

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

    //qDebug() << "ComponentPropertiesModel::clearComponentProperty - aName: " << aName;

    // Get Base Components Model Count
    int bcmCount = rowCount();

    // Iterate Thru Base Components
    for (int i=0; i<bcmCount; i++) {
        // Get Base Component Own Properties Model
        ComponentOwnPropertiesModel* bcopModel = mBaseComponentProperties.value(mBaseComponentProperties.keys()[i]);
        // Check Model
        if (bcopModel && bcopModel->hasProperty(aName)) {
            // Remove Key
            mComponent->mProperties.remove(aName);
            // Set Component Dirty
            mComponent->setDirty(true);
            // Refresh For base Component Property List Update
            bcopModel->refreshProperty(aName);

            return true;
        }
    }

    return false;
}

//==============================================================================
// Check If Component Property Is Set
//==============================================================================
bool ComponentPropertiesModel::componentPropertyIsSet(const QString& aName)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    return (mComponent->mProperties.keys().indexOf(aName) >= 0);
}

//==============================================================================
// Get Component Property List
//==============================================================================
ComponentOwnPropertiesModel* ComponentPropertiesModel::componentPropertyList(const int& aIndex) const
{
    // Check Index
    if (aIndex >= 0 && aIndex < rowCount()) {

        return mBaseComponentProperties.value(mBaseComponentProperties.keys()[aIndex]);

    } else {
        //qWarning() << "ComponentPropertiesModel::componentPropertyList - aIndex: " << aIndex << " - OUT OF BOUNDS!!";
    }

    return NULL;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentPropertiesModel::rowCount(const QModelIndex& ) const
{
    return mBaseComponentProperties.keys().count();
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
            case ESMRBaseName:  return mBaseComponentProperties.keys()[pmRow];
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
