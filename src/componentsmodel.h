#ifndef COMPONENTSLISTMODEL_H
#define COMPONENTSLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMap>

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
    bool addComponent(ComponentInfo* aComponent);
    // Remove Component
    bool removeComponent(const int& aIndex);

    // Get Component Index By Name
    int getComponentIndex(const QString& aName);
    // Get Component By Name
    ComponentInfo* getComponent(const QString& aName, const bool& aPreload = false);
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
    enum ECItemRoles {
        ECRName = Qt::UserRole + 1
    };

    // Project Model
    ProjectModel*                   mProjectModel;
    // Components
    QMap<QString, ComponentInfo*>   mComponents;
    // Components Dir
    QString                         mComponentsDir;
};

#endif // COMPONENTSLISTMODEL_H
