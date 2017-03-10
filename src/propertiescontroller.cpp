#include <QDebug>

#include "propertiescontroller.h"
#include "projectmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
PropertiesController::PropertiesController(ProjectModel* aProjectModel, QObject* aParent)
    : QObject(aParent)
    , mProject(aProjectModel)
    , mFocusedComponent(NULL)
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
    // Clear
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
        qDebug() << "PropertiesController::setFocusedCompoenent - componentName: " << (aComponent ? aComponent->componentName() : "NULL");
        // Set Focused Component
        mFocusedComponent = aComponent;
        // Emit Focused Component Changed Signal
        emit focusedComponentChanged(mFocusedComponent);

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

}

// ...

//==============================================================================
// Add Own Property
//==============================================================================
void PropertiesController::addOwnProperty(const QString& aKey, PropertiesController::EPropertyType aType)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Remove Own Property
//==============================================================================
void PropertiesController::removeOwnProperty(const QString& aKey)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Set Property
//==============================================================================
void PropertiesController::setProperty(const QString& aKey, const QString& aValue)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Clear Property
//==============================================================================
void PropertiesController::clearProperty(const QString& aKey)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Add Signal
//==============================================================================
void PropertiesController::addSignal(const QString& aSignalDef)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Remove Signal
//==============================================================================
void PropertiesController::removeSignal(const QString& aSignalDef)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Add State
//==============================================================================
void PropertiesController::addState(const QString& aName)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Remove State
//==============================================================================
void PropertiesController::removeState(const QString& aName)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Add Transition
//==============================================================================
void PropertiesController::addTransition(const QString& aFrom, const QString& aTo)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
}

//==============================================================================
// Remove Transition
//==============================================================================
void PropertiesController::removeTransition(const QString& aFrom, const QString& aTo)
{
    // Check Focused Component
    if (!mFocusedComponent)
        return;

    // ...
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

    qDebug() << "PropertiesController deleted.";
}
