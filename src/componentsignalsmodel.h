#ifndef COMPONENTSIGNALSMODEL_H
#define COMPONENTSIGNALSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

class ComponentInfo;
class ComponentSignal;

//==============================================================================
// Component Signals Model
//==============================================================================
class ComponentSignalsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Constructor
    explicit ComponentSignalsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Add Signal
    Q_INVOKABLE void addSignal(const QString& aName, const QStringList& aParameters = QStringList());
    // Remove Signal
    Q_INVOKABLE void removeSignal(const int& aIndex);
    // Rename Signal
    Q_INVOKABLE void renameSignal(const int& aIndex, const QString& aName);

    // Check If Signal Valid
    Q_INVOKABLE bool signalValid(const QString& aName);

    // Create New Signal To Add
    Q_INVOKABLE ComponentSignal* createNewSignal();
    // Get/Select Signal For Editing
    Q_INVOKABLE ComponentSignal* selectSignal(const int& aIndex);

    // Append Signal To Signal List
    Q_INVOKABLE void appendSignal(ComponentSignal* aSignal);
    // Discard New Signal
    Q_INVOKABLE void discardNewSignal(ComponentSignal* aSignal);
    // Update Selected Signal
    Q_INVOKABLE void updateSelectedSignal(const bool& aDoneEdit = true);

    // Exports Model To JSON Array
    QJsonArray toJSONArray();

    // Destructor
    ~ComponentSignalsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

protected:
    friend class ComponentSignal;
    // Init
    void init();
    // Clear
    void clear();

    // Set Dirty
    void setDirty(const bool& aDirty);

    // Load Component Signals
    void loadComponentSignals();
    // Save Component Signals
    void saveComponentSignals();
    // Clear Component Signals
    void clearComponentSignals();

public: // from QAbstractListModel
    // Row Count
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    // Data
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    // Get Role Names
    virtual QHash<int,QByteArray> roleNames() const;

public:
    // Signals Model Roles
    enum SMRoles {
        ESMRName      = Qt::UserRole + 1,
        ESMRParameters
    };

protected: // Data
    // Component
    ComponentInfo*          mComponent;
    // Signals
    QList<ComponentSignal*> mSignals;
    // New Signal
    bool                    mNewSignal;
    // Dirty
    bool                    mDirty;
    // Selected Index
    int                     mSelectedIndex;
};








//==============================================================================
// Component Signal Class
//==============================================================================
class ComponentSignal : public QObject
{
    Q_OBJECT

    // Name
    Q_PROPERTY(QString signalName READ signalName WRITE setSignalName NOTIFY signalNameChanged)
    // Parameters
    Q_PROPERTY(QStringList signalParameters READ signalParameters WRITE setSignalParameters NOTIFY signalParametersChanged)

public:
    // From JSON Object
    static ComponentSignal* fromJSONObject(ComponentSignalsModel* aModel, const QJsonObject& aObject);

    // Get Signal Name
    QString signalName();
    // Set Signal Name
    void setSignalName(const QString& aName);

    // Get Signal Parameters
    QStringList signalParameters();
    // Set Signal Parameters
    void setSignalParameters(const QStringList& aParameters);

    // Add Signal Parameter
    Q_INVOKABLE void addSignalParameter(const QString& aParameter);
    // Remove Signal Parameter
    Q_INVOKABLE void removeSignalParameter(const int& aIndex);
    // Update Signal Parameter
    Q_INVOKABLE void updateSignalParameter(const int& aIndex, const QString& aParameter);
    // Check If Parameter Valid
    Q_INVOKABLE bool parameterValid(const QString& aParameter, const bool& aNewParameter = true);

    // To JSON Object
    QJsonObject toJSONObject();

    // Destructor
    ~ComponentSignal();

signals:
    // Signal Name Changed Signal
    void signalNameChanged(const QString& aName);
    // Signal Parameters Changed Signal
    void signalParametersChanged(const QStringList& aParameters);

protected:
    friend class ComponentSignalsModel;

    // Constructor
    explicit ComponentSignal(ComponentSignalsModel* aModel, const QString& aName, const QStringList& aParameters = QStringList(), QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

protected: // Data
    // Signals Model
    ComponentSignalsModel*  mModel;
    // Signal Name
    QString                 mName;
    // Parameters
    QStringList             mParameters;
    // New Parameter
    bool                    mNewParameter;
};

#endif // COMPONENTSIGNALSMODEL_H
