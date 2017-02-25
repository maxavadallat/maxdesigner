
#include <QDebug>

#include "src/projectitemmodel.h"


//==============================================================================
// Constructor
//==============================================================================
ProjectItemModel::ProjectItemModel(QObject* aParent)
    : QAbstractItemModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ProjectItemModel::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ProjectItemModel::clear()
{

}

//==============================================================================
// Index
//==============================================================================
QModelIndex ProjectItemModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

//==============================================================================
// Parent
//==============================================================================
QModelIndex ProjectItemModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

//==============================================================================
// Sibling
//==============================================================================
QModelIndex ProjectItemModel::sibling(int row, int column, const QModelIndex& idx) const
{
    return QModelIndex();
}

//==============================================================================
// Row Count
//==============================================================================
int ProjectItemModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

//==============================================================================
// Column Count
//==============================================================================
int ProjectItemModel::columnCount(const QModelIndex& parent) const
{
    return 0;
}

//==============================================================================
// Has Childrent
//==============================================================================
bool ProjectItemModel::hasChildren(const QModelIndex& parent) const
{
    return false;
}

//==============================================================================
// Data
//==============================================================================
QVariant ProjectItemModel::data(const QModelIndex& index, int role) const
{
    return "";
}

//==============================================================================
// Destructor
//==============================================================================
ProjectItemModel::~ProjectItemModel()
{
    // ...
}
