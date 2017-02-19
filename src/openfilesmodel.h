#ifndef OPENFILESMODEL_H
#define OPENFILESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QFileInfoList>

//==============================================================================
// Opened File List Model
//==============================================================================
class OpenFilesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor
    explicit OpenFilesModel(QObject* aParent = NULL);

    // Open File
    void openFile(const QString& aFilePath);
    // Close File
    void closeFile(const int& aIndex);

    // Open RecentFiles
    void openRecentFiles();
    // Clear recent files
    void clearRecentFiles();
    // Save Recent files
    void saveRecentFiles();

    // Destructor
    ~OpenFilesModel();

signals:

private:
    // Init
    void init();
    // Clear
    void clear();

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
        FileNameRole = Qt::UserRole + 1
    };

    // Open File List
    QFileInfoList   mFileInfoList;
};

#endif // OPENFILESMODEL_H
