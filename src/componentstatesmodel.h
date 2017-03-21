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

public:
    // From JSON Array
    //static ComponentStatesModel* fromJSONArray(ComponentInfo* aComponent, const QJsonArray& aArray);

    // Add State
    void addState(const QString& aStateName);
    // Set State Name
    void setStateName(const int& aIndex, const QString& aStateName);
    // Clear State
    void clearState(const QString& aStateName);
    // Remove State
    void removeState(const QString& aStateName);
    // Remove State
    void removeState(const int& aindex);

    // Add Property Change
    void addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QString& aValue);
    // Set Property Change
    void setPropertyChange(const QString& aStateName, const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue);
    // Remove Property Change
    void removePropertyChange(const QString& aStateName, const int& aIndex);

    // To JSON Array
    QJsonArray toJSONArray();

    // Get State By Name
    Q_INVOKABLE ComponentState* getState(const QString& aStateName);
    // Get State By Index
    Q_INVOKABLE ComponentState* getState(const int& aIndex);

    // Destructor
    ~ComponentStatesModel();

protected:
    friend class ComponentInfo;

    // Constructor
    explicit ComponentStatesModel(ComponentInfo* aComponent, QObject* aParent = NULL);
    // Init
    void init();
    // Clear
    void clear();

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
    static ComponentState* fromJSONObject(const QJsonObject& aObject);

    // Constructor
    explicit ComponentState(const QString& aName, QObject* aParent = NULL);

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
    void appendPropertyChange(ComponentPropertyChange* aPropertyChange);
    // Insert Property Change
    void insertPropertyChange(const int& aIndex, ComponentPropertyChange* aPropertyChange);
    // Remove Property Change
    void removePropertyChange(const int& aIndex);

    // Set Property Change
    void setPropertyChange(const int& aIndex, const QString& aTarget, const QString& aProperty, const QString& aValue);

    // Clear State
    void clearState();

    // To JSON Object
    QJsonObject toJSONObject();

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

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int, QByteArray> roleNames() const;

protected:
    // Set Has Children
    void setHasChildren(const bool& aHasChildren);

public:
    // State Model Roles
    enum SMRoles {
        ESMRTarget      = Qt::UserRole + 1,
        ESMRProperty,
        ESMRValue
    };

protected: // Data
    // State Name
    QString                         mName;
    // When Trigger
    QString                         mWhen;
    // Property Changes
    QList<ComponentPropertyChange*> mPropertyChanges;
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
    static ComponentPropertyChange* fromJSONObject(const QJsonObject& aObject);

    // Constructor
    explicit ComponentPropertyChange(const QString& aTarget,
                                     const QString& aProperty,
                                     const QString& aValue,
                                     QObject* aParent = NULL);

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

protected: // Data
    // Target
    QString         mTarget;
    // Property
    QString         mProperty;
    // Value
    QString         mValue;
};

#endif // COMPONENTSTATESMODEL_H
