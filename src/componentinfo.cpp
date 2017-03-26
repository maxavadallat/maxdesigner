#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QFileInfo>
#include <QDir>
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
    ComponentInfo* newComponent = new ComponentInfo("", "", "", aProject);
    // Load Component
    newComponent->load(aFilePath);

    return newComponent;
}

//==============================================================================
// Clone Component Info
//==============================================================================
ComponentInfo* ComponentInfo::clone()
{
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mCategory, mProject, mBaseName);
    // Set ProtoType
    newComponent->mProtoType = false;
    // Set Is Root
    newComponent->mIsRoot = false;
    // Set Dirty
    //newComponent->mDirty = false;

    // ...

    return newComponent;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentInfo::ComponentInfo(const QString& aName,
                             const QString& aType,
                             const QString& aCategory,
                             ProjectModel* aProject,
                             const QString& aBaseName,
                             const bool& aBuiltIn,
                             QObject* aParent)
    : QObject(aParent)
    , mProject(aProject)
    , mProtoType(true)
    , mDirty(true)
    , mBuiltIn(aBuiltIn)
    , mInfoPath("")
    , mQMLPath("")
    , mName(aName)
    , mType(aType)
    , mCategory(aCategory)
    , mBaseName(aBaseName)
    , mFocused(false)
    , mIsRoot(true)
    , mBase(mProject ? mProject->getComponentByName(mBaseName) : NULL)
    , mParent(NULL)
{
    qDebug() << "ComponentInfo created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentInfo::init()
{
    // Check Project
    if (mProject) {
        // Init info Path
        QString ipTemp = "";
        // Check Type
        if (mType == COMPONENT_TYPE_BASECOMPONENT) {
            // Set Info Path
            ipTemp = mProject->baseComponentsDir();
        } else if (mType == COMPONENT_TYPE_COMPONENT) {
            // Set Info Path
            ipTemp = mProject->componentsDir();
        } else if (mType == COMPONENT_TYPE_VIEW) {
            // Set Info Path
            ipTemp = mProject->viewsDir();
        } else if (mType != "") {
            qWarning() << "ComponentInfo::init - mType: " << mType << " - NOT SUPPORTED TYPE!!";

            return;
        }

        // Check Component Name
        if (mName.isEmpty()) {
            return;
        }

        // Set Info Path
        setInfoPath(QString("%1/%2.%3").arg(ipTemp).arg(mName).arg(DEFAULT_JSON_SUFFIX));

        qDebug() << "ComponentInfo::init - mInfoPath: " << mInfoPath;

    } else {
        qWarning() << "ComponentInfo::init - NO PROJECT!!";
    }

    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentInfo::clear()
{
    qDebug() << "ComponentInfo::clear";
    // Clear ID Map
    clearIDMap();
    // Clear Children
    clearChildren();
}

//==============================================================================
// Clear Children
//==============================================================================
void ComponentInfo::clearChildren()
{
    // Iterate Through Children
    while (mChildren.count() > 0) {
        // Delete Last
        delete mChildren.takeLast();
    }
}

//==============================================================================
// Clear ID Map
//==============================================================================
void ComponentInfo::clearIDMap()
{
    // Clear ID Map
    mIDMap.clear();
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
        setInfoPath(aFilePath);
    }

    // Init Component Info File
    QFile ciFile(mInfoPath);

    qDebug() << "ComponentInfo::load - fileName: " << ciFile.fileName();

    // Open File
    if (ciFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read File Content
        QString ciFileContent = ciFile.readAll();
        //qDebug() << "ComponentInfo::load - ciFileContent: " << ciFileContent;
        // Close File
        ciFile.close();
        // From JSON
        fromJSON(ciFileContent.toUtf8());
        // Set Dirty State
        setDirty(false);
    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }
}

//==============================================================================
// Save
//==============================================================================
void ComponentInfo::save(const QString& aFilePath)
{
    // Check If Prototype
    if (!mProtoType) {
        // Saving Only Prototypes...
        return;
    }

    // Check File Path
    if (aFilePath.isEmpty() && !mDirty) {
        // No Need to Save
        return;
    }

    // Init File Info
    QFileInfo fileInfo(aFilePath.isEmpty() ? mInfoPath : aFilePath);
    // Init File Info Dir
    QDir fileInfoDir(fileInfo.absolutePath());
    // Check If Dir Exists
    if (!fileInfoDir.exists()) {
        // Try to Create Path
        if (!fileInfoDir.mkpath(fileInfoDir.absolutePath())) {
            qWarning() << "ComponentInfo::save - ERROR CREATING COMPONENT DIR!!";
            return;
        }
    }

    // Init Component Info File
    QFile ciFile(fileInfo.absoluteFilePath());

    qDebug() << "ComponentInfo::save - fileName: " << ciFile.fileName();

    // Open File
    if (ciFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream textStream(&ciFile);
        // Write To Text Stream
        textStream << toJSONContent();
        // Flush Text Stream
        textStream.flush();
        // Close File
        ciFile.close();
        // Reset Dirty
        setDirty(false);

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
// Get Component Category
//==============================================================================
QString ComponentInfo::componentCategory()
{
    return mCategory;
}

//==============================================================================
// Set Component Category
//==============================================================================
void ComponentInfo::setComponentCategory(const QString& aCategory)
{
    // Check Category
    if (mCategory != aCategory) {
        // Set Category
        mCategory = aCategory;
        // Emit Component category Changed Signal
        emit componentCategoryChanged(mCategory);
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
// Get Component Parent
//==============================================================================
ComponentInfo* ComponentInfo::componentParent()
{
    return mParent;
}

//==============================================================================
// Set Component Parent
//==============================================================================
void ComponentInfo::setComponentParent(ComponentInfo* aParent)
{
    // Check Parent
    if (mParent != aParent) {
        // Set Parent
        mParent = aParent;
        // Emit Parent Changed Signal
        emit componentParentChanged(mParent);
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
// Get Is Root
//==============================================================================
bool ComponentInfo::isRoot()
{
    return mIsRoot;
}

//==============================================================================
// Set Is Root
//==============================================================================
void ComponentInfo::setIsRoot(const bool& aRoot)
{
    // Check Is Root
    if (mIsRoot != aRoot) {
        // Set Is Root
        mIsRoot = aRoot;
        // Emit Is Root Changed Signal
        emit isRootChanged(mIsRoot);
    }
}

//==============================================================================
// Get Component Info Path
//==============================================================================
QString ComponentInfo::infoPath()
{
    return mInfoPath;
}

//==============================================================================
// Set Info Path
//==============================================================================
void ComponentInfo::setInfoPath(const QString& aInfoPath)
{
    // Check Info Path
    if (mInfoPath != aInfoPath) {
        // Set Info Path
        mInfoPath = aInfoPath;
        // Emit Info Path Changed Signal
        emit infoPathChanged(mInfoPath);
        // Set Dirty
        setDirty(true);
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
// Get Component ID
//==============================================================================
QString ComponentInfo::componentID()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_ID).toString();
}

//==============================================================================
// Set Component ID
//==============================================================================
void ComponentInfo::setComponentID(const QString& aID)
{
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_ID, aID);
    // Emit Component ID Changed Signal
    emit componentIDChanged(componentID());
}

//==============================================================================
// Get Object Name
//==============================================================================
QString ComponentInfo::componentObjectName()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME).toString();
}

//==============================================================================
// Set Object Name
//==============================================================================
void ComponentInfo::setComponentObjectName(const QString& aObjectName)
{
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME, aObjectName);
    // Emit Object Name Changed Signal
    emit componentObjectNameChanged(componentObjectName());
}

//==============================================================================
// Get Pos X
//==============================================================================
QString ComponentInfo::posX()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_X).toString();
}

//==============================================================================
// Set Pos X
//==============================================================================
void ComponentInfo::setPosX(const QString& aPosX)
{
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_X, aPosX);
    // Emit Pos X Changed Signal
    emit posXChanged(posX());
}

