#ifndef COMPONENTSLISTMODEL_H
#define COMPONENTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
//#include <QJsonObject>

class ProjectModel;
class ComponentInfo;

//==============================================================================
// Components List Model
//==============================================================================
class ComponentsModel : public QAbstractListModel
{
public:
    // Constructor
    explicit ComponentsModel(ProjectModel* aProjectModel, QObject* aParent = NULL);

    // Set Components Dir
    void setComponentsDir(const QString& aDirPath);

    // Add Component
    void addComponent(ComponentInfo* aComponent);
    // Remove Compoennt
    void removeComponent(ComponentInfo* aComponent, const bool& aDelete = true);

    // Destructor
    ~ComponentsModel();

private:
    // Init
    void init();
    // Clear
    void clear();

    // Load Components
    void loadComponents();

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
    // Component List
    QList<ComponentInfo*>   mComponentList;
    // Components Dir
    QString                 mComponentsDir;
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
