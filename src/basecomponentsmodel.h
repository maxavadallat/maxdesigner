#ifndef BASECOMPONENTSMODEL_H
#define BASECOMPONENTSMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Base Components List Model
//==============================================================================
class BaseComponentsModel : public QAbstractListModel
{
public:
    // Constructor
    explicit BaseComponentsModel(ProjectModel* aProjectModel, QObject* aParent = NULL);

    // Set Base Components Dir
    void setBaseComponentsDir(const QString& aDirPath);

    // Add Base Component
    void addBaseComponent(ComponentInfo* aComponent);
    // Remove Base Compoennt
    void removeBaseComponent(ComponentInfo* aComponent, const bool& aDelete = true);

    // Get Component Index By Name
    int getComponentIndex(const QString& aName);
    // Get Component By Name
    ComponentInfo* getComponent(const QString& aName);

    // Destructor
    ~BaseComponentsModel();

private:
    // Init
    void init();
    // Clear
    void clear();

    // Load Base Components
    void loadBaseComponents();

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
        ComponentNameRole = Qt::UserRole + 1
    };

    // Project Model
    ProjectModel*           mProjectModel;
    // Base Component List
    QList<ComponentInfo*>   mBaseComponentList;
    // Base Components Dir
    QString                 mBaseComponentsDir;
};








/*
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
*/

#endif // BASECOMPONENTSMODEL_H
