#include <QDebug>

#include "propertiescontroller.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "componentimportsmodel.h"
#include "componentownpropertiesmodel.h"
#include "componentpropertiesmodel.h"
#include "componentsignalsmodel.h"
#include "componentslotsmodel.h"
#include "componentanchorsmodel.h"
#include "componentstatesmodel.h"
#include "componenttransitionsmodel.h"
#include "componentfunctionsmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
PropertiesController::PropertiesController(ProjectModel* aProjectModel, QObject* aParent)
    : QObject(aParent)
    , mProject(aProjectModel)
    , mFocusedComponent(NULL)
    , mComponentImports(NULL)
    , mComponentAnchors(NULL)
    , mComponentOwnProperties(NULL)
    , mComponentProperties(NULL)
    , mComponentSignals(NULL)
    , mComponentSlots(NULL)
    , mComponentFunctions(NULL)
    , mComponentStates(NULL)
    , mComponentTransitions(NULL)
{
    qDebug() << "PropertiesController created.";
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void PropertiesController::init()
{
    //qDebug() << "PropertiesController::init";

    // Check Project Model
    if (mProject) {
        // Set Properties Controller
        mProject->setPropertiesController(this);
        // Update Base Components
        mProject->updateBaseComponents();
    }

    // Set Filtered Properties
    setFilteredProperties(QString("id,objectName,x,y,z,width,height,states,transitions,children").split(","));
    // Set Filtered Property Changes
    setFilteredPropertyChanges(QString("x,y,z").split(","));

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void PropertiesController::clear()
{
    //qDebug() << "PropertiesController::clear";

    // Set Focused Component
    setFocusedComponent(NULL);

    // Check Component Imports Model
    if (mComponentImports) {
        // Delete Component Imports Model
        delete mComponentImports;
        mComponentImports = NULL;
        // Set Component Imports Model
        setImportsModel(NULL);
    }

    // Check Component Anchors Model
    if (mComponentAnchors) {
        // Delete Component Anchors Model
        delete mComponentAnchors;
        mComponentAnchors = NULL;
        // Set Component Anchors Model
        setAnchorsModel(NULL);
    }

    // Check Component Properties Model
    if (mComponentProperties) {
        // Delete Component Properties Model
        delete mComponentProperties;
        mComponentProperties = NULL;
        // Set Component Properties Model
        setPropertiesModel(NULL);
    }

    // Check Component Own Properties Model
    if (mComponentOwnProperties) {
        // Delete Component Own Properties Model
        delete mComponentOwnProperties;
        mComponentOwnProperties = NULL;
        // Set Component Own Properties Model
        setOwnPropertiesModel(NULL);
    }

    // Check Component Signals Model
    if (mComponentSignals) {
        // Delete Component Signals Model
        delete mComponentSignals;
        mComponentSignals = NULL;
        // Set Component Signals Model
        setSignalsModel(NULL);
    }

    // Check Component Slots Model
    if (mComponentSlots) {
        // Delete Compoennt Slots Model
        delete mComponentSlots;
        mComponentSlots = NULL;
        // Set Component Slots Model
        setSlotsModel(mComponentSlots);
    }

    // Check Component States Model
    if (mComponentStates) {
        // Delete Component States Model
        delete mComponentStates;
        mComponentStates = NULL;
        // Set Component States Model
        setStatesModel(NULL);
    }

    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Delete Component Transitions Model
        delete mComponentTransitions;
        mComponentTransitions = NULL;
        // Set Component Transitions Model
        setTransitionsModel(NULL);
    }

    // Check Component Functions Model
    if (mComponentFunctions) {
        // Delete Component Functions Model
        delete mComponentFunctions;
        mComponentFunctions = NULL;
        // Set Component Functions Model
        setFunctionsModel(NULL);
    }

    // Clear Filtered Properties
    mFilteredProperties.clear();

    // ...
}

//==============================================================================
// Set Filtered Properties
//==============================================================================
void PropertiesController::setFilteredProperties(const QStringList& aProperties)
{
    // Check Filtered Properties
    if (mFilteredProperties != aProperties) {
        // Set Filtered Properties
        mFilteredProperties = aProperties;
        // Emit Filtered Properties Changed Signal
        emit filteredPropertiesChanged(mFilteredProperties);
    }
}

//==============================================================================
// Get Filtered Property Changes
//==============================================================================
void PropertiesController::setFilteredPropertyChanges(const QStringList& aFilteredChanges)
{
    // Check filtered Property Changes
    if (mFilteredPropertyChanges != aFilteredChanges) {
        // Set Filtered Property Changes
        mFilteredPropertyChanges = aFilteredChanges;
        // Emit Filtered Property Changes Changed Signal
        emit filteredPropertyChangesChanged(mFilteredPropertyChanges);
    }
}

//==============================================================================
// Set Imports Model
//==============================================================================
void PropertiesController::setImportsModel(ComponentImportsModel* aImportsModel)
{
    // Check Component Imports Model
    if (mComponentImports != aImportsModel) {
        // Set Component Imports Model
        mComponentImports = aImportsModel;
        // Emit Component Imports Model Changed Signal
        emit importsModelChanged(mComponentImports);
    }
}

//==============================================================================
// Set Anchors Model
//==============================================================================
void PropertiesController::setAnchorsModel(ComponentAnchorsModel* aAnchorsModel)
{
    // Check Component Anchors Model
    if (mComponentAnchors != aAnchorsModel) {
        // Set Component Anchors Model
        mComponentAnchors = aAnchorsModel;
        // Emit Component Anchors Model Changed Signal
        emit anchorsModelChanged(mComponentAnchors);
    }
}

//==============================================================================
// Set Own Properties Model
//==============================================================================
void PropertiesController::setOwnPropertiesModel(ComponentOwnPropertiesModel* aOwnPropertiesModel)
{
    // Check Component Own Properties Model
    if (mComponentOwnProperties != aOwnPropertiesModel) {
        // Set Component Own Properties Model
        mComponentOwnProperties = aOwnPropertiesModel;
        // Emit Component Own Properties Model Changed Signal
        emit ownPropertiesModelChanged(mComponentOwnProperties);
    }
}

//==============================================================================
// Set Properties Model
//==============================================================================
void PropertiesController::setPropertiesModel(ComponentPropertiesModel* aPropertiesModel)
{
    // Check Component Properties Model
    if (mComponentProperties != aPropertiesModel) {
        // Set Component Properties Model
        mComponentProperties = aPropertiesModel;
        // Emit Component Properties Model Changed Signal
        emit propertiesModelChanged(mComponentProperties);
    }
}

//==============================================================================
// Set Signals Model
//==============================================================================
void PropertiesController::setSignalsModel(ComponentSignalsModel* aSignalsModel)
{
    // Check Component Signals Model
    if (mComponentSignals != aSignalsModel) {
        // Set Component Signals Model
        mComponentSignals = aSignalsModel;
        // Emit Component Signals Model Changed Signal
        emit signalsModelChanged(mComponentSignals);
    }
}

//==============================================================================
// Set Slots Model
//==============================================================================
void PropertiesController::setSlotsModel(ComponentSlotsModel* aSlotsModel)
{
    // Check Component Slots Model
    if (mComponentSlots != aSlotsModel) {
        // Set Component Slots Model
        mComponentSlots = aSlotsModel;
        // Emit Component Slots Model Changed Signal
        emit slotsModelChanged(mComponentSlots);
    }
}

//==============================================================================
// Set States Model
//==============================================================================
void PropertiesController::setStatesModel(ComponentStatesModel* aStatesModel)
{
    // Check Component States Model
    if (mComponentStates != aStatesModel) {
        // Set Component States Model
        mComponentStates = aStatesModel;
        // Emit Component States Model Changed Signal
        emit statesModelChanged(mComponentStates);
    }
}

//==============================================================================
// Set Transitions Model
//==============================================================================
void PropertiesController::setTransitionsModel(ComponentTransitionsModel* aTransitionsModel)
{
    // Check Component Transitions Model
    if (mComponentTransitions != aTransitionsModel) {
        // Set Component Transitions Model
        mComponentTransitions = aTransitionsModel;
        // Emit Component Transitions Model Changed Signal
        emit transitionsModelChanged(mComponentTransitions);
    }
}

//==============================================================================
// Set Functions Model
//==============================================================================
void PropertiesController::setFunctionsModel(ComponentFunctionsModel* aFunctionsModel)
{
    // Check Component Functions Model
    if (mComponentFunctions != aFunctionsModel) {
        // Set Component Functions Model
        mComponentFunctions = aFunctionsModel;
        // Emit Component Functions Model Changed Signal
        emit functionsModelChanged(mComponentFunctions);
    }
}

//==============================================================================
// Child About To Be Removed Slot
//==============================================================================
void PropertiesController::childAboutToBeRemoved(ComponentInfo* aChild)
{
    // Check Child Component
    if (mFocusedComponent == aChild) {
        // Check Child Component
        if (aChild && aChild->mParent) {
            // Set Focused Component
            setFocusedComponent(aChild->mParent);
        } else {
            // Set Focused Component
            setFocusedComponent(NULL);
        }
    }
}

//==============================================================================
// Get Current Project
//==============================================================================
ProjectModel* PropertiesController::currentProject()
{
    return mProject;
}

//==============================================================================
// Set Current Project
//==============================================================================
void PropertiesController::setCurrentProject(ProjectModel* aProjectModel)
{
    // Check Current Project Model
    if (mProject != aProjectModel) {
        qDebug() << "PropertiesController::setCurrentProject - aProjectModel: " << (aProjectModel ? aProjectModel->projectName() : "NULL");
        // Set Current Project Model
        mProject = aProjectModel;
        // Emit Current Project Changed Signal
        emit currentProjectChanged(mProject);
    }
}

//==============================================================================
// Get Focused Component
//==============================================================================
ComponentInfo* PropertiesController::focusedComponent()
{
    return mFocusedComponent;
}

//==============================================================================
// Set Focused Component
//==============================================================================
void PropertiesController::setFocusedComponent(ComponentInfo* aComponent)
{
    // Check Focused Component
    if (mFocusedComponent != aComponent) {

        //qDebug() << "PropertiesController::setFocusedComponent - aComponent: " << (aComponent ? aComponent->mName : "NULL");

        // Check Focused Component
        if (mFocusedComponent) {
            // Disconnect Signal
            disconnect(mFocusedComponent, SIGNAL(childAboutToBeRemoved(ComponentInfo*)), this, SLOT(childAboutToBeRemoved(ComponentInfo*)));
        }

        // Set Focused Component
        mFocusedComponent = aComponent;

        // Check Inherited Properties Model
        if (mComponentProperties) {
            // Set Current Component
            mComponentProperties->setCurrentComponent(aComponent);
        } else {
            // Create New Compoennt Inherited Properties Model
            ComponentPropertiesModel* newComponentPropertiesModel = new ComponentPropertiesModel(mFocusedComponent, mProject);
            // Set Component Inherited Properties Model
            setPropertiesModel(newComponentPropertiesModel);
        }

        // Check Imports Model
        if (mComponentImports) {
            // Set Current Component
            mComponentImports->setCurrentComponent(aComponent);
        } else {
            // Create New Imports Model
            ComponentImportsModel* newImportsModel = new ComponentImportsModel(mFocusedComponent);
            // Set Component Imports Model
            setImportsModel(newImportsModel);
        }

        // Check Own Properties Model
        if (mComponentOwnProperties) {
            // Set Current Component
            mComponentOwnProperties->setCurrentComponent(aComponent);
        } else {
            // Create New Component Own Properties Model
            ComponentOwnPropertiesModel* newOwnPropertiesModel = new ComponentOwnPropertiesModel(mFocusedComponent, mProject);
            // Set Component Own Properties Model
            setOwnPropertiesModel(newOwnPropertiesModel);
        }

        // Check Anchors Model
        if (mComponentAnchors) {
            // Set Current Component
            mComponentAnchors->setCurrentComponent(aComponent);
        } else {
            // Create New Component Anchors Model
            ComponentAnchorsModel* newComponentAnchorsModel = new ComponentAnchorsModel(mFocusedComponent);
            // Set Component Anchors Model
            setAnchorsModel(newComponentAnchorsModel);
        }

        // Check Signals Model
        if (mComponentSignals) {
            // Set Current Component
            mComponentSignals->setCurrentComponent(aComponent);
        } else {
            // Create New Component Signals Model
            ComponentSignalsModel* newComponentSignalsModel = new ComponentSignalsModel(mFocusedComponent);
            // Set Component Signals Model
            setSignalsModel(newComponentSignalsModel);
        }

        // Check Slots Model
        if (mComponentSlots) {
            // Set Current Component
            mComponentSlots->setCurrentComponent(aComponent);
        } else {
            // Create New Component Slots Model
            ComponentSlotsModel* newComponentSlotsModel = new ComponentSlotsModel(mFocusedComponent);
            // Set Component Slots Model
            setSlotsModel(newComponentSlotsModel);
        }

        // Check Component Functions Model
        if (mComponentFunctions) {
            // Set Current Component
            mComponentFunctions->setCurrentComponent(aComponent);
        } else {
            // Create New Component Functions Model
            ComponentFunctionsModel* newComponentFunctionsModel = new ComponentFunctionsModel(mFocusedComponent);
            // Set Component Functions Model
            setFunctionsModel(newComponentFunctionsModel);
        }

        // Check Component States
        if (mComponentStates) {
            // Set Current Component
            mComponentStates->setCurrentComponent(aComponent);
        } else {
            // Create New Component States Model
            ComponentStatesModel* newComponentStatesModel = new ComponentStatesModel(mFocusedComponent);
            // Set Component States Model
            setStatesModel(newComponentStatesModel);
        }

        // Check Transitions Model
        if (mComponentTransitions) {
            // Set Current Component
            mComponentTransitions->setCurrentComponent(aComponent);
        } else {
            // Create New Component Trnsitions Model
            ComponentTransitionsModel* newComponentTransitionsModel = new ComponentTransitionsModel(mFocusedComponent);
            // Set Component Transitions Model
            setTransitionsModel(newComponentTransitionsModel);
        }

        // ...

        // Check Focused Component
        if (mFocusedComponent) {
            // Connect Signal
            connect(mFocusedComponent, SIGNAL(childAboutToBeRemoved(ComponentInfo*)), this, SLOT(childAboutToBeRemoved(ComponentInfo*)));
        }

        // Emit Focused Component Changed Signal
        emit focusedComponentChanged(mFocusedComponent);
    }
}

//==============================================================================
// Get Component ID
//==============================================================================
QString PropertiesController::cID()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_ID).toString() : "";
}

