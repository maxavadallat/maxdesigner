#ifndef COMPONENTSLISTMODEL_H
#define COMPONENTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
//#include <QJsonObject>


class ComponentInfo;

//==============================================================================
// Components List Model
//==============================================================================
class ComponentsListModel : public QAbstractListModel
{
public:
    // Constructor
    explicit ComponentsListModel(QObject* aParent = NULL);

    // Destructor
    ~ComponentsListModel();

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

    // Component List
    QList<ComponentInfo>    mComponentList;
};











/*
//==============================================================================
// Component Info Class
//==============================================================================
class ComponentInfo : public QObject
{
public:
    // Constructor
    explicit ComponentInfo(const QString& aName, QObject* aParent = NULL);

    // Get Component Name
    QString name();

    // Save Info
    void save();

    // Destructor
    ~ComponentInfo();

private:

    // Init
    void init();

private: // Data
    // Name
    QString     mName;
    // Component Info
    QJsonObject mInfo;
};
*/

#endif // COMPONENTSLISTMODEL_H
