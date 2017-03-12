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
    Q_OBJECT

public:
    // Set Components Dir
    void setComponentsDir(const QString& aDirPath);

    // Add Component
    void addComponent(ComponentInfo* aComponent);
    // Remove Compoennt
    void removeComponent(ComponentInfo* aComponent, const bool& aDelete = true);

    // Get Component Index By Name
    int getComponentIndex(const QString& aName);
    // Get Component By Name
    ComponentInfo* getComponent(const QString& aName);
    // Get Compoennt By Index
    Q_INVOKABLE ComponentInfo* getComponentByIndex(const int& aIndex);

    // Destructor
    ~ComponentsModel();

protected:
    friend class ProjectModel;

    // Constructor
    explicit ComponentsModel(ProjectModel* aProjectModel, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

    // Load Components
    void loadComponents();
    // Update Base Components
    void updateBaseComponents();

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

#endif // COMPONENTSLISTMODEL_H
