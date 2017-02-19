#ifndef PROJECTLISTMODEL_H
#define PROJECTLISTMODEL_H

#include <QObject>
#include <QAbstractItemModel>

//==============================================================================
// Project List Model
//==============================================================================
class ProjectListModel : public QAbstractItemModel
{
public:
    // Constructor
    explicit ProjectListModel(QObject* aParent = NULL);
    // Destructor
    ~ProjectListModel();

private:
    // Init
    void init();
    // Clear
    void clear();

public: // from QAbstractItemModel

    // Index
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    // Parent
    virtual QModelIndex parent(const QModelIndex& child) const;
    // Sibling
    virtual QModelIndex sibling(int row, int column, const QModelIndex& idx) const;
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Column Count
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
    // Has Childrent
    virtual bool hasChildren(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private: // Data

};

#endif // PROJECTLISTMODEL_H
