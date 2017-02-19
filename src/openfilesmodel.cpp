#include <QDebug>

#include "src/openfilesmodel.h"

//==============================================================================
// Constructor
//==============================================================================
OpenFilesModel::OpenFilesModel(QObject* aParent)
    : QAbstractListModel(aParent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void OpenFilesModel::init()
{
    // Open Recent Files
    openRecentFiles();
}

//==============================================================================
// Clear
//==============================================================================
void OpenFilesModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear File Info List
    mFileInfoList.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Open File
//==============================================================================
void OpenFilesModel::openFile(const QString& aFilePath)
{
    // Init New File Info
    QFileInfo fileInfo(aFilePath);

    // Get File Info List Count
    int filCount = mFileInfoList.count();
    // Iterate Through File info List
    for (int i=0; i<filCount; i++) {
        if (fileInfo.fileName() < mFileInfoList[i].fileName()) {
            // Begin Insert Rows
            beginInsertRows(QModelIndex(), i, i);
            // Insert Item
            mFileInfoList.insert(i, fileInfo);
            // End Insert Rows
            endInsertRows();
            return;
        }
    }

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), filCount, filCount);
    // Append File Info
    mFileInfoList << fileInfo;
    // End Insert Rows
    endInsertRows();
}

//==============================================================================
// Close File
//==============================================================================
void OpenFilesModel::closeFile(const int& aIndex)
{
    // Get File Info List Count
    int filCount = mFileInfoList.count();
    // Check Index
    if (aIndex >= 0 && aIndex < filCount) {
        // Begin Remove Rows
        beginRemoveRows(QModelIndex(), aIndex, aIndex);
        // Remove Item
        mFileInfoList.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();
    }
}

//==============================================================================
// Open RecentFiles
//==============================================================================
void OpenFilesModel::openRecentFiles()
{

}

//==============================================================================
// Clear recent files
//==============================================================================
void OpenFilesModel::clearRecentFiles()
{

}

//==============================================================================
// Save Recent files
//==============================================================================
void OpenFilesModel::saveRecentFiles()
{

}

//==============================================================================
// Row Count
//==============================================================================
int OpenFilesModel::rowCount(const QModelIndex& ) const
{
    return mFileInfoList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant OpenFilesModel::data(const QModelIndex& index, int role) const
{
    // Get Index
    int i = index.row();
    // Get File Info List Count
    int filCount = mFileInfoList.count();


    // Check Index
    if (i >= 0 && i < filCount) {
        // Switch Role
        switch (role) {
            case FileNameRole:      return mFileInfoList[i].fileName();
        }
    }

    return "";
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> OpenFilesModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Add Role Names
    rNames[FileNameRole] = "fileName";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
OpenFilesModel::~OpenFilesModel()
{
    // Save Recent Files
    saveRecentFiles();
    // Clear
    clear();

}
