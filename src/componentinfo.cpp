#include <QApplication>
#include <QQmlEngine>
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
#include "constants.h"
#include "utils.h"

//==============================================================================
// Create Component From Component Info File
//==============================================================================
ComponentInfo* ComponentInfo::fromInfoFile(const QString& aFilePath, ProjectModel* aProject, const bool aCreateChildren)
{
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo("", "", "", aProject);
    // Load Component
    if (newComponent->load(aFilePath, aCreateChildren)) {
        return newComponent;
    }

    qWarning() << "ComponentInfo::fromInfoFile - aFilePath: " << aFilePath << " - UNABLE TO LOAD COMPONENT!!";

    // Reset ProtoType & Dirty  Flag to Avoid Saving At Delete
    newComponent->mIsProtoType = false;
    newComponent->mDirty = false;

    delete newComponent;

    return NULL;
}

//==============================================================================
// Clone Component Info
//==============================================================================
ComponentInfo* ComponentInfo::clone()
{
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mCategory, mProject, mBaseName, mBuiltIn, false);
    // Set Proto Type
    newComponent->setProtoType(this);
    // Set Is Root
    newComponent->mIsRoot = false;

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
    , mLocked(false)
    , mInfoPath("")
    , mQMLPath("")
    , mName(aName)
    , mType(aType)
    , mTag("")
    , mCategory(aCategory)
    , mBaseName(aBaseName)
    , mImplicitPosX(false)
    , mImplicitPosY(false)
    , mImplicitWidth(false)
    , mImplicitHeight(false)
    , mFocused(false)
    , mLayerVisible(true)
    , mIsRoot(true)
    , mGroupped(false)
    , mContainer(NULL)
    , mBase(NULL)
    , mParent(NULL)
    , mProtoType(NULL)
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
    // Set Ownership
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    // Check Project
    if (mProject) {
        // Set Base Component
        setBaseComponent(mProject->getComponentByName(mBaseName));

        // Check If ProtoType
        if (!mProtoType && !mIsProtoType) {
            // Set Component ProtoType
            setProtoType(mProject->getComponentByName(mName, mType));
        }

    } else {
        qWarning() << "ComponentInfo::init - NO PROJECT!!";
    }

    // Init Info Path
    initInfoPath();

    //qDebug() << "ComponentInfo::init - mInfoPath: " << mInfoPath;

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
// Init Info Path
//==============================================================================
bool ComponentInfo::initInfoPath()
{
    // Check Component Name
    if (mName.isEmpty()) {
        //qWarning() << "ComponentInfo::initInfoPath - NO NAME!";
        return false;
    }

    // Check Project
    if (!mProject) {
        qWarning() << "ComponentInfo::initInfoPath - NO PROJECT!";
        return false;
    }

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
    } else if (mType == COMPONENT_TYPE_DATASOURCE) {
        // Set Info Path
        ipTemp = mProject->dataSourcesDir();
    } else if (mType != "") {
        qWarning() << "ComponentInfo::initInfoPath - mType: " << mType << " - NOT SUPPORTED TYPE!!";

        return false;
    }

    // Set Info Path
    setInfoPath(QString("%1/%2.%3").arg(ipTemp).arg(mName).arg(DEFAULT_JSON_SUFFIX));

    return true;
}

//==============================================================================
// Load
//==============================================================================
bool ComponentInfo::load(const QString& aFilePath, const bool aCreateChildren)
{
    // Check File Path
    if (aFilePath.isEmpty()) {
        return false;
    }

    // Set Info Path
    //setInfoPath(aFilePath);

    // Init Component Info File
    QFile ciFile(aFilePath);

    //qDebug() << "ComponentInfo::load - fileName: " << ciFile.fileName();

    // Open File
    if (ciFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read File Content
        QString ciFileContent = ciFile.readAll();
        //qDebug() << "ComponentInfo::load - ciFileContent: " << ciFileContent;
        // Close File
        ciFile.close();
        // From JSON
        fromJSON(ciFileContent.toUtf8(), aCreateChildren);
        // Set Dirty State
        setDirty(false);

        return true;

    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }

    return false;
}

//==============================================================================
// Save
//==============================================================================
bool ComponentInfo::save(const QString& aFilePath)
{
    // Check If Prototype
    if (!mIsProtoType) {
        // Saving Only Prototypes...
        return false;
    }

    // Check File Path
    if (aFilePath.isEmpty() && !mDirty) {
        // No Need to Save
        return false;
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
            return false;
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

        return true;
    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }

    return false;
}

//==============================================================================
// Get Prototype
//==============================================================================
bool ComponentInfo::protoType()
{
    return mIsProtoType;
}

//==============================================================================
// Get Dirty
//==============================================================================
bool ComponentInfo::getDirty()
{
    return mDirty;
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
// Component Tag
//==============================================================================
QString ComponentInfo::componentTag()
{
    return mTag;
}

//==============================================================================
// Set Component Tag
//==============================================================================
void ComponentInfo::setComponentTag(const QString& aTag)
{
    // Check Component Tag
    if (mTag != aTag) {
        // Set Component Tag
        mTag = aTag;
        // Emit Compoennt Tag Changed Signal
        emit componentTagChanged(mTag);
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
// Get Component Path
//==============================================================================
QString ComponentInfo::componentPath()
{
    // Check Parent
    if (mParent) {
        return QString("%1.%2").arg(mParent->componentPath()).arg(mName);
    }

    return mName;
}

//==============================================================================
// Get QML Container
//==============================================================================
QObject* ComponentInfo::componentContainer()
{
    return mContainer;
}

//==============================================================================
// Set QML Container
//==============================================================================
void ComponentInfo::setComponentContainer(QObject* aContainer)
{
    // Check Container
    if (mContainer != aContainer) {
        //qDebug() << "ComponentInfo::setComponentContainer - aContainer: " << aContainer;
        // Set QML Container
        mContainer = aContainer;
        // Emit QML Container Changed Signal
        emit componentContainerChanged(mContainer);
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
    // Check Component ID
    if (componentID() != aID) {
        // Set Component Property
        setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_ID, aID);
        // Set Child Object ID
        setChildObjectID(this, aID);
        // Emit Component ID Changed Signal
        emit componentIDChanged(componentID());
    }
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
    // Check Object Name
    if (componentObjectName() != aObjectName) {
        // Set Component Property
        setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME, aObjectName);

        // Emit Object Name Changed Signal
        emit componentObjectNameChanged(componentObjectName());
    }
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
// Get Use Implicit Pos X
//==============================================================================
bool ComponentInfo::useIPosX()
{
    return mImplicitPosX;
}

//==============================================================================
// Set Use Implicit Pos X
//==============================================================================
void ComponentInfo::setUseIPosX(const bool& aUseIPosX)
{
    // Check Use Implicit Pos X
    if (mImplicitPosX != aUseIPosX) {
        // Set Use Implicit Pos X
        mImplicitPosX = aUseIPosX;
        // Emit Use Implicit Pos X Changed Signal
        emit useIPosXChanged(mImplicitPosX);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Use Implicit Pos Y
//==============================================================================
bool ComponentInfo::useIPosY()
{
    return mImplicitPosY;
}

//==============================================================================
// Set Use Implicit Pos Y
//==============================================================================
void ComponentInfo::setUseIPosY(const bool& aUseIPosY)
{
    // Check Use Implicit Pos Y
    if (mImplicitPosY != aUseIPosY) {
        // Set Use Implicit Pos Y
        mImplicitPosY = aUseIPosY;
        // Emit Use Implicit Pos Y Changed Signal
        emit useIPosYChanged(mImplicitPosY);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Use Implicit Width
//==============================================================================
bool ComponentInfo::useIWidth()
{
    return mImplicitWidth;
}

//==============================================================================
// Set Use Implicit Width
//==============================================================================
void ComponentInfo::setUseIWidth(const bool& aUseIWidth)
{
    // Check Use Implicit Width
    if (mImplicitWidth != aUseIWidth) {
        // Set Use Implicit Width
        mImplicitWidth = aUseIWidth;
        // Emit Use Implicit Width Changed Signal
        emit useIWidthChanged(mImplicitWidth);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Get Use Implicit Height
//==============================================================================
bool ComponentInfo::useIHeight()
{
    return mImplicitHeight;
}

//==============================================================================
// Set Use Implicit Height
//==============================================================================
void ComponentInfo::setUseIHeight(const bool& aUseIHeight)
{
    // Check Use Implicit Height
    if (mImplicitHeight != aUseIHeight) {
        // Set Use Implicit Height
        mImplicitHeight = aUseIHeight;
        // Emit Use Implicit Height Changed Signal
        emit useIHeightChanged(mImplicitHeight);
        // Set Dirty
        setDirty(true);
    }
}

//==============================================================================
// Left Anchor Target
//==============================================================================
QString ComponentInfo::anchorsLeft()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT).toString();
}

//==============================================================================
// Right Anchor Target
//==============================================================================
QString ComponentInfo::anchorsRight()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT).toString();
}

//==============================================================================
// Top Anchor Target
//==============================================================================
QString ComponentInfo::anchorsTop()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP).toString();
}

//==============================================================================
// Bottom Anchor Target
//==============================================================================
QString ComponentInfo::anchorsBottom()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM).toString();
}

//==============================================================================
// Fill Target
//==============================================================================
QString ComponentInfo::anchorsFill()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL).toString();
}

