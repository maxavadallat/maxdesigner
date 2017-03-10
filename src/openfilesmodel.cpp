#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "openfilesmodel.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
OpenFilesModel::OpenFilesModel(QObject* aParent)
    : QAbstractListModel(aParent)
    , mProject(NULL)
    , mBusy(false)
    , mCurrentIndex(-1)
{
    qDebug() << "OpenFilesModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void OpenFilesModel::init()
{
    // ...
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

//    // Clear Component Map
//    mComponentMap.clear();
}

//==============================================================================
// Get Busy State
//==============================================================================
bool OpenFilesModel::busy()
{
    return mBusy;
}

//==============================================================================
// Set Busy State
//==============================================================================
void OpenFilesModel::setBusy(const bool& aBusy)
{
    // Check Busy State
    if (mBusy != aBusy) {
        // Set Busy State
        mBusy = aBusy;
        // Emit Busy State Changed Signal
        emit busyChanged(mBusy);
    }
}

//==============================================================================
// Get Current Index
//==============================================================================
int OpenFilesModel::currentIndex()
{
    return mCurrentIndex;
}

//==============================================================================
// Set Current Index
//==============================================================================
void OpenFilesModel::setCurrentIndex(const int& aCurrentIndex)
{
    // Get Count
    int ofCount = rowCount();
    // Check Current Index
    if (mCurrentIndex != aCurrentIndex && aCurrentIndex >= 0 && aCurrentIndex < ofCount) {
        // Set Current Index
        mCurrentIndex = aCurrentIndex;
        // Emit Current Index Changed Signal
        emit currentIndexChanged(mCurrentIndex);
    }
}

//==============================================================================
// Set Project Model
//==============================================================================
void OpenFilesModel::setProjectModel(ProjectModel* aProject)
{
    qDebug() << "OpenFilesModel::setProjectModel - aProject.projectName: " << (aProject ? aProject->projectName() : "");

    // Save Recent Files
    saveRecentFiles();
    // Clear
    clear();

    // Set Project Model
    mProject = aProject;

    // Open Recent Files
    openRecentFiles();
}

//==============================================================================
// Open File - Add File To
//==============================================================================
int OpenFilesModel::openFile(const QString& aFilePath)
{
    // Init New File Info
    QFileInfo fileInfo(aFilePath);

    // Check If File Exists
    if (!fileInfo.exists()) {
        qWarning() << "OpenFilesModel::openFile - aFilePath: " << aFilePath << " - FILE DOESN'T EXIST!";
        return -1;
    }

    // Get Index of File Info
    int fIndex = mFileInfoList.indexOf(fileInfo);

    // Check Index
    if (fIndex >= 0) {
        // Emit File Selected Signal
        emit fileSelected(aFilePath);
        // File Already Open
        return -1;
    }

    // Get File Info List Count
    int filCount = mFileInfoList.count();

    // Iterate Through File info List
    for (int i=0; i<filCount; i++) {
        // Check File Name
        if (fileInfo.fileName() < mFileInfoList[i].fileName()) {
            // Begin Insert Rows
            beginInsertRows(QModelIndex(), i, i);
            // Insert Item
            mFileInfoList.insert(i, fileInfo);
            // End Insert Rows
            endInsertRows();

            // Emit File Opened Signal

            return i;
        }
    }

    // Begin Insert Rows
    beginInsertRows(QModelIndex(), filCount, filCount);
    // Append File Info
    mFileInfoList << fileInfo;
    // End Insert Rows
    endInsertRows();

    // Emit File Opened Signal

    return mFileInfoList.count() - 1;
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
        // Get File Path
        QString filePath = mFileInfoList[aIndex].absoluteFilePath();
        // Remove Item
        mFileInfoList.removeAt(aIndex);
        // End Remove Rows
        endRemoveRows();

        // Emit File Closed Signal
        emit fileClosed(filePath);
    }
}

//==============================================================================
// Close File
//==============================================================================
void OpenFilesModel::closeFile(const QString& aFilePath)
{
    // Init File Info
    QFileInfo fileInfo(aFilePath);

    // Get Index
    int fIndex = mFileInfoList.indexOf(fileInfo);

    // Check Index
    if (fIndex >= 0) {
        // Close File
        closeFile(fIndex);
    }

    // ...
}

