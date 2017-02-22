#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "recentprojectsmodel.h"

//==============================================================================
// Constructor
//==============================================================================
RecentProjectsModel::RecentProjectsModel(QObject* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void RecentProjectsModel::init()
{
    // Load Recent Projects
    loadRecentProjects();
}

//==============================================================================
// Store Recent Project
//==============================================================================
void RecentProjectsModel::storeRecentProject(const QString& aFilePath)
{
    // Get Index Of File Path
    int fpIndex = mRecentProjectList.indexOf(aFilePath);

    // Check Path
    if (fpIndex > 0) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), fpIndex, fpIndex);
        // Remove Recent Project
        mRecentProjectList.removeAt(fpIndex);
        // End Remove Rows
        endRemoveRows();
    }

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), 0, 0);
    // Insert Project File Path
    mRecentProjectList.insert(0, aFilePath);
    // End Insert Rows
    endInsertRows();

    // Save Recent Projects
    saveRecentProjects();
}

//==============================================================================
// Clear
//==============================================================================
void RecentProjectsModel::clear()
{
    // Begin Reset Model
    beginResetModel();
    // Clear Recent Projects
    mRecentProjectList.clear();
    // End Reset Model
    endResetModel();
}

//==============================================================================
// Load
//==============================================================================
void RecentProjectsModel::loadRecentProjects()
{
    // ...
}

//==============================================================================
// Save
//==============================================================================
void RecentProjectsModel::saveRecentProjects()
{
    // ...
}

//==============================================================================
// Row Count
//==============================================================================
int RecentProjectsModel::rowCount(const QModelIndex& ) const
{
    return mRecentProjectList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant RecentProjectsModel::data(const QModelIndex& index, int role) const
{
    // Get Row
    int fpRow = index.row();
    // Check Row
    if (fpRow >= 0 && fpRow < mRecentProjectList.count()) {
        // Switch Role
        switch (role) {
            case FilePathRole:  return mRecentProjectList[fpRow];
        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> RecentProjectsModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Add Role Names
    rNames[FilePathRole] = "filePath";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
RecentProjectsModel::~RecentProjectsModel()
{
    // Clear
    clear();
}