//==============================================================================
// Request Component ID
//==============================================================================
void PropertiesController::requestCID(const QString& aID)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Set Component ID
        mFocusedComponent->setComponentID(aID);
    }
}

//==============================================================================
// Get Component Object Name
//==============================================================================
QString PropertiesController::cObjectName()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME).toString() : "";
}

//==============================================================================
// Request Component Object Name
//==============================================================================
void PropertiesController::requestCObjectName(const QString& aObjectName)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Set Component Object Name
        mFocusedComponent->setComponentObjectName(aObjectName);
    }
}

//==============================================================================
// Get Component X
//==============================================================================
QString PropertiesController::cX()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_X).toString() : "";
}

//==============================================================================
// Request Component X
//==============================================================================
void PropertiesController::requestCX(const QString& aX)
{
    // Check Focused Component
    if (mFocusedComponent && mFocusedComponent->mCategory != COMPONENT_CATEGORY_NONVISUAL && !mFocusedComponent->mIsRoot) {
        // Set Pos X
        mFocusedComponent->setPosX(aX);
    }
}

//==============================================================================
// Get Component Y
//==============================================================================
QString PropertiesController::cY()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_Y).toString() : "";
}

//==============================================================================
// Request Component Y
//==============================================================================
void PropertiesController::requestCY(const QString& aY)
{
    // Check Focused Component
    if (mFocusedComponent && mFocusedComponent->mCategory != COMPONENT_CATEGORY_NONVISUAL && !mFocusedComponent->mIsRoot) {
        // Set Pos Y
        mFocusedComponent->setPosY(aY);
    }
}

