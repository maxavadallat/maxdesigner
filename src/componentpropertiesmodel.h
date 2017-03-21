#ifndef COMPONENTPROPERTIESMODEL_H
#define COMPONENTPROPERTIESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentInfo;

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

protected: // Data
    // Current Component
    ComponentInfo*  mComponent;
};

#endif // COMPONENTPROPERTIESMODEL_H
