#include <QApplication>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "designerapplication.h"
#include "mainwindow.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "qmlparser.h"
#include "constants.h"

//==============================================================================
// Create Component From QML File
//==============================================================================
ComponentInfo* ComponentInfo::fromQML(const QString& aFilePath, ProjectModel* aProject)
{
    // Init Parser
    QMLParser parser;
    // Parse QML
    return parser.parseQML(aFilePath, aProject);
}

//==============================================================================
// Create Component From Component Info File
//==============================================================================
ComponentInfo* ComponentInfo::fromInfoFile(const QString& aFilePath, ProjectModel* aProject)
{
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo("", "", aProject);
    // Set Info File Path
    newComponent->mInfoPath = aFilePath;
    // Load Component
    newComponent->load();

    return newComponent;
}

//==============================================================================
// Clone Component Info
//==============================================================================
ComponentInfo* ComponentInfo::clone()
{
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mProject, mBaseName);

    // Set ProtoType
    newComponent->mProtoType = false;

    // ...

    return newComponent;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentInfo::ComponentInfo(const QString& aName, const QString& aType, ProjectModel* aProject, const QString& aBaseName, QObject* aParent)
    : QObject(aParent)
    , mProject(aProject)
    , mInfoPath("")
    , mQMLPath("")
    , mProtoType(true)
    , mName(aName)
    , mType(aType)
    , mBaseName(aBaseName)
    , mFocused(false)
    , mBase(mProject ? mProject->getComponentByName(mBaseName) : NULL)
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
void ComponentInfo::load(const QString& aFilePath)
{
    // Check File Path
    if (aFilePath.isEmpty()) {
        // Check Project
        if (!mProject) {
            return;
        }
    } else {
        // Set Info Path
        mInfoPath = aFilePath;
    }

    // Init Component Info File
    QFile ciFile(mInfoPath);

    // Open File
    if (ciFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read File Content
        QString ciFileContent = ciFile.readAll();
        // Close File
        ciFile.close();
        // From JSON
        fromJSON(ciFileContent.toUtf8());
    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }
}

//==============================================================================
// Save
//==============================================================================
void ComponentInfo::save(const QString& aFilePath)
{
    // Init Component Info File
    QFile ciFile(aFilePath.isEmpty() ? mInfoPath : aFilePath);

    // Open File
    if (ciFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream textStream(&ciFile);
        // Write To Text Stream
        textStream << toJSON();
        // Flush Text Stream
        textStream.flush();
        // Close File
        ciFile.close();
    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }
}

//==============================================================================
// Get Prototype
//==============================================================================
bool ComponentInfo::protoType()
{
    return mProtoType;
}

//==============================================================================
// Get Component Name
//==============================================================================
QString ComponentInfo::componentName()
{
    return mName;
}

//==============================================================================
// Set Component Name
//==============================================================================
void ComponentInfo::setComponentName(const QString& aName)
{
    // Check Component Name
    if (mName != aName) {
        // Set Component Name
        mName = aName;
        // Emit Component Name Changed Signal
        emit componentNameChanged(mName);
    }
}

//==============================================================================
// Get Component Type
//==============================================================================
QString ComponentInfo::componentType()
{
    return mType;
}

//==============================================================================
// Set Component Type
//==============================================================================
void ComponentInfo::setComponentType(const QString& aType)
{
    // Check Component Type
    if (mType != aType) {
        // Set Component Type
        mType = aType;
        // Emit Component Type Changed Signal
        emit componentTypeChanged(mType);
    }
}

//==============================================================================
// Get Component Base Name
//==============================================================================
QString ComponentInfo::componentBase()
{
    return mBaseName;
}

//==============================================================================
// Set Component Base Name
//==============================================================================
void ComponentInfo::setComponentBase(const QString& aBaseName)
{
    // Check Component Base Name
    if (mBaseName != aBaseName) {
        // Set Component Base Name
        mBaseName = aBaseName;
        // Emit Component Base Name Changed Signal
        emit componentBaseChanged(mBaseName);
    }
}

//==============================================================================
// Get Focused State
//==============================================================================
bool ComponentInfo::focused()
{
    return mFocused;
}

//==============================================================================
// Set Focused State
//==============================================================================
void ComponentInfo::setFocused(const bool& aFocused)
{
    // Check Focused State
    if (mFocused != aFocused) {
        // Set Focused State
        mFocused = aFocused;
        // Emit Focused State Changed Signal
        emit focusedChanged(mFocused);
    }
}

//==============================================================================
// Get QML Source Path
//==============================================================================
QString ComponentInfo::sourcePath()
{
    return mQMLPath;
}

