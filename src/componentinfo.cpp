#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDebug>

#include "propertiescontroller.h"
#include "designerapplication.h"
#include "mainwindow.h"
#include "componentinfo.h"
#include "projectmodel.h"
#include "qmlparser.h"
#include "qmlgenerator.h"
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
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mCategory, mProject, mBaseName, mBuiltIn, false);
    // Set Is Root
    newComponent->mIsRoot = false;

    // Imports

    // Anchors

    // Own Properties

    // Properties

    // Signals

    // Slots

    // Functions

    // Children

    // States

    // Transitions

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
                             const bool& aProtoType,
                             QObject* aParent)
    : QObject(aParent)
    , mProject(aProject)
    , mIsProtoType(aProtoType)
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
    , mProtoType(mIsProtoType ? NULL : mProject ? mProject->getComponentByName(mName, mType) : NULL)
{
    //qDebug() << "ComponentInfo " <<  mName << " created.";

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
    //qDebug() << "ComponentInfo::clear";
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
    if (!mIsProtoType) {
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
    return mIsProtoType;
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
// Built In
//==============================================================================
bool ComponentInfo::builtIn()
{
    return mBuiltIn;
}

//==============================================================================
// Set Built In
//==============================================================================
void ComponentInfo::setBuiltIn(const bool& aBuiltIn)
{
    // Check Built In
    if (mBuiltIn != aBuiltIn) {
        // Set Built In
        mBuiltIn = aBuiltIn;
        // Emit Built In Changed Signal
        emit builtInChanged(mBuiltIn);
        // Set Dirty
        setDirty(true);
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
// Get Property Keys
//==============================================================================
QStringList ComponentInfo::componentPropertyKeys()
{
    // Init Property Keys
    QStringList propertyKeys = mOwnProperties.keys();

    // Check Base
    if (mBase) {
        // Add Properties
        propertyKeys += mBase->componentPropertyKeys();
    }

    return propertyKeys;
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
    cth << mName;

    return cth;
}

//==============================================================================
// Get Child Component ID List
//==============================================================================
QStringList ComponentInfo::idList()
{
    return mIDMap.keys();
}

//==============================================================================
// Export To QML
//==============================================================================
void ComponentInfo::exportToQML(const QString& aFilePath)
{
    // Generate QML
    QMLGenerator::generateQML(this, aFilePath);
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
    // Set Built In
    ciObject[JSON_KEY_COMPONENT_BUILTIN] = QJsonValue(mBuiltIn);

    // ...

    // Check Anchors
    if (!mAnchors.isEmpty()) {
        // Set Anchors
        ciObject[JSON_KEY_COMPONENT_ANCHORS] = mAnchors;
    }

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

    // Imports
    if (!mImports.isEmpty()) {
        // Set Signals
        ciObject[JSON_KEY_COMPONENT_IMPORTS] = mImports;
    }

    // Check Signals
    if (!mSignals.isEmpty()) {
        // Set Signals
        ciObject[JSON_KEY_COMPONENT_SIGNALS] = mSignals;
    }

    // Check Slots
    if (!mSlots.isEmpty()) {
        // Set Signals
        ciObject[JSON_KEY_COMPONENT_SLOTS] = mSlots;
    }

    // Functions
    if (!mFunctions.isEmpty()) {
        // Set Signals
        ciObject[JSON_KEY_COMPONENT_FUNCTIONS] = mFunctions;
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
    // Set Built In
    setBuiltIn(aObject[JSON_KEY_COMPONENT_BUILTIN].toBool());

    // ...

    // Set Anchors
    mAnchors = aObject[JSON_KEY_COMPONENT_ANCHORS].toObject();
    // Set Own Properties
    mOwnProperties = aObject[JSON_KEY_COMPONENT_OWN_PROPERTIES].toObject();
    // Set Properties
    mProperties = aObject[JSON_KEY_COMPONENT_PROPERTIES].toObject();

    // Base Components Might Not Be Ready !!!!

    // Set Base Component
    mBase = mProject ? mProject->getComponentByName(mBaseName) : NULL;
    // Set Parent Component
    mParent = mProject ? mProject->getComponentByName(aObject[JSON_KEY_COMPONENT_PARENT].toString()) : NULL;
    // Set ProtoType Component
    mProtoType = mProject && mIsProtoType ? mProject->getComponentByName(mName, mType) : NULL;

    // Set Imports
    mImports = aObject[JSON_KEY_COMPONENT_IMPORTS].toArray();
    // Set Signals
    mSignals = aObject[JSON_KEY_COMPONENT_SIGNALS].toArray();
    // Set Slots
    mSlots = aObject[JSON_KEY_COMPONENT_SLOTS].toArray();
    // Set Functions
    mFunctions = aObject[JSON_KEY_COMPONENT_FUNCTIONS].toArray();
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
// Generate Live Code for Designer
//==============================================================================
QString ComponentInfo::generateLiveCode()
{
    qDebug() << "ComponentInfo::generateLiveCode - name: " << mName;

    // Init Live Code
    QString liveCode = "";

    // Add Imports =============================================================

    // Get Imports Count
    int iCount = mImports.count();
    // Iterate Through Imports
    for (int i=0; i<iCount; i++) {
        // Append Imports
        liveCode += QString("import %1\n").arg(mImports[i].toString());
    }

    // Add New Line
    liveCode += "\n";

    // Add Type
    liveCode += mName + " {\n";

    // Add ID ==================================================================

    // Get Component ID
    QString cID = componentProperty(JSON_KEY_COMPONENT_PROPERTY_ID).toString();

    // Check ID
    if (cID.isEmpty() && mIsRoot) {
        // Set ID
        cID = "root";
    }

    // Check ID
    if (!cID.isEmpty()) {
        // Add ID
        liveCode += QString("%1id: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cID);
    }

    // Add Object Name =========================================================

    // Get Object Name
    QString objectName = componentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME).toString();

    // Check Object Name
    if (!objectName.isEmpty()) {
        // Add Object Name
        liveCode += QString("%1objectName: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(objectName);
    }

    // Check ID & Object Name
    if (!cID.isEmpty() || !objectName.isEmpty()) {
        // Add New Line
        liveCode += "\n";
    }

    // Add Pos =================================================================

    // Get Pos X
    QString cpX = posX();
    // Check Pos X
    if (cpX != "0") {
        // Add Pos X
        liveCode += QString("%1x: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cpX);
    }

    // Get Pos Y
    QString cpY = posY();
    // Check Pos Y
    if (cpY != "0") {
        // Add Pos Y
        liveCode += QString("%1y: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cpY);
    }

    // Get Pos Z
    QString cpZ = posZ();
    // Check Pos Z
    if (cpZ != "0") {
        // Add Pos Z
        liveCode += QString("%1z: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cpZ);
    }

    // Add Size ================================================================

    // Get Width
    QString cWidth = width();
    // Check Width
    if (cWidth != "0") {
        // Add Width
        liveCode += QString("%1width: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cWidth);
    }

    // Get Height
    QString cHeight = height();
    // Check Height
    if (cHeight != "0") {
        // Add Height
        liveCode += QString("%1height: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(cHeight);
    }

    // Add Anchors =============================================================

    // Check Anchors
    if (!mAnchors.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // Get Anchors Fill Target
        QString afTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL).toString();
        // Get Anchors Center In Target
        QString acTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN).toString();
        // Get Horizontal Center Anchor Target
        QString ahcTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER).toString();
        // Get Vertical Center Anchor Target
        QString avcTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER).toString();

        // Init Horizontal Center Used Flag
        bool hCenter = false;
        // Init Vertical Center Used Flag
        bool vCenter = false;

        // Check Fill Target
        if (!afTarget.isEmpty()) {
            // Add Fill Target
            liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL).arg(afTarget);
        // Check Center In Target
        } else if (!acTarget.isEmpty()) {
            // Add Center In Target
            liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN).arg(acTarget);
            // Set Horizontal & Vertical Center Used Flag
            hCenter = true;
            vCenter = true;
        } else {
            // Check Horizontal Center Target
            if (!ahcTarget.isEmpty()) {
                // Add Horizontal Center Target
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER).arg(ahcTarget);
                // Set Horizontal Center Used Flag
                hCenter = true;
            } else {
                // Get Left Anchor Target
                QString alTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT).toString();
                // Get Right Anchor Target
                QString arTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT).toString();

                // Check Left Anchor Target
                if (!alTarget.isEmpty()) {
                    // Add Left Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT).arg(alTarget);
                }

                // Check Right Anchor Target
                if (!arTarget.isEmpty()) {
                    // Add Right Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT).arg(arTarget);
                }
            }

            // Check Vertical Center Target
            if (!avcTarget.isEmpty()) {
                // Add Vertical Center Target
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER).arg(avcTarget);
                // Set Vertical Center Used Flag
                vCenter = true;
            } else {
                // Get Top Anchor Target
                QString atTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP).toString();
                // Get Bottom Anchor Target
                QString abTarget = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM).toString();

                // Check Top Anchor Target
                if (!atTarget.isEmpty()) {
                    // Add Top Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP).arg(atTarget);
                }

                // Check Bottom Anchor Target
                if (!abTarget.isEmpty()) {
                    // Add Bottom Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM).arg(abTarget);
                }
            }
        }

        // Check Center In and Horizontal Center Target
        if (!acTarget.isEmpty() || !ahcTarget.isEmpty()) {
            // Get Horizontal Center Offset
            QString hcOffset = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS).toString();
            // Check Horizontal Center Offset
            if (!hcOffset.isEmpty()) {
                // Add Horiontal Center Offset
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS).arg(hcOffset);
                // Set Horizontal Center Used Flag
                hCenter = true;
            }
        }

        // Check Center In and Vertical Center Target
        if (!acTarget.isEmpty() || !avcTarget.isEmpty()) {
            // Get Vertical Center Offset
            QString vcOffset = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS).toString();
            // Check Vertical Center Offset
            if (!vcOffset.isEmpty()) {
                // Add Horiontal Center Offset
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS).arg(vcOffset);
                // Set Vertical Center Used Flag
                vCenter = true;
            }
        }

        // Init Single Margin Used Flag
        bool sMargin = false;

        // Check If Hoizontal CenTer Is used
        if (!hCenter) {
            // Get Left Anchor Margin
            QString alMargin = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN).toString();
            // Get Right Anchor Margin
            QString arMargin = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN).toString();

            // Check Left Margin
            if (!alMargin.isEmpty()) {
                // Add Left Margin
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN).arg(alMargin);
                // Set Single Margin Used
                sMargin = true;
            }

            // Check Right Margin
            if (!arMargin.isEmpty()) {
                // Add Right Margin
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN).arg(arMargin);
                // Set Single Margin Used
                sMargin = true;
            }
        }

        // Check If Vertical Center Used
        if (!vCenter) {
            // Get Top Anchor Margin
            QString atMargin = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN).toString();
            // Get Bottom Anchor Margin
            QString abMargin = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN).toString();

            // Check Top Margin
            if (!atMargin.isEmpty()) {
                // Add Top Margin
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN).arg(atMargin);
                // Set Single Margin Used
                sMargin = true;
            }

            // Check Bottom Margin
            if (!abMargin.isEmpty()) {
                // Add Bottom Margin
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN).arg(abMargin);
                // Set Single Margin Used
                sMargin = true;
            }
        }

        // Check Single Margin Used &  Center Flags
        if (!sMargin && !hCenter && !vCenter) {
            // Get Anchor Margins
            QString aMargins = mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS).toString();
            // Check Margins
            if (!aMargins.isEmpty()) {
                // Add Bottom Margin
                liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS).arg(aMargins);
            }
        }
    }

    // Add Own Properties ======================================================

    // Init Own Property Value Hook List
    QStringList opvHookList = QStringList();
    // Init Inherited Properties Value Hook List
    QStringList pvHookList = QStringList();

    // Get Own Properties Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Own Properties Count
    int opCount = opKeys.count();

    // Check Own Prpoerties Key Count
    if (opCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Get Filtered Property Keys
        QStringList fpKeys = mProject->propertiesController() ? mProject->propertiesController()->filteredProperties() : QStringList();

        // Iterate Through Own Properties
        for (int j=0; j<opCount; j++) {
            // Check Filtered Properties
            if (fpKeys.indexOf(opKeys[j]) == -1) {
                // Get Property Type And Value
                QStringList typeAndValue = mOwnProperties[opKeys[j]].toString().split(":");
                // Get Type
                QString pType = typeAndValue[0];
                // Get Value
                QString pValue = typeAndValue[1];
                // Check Type
                if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING && pValue.isEmpty()) {
                    // Set Value
                    pValue = "\"\"";
                }
                // Append Live Code
                liveCode += QString("%1property %2 %3: %4\n").arg(DEFAULT_SOURCE_INDENT).arg(pType).arg(opKeys[j]).arg(pValue);
                // Add Value Setting Hook
                opvHookList << QString("%1%1%1case %2: %3.%2 = value; break;\n").arg(DEFAULT_SOURCE_INDENT).arg(opKeys[j]).arg(cID);
            }
        }
    }

    // Add Inherited Properties ================================================

    // Get Properties Keys
    QStringList pKeys = mProperties.keys();
    // Get Properties Count
    int pCount = pKeys.count();

    // Check Inherited Properties Keys Count
    if (pCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Iterate Through Properties
        for (int k=0; k<pCount; k++) {
            // Get Value
            QString pValue = mProperties.value(pKeys[k]).toString();
            // Append Live Code
            liveCode += QString("%1%2: %3\n").arg(DEFAULT_SOURCE_INDENT).arg(pKeys[k]).arg(pValue);
            // Add Value Setting Hook
            pvHookList << QString("%1%1%1case %2: %3.%2 = value; break;\n").arg(DEFAULT_SOURCE_INDENT).arg(pKeys[k]).arg(cID);
        }

        // ...
    }

    // Add Signals =============================================================

    // Check Signals
    if (!mSignals.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // Get Signals Count
        int signalsCount = mSignals.count();

        // Iterate Through Signals
        for (int l=0; l<signalsCount; l++) {
            // Get Signal Object
            QJsonObject signalObject = mSignals[l].toObject();
            // Get Name
            QString signalName = signalObject.value(JSON_KEY_COMPONENT_SIGNAL_NAME).toString();
            // Get Parameters
            QString signalParams = signalObject.value(JSON_KEY_COMPONENT_SIGNAL_PARAMETERS).toString();
            // Init Signal String
            QString signalDef = QString("signal %1(").arg(signalName);

            // Check Parameters
            if (!signalParams.isEmpty()) {
                // Get Parameter List
                QStringList signalParamList = signalParams.split(",");
                // Get Parameter List Count
                int splCount = signalParamList.count();
                // Iterate Through Signal Parameter List
                for (int m=0; m<splCount; m++) {
                    // Check Index
                    if (m > 0) {
                        // Add Separator
                        signalDef += ", ";
                    }

                    // Add Parameter
                    signalDef += QString("var %1").arg(signalParamList[m]);
                }
            }

            // Add Final )
            signalDef += ")\n";

            // Append To Live Code
            liveCode += QString("%1%2\n").arg(DEFAULT_SOURCE_INDENT).arg(signalDef);
        }
    }

    // Add Slots ===============================================================

    // Check Slots
    if (!mSlots.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // Get Slots Count
        int slotsCount = mSlots.count();

        // Iterate Through Signals
        for (int n=0; n<slotsCount; n++) {
            // Get Slot Object
            QJsonObject slotObject = mSlots[n].toObject();
            // Get Slot Name
            QString slotName = slotObject.value(JSON_KEY_COMPONENT_SLOT_NAME).toString();
            // Get Source
            QString slotSource = slotObject.value(JSON_KEY_COMPONENT_SLOT_SOURCE).toString();
            // Append To Live Code
            liveCode += QString("%1%2: %3\n\n").arg(DEFAULT_SOURCE_INDENT).arg(slotName).arg(slotSource);
        }
    }

    // Add Hooks for Property Getters And Setters !!! ==============================

    // Get Own Property Value Hookss Count
    int opvhCount = opvHookList.count();
    // Get Inherited Properties Value Hook's Count
    int pvhCount = pvHookList.count();

    // Check Properties Count
    if (opvhCount > 0 || pvhCount > 0) {
        // Init Property Update Hook Function Code
        QString propertyHooks = QString("%1function __setProperty(key, value) {\n").arg(DEFAULT_SOURCE_INDENT);
        // Add Key Switch
        propertyHooks += QString("%1%1switch (key) {\n").arg(DEFAULT_SOURCE_INDENT);
        // Add Default Hook
        propertyHooks += QString("%1%1%1default: console.log(\"__setProperty property:\" + key + \" IS NOT DEFINED!\"); break;\n").arg(DEFAULT_SOURCE_INDENT);

        // Iterate Through Own Property Value Hooks
        for (int i=0; i<opvhCount; i++) {
            // Append Own Property Vlaue Hook
            propertyHooks += opvHookList[i];
        }

        // Iterate Through Inherited Property Value Hooks
        for (int j=0; j<pvhCount; j++) {
            // Append Inherited Property Value Hook
            propertyHooks += pvHookList[j];
        }

        // Add Switch Closing Bracket
        propertyHooks += QString("%1%1}\n").arg(DEFAULT_SOURCE_INDENT);
        // Add Final Bracket
        propertyHooks += QString("%1}\n").arg(DEFAULT_SOURCE_INDENT);

        // Append Property Hooks To Live Code
        liveCode += propertyHooks;

        // Add New Line
        liveCode += "\n";
    }

    // Add Functions ===========================================================

    // Check Functions
    if (!mFunctions.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    // Add Children ============================================================

    // Check Children
    if (mChildren.count() > 0) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    // Add States ==============================================================

    // Check States
    if (!mStates.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    // Add Transitions =========================================================

    // Check Transitions
    if (!mTransitions.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    //==========================================================================

    liveCode += QString("%1//...\n\n").arg(DEFAULT_SOURCE_INDENT);

    liveCode += "}\n";

    qDebug() << "ComponentInfo::generateLiveCode - liveCode: " << liveCode;

    return liveCode;
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::componentProperty(const QString& aName)
{
    // Check Own Properties First
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        return mOwnProperties.value(aName).toString().split(":")[1];
    }

    // Check Property Keys
    if (mProperties.keys().indexOf(aName) >= 0) {
        return mProperties.value(aName).toVariant();
    }

    // Check Prototype
    if (mProtoType) {
        // Get Property
        QString protoProperty = mProtoType->componentProperty(aName).toString();
        // Check Property
        if (!protoProperty.isNull()) {
            return protoProperty;
        }
    }

    // Check Base Component
    if (mBase) {
        // Get Property
        QString baseProperty = mBase->componentProperty(aName).toString();
        // Check Base Property
        if (!baseProperty.isNull()) {
            return baseProperty;
        }
    }

    qWarning() << "ComponentInfo::componentProperty - aName: " << aName << " - NO PROPERTY!";

    return QVariant();
}

//==============================================================================
// Set Property
//==============================================================================
void ComponentInfo::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // Get Property Keys
    QStringList baseProperties = mBase ? mBase->componentPropertyKeys() : QStringList();
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

        // Emit Own Property Added Signal
        emit ownPropertyAdded(mOwnProperties.keys().indexOf(aName));

    } else {
        qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - BASE";

        // Set Property
        mProperties[aName] = aValue.toString();

        // Emit Property Updated Signal
        emit propertyUpdated(aName);
    }

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Check If Has Property
//==============================================================================
bool ComponentInfo::hasProperty(const QString& aName)
{
    // Get Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Property Index
    int opIndex = opKeys.indexOf(aName);

    // Check Property Index
    if (opIndex >= 0) {
        return true;
    }

    // Check Prototype
    if (mProtoType && mProtoType->hasProperty(aName)) {
        return true;
    }

    // Check Base Component
    if (mBase && mBase->hasProperty(aName)) {
        return true;
    }

    return false;
}

//==============================================================================
// Add Child
//==============================================================================
void ComponentInfo::addChild(ComponentInfo* aChild)
{
    // Check Child
    if (aChild) {
        // Set Parent Component
        aChild->mParent = this;
        // Append Child
        mChildren << aChild;
        // Set Dirty
        setDirty(true);
        // Emit Child Count Changed Signal
        emit childCountChanged(mChildren.count());
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

            // Set Dirty
            setDirty(true);
            // Emit Child Count Changed Signal
            emit childCountChanged(mChildren.count());

        } else {
            qWarning() << "ComponentInfo::removeChild - aChild: " << aChild << " - CHILD COMPONENT NOT FOUND!";
        }
    }
}

//==============================================================================
// Get Child Count
//==============================================================================
int ComponentInfo::childCount()
{
    return mChildren.count();
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

    qDebug() << "ComponentInfo " << mName << " deleted.";
}


