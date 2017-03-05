#ifndef PROJECTITEMMODEL_H
#define PROJECTITEMMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QFileSystemModel>
#include <QStringList>
#include <QFileInfo>
#include <QThread>

//==============================================================================
// Project Tree Model
//==============================================================================
class ProjectTreeModel : public QFileSystemModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentPath READ currentPath WRITE setCurrentPath NOTIFY currentPathChanged)
    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY rootIndexChanged)

public:
    // Constructor
    explicit ProjectTreeModel(QObject* aParent = NULL);

    // Get Current Path
    QString currentPath();
    // Set Current Path
    void setCurrentPath(const QString& aPath);

    // Get Root Index
    QModelIndex rootIndex();

    // Destructor
    ~ProjectTreeModel();

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

#endif // PROJECTITEMMODEL_H
