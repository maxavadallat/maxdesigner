#ifndef COMPONENTSLOTSMODEL_H
#define COMPONENTSLOTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class ComponentSlot;
class ComponentInfo;
class PropertiesController;

//==============================================================================
// Component Slots Model Class
//==============================================================================
class ComponentSlotsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Destructor
    ~ComponentSlotsModel();

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
    explicit ComponentSlotsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Load Component Slots
    void loadComponentSlots();
    // Save Component Slots
    void saveComponentSlots();

public:
    // Item Field Roles
    enum SMRoles {
        SMRNameRole = Qt::UserRole + 1,
        SMRSoureRole
    };

protected: // Data
    // Current Component
    ComponentInfo*              mComponent;
    // Slots
    QList<ComponentSlot*>       mSlots;
};









//==============================================================================
// Component Slot Class
//==============================================================================
class ComponentSlot : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString slotName READ slotName WRITE setSlotName NOTIFY slotNameChanged)
    Q_PROPERTY(QString slotSource READ slotSource WRITE setSlotSource NOTIFY slotSourceChanged)

public:
    // Constructor
    explicit ComponentSlot(QObject* aParent = NULL);

    // Get Slot Name
    QString slotName();
    // Set Slot Name
    void setSlotName(const QString& aSlotName);

    // Get Slot Source
    QString slotSource();
    // Set Slot Source
    void setSlotSource(const QString& aSource);

    // Export To JSON Object
    QJsonObject toJSONObject();

    // Destructor
    ~ComponentSlot();

signals:
    // Slot Name Changed Signal
    void slotNameChanged(const QString& aSlotName);
    // Slot Source Changed Signal
    void slotSourceChanged(const QString& aSource);

protected:
    // Name
    QString     mName;
    // Source
    QString     mSource;
};







#endif // COMPONENTSLOTSMODEL_H
