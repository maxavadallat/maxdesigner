#ifndef COMPONENTPROPERTIESMODEL_H
#define COMPONENTPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentInfo;
class ComponentOwnPropertiesModel;

//==============================================================================
// Component Properties Model
//==============================================================================
class ComponentPropertiesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Constructor
    explicit ComponentPropertiesModel(QObject* aParent = NULL);

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Get Base Properties

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
    // Init
    void init();
    // Clear
    void clear();

    // Load Component Properties
    void loadComponentProperties();
//    // Save Component Properties
//    void saveComponentProperties();

public:
    // Properties Model Roles
    enum PMRoles {
        ESMRBaseName   =   Qt::UserRole + 1
    };

protected: // Data
    // Current Component
    ComponentInfo*          mComponent;
    // Component Bases/Hierarchy
    QList<ComponentInfo*>   mHierarchy;
};

#endif // COMPONENTPROPERTIESMODEL_H
