#ifndef COMPONENTSTATESMODEL_H
#define COMPONENTSTATESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentInfo;
class ComponentState;
class ComponentPropertyChange;

//==============================================================================
// Component States Model
//==============================================================================
class ComponentStatesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Create New State
    Q_INVOKABLE ComponentState* createNewState();
    // Discard New State
    Q_INVOKABLE void discardNewState();
    // Append State
    Q_INVOKABLE void appendState(ComponentState* aState);
    // Remove State
    Q_INVOKABLE void removeState(const int& aindex);

    // Add State
    void addState(const QString& aStateName, const QString& aWhen = "");
    // Set State Name
    void setStateName(const int& aIndex, const QString& aStateName);
    // Clear State
    void clearState(const QString& aStateName);
    // Remove State
    void removeState(const QString& aStateName);

    // Add Property Change
    void addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QString& aValue);
    // Set Property Change
    void setPropertyChange(const QString& aStateName, const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue);
    // Remove Property Change
    void removePropertyChange(const QString& aStateName, const int& aIndex);

    // Get State By Name
    Q_INVOKABLE ComponentState* getState(const QString& aStateName);
    // Get State By Index
    Q_INVOKABLE ComponentState* getState(const int& aIndex);

    // Update Selected State
    Q_INVOKABLE void updateSelectedState();

    // Check If State Valid
    Q_INVOKABLE bool stateValid(const QString& aName, const bool& aNewState = true);

    // Destructor
    ~ComponentStatesModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

protected:
    friend class ComponentInfo;
    friend class PropertiesController;
    friend class ComponentState;

    // Constructor
    explicit ComponentStatesModel(ComponentInfo* aComponent, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

    // Load Component States
    void loadComponentStates();
    // Save Component States
    void saveComponentStates();

    // Reset States Dirty State
    void resetStatesDirtyState();

    // Set Dirty State
    void setDirty(const bool& aDirty);

    // To JSON Array
    QJsonArray toJSONArray();

protected slots:
    // Component State Dirty State Changed
    void componentStateDirtyChanged(const bool& aDirty);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

public:
    // States Model Roles
    enum SMRoles {
        ESMRName   =   Qt::UserRole + 1,
        ESMRWhen,
        ESMRChanges
    };

protected: // Data
    // Component Info
    ComponentInfo*          mComponent;
    // State List
    QList<ComponentState*>  mStates;
    // New State For Creation
    ComponentState*         mNewState;
    // Dirty State
    bool                    mDirty;
    // Selected Index
    int                     mSelectedIndex;
};









//==============================================================================
// Component State
//==============================================================================
class ComponentState : public QAbstractListModel
{
    Q_OBJECT

    // Name
    Q_PROPERTY(QString stateName READ stateName WRITE setStateName NOTIFY stateNameChanged)
    // When Trigger
    Q_PROPERTY(QString stateWhen READ stateWhen WRITE setStateWhen NOTIFY stateWhenChanged)
    // Has Children
    Q_PROPERTY(bool hasPropertyChanges READ hasPropertyChanges NOTIFY hasPropertyChangesChanged)

public:
    // From JSON Object
    static ComponentState* fromJSONObject(const QJsonObject& aObject, ComponentStatesModel* aModel);

    // Create New Property Change
    Q_INVOKABLE ComponentPropertyChange* createNewPropertyChange();
    // Discard New Property Change
    Q_INVOKABLE void discardNewPropertyChange();

    // Get Property Change by Index
    Q_INVOKABLE ComponentPropertyChange* getPropertyChange(const int& aIndex);
    // Update Selected Property Change
    Q_INVOKABLE void updateSelectedPropertyChange();

    // Get State Name
    QString stateName();
    // Set State Name
    void setStateName(const QString& aName);

    // Get When Trigger
    QString stateWhen();
    // Set When Trigger
    void setStateWhen(const QString& aWhen);

    // Has Property Changes
    bool hasPropertyChanges();