//==============================================================================
// Select File
//==============================================================================
void OpenFilesModel::selectFile(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mFileInfoList.count()) {
        // Emit File Selected Signal
        emit fileSelected(mFileInfoList[aIndex].absoluteFilePath());
    }
}

//==============================================================================
// Select File
//==============================================================================
void OpenFilesModel::selectFile(const QString& aFilePath)
{
    // Init File Info
    QFileInfo fileInfo(aFilePath);

    // Get Index
    int fIndex = mFileInfoList.indexOf(fileInfo);

    // Check Index
    if (fIndex >= 0) {
        // SelectFile
        selectFile(fIndex);
    }
}

//==============================================================================
// Open Component
//==============================================================================
void OpenFilesModel::openComponent(ComponentInfo* aComponent)
{
    // Check Project Model
    if (mProject) {
        // ...
    }

    // Get Component Index
    int cIndex = compoenntIndex(aComponent);

    // Check Compoennt Index
    if (cIndex >= 0) {
        // Emit Component Selected
        emit componentSelected(aComponent);
        return;
    }

    // Check Component
    if (aComponent) {
        // Open File
        openFile(aComponent->infoPath());
        // Emit Component Opened Signal
        emit componentOpened(aComponent);
    }
}

//==============================================================================
// Close Component
//==============================================================================
void OpenFilesModel::closeComponent(ComponentInfo* aComponent)
{
    // Get Component Index
    int cIndex = compoenntIndex(aComponent);

    // Check Component Index
    if (cIndex >= 0) {
        // Close File
        closeFile(cIndex);
        // Emit Component Closed
        emit compoenntClosed(aComponent);
    }
}

//==============================================================================
// Open RecentFiles
//==============================================================================
void OpenFilesModel::openRecentFiles()
{
    // Check Current Project
    if (!mProject) {
        return;
    }

    // Init Recent File Path
    QString recentFilesPath = mProject->absoluteProjectPath() + "/" + DEFAULT_RECENTFILESLIST_FILE_NAME;
    // Init Recent Project File
    QFile rFiles(recentFilesPath);

    // Set Busy
    setBusy(true);

    // Open Recent Files
    if (rFiles.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read All Content
        QString rfContent = rFiles.readAll();
        // Set Recent File List
        QStringList recentFiles = rfContent.split("\n");
        // Get Recent Files Count
        int rfCount = recentFiles.count();
        // Iterate Through Recent Files
        for (int i=0; i<rfCount; i++) {
            // Open File
            openFile(recentFiles[i]);
        }

        // Close Files
        rFiles.close();
    }

    // Set Busy
    setBusy(false);
}

//==============================================================================
// Save Recent files
//==============================================================================
void OpenFilesModel::saveRecentFiles()
{
    // Check Current Project
    if (!mProject) {
        return;
    }

    // Init Recent File Path
    QString recentFilesPath = mProject->absoluteProjectPath() + "/" + DEFAULT_RECENTFILESLIST_FILE_NAME;
    // Init Recent Project File
    QFile rFiles(recentFilesPath);

    // Set Busy
    setBusy(true);

    // Open Recent Files
    if (rFiles.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream rfStream(&rFiles);
        // Get Open Files Count
        int ofCount = mFileInfoList.count();
        // Iterate Through File Info List
        for (int i=0; i<ofCount; i++) {
            // Add File Path
            rfStream << mFileInfoList[i].absoluteFilePath();
            // Add New Line
            rfStream << "\n";
        }

        // Flush Stream
        rfStream.flush();
        // Close Files
        rFiles.close();
    }

    // Set Busy
    setBusy(false);
}

//==============================================================================
// Get Compoennt index
//==============================================================================
int OpenFilesModel::compoenntIndex(ComponentInfo* aComponent)
{
    // Init Component File Info
    QFileInfo componentInfo(aComponent->infoPath());

    return mFileInfoList.indexOf(componentInfo);
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
            case FilePathRole:      return mFileInfoList[i].absoluteFilePath();
            case FileIconRole:      return "";
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
    rNames[FilePathRole] = "filePath";
    rNames[FileIconRole] = "fileIcon";

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

    qDebug() << "OpenFilesModel deleted.";
}
