#ifndef OPENFILESMODEL_H
#define OPENFILESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QFileInfoList>
#include <QMap>

class ComponentInfo;
class ProjectModel;

//==============================================================================
// Opened File List Model
//==============================================================================
class OpenFilesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

public:
    // Constructor
    explicit OpenFilesModel(QObject* aParent = NULL);

    // Set Project Model
    void setProjectModel(ProjectModel* aProject);

    // Get Busy State
    bool busy();

    // Get Current Index
    int currentIndex();
    // Set Current Index
    void setCurrentIndex(const int& aCurrentIndex);
    // Open File
    Q_INVOKABLE int openFile(const QString& aFilePath);
    // Close File
    Q_INVOKABLE void closeFile(const int& aIndex);
    // Close File
    Q_INVOKABLE void closeFile(const QString& aFilePath);
    // Select File
    Q_INVOKABLE void selectFile(const int& aIndex);
    // Select File
    Q_INVOKABLE void selectFile(const QString& aFilePath);
    // Open Component
    Q_INVOKABLE void openComponent(ComponentInfo* aComponent);
    // Close Component
    Q_INVOKABLE void closeComponent(ComponentInfo* aComponent);

    // Destructor
    ~OpenFilesModel();

signals:
    // Busy State Changed Signal
    void busyChanged(const bool& aBusy);

    // File Opened Signal
    void fileOpened(const QString& aFilePath);
    // File Selected Signal
    void fileSelected(const QString& aFilePath);

    // Component Opened Signal
    void componentOpened(ComponentInfo* aComponent);
    // Component Selected Signal
    void componentSelected(ComponentInfo* aComponent);

    // Current Index Changed Signal
    void currentIndexChanged(const int& aCurrentIndex);

    // File Closed Signal
    void fileClosed(const QString& aFilePath);
    // Component Closed Signal
    void compoenntClosed(ComponentInfo* aComponent);

private:
    // Init
    void init();
    // Clear
    void clear();

    // Set Busy State
    void setBusy(const bool& aBusy);

    // Open RecentFiles
    void openRecentFiles();
    // Save Recent files
    void saveRecentFiles();

    // Get Compoennt index
    int compoenntIndex(ComponentInfo* aComponent);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private: // Data

    // Item Field Roles
    enum ItemRoles {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileIconRole
    };

    // Project Model
    ProjectModel*               mProject;
    // Busy State
    bool                        mBusy;
    // Open File List
    QFileInfoList               mFileInfoList;
//    // Component File Info Index Map
//    QMap<ComponentInfo*, int>   mComponentMap;
    // Current Index
    int                         mCurrentIndex;
};

#endif // OPENFILESMODEL_H
