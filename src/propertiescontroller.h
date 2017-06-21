#ifndef PROPERTIESCONTROLLER_H
#define PROPERTIESCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <QThread>

class ProjectModel;
class ComponentInfo;
class ComponentImportsModel;
class ComponentOwnPropertiesModel;
class ComponentPropertiesModel;
class ComponentAnchorsModel;
class ComponentSignalsModel;
class ComponentSlotsModel;
class ComponentStatesModel;
class ComponentTransitionsModel;
class ComponentTransition;
class ComponentTransitionNode;
class ComponentFunctionsModel;
class AnimationComponentsModel;

//==============================================================================
// Properties Controller Class
//==============================================================================
class PropertiesController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* currentProject READ currentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(ComponentInfo* focusedComponent READ focusedComponent WRITE setFocusedComponent NOTIFY focusedComponentChanged)
    Q_PROPERTY(QObject* focusedContainer READ focusedContainer WRITE setFocusedContainer NOTIFY focusedContainerChanged)

    Q_PROPERTY(QString cID READ cID NOTIFY cIDChanged)
    Q_PROPERTY(QString cObjectName READ cObjectName NOTIFY cObjectNameChanged)

    Q_PROPERTY(QString cX READ cX NOTIFY cXChanged)
    Q_PROPERTY(QString cY READ cY NOTIFY cYChanged)
    Q_PROPERTY(QString cZ READ cZ NOTIFY cZChanged)

    Q_PROPERTY(QString cWidth READ cWidth NOTIFY cWidthChanged)
    Q_PROPERTY(QString cHeight READ cHeight NOTIFY cHeightChanged)

    Q_PROPERTY(QStringList filteredProperties READ filteredProperties WRITE setFilteredProperties NOTIFY filteredPropertiesChanged)
    Q_PROPERTY(QStringList filteredPropertyChanges READ filteredPropertyChanges WRITE setFilteredPropertyChanges NOTIFY filteredPropertyChangesChanged)

    Q_PROPERTY(ComponentImportsModel* importsModel READ importsModel WRITE setImportsModel NOTIFY importsModelChanged)
    Q_PROPERTY(ComponentOwnPropertiesModel* ownPropertiesModel READ ownPropertiesModel NOTIFY ownPropertiesModelChanged)
    Q_PROPERTY(ComponentAnchorsModel* anchorsModel READ anchorsModel NOTIFY anchorsModelChanged)
    Q_PROPERTY(ComponentSignalsModel* signalsModel READ signalsModel NOTIFY signalsModelChanged)
    Q_PROPERTY(ComponentSlotsModel* slotsModel READ slotsModel WRITE setSlotsModel NOTIFY slotsModelChanged)
    Q_PROPERTY(ComponentStatesModel* statesModel READ statesModel NOTIFY statesModelChanged)
    Q_PROPERTY(ComponentTransitionsModel* transitionsModel READ transitionsModel NOTIFY transitionsModelChanged)
    Q_PROPERTY(ComponentPropertiesModel* propertiesModel READ propertiesModel NOTIFY propertiesModelChanged)
    Q_PROPERTY(ComponentFunctionsModel* functionsModel READ functionsModel WRITE setFunctionsModel NOTIFY functionsModelChanged)
    Q_PROPERTY(AnimationComponentsModel* animComponentsModel READ animComponentsModel NOTIFY animComponentsModelChanged)

    // ...