//==============================================================================
// Get Pos Y
//==============================================================================
QString ComponentInfo::posY()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_Y).toString();
}

//==============================================================================
// Set Pos Y
//==============================================================================
void ComponentInfo::setPosY(const QString& aPosY)
{
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_Y, aPosY);
    // Emit Pos Y Changed Signal
    emit posYChanged(posY());
}

//==============================================================================
// Get Pos Z
//==============================================================================
QString ComponentInfo::posZ()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_Z).toString();
}

//==============================================================================
// Set Pos Z
//==============================================================================
void ComponentInfo::setPosZ(const QString& aPosZ)
{
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_Z, aPosZ);
    // Emit Pos Z Changed Signal
    emit posZChanged(posZ());
}

//==============================================================================
// Get Width
//==============================================================================
QString ComponentInfo::width()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH).toString();
}

//==============================================================================
// Set Width
//==============================================================================
void ComponentInfo::setWidth(const QString& aWidth)
{
    // Set Property - Width
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH, aWidth);
    // Emit Width Changed Signal
    emit widthChanged(width());
}

//==============================================================================
// Get Height
//==============================================================================
QString ComponentInfo::height()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT).toString();
}

//==============================================================================
// Set Height
//==============================================================================
void ComponentInfo::setHeight(const QString& aHeight)
{
    // Set Property - Height
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT, aHeight);
    // Emit Height Changed Signal
    emit heightChanged(height());
}