//==============================================================================
// CenterIn Target
//==============================================================================
QString ComponentInfo::anchorsCenterIn()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN).toString();
}

//==============================================================================
// Horizontal Center Target
//==============================================================================
QString ComponentInfo::horizontalCenter()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER).toString();
}

//==============================================================================
// Vertical Center Target
//==============================================================================
QString ComponentInfo::verticalCenter()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER).toString();
}

//==============================================================================
// Margins
//==============================================================================
QString ComponentInfo::anchorsMargins()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS).toString();
}

//==============================================================================
// Left Margin
//==============================================================================
QString ComponentInfo::anchorsLeftMargin()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN).toString();
}

//==============================================================================
// Right Margin
//==============================================================================
QString ComponentInfo::anchorsRightMargin()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN).toString();
}

//==============================================================================
// Top Margin
//==============================================================================
QString ComponentInfo::anchorsTopMargin()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN).toString();
}

//==============================================================================
// Bottom Margin
//==============================================================================
QString ComponentInfo::anchorsBottomMargin()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN).toString();
}

//==============================================================================
// Horizontal Center Offset
//==============================================================================
QString ComponentInfo::anchorsHorizontalOffset()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS).toString();
}

//==============================================================================
// Vertical Center Offset
//==============================================================================
QString ComponentInfo::anchorsVerticalOffset()
{
    return mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS).toString();
}

//==============================================================================
// Get Layer Visible
//==============================================================================
bool ComponentInfo::layerVisible()
{
    return mLayerVisible;
}

//==============================================================================
// Set Layer Visible
//==============================================================================
void ComponentInfo::setLayerVisible(const bool& aLayerVisible)
{
    // Check Layer Visible
    if (mLayerVisible != aLayerVisible) {
        // Set Layer Visible
        mLayerVisible = aLayerVisible;
        // Emit Layer Visible Changed Signal
        emit layerVisibleChanged(mLayerVisible);
    }
}

//==============================================================================
// Get Property Keys
//==============================================================================
QStringList ComponentInfo::componentOwnPropertyKeys()
{
    // Init Property Keys
    QStringList propertyKeys = mOwnProperties.keys();

    // Check Proto Typw For Child Components
    if (mProtoType) {
        // Add Property Keys
        propertyKeys += mProtoType->componentOwnPropertyKeys();
    }

    //qDebug() << "ComponentInfo::componentPropertyKeys - mName: " << mName << " - propertyKeys: " << propertyKeys;

    // Remove Duplicates
    propertyKeys.removeDuplicates();

    return propertyKeys;
}

//==============================================================================
// Get All Inherited Property Keys
//==============================================================================
QStringList ComponentInfo::inheritedPropertyKeys()
{
    // Init Property Keys
    QStringList propertyKeys = mProperties.keys();

    // Check Bse Name
    if (!mBaseName.isEmpty() && !mBase && mProject) {
        // Set Base Component
        setBaseComponent(mProject ? mProject->getComponentByName(mBaseName, "", true) : NULL);
    }

    // Check Base
    if (mBase) {
        // Add Properties
        propertyKeys += mBase->componentOwnPropertyKeys();
    }

    // Remove Duplicates
    propertyKeys.removeDuplicates();

    return propertyKeys;
}

//==============================================================================
// Set Dirty State
//==============================================================================
void ComponentInfo::setDirty(const bool& aDirty)
{
    // Check Dirty
    if (mDirty != aDirty) {
        //qDebug() << "ComponentInfo::setDirty - path: " << componentPath() << " - aDirty: " << aDirty;

        // Set Dirty
        mDirty = aDirty;

        // Emit Dirty Changed Signal
        emit dirtyChanged(mDirty);

        // Check Parent
        if (mParent && mDirty) {
            // Set Dirty
            mParent->setDirty(true);
        }
    }
}

//==============================================================================
// Set Proto Type
//==============================================================================
void ComponentInfo::setProtoType(ComponentInfo* aProtoType)
{
    // Check If ProotType
    if (!mIsProtoType) {
        // Check ProtoType Component
        if (mProtoType != aProtoType) {
            //qDebug() << "ComponentInfo::setProtoType - mName: " << mName << " - aProtoType: " << (aProtoType ? aProtoType->mName : "NULL");

            // Check ProtoType
            if (mProtoType) {
                // Disconnect Component Property Changed Signal
                disconnect(mProtoType, SIGNAL(componentPropertyChanged(QString,QVariant)), this, SLOT(handleBasePropertyChanges(QString,QVariant)));
            }

            // Set Component ProtoType
            mProtoType = aProtoType;

            // Check ProtoType
            if (mProtoType) {
                // Connect Property Updated Signal
                connect(mProtoType, SIGNAL(componentPropertyChanged(QString,QVariant)), this, SLOT(handleBasePropertyChanges(QString,QVariant)));
            }

            // ...
        }
    }
}

