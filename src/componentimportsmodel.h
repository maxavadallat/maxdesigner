#ifndef COMPONENTIMPORTSMODEL_H
#define COMPONENTIMPORTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

class ComponentInfo;
class PropertiesController;

//==============================================================================
// Component Imports Model Class
//==============================================================================
class ComponentImportsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Add Import
    Q_INVOKABLE void addImport(const QString& aImport);
    // Remove Import
    Q_INVOKABLE void removeImport(const QString& aImport);
    // Remove Import
    Q_INVOKABLE void removeImport(const int& aIndex);
    // Check If Import Valid
    Q_INVOKABLE bool importValid(const QString& aImport);

    // Destructor
    ~ComponentImportsModel();

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
    explicit ComponentImportsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Load Component Imports
    void loadComponentImports();
    // Save Component Imports
    void saveComponentImports();

public:
    // Item Field Roles
    enum IMRoles {
        IMRNameRole = Qt::UserRole + 1
    };

protected: // Data
    // Current Component
    ComponentInfo*      mComponent;
};

#endif // COMPONENTIMPORTSMODEL_H
