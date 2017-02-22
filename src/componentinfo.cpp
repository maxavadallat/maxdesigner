#include <QDebug>

#include "componentinfo.h"
#include "qmlparser.h"
#include "constants.h"

//==============================================================================
// Create Component From QML File
//==============================================================================
ComponentInfo* ComponentInfo::fromQML(const QString& aFilePath)
{
    // Init Parser
    QMLParser parser;
    // Parse QML
    return parser.parseQML(aFilePath);
}

//==============================================================================
// Constructor
//==============================================================================
ComponentInfo::ComponentInfo(const QString& aName, const QString& aType, const QString& aParentName, QObject* aParent)
    : QObject(aParent)
    , QJsonObject()
    , mName(aName)
    , mType(aType)
    , mParentName(aParentName)
    , mParent(NULL)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentInfo::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentInfo::clear()
{
    // Clear Children
}

//==============================================================================
// Load
//==============================================================================
void ComponentInfo::load()
{

}

//==============================================================================
// Save
//==============================================================================
void ComponentInfo::save()
{

}

//==============================================================================
// Set Parent
//==============================================================================
void ComponentInfo::setParent(ComponentInfo* aParent)
{
    // Set Parent
    mParent = aParent;
}

//==============================================================================
// Export To QML
//==============================================================================
void ComponentInfo::exportToQML(const QString& aFilePath)
{
    // ...
}

//==============================================================================
// Add Propery
//==============================================================================
void ComponentInfo::addProperty(const QString& aName, const QVariant& aValue)
{
    mProperties[aName] = aValue.toJsonValue();
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::property(const QString& aName)
{
    return mProperties.value(aName);
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentInfo::setProperty(const QString& aName, const QVariant& aValue)
{
    mProperties[aName] = aValue.toJsonObject();
}

//==============================================================================
// Add Child
//==============================================================================
void ComponentInfo::addChild(ComponentInfo* aChild)
{
    // Check Child
    if (aChild) {
        // ...
    }
}

//==============================================================================
// Remove Child
//==============================================================================
void ComponentInfo::removeChild(ComponentInfo* aChild)
{
    // Check Child
    if (aChild) {
        // ...
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentInfo::~ComponentInfo()
{
    // Clear
    clear();
}