//==============================================================================
// Set Base Component
//==============================================================================
void ComponentInfo::setBaseComponent(ComponentInfo* aBase)
{
    // Check Base Component
    if (mBase != aBase) {
        //qDebug() << "ComponentInfo::setBaseComponent - mName: " << mName << " - aBase: " << (aBase ? aBase->mName : "NULL");

        // Check Base
        if (mBase) {
            // Disconnect Component Property Changed Signal
            disconnect(mBase, SIGNAL(componentPropertyChanged(QString,QVariant)), this, SLOT(handleBasePropertyChanges(QString,QVariant)));
        }

        // Set Base Component
        mBase = aBase;

        // Check Base
        if (mBase) {
            // Connect Component Property Changed Signal
            connect(mBase, SIGNAL(componentPropertyChanged(QString,QVariant)), this, SLOT(handleBasePropertyChanges(QString,QVariant)));
        }

        // ...
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
// Data Sources Dir Changed Slot
//==============================================================================
void ComponentInfo::dataSourcesDirChanged(const QString& aDataSourcesDir)
{
    // Check Type
    if (mType == COMPONENT_TYPE_DATASOURCE) {
        // Set Info Path
        setInfoPath(QString("%1/%2.%3").arg(aDataSourcesDir).arg(mName).arg(DEFAULT_JSON_SUFFIX));
    }
}

//==============================================================================
// Handle Base Property Changes
//==============================================================================
void ComponentInfo::handleBasePropertyChanges(const QString& aName, const QVariant& aValue)
{
    // Check Inherited Properties
    if (mProperties.keys().indexOf(aName) == -1) {
        qDebug() << "ComponentInfo::handleBasePropertyChanges - aName: " << aName << " - aValue: " << aValue;
        // Emit Component Property Changed Signal
        emit componentPropertyChanged(aName, aValue);
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
// Get JSON Object
//==============================================================================
QJsonObject ComponentInfo::toJSONObject(const bool& aChild)
{
    // Init JSON Object
    QJsonObject ciObject;

    // Set Component Name
    ciObject[JSON_KEY_COMPONENT_NAME] = QJsonValue(mName);

    // Check Parent Component
    if (mParent) {
        // Save Parent
        ciObject[JSON_KEY_COMPONENT_PARENT] = mParent->componentName();
    }

    // Set Component Type
    ciObject[JSON_KEY_COMPONENT_TYPE] = QJsonValue(mType);

    // Set Component Tag
    ciObject[JSON_KEY_COMPONENT_TAG] = QJsonValue(mTag);

    // Check If Child Component
    if (!aChild) {
        // Set Category
        ciObject[JSON_KEY_COMPONENT_CATEGORY] = QJsonValue(mCategory);
        // Set Component Base Name
        ciObject[JSON_KEY_COMPONENT_BASE] = QJsonValue(mBaseName);
        // Set Built In
        ciObject[JSON_KEY_COMPONENT_BUILTIN] = QJsonValue(mBuiltIn);
    }

    // Check Use Implicit Pos X
    if (mImplicitPosX) {
        // Set Use Implicit Pos X
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSX] = QJsonValue(mImplicitPosX);
    }

    // Check Use Implicit Pos Y
    if (mImplicitPosY) {
        // Set Use Implicit Pos Y
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSY] = QJsonValue(mImplicitPosY);
    }

    // Check Use Implicit Width
    if (mImplicitWidth) {
        // Set Use Implicit Width
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_WIDTH] = QJsonValue(mImplicitWidth);
    }

    // Check Use Implicit Height
    if (mImplicitHeight) {
        // Set Use Implicit Height
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_HEIGHT] = QJsonValue(mImplicitHeight);
    }

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
            cArray << mChildren[i]->toJSONObject(true);
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
void ComponentInfo::fromJSONObject(const QJsonObject& aObject, const bool aCreateChildren)
{
    // Set Component Name
    setComponentName(aObject[JSON_KEY_COMPONENT_NAME].toString());

    qDebug() << "ComponentInfo::fromJSONObject - mName: " << mName;

    // Set Component Type
    setComponentType(aObject[JSON_KEY_COMPONENT_TYPE].toString());

    // Init Info Path
    initInfoPath();

    // Set Component Tag
    setComponentTag(aObject[JSON_KEY_COMPONENT_TAG].toString());

    // Check Keys
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_CATEGORY) >= 0) {
        // Set Component Category
        setComponentCategory(aObject[JSON_KEY_COMPONENT_CATEGORY].toString());
    }

    // Check Keys - Base
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_BASE) >= 0) {
        // Set Component Base Name
        setComponentBase(aObject[JSON_KEY_COMPONENT_BASE].toString());

        // Base Components Might Not Be Ready !!!!

        // Set Base Component
        setBaseComponent(mProject ? mProject->getComponentByName(mBaseName) : NULL);
    }

    // Check Keys - Built In
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_BUILTIN) >= 0) {
        // Set Built In
        setBuiltIn(aObject[JSON_KEY_COMPONENT_BUILTIN].toBool());
    }

    // Check Keys - Use Implicit Pos X
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_USE_IMPLICIT_POSX) >= 0) {
        // Set Use Implicit Pos X
        setUseIPosX(aObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSX].toBool());
    }

    // Check Keys - Use Implicit Pos Y
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_USE_IMPLICIT_POSY) >= 0) {
        // Set Use Implicit Pos Y
        setUseIPosY(aObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSY].toBool());
    }

    // Check Keys - Use Implicit Width
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_USE_IMPLICIT_WIDTH) >= 0) {
        // Set Use Implicit Width
        setUseIWidth(aObject[JSON_KEY_COMPONENT_USE_IMPLICIT_WIDTH].toBool());
    }

    // Check Keys - Use Implicit Height
    if (aObject.keys().indexOf(JSON_KEY_COMPONENT_USE_IMPLICIT_HEIGHT) >= 0) {
        // Set Use Implicit Height
        setUseIHeight(aObject[JSON_KEY_COMPONENT_USE_IMPLICIT_HEIGHT].toBool());
    }

    // ...

//    // Set Parent Component
//    mParent = mProject ? mProject->getComponentByName(aObject[JSON_KEY_COMPONENT_PARENT].toString()) : NULL;

    // Set ProtoType Component
    mProtoType = (mProject && !mIsProtoType) ? mProject->getComponentByName(mName, mType) : NULL;

    // ...

    // Set Imports
    mImports = aObject[JSON_KEY_COMPONENT_IMPORTS].toArray();
    // Set Anchors
    mAnchors = aObject[JSON_KEY_COMPONENT_ANCHORS].toObject();
    // Set Own Properties
    mOwnProperties = aObject[JSON_KEY_COMPONENT_OWN_PROPERTIES].toObject();
    // Set Properties
    mProperties = aObject[JSON_KEY_COMPONENT_PROPERTIES].toObject();
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

    // Check To Create Children
    if (aCreateChildren && caCount > 0) {
        // Iterate Through Children Array
        for (int i=0; i<caCount; i++) {
            // Get Array Item
            QJsonObject childObject = childrenArray[i].toObject();

            // Get Child Component Name
            QString ccName = childObject[JSON_KEY_COMPONENT_NAME].toString();
            // Get Child Component Type
            QString ccType = childObject[JSON_KEY_COMPONENT_TYPE].toString();

            // Get Child Compoennt ProtoType
            ComponentInfo* componentProtoType = mProject ? mProject->getComponentByName(ccName, ccType, true) : NULL;

            // Check Child Component
            if (componentProtoType) {
                //qDebug() << "ComponentInfo::fromJSONObject - componentProtoType: " << componentProtoType->mName;
                // Clone Component
                ComponentInfo* childComponent = componentProtoType->clone();
                // Set Parent FIRST!!! Needed for the Recursive call of fromJSONObject
                childComponent->mParent = this;
                // Emit Depth Changed Signal
                emit childComponent->depthChanged(childComponent->depth());
                // Set Up/Update Child Component from JSON Object
                childComponent->fromJSONObject(childObject);
                // Add Child
                addChild(childComponent);

            } else {
                qWarning() << "ComponentInfo::fromJSONObject - ccName: " << ccName << " - NO COMPONENT!!";
            }
        }
    }
}

//==============================================================================
// Set Up Component From JSON Content/String
//==============================================================================
void ComponentInfo::fromJSON(const QByteArray& aContent, const bool aCreateChildren)
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
    fromJSONObject(ciObject, aCreateChildren);
}

//==============================================================================
// Remove/Delete From Parent
//==============================================================================
void ComponentInfo::removeFromParent()
{
    // Check Parent
    if (mParent) {
        qDebug() << "ComponentInfo::removeFromParent";
        // Remove Child
        mParent->removeChild(this);
    }
}

//==============================================================================
// Take From Parent
//==============================================================================
int ComponentInfo::takeFromParent()
{
    // Check Parent
    if (mParent) {
        qDebug() << "ComponentInfo::takeFromParent";
        // Take Child From Parent
        return mParent->takeChild(this);
    }

    return -1;
}

//==============================================================================
// Request Close
//==============================================================================
void ComponentInfo::requestClose()
{
    // Check If Is Root
    if (mIsRoot) {
        qDebug() << "ComponentInfo::requestClose";
        // Emit Request Container Close
        emit requestContainerClose();
    }
}

//==============================================================================
// Set Child Object ID
//==============================================================================
void ComponentInfo::setChildObjectID(QObject* aObject, const QString& aID)
{
    // Check Object
    if (!aObject) {
        qWarning() << "ComponentInfo::setChildObjectID - aObject IS NULL!!";
        return;
    }

    // Init Root Component Info
    ComponentInfo* rootInfo = findRoot(this);

    // Check Root Info
    if (!rootInfo) {
        qWarning() << "ComponentInfo::setChildObjectID - NULL Root Info!!!";
        return;
    }

    // Try To Find Key If ID Is Updated
    QString cidKey = rootInfo->mIDMap.key(aObject);

    // Check Key
    if (!cidKey.isEmpty()) {
        // Remove Key
        rootInfo->mIDMap.remove(cidKey);
    }

    // Check ID
    if (aID.isEmpty()) {
        //qDebug() << "ComponentInfo::setChildObjectID - aObject: " << aObject << " - ID CLEARED.";
        return;
    }

    // Check If ID Is Already Registered
    if (rootInfo->mIDMap.keys().indexOf(aID) < 0) {

        //qDebug() << "ComponentInfo::setChildObjectID - aObject: " << aObject << " - aID: " << aID;

        // Add Object ID
        rootInfo->mIDMap[aID] = aObject;

        //qDebug() << "ComponentInfo::setChildObjectID - mIDMap: " << mIDMap;

    } else {
        qWarning() << "ComponentInfo::setChildObjectID - aID: " << aID << " - ID IS ALREADY IN USE!!";
    }
}