//==============================================================================
// Set QML Source Path
//==============================================================================
void ComponentInfo::setSourcePath(const QString& aPath)
{
    // Check QML Path
    if (mQMLPath != aPath) {
        // Set QML Path
        mQMLPath = aPath;
        // Emit Source Path Changed Signal
        emit sourcePathChanged(mQMLPath);
    }
}

//==============================================================================
// Get Component Type Hierarchy
//==============================================================================
QStringList ComponentInfo::hierarchy()
{
    // Init Component Type Hierarchy
    QStringList cth = mBase ? mBase->hierarchy() : QStringList();

    // Append Component Type Name
    cth << mType;

    return cth;
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
    Q_UNUSED(aFilePath);

    // ...
}

//==============================================================================
// Get JSON Content/Sting
//==============================================================================
QByteArray ComponentInfo::toJSON()
{
    // Init JSON Object
    QJsonObject ciObject;

    // Set Component Name
    ciObject[JSON_KEY_COMPONENT_NAME] = QJsonValue(mName);
    // Set Component Type
    ciObject[JSON_KEY_COMPONENT_TYPE] = QJsonValue(mType);
    // Set Component Base Name
    ciObject[JSON_KEY_COMPONENT_BASE] = QJsonValue(mBaseName);

    // ...

    // Save Own Properties

    // Save Properties

    // Save Parent

    // Save Children

    // Init JSON Document
    QJsonDocument ciDocument(ciObject);

    return ciDocument.toJson();
}

//==============================================================================
// Set Up Component From JSON Content/String
//==============================================================================
void ComponentInfo::fromJSON(const QByteArray& aContent)
{
    // Init Component Info Document
    QJsonDocument ciDocument = QJsonDocument::fromJson(aContent);
    // Init JSON Object
    QJsonObject ciObject = ciDocument.object();

    // Set Component Name
    setComponentName(ciObject[JSON_KEY_COMPONENT_NAME].toString());
    // Set Component Type
    setComponentType(ciObject[JSON_KEY_COMPONENT_TYPE].toString());
    // Set Component Base Name
    setComponentBase(ciObject[JSON_KEY_COMPONENT_BASE].toString());

    // ...

    // Set Own Properties

    // Set Properties

    // Set Base
    mBase = mProject->getComponentByName(mBaseName);

    // Set Parent

    // Set Children

}

//==============================================================================
// Add Propery
//==============================================================================
void ComponentInfo::addProperty(const QString& aName, const QVariant& aValue)
{
    mOwnProperties[aName] = aValue.toJsonValue();
}

//==============================================================================
// Remove Property
//==============================================================================
void ComponentInfo::removeProperty(const QString& aName)
{
    // Get Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Property Index
    int opIndex = opKeys.indexOf(aName);
    // Check Own Property Index
    if (opIndex >= 0) {
        // Remove Value
        mProperties.remove(aName);
    }
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::property(const QString& aName)
{
    // Check Own Properties First
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        return mOwnProperties.value(aName);
    }

    return mProperties.value(aName);
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentInfo::setProperty(const QString& aName, const QVariant& aValue)
{
    // Check Own Properties
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        // Set Own Properties
        mOwnProperties[aName] = aValue.toJsonValue();
    } else {
        // Check Type
        if ((mType == COMPONENT_TYPE_COMPONENT || mType == COMPONENT_TYPE_VIEW) && mBase) {

        } else {
            qWarning() << "ComponentInfo::setProperty - aName: " << aName << " - NO PRORPERTY!";
        }
    }
}

//==============================================================================
// Add Child
//==============================================================================
void ComponentInfo::addChild(ComponentInfo* aChild)
{
    // Check Child
    if (aChild) {
        // Append Child
        mChildren << aChild;
    }
}

//==============================================================================
// Remove Child
//==============================================================================
void ComponentInfo::removeChild(ComponentInfo* aChild, const bool& aDelete)
{
    // Check Child
    if (aChild) {
        // Get Child Index
        int cIndex = mChildren.indexOf(aChild);
        // Check Child Index
        if (cIndex >= 0 && cIndex < mChildren.count()) {
            // Check Delete
            if (aDelete) {
                // Delete Child
                delete mChildren.takeAt(cIndex);
            } else {
                // Remove Child
                mChildren.removeAt(cIndex);
            }
        } else {
            qWarning() << "ComponentInfo::removeChild - aChild: " << aChild << " - CHILD COMPONENT NOT FOUND!";
        }
    }
}

//==============================================================================
// Destructor
//==============================================================================
ComponentInfo::~ComponentInfo()
{
    // Save
    save();
    // Clear
    clear();
}


