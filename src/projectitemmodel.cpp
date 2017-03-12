
#include <QDebug>
#include <QDir>
#include <QDirIterator>

#include "projectitemmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ProjectTreeModel::ProjectTreeModel(QObject* aParent)
    : QFileSystemModel(aParent)
    //, mCurrentPath("/Users/max/Dev/MaxDesigner/assets")
    , mCurrentPath(QDir::homePath())
{
    qDebug() << "ProjectTreeModel created.";

    // Clear Filters
    mFilters.clear();

    // Add Filters
    mFilters = QString(DEFAULT_IMAGE_SUFFIXES).split(" ");
    mFilters << QString(DEFAULT_QML_SUFFIX);
    mFilters << QString(DEFAULT_JS_SUFFIX);

    // Iterate Throug hFilters
    for (int i=0; i<mFilters.count(); i++) {
        // Add File Name Mask
        mFilters[i] = QString("%1%2").arg(DEFAULT_FILE_NAME_MASK).arg(mFilters[i]);
    }

    //qDebug() << "ProjectTreeModel::ProjectTreeModel - mFilters: " << mFilters;

    // Init
    init();

//    // Start Worker Thread
//    mWorker->start(QThread::LowestPriority);
}

//==============================================================================
// Init
//==============================================================================
void ProjectTreeModel::init()
{
    // Set Root Path
    setRootPath(mCurrentPath);
}

//==============================================================================
// Clear
//==============================================================================
void ProjectTreeModel::clear()
{
    // ...
}

//==============================================================================
// Get Current Path
//==============================================================================
QString ProjectTreeModel::currentPath()
{
    return mCurrentPath;
}

//==============================================================================
// Set Current Path
//==============================================================================
void ProjectTreeModel::setCurrentPath(const QString& aPath)
{
    // Check Current Path
    if (mCurrentPath != aPath) {
        qDebug() << "ProjectTreeModel::setCurrentPath - aPath: " << aPath;
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
QModelIndex ProjectTreeModel::rootIndex()
{
    return index(mCurrentPath);
}

//==============================================================================
// Get Path By Index
//==============================================================================
QString ProjectTreeModel::getPathByIndex(const QModelIndex& aIndex)
{
    // Init File Info
    QFileInfo fileInfo(data(aIndex, FilePathRole).toString());

    return fileInfo.isDir() ? "" : fileInfo.absoluteFilePath();
}

//==============================================================================
// Data
//==============================================================================
QVariant ProjectTreeModel::data(const QModelIndex& index, int role) const
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
QHash<int,QByteArray> ProjectTreeModel::roleNames() const
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
ProjectTreeModel::~ProjectTreeModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "ProjectTreeModel deleted.";
}