//==============================================================================
// Get Component Z
//==============================================================================
QString PropertiesController::cZ()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_Z).toString() : "";
}

//==============================================================================
// Request Component Z
//==============================================================================
void PropertiesController::requestCZ(const QString& aZ)
{
    // Check Focused Component
    if (mFocusedComponent && mFocusedComponent->mCategory != COMPONENT_CATEGORY_NONVISUAL && !mFocusedComponent->mIsRoot) {
        // Set Pos Z
        mFocusedComponent->setPosZ(aZ);
    }
}

//==============================================================================
// Get Component Width
//==============================================================================
QString PropertiesController::cWidth()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH).toString() : "";
}

//==============================================================================
// Request Component Width
//==============================================================================
void PropertiesController::requestCWidth(const QString& aWidth)
{
    // Check Focused Component
    if (mFocusedComponent && mFocusedComponent->mCategory != COMPONENT_CATEGORY_NONVISUAL) {
        // Set Width
        mFocusedComponent->setWidth(aWidth);
    }
}

//==============================================================================
// Get Component Height
//==============================================================================
QString PropertiesController::cHeight()
{
    return mFocusedComponent ? mFocusedComponent->componentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT).toString() : "";
}

//==============================================================================
// Request Component Height
//==============================================================================
void PropertiesController::requestCHeight(const QString& aHeight)
{
    // Check Focused Component
    if (mFocusedComponent && mFocusedComponent->mCategory != COMPONENT_CATEGORY_NONVISUAL) {
        // Set Height
        mFocusedComponent->setHeight(aHeight);
    }
}

