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
    qDebug() << "ComponentImportsModel created.";

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
    // ...
}

//==============================================================================
// Load Component Imports
//==============================================================================
void ComponentImportsModel::loadComponentImports()
{
    // Clear
    clear();

    // Begin Reset Model
    beginResetModel();

    // ...

    // End Reset Model
    endResetModel();
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
        // Save Previous Component Imports
        saveComponentImports();
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed Signal
        emit currentComponentChanged(mComponent);
        // Load New Component Imports
        loadComponentImports();
    }
}

//==============================================================================
// Add Import
//==============================================================================
void ComponentImportsModel::addImport(const QString& aImport)
{
    // Check If Import Valid
    if (!importValid(aImport)) {
        return;
    }

    qDebug() << "ComponentImportsModel::addImport - aImport: " << aImport;

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    // Append Import
    mComponent->mImports << QJsonValue(aImport);
    // End Insert Rows
    endInsertRows();

    // Set Dirty
    mComponent->setDirty(true);

    // Emit Import Added Signal
    emit mComponent->importAdded(rowCount() - 1);
}

//==============================================================================
// Remove Import
//==============================================================================
void ComponentImportsModel::removeImport(const QString& aImport)
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // Get Imports Count
    int iCount = mComponent->mImports.count();
    // Iterate Through Imports
    for (int i=0; i<iCount; i++) {
        // Get String Value
        QString jsonValueString = mComponent->mImports[i].toString();
        // Check JS String Value
        if (jsonValueString == aImport) {
            // Begin Remove Rows
            beginRemoveRows(QModelIndex(), i, i);
            // Remove Import
            mComponent->mImports.removeAt(i);
            // End Remove Rows
            endRemoveRows();
            // Set Dirty
            mComponent->setDirty(true);
            // Emit Import Removed Signal
            emit mComponent->importRemoved(i);

            return;
        }
    }
}

//==============================================================================
// Remove Import
//==============================================================================
void ComponentImportsModel::removeImport(const int& aIndex)
{
    // Check Index
    if (mComponent && aIndex >= 0 && aIndex < mComponent->mImports.count()) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Import
        mComponent->mImports.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
        // Set Dirty
        mComponent->setDirty(true);
        // Emit Import Removed Signal
        emit mComponent->importRemoved(aIndex);
    }
}

//==============================================================================
// Check If Import Vali
//==============================================================================
bool ComponentImportsModel::importValid(const QString& aImport)
{
    // Check Component
    if (!mComponent) {
        return false;
    }

    // Check Import
    if (!aImport.isEmpty()) {
        // Get Imports Count
        int iCount = rowCount();
        // Iterate Through Imports
        for (int i=0; i<iCount; i++) {
            // Get String Value
            QString jsonValueString = mComponent->mImports[i].toString();
            // Check JS String Value
            if (jsonValueString == aImport) {
                return false;
            }
        }

        return true;
    }

    return false;
}

//==============================================================================
// Row Count
//==============================================================================
int ComponentImportsModel::rowCount(const QModelIndex& ) const
{
    return mComponent ? mComponent->mImports.count() : 0;
}

//==============================================================================
// Data
//==============================================================================
QVariant ComponentImportsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int imRow = index.row();

    // Check Row
    if (mComponent && imRow >= 0 && imRow < rowCount()) {
        // Switch Role
        switch (role) {
            default:
            case IMRNameRole:   return mComponent->mImports[imRow].toString();
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

    qDebug() << "ComponentImportsModel deleted.";
}
