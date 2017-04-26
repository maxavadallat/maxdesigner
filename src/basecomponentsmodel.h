#ifndef BASECOMPONENTSMODEL_H
#define BASECOMPONENTSMODEL_H

#include <QObject>
#include <QList>
#include <QMap>
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
    bool addBaseComponent(ComponentInfo* aComponent);
    // Remove Base Component
    bool removeBaseComponent(const int& aIndex);

    // Get Component Index By Name
    int getComponentIndex(const QString& aName);
    // Get Component By Name
    ComponentInfo* getComponent(const QString& aName, const bool& aPreload = false);
    // Get Compoennt By Index
    Q_INVOKABLE ComponentInfo* getComponentByIndex(const int& aIndex);

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

    // Update Base Components
    void updateBaseComponents();

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
    enum EBCItemRoles {
        EBCRName = Qt::UserRole + 1,
        EBCRBuiltIn
    };

    // Project Model
    ProjectModel*                   mProjectModel;
    // Base Components
    QMap<QString, ComponentInfo*>   mBaseComponents;
    // Base Components Dir
    QString                         mBaseComponentsDir;
};

#endif // BASECOMPONENTSMODEL_H
