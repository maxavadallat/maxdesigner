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

    // Append Signal
    void appendSignal(ComponentSignal* aSignal);
    // Remove Signal
    void removeSignal(const int& aIndex);

    // To JSON Array
    QJsonArray toJSONArray();
    // Destructor
    ~ComponentSignalsModel();

signals:
    // Current Component Changed Signal
    void currentComponentChanged(ComponentInfo* aComponent);

protected:
    // Init
    void init();
    // Clear
    void clear();

    // Load Component Signals
    void loadComponentSignals(const QJsonArray& aArray);
    // Save Component Signals
    void saveComponentSignals();

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
    static ComponentSignal* fromJSONObject(const QJsonObject& aOvject);
    // Constructor
    explicit ComponentSignal(const QString& aName, const QStringList& aParameters, QObject* aParent = NULL);

    // Get Signal Name
    QString signalName();
    // Set Signal Name
    void setSignalName(const QString& aName);

    // Get Signal Parameters
    QStringList signalParameters();
    // Set Signal Parameters
    void setSignalParameters(const QStringList& aParameters);

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
    // Init
    void init();
    // Clear
    void clear();

protected: // Data
    // Signal Name
    QString         mName;
    // Parameters
    QStringList     mParameters;
};

#endif // COMPONENTSIGNALSMODEL_H