    // Append Property Change
    Q_INVOKABLE void appendPropertyChange(ComponentPropertyChange* aPropertyChange);
    // Insert Property Change
    Q_INVOKABLE void insertPropertyChange(const int& aIndex, ComponentPropertyChange* aPropertyChange);
    // Remove Property Change
    Q_INVOKABLE void removePropertyChange(const int& aIndex);

    // Set Property Change
    void setPropertyChange(const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue);

    // Clear State
    void clearState();

    // Destructor
    ~ComponentState();

signals:
    // State Name Changed Signal
    void stateNameChanged(const QString& aStateName);
    // When Trigger Changed Signal
    void stateWhenChanged(const QString& aWhen);
    // Has Property Changes Changed Signal
    void hasPropertyChangesChanged();
    // State Property Changes Changed Signal
    void stateChangesChanged();
    // Dirty State changed Signal
    void dirtyStateChanged(const bool& aDirty);

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected:
    friend class ComponentPropertyChange;

    // Constructor
    explicit ComponentState(const QString& aName, const QString& aWhen, ComponentStatesModel* aModel, QObject* aParent = NULL);

    // To JSON Object
    QJsonObject toJSONObject();

    // Set Has Children
    void setHasChildren(const bool& aHasChildren);

    // Set Dirty State
    void setDirty(const bool& aDirty);

public:
    // State Model Roles
    enum SMRoles {
        ESMRTarget      = Qt::UserRole + 1,
        ESMRProperty,
        ESMRValue
    };

protected: // Data
    friend class ComponentStatesModel;

    // State Model
    ComponentStatesModel*           mStatesModel;
    // State Name
    QString                         mName;
    // When Trigger
    QString                         mWhen;
    // Property Changes
    QList<ComponentPropertyChange*> mPropertyChanges;
    // New Property Change
    ComponentPropertyChange*        mNewPropertyChange;
    // Dirty State
    bool                            mDirty;
    // Selected Index
    int                             mSelectedIndex;
};







//==============================================================================
// Component State Property Change
//==============================================================================
class ComponentPropertyChange : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString propertyChangeTarget READ propertyChangeTarget WRITE setPropertyChangeTarget NOTIFY propertyChangeTargetChanged)
    Q_PROPERTY(QString propertyChangeProperty READ propertyChangeProperty WRITE setPropertyChangeProperty NOTIFY propertyChangePropertyChanged)
    Q_PROPERTY(QString propertyChangeValue READ propertyChangeValue WRITE setPropertyChangeValue NOTIFY propertyChangeValueChanged)

public:
    // From JSON Object
    static ComponentPropertyChange* fromJSONObject(const QJsonObject& aObject, ComponentState* aState);

    // Get Target
    QString propertyChangeTarget();
    // Set Target
    void setPropertyChangeTarget(const QString& aTarget);

    // Get Property
    QString propertyChangeProperty();
    // Set Property
    void setPropertyChangeProperty(const QString& aProperty);

    // Get Value
    QString propertyChangeValue();
    // Set Value
    void setPropertyChangeValue(const QString& aValue);

    // Destructor
    ~ComponentPropertyChange();

signals:
    // Property Change Target Changed Signal
    void propertyChangeTargetChanged(const QString& aTarget);
    // Property Change Property Changed Signal
    void propertyChangePropertyChanged(const QString& aTarget);
    // Property Change Value Changed Signal
    void propertyChangeValueChanged(const QString& aValue);

protected:
    // Constructor
    explicit ComponentPropertyChange(const QString& aTarget,
                                     const QString& aProperty,
                                     const QString& aValue,
                                     ComponentState* aState,
                                     QObject* aParent = NULL);

    // Set Dirty State
    void setDirty(const bool& aDirty);

    // To JSON Object
    QJsonObject toJSONObject();

protected: // Data
    friend class ComponentStatesModel;
    friend class ComponentState;

    // Component State
    ComponentState* mState;
    // Target
    QString         mTarget;
    // Property
    QString         mProperty;
    // Value
    QString         mValue;
    // Dirty State
    bool            mDirty;
};

#endif // COMPONENTSTATESMODEL_H