//==============================================================================
// Clear Object ID
//==============================================================================
void ComponentInfo::clearObjectID(const QString& aID)
{
    // Init Root Component Info
    ComponentInfo* rootInfo = findRoot(this);

    // Check If ID Is Already Registered
    if (rootInfo->mIDMap.keys().indexOf(aID) >= 0) {
        qDebug() << "ComponentInfo::clearObjectID - aID: " << aID;
        // Remove Object ID
        rootInfo->mIDMap.remove(aID);
    } else {
        qWarning() << "ComponentInfo::clearObjectID - aID: " << aID << " - IS NOT REGISTERED!!";
    }
}

//==============================================================================
// Get Child Object By ID
//==============================================================================
QObject* ComponentInfo::getChildObject(const QString& aID)
{
    // Init Root Component Info
    ComponentInfo* rootInfo = findRoot(this);

    return rootInfo ? rootInfo->mIDMap.value(aID) : NULL;
}

//==============================================================================
// Find Root Component
//==============================================================================
ComponentInfo* ComponentInfo::findRoot(ComponentInfo* aComponent)
{
    // Check Component Info
    if (!aComponent) {
        return NULL;
    }

    // Check Component Info
    if (aComponent->mIsRoot) {
        //qDebug() << "ComponentInfo::findRoot - mName: " << aComponent->mName << " - mIsRoot: " << aComponent->mIsRoot << " - FOUND!";

        return aComponent;
    }

    //qDebug() << "ComponentInfo::findRoot - mName: " << aComponent->mName << " - mIsRoot: " << aComponent->mIsRoot;


    return findRoot(aComponent->mParent);
}

//==============================================================================
// Generate Component ID
//==============================================================================
QString ComponentInfo::liveCodeGenerateID(const bool& aLiveRoot)
{
    // Get Component ID
    QString cID = componentProperty(JSON_KEY_COMPONENT_PROPERTY_ID).toString();

    // Check ID
    if (cID.isEmpty()) {
        // Set Component ID
        cID = mName;
        // Lower First Char
        cID[0] = cID[0].toLower();
        // Check If Root
        if (aLiveRoot) {
            // Set ID
            cID += "Root";
        } else {
            // ...
        }
    }

    return cID;
}

//==============================================================================
// Format Imports
//==============================================================================
QString ComponentInfo::liveCodeFormatImports(const bool& /*aLiveRoot*/)
{
//    // Check Live Root
//    if (!aLiveRoot) {
//        return "";
//    }

    // Init Live Code
    QString liveCode = "";

    // Get Imports Count
    int iCount = mImports.count();

    // Check Imports Count
    if (iCount > 0) {
        // Iterate Through Imports
        for (int i=0; i<iCount; i++) {
            // Append Imports
            liveCode += QString("import %1\n").arg(mImports[i].toString());
        }
    } else {
        // Append Imports
        liveCode += QString("import QtQuick 2.7\n");
    }

    // Add New Line
    liveCode += "\n";

    return liveCode;
}

//==============================================================================
// Format Component Name
//==============================================================================
QString ComponentInfo::liveCodeFormatName(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Component Type
    if (mType == COMPONENT_TYPE_DATASOURCE) {
        // Add Type
        liveCode += QString("%1%2").arg(aIndent).arg("QtObject {\n");
    } else {
        // Check If build In
        if (mBuiltIn) {
            // Add Name
            liveCode += QString("%1%2 {\n").arg(aIndent).arg(mName);
        } else {

            // Check Base Component
            if (!mBase) {
                qCritical() << "ComponentInfo::liveCodeFormatName - NO BASE COMPONENT!!";
                return "";
            }

            // Add Type
            liveCode += QString("%1%2 {\n").arg(aIndent).arg(mBase->mName);
        }
    }

    return liveCode;
}

//==============================================================================
// Format ID
//==============================================================================
QString ComponentInfo::liveCodeFormatID(const QString& aCID, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check ID
    if (!aCID.isEmpty()) {
        // Add ID
        liveCode += QString("%1id: %2\n").arg(aIndent).arg(aCID);
    }

    return liveCode;
}

//==============================================================================
// Fromat Object Name
//==============================================================================
QString ComponentInfo::liveCodeFormatObjectName(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Get Object Name
    QString objectName = componentProperty(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME).toString();

    // Check Object Name
    if (!objectName.isEmpty()) {
        // Add Object Name
        liveCode += QString("%1objectName: %2\n").arg(aIndent).arg(objectName);
    }

    return liveCode;
}

//==============================================================================
// Format Positions
//==============================================================================
QString ComponentInfo::liveCodeFormatPosition(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Component Category
    if (mCategory != COMPONENT_CATEGORY_NONVISUAL) {
        // Get Pos X
        QString cpX = posX();
        // Check Pos X
        if (!cpX.isEmpty() && cpX != "0") {
            // Add Pos X
            liveCode += QString("%1x: %2\n").arg(aIndent).arg(cpX);
        }

        // Get Pos Y
        QString cpY = posY();
        // Check Pos Y
        if (!cpY.isEmpty() && cpY != "0") {
            // Add Pos Y
            liveCode += QString("%1y: %2\n").arg(aIndent).arg(cpY);
        }

        // Get Pos Z
        QString cpZ = posZ();
        // Check Pos Z
        if (!cpZ.isEmpty() && cpZ != "0") {
            // Add Pos Z
            liveCode += QString("%1z: %2\n").arg(aIndent).arg(cpZ);
        }
    }

    return liveCode;
}

//==============================================================================
// Format Size
//==============================================================================
QString ComponentInfo::liveCodeFormatSize(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Component Category
    if (mCategory != COMPONENT_CATEGORY_NONVISUAL) {
        // Get Width
        QString cWidth = width();
        // Check Width
        if (!cWidth.isEmpty() && cWidth != "0") {
            // Add Width
            liveCode += QString("%1width: %2\n").arg(aIndent).arg(cWidth);
        }

        // Get Height
        QString cHeight = height();
        // Check Height
        if (!cHeight.isEmpty() && cHeight != "0") {
            // Add Height
            liveCode += QString("%1height: %2\n").arg(aIndent).arg(cHeight);
        }
    }

    return liveCode;
}

//==============================================================================
// Format Anchors
//==============================================================================
QString ComponentInfo::liveCodeFormatAnchors(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Anchors
    if (!mIsRoot && !mAnchors.isEmpty()) {
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
            liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL).arg(afTarget);
        // Check Center In Target
        } else if (!acTarget.isEmpty()) {
            // Add Center In Target
            liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN).arg(acTarget);
            // Set Horizontal & Vertical Center Used Flag
            hCenter = true;
            vCenter = true;
        } else {
            // Check Horizontal Center Target
            if (!ahcTarget.isEmpty()) {
                // Add Horizontal Center Target
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER).arg(ahcTarget);
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
                    liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT).arg(alTarget);
                }

                // Check Right Anchor Target
                if (!arTarget.isEmpty()) {
                    // Add Right Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT).arg(arTarget);
                }
            }

            // Check Vertical Center Target
            if (!avcTarget.isEmpty()) {
                // Add Vertical Center Target
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER).arg(avcTarget);
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
                    liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP).arg(atTarget);
                }

                // Check Bottom Anchor Target
                if (!abTarget.isEmpty()) {
                    // Add Bottom Anchor Target
                    liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM).arg(abTarget);
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
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS).arg(hcOffset);
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
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS).arg(vcOffset);
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
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN).arg(alMargin);
                // Set Single Margin Used
                sMargin = true;
            }

            // Check Right Margin
            if (!arMargin.isEmpty()) {
                // Add Right Margin
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN).arg(arMargin);
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
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN).arg(atMargin);
                // Set Single Margin Used
                sMargin = true;
            }

            // Check Bottom Margin
            if (!abMargin.isEmpty()) {
                // Add Bottom Margin
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN).arg(abMargin);
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
                liveCode += QString("%1%2: %3\n").arg(aIndent).arg(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS).arg(aMargins);
            }
        }
    }

    return liveCode;
}

