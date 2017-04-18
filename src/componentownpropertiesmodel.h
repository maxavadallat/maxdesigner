#ifndef COMPONENTOWNPROPERTIESMODEL_H
#define COMPONENTOWNPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentInfo;
class PropertiesController;
class ProjectModel;

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

    // Add Own Property
    void addComponentProperty(const QString& aName, const int& aType = 0, const QVariant& aDefault = QVariant());
    // Remove Own Property
    void removeComponentProperty(const QString& aName);
    // Set Component Own Property Value
    bool setComponentProperty(const QString& aName, const QVariant& aValue);
    // Clear Component Property
    bool clearComponentProperty(const QString& aName);

    // Destructor
    ~ComponentOwnPropertiesModel();

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
    explicit ComponentOwnPropertiesModel(ComponentInfo* aComponent, ProjectModel* aProject, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear(const bool& aEndReset = true);

    // Load Component Properties
    void loadComponentProperties();

    // Generate Merged Keys
    void generateMergedKeys();

protected slots:
//    // Own Property Added Slot
//    void propertyAdded(const int& aIndex);
//    // Own Property Updated
//    void propertyUpdated(const int& aIndex);
//    // Own Property Removed Slot
//    void propertyRemoved(const int& aIndex);
//    // Properties Updated Slot
//    void propertiesUpdated();

public:
    // Item Field Roles
    enum OPMRoles {
        PropertyNameRole = Qt::UserRole + 1,
        PropertyTypeRole,
        PropertyValueRole,
        PropertyIsFormula,
        PropertyIsProto
    };

protected: // Data
    // Current Component
    ComponentInfo*  mComponent;
    // Project Model
    ProjectModel*   mProject;
    // Property Keys
    QStringList     mKeys;
};

#endif // COMPONENTOWNPROPERTIESMODEL_H
