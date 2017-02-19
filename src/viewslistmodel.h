#ifndef VIEWSLISTMODEL_H
#define VIEWSLISTMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QJsonObject>

class ViewInfo;

//==============================================================================
// View List Model
//==============================================================================
class ViewsListModel : public QAbstractListModel
{
public:
    // Constructor
    explicit ViewsListModel(QObject* aParent = NULL);
    // Destructor
    ~ViewsListModel();

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

    // View List
    QList<ViewInfo>    mViewList;

};









//==============================================================================
// View Info Class
//==============================================================================
class ViewInfo : public QObject
{
public:
    // Constructor
    explicit ViewInfo(const QString& aName, QObject* aParent = NULL);

    // Get Component Name
    QString name();

    // Save Info
    void save();

    // Destructor
    ~ViewInfo();

private:

    // Init
    void init();

private: // Data
    // Name
    QString     mName;
    // Component Info
    QJsonObject mInfo;
};


#endif // VIEWSLISTMODEL_H