public:
    // Constructor
    explicit PropertiesController(ProjectModel* aProjectModel = NULL, QObject* aParent = NULL);

    // Get Current Project
    ProjectModel* currentProject();
    // Set Current Project
    void setCurrentProject(ProjectModel* aProjectModel);

    // Get Focused Component
    ComponentInfo* focusedComponent();
    // Set Focused Component
    void setFocusedComponent(ComponentInfo* aComponent);

    // Get Focused Container
    QObject* focusedContainer();
    // Set Focused Container
    void setFocusedContainer(QObject* aContainer);

    // Get Component ID
    QString cID();
    // Request Component ID
    Q_INVOKABLE void requestCID(const QString& aID);

    // Get Component Object Name
    QString cObjectName();
    // Request Component Object Name
    Q_INVOKABLE void requestCObjectName(const QString& aObjectName);

    // Get Component X
    QString cX();
    // Request Component X
    Q_INVOKABLE void requestCX(const QString& aX);

    // Get Component Y
    QString cY();
    // Request Component Y
    Q_INVOKABLE void requestCY(const QString& aY);

    // Get Component Z
    QString cZ();
    // Request Component Z
    Q_INVOKABLE void requestCZ(const QString& aZ);

    // Get Component Width
    QString cWidth();
    // Request Component Width
    Q_INVOKABLE void requestCWidth(const QString& aWidth);

    // Get Component Height
    QString cHeight();
    // Request Component Height
    Q_INVOKABLE void requestCHeight(const QString& aHeight);

    // Get Filtered Properties
    QStringList filteredProperties();
    // Get Filtered Property Changes
    QStringList filteredPropertyChanges();

    // Get Imports Model
    ComponentImportsModel* importsModel();
    // Get Anchors Model
    ComponentAnchorsModel* anchorsModel();
    // Get Own Properties Model
    ComponentOwnPropertiesModel* ownPropertiesModel();
    // Get Signals Model
    ComponentSignalsModel* signalsModel();
    // Get Slots Model
    ComponentSlotsModel* slotsModel();
    // Get States Model
    ComponentStatesModel* statesModel();
    // Get Transitins Model
    ComponentTransitionsModel* transitionsModel();
    // Get Properties Model
    ComponentPropertiesModel* propertiesModel();
    // Get Functions Model
    ComponentFunctionsModel* functionsModel();
    // Get Animation Components Model
    AnimationComponentsModel* animComponentsModel();

    // Set Component Tag
    Q_INVOKABLE void setComponentTag(const QString& aTag);

    // Select Component By Name
    Q_INVOKABLE ComponentInfo* selectComponent(const QString& aName, const int& aChildIndex = -1);

    // Add Import
    Q_INVOKABLE void addComponentImport(const QString& aImport);
    // Remove Import
    Q_INVOKABLE void removeComponentImport(const int& aIndex);

    // Get Component Property
    Q_INVOKABLE QVariant componentProperty(const QString& aName);
    // Set Property
    Q_INVOKABLE void setComponentProperty(const QString& aName, const QVariant& aValue);
    // Clear Component Property
    Q_INVOKABLE void clearComponentProperty(const QString& aName);

    // Add Own Property
    Q_INVOKABLE void addOwnComponentProperty(const QString& aName,
                                             const int& aType,
                                             const QString& aMin = "",
                                             const QString& aMax = "",
                                             const QString& aEnumValues = "",
                                             const QVariant& aDefaultValue = QVariant(),
                                             const bool& aReadOnly = false,
                                             const bool& aDefaultAlias = false);
    // Remove Own Property
    Q_INVOKABLE void removeComponentProperty(const QString& aName);

    // ...

    // Add Signal
    Q_INVOKABLE void addSignal(const QString& aName, const QStringList& aParameters = QStringList());
    // Remove Signal
    Q_INVOKABLE void removeSignal(const int& aindex);

    // Add Slot
    Q_INVOKABLE void addSlot(const QString& aName, const QString& aSource = "");
    // Remove Slot
    Q_INVOKABLE void removeSlot(const int& aIndex);

    // Add Function
    Q_INVOKABLE void addFunction(const QString& aName, const QStringList& aParameters = QStringList(), const QString& aSource = "");
    // Remove Function
    Q_INVOKABLE void removeFunction(const int& aIndex);

    // Add State
    Q_INVOKABLE void addState(const QString& aName, const QString& aWhen = "");
    // Remove State
    Q_INVOKABLE void removeState(const int& aIndex);
    // Add Property Change
    Q_INVOKABLE void addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QString& aValue);

    // Add Transition
    Q_INVOKABLE void addTransition(const QString& aFrom, const QString& aTo);
    // Remove Transition
    Q_INVOKABLE void removeTransition(const int& aIndex);

    // ...

    // Destructor
    ~PropertiesController();

