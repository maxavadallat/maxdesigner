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
    Q_OBJECT

public:
    // Set Base Components Dir
    void setBaseComponentsDir(const QString& aDirPath);

    // Add Base Component
    void addBaseComponent(ComponentInfo* aComponent);
    // Remove Base Compoennt
    void removeBaseComponent(ComponentInfo* aComponent, const bool& aDelete = true);

    // Set Base Component
    void setBaseComponent(const int& aIndex, ComponentInfo* aComponent);

    // Get Component Index By Name
    int getComponentIndex(const QString& aName);
    // Get Component By Name
    ComponentInfo* getComponent(const QString& aName);

    // Destructor
    ~BaseComponentsModel();

protected:
    friend class ProjectModel;

    // Constructor
    explicit BaseComponentsModel(ProjectModel* aProjectModel, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

protected slots:
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

#endif // BASECOMPONENTSMODEL_H