//==============================================================================
// Get Filtered Properties
//==============================================================================
QStringList PropertiesController::filteredProperties()
{
    return mFilteredProperties;
}

//==============================================================================
// Get Filtered Property Changes
//==============================================================================
QStringList PropertiesController::filteredPropertyChanges()
{
    return mFilteredPropertyChanges;
}

//==============================================================================
// Get Imports Model
//==============================================================================
ComponentImportsModel* PropertiesController::importsModel()
{
    return mComponentImports;
}

//==============================================================================
// Get Anchors Model
//==============================================================================
ComponentAnchorsModel* PropertiesController::anchorsModel()
{
    return mComponentAnchors;
}

//==============================================================================
// Get Own Properties Model
//==============================================================================
ComponentOwnPropertiesModel* PropertiesController::ownPropertiesModel()
{
    return mComponentOwnProperties;
}

//==============================================================================
// Get Signals Model
//==============================================================================
ComponentSignalsModel* PropertiesController::signalsModel()
{
    return mComponentSignals;
}

//==============================================================================
// Get Slots Model
//==============================================================================
ComponentSlotsModel* PropertiesController::slotsModel()
{
    return mComponentSlots;
}

//==============================================================================
// Get States Model
//==============================================================================
ComponentStatesModel* PropertiesController::statesModel()
{
    return mComponentStates;
}