//==============================================================================
// Format Own Properties
//==============================================================================
QString ComponentInfo::liveCodeFormatOwnProperties(QStringList& aOPHooks, QStringList& aEnumHooks, const QString& aID, const QStringList& aFPKeys, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Get Own Properties Keys
    QStringList opKeys = componentOwnPropertyKeys();
    // Get Property Keys
    QStringList pKeys = inheritedPropertyKeys();
    // Get Own Properties Count
    int opCount = opKeys.count();

    // Check Own Prpoerties Keys Count
    if (opCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Iterate Through Own Properties
        for (int i=0; i<opCount; i++) {
            // Get Property Name
            QString pName = opKeys[i];
            // Check Filtered Properties
            if (aFPKeys.indexOf(pName) == -1) {
                // Get Type And Value
                QString typeAndValue = propertyTypeAndValue(pName);
                // Init Read Only
                bool readOnly = false;
                // Init Default Alias
                bool defaultAlias = false;
                // Get Type
                QString pType = Utils::parseType(typeAndValue, readOnly, defaultAlias);
                // Get Value
                QString pValue = Utils::parseValue(typeAndValue);

                // TODO: Handle Formulas And Bindigs!!!

                // Check Type
                if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING) {
                    // Set Value
                    pValue = QString("\"%1\"").arg(pValue);
                }

                // Check Inherited Property Keys
                if (pKeys.indexOf(pName) == -1) {
                    // Check If Built In Component
                    if (mBuiltIn) {
                        // Check If Read Only
                        if (!readOnly) {
                            // Append Live Code
                            liveCode += QString("%1%3: %4\n").arg(aIndent).arg(pName).arg(pValue);
                        }

                    } else {
                        // Check Read Only
                        if (readOnly) {
                            // Append Live Code
                            liveCode += QString("%1readonly property %2 %3: %4\n").arg(aIndent).arg(pType).arg(pName).arg(pValue);
                        } else if (defaultAlias) {
                            // Append Live Code
                            liveCode += QString("%1default property %2 %3: %4\n").arg(aIndent).arg(pType).arg(pName).arg(pValue);
                        } else {
                            // Append Live Code
                            liveCode += QString("%1property %2 %3: %4\n").arg(aIndent).arg(pType).arg(pName).arg(pValue);
                        }
                    }
                }

                // Check Property Type
                if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM) {
                    // Add Enum Values to Enum Hooks
                    aEnumHooks << liveCodeGenerateEnumValueCases(propertyEnums(pName));

                    // Value Setting Hook
                    aOPHooks << QString("%1%1%1case \"%2\": %3.%2 = __string2enum(value); break;\n").arg(aIndent).arg(pName).arg(aID);

                } else {
                    // Check If Read Only
                    if (!readOnly) {
                        // Add Value Setting Hook
                        aOPHooks << QString("%1%1%1case \"%2\": %3.%2 = value; break;\n").arg(aIndent).arg(pName).arg(aID);
                    }
                }

                // TODO: Handle Property Changes -> Add propertyChanged Slots
            }
        }
    }

    return liveCode;
}

//==============================================================================
// Format Properties
//==============================================================================
QString ComponentInfo::liveCodeFormatInheritedProperties(QStringList& aPHooks, QStringList& aEnumHooks, const QString& aID, const QStringList& aFPKeys, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Get All Inherited Properties Keys
    QStringList pKeys = inheritedPropertyKeys();
    // Get Properties Count
    int pCount = pKeys.count();

    // Check Inherited Properties Keys Count
    if (pCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Iterate Through Property Keys
        for (int k=0; k<pCount; k++) {
            // Get Type
            QString pType = propertyType(pKeys[k]);
            // Init ReadOnly
            bool readOnly = pType.indexOf(JSON_VALUE_PROPERTY_TYPE_PREFIX_READONLY) >= 0;
            // Get Value
            QString pValue = componentProperty(pKeys[k]).toString();

            // Check readOnly
            if (!readOnly) {
                // Check Key
                if (aFPKeys.indexOf(pKeys[k]) == -1) {

                    // Check Type
                    if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING) {
                        // Set Value
                        pValue = QString("\"%1\"").arg(pValue);
                    }

                    // Append Live Code
                    liveCode += QString("%1%2: %3\n").arg(aIndent).arg(pKeys[k]).arg(pValue);
                }

                // Check Property Key
                if (pKeys[k] != JSON_KEY_COMPONENT_PROPERTY_ID) {
                    // Check Property Type
                    if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM) {

                        // Add Enum Values To Enum Hooks
                        aEnumHooks << liveCodeGenerateEnumValueCases(propertyEnums(pKeys[k]));

                        // Add Value Setting Hook
                        aPHooks << QString("%1%1%1case \"%2\": %3.%2 = __string2enum(value); break;\n").arg(aIndent).arg(pKeys[k]).arg(aID);

                    } else {
                        // Add Value Setting Hook
                        aPHooks << QString("%1%1%1case \"%2\": %3.%2 = value; break;\n").arg(aIndent).arg(pKeys[k]).arg(aID);
                    }
                }
            }

            // TODO: Handle Property Changes -> PropertyChanged Slot

        }
    }

    return liveCode;
}

//==============================================================================
// Format Signals
//==============================================================================
QString ComponentInfo::liveCodeFormatSignals(const QStringList& /*aOPKeys*/, const QStringList& /*pKeys*/, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

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
            liveCode += QString("%1%2\n").arg(aIndent).arg(signalDef);
        }
    }

    // TODO: Add Property Changes Signal

    // Own Properties

    // Inherited Properties

    // ...

    return liveCode;
}

//==============================================================================
// Format Slots
//==============================================================================
QString ComponentInfo::liveCodeFormatSlots(const QStringList& /*aOPKeys*/, const QStringList& /*pKeys*/, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

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
            liveCode += QString("%1%2: %3\n\n").arg(aIndent).arg(slotName).arg(slotSource);
        }
    }

    // TODO: Add Property Value Changed Slots

    // TODO: Add Property Value Changed Signal

    return liveCode;
}

