#ifndef BASECOMPONENTSMODEL_H
#define BASECOMPONENTSMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include <QJsonObject>

class BaseComponentInfo;

//==============================================================================
// Base Components List Model
//==============================================================================
class BaseComponentsModel : public QAbstractListModel
{
public:
    // Constructor
    explicit BaseComponentsModel(QObject* aParent = NULL);
    // Destructor
    ~BaseComponentsModel();

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

    // Base Component List
    QList<BaseComponentInfo>    mBaseComponentList;

};









//==============================================================================
// Base Component Info Class
//==============================================================================
class BaseComponentInfo : public QObject
{
public:
    // Constructor
    explicit BaseComponentInfo(const QString& aName, QObject* aParent = NULL);

    // Get Component Name
    QString name();

    // Save Info
    void save();

    // Destructor
    ~BaseComponentInfo();

private:

    // Init
    void init();

private: // Data
    // Name
    QString     mName;
    // Component Info
    QJsonObject mInfo;
};

#endif // BASECOMPONENTSMODEL_H