//==============================================================================
// Get Transitins Model
//==============================================================================
ComponentTransitionsModel* PropertiesController::transitionsModel()
{
    return mComponentTransitions;
}

//==============================================================================
// Get Properties Model
//==============================================================================
ComponentPropertiesModel* PropertiesController::propertiesModel()
{
    return mComponentProperties;
}

//==============================================================================
// Get Functions Model
//==============================================================================
ComponentFunctionsModel* PropertiesController::functionsModel()
{
    return mComponentFunctions;
}

//==============================================================================
// Set Component Tag
//==============================================================================
void PropertiesController::setComponentTag(const QString& aTag)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Set Component Tag
        mFocusedComponent->setComponentTag(aTag);
    }
}

//==============================================================================
// Select Component By Name
//==============================================================================
void PropertiesController::selectComponent(const QString& aName, const int& aChildIndex)
{
    // Check Name
    if (aName.isEmpty()) {
        return;
    }

    // Check Project Model
    if (!mProject) {
        return;
    }

    // Get Component
    ComponentInfo* componentInfo = mProject->getComponentByName(aName);
    // Check Component Info
    if (componentInfo) {
        // Set Focused Component
        setFocusedComponent(aChildIndex >= 0 ? componentInfo->childInfo(aChildIndex) : componentInfo);
    }
}

