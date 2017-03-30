#ifndef COMPONENTOWNPROPERTIESMODEL_H
#define COMPONENTOWNPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentInfo;
class PropertiesController;

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
    explicit ComponentOwnPropertiesModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

public:
    // Item Field Roles
    enum OPMRoles {
        PropertyNameRole = Qt::UserRole + 1,
        PropertyTypeRole,
        PropertyValueRole
    };

protected: // Data
    // Current Component
    ComponentInfo*  mComponent;
};

#endif // COMPONENTOWNPROPERTIESMODEL_H