signals:
    // Current Project Changed Signal
    void currentProjectChanged(ProjectModel* aProjectModel);
    // Focused Component Changed Signal
    void focusedComponentChanged(ComponentInfo* aComponent);
    // Focused Container Changed Signal
    void focusedContainerChanged(QObject* aContainer);

    // Component ID Changed Signal
    void cIDChanged(const QString& aID);
    // Component Object Name Changed Signal
    void cObjectNameChanged(const QString& aObjectName);
    // Component X Changed Signal
    void cXChanged(const QString& aX);
    // Component Y Changed Signal
    void cYChanged(const QString& aY);
    // Component Z Changed Signal
    void cZChanged(const QString& aZ);
    // Component Width Changed Signal
    void cWidthChanged(const QString& aWidth);
    // Component Height Changed Signal
    void cHeightChanged(const QString& aHeight);
    // Filtered Properties Changed Signal
    void filteredPropertiesChanged(const QStringList& aProperties);
    // Filtered Property Changes Changed Signal
    void filteredPropertyChangesChanged(const QStringList& aFilteredChanges);

    // Imports Model Changed Signal
    void importsModelChanged(ComponentImportsModel* aImportsModel);
    // Anchors Model Changed Signal
    void anchorsModelChanged(ComponentAnchorsModel* aAnchorsModel);
    // Own Properties Model Changed Signal
    void ownPropertiesModelChanged(ComponentOwnPropertiesModel* aOwnPropertiesModel);
    // Properties Model Changed Signal
    void propertiesModelChanged(ComponentPropertiesModel* aPropertiesModel);
    // Singals Model Changed Signal
    void signalsModelChanged(ComponentSignalsModel* aSignalsModel);
    // Slots Model Changed Signal
    void slotsModelChanged(ComponentSlotsModel* aSlotsModel);
    // States Model Changed Signal
    void statesModelChanged(ComponentStatesModel* aStatesModel);
    // Transitions Model Changed Signal
    void transitionsModelChanged(ComponentTransitionsModel* aTransitionsModel);
    // Functions Model Changed Signal
    void functionsModelChanged(ComponentFunctionsModel* aFunctionsModel);
    // Animation Components Model Changed Signal
    void animComponentsModelChanged(AnimationComponentsModel* aAnimComponentsModel);

    // Component Updated Signal
    void componentUpdated();

    // ...

private:
    // Init
    void init();
    // Clear
    void clear();

    // Set Filtered Properties
    void setFilteredProperties(const QStringList& aProperties);
    // Get Filtered Property Changes
    void setFilteredPropertyChanges(const QStringList& aFilteredChanges);

    // Set Imports Model
    void setImportsModel(ComponentImportsModel* aImportsModel);
    // Set Anchors Model
    void setAnchorsModel(ComponentAnchorsModel* aAnchorsModel);
    // Set Own Properties Model
    void setOwnPropertiesModel(ComponentOwnPropertiesModel* aOwnPropertiesModel);
    // Set Properties Model
    void setPropertiesModel(ComponentPropertiesModel* aPropertiesModel);
    // Set Signals Model
    void setSignalsModel(ComponentSignalsModel* aSignalsModel);
    // Set Slots Model
    void setSlotsModel(ComponentSlotsModel* aSlotsModel);
    // Set States Model
    void setStatesModel(ComponentStatesModel* aStatesModel);
    // Set Transitions Model
    void setTransitionsModel(ComponentTransitionsModel* aTransitionsModel);
    // Set Functions Model
    void setFunctionsModel(ComponentFunctionsModel* aFunctionsModel);
    // Set Animation Components Model
    void setAnimComponentsModel(AnimationComponentsModel* aAnimComponentsModel);

private slots:
    // Child About To Be Removed Slot
    void childAboutToBeRemoved(ComponentInfo* aChild);

protected: // Data
    friend class ProjectModel;
    friend class MainWindow;

    // Project Model
    ProjectModel*                   mProject;

    // Focused Component
    ComponentInfo*                  mFocusedComponent;
    // Focused Container
    QObject*                        mFocusedContainer;

    // Filtered Properties
    QStringList                     mFilteredProperties;
    // Filtered Properties
    QStringList                     mFilteredPropertyChanges;

    // Imports
    ComponentImportsModel*          mComponentImports;
    // Anchors
    ComponentAnchorsModel*          mComponentAnchors;
    // Own Properties
    ComponentOwnPropertiesModel*    mComponentOwnProperties;
    // Properties
    ComponentPropertiesModel*       mComponentProperties;
    // Signals
    ComponentSignalsModel*          mComponentSignals;
    // Slots
    ComponentSlotsModel*            mComponentSlots;
    // Functions
    ComponentFunctionsModel*        mComponentFunctions;
    // States
    ComponentStatesModel*           mComponentStates;
    // Transitions
    ComponentTransitionsModel*      mComponentTransitions;
    // Animation Components Model
    AnimationComponentsModel*       mAnimationComponents;
};

#endif // PROPERTIESCONTROLLER_H
