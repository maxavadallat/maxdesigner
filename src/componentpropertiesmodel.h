#ifndef COMPONENTPROPERTIESMODEL_H
#define COMPONENTPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ProjectModel;
class ComponentInfo;
class ComponentOwnPropertiesModel;
class PropertiesController;

//==============================================================================
// Component Properties Model
//==============================================================================
class ComponentPropertiesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Component Property Name By Index
    Q_INVOKABLE QString componentPropertyName(const QString& aBaseName, const int& aIndex);

    // Set Component Own Property Value
    Q_INVOKABLE bool setComponentProperty(const QString& aName, const QVariant& aValue);
    // Clear Component Property
    Q_INVOKABLE bool clearComponentProperty(const QString& aName);

    // Get Component Property List
    Q_INVOKABLE QAbstractListModel* componentPropertyList(const int& aIndex);

    // Destructor
    ~ComponentPropertiesModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected:
    friend class PropertiesController;
    // Constructor
    explicit ComponentPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Load Component Properties
    void loadComponentProperties();

    // Add Component To Hierarchy
    void addComponentToHierarchy(const QString& aBaseName);

public:
    // Properties Model Roles
    enum PMRoles {
        ESMRBaseName   =   Qt::UserRole + 1
    };

protected: // Data
    // Current Component
    ComponentInfo*          mComponent;
    // Project Model
    ProjectModel*           mProject;
    // Component Bases/Hierarchy
    QList<ComponentInfo*>   mHierarchy;
};

#endif // COMPONENTPROPERTIESMODEL_H