//==============================================================================
// Add Import
//==============================================================================
void PropertiesController::addComponentImport(const QString& aImport)
{
    // Check Component Imports Model
    if (mComponentImports) {
        // Add Import
        mComponentImports->addImport(aImport);
    }
}

//==============================================================================
// Remove Import
//==============================================================================
void PropertiesController::removeComponentImport(const int& aIndex)
{
    // Check Component Imports Model
    if (mComponentImports) {
        // Remove Import
        mComponentImports->removeImport(aIndex);
    }
}

//==============================================================================
// Get Component Property
//==============================================================================
QVariant PropertiesController::componentProperty(const QString& aName)
{
    // Check Name
    if (aName.isEmpty()) {
        qWarning() << "PropertiesController::componentProperty - aName: IS EMPTY!";
        return QVariant();
    }

    // Check Focused Component
    if (!mFocusedComponent) {
        qWarning() << "PropertiesController::componentProperty - mFocusedComponent: IS NULL!";

        return QVariant();
    }

    return mFocusedComponent->componentProperty(aName);
}

//==============================================================================
// Set Property
//==============================================================================
void PropertiesController::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    // Check Name
    if (aName.isEmpty()) {
        qWarning() << "PropertiesController::setComponentProperty - aName: IS EMPTY!";
        return;
    }

    // Check Component Own Properties Model
    if (mComponentOwnProperties) {
        // Set Component Own Property Value
        if (mComponentOwnProperties->setComponentProperty(aName, aValue)) {
            //qDebug() << "PropertiesController::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - OWN";
            return;
        }
    }

    // Check Component Properties Model
    if (mComponentProperties) {
        // Set Component Property Value
        if (mComponentProperties->setComponentProperty(aName, aValue)) {
            //qDebug() << "PropertiesController::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - BASE";
            return;
        }
    }

    qWarning() << "PropertiesController::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - NO PROPERTY!!";
}

