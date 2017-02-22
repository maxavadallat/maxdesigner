#ifndef RECENTPROJECTSMODEL_H
#define RECENTPROJECTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

//==============================================================================
// Recent Projects Model
//==============================================================================
class RecentProjectsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Constructor
    explicit RecentProjectsModel(QObject* aParent = NULL);

    // Store Recent Project
    void storeRecentProject(const QString& aFilePath);
    // Clear
    void clear();

    // Destructor
    ~RecentProjectsModel();

private:
    // Init
    void init();

    // Load
    void loadRecentProjects();
    // Save
    void saveRecentProjects();

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
        FilePathRole = Qt::UserRole + 1
    };

    // Recent Projects
    QStringList     mRecentProjectList;
};

#endif // RECENTPROJECTSMODEL_H