//==============================================================================
// Format Functions
//==============================================================================
QString ComponentInfo::liveCodeFormatFunctions(const QStringList& aOPHooks, const QStringList& aPHooks, const QStringList& aEnumHooks, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Add Enum Value Hooks ====================================================

    // Get Enum Value Hooks Count
    int evhCount = aEnumHooks.count();

    // Check Count
    if (evhCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Comment Line
        liveCode += QString("%1// Convert Strings to Enum Values\n").arg(aIndent);

        // Init String To Enum Function Code
        QString enumValueFunction = QString("%1function __string2enum(value) {\n").arg(aIndent);
        // Add Value Switch
        enumValueFunction += QString("%1%1switch (value) {\n").arg(aIndent);
        // Add Default Value Case
        enumValueFunction += QString("%1%1%1default: console.log(\"__string2enum value:\" + value + \" IS NOT DEFINED!\"); break;\n").arg(aIndent);

        // Iterate Through Enum Value Hooks
        for (int eh=0; eh<evhCount; eh++) {
            // Add Enum Value Case Line
            enumValueFunction += aEnumHooks[eh];
        }

        // Add Switch Closing Bracket
        enumValueFunction += QString("%1%1}\n").arg(aIndent);
        // Add Final Bracket
        enumValueFunction += QString("%1}\n").arg(aIndent);

        liveCode += enumValueFunction;

        // Add New Line
        liveCode += "\n";
    }

    // Add Value Setting Hooks =================================================

    // Get Own Property Value Hook's Count
    int opvhCount = aOPHooks.count();
    // Get Inherited Properties Value Hook's Count
    int pvhCount = aPHooks.count();

    // Check Properties Count
    if (opvhCount > 0 || pvhCount > 0) {
        // Add New Line
        liveCode += "\n";
        // Comment Line
        liveCode += QString("%1// Property Set Hook\n").arg(aIndent);
        // Init Property Update Hook Function Code
        QString propertyHooks = QString("%1function __setProperty(key, value) {\n").arg(aIndent);
        // Add Key Switch
        propertyHooks += QString("%1%1switch (key) {\n").arg(aIndent);
        // Add Default Hook
        propertyHooks += QString("%1%1%1default: console.log(\"__setProperty property:\" + key + \" IS NOT DEFINED!\"); break;\n").arg(aIndent);

        // Iterate Through Own Property Value Hooks
        for (int i=0; i<opvhCount; i++) {
            // Append Own Property Vlaue Hook
            propertyHooks += aOPHooks[i];
        }

        // Iterate Through Inherited Property Value Hooks
        for (int j=0; j<pvhCount; j++) {
            // Append Inherited Property Value Hook
            propertyHooks += aPHooks[j];
        }

        // Add Switch Closing Bracket
        propertyHooks += QString("%1%1}\n").arg(aIndent);
        // Add Final Bracket
        propertyHooks += QString("%1}\n").arg(aIndent);

        // Append Property Hooks To Live Code
        liveCode += propertyHooks;

        // Add New Line
        liveCode += "\n";
    }

    // Add Functions ===========================================================

    // Check Functions
    if (!mFunctions.isEmpty()) {
        // Get Functions Count
        int fCount = mFunctions.count();

        // Iterate Through Functions
        for (int f=0; f<fCount; f++) {
            // Get Function Object
            QJsonObject functionObject = mFunctions[f].toObject();
            // Get Function Name
            QString functionName = functionObject[JSON_KEY_COMPONENT_FUNCTION_NAME].toString();
            // Get Function Parameters
            QString functionParameters = functionObject[JSON_KEY_COMPONENT_FUNCTION_PARAMETERS].toString();
            // Get Function Source
            QString functionSource = functionObject[JSON_KEY_COMPONENT_FUNCTION_SOURCE].toString();
            // Append To Live Code
            liveCode += QString("%1function %2(%3) {\n").arg(aIndent).arg(functionName).arg(functionParameters);
            // Get Source Code Lines
            QStringList sourceLines = functionSource.split("\n", QString::SkipEmptyParts);
            // Get Lines Count
            int slCount = sourceLines.count();
            // Iterate Through Source Lines
            for (int sl=0; sl<slCount; sl++) {
                // Append Source
                liveCode += QString("%1%2\n").arg(aIndent).arg(sourceLines[sl]);
            }

            // Add New Line
            liveCode += QString("%1}\n\n").arg(aIndent);
        }
    }

    return liveCode;
}

//==============================================================================
// Format Children
//==============================================================================
QString ComponentInfo::liveCodeFormatChildren(const bool& aGenerateChildren, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Children
    if (aGenerateChildren && mChildren.count() > 0) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    return liveCode;
}

//==============================================================================
// Format States
//==============================================================================
QString ComponentInfo::liveCodeFormatStates(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check States
    if (!mStates.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    return liveCode;
}

//==============================================================================
// Format Transitions
//==============================================================================
QString ComponentInfo::liveCodeFormatTransitions(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Check Transitions
    if (!mTransitions.isEmpty()) {
        // Add New Line
        liveCode += "\n";

        // ...
    }

    return liveCode;
}

//==============================================================================
// Generate Enum Value Live Code Cases
//==============================================================================
QStringList ComponentInfo::liveCodeGenerateEnumValueCases(const QStringList& aEnumValues)
{
    // Init Live Enum Cases
    QStringList enumLiveCases = QStringList();

    // Get Enum Values Count
    int evCount = aEnumValues.count();
    // Iterate Through Enum Values
    for (int i=0; i<evCount; i++) {
        // Init Enum Value Case Line
        QString evLine = QString("%1%1%1case \"%2\": return %2;\n").arg(DEFAULT_SOURCE_INDENT).arg(aEnumValues[i]);

        //qDebug() << "ComponentInfo::liveCodeGenerateEnumValuecases - aEnumValues[" << i << "]: " << aEnumValues[i] <<  " -> " << evLine;

        // Append To live Enum Cases
        enumLiveCases << evLine;
    }

    return enumLiveCases;
}

//==============================================================================
// Generate Live Code for Designer
//==============================================================================
QString ComponentInfo::generateLiveCode(const bool& aLiveRoot, const bool& aGenerateChildren)
{
//    // Check If Built In
//    if (mBuiltIn && !aLiveRoot) {
//        qDebug() << "#### ComponentInfo::generateLiveCode - buildin non root!";
//        // No Need to Generate
//        return "";
//    }

    qDebug() << "ComponentInfo::generateLiveCode - mName: " << mName << " - aLiveRoot: " << aLiveRoot << " - aGenerateChildren: " << aGenerateChildren;

    // Init Live Code
    QString liveCode = QString("// Component: %1\n").arg(componentPath());
    // Init Indent Level
    int indentLevel = 0;
    // Init Current Indent
    QString indent = "";
    // Fill
    indent.fill(' ', indentLevel * 4);



    // Add Imports =============================================================

    liveCode += liveCodeFormatImports(aLiveRoot);

    // Get Component Name
    QString clName = liveCodeFormatName(indent);

    // Check Component Name Line
    if (clName.isEmpty()) {
        qCritical() << "ComponentInfo::generateLiveCode - INVALID COMPONENT NAME!!!";
    }

    // Add Name ================================================================

    liveCode += clName;

    // Inc Indent Level
    indentLevel++;
    // Increase Indent
    indent.fill(' ', indentLevel * 4);

    // Init Component ID
    QString cID = liveCodeGenerateID();

    // Get Component ID
    QString lccID = liveCodeFormatID(cID, indent);

    // Add ID ==================================================================

    liveCode += lccID;

    // Get Object Name
    QString objectName = liveCodeFormatObjectName(indent);

    // Add Object Name =========================================================

    liveCode += objectName;

    // Check ID & Object Name
    if (!lccID.isEmpty() || !objectName.isEmpty()) {
        // Add New Line
        liveCode += "\n";
    }

    // Add Pos =================================================================

    // Check Live Root
    if (aLiveRoot) {
        liveCode += liveCodeFormatPosition(indent);
    }

    // Add Size ================================================================

    liveCode += liveCodeFormatSize(indent);

    // Add Anchors =============================================================

    //liveCode += liveCodeFormatAnchors(indent);

    // Init Own Property Value Hook List
    QStringList opvHookList = QStringList();
    // Init Inherited Properties Value Hook List
    QStringList pvHookList = QStringList();
    // Init Enum Hook List
    QStringList enumHookList = QStringList();

    // Get Filtered Property Keys
    QStringList fpKeys = mProject->filteredProperties();

    // Add Own Properties ======================================================

    liveCode += liveCodeFormatOwnProperties(opvHookList, enumHookList, cID, fpKeys, indent);

    // Add Inherited Properties ================================================

    liveCode += liveCodeFormatInheritedProperties(pvHookList, enumHookList, cID, fpKeys, indent);

    // Add Signals =============================================================

    liveCode += liveCodeFormatSignals(componentOwnPropertyKeys(), inheritedPropertyKeys(), indent);

    // Add Slots ===============================================================

    liveCode += liveCodeFormatSlots(componentOwnPropertyKeys(), inheritedPropertyKeys(), indent);

    // Add Hooks for Property Getters And Setters and Functions ================

    liveCode += liveCodeFormatFunctions(opvHookList, pvHookList, enumHookList, indent);

    // Add Children ============================================================

    liveCode += liveCodeFormatChildren(aGenerateChildren, indent);

    // Add States ==============================================================

    liveCode += liveCodeFormatStates(indent);

    // Add Transitions =========================================================

    liveCode += liveCodeFormatTransitions(indent);

    //==========================================================================

    liveCode += QString("%1//...\n\n").arg(indent);

    liveCode += "}\n";

    //qDebug() << "ComponentInfo::generateLiveCode - liveCode: " << liveCode;

    return liveCode;
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::componentProperty(const QString& aName)
{
    // Check Property Keys
    if (mProperties.keys().indexOf(aName) >= 0) {
        return mProperties.value(aName).toString();
    }

    // Check Own Properties First
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        return Utils::parseValue(mOwnProperties.value(aName).toString(), true);
    }

    // Check Property Name
    if (aName != JSON_KEY_COMPONENT_PROPERTY_ID && aName != JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME) {
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
            return mBase->componentProperty(aName);
        }

        //qWarning() << "ComponentInfo::componentProperty - aName: " << aName << " - NO PROPERTY!";
    }

    return QVariant();
}

