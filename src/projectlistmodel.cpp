
#include <QDebug>

#include "src/projectlistmodel.h"


//==============================================================================
// Constructor
//==============================================================================
ProjectListModel::ProjectListModel(QObject* aParent)
    : QAbstractItemModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ProjectListModel::init()
{

}

//==============================================================================
// Clear
//==============================================================================
void ProjectListModel::clear()
{

}

//==============================================================================
// Index
//==============================================================================
QModelIndex ProjectListModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

//==============================================================================
// Parent
//==============================================================================
QModelIndex ProjectListModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

//==============================================================================
// Sibling
//==============================================================================
QModelIndex ProjectListModel::sibling(int row, int column, const QModelIndex& idx) const
{
    return QModelIndex();
}

//==============================================================================
// Row Count
//==============================================================================
int ProjectListModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

//==============================================================================
// Column Count
//==============================================================================
int ProjectListModel::columnCount(const QModelIndex& parent) const
{
    return 0;
}

//==============================================================================
// Has Childrent
//==============================================================================
bool ProjectListModel::hasChildren(const QModelIndex& parent) const
{
    return false;
}

//==============================================================================
// Data
//==============================================================================
QVariant ProjectListModel::data(const QModelIndex& index, int role) const
{
    return "";
}

//==============================================================================
// Destructor
//==============================================================================
ProjectListModel::~ProjectListModel()
{
    // ...
}
