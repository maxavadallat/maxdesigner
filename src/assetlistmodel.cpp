#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

#include "assetlistmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
AssetListModel::AssetListModel(QObject* aParent)
    : QAbstractListModel(aParent)
    , mCurrentDir(QDir::homePath())
{
    qDebug() << "AssetListModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void AssetListModel::init()
{
    // Set Name Filter
    mNameFilters = QString(DEFAULT_IMAGE_SUFFIXES).split(" ");

    // Get Name Filters Count
    int nfCount = mNameFilters.count();
    // Iterate Through Name Filters
    for (int i=0; i<nfCount; i++) {
        // Adjust Name Filters
        mNameFilters[i] = QString("*.%1").arg(mNameFilters[i]);
    }

    // Laod Assets
    loadAssets();

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void AssetListModel::clear()
{
    // Begin Reset Model
    beginResetModel();

    // Clear File List
    mFileList.clear();

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Reload
//==============================================================================
void AssetListModel::reload()
{
    // Clear
    clear();
    // Load Assets
    loadAssets();
}

//==============================================================================
// Load Assets
//==============================================================================
void AssetListModel::loadAssets()
{
    qDebug() << "AssetListModel::loadAssets - mCurrentDir: " << mCurrentDir;

    // Begin Reset Model
    beginResetModel();

    // Init Assets Dir
    QDir assetsDir(mCurrentDir);

    // Set File Info List
    mFileList = assetsDir.entryInfoList(mNameFilters, QDir::AllDirs | QDir::NoDot | QDir::Files, QDir::Name | QDir::DirsFirst);

    // End Reset Model
    endResetModel();
}

//==============================================================================
// Get Current Dir
//==============================================================================
QString AssetListModel::currentDir()
{
    return mCurrentDir;
}

//==============================================================================
// Set Current Dir
//==============================================================================
void AssetListModel::setCurrentDir(const QString& aCurrentDir)
{
    // Check Current Dir
    if (mCurrentDir != aCurrentDir) {
        // Set Current Dir
        mCurrentDir = aCurrentDir;
        // Emit Current Dir Changed Signal
        emit currentDirChanged(mCurrentDir);

        // Reload
    }
}

//==============================================================================
// Row Count
//==============================================================================
int AssetListModel::rowCount(const QModelIndex& aParent) const
{
    Q_UNUSED(aParent);

    return mFileList.count();
}

//==============================================================================
// Data
//==============================================================================
QVariant AssetListModel::data(const QModelIndex& aIndex, int aRole) const
{
    // Get Row Indw
    int rIndex = aIndex.row();

    // Check Row Index
    if (rIndex >= 0 && rIndex < rowCount()) {
        // Switch Role
        switch (aRole) {
            case EALRName:          return mFileList[rIndex].fileName();
            case EALRSize:          return mFileList[rIndex].size() / 1024;
            case EALRPath:          return mFileList[rIndex].absoluteFilePath();
            case EALRDimension:     return "";
            case EALRIsDir:         return mFileList[rIndex].isDir();
        }
    }

    return QVariant();
}

//==============================================================================
// Get Role Names
//==============================================================================
QHash<int, QByteArray> AssetListModel::roleNames() const
{
    // Init Role Names
    QHash<int, QByteArray> rNames;

    // Set Role Names
    rNames[EALRName]        = "assetName";
    rNames[EALRSize]        = "assetSize";
    rNames[EALRPath]        = "assetPath";
    rNames[EALRDimension]   = "assetDimension";
    rNames[EALRIsDir]       = "isDir";

    // ...

    return rNames;
}

//==============================================================================
// Destructor
//==============================================================================
AssetListModel::~AssetListModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "AssetListModel deleted.";
}
