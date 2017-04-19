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

    // Add Slot
    Q_INVOKABLE void addSlot(const QString& aName, const QString& aSource = "");
    // Remove Slot
    Q_INVOKABLE void removeSlot(const int& aIndex);
    // Rename Slot
    Q_INVOKABLE void renameSlot(const int& aIndex, const QString& aName);

    // Is Slot Valie
    Q_INVOKABLE bool slotValid(const QString& aName);

    // Create New Slot To Add
    Q_INVOKABLE ComponentSlot* createNewSlot();
    // Get/Select Slot For Editing
    Q_INVOKABLE ComponentSlot* selectSlot(const int& aIndex);

    // Append Slot
    Q_INVOKABLE void appendSlot(ComponentSlot* aSlot);
    // Discard New Slot
    Q_INVOKABLE void discardNewSlot(ComponentSlot* aSlot);
    // Update Selected Slot
    Q_INVOKABLE void updateSelectedSlot(const bool& aDoneEdit = true);

//    // Update Source
//    void updateSlotSource(const QString& aName, const QString& aSource);
//    // Update Source
//    void updateSlotSource(const int& aIndex, const QString& aSource);

    // To JSON Array
    QJsonArray toJSONArray();

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
    friend class ComponentSlot;

    // Constructor
    explicit ComponentSlotsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Set Dirty
    void setDirty(const bool& aDirty);

    // Load Component Slots
    void loadComponentSlots();
    // Save Component Slots
    void saveComponentSlots();
    // Clear Component Slots
    void clearComponentSlots();

public:
    // Item Field Roles
    enum SMRoles {
        SMRNameRole = Qt::UserRole + 1,
        SMRSoureRole
    };

protected: // Data
    // Current Component
    ComponentInfo*          mComponent;
    // Slots
    QList<ComponentSlot*>   mSlots;
    // New Slot
    bool                    mNewSlot;
    // Dirty
    bool                    mDirty;
    // Selected Index
    int                     mSelectedIndex;
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
    // From JSON Object
    static ComponentSlot* fromJSONObject(ComponentSlotsModel* aModel, const QJsonObject& aObject);

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
    friend class ComponentSlotsModel;
    // Constructor
    explicit ComponentSlot(ComponentSlotsModel* aModel, const QString& aName, const QString& aSource, QObject* aParent = NULL);

protected:
    // Slots Model
    ComponentSlotsModel*    mModel;
    // Name
    QString                 mName;
    // Source
    QString                 mSource;
};


#endif // COMPONENTSLOTSMODEL_H
