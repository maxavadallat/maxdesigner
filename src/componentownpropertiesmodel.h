#ifndef COMPONENTOWNPROPERTIESMODEL_H
#define COMPONENTOWNPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ProjectModel;
class ComponentInfo;
class PropertiesController;
class ComponentPropertiesModel;

//==============================================================================
// Component Own Properties Model
//==============================================================================
class ComponentOwnPropertiesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Component Property Name By Index
    Q_INVOKABLE QString componentPropertyName(const int& aIndex);

    // Add Own Property
    Q_INVOKABLE bool addComponentProperty(const QString& aName,
                                          const int& aType = 0,
                                          const QString& aMin = "",
                                          const QString& aMax = "",
                                          const QString& aEnumValues = "",
                                          const QVariant& aDefaultValue = QVariant());

    // Set Component Property Value
    Q_INVOKABLE void setComponentProperty(const int& aIndex, const QVariant& aValue);
    // Get Component Property Value
    Q_INVOKABLE QVariant componentPropertyValue(const QString& aName);

    // Update Own Property
    Q_INVOKABLE void updateComponentProperty(const int& aIndex,
                                             const QString& aName,
                                             const int& aType = 0,
                                             const QString& aMin = "",
                                             const QString& aMax = "",
                                             const QString& aEnumValues = "",
                                             const QVariant& aDefault = QVariant());

    // Clear Component Property, Reset To Default/Base Component Value
    Q_INVOKABLE void clearComponentProperty(const int& aIndex);
    // Remove Property
    Q_INVOKABLE void removeComponentProperty(const int& aIndex);

    // Check If Property Name Valid For Addition Or Update
    Q_INVOKABLE bool propertyValid(const QString& aName, const bool& aNewProperty = true);

    // Check IF Has Property
    Q_INVOKABLE bool hasProperty(const QString& aName);

    // Remove Own Property
    Q_INVOKABLE bool removeComponentProperty(const QString& aName);
    // Set Component Own Property Value
    Q_INVOKABLE bool setComponentProperty(const QString& aName, const QVariant& aValue);
    // Clear Component Property
    Q_INVOKABLE bool clearComponentProperty(const QString& aName);

    // Destructor
    ~ComponentOwnPropertiesModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

    // Own Property Added Signal
    void ownPropertyAdded(const QString& aName);
    // Own Property Updated Signal
    void ownPropertyUpdated(const QString& aName, const int& aType, const QVariant& aDefault);
    // Own Prperty Removed Signal
    void ownPropertyRemoved(const QString& aName);
    // Own Prperty Cleared Signal
    void ownPropertyCleared(const QString& aName);
    // Own Property Value Changed
    void ownPropertyValueChanged(const QString& aName, const QVariant& aValue);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected:
    friend class PropertiesController;
    friend class ComponentPropertiesModel;

    // Constructor
    explicit ComponentOwnPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, ComponentInfo* aDerivedComponent = NULL, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Load Component Properties
    void loadComponentProperties();
    // Generate Own Property Keys
    void generateOwnPropertyKeys();

    // Refresh Property For Inherited Property Set
    void refreshProperty(const QString& aName);

public:
    // Item Field Roles
    enum OPMRoles {
        PropertyNameRole = Qt::UserRole + 1,
        PropertyTypeRole,
        PropertyEnumsRole,
        PropertyMinRole,
        PropertyMaxRole,
        PropertyValueRole,
        PropertyReadOnlyRole,
        PropertyDefaultRole,
        PropertyIsBind,
        PropertyIsFormula,
        PropertyIsProto,
        PropertyUseProto,
        PropertyIsBase
    };

protected: // Data
    // Current Component
    ComponentInfo*  mComponent;
    // Project Model
    ProjectModel*   mProject;
    // Property Keys
    QStringList     mKeys;
    // Derived Component
    ComponentInfo*  mDerivedComponent;
};

#endif // COMPONENTOWNPROPERTIESMODEL_H
