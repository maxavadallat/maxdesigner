#ifndef DATASOURCESMODEL_H
#define DATASOURCESMODEL_H

#include <QObject>
#include <QAbstractListModel>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Data Sources List Model
//==============================================================================
class DataSourcesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Set Data Sources Dir
    void setDataSourcesDir(const QString& aDirPath);

    // Add Data Source
    bool addDataSource(ComponentInfo* aComponent);
    // Remove Data Source
    bool removeDataSource(const int& aIndex);

    // Get Data Source Index By Name
    int getDataSourceIndex(const QString& aName);
    // Get Data Source By Name
    ComponentInfo* getDataSource(const QString& aName, const bool& aPreload = false);
    // Get Data Source By Index
    Q_INVOKABLE ComponentInfo* getDataSourceByIndex(const int& aIndex);

    // Destructor
    ~DataSourcesModel();

protected:
    friend class ProjectModel;

    // Constructor
    explicit DataSourcesModel(ProjectModel* aProjectModel, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

    // Load Data Sources
    void loadDataSources();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

private: // Data
    // Item Field Roles
    enum EDSItemRoles {
        EDSRName = Qt::UserRole + 1,
        EDSRDirty
    };

    // Project Model
    ProjectModel*                   mProjectModel;
    // Data Sources
    QMap<QString, ComponentInfo*>   mDataSources;
    // Data Sources Dir
    QString                         mDataSourcesDir;
};

#endif // DATASOURCESMODEL_H