//==============================================================================
// Get Properties
//==============================================================================
QStringList ComponentInfo::componentProperties()
{
    // Init Property Keys
    QStringList propertyKeys = mOwnProperties.keys();

    // Check Base
    if (mBase) {
        // Add Properties
        propertyKeys += mBase->componentProperties();
    }

    return propertyKeys;
}

//==============================================================================
// Get Dynamic Properties
//==============================================================================
QList<QByteArray> ComponentInfo::dynamicProperties()
{
    return dynamicPropertyNames();
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentInfo::setDirty(const bool& aDirty)
{
    // Check Dirty
    if (mDirty != aDirty) {
        // Set Dirty
        mDirty = aDirty;
    }
}

//==============================================================================
// Base Components Dir Changed Slot
//==============================================================================
void ComponentInfo::baseComponentsDirChanged(const QString& aBaseComponentsDir)
{
    // Check Type
    if (mType == COMPONENT_TYPE_BASECOMPONENT) {
        // Set Info Path
        setInfoPath(QString("%1/%2.%3").arg(aBaseComponentsDir).arg(mName).arg(DEFAULT_JSON_SUFFIX));
    }
}

//==============================================================================
// Components Dir Changed Slot
//==============================================================================
void ComponentInfo::componentsDirChanged(const QString& aComponentsDir)
{
    // Check Type
    if (mType == COMPONENT_TYPE_COMPONENT) {
        // Set Info Path
        setInfoPath(QString("%1/%2.%3").arg(aComponentsDir).arg(mName).arg(DEFAULT_JSON_SUFFIX));
    }
}

//==============================================================================
// Views Dir Changed Slot
//==============================================================================
void ComponentInfo::viewsDirChanged(const QString& aViewsDir)
{
    // Check Type
    if (mType == COMPONENT_TYPE_VIEW) {
        // Set Info Path
        setInfoPath(QString("%1/%2.%3").arg(aViewsDir).arg(mName).arg(DEFAULT_JSON_SUFFIX));
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
// Get JSON Object
//==============================================================================
QJsonObject ComponentInfo::toJSONObject()
{
    // Init JSON Object
    QJsonObject ciObject;

    // Set Component Name
    ciObject[JSON_KEY_COMPONENT_NAME] = QJsonValue(mName);
    // Set Component Type
    ciObject[JSON_KEY_COMPONENT_TYPE] = QJsonValue(mType);
    // Set Category
    ciObject[JSON_KEY_COMPONENT_CATEGORY] = QJsonValue(mCategory);
    // Set Component Base Name
    ciObject[JSON_KEY_COMPONENT_BASE] = QJsonValue(mBaseName);

    // ...

    // Check Own Properties
    if (!mOwnProperties.isEmpty()) {
        // Set Own Properties
        ciObject[JSON_KEY_COMPONENT_OWN_PROPERTIES] = mOwnProperties;
    }

    // Check Properties
    if (!mProperties.isEmpty()) {
        // Set Properties
        ciObject[JSON_KEY_COMPONENT_PROPERTIES] = mProperties;
    }

    // Check Parent Component
    if (mParent) {
        // Save Parent
        ciObject[JSON_KEY_COMPONENT_PARENT] = mParent->componentName();
    }

    // Check Signals
    if (!mSignals.isEmpty()) {
        // Set Signals
        ciObject[JSON_KEY_COMPONENT_SIGNALS] = mSignals;
    }

    // Check States
    if (!mStates.isEmpty()) {
        // Set States
        ciObject[JSON_KEY_COMPONENT_STATES] = mStates;
    }

    // Check Transitions
    if (!mTransitions.isEmpty()) {
        // Set Transitions
        ciObject[JSON_KEY_COMPONENT_TRANSITIONS] = mTransitions;
    }

    // Get Children Count
    int cCount = mChildren.count();

    // Check Children
    if (cCount > 0) {
        // Init Children Array
        QJsonArray cArray;

        // Iterate Through Children Array
        for (int i=0; i<cCount; i++) {
            // Append Child
            cArray << mChildren[i]->toJSONObject();
        }

        // Save Children
        ciObject[JSON_KEY_COMPONENT_CHILDREN] = cArray;
    }

    // ...

    return ciObject;
}

//==============================================================================
// Get JSON Content/Sting
//==============================================================================
QByteArray ComponentInfo::toJSONContent()
{
    // Init JSON Document
    QJsonDocument ciDocument(toJSONObject());

    return ciDocument.toJson();
}

//==============================================================================
// Set Up From JSON Object
//==============================================================================
void ComponentInfo::fromJSONObject(const QJsonObject& aObject)
{
    // Set Component Name
    setComponentName(aObject[JSON_KEY_COMPONENT_NAME].toString());
    // Set Component Type
    setComponentType(aObject[JSON_KEY_COMPONENT_TYPE].toString());
    // Set Component Category
    setComponentCategory(aObject[JSON_KEY_COMPONENT_CATEGORY].toString());
    // Set Component Base Name
    setComponentBase(aObject[JSON_KEY_COMPONENT_BASE].toString());

    // ...

    // Set Own Properties
    mOwnProperties = aObject[JSON_KEY_COMPONENT_OWN_PROPERTIES].toObject();
    // Set Properties
    mProperties = aObject[JSON_KEY_COMPONENT_PROPERTIES].toObject();

    // Base Components Might Not Be Ready !!!!
    // Set Base Component
    mBase = mProject ? mProject->getComponentByName(mBaseName) : NULL;
    // Set Parent Component
    mParent = mProject ? mProject->getComponentByName(aObject[JSON_KEY_COMPONENT_PARENT].toString()) : NULL;

    // Set Signals
    mSignals = aObject[JSON_KEY_COMPONENT_SIGNALS].toArray();
    // States
    mStates = aObject[JSON_KEY_COMPONENT_STATES].toArray();
    // Transitions
    mTransitions = aObject[JSON_KEY_COMPONENT_TRANSITIONS].toArray();

    // Set Children
    QJsonArray childrenArray = aObject[JSON_KEY_COMPONENT_CHILDREN].toArray();
    // Get Children Array Count
    int caCount = childrenArray.count();
    // Iterate Through Children Array
    for (int i=0; i<caCount; i++) {
        // Get Array Item
        QJsonObject childObject = childrenArray[i].toObject();
        // Get Child Component Name
        QString ccName = childObject[JSON_KEY_COMPONENT_NAME].toString();
        // Get Compoennt ProtoType
        ComponentInfo* componentProtoType = mProject ? mProject->getComponentByName(ccName) : NULL;
        // Check Child Component
        if (componentProtoType) {
            // Clone Component
            ComponentInfo* childComponent = componentProtoType->clone();
            // Set Up Child Component
            childComponent->fromJSONObject(childObject);
            // Add To Children
            mChildren << childComponent;
        } else {
            qWarning() << "ComponentInfo::fromJSON - ccName: " << ccName << " - NO COMPONENT!!";
        }
    }
}

//==============================================================================
// Set Up Component From JSON Content/String
//==============================================================================
void ComponentInfo::fromJSON(const QByteArray& aContent)
{
    // Init Parser Error
    QJsonParseError parserError;
    // Init Component Info Document
    QJsonDocument ciDocument = QJsonDocument::fromJson(aContent, &parserError);

    // Check Document
    if (ciDocument.isEmpty() || ciDocument.isNull() || parserError.error != QJsonParseError::NoError) {
        qCritical() << "ComponentInfo::fromJSON - INVALID OBJECT! - parserError: " << parserError.errorString();
    }

    // Init JSON Object
    QJsonObject ciObject = ciDocument.object();

    // From JSON Object
    fromJSONObject(ciObject);
}

//==============================================================================
// Request Close
//==============================================================================
void ComponentInfo::requestClose()
{
    // Check If Is Root
    if (mIsRoot) {
        // Emit Request Container Close
        emit requestContainerClose();
    }
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::componentProperty(const QString& aName)
{
    // Check Own Properties First
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        return mOwnProperties[aName].toString().split(":")[1];
    }

    // Check Property Keys
    if (mProperties.keys().indexOf(aName) >= 0) {
        return mProperties[aName].toVariant();
    }

    qWarning() << "ComponentInfo::componentProperty - aName: " << aName << " - NO PROPERTY!";

    return QVariant();
}

//==============================================================================
// Add Own Property
//==============================================================================
void ComponentInfo::addComponentOwnProperty(const QString& aName, const EPropertyType& aType, const QVariant& aDefault)
{
    // Switch Type
    switch (aType) {
        default:
        case EPropertyType::EPTString:          mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING).arg(aDefault.toString()); break;
        case EPropertyType::EPTBool:            mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL).arg(aDefault.toString()); break;
        case EPropertyType::EPTInt:             mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_INT).arg(aDefault.toString()); break;
        case EPropertyType::EPTDouble:          mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE).arg(aDefault.toString()); break;
        case EPropertyType::EPTReal:            mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL).arg(aDefault.toString()); break;
        case EPropertyType::EPTVar:             mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR).arg(aDefault.toString()); break;
        case EPropertyType::EPTQtObject:        mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT).arg(aDefault.toString()); break;
        case EPropertyType::EPTQtObjectList:    mOwnProperties[aName] = QString("%1:%2").arg(JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST).arg(aDefault.toString()); break;
        break;
    }
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentInfo::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    // Get Property Keys
    QStringList baseProperties = mBase ? mBase->componentProperties() : QStringList();
    // Get Base Key Index
    int bpkIndex = baseProperties.indexOf(aName);

    // Check Base Key Index
    if (bpkIndex < 0) {
        qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - OWN";

        // Init Type Prefix
        QString tPrefix = mOwnProperties[aName].toString().split(":")[0];

        // Check Prefix
        if (tPrefix.isEmpty()) {
            // Switch Type
            switch (aValue.type()) {
                default:
                case QVariant::String:  tPrefix = JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING;   break;
                case QVariant::Bool:    tPrefix = JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL;     break;
                case QVariant::UInt:
                case QVariant::Int:     tPrefix = JSON_VALUE_PROPERTY_TYPE_PREFIX_INT;      break;
                case QVariant::Double:  tPrefix = JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE;   break;
                break;
            }
        }

        // Set Own Property
        mOwnProperties[aName] = QString("%1:%2").arg(tPrefix).arg(aValue.toString());

    } else {
        qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - BASE";

        // Set Property
        //mProperties[aName] = aValue.type() == QVariant::Int ? aValue.toString() : aValue.toJsonValue();
        mProperties[aName] = aValue.toString();
    }

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Remove Property
//==============================================================================
void ComponentInfo::removeProperty(const QString& aName)
{
    qDebug() << "ComponentInfo::removeProperty - aName: " << aName;

    // Get Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Property Index
    int opIndex = opKeys.indexOf(aName);
    // Check Own Property Index
    if (opIndex >= 0) {
        // Remove Value
        mOwnProperties.remove(aName);
    } else {
        // Remove Value
        mProperties.remove((aName));
    }

    // Set Dirty
    setDirty(true);
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
        // Set Dirty
        setDirty(true);
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

        // Set Dirty
        setDirty(true);
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

    qDebug() << "ComponentInfo deleted.";
}