//==============================================================================
// Add Own Property
//==============================================================================
bool ComponentInfo::addComponentProperty(const QString& aName,
                                         const ComponentInfo::EPropertyType& aType,
                                         const QString& aMin,
                                         const QString& aMax,
                                         const QString& aEnumValues,
                                         const QVariant& aDefaultValue)
{
    // Check Owh Property Keys
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        qDebug() << "ComponentInfo::addComponentProperty - ALREADY HAS A PROPERTY!";

        return false;
    }

    // Switch Type
    switch (aType) {
        default:
        case ComponentInfo::EPropertyType::EPTString:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING, aDefaultValue.toString());
        break;
        case ComponentInfo::EPropertyType::EPTBool:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL, aDefaultValue.toString());
        break;
        case ComponentInfo::EPropertyType::EPTInt:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_INT, aDefaultValue.toString(), aMin, aMax);
        break;
        case ComponentInfo::EPropertyType::EPTDouble:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE, aDefaultValue.toString(), aMin, aMax);
        break;
        case ComponentInfo::EPropertyType::EPTReal:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL, aDefaultValue.toString(), aMin, aMax);
        break;
        case ComponentInfo::EPropertyType::EPTVar:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR, aDefaultValue.toString());
        break;
        case ComponentInfo::EPropertyType::EPTQtObject:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT, aDefaultValue.toString());
        break;
        case ComponentInfo::EPropertyType::EPTQtObjectList:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST, aDefaultValue.toString());
        break;
        case ComponentInfo::EPropertyType::EPTEnum:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM, aDefaultValue.toString(), "", "", aEnumValues);
        break;
        case ComponentInfo::EPropertyType::EPTAlias:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ALIAS, aDefaultValue.toString());
        break;
    }

    // Set Dirty
    setDirty(true);
    // Emit Own Property Added
    emit ownPropertyAdded(aName);


    return true;
}

//==============================================================================
// Remove Property
//==============================================================================
void ComponentInfo::removeComponentProperty(const QString& aName)
{
    // Check Own Properties
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        // Remove Key
        mOwnProperties.remove(aName);
    }
}

//==============================================================================
// Set Property - Simple!!!
//==============================================================================
bool ComponentInfo::setComponentProperty(const QString& aName, const QVariant& aValue)
{
    //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue;

    // Check Property Keys
    if (mProperties.keys().indexOf(aName) >= 0) {
        // Check Value
        if (mProperties.value(aName).toString() != aValue.toString()) {
            //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - INHERITED";
            // Set Property
            mProperties[aName] = aValue.toString();
            // Set Dirty
            setDirty(true);
            // Check If Filtered Property Change
            if (mProject->filteredProperties().indexOf(aName) == -1) {
                // Emit Property Changed Signal
                emit componentPropertyChanged(aName, aValue);
            }

            return true;
        }

        return false;
    }

    // Check Own Property Keys
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        // Get Type And Value
        QString typeAndValue = mOwnProperties.value(aName).toString();
        // Split Type And Value
        QStringList tavElements = typeAndValue.split(":");

        // Check Value
        if (Utils::parseValue(typeAndValue, true) != aValue.toString()) {
            //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - OWN";

            // Set New Type And Value
            typeAndValue = Utils::composeTypeAndValue(tavElements[0],
                                                      aValue.toString(),
                                                      tavElements[1],
                                                      tavElements[2],
                                                      tavElements[3]);

            // Set Property
            mOwnProperties[aName] = typeAndValue;
            // Set Dirty
            setDirty(true);
            // Check If Filtered Property Change
            if (mProject->filteredProperties().indexOf(aName) == -1) {
                // Emit Property Changed Signal
                emit componentPropertyChanged(aName, aValue);
            }

            return true;
        }

        return false;
    }

    // Check ProtoType Own Properties
    if (mProtoType && mProtoType->mOwnProperties.keys().indexOf(aName) >= 0) {
        // Get ProtoType Type & Value
        QString ptTypeAndValue = mProtoType->mOwnProperties.value(aName).toString();
        // Check Value
        if (Utils::parseValue(ptTypeAndValue, true) != aValue.toString()) {
            //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - PROTOTYPE";
            // Store To Properties
            mProperties[aName] = aValue.toString();
            // Set Dirty
            setDirty(true);
            // Check If Filtered Property Change
            if (mProject->filteredProperties().indexOf(aName) == -1) {
                // Emit Property Changed Signal
                emit componentPropertyChanged(aName, aValue);
            }

            return true;
        }

        return false;
    }

    // Check Base Component
    if (mBase && mBase->hasProperty(aName)) {
        // Get Value
        QVariant bValue = mBase->componentProperty(aName);
        // Check Value
        if (bValue != aValue) {
            //qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - BASE";
            // Store To Properties
            mProperties[aName] = aValue.toString();
            // Set Dirty
            setDirty(true);
            // Check If Filtered Property Change
            if (mProject->filteredProperties().indexOf(aName) == -1) {
                // Emit Property Changed Signal
                emit componentPropertyChanged(aName, aValue);
            }

            return true;
        }

        return false;
    }

    // Add Own Property - NOT RECOMMENDED!! Use Own Properties Model to Add Properties!

    // Init Type Prefix
    QString tPrefix = "";

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

    qDebug() << "ComponentInfo::setComponentProperty - aName: " << aName << " - aValue: " << aValue << " - ADDING OWN";

    // Add New Own Property
    mOwnProperties[aName] = Utils::composeTypeAndValue(tPrefix, aValue.toString());
    // Check If Filtered Property Change
    if (mProject->filteredProperties().indexOf(aName) == -1) {
        // Emit Own Property Added Signal
        emit ownPropertyAdded(aName);
    }

    // Set Dirty
    setDirty(true);

    // ...

    return true;
}

//==============================================================================
// Check If Has Property
//==============================================================================
bool ComponentInfo::hasProperty(const QString& aName)
{
    // Check Properyy Key Index
    if (mProperties.keys().indexOf(aName) >= 0) {
        return true;
    }

    // Check Property Index
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
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
// Get Property Type & Value
//==============================================================================
QString ComponentInfo::propertyTypeAndValue(const QString& aName)
{
    // Get Type And Value
    QString typeAndValue = mOwnProperties.value(aName).toString();

    // Check Type And Value
    if (!typeAndValue.isEmpty()) {
        return typeAndValue;
    }

    // Check ProtoType
    if (mProtoType) {
        // Get Type & Value From ProtoType
        typeAndValue = mProtoType->propertyTypeAndValue(aName);

        // Check Type And Value
        if (!typeAndValue.isEmpty()) {
            return typeAndValue;
        }
    }

    // Check Base
    if (mBase) {
        // Get Type And Value
        typeAndValue = mBase->propertyTypeAndValue(aName);

        // Check Type And Value
        if (!typeAndValue.isEmpty()) {
            return typeAndValue;
        }
    }

    return typeAndValue;
}

//==============================================================================
// Get Property Type
//==============================================================================
QString ComponentInfo::propertyType(const QString& aName)
{
    // Get Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Property Index
    int opIndex = opKeys.indexOf(aName);

    // Init Read Only
    bool readOnly = false;
    // Init Default Alias
    bool defaultAlias = false;

    // Check Property Index
    if (opIndex >= 0) {
        // Get Type
        return Utils::parseType(mOwnProperties.value(aName).toString(), readOnly, defaultAlias);
    }

    // Check Prototype
    if (mProtoType) {
        // Get Type
        QString pType = mProtoType->propertyType(aName);
        // Check Property Type
        if (!pType.isEmpty()) {
            return pType;
        }
    }

    return mBase ? mBase->propertyType(aName) : "";
}

//==============================================================================
// Get Property Enum Values
//==============================================================================
QStringList ComponentInfo::propertyEnums(const QString& aName)
{
    // Get Keys
    QStringList opKeys = mOwnProperties.keys();
    // Get Property Index
    int opIndex = opKeys.indexOf(aName);

    // Check Property Index
    if (opIndex >= 0) {
        // Get Enum Values
        return Utils::parseEnumValues(mOwnProperties.value(aName).toString());
    }

    // Check Prototype
    if (mProtoType) {
        // Get Type
        QStringList pEnums = mProtoType->propertyEnums(aName);
        // Check Property Type
        if (!pEnums.isEmpty()) {
            return pEnums;
        }
    }

    return mBase ? mBase->propertyEnums(aName) : QStringList();
}

//==============================================================================
// Get Property Value
//==============================================================================
QVariant ComponentInfo::propertyValue(const QString& aName, const bool& aRaw)
{
    // Check Name
    if (aName.isEmpty()) {
        return QVariant();
    }

    // Check Properties
    QString result = mProperties.value(aName).toString();

    // Check Result
    if (!result.isEmpty()) {
        return result;
    }

    // Get Type And Value
    QString typeAndValue = mOwnProperties.value(aName).toString();
    // Check Type And Value
    if (!typeAndValue.isEmpty()) {
        // Parse Value
        return Utils::parseValue(typeAndValue, aRaw);
    }

    // Check Prototype
    if (mProtoType) {
        // Get Type And Value From ProtoType
        typeAndValue = mProtoType->mOwnProperties.value(aName).toString();

        // Check Type And Value
        if (!typeAndValue.isEmpty()) {
            // Parse Value
            return Utils::parseValue(typeAndValue, aRaw);
        }
    }

    // Check Base
    if (mBase) {
        return mBase->propertyValue(aName);
    }

    return QVariant();
}

//==============================================================================
// Get Child Count
//==============================================================================
int ComponentInfo::childCount()
{
    return mChildren.count();
}

//==============================================================================
// Child Depth
//==============================================================================
int ComponentInfo::depth()
{
    // Check Parent
    if (mParent) {
        return mParent->depth() + 1;
    }

    return 0;
}

//==============================================================================
// Get Child
//==============================================================================
ComponentInfo* ComponentInfo::childInfo(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mChildren.count()) {
        return mChildren[aIndex];
    }

    return NULL;
}

