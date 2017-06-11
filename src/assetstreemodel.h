#ifndef ASSETSTREEMODEL_H
#define ASSETSTREEMODEL_H

#include <QObject>
#include <QFileSystemModel>


//==============================================================================
// Assets Tree Model
//==============================================================================
class AssetsTreeModel : public QFileSystemModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY rootIndexChanged)

public:
    // Constructor
    explicit AssetsTreeModel(QObject* aParent = NULL);

    // Get Current Path
    QString currentPath();
    // Set Current Path
    void setCurrentPath(const QString& aPath);

    // Get Root Index
    QModelIndex rootIndex();

    // Get Path By Index
    Q_INVOKABLE QString getPathByIndex(const QModelIndex& aIndex);

    // Destructor
    ~AssetsTreeModel();

signals:
    // Current Path Changed Signal
    void currentPathChanged(const QString& aPath);
    // Root Index Has Been Changed Signal
    void rootIndexChanged();

protected:
    // Init
    void init();
    // Clear
    void clear();

public: // from QAbstractItemModel
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

private: // Data
    // Current Path
    QString                 mCurrentPath;
    // Filters
    QStringList             mFilters;
};

#endif // ASSETSTREEMODEL_H
