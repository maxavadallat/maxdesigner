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

    // Add Function
    Q_INVOKABLE void addFunction(const QString& aName, const QStringList& aParameters = QStringList(), const QString& aSource = "");

    // Remove Function
    Q_INVOKABLE void removeFunction(const int& aIndex);
    // Rename Function
    Q_INVOKABLE void renameFunction(const int& aIndex, const QString& aName);

    // Check If Function Valid
    Q_INVOKABLE bool functionValid(const QString& aName);

    // Create New Function
    Q_INVOKABLE ComponentFunction* createNewFunction();
    // Select Function
    Q_INVOKABLE ComponentFunction* selectFunction(const int& aIndex);

    // Append Function
    Q_INVOKABLE void appendFunction(ComponentFunction* aFunction);
    // Discard New Function
    Q_INVOKABLE void discardNewFunction(ComponentFunction* aFunction);
    // Update Selected Function
    Q_INVOKABLE void updateSelectedFunction(const bool& aDoneEdit = true);

    // To JSON Array
    QJsonArray toJSONArray();

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
    friend class ComponentFunction;

    // Constructor
    explicit ComponentFunctionsModel(ComponentInfo* aComponent, QObject* aParent = NULL);

    // Init
    void init();
    // Clear
    void clear();

    // Set Dirty
    void setDirty(const bool& aDirty);

    // Load Component Functions
    void loadComponentFunctions();
    // Save Component Functions
    void saveComponentFunctions();
    // Clear Component Functions
    void clearComponentFunctions();

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
    // New Function
    bool                        mNewFunction;
    // Dirty
    bool                        mDirty;
    // Selected Function Index
    int                         mSelectedIndex;
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
    // From JSON Object
    static ComponentFunction* fromJSONObject(ComponentFunctionsModel* aModel, const QJsonObject& aObject);

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
    Q_INVOKABLE void insertFunctionParameter(const int& aIndex, const QString& aParameter);
    // Append Parameter
    Q_INVOKABLE void appendFunctionParameter(const QString& aParameter);
    // Remove Parameter
    Q_INVOKABLE void removeFunctionParameter(const int& aIndex);
    // Check If Parameter Valid
    Q_INVOKABLE bool parameterValid(const QString& aParameter, const bool& aNewParameter = true);

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
    friend class ComponentFunctionsModel;
    // Constructor
    explicit ComponentFunction(ComponentFunctionsModel* aModel,
                               const QString& aName,
                               const QString& aSource,
                               const QStringList& aParameters = QStringList(),
                               QObject* aParent = NULL);

protected:
    // Compoennt Functions Model
    ComponentFunctionsModel*    mModel;
    // Name
    QString                     mName;
    // Parameters
    QStringList                 mParameters;
    // Source
    QString                     mSource;
};


#endif // COMPONENTFUNCTIONSMODEL_H