//==============================================================================
// Clear Component Property
//==============================================================================
void PropertiesController::clearComponentProperty(const QString& aName)
{
    // Check Name
    if (aName.isEmpty()) {
        qWarning() << "PropertiesController::clearComponentProperty - aName: IS EMPTY!";
        return;
    }

    // Check Focused Component
    if (!mFocusedComponent) {
        return;
    }

    // Check Component Own Properties Model
    if (mComponentOwnProperties) {
        // Set Component Own Property Value
        if (mComponentOwnProperties->clearComponentProperty(aName)) {
            qDebug() << "PropertiesController::clearComponentProperty - aName: " << aName << " - OWN";
            return;
        }
    }

    // Check Component Properties Model
    if (mComponentProperties) {
        // Set Component Property Value
        if (mComponentProperties->clearComponentProperty(aName)) {
            qDebug() << "PropertiesController::clearComponentProperty - aName: " << aName << " - BASE";
            // Get Base Component Property
            QVariant baseValue = componentProperty(aName);
            // Emit Component Property Changed Signal
            emit mFocusedComponent->componentPropertyChanged(aName, baseValue);
            return;
        }
    }

    qWarning() << "PropertiesController::clearComponentProperty - aName: " << aName << " - NO PROPERTY!!";
}

//==============================================================================
// Add Own Property
//==============================================================================
void PropertiesController::addOwnComponentProperty(const QString& aName,
                                                   const int& aType,
                                                   const QString& aMin,
                                                   const QString& aMax,
                                                   const QString& aEnumValues,
                                                   const QVariant& aDefaultValue)
{
    // Check Component Own Properties Model
    if (mComponentOwnProperties) {
        // Add Property
        mComponentOwnProperties->addComponentProperty(aName, aType, aMin, aMax, aEnumValues, aDefaultValue);
    }
}

//==============================================================================
// Remove Own Property
//==============================================================================
void PropertiesController::removeComponentProperty(const QString& aName)
{
    // Check Component Own Properties Model
    if (mComponentOwnProperties) {
        // Remove Component Property
        mComponentOwnProperties->removeComponentProperty(aName);
    }
}

//==============================================================================
// Add Signal
//==============================================================================
void PropertiesController::addSignal(const QString& aName, const QStringList& aParameters)
{
    // Check Component Signals Model
    if (mComponentSignals) {
        // Add Signal
        mComponentSignals->addSignal(aName, aParameters);
    }
}

//==============================================================================
// Remove Signal
//==============================================================================
void PropertiesController::removeSignal(const int& aIndex)
{
    // Check Component Signals Model
    if (mComponentSignals) {
        // Remove Signal
        mComponentSignals->removeSignal(aIndex);
    }
}

//==============================================================================
// Add Slot
//==============================================================================
void PropertiesController::addSlot(const QString& aName, const QString& aSource)
{
    // Check Component Slots Model
    if (mComponentSlots) {
        // Add Slot
        mComponentSlots->addSlot(aName, aSource);
    }
}

//==============================================================================
// Remove Slot
//==============================================================================
void PropertiesController::removeSlot(const int& aIndex)
{
    // Check Component Slots Model
    if (mComponentSlots) {
        // Remove Slot
        mComponentSlots->removeSlot(aIndex);
    }
}

//==============================================================================
// Add Function
//==============================================================================
void PropertiesController::addFunction(const QString& aName, const QStringList& aParameters, const QString& aSource)
{
    // Check Compoennt Functions Model
    if (mComponentFunctions) {
        // Add Function
        mComponentFunctions->addFunction(aName, aParameters, aSource);
    }
}

//==============================================================================
// Remove Function
//==============================================================================
void PropertiesController::removeFunction(const int& aIndex)
{
    // Check Compoennt Functions Model
    if (mComponentFunctions) {
        // Remove Function
        mComponentFunctions->removeFunction(aIndex);
    }
}

//==============================================================================
// Add State
//==============================================================================
void PropertiesController::addState(const QString& aName, const QString& aWhen)
{
    // Check Component States Model
    if (mComponentStates) {
        // Add State
        mComponentStates->addState(aName, aWhen);
    }
}

//==============================================================================
// Remove State
//==============================================================================
void PropertiesController::removeState(const int& aIndex)
{
    // Check Component States Model
    if (mComponentStates) {
        // Remove State
        mComponentStates->removeState(aIndex);
    }
}

