#include <QDebug>

#include "propertiescontroller.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "componentpropertiesmodel.h"
#include "componentsignalsmodel.h"
#include "componentanchorsmodel.h"
#include "componentstatesmodel.h"
#include "componenttransitionsmodel.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
PropertiesController::PropertiesController(ProjectModel* aProjectModel, QObject* aParent)
    : QObject(aParent)
    , mProject(aProjectModel)
    , mFocusedComponent(NULL)
    , mComponentAnchors(NULL)
    , mComponentSignals(NULL)
    , mComponentProperties(NULL)
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
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void PropertiesController::clear()
{
    // Check Component Anchors Model
    if (mComponentAnchors) {
        // Delete Component Anchors Model
        delete mComponentAnchors;
        mComponentAnchors = NULL;
    }

    // Check Component Signals Model
    if (mComponentSignals) {
        // Delete Component Signals Model
        delete mComponentSignals;
        mComponentSignals = NULL;
    }

    // Check Component Properties Model
    if (mComponentProperties) {
        // Delete Component Properties Model
        delete mComponentProperties;
        mComponentProperties = NULL;
    }

    // Check Component States Model
    if (mComponentStates) {
        // Delete Component States Model
        delete mComponentStates;
        mComponentStates = NULL;
    }

    // Check Component Transitions Model
    if (mComponentTransitions) {
        // Delete Component Transitions Model
        delete mComponentTransitions;
        mComponentTransitions = NULL;
    }

    // ...
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
        qDebug() << "PropertiesController::setCurrentProject - projectName: " << (aProjectModel ? aProjectModel->projectName() : "NULL");
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

        // Check Previous Focused Component


        qDebug() << "PropertiesController::setFocusedCompoenent - componentName: " << (aComponent ? aComponent->componentName() : "NULL");

        // Set Focused Component
        mFocusedComponent = aComponent;

        // Emit Focused Component Changed Signal
        emit focusedComponentChanged(mFocusedComponent);

        // Load Models

        // Emit Changes For All Properties

        // ...
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
    if (mFocusedComponent) {
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
    if (mFocusedComponent) {
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
    if (mFocusedComponent) {
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
    if (mFocusedComponent) {
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
    if (mFocusedComponent) {
        // Set Height
        mFocusedComponent->setHeight(aHeight);
    }
}

// ...

//==============================================================================
// Add Own Property
//==============================================================================
void PropertiesController::addOwnProperty(const QString& aName, PropertiesController::EPropertyType aType)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Switch Type
        switch (aType) {
            default:
            case PropertiesController::EPropertyType::EPTString:
                // Set Property
                mFocusedComponent->setComponentProperty(aName, QVariant(QVariant::String));
            break;

            case PropertiesController::EPropertyType::EPTBool:
                // Set Property
                mFocusedComponent->setComponentProperty(aName, QVariant(QVariant::Bool));
            break;

            case PropertiesController::EPropertyType::EPTInt:
                // Set Property
                mFocusedComponent->setComponentProperty(aName, QVariant(QVariant::Int));
            break;

            case PropertiesController::EPropertyType::EPTReal:
            case PropertiesController::EPropertyType::EPTDouble:
                // Set Property
                mFocusedComponent->setComponentProperty(aName, QVariant(QVariant::Double));
            break;

            case PropertiesController::EPropertyType::EPTVar:
                // Set Property
                mFocusedComponent->setComponentProperty(aName, QJsonObject());
            break;
        }
    }
}

//==============================================================================
// Remove Own Property
//==============================================================================
void PropertiesController::removeOwnProperty(const QString& aName)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Remove Property
        mFocusedComponent->removeProperty(aName);
    }
}

//==============================================================================
// Set Property
//==============================================================================
void PropertiesController::setProperty(const QString& aName, const QString& aValue)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Set Property
        mFocusedComponent->setComponentProperty(aName, aValue);
    }
}

//==============================================================================
// Clear Property
//==============================================================================
void PropertiesController::clearProperty(const QString& aName)
{
    // Check Focused Component
    if (mFocusedComponent) {
        // Remove Property
        mFocusedComponent->removeProperty(aName);
    }
}

//==============================================================================
// Add Signal
//==============================================================================
void PropertiesController::addSignal(const QString& aSignalDef)
{
    Q_UNUSED(aSignalDef);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

//==============================================================================
// Remove Signal
//==============================================================================
void PropertiesController::removeSignal(const QString& aSignalDef)
{
    Q_UNUSED(aSignalDef);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

//==============================================================================
// Add State
//==============================================================================
void PropertiesController::addState(const QString& aName)
{
    Q_UNUSED(aName);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

//==============================================================================
// Remove State
//==============================================================================
void PropertiesController::removeState(const QString& aName)
{
    Q_UNUSED(aName);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

//==============================================================================
// Add Transition
//==============================================================================
void PropertiesController::addTransition(const QString& aFrom, const QString& aTo)
{
    Q_UNUSED(aFrom);
    Q_UNUSED(aTo);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

//==============================================================================
// Remove Transition
//==============================================================================
void PropertiesController::removeTransition(const QString& aFrom, const QString& aTo)
{
    Q_UNUSED(aFrom);
    Q_UNUSED(aTo);

    // Check Focused Component
    if (mFocusedComponent) {

        // ...
    }
}

// ...

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
