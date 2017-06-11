#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "assetstreemodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
AssetsTreeModel::AssetsTreeModel(QObject* aParent)
    : QFileSystemModel(aParent)
    , mCurrentPath(QDir::homePath())
{
    qDebug() << "AssetsTreeModel created.";

    // Clear Filters
    mFilters.clear();

//    // Add Filters
//    mFilters = QString(DEFAULT_IMAGE_SUFFIXES).split(" ");
//    mFilters << QString(DEFAULT_QML_SUFFIX);
//    mFilters << QString(DEFAULT_JS_SUFFIX);

//    // Iterate Throug hFilters
//    for (int i=0; i<mFilters.count(); i++) {
//        // Add File Name Mask
//        mFilters[i] = QString("%1%2").arg(DEFAULT_FILE_NAME_MASK).arg(mFilters[i]);
//    }

    //qDebug() << "AssetsTreeModel::AssetsTreeModel - mFilters: " << mFilters;

    // Init
    init();

}

//==============================================================================
// Init
//==============================================================================
void AssetsTreeModel::init()
{
    // Set Filter
    setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    // Set Root Path
    setRootPath(mCurrentPath);
}

//==============================================================================
// Clear
//==============================================================================
void AssetsTreeModel::clear()
{
    // ...
}

//==============================================================================
// Get Current Path
//==============================================================================
QString AssetsTreeModel::currentPath()
{
    return mCurrentPath;
}

//==============================================================================
// Set Current Path
//==============================================================================
void AssetsTreeModel::setCurrentPath(const QString& aPath)
{
    // Check Current Path
    if (mCurrentPath != aPath) {
        //qDebug() << "AssetsTreeModel::setCurrentPath - aPath: " << aPath;
        // Set Current Path
        mCurrentPath = aPath;

        // Set Root
        setRootPath(mCurrentPath);
        // Emit Current Path Changed Signal
        emit currentPathChanged(mCurrentPath);
        // Emit Root Index Changed Signal
        emit rootIndexChanged();
    }
}

//==============================================================================
// Get Root Index
//==============================================================================
QModelIndex AssetsTreeModel::rootIndex()
{
    return index(mCurrentPath);
}

//==============================================================================
// Get Path By Index
//==============================================================================
QString AssetsTreeModel::getPathByIndex(const QModelIndex& aIndex)
{
    // Init File Info
    QFileInfo fileInfo(data(aIndex, FilePathRole).toString());

    return fileInfo.absoluteFilePath();
}

//==============================================================================
// Data
//==============================================================================
QVariant AssetsTreeModel::data(const QModelIndex& index, int role) const
{
    // Check Index
    if (!index.isValid()) {
        return QVariant();
    }

    // Switch Role
    switch (role) {
        case FileIconRole:          return QString("image://%1/%2").arg(DEFAULT_IMAGE_PROVIDER_ID).arg(QFileSystemModel::data(index, FilePathRole).toString());
        case (Qt::UserRole + 4):    return isDir(index);
    }

    return QFileSystemModel::data(index, role);
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int,QByteArray> AssetsTreeModel::roleNames() const
{
    // Init Role Names
    QHash<int,QByteArray> rNames;

    // Add Role Names
    rNames[FileNameRole]        = "fileName";
    rNames[FileIconRole]        = "fileIcon";
    rNames[FilePathRole]        = "filePath";
    rNames[Qt::UserRole + 4]    = "fileIsDir";

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
AssetsTreeModel::~AssetsTreeModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "AssetsTreeModel deleted.";
}
