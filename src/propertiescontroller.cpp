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
ComponentInfo* PropertiesController::focusedCompoenent()
{
    return mFocusedComponent;
}

//==============================================================================
// Set Focused Component
//==============================================================================
void PropertiesController::setFocusedCompoenent(ComponentInfo* aComponent)
{
    // Check Focused Component
    if (mFocusedComponent != aComponent) {
        qDebug() << "PropertiesController::setFocusedCompoenent - componentName: " << (aComponent ? aComponent->componentName() : "NULL");

        // Set Focused Component
        mFocusedComponent = aComponent;
        // Emit Focused Component Changed Signal
        emit focusedCompoenentChanged(mFocusedComponent);
    }
}

// Get Component ID
QString PropertiesController::cID()
{

}

// Request Component ID
void PropertiesController::requestCID(const QString& aID)
{
}

// Get Component Object Name
QString PropertiesController::cObjectName()
{

}

// Request Component Object Name
void PropertiesController::requestCObjectName(const QString& aObjectName)
{

}

// Get Component X
QString PropertiesController::cX()
{

}

// Request Component X
void PropertiesController::requestCX(const QString& aX)
{

}

// Get Component Y
QString PropertiesController::cY()
{

}

// Request Component Y
void PropertiesController::requestCY(const QString& aY)
{

}

// Get Component Z
QString PropertiesController::cZ()
{

}

// Request Component Z
void PropertiesController::requestCZ(const QString& aZ)
{

}

// Get Component Width
QString PropertiesController::cWidth()
{

}

// Request Component Width
void PropertiesController::requestCWidth(const QString& aWidth)
{

}

// Get Component Height
QString PropertiesController::cHeight()
{

}

// Request Component Height
void PropertiesController::requestCHeight(const QString& aHeight)
{

}

// ...

//==============================================================================
// Add Own Property
//==============================================================================
void PropertiesController::addOwnProperty(const QString& aKey, PropertiesController::EPropertyType aType)
{

}

//==============================================================================
// Remove Own Property
//==============================================================================
void PropertiesController::removeOwnProperty(const QString& aKey)
{

}

//==============================================================================
// Set Property
//==============================================================================
void PropertiesController::setProperty(const QString& aKey, const QString& aValue)
{

}

//==============================================================================
// Clear Property
//==============================================================================
void PropertiesController::clearProperty(const QString& aKey)
{

}

//==============================================================================
// Add Signal
//==============================================================================
void PropertiesController::addSignal(const QString& aSignalDef)
{

}

//==============================================================================
// Remove Signal
//==============================================================================
void PropertiesController::removeSignal(const QString& aSignalDef)
{

}

//==============================================================================
// Add State
//==============================================================================
void PropertiesController::addState(const QString& aName)
{

}

//==============================================================================
// Remove State
//==============================================================================
void PropertiesController::removeState(const QString& aName)
{

}

//==============================================================================
// Add Transition
//==============================================================================
void PropertiesController::addTransition(const QString& aFrom, const QString& aTo)
{

}

//==============================================================================
// Remove Transition
//==============================================================================
void PropertiesController::removeTransition(const QString& aFrom, const QString& aTo)
{

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
