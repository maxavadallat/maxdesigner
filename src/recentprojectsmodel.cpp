#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

#include "recentprojectsmodel.h"
#include "constants.h"

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
    qDebug() << "RecentProjectsModel::storeRecentProject - aFilePath: " << aFilePath;

    // Get Index Of File Path
    int fpIndex = mRecentProjectList.indexOf(aFilePath);

    // Check Index
    if (fpIndex == 0) {
        return;
    }

    // Check Index
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

    // Check Count
    if (mRecentProjectList.count() > DEFAULT_RECENTPROJECTS_MAX) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), mRecentProjectList.count() - 1, mRecentProjectList.count() - 1);
        // Remove Last
        mRecentProjectList.removeLast();
        // End Remove Rows
        endRemoveRows();
    }

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
    // Init Recent Projects List File
    QFile rplFile(QDir::homePath() + "/" + DEFAULT_RECENTPROJECTLIST_FILE_NAME);

    // Open File
    if (rplFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read All Content
        QString rplContent = rplFile.readAll();
        // Close File
        rplFile.close();
        // Begin Reset Model
        beginResetModel();
        // Set Recent Project List
        mRecentProjectList = rplContent.split("\n");
        // End Reset Model
        endResetModel();
    } else {
        qWarning() << "RecentProjectsModel::loadRecentProjects - ERROR OPENING FILE! - rplFile: " << rplFile.fileName();
    }
}

//==============================================================================
// Save
//==============================================================================
void RecentProjectsModel::saveRecentProjects()
{
    // Init Recent Projects List File
    QFile rplFile(QDir::homePath() + "/" + DEFAULT_RECENTPROJECTLIST_FILE_NAME);

    // Open File
    if (rplFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream rplStream(&rplFile);
        // Write To Recent Project List Stream
        rplStream << mRecentProjectList.join("\n");
        // Flush
        rplStream.flush();
        // Close File
        rplFile.close();
    } else {
        qWarning() << "RecentProjectsModel::saveRecentProjects - ERROR SAVING FILE! - rplFile: " << rplFile.fileName();
    }
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