//==============================================================================
// Add Property Change
//==============================================================================
void PropertiesController::addPropertyChange(const QString& aStateName, const QString& aTarget, const QString& aProperty, const QString& aValue)
{
    // Check Component States Model
    if (mComponentStates) {
        // Add Property Change
        mComponentStates->addPropertyChange(aStateName, aTarget, aProperty, aValue);
    }
}

//==============================================================================
// Add Transition
//==============================================================================
void PropertiesController::addTransition(const QString& aFrom, const QString& aTo)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Transition
        mComponentTransitions->addTransition(aFrom, aTo);
    }
}

//==============================================================================
// Remove Transition
//==============================================================================
void PropertiesController::removeTransition(const int& aIndex)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Remove Transitions
        mComponentTransitions->removeTransition(aIndex);
    }
}

//==============================================================================
// Remove Transition
//==============================================================================
void PropertiesController::removeTransition(ComponentTransition* aTransition)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Remove Transition
        mComponentTransitions->removeTransition(aTransition);
    }
}

//==============================================================================
// Add Parallel Animation Node
//==============================================================================
void PropertiesController::addParallelAnimation(ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Parallel Animation
        mComponentTransitions->addParallelAnimation(aTransition, aParentNode);
    }
}

//==============================================================================
// Add Sequential Animation Node
//==============================================================================
void PropertiesController::addSequentialAnimation(ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Sequential Animatino
        mComponentTransitions->addSequentialAnimation(aTransition, aParentNode);
    }
}

//==============================================================================
// Add Pause Animation Node
//==============================================================================
void PropertiesController::addPauseAnimation(const QString& aDuration, ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Pause Animation
        mComponentTransitions->addPauseAnimation(aDuration, aTransition, aParentNode);
    }
}

//==============================================================================
// Add Property Animation Node
//==============================================================================
void PropertiesController::addPropertyAnimation(const QString& aTarget,
                                                const QString& aProperty,
                                                const QString& aFrom,
                                                const QString& aTo,
                                                const QString& aDuration,
                                                const QString& aEasing,
                                                ComponentTransition* aTransition,
                                                ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Property Animation
        mComponentTransitions->addPropertyAnimation(aTarget, aProperty, aFrom, aTo, aDuration, aEasing, aTransition, aParentNode);
    }
}

//==============================================================================
// Add Property Action Node
//==============================================================================
void PropertiesController::addPropertyAction(const QString& aTarget, const QString& aProperty, const QString& aValue, ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Property Action
        mComponentTransitions->addPropertyAction(aTarget, aProperty, aValue, aTransition, aParentNode);
    }
}

//==============================================================================
// Add Script Action Node
//==============================================================================
void PropertiesController::addScriptAction(const QString& aScript, ComponentTransition* aTransition, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Add Script Action
        mComponentTransitions->addScriptAction(aScript, aTransition, aParentNode);
    }
}

//==============================================================================
// Remove Transition Node
//==============================================================================
void PropertiesController::removeTransitionNode(ComponentTransition* aTransition, ComponentTransitionNode* aNode, ComponentTransitionNode* aParentNode)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Remove Transition Node
        mComponentTransitions->removeTransitionNode(aTransition, aNode, aParentNode);
    }
}

//==============================================================================
// Move Transition Node
//==============================================================================
void PropertiesController::moveTransitionNode(ComponentTransition* aTransition,
                                              ComponentTransitionNode* aNode,
                                              ComponentTransitionNode* aTargetNode,
                                              const int& aTargetIndex)
{
    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Move Transition
        mComponentTransitions->moveTransitionNode(aTransition, aNode, aTargetNode, aTargetIndex);
    }
}

//==============================================================================
// Destructor
//==============================================================================
PropertiesController::~PropertiesController()
{
    // ...

    // Clear
    clear();

    // ...

    qDebug() << "PropertiesController deleted.";
}