//==============================================================================
// Add Child
//==============================================================================
void ComponentInfo::addChild(ComponentInfo* aChild)
{
    // Check Child
    if (aChild) {
        qDebug() << "ComponentInfo::addChild - path: " <<  componentPath() << " <- " << aChild->mName;
        // Reset ProtoType Flag
        aChild->mIsProtoType = false;
        // Clear Dirty Flag
        aChild->mDirty = false;
        // Set Parent
        aChild->mParent = this;
        // Append Child
        mChildren << aChild;
        // Add ID To ID Map
        setChildObjectID(aChild, aChild->componentID());
        // Set Dirty
        setDirty(true);
        // Emit Child Added
        emit childAdded(mChildren.count() - 1);
        // Emit Child Count Changed Signal
        emit childCountChanged(mChildren.count());
    }
}

//==============================================================================
// Insert Child
//==============================================================================
void ComponentInfo::insertChild(const int& aIndex, ComponentInfo* aChild)
{
    // Check Child Info
    if (aChild) {
        qDebug() << "ComponentInfo::addChild - path: " <<  componentPath() << " <- " << aChild->mName << " - aIndex: " << aIndex;

        // Reset ProtoType Flag
        aChild->mIsProtoType = false;
        // Set Parent
        aChild->mParent = this;
        // Clear Dirty Flag
        aChild->mDirty = false;
        // Add ID To ID Map
        setChildObjectID(aChild, aChild->componentID());
        // Insert Child
        mChildren.insert(aIndex, aChild);
        // Set Dirty
        setDirty(true);
        // Emit Child Added
        emit childAdded(aIndex);
        // Emit Child Cound Changed Signal
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
            // Get Child Component Info
            ComponentInfo* childComponent = mChildren[cIndex];

            qDebug() << "ComponentInfo::removeChild - path: " << componentPath() << " - mName: " << childComponent->mName;

            // Emit Child About To Be Removed
            emit childComponent->childAboutToBeRemoved(childComponent);

            // Remove Child Object From ID Map
            setChildObjectID(childComponent, "");

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

            // Emit Child Removed Signal
            emit childRemoved(cIndex);
            // Emit Child Count Changed Signal
            emit childCountChanged(mChildren.count());

        } else {
            qWarning() << "ComponentInfo::removeChild - aChild: " << aChild << " - CHILD COMPONENT NOT FOUND!";
        }
    }
}

//==============================================================================
// Move Child
//==============================================================================
void ComponentInfo::moveChild(const int& aIndex, const int& aTargetIndex)
{
    // Check Indexes
    if (aIndex == aTargetIndex) {
        return;
    }

    // Init New target Index
    int newTargetIndex = aIndex < aTargetIndex ? aTargetIndex-1 : aTargetIndex;

    // Init New Target Index
    //int newTargetIndex = qBound(0, aTargetIndex, mChildren.count() - 1);

    qDebug() << "ComponentInfo::moveChild - aIndex: " << aIndex << " -> " << newTargetIndex;

    // Move Child
    mChildren.move(aIndex, newTargetIndex);

    // Emit Child Moved Signal
    emit childMoved(aIndex, newTargetIndex);

    // Set Dirty
    setDirty(true);
}

//==============================================================================
// Move Child
//==============================================================================
void ComponentInfo::moveChild(ComponentInfo* aChildInfo, const int& aIndex, ComponentInfo* aTargetChildInfo, const int& aTargetIndex)
{
    // Check Component Info & Target Info
    if (aChildInfo == aTargetChildInfo) {
        // Move Child
        aChildInfo->moveChild(aIndex, aTargetIndex);
    } else {
        // Take Child
        ComponentInfo* takenChild = aChildInfo->takeChild(aIndex);

        qDebug() << "ComponentInfo::moveChild - mName: " << takenChild->mName << " -> " << aTargetChildInfo->componentPath() << " - aTargetIndex: " << aTargetIndex;

        // Reset Pos
        takenChild->setPosX(QString("4"));
        takenChild->setPosY(QString("4"));

        // Reset Anchors
        while (!takenChild->mAnchors.empty()) {
            // Remove Last
            takenChild->mAnchors.erase(takenChild->mAnchors.end());
        }

        // Insert Child
        aTargetChildInfo->insertChild(aTargetIndex, takenChild);
    }
}

//==============================================================================
// Take Child Info
//==============================================================================
ComponentInfo* ComponentInfo::takeChild(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mChildren.count()) {
        // Take Child
        ComponentInfo* takenChild = mChildren.takeAt(aIndex);
        // Check Taken Child
        if (takenChild) {
            qDebug() << "ComponentInfo::takeChild - path: " << componentPath() << " - aIndex: " << aIndex;

            // Emit Child About To Be Removed
            emit takenChild->childAboutToBeRemoved(takenChild);

            // Remove Child Object From ID Map
            setChildObjectID(takenChild, "");
            // Set Dirty
            setDirty(true);
            // Emmit Child Removed Signal
            emit childRemoved(aIndex);
            // Emit Child Cound Changed Signal
            emit childCountChanged(mChildren.count());

            return takenChild;
        }
    }

    return NULL;
}

//==============================================================================
// Take Child Info
//==============================================================================
int ComponentInfo::takeChild(ComponentInfo* aChildInfo)
{
    // Get Child Index
    int cIndex = mChildren.indexOf(aChildInfo);
    // Find Index
    if (cIndex >= 0) {
        qDebug() << "ComponentInfo::takeChild - path: " << componentPath() << " - mName: " << aChildInfo->mName;

        // Take Child
        ComponentInfo* takenChild = mChildren.takeAt(cIndex);

        // Remove Child Object From ID Map
        setChildObjectID(takenChild, "");
        // Emit Child About To Be Removed
        emit takenChild->childAboutToBeRemoved(takenChild);

        // Set Dirty
        setDirty(true);

        // Emmit Child Removed Signal
        emit childRemoved(cIndex);
        // Emit Child Cound Changed Signal
        emit childCountChanged(mChildren.count());

        return cIndex;
    }

    return -1;
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

    qDebug() << "ComponentInfo " << componentPath() << " deleted.";
}


