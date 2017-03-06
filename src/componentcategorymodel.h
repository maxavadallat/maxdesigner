#ifndef COMPONENTCATEGORYMODEL_H
#define COMPONENTCATEGORYMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

//==============================================================================
// Components Category List Model
//==============================================================================
class ComponentCategoryModel : public QAbstractListModel
{
public:
    // Constructor
    explicit ComponentCategoryModel(QObject* aParent = NULL);

    // Get index
    int getIndex(const QString& aCategory);

    // Destructor
    ~ComponentCategoryModel();

public: // From QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:

    // Init
    void init();
    // Clear
    void clear();

private: // Data

    // Categories
    QStringList     mCategories;
};

#endif // COMPONENTCATEGORYMODEL_H
