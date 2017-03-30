#ifndef COMPONENTFUNCTIONSMODEL_H
#define COMPONENTFUNCTIONSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class ComponentFunction;
class ComponentInfo;
class PropertiesController;

//==============================================================================
// Component Functions Model
//==============================================================================
class ComponentFunctionsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ComponentInfo* currentComponent READ currentComponent WRITE setCurrentComponent NOTIFY currentComponentChanged)

public:
    // Get Current Component
    ComponentInfo* currentComponent();
    // Set Current Component
    void setCurrentComponent(ComponentInfo* aComponent);

    // Destructor
    ~ComponentFunctionsModel();

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
    explicit ComponentFunctionsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Load Component Functions
    void loadComponentFunctions();
    // Save Component Functions
    void saveComponentFunctions();

public:
    // Item Field Roles
    enum FMRoles {
        FMRNameRole = Qt::UserRole + 1,
        FMRParamsRole,
        FMRSoureRole
    };

protected: // Data
    // Current Component
    ComponentInfo*              mComponent;
    // Function List
    QList<ComponentFunction*>   mFunctions;
};








//==============================================================================
// Component Function Class
//==============================================================================
class ComponentFunction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString functionName READ functionName WRITE setFunctionName NOTIFY functionNameChanged)
    Q_PROPERTY(QStringList functionParameters READ functionParameters WRITE setFunctionParameters NOTIFY functionParametersChanged)
    Q_PROPERTY(QString functionSource READ functionSource WRITE setFunctionSource NOTIFY functionSourceChanged)

public:
    // Constructor
    explicit ComponentFunction(QObject* aParent = NULL);

    // Get Function Name
    QString functionName();
    // Set Function Name
    void setFunctionName(const QString& aFunctionName);

    // Get Function Parameters
    QStringList functionParameters();
    // Set Function Parameters
    void setFunctionParameters(const QStringList& aParameters);

    // Get Function Source
    QString functionSource();
    // Set Function Source
    void setFunctionSource(const QString& aSource);

    // Insert Parameter
    void insertParameter(const int& aIndex, const QString& aParameter);
    // Append Parameter
    void appendParameter(const QString& aParameter);
    // Remove Parameter
    void removeParameter(const int& aIndex);

    // Export To JSON Object
    QJsonObject toJSONObject();

    // Destructor
    ~ComponentFunction();

signals:
    // Function Name Changed Signal
    void functionNameChanged(const QString& aFunctionName);
    // Function Parameters Changed Signal
    void functionParametersChanged(const QStringList& aPerameters);
    // Function Source Changed Signal
    void functionSourceChanged(const QString& aSource);

protected:
    // Name
    QString     mName;
    // Parameters
    QStringList mParameters;
    // Source
    QString     mSource;
};





#endif // COMPONENTFUNCTIONSMODEL_H
