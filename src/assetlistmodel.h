#ifndef ASSETLISTMODEL_H
#define ASSETLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFileInfoList>

//==============================================================================
// Asset List Model Class
//==============================================================================
class AssetListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentDir READ currentDir WRITE setCurrentDir NOTIFY currentDirChanged)

public:
    // Constructor
    explicit AssetListModel(const QString& aAssetsDir = "", QObject* aParent = NULL);

    // Set Assets Dir
    void setAssetsDir(const QString& aAssetsDir);

    // Get Current Dir
    QString currentDir();
    // Set Current Dir
    void setCurrentDir(const QString& aCurrentDir);

    // Get Index By Name
    Q_INVOKABLE int getIndexByName(const QString& aName);

    // Get File Path By Index
    Q_INVOKABLE QString getPathByIndex(const int& aIndex);

    // Destructor
    ~AssetListModel();

signals:
    // Current Dir Changed Signal
    void currentDirChanged(const QString& aCurrentDir);

protected:
    // Init
    void init();
    // Clear
    void clear();

    // Reload
    void reload();
    // Load Assets
    void loadAssets();

protected slots:
    // Assets Dir Update
    void assetsDirUpdate(const QString& aAssetsDir);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected: // Data
    friend class AssetBrowserWindow;

    // Item Field Roles
    enum EALMRoles {
        EALRName = Qt::UserRole + 1,
        EALRSize,
        EALRPath,
        EALRDimension,
        EALRIsDir
    };

    // Assets Dir
    QString         mAssetsDir;
    // Current Dir
    QString         mCurrentDir;
    // File Info List
    QFileInfoList   mFileList;
    // File Name Filters
    QStringList     mNameFilters;
};

#endif // ASSETLISTMODEL_H
