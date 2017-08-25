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
#include "componentstatesmodel.h"
#include "componenttransitionsmodel.h"
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
// Clone Prototype Component Info
//==============================================================================
ComponentInfo* ComponentInfo::clone()
{
    qDebug() << "ComponentInfo::clone - mName: " << mName;
    // Load Children For Proto Type
    loadChildren();
    // Load Animations
    loadAnimations();
    // Load Behaviors
    loadBehaviors();
    // Inc Ref Count
    incRefCount();
    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mCategory, mProject, mBaseName, mBuiltIn, false);
    // Set Proto Type
    newComponent->setProtoType(this);
    // Set Is Root
    newComponent->mIsRoot = false;

    return newComponent;
}

//==============================================================================
// Duplicate Component Info
//==============================================================================
ComponentInfo* ComponentInfo::duplicate()
{
    // Check If Root & Parents
    if (mIsRoot || (mParent == NULL && mTransitionParent == NULL)) {
        return NULL;
    }

    qDebug() << "#### ComponentInfo::duplicate - mName: " << mName;

    // Create Component Info
    ComponentInfo* newComponent = new ComponentInfo(mName, mType, mCategory, mProject, mBaseName, mBuiltIn, false);
    // Set Is Root
    newComponent->mIsRoot = false;
    // Set Parent
    newComponent->mParent = mParent;
    // Set Transition Parent
    newComponent->mTransitionParent = mTransitionParent;
    // Set Base
    newComponent->mBase = mBase;
    // Set ProtoType
    newComponent->mProtoType = mProtoType;

    // Copy Imports
    newComponent->mImports = mImports;
    // Copy Anchors
    newComponent->mAnchors = mAnchors;
    // Copy Own Properties
    newComponent->mOwnProperties = mOwnProperties;
    // Copy Properties
    newComponent->mProperties = mProperties;
    // Copy Signals
    newComponent->mSignals = mSignals;
    // Copy Slots
    newComponent->mSlots = mSlots;
    // Copy Functions
    newComponent->mFunctions = mFunctions;

    // Copy Behaviors
    newComponent->mBehaviors = mBehaviors;
    // Copy Children
    newComponent->mChildren = mChildren;
    // Copy Animations
    newComponent->mAnimations = mAnimations;

    // Copy States
    newComponent->mStates = mStates;
    // Copy Transitions
    newComponent->mTransitions = mTransitions;

    // Set Children Loaded
    newComponent->mChildrenLoaded = mChildrenLoaded;
    // Set Animations Loaded
    newComponent->mAnimationsLoaded = mAnimationsLoaded;
    // Set Behaviors Loaded
    newComponent->mBehaviorsLoaded = mBehaviorsLoaded;

    // Deep Copy Children, Animations, Behaviors

    // ...

    // Check Children Loaded
    if (mChildrenLoaded) {
        // Get Child Components Count
        int ccCount = mChildComponents.count();
        // Iterate Through Child Components
        for (int i=0; i<ccCount; i++) {
            // Append Child Component
            newComponent->mChildComponents << mChildComponents[i]->duplicate();
        }
    }

    // Check If Animations Loaded
    if (mAnimationsLoaded) {
        // Get Animation Components Count
        int acCount = mAnimationComponents.count();
        // Iterate Through Aniamtion Components
        for (int j=0; j<acCount; j++) {
            // Append Animation Components
            newComponent->mAnimationComponents << mAnimationComponents[j]->duplicate();
        }
    }

    // Check Behaviors Loaded
    if (mBehaviorsLoaded) {
        // Get Behavior Components Count
        int bcCount = mBehaviorComponents.count();
        // Iterate Through Behavior Components
        for (int k=0; k<bcCount; k++) {
            // Append Behavior Component
            newComponent->mBehaviorComponents << mBehaviorComponents[k]->duplicate();
        }
    }

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
    , mStatesModel(NULL)
    , mTransitionParent(NULL)
    , mTransitionsModel(NULL)
    , mComponentHandler(NULL)
    , mIsProtoType(aProtoType)
    , mDirty(true)
    , mBuiltIn(aBuiltIn)
    , mLocked(false)
    , mInfoPath("")
    , mName(aName)
    , mType(aType)
    , mTag("")
    , mCategory(aCategory)
    , mBaseName(aBaseName)
    , mUseImplicitPosX(false)
    , mUseImplicitPosY(false)
    , mUseImplicitWidth(false)
    , mUseImplicitHeight(false)
    , mImplicitPosX("-1")
    , mImplicitPosY("-1")
    , mImplicitWidth("-1")
    , mImplicitHeight("-1")
    , mFocused(false)
    , mClosing(false)
    , mLayerVisible(true)
    , mIsRoot(true)
    , mGroupped(false)
    , mChildrenLoaded(false)
    , mAnimationsLoaded(false)
    , mBehaviorsLoaded(false)
    , mRefCount(0)
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
    // Clear Animations
    clearAnimations();
    // Clear Behaviors
    clearBehaviors();

    // Check ProtoType
    if (mProtoType) {
        // Release Reference
        mProtoType->releaseRef();
    }
}

//==============================================================================
// Clear ID Map
//==============================================================================
void ComponentInfo::clearIDMap()
{
    // Check ID Map Count
    if (mIDMap.count() > 0) {
        qDebug() << "ComponentInfo::clearIDMap";
        // Clear ID Map
        mIDMap.clear();
        // Emit Component ID Map Changed
        emit componentIDMapChanged();
    }
}

//==============================================================================
// Clear Children
//==============================================================================
void ComponentInfo::clearChildren()
{
    // Check Child Component Count
    if (mChildComponents.count() > 0) {
        qDebug() << "ComponentInfo::clearChildren - mName: " << mName;

        // Iterate Through Children
        while (mChildComponents.count() > 0) {
            // Take Child Component
            ComponentInfo* takenChild = mChildComponents.takeLast();
            // Check If Proto
            if (!takenChild->mIsProtoType && takenChild->mProtoType) {
                // Dec Ref Count For ProtoType
                takenChild->mProtoType->releaseRef();
            }

            // Delete Taken Child
            delete takenChild;
        }
    }

    // Reset Ref Count
    mRefCount = 0;

    // Reset Children Loaded
    setChildrenLoaded(false);
}

//==============================================================================
// Clear Animations
//==============================================================================
void ComponentInfo::clearAnimations()
{
    // Check Animation Components Count
    if (mAnimationComponents.count() > 0) {
        qDebug() << "ComponentInfo::clearAnimations - mName: " << mName;

        // Iterate Through Animation Components
        while (mAnimationComponents.count() > 0) {
            // Take Animation Component
            ComponentInfo* takenAnimation = mAnimationComponents.takeLast();

            // Check If Proto
            if (!takenAnimation->mIsProtoType && takenAnimation->mProtoType) {
                // Dec Ref Count For ProtoType
                takenAnimation->mProtoType->releaseRef();
            }

            // Delete Taken Animation
            delete takenAnimation;
        }
    }
}

//==============================================================================
// Clear Behaviors
//==============================================================================
void ComponentInfo::clearBehaviors()
{
    // Check Behavior Components Count
    if (mBehaviorComponents.count() < 0) {
        qDebug() << "ComponentInfo::clearBehaviors - mName: " << mName;

        // Iterate Through Animation Components
        while (mBehaviorComponents.count() > 0) {
            // Take Behavior Component
            ComponentInfo* takenBehavior = mBehaviorComponents.takeLast();

            // Delete Taken Behavior
            delete takenBehavior;
        }
    }
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
    // Check File Path
    if (aFilePath.isEmpty() && !mDirty) {
//        qDebug() << "##########################################################";
//        qDebug() << "####                 NOT SAVING!                      ####";
//        qDebug() << "##########################################################";
        // No Need to Save
        return false;
    }

    qDebug() << "ComponentInfo::save - path: " << componentPath();

    // Save Children
    saveChildren();
    // Save Animations
    saveAnimations();
    // Save Behaviors
    saveBehaviors();

    // Save States
    saveStates();
    // Save Transitions
    saveTransitions();

    // Check If Prototype
    if (!mIsProtoType) {
        // Saving Only Prototypes...
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

    qDebug() << "ComponentInfo::save - mName: " << mName << " -> fileName: " << ciFile.fileName();

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

        // Check Component Type
        if (mType == COMPONENT_TYPE_DATASOURCE) {
            // Save Live Data Source
            return saveLiveDataSource();
        }

        return true;
    } else {
        qWarning() << "ComponentInfo::load - mInfoPath: " << mInfoPath << " - ERROR LOADING COMPONENT INFO!";
    }

    return false;
}

//==============================================================================
// Load Children
//==============================================================================
void ComponentInfo::loadChildren()
{
    // Get Children Array Count
    int caCount = mChildren.count();

    // Check Children Loaded
    if (!mChildrenLoaded) {
        // Set Children Loaded
        setChildrenLoaded(true);

        // Check To Create Children
        if (caCount > 0) {
            qDebug() << "ComponentInfo::loadChildren - caCount: " << caCount;

            // Iterate Through Children Array
            for (int i=0; i<caCount; i++) {
                // Get Array Item
                QJsonObject childObject = mChildren[i].toObject();

                // Get Child Component Name
                QString ccName = childObject[JSON_KEY_COMPONENT_NAME].toString();
                // Get Child Component Type
                QString ccType = childObject[JSON_KEY_COMPONENT_TYPE].toString();

                // Get Child Compoennt ProtoType
                ComponentInfo* componentProtoType = mProject ? mProject->getComponentByName(ccName, ccType, true) : NULL;

                // Check Child Component
                if (componentProtoType) {
                    //qDebug() << "ComponentInfo::loadChildren - componentProtoType: " << componentProtoType->mName;
                    // Clone Component
                    ComponentInfo* childComponent = componentProtoType->clone();
                    // Set Parent FIRST!!! Needed for the Recursive call of fromJSONObject
                    childComponent->mParent = this;
                    // Emit Depth Changed Signal
                    emit childComponent->depthChanged(childComponent->depth());
                    // Set Up/Update Child Component from JSON Object
                    childComponent->fromJSONObject(childObject, true);
                    // Reset Dirty State
                    childComponent->setDirty(false);
                    // Add Child
                    addChild(childComponent, true);

                } else {
                    qWarning() << "ComponentInfo::loadChildren - ccName: " << ccName << " - NO COMPONENT!!";
                }
            }
        }
    }
}

//==============================================================================
// Load Animations
//==============================================================================
void ComponentInfo::loadAnimations()
{
    // Get Animations Array Count
    int aaCount = mAnimations.count();

    // Check Animations Loaded
    if (!mAnimationsLoaded) {
        // Set Animations Loaded
        setAnimationsLoaded(true);

        // Check To Create Animations
        if (aaCount > 0) {
            qDebug() << "ComponentInfo::loadAnimations - aaCount: " << aaCount;

            // Iterate Through Animations Array
            for (int i=0; i<aaCount; i++) {
                // Get Array Item
                QJsonObject animObject = mAnimations[i].toObject();

                // Get Anim Component Name
                QString acName = animObject[JSON_KEY_COMPONENT_NAME].toString();
                // Get Anim Component Type
                QString acType = animObject[JSON_KEY_COMPONENT_TYPE].toString();

                // Get Anim Compoennt ProtoType
                ComponentInfo* componentProtoType = mProject ? mProject->getComponentByName(acName, acType, true) : NULL;

                // Check Anim Component
                if (componentProtoType) {
                    //qDebug() << "ComponentInfo::loadAnimations - componentProtoType: " << componentProtoType->mName;
                    // Clone Component
                    ComponentInfo* animComponent = componentProtoType->clone();
                    // Set Parent FIRST!!! Needed for the Recursive call of fromJSONObject
                    animComponent->mParent = this;
                    // Emit Depth Changed Signal
                    emit animComponent->depthChanged(animComponent->depth());
                    // Set Up/Update Anim Component from JSON Object
                    animComponent->fromJSONObject(animObject, true);
                    // Reset Dirty State
                    animComponent->setDirty(false);
                    // Add Anim
                    addChild(animComponent, true);

                } else {
                    qWarning() << "ComponentInfo::fromJSONObject - acName: " << acName << " - NO COMPONENT!!";
                }
            }
        }
    }
}

//==============================================================================
// Load BEhaviors
//==============================================================================
void ComponentInfo::loadBehaviors()
{
    // ...
}

//==============================================================================
// Save Children Components To Children JSON Array
//==============================================================================
void ComponentInfo::saveChildren()
{
    // Init New JSON Array
    QJsonArray newChildArray;

    // Get Children Components Count
    int cCount = mChildComponents.count();

    // Check Children JSON Array Count
    if (mChildren.count() > 0 && !mChildrenLoaded && cCount > 0) {
        qWarning() << "###########################################################################";
        qWarning() << "#### ComponentInfo::saveChildren - CHILD COMPONENTS WERE NOT LOADED!!! ####";
        qWarning() << "###########################################################################";

        // NEVER SHOULD GET HERE!!!

        return;
    }

    // Check Child Components Count
    if (cCount > 0) {
        qDebug() << "ComponentInfo::saveChildren - path: " << componentPath();

        // Iterate Through Children Array
        for (int i=0; i<cCount; i++) {
            // Get Child Info
            ComponentInfo* childInfo = mChildComponents[i];
            // Save Children
            childInfo->saveChildren();
            // Save Animations
            childInfo->saveAnimations();
            // Save Behaviors
            childInfo->saveBehaviors();
            // Append Child
            newChildArray << childInfo->toJSONObject(true);
        }
    }

    // Set Children JSON Array
    mChildren = newChildArray;
}

//==============================================================================
// Save Animations
//==============================================================================
void ComponentInfo::saveAnimations()
{
    // Init New JSON Array
    QJsonArray newAnimsArray;

    // Get Anim Components Count
    int cCount = mAnimationComponents.count();

    // Check Anims JSON Array Count
    if (mAnimations.count() > 0 && !mAnimationsLoaded && cCount > 0) {
        qWarning() << "#################################################################################";
        qWarning() << "#### ComponentInfo::saveAnimations - ANIMATION COMPONENTS WERE NOT LOADED!!! ####";
        qWarning() << "#################################################################################";

        // NEVER SHOULD GET HERE!!!

        return;
    }

    // Check Child Components Count
    if (cCount > 0) {
        qDebug() << "ComponentInfo::saveAnimations - path: " << componentPath() << " - cCount: " << cCount;

        // Iterate Through Children Array
        for (int i=0; i<cCount; i++) {
            // Get Child Info
            ComponentInfo* childInfo = mAnimationComponents[i];
            // Save Animations
            childInfo->saveAnimations();
            // Get JSON Object
            QJsonObject newObject = childInfo->toJSONObject(true);
            // Append Child
            newAnimsArray << newObject;
        }
    }

    // Set Children JSON Array
    mAnimations = newAnimsArray;
}

//==============================================================================
// Save Behaviors
//==============================================================================
void ComponentInfo::saveBehaviors()
{
    // Init New JSON Array
    QJsonArray newBehaviorsArray;

    // Get Behavior Components Count
    int cCount = mBehaviorComponents.count();

    // Check Behaviors JSON Array Count
    if (mBehaviors.count() > 0 && !mBehaviorsLoaded && cCount > 0) {
        qWarning() << "################################################################################";
        qWarning() << "#### ComponentInfo::saveBehaviors - BEHAVIOR COMPONENTS WERE NOT LOADED!!! #####";
        qWarning() << "################################################################################";

        // NEVER SHOULD GET HERE!!!

        return;
    }

    // Check Child Components Count
    if (cCount > 0) {
        qDebug() << "ComponentInfo::saveBehaviors - path: " << componentPath();

        // Iterate Through Children Array
        for (int i=0; i<cCount; i++) {
            // Get Child Info
            ComponentInfo* childInfo = mBehaviorComponents[i];
            // Save Animations
            childInfo->saveAnimations();
            // Append Child
            newBehaviorsArray << childInfo->toJSONObject(true);
        }
    }

    // Set Children JSON Array
    mBehaviors = newBehaviorsArray;
}

//==============================================================================
// Component States
//==============================================================================
void ComponentInfo::saveStates()
{
    // Check Component States Model
    if (mStatesModel) {
        qDebug() << "ComponentInfo::saveStates";

        // Save Component States
        //mStatesModel->saveComponentStates();

        // ...

    }
}

//==============================================================================
// Save Component Transitions
//==============================================================================
void ComponentInfo::saveTransitions()
{
    // Check Component Transitions Model
    if (mTransitionsModel) {
        qDebug() << "ComponentInfo::saveTransitions";

        // Save Component Transitions
        mTransitionsModel->saveComponentTransitions();

        // ...

    }
}


//==============================================================================
// Set Children Loaded
//==============================================================================
void ComponentInfo::setChildrenLoaded(const bool& aChildrenLoaded)
{
    // Check Children Loaded
    if (mChildrenLoaded != aChildrenLoaded) {
        // Set Children Loaded
        mChildrenLoaded = aChildrenLoaded;
        // Emit Children Loaded Changed Signal
        emit childrenLoadedChanged(mChildrenLoaded);
    }
}

//==============================================================================
// Set Animations Loaded
//==============================================================================
void ComponentInfo::setAnimationsLoaded(const bool& aAnimationsLoaded)
{
    // Check Animations Loaded
    if (mAnimationsLoaded != aAnimationsLoaded) {
        // Set Animations Loaded
        mAnimationsLoaded = aAnimationsLoaded;
        // Emit Animations Loaded Changed Signal
        emit animationsLoadedChanged(mAnimationsLoaded);
    }
}

//==============================================================================
// Set Behaviors Loaded
//==============================================================================
void ComponentInfo::setBehaviorsLoaded(const bool& aBehaviorsLoaded)
{
    // Check Beaviors Loaded
    if (mBehaviorsLoaded != aBehaviorsLoaded) {
        // Set Behaviors Loaded
        mBehaviorsLoaded = aBehaviorsLoaded;
        // Emit Behaviors Loaded Changed Signal
        emit behaviorsLoadedChanged(mBehaviorsLoaded);
    }
}

//==============================================================================
// Save Live data Source
//==============================================================================
bool ComponentInfo::saveLiveDataSource()
{
    // Check Project Model
    if (!mProject) {
        return false;
    }

    // Check Type
    if (mType != COMPONENT_TYPE_DATASOURCE) {
        return false;
    }

    // Init Data Source File
    QFile liveDataSourceFile(mProject->liveTempDir() + "/" + DEFAULT_PROJECT_DATASOURCES_DIR_NAME + "/" + mName + ".qml");

    // Open Live Data Source File
    if (liveDataSourceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Init Text Stream
        QTextStream textStream(&liveDataSourceFile);
        // Generate Component Code
        QString content = generateComponentCode();
        // Add To Text Stream
        textStream << content;
        // Flush Text Stream
        textStream.flush();
        // Close Live Data Source File
        liveDataSourceFile.close();

        return true;
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
QObject* ComponentInfo::componentHandler()
{
    return mComponentHandler;
}

//==============================================================================
// Set QML Container
//==============================================================================
void ComponentInfo::setComponentHandler(QObject* aContainer)
{
    // Check Container
    if (mComponentHandler != aContainer) {
        //qDebug() << "ComponentInfo::setComponentContainer - aContainer: " << aContainer;
        // Set QML Container
        mComponentHandler = aContainer;
        // Emit QML Container Changed Signal
        emit componentContainerChanged(mComponentHandler);
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
// Get Closing State
//==============================================================================
bool ComponentInfo::closing()
{
    return mClosing;
}

//==============================================================================
// Set Closing State
//==============================================================================
void ComponentInfo::setClosing(const bool& aClosing)
{
    // Check Closing State
    if (mClosing != aClosing) {
        // Set Closing State Changed
        mClosing = aClosing;
        // Emit Closing State Changed Signal
        emit closingChanged(mClosing);
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
    return "";
//    return mQMLPath;
}

//==============================================================================
// Set QML Source Path
//==============================================================================
void ComponentInfo::setSourcePath(const QString& aPath)
{
    Q_UNUSED(aPath);
//    // Check QML Path
//    if (mQMLPath != aPath) {
//        // Set QML Path
//        mQMLPath = aPath;
//        // Emit Source Path Changed Signal
//        emit sourcePathChanged(mQMLPath);
//    }
}

//==============================================================================
// Get Component ID
//==============================================================================
QString ComponentInfo::componentID()
{
    return mProperties.value(JSON_KEY_COMPONENT_PROPERTY_ID).toString();
}

//==============================================================================
// Set Component ID
//==============================================================================
void ComponentInfo::setComponentID(const QString& aID)
{
    // Check Component ID
    if (componentID() != aID) {
        // Set Component ID Directly to Inherited Properties
        mProperties[JSON_KEY_COMPONENT_PROPERTY_ID] = aID;
        // Set Child Object ID
        setChildObjectID(this, aID);
        // Set Dirty
        setDirty(true);
        // Emit Component ID Changed Signal
        emit componentIDChanged(componentID());
    }
}

//==============================================================================
// Get Object Name
//==============================================================================
QString ComponentInfo::componentObjectName()
{
    return mProperties.value(JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME).toString();
}

//==============================================================================
// Set Object Name
//==============================================================================
void ComponentInfo::setComponentObjectName(const QString& aObjectName)
{
    // Check Object Name
    if (componentObjectName() != aObjectName) {
        // Set Object Name Directly to Inherited Properties
        mProperties[JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME] = aObjectName;
        // Set Dirty
        setDirty(true);
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
    // Check Category
    if (mCategory == "Animation" || mCategory == "Behavior") {
        return;
    }
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
    // Check Category
    if (mCategory == "Animation" || mCategory == "Behavior") {
        return;
    }
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
    // Check Category
    if (mCategory == "Animation" || mCategory == "Behavior") {
        return;
    }
    // Set Component Property
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_Z, aPosZ);
    // Emit Pos Z Changed Signal
    emit posZChanged(posZ());
}

//==============================================================================
// Get Implicit Pos X
//==============================================================================
QString ComponentInfo::implicitPosX()
{
    return mImplicitPosX;
}

//==============================================================================
// Set Implicit Pos X
//==============================================================================
void ComponentInfo::setImplicitPosX(const QString& aIPosX)
{
    // Check Implicit Pos X
    if (mImplicitPosX != aIPosX) {
        // Set Implicit Pos X
        mImplicitPosX = aIPosX;
        // Emit Implicit Pos X Changed Signal
        emit implicitPosXChanged(mImplicitPosX);
    }
}

//==============================================================================
// Get Implicit Pos Y
//==============================================================================
QString ComponentInfo::implicitPosY()
{
    return mImplicitPosY;
}

//==============================================================================
// Set Implicit Pos Y
//==============================================================================
void ComponentInfo::setImplicitPosY(const QString& aIPosY)
{
    // Check Implicit Pos Y
    if (mImplicitPosY != aIPosY) {
        // Set Implicit Pos Y
        mImplicitPosY = aIPosY;
        // Emit Implicit Pos Y Changed Signal
        emit implicitPosYChanged(mImplicitPosY);
    }
}

//==============================================================================
// Get Width
//==============================================================================
QString ComponentInfo::width()
{
    // Check If Using Implicit Width
    if (mUseImplicitWidth) {
        return mImplicitWidth;
    }

    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_WIDTH).toString();
}

//==============================================================================
// Set Width
//==============================================================================
void ComponentInfo::setWidth(const QString& aWidth)
{
    // Check Category
    if (mCategory == "Animation" || mCategory == "Behavior") {
        return;
    }

    //qDebug() << "ComponentInfo::setWidth - aWidth: " << aWidth;

    // Reset Use Implicit Width
    setUseIWidth(false);

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
    // Check If Using Implicit Height
    if (mUseImplicitHeight) {
        return mImplicitHeight;
    }

    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT).toString();
}

//==============================================================================
// Set Height
//==============================================================================
void ComponentInfo::setHeight(const QString& aHeight)
{
    // Check Category
    if (mCategory == "Animation" || mCategory == "Behavior") {
        return;
    }

    //qDebug() << "ComponentInfo::setHeight - aHeight: " << aHeight;

    // Reset Use Implicit Height
    setUseIHeight(false);

    // Set Property - Height
    setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_HEIGHT, aHeight);
    // Emit Height Changed Signal
    emit heightChanged(height());
}

//==============================================================================
// Get Implicit Width
//==============================================================================
QString ComponentInfo::implicitWidth()
{
    return mImplicitWidth;
}

//==============================================================================
// Set Implicit Width
//==============================================================================
void ComponentInfo::setImplicitWidth(const QString& aIWidth)
{
    // Check Implicit Width
    if (mImplicitWidth != aIWidth) {
        //qDebug() << "ComponentInfo::setImplicitWidth - aIWidth: " << aIWidth;
        // Set Implicit Width
        mImplicitWidth = aIWidth;
        // Emit Implicit Width Changed Signal
        emit implicitWidthChanged(mImplicitWidth);
        // Check Use Implicit Width
        if (mUseImplicitWidth) {
            // Emit Width Changed Signal
            emit widthChanged(mImplicitWidth);
        }
    }
}

//==============================================================================
// Get Implicit Height
//==============================================================================
QString ComponentInfo::implicitHeight()
{
    return mImplicitHeight;
}

//==============================================================================
// Set Implicit Height
//==============================================================================
void ComponentInfo::setImplicitHeight(const QString& aIHeight)
{
    // Check Implicit Height
    if (mImplicitHeight != aIHeight) {
        //qDebug() << "ComponentInfo::setImplicitHeight - aIHeight: " << aIHeight;
        // Set Implicit Height
        mImplicitHeight = aIHeight;
        // Emit Implicit Height Changed Signal
        emit implicitHeightChanged(mImplicitHeight);
        // Check Use Implicit Height
        if (mUseImplicitHeight) {
            // Emit Height Changed Signal
            emit heightChanged(mImplicitHeight);
        }
    }
}

//==============================================================================
// Get Use Implicit Pos X
//==============================================================================
bool ComponentInfo::useIPosX()
{
    return mUseImplicitPosX;
}

//==============================================================================
// Set Use Implicit Pos X
//==============================================================================
void ComponentInfo::setUseIPosX(const bool& aUseIPosX)
{
    // Check Use Implicit Pos X
    if (mUseImplicitPosX != aUseIPosX) {
        // Set Use Implicit Pos X
        mUseImplicitPosX = aUseIPosX;
        // Emit Use Implicit Pos X Changed Signal
        emit useIPosXChanged(mUseImplicitPosX);
        // Set Dirty
        setDirty(true);

        // Check Use Implicit Width
        if (mUseImplicitPosX && mProperties.keys().indexOf(JSON_KEY_COMPONENT_PROPERTY_X) >= 0) {
            // Remove Property
            mProperties.remove(JSON_KEY_COMPONENT_PROPERTY_X);
            // Emit Need Refresh
            emit needRefresh();
        }
    }
}

//==============================================================================
// Get Use Implicit Pos Y
//==============================================================================
bool ComponentInfo::useIPosY()
{
    return mUseImplicitPosY;
}

//==============================================================================
// Set Use Implicit Pos Y
//==============================================================================
void ComponentInfo::setUseIPosY(const bool& aUseIPosY)
{
    // Check Use Implicit Pos Y
    if (mUseImplicitPosY != aUseIPosY) {
        // Set Use Implicit Pos Y
        mUseImplicitPosY = aUseIPosY;
        // Emit Use Implicit Pos Y Changed Signal
        emit useIPosYChanged(mUseImplicitPosY);
        // Set Dirty
        setDirty(true);

        // Check Use Implicit Width
        if (mUseImplicitPosY && mProperties.keys().indexOf(JSON_KEY_COMPONENT_PROPERTY_Y) >= 0) {
            // Remove Property
            mProperties.remove(JSON_KEY_COMPONENT_PROPERTY_Y);
            // Emit Need Refresh
            emit needRefresh();
        }
    }
}

//==============================================================================
// Get Use Implicit Width
//==============================================================================
bool ComponentInfo::useIWidth()
{
    return mUseImplicitWidth;
}

//==============================================================================
// Set Use Implicit Width
//==============================================================================
void ComponentInfo::setUseIWidth(const bool& aUseIWidth)
{
    // Check Use Implicit Width
    if (mUseImplicitWidth != aUseIWidth) {
        //qDebug() << "ComponentInfo::setUseIWidth - aUseIWidth: " << aUseIWidth;

        // Set Use Implicit Width
        mUseImplicitWidth = aUseIWidth;
        // Emit Use Implicit Width Changed Signal
        emit useIWidthChanged(mUseImplicitWidth);
        // Set Dirty
        setDirty(true);

        // Check Use Implicit Width
        if (mUseImplicitWidth) {
            // Check If Property Set
            if (mProperties.keys().indexOf(JSON_KEY_COMPONENT_PROPERTY_WIDTH) >= 0) {
                // Remove Property
                mProperties.remove(JSON_KEY_COMPONENT_PROPERTY_WIDTH);
            }

            // Emit Need Refresh
            emit needRefresh();

        } else {
            // Reset Implicit Width
            setImplicitWidth("-1");
        }
    }
}

//==============================================================================
// Get Use Implicit Height
//==============================================================================
bool ComponentInfo::useIHeight()
{
    return mUseImplicitHeight;
}

//==============================================================================
// Set Use Implicit Height
//==============================================================================
void ComponentInfo::setUseIHeight(const bool& aUseIHeight)
{
    // Check Use Implicit Height
    if (mUseImplicitHeight != aUseIHeight) {
        //qDebug() << "ComponentInfo::setUseIHeight - aUseIHeight: " << aUseIHeight;

        // Set Use Implicit Height
        mUseImplicitHeight = aUseIHeight;
        // Emit Use Implicit Height Changed Signal
        emit useIHeightChanged(mUseImplicitHeight);

        // Set Dirty
        setDirty(true);

        // Check Use Implicit Height
        if (mUseImplicitHeight) {
            // Check If Property Set
            if (mProperties.keys().indexOf(JSON_KEY_COMPONENT_PROPERTY_HEIGHT) >= 0) {
                // Clear Property Height
                mProperties.remove(JSON_KEY_COMPONENT_PROPERTY_HEIGHT);
            }

            // Emit Need Refresh
            emit needRefresh();

        } else {
            // Reset Implicit Height
            setImplicitHeight("-1");
        }
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
// Reset Anchors
//==============================================================================
void ComponentInfo::resetAnchors()
{
    //qDebug() << "ComponentInfo::resetAnchors";

    // Reset Anchors
    mAnchors = QJsonObject();

    // Emit Anchors Changed Signals

    // Left Anchor Changed Signal
    emit anchorsLeftChanged("");
    // Left Anchor Margin Changed Signal
    emit anchorsLeftMarginChanged("0");

    // Right Anchor Changed Signal
    emit anchorsRightChanged("");
    // Right Anchor Margin Changed Signal
    emit anchorsRightMarginChanged("0");

    // Top Anchor Changed Signal
    emit anchorsTopChanged("");
    // Top Anchor Margin Changed Signal
    emit anchorsTopMarginChanged("0");

    // Bottom Anchor Changed Signal
    emit anchorsBottomChanged("");
    // Bottom Anchor Margin Changed Signal
    emit anchorsBottomMarginChanged("0");

    // Anchor Margin Changed Signal
    emit anchorsMarginsChanged("0");

    // Fill Anchor Changed Signal
    emit anchorsFillChanged("");

    // Center Anchor Changed Signal
    emit anchorsCenterInChanged("");

    // Horizontal Center Anchor Changed Signal
    emit anchorsHorizontalCenterChanged("");
    // Vertical Center Anchor Changed Signal
    emit anchorsVerticalCenterChanged("");

    // Horizontal Center Anchor Offset Changed Signal
    emit anchorsHorizontalOffsetChanged("0");
    // Vertical Center Anchor Offset Changed Signal
    emit anchorsVerticalOffsetChanged("0");

    // ...


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
// Get Component State
//==============================================================================
QString ComponentInfo::componentState()
{
    return componentProperty(JSON_KEY_COMPONENT_PROPERTY_STATE).toString();
}

//==============================================================================
// Get Component State
//==============================================================================
void ComponentInfo::setComponentState(const QString& aState)
{
    // Check Component state
    if (componentState() != aState) {
        // Set Component State
        setComponentProperty(JSON_KEY_COMPONENT_PROPERTY_STATE, aState);
        // Emit Component State Changed Signal
        emit componentStateChanged(componentState());
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
        // Add Inherited Property Heys
        propertyKeys += mBase->inheritedPropertyKeys();
    }

    // Remove Duplicates
    propertyKeys.removeDuplicates();

    return propertyKeys;
}

//==============================================================================
// Get Proto Type Keys
//==============================================================================
QStringList ComponentInfo::protoTypeKeys()
{
    return mProtoType ? mProtoType->componentOwnPropertyKeys() : QStringList();
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

        // Check Drity
        if (mDirty) {
            qDebug() << "#### ComponentInfo::setDirty - componentPath: " << componentPath() << " IS DIRTY! ####";
        }

        // Emit Dirty Changed Signal
        emit dirtyChanged(mDirty);

        // Check If Dirty
        if (mDirty) {
            // Check Parent
            if (mParent) {
                // Set Dirty
                mParent->setDirty(true);
            }

            // Check Transition Parent
            if (mTransitionParent) {
                // Set Dirty
                mTransitionParent->setDirty(true);
            }

        } else {
            // Get Children Count
            int cCount = childCount();
            // Iterate Through Children
            for (int i=0; i<cCount; i++) {
                // Reset Dirty State
                childInfo(i)->setDirty(false);
            }
            // Get Animations Count
            int aCount = animsCount();
            // Iterate Through Animations
            for (int j=0; j<aCount; j++) {
                // Reset Dirty State
                animInfo(j)->setDirty(false);
            }
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

    // Check Tag
    if (!mTag.isEmpty()) {
        // Set Component Tag
        ciObject[JSON_KEY_COMPONENT_TAG] = QJsonValue(mTag);
    }

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
    if (mUseImplicitPosX) {
        // Set Use Implicit Pos X
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSX] = QJsonValue(mUseImplicitPosX);
    }

    // Check Use Implicit Pos Y
    if (mUseImplicitPosY) {
        // Set Use Implicit Pos Y
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_POSY] = QJsonValue(mUseImplicitPosY);
    }

    // Check Use Implicit Width
    if (mUseImplicitWidth) {
        // Set Use Implicit Width
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_WIDTH] = QJsonValue(mUseImplicitWidth);
    }

    // Check Use Implicit Height
    if (mUseImplicitHeight) {
        // Set Use Implicit Height
        ciObject[JSON_KEY_COMPONENT_USE_IMPLICIT_HEIGHT] = QJsonValue(mUseImplicitHeight);
    }

    // Check Anchors
    if (!mAnchors.isEmpty()) {
        // Set Anchors
        ciObject[JSON_KEY_COMPONENT_ANCHORS] = mAnchors;
    }

    // Check Behaviors
    if (!mBehaviors.isEmpty()) {
        // Set Behaviors
        ciObject[JSON_KEY_COMPONENT_BEHAVIORS] = mBehaviors;
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

    // Check Child Array
    if (!mChildren.isEmpty()) {
        // Set Children
        ciObject[JSON_KEY_COMPONENT_CHILDREN] = mChildren;
    }

    // Check Animations Array
    if (!mAnimations.isEmpty()) {
        // Set Animations
        ciObject[JSON_KEY_COMPONENT_ANIMATIONS] = mAnimations;
    }

    // Check Behaviors Array
    if (!mBehaviors.isEmpty()) {
        // Set Behaviors
        ciObject[JSON_KEY_COMPONENT_BEHAVIORS] = mBehaviors;
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
    // Set Behaviors
    mBehaviors = aObject[JSON_KEY_COMPONENT_BEHAVIORS].toArray();
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
    // Children
    mChildren = aObject[JSON_KEY_COMPONENT_CHILDREN].toArray();
    // Animations
    mAnimations = aObject[JSON_KEY_COMPONENT_ANIMATIONS].toArray();
    // Behaviors
    mBehaviors = aObject[JSON_KEY_COMPONENT_BEHAVIORS].toArray();

    // Check If Load Children
    if (aCreateChildren) {
        // Load Children
        loadChildren();
        // Load Animations
        loadAnimations();
        // Load Behaviors
        loadBehaviors();
    }

    // ...
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
    qDebug() << "ComponentInfo::removeFromParent - componentPath: " << componentPath();

    // Check Parent
    if (mParent) {
        qDebug() << "ComponentInfo::removeFromParent - child";
        // Remove Child
        mParent->removeChild(this);
        return;
    }

    // Check Transition Parent
    if (mTransitionParent) {
        qDebug() << "ComponentInfo::removeFromParent - transition node";
        // Remove Node
        mTransitionParent->removeNode(this);

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
        // Emit Component ID Map Changed Signal
        emit componentIDMapChanged();
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
        // Emit Component ID Map Changed Signal
        emit componentIDMapChanged();

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
// Get Index
//==============================================================================
int ComponentInfo::getChildIndex()
{
    // Check Parent
    if (!mParent) {
        return -1;
    }

    return mParent->mChildComponents.indexOf(this);
}

//==============================================================================
// Get Global Child Index Map
//==============================================================================
QString ComponentInfo::getGlobalChildIndexMap()
{
    // Check Root
    if (mIsRoot) {
        return mName;
    }

    // Init Global Child Index Map
    QString gciMap = "";

    // Check Parent
    if (mParent) {
        // Get Child Index
        int cIndex = getChildIndex();
        // Set Global Child Index Map
        gciMap = QString("%1.%2").arg(mParent->getGlobalChildIndexMap()).arg(cIndex);
    }

    return gciMap;
}

//==============================================================================
// Generate Component ID
//==============================================================================
QString ComponentInfo::liveCodeGenerateID(const bool& aLiveRoot)
{
    // Get Component ID
    QString cID = componentID();//componentProperty(JSON_KEY_COMPONENT_PROPERTY_ID).toString();

    // Check ID
    if (cID.isEmpty() && aLiveRoot) {
        // Set Component ID
        cID = mName;
        // Lower First Char
        cID[0] = cID[0].toLower();
        // Set ID
        cID += "Root";
    }

    return cID;
}

//==============================================================================
// Format Imports
//==============================================================================
QString ComponentInfo::liveCodeFormatImports()
{
    // Init Live Code
    QString liveCode = "";

    // Append Imports
    liveCode += QString("import QtQuick 2.7\n");

//    // Add Live Temp
//    liveCode += QString("import \"%1\"\n").arg(mProject->liveTempDir());

    // Get Imports Count
    int iCount = mImports.count();

    // Check Imports Count
    if (iCount > 0) {
        // Iterate Through Imports
        for (int i=0; i<iCount; i++) {
            // Append Imports
            liveCode += QString("import %1\n").arg(mImports[i].toString());
        }
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

    // Add Name
    liveCode += QString("%1%2 {\n").arg(aIndent).arg(mIsRoot && !mBuiltIn? mBaseName : mName);

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
    if (mCategory != COMPONENT_CATEGORY_NONVISUAL && mCategory != COMPONENT_CATEGORY_ANIMATION) {
        // Get Pos X
        QString cpX = posX();
        // Check Pos X
        if (!mUseImplicitPosX && !cpX.isEmpty() && cpX.toInt() != 0) {
            // Add Pos X
            liveCode += QString("%1x: %2\n").arg(aIndent).arg(cpX);
        }

        // Get Pos Y
        QString cpY = posY();
        // Check Pos Y
        if (!mUseImplicitPosY && !cpY.isEmpty() && cpY.toInt() != 0) {
            // Add Pos Y
            liveCode += QString("%1y: %2\n").arg(aIndent).arg(cpY);
        }

        // Get Pos Z
        QString cpZ = posZ();
        // Check Pos Z
        if (!cpZ.isEmpty() && cpZ.toDouble() != 0.0) {
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
    if (mCategory != COMPONENT_CATEGORY_NONVISUAL && mCategory != COMPONENT_CATEGORY_ANIMATION ) {
        // Get Width
        QString cWidth = width();
        // Check Width
        if (!mUseImplicitWidth && !cWidth.isEmpty() && cWidth != "0") {
            // Add Width
            liveCode += QString("%1width: %2\n").arg(aIndent).arg(cWidth);
        }

        // Get Height
        QString cHeight = height();
        // Check Height
        if (!mUseImplicitHeight && !cHeight.isEmpty() && cHeight != "0") {
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
QString ComponentInfo::liveCodeFormatOwnProperties(QStringList& aOPHooks,
                                                   QStringList& aEnumHooks,
                                                   QStringList& aPCHookList,
                                                   const QString& aID,
                                                   const QStringList& aFPKeys,
                                                   const QString& aIndent,
                                                   const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Get Own Properties Keys
    QStringList opKeys = mOwnProperties.keys();
    //QStringList opKeys = componentOwnPropertyKeys();
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

            //qDebug() << "ComponentInfo::liveCodeFormatOwnProperties - mName: " << mName << " - pName: " << pName;

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
                QString pValue = Utils::parseValue(typeAndValue, true);
                // Init Value Is Binding/Formula
                bool pIsBinding = (pValue[0] == QChar(16));

                // TODO: Handle Formulas And Bindigs!!!

                if (pIsBinding) {
                    // Remove Char Code 16
                    pValue = pValue.mid(1);
                }

                // Check Type
                if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING) {
                    // Set Value
                    pValue = QString("\"%1\"").arg(pValue);
                }

                // Check Inherited Property Keys
                if (pKeys.indexOf(pName) == -1) {
                    // Check If Built In Component
                    if (mBuiltIn && mIsProtoType) {
                        // Check If Read Only
                        if (!readOnly && !pValue.isEmpty()) {
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

                    // Check Proprty Name
                    if (!aComponentCode && opKeys[i].indexOf(".") == -1) {
                        // Init Property Change Slot Name
                        QString pcSlotName = QString("on%1Changed").arg(opKeys[i]);
                        // UpperCase 3rd Char
                        pcSlotName[2] = pcSlotName[2].toUpper();
                        // Add To Property Change Hook List
                        aPCHookList << pcSlotName;
                    }
                }

                // Check Component Code
                if (!aComponentCode) {
                    // Check Property Type
                    if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM) {
                        // Add Enum Values to Enum Hooks
                        aEnumHooks << liveCodeGenerateEnumValueCases(propertyEnums(pName), aIndent);
                        // Check ID
                        if (aID.isEmpty()) {
                            // Value Setting Hook
                            aOPHooks << QString("%1%2%2case \"%3\": %3 = __string2enum(value); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName);
                        } else {
                            // Value Setting Hook
                            aOPHooks << QString("%1%2%2case \"%3\": %4.%3 = __string2enum(value); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName).arg(aID);
                        }

                    } else {
                        // Check If Read Only
                        if (!readOnly) {
                            // Check ID
                            if (aID.isEmpty()) {
                                // Add Value Setting Hook
                                aOPHooks << QString("%1%2%2case \"%3\": %3 = value; break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName);
                            } else {
                                // Add Value Setting Hook
                                aOPHooks << QString("%1%2%2case \"%3\": %4.%3 = value; break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName).arg(aID);
                            }
                        }
                    }
                }
            }
        }
    }

    return liveCode;
}

//==============================================================================
// Format Properties
//==============================================================================
QString ComponentInfo::liveCodeFormatInheritedProperties(QStringList& aPHooks,
                                                         QStringList& aEnumHooks,
                                                         QStringList& aPCHookList,
                                                         const QString& aID,
                                                         const QStringList& aFPKeys,
                                                         const QString& aIndent,
                                                         const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Get All Inherited Properties Keys
    QStringList pKeys = inheritedPropertyKeys();
    // Add Proto Type Keys
    pKeys << protoTypeKeys();
    // Remove Duplicates
    pKeys.removeDuplicates();

    // Get Properties Count
    int pCount = pKeys.count();

    // Check Inherited Properties Keys Count
    if (pCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Iterate Through Property Keys
        for (int k=0; k<pCount; k++) {
            // Get Property Name
            QString pName = pKeys[k];

            //qDebug() << "ComponentInfo::liveCodeFormatInheritedProperties - mName: " << mName << " - pName: " << pName;

            // Get Type
            QString pType = propertyType(pName);
            // Init ReadOnly
            bool readOnly = pType.indexOf(JSON_VALUE_PROPERTY_TYPE_PREFIX_READONLY) >= 0;
            // Get Value
            QString pValue = componentProperty(pName).toString();
            // Init Value Is Binding/Formula
            bool pIsBinding = (pValue[0] == QChar(16));

            // Check readOnly
            if (!readOnly) {
                // Check Key
                if (aFPKeys.indexOf(pName) == -1 /*&& mProperties.keys().indexOf(pName) != -1*/) {
                    // Check If Binding
                    if (pIsBinding) {
                        // Remove Char 16
                        pValue = pValue.mid(1);
                    // Check For String Type
                    } else if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING /*&& !pValue.isEmpty()*/) {
                        // Set Value
                        pValue = QString("\"%1\"").arg(pValue);
                    }

                    // Check Value
                    if (!pValue.isEmpty()) {
                        // Append Live Code
                        liveCode += QString("%1%2: %3\n").arg(aIndent).arg(pName).arg(pValue);
                    }
                }

                // Check Property Key
                if (pName != JSON_KEY_COMPONENT_PROPERTY_ID && !aComponentCode) {

                    // Check Property Type
                    if (pType == JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM) {

                        // Add Enum Values To Enum Hooks
                        aEnumHooks << liveCodeGenerateEnumValueCases(propertyEnums(pName), aIndent);

                        // Check ID
                        if (aID.isEmpty()) {
                            // Add Value Setting Hook
                            aPHooks << QString("%1%2%2case \"%3\": %3 = __string2enum(value); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName);
                        } else {
                            // Add Value Setting Hook
                            aPHooks << QString("%1%2%2case \"%3\": %4.%3 = __string2enum(value); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName).arg(aID);
                        }

                    } else {
                        // Check ID
                        if (aID.isEmpty()) {
                            // Add Value Setting Hook
                            aPHooks << QString("%1%2%2case \"%3\": %3 = value; break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName);
                        } else {
                            // Add Value Setting Hook
                            aPHooks << QString("%1%2%2case \"%3\": %4.%3 = value; break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName).arg(aID);
                        }
                    }
                }
            }

            // TODO: Handle Property Changes -> PropertyChanged Slot

            // Check Proprty Name
            if (!aComponentCode && aFPKeys.indexOf(pName) == -1 && pName.indexOf(".") == -1) {
                // Init Property Change Slot Name
                QString pcSlotName = QString("on%1Changed").arg(pName);
                // UpperCase 3rd Char
                pcSlotName[2] = pcSlotName[2].toUpper();
                // Add To Property Change Hook List
                aPCHookList << pcSlotName;
            }
        }

        // Add New Line
        liveCode += "\n";
    }

    return liveCode;
}

//==============================================================================
// Format Signals
//==============================================================================
QString ComponentInfo::liveCodeFormatSignals(const QString& aIndent)
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

    // ...

    return liveCode;
}

//==============================================================================
// Format Slots
//==============================================================================
QString ComponentInfo::liveCodeFormatSlots(const QStringList& aPCHookList,
                                           const QString& aIndent,
                                           const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Init Used Property Change Hook Slot Names
    QStringList upchList = QStringList();

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
            // Init Slot Source
            QString slotSource = "";

            // Add To Live Code
            liveCode += QString("%1%2: {\n").arg(aIndent).arg(slotName);

            // Get Property Change Hook Lost Index
            int pchlIndex = aPCHookList.indexOf(slotName);

            // Check Slot Hook List
            if (pchlIndex != -1 && !aComponentCode) {
                // Get Property Name From Property Change Slot Name
                QString pName = aPCHookList[pchlIndex].mid(2);
                // Lower Case First Char
                pName[0] = pName[0].toLower();
                // Cut Of Changed Parth
                pName = pName.left(pName.length() - 7);

                // Set Slot Source
                slotSource += QString("%1%2property__Changed(\"%3\", %3);\n\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(pName);
                // Add User Slot Source
                slotSource += slotObject.value(JSON_KEY_COMPONENT_SLOT_SOURCE).toString();

                // Add To Used Property Change Hook List
                upchList << slotName;
            } else {

                // Get Source
                slotSource = slotObject.value(JSON_KEY_COMPONENT_SLOT_SOURCE).toString();

            }

            // Add Slot Source
            liveCode += slotSource.trimmed();
            // Add Line Break;
            liveCode += "\n";

            // Add Closing Bracket
            liveCode += QString("%1}\n\n").arg(aIndent);
        }
    }

    if (!aComponentCode) {
        // Get Property Change Hook List Count
        int pchlCount = aPCHookList.count();

        // Check Count
        if (pchlCount > 0) {
            // Add New Line
            liveCode += "\n";

            // Add Comment
            liveCode += QString("%1// Property Change Hook Slots\n").arg(aIndent);


            // Iterate Through Property Change Hook List
            for (int m=0; m<pchlCount; m++) {
                // Check If Not Used Already
                if (upchList.indexOf(aPCHookList[m]) == -1) {
                    // Get Property Name From Property Change Slot Name
                    QString pName = aPCHookList[m].mid(2);
                    // Lower Case First Char
                    pName[0] = pName[0].toLower();
                    // Cut Of Changed Parth
                    pName = pName.left(pName.length() - 7);
                    // Add To Live Code
                    liveCode += QString("%1%2: property__Changed(\"%3\", %3);\n").arg(aIndent).arg(aPCHookList[m]).arg(pName);
                }
            }
        }
    }

    return liveCode;
}

//==============================================================================
// Format Hooks
//==============================================================================
QString ComponentInfo::liveCodeFormatHooks(const QStringList& aOPHooks, const QStringList& aPHooks, const QStringList& aEnumHooks, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Add Property Changed Signal =============================================

    // Check Properties
    if (aOPHooks.count() > 0 || aPHooks.count() > 0) {
        // Add New Line
        liveCode += "\n";

        // Add Comment Line
        liveCode += QString("%1// Property Changed Signal for All Property Changes\n").arg(aIndent);
        // Add Property Changed Signal
        liveCode += QString("%1signal property__Changed(var aKey, var aValue)\n").arg(aIndent);
    }

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
        enumValueFunction += QString("%1%2switch (value) {\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);
        // Add Default Value Case
        enumValueFunction += QString("%1%2%2default: console.log(\"__string2enum value:\" + value + \" IS NOT DEFINED!\"); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

        // Iterate Through Enum Value Hooks
        for (int eh=0; eh<evhCount; eh++) {
            // Add Enum Value Case Line
            enumValueFunction += aEnumHooks[eh];
        }

        // Add Switch Closing Bracket
        enumValueFunction += QString("%1%2}\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);
        // Add Final Bracket
        enumValueFunction += QString("%1}\n").arg(aIndent);

        liveCode += enumValueFunction;

        // Add New Line
        //liveCode += "\n";
    }

    // Add Value Setting Hooks =================================================

    // Get Own Property Value Hook's Count
    int opvhCount = aOPHooks.count();
    // Get Inherited Properties Value Hook's Count
    int pvhCount = aPHooks.count();

    // Check Properties Count
    if ((opvhCount > 0 || pvhCount > 0)) {
        // Add New Line
        liveCode += "\n";
        // Comment Line
        liveCode += QString("%1// Property Set Hook\n").arg(aIndent);
        // Init Property Update Hook Function Code
        QString propertyHooks = QString("%1function __setProperty(key, value) {\n").arg(aIndent);
        // Add Console Log
        propertyHooks += QString("%1%2console.log(\"__setProperty - key: \" + key + \" - value: \" + value);\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);
        // Add Key Switch
        propertyHooks += QString("%1%2switch (key) {\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);
        // Add Default Hook
        propertyHooks += QString("%1%2%2default: console.log(\"__setProperty property:\" + key + \" IS NOT DEFINED!\"); break;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

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
        propertyHooks += QString("%1%2}\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);
        // Add Final Bracket
        propertyHooks += QString("%1}\n").arg(aIndent);

        // Append Property Hooks To Live Code
        liveCode += propertyHooks;

        // Add New Line
        liveCode += "\n";
    }

    return liveCode;
}

//==============================================================================
// Format Functions
//==============================================================================
QString ComponentInfo::liveCodeFormatFunctions(const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

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
QString ComponentInfo::liveCodeFormatChildren(const QString& aIndent, const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Get Number Of Children
    int cCount = mChildComponents.count();

    // Check Children
    if (cCount > 0) {
        // Add Comment
        liveCode += QString("\n%1// Children\n\n").arg(aIndent);
        // Iterate Through Children
        for (int i=0; i<cCount; i++) {
            // Get Child Object
            liveCode += mChildComponents[i]->generateLiveCode(false, true, aIndent, aComponentCode);
            // Add New Line
            liveCode += "\n";
        }
    }

    return liveCode;
}

//==============================================================================
// Format Animations
//==============================================================================
QString ComponentInfo::liveCodeFormatAnimations(const QString& aIndent, const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Get Number Of Animations
    int acCount = mAnimationComponents.count();

    // Check Animations Count
    if (acCount > 0) {
        // Add Comment
        liveCode += QString("\n%1// Animations\n\n").arg(aIndent);
        // Iterate Through Children
        for (int i=0; i<acCount; i++) {
            // Get Child Object
            liveCode += mAnimationComponents[i]->generateLiveCode(false, true, aIndent, aComponentCode);
            // Add New Line
            liveCode += "\n";
        }
    }

    return liveCode;
}

//==============================================================================
// Format Behaviors
//==============================================================================
QString ComponentInfo::liveCodeFormatBehaviors(const QString& aIndent, const bool& aComponentCode)
{
    // Init Live Code
    QString liveCode = "";

    // Get Number Of Behaviors
    int bcCount = mBehaviorComponents.count();

    // Check Animations Count
    if (bcCount > 0) {
        // Add Comment
        liveCode += QString("\n%1// Behaviors\n\n").arg(aIndent);
        // Iterate Through Children
        for (int i=0; i<bcCount; i++) {
            // Get Child Object
            liveCode += mBehaviorComponents[i]->generateLiveCode(false, true, aIndent, aComponentCode);
            // Add New Line
            liveCode += "\n";
        }
    }

    return liveCode;
}

//==============================================================================
// Format States
//==============================================================================
QString ComponentInfo::liveCodeFormatState(const int& aIndex, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Get State Object
    QJsonObject stateObject = mStates[aIndex].toObject();

    // Add Opening To Live Code
    liveCode += QString("%1%2State {\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

    // Add Name
    liveCode += QString("%1%2%2name: \"%3\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(stateObject[JSON_KEY_COMPONENT_STATE_NAME].toString());

    // Check When
    if (stateObject.keys().indexOf(JSON_KEY_COMPONENT_STATE_WHEN) >= 0) {
        // Add When
        liveCode += QString("%1%2%2when: %3\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(stateObject[JSON_KEY_COMPONENT_STATE_WHEN].toString());
    }

    // Get Property Changes
    QJsonArray propertyChanges = stateObject[JSON_KEY_COMPONENT_STATE_PROPERTY_CHANGES].toArray();
    // Get Count
    int pcCount = propertyChanges.count();
    // Iterate Through Property Changes
    for (int i=0; i<pcCount; i++) {
        // Get Property Change Object
        QJsonObject pcObject = propertyChanges[i].toObject();

        // Add Property Change
        liveCode += QString("%1%2%2PropertyChanges { target: %3; %4: %5 }\n").arg(aIndent)
                                                                             .arg(DEFAULT_SOURCE_INDENT)
                                                                             .arg(pcObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET].toString())
                                                                             .arg(pcObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY].toString())
                                                                             .arg(pcObject[JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE].toString());
    }

    // Add Closing Bracket To Live Code
    liveCode += QString("%1%2}").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

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

        // Add Comment
        liveCode += QString("%1// States\n").arg(aIndent);

        // Add States To Live Code
        liveCode += QString("%1states: [\n").arg(aIndent);

        // Get States Count
        int sCount = mStates.count();
        // Iterate Through States
        for (int i=0; i<sCount; i++) {
            // Format State
            liveCode += liveCodeFormatState(i, aIndent);
            // Check Count & Index
            if (sCount > 1 && i < (sCount - 1)) {
                // Append Comma And New Line
                liveCode += QString(",\n\n");
            } else {
                liveCode += QString("\n");
            }
        }

        // Add To Live Code
        liveCode += QString("%1]\n\n").arg(aIndent);
    }

    return liveCode;
}

//==============================================================================
// Format Transition Node
//==============================================================================
QString ComponentInfo::liveCodeFormatTransitionNode(const QJsonObject& aTransitionNode, const QString& aIndent)
{
    // Check Transition Object
    if (aTransitionNode.isEmpty()) {
        return "";
    }

    // Init Live Code
    QString liveCode = "";

    // Get Transition Node Name
    QString tnName = aTransitionNode.value(JSON_KEY_COMPONENT_NAME).toString();

    // Check Name
    if (tnName.isEmpty()) {
        return "";
    }

    // Get Transition Node Type
    QString tnType = aTransitionNode.value(JSON_KEY_COMPONENT_TYPE).toString();

    // Get Proto Type
    ComponentInfo* tnProto = mProject->getComponentByName(tnName, tnType);

    // Check Proto Type
    if (!tnProto) {
        return "";
    }


    // Add Node Name
    liveCode += QString("%1%2%3 {\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(tnName);

    // Get Node Compoennt Info Properties
    QJsonObject tnicProperties = aTransitionNode.value(JSON_KEY_COMPONENT_PROPERTIES).toObject();

    // Add Target ==============================================================

    // Get Target
    QString tnTarget = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TARGET).toString();
    // Check target
    if (!tnTarget.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TARGET).arg(tnTarget);
    }

    // Add Properties ==========================================================

    // Get Properties
    QString tnProperties  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTIES).toString();
    // Check Properties
    if (tnProperties.isEmpty()) {
        // Get Proto Properties
        tnProperties = tnProto->propertyValue(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTIES).toString();
    }

    // Check Properties
    if (!tnProperties.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: \"%4\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTIES).arg(tnProperties);
    }

    // Add Property ============================================================

    // Get Property
    QString tnProperty  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTY).toString();

    // Check Property
    if (tnProperty.isEmpty()) {
        // Get Property From Proto
        tnProperty = tnProto->propertyValue(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTY).toString();
    }

    // Check Property
    if (!tnProperty.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: \"%4\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTY).arg(tnProperty);
    }

    // Add Value ===============================================================

    // Get Value
    QString tnValue  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_VALUE).toString();
    // Check Value
    if (!tnValue.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_VALUE).arg(tnValue);
    }

    // Add From Value ==========================================================

    // Get From Value
    QString tnFromValue  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_FROM).toString();
    // Check From Value
    if (!tnFromValue.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_FROM).arg(tnFromValue);
    }

    // Add To Value ============================================================

    // Get To Value
    QString tnToValue  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TO).toString();
    // Check To Value
    if (!tnToValue.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TO).arg(tnToValue);
    }

    // Add Duration ============================================================

    // Get Duration
    QString tnDuration  = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_DURATION).toString();

    // Check Duration
    if (tnDuration.isEmpty()) {
        // Get Duration From Proto
        tnDuration = tnProto->propertyValue(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_DURATION).toString();
    }

    // Check Duration
    if (!tnDuration.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_DURATION).arg(tnDuration);
    }

    // Add Easing Type =========================================================

    // Get Easing Type
    QString tnEasingType = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_TYPE).toString();
    // Check Easing Type
    if (!tnEasingType.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_TYPE).arg(tnEasingType);
    }

    // Add Easing Curve ========================================================

    // Get Easing Curve
    QString tnEasingCurve = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_CURVE).toString();
    // Check Easing Curve
    if (!tnEasingCurve.isEmpty()) {
        // Add To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_CURVE).arg(tnEasingCurve);
    }

    // Add Script ==============================================================

    // Get Script
    QString tnScript = tnicProperties.value(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_SCRIPT).toString();
    // Check Script
    if (!tnScript.isEmpty()) {
        // Add Script To Live Code
        liveCode += QString("%1%2%2%3: %4\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(JSON_KEY_COMPONENT_PROPERTY_TRANSITION_SCRIPT).arg(tnScript);
    }

    // Get Child Animation Nodes
    QJsonArray transitionNodes = aTransitionNode.value(JSON_KEY_COMPONENT_ANIMATIONS).toArray();

    // Get Nodes Count
    int tnCount = transitionNodes.count();
    // Iterate Through Nodes
    for (int i=0; i<tnCount; i++) {
        // Format Node
        liveCode += liveCodeFormatTransitionNode(transitionNodes[i].toObject(), aIndent + DEFAULT_SOURCE_INDENT);
        // Check Count & Index
        if (tnCount > 1 && i < (tnCount - 1)) {
            // Append Comma And New Line
            liveCode += QString("\n\n");
        } else {
            liveCode += QString("\n");
        }
    }

    liveCode += QString("%1%2}").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

    return liveCode;
}

//==============================================================================
// Format Transition
//==============================================================================
QString ComponentInfo::liveCodeFormatTransition(const int& aIndex, const QString& aIndent)
{
    // Init Live Code
    QString liveCode = "";

    // Get Transition Object
    QJsonObject transitionObject = mTransitions[aIndex].toObject();

    // Add Opening To Live Code
    liveCode += QString("%1%2Transition {\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

    // Get From State
    QString fromState = transitionObject.value(JSON_KEY_COMPONENT_TRANSITION_FROM).toString();

    // Check From State
    if (!fromState.isEmpty()) {
        // Add From State
        liveCode += QString("%1%2%2from: \"%3\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(fromState);
    }

    // Get To State
    QString toState = transitionObject.value(JSON_KEY_COMPONENT_TRANSITION_TO).toString();

    // Check To State
    if (!toState.isEmpty()) {
        // Add To State
        liveCode += QString("%1%2%2to: \"%3\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(toState);
    }

    // Add Nodes

    // Get Nodes
    QJsonArray transitionNodes = transitionObject.value(JSON_KEY_COMPONENT_TRANSITION_NODES).toArray();

    // Get Nodes Count
    int tnCount = transitionNodes.count();

    // Check Nodes Count
    if (tnCount > 0) {
        // Add New Line
        liveCode += "\n";

        // Iterate Through Nodex
        for (int i=0; i<tnCount; i++) {
            // Generate Live Code
            liveCode += liveCodeFormatTransitionNode(transitionNodes[i].toObject(), aIndent + DEFAULT_SOURCE_INDENT);
            // Check Count & Index
            if (tnCount > 1 && i < (tnCount - 1)) {
                // Append Comma And New Line
                liveCode += QString("\n\n");
            } else {
                liveCode += QString("\n");
            }
        }
    }

    // ...

    // Add Closing Bracket To Live Code
    liveCode += QString("%1%2}").arg(aIndent).arg(DEFAULT_SOURCE_INDENT);

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

        // Add Comment
        liveCode += QString("%1// Transitions\n").arg(aIndent);

        // Add To Live Code
        liveCode += QString("%1transitions: [\n").arg(aIndent);

        // Get Transitions Count
        int tCount = mTransitions.count();
        // Iterate Through Transitions
        for (int i=0; i<tCount; i++) {
            // Format State
            liveCode += liveCodeFormatTransition(i, aIndent);
            // Check Count & Index
            if (tCount > 1 && i < (tCount - 1)) {
                // Append Comma And New Line
                liveCode += QString(",\n\n");
            } else {
                liveCode += QString("\n");
            }
        }

        // Add To Live Code
        liveCode += QString("%1]\n\n").arg(aIndent);
    } else {

        // TEMPORARY

        // Check States
        if (!mStates.isEmpty()) {

            liveCode += QString("%1transitions: Transition {\n%1%2PropertyAnimation { properties: \"width, height\"; duration: %3 }\n%1}\n\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(200);

        }

        // TEMPORARY

    }

    return liveCode;
}

//==============================================================================
// Generate Enum Value Live Code Cases
//==============================================================================
QStringList ComponentInfo::liveCodeGenerateEnumValueCases(const QStringList& aEnumValues, const QString& aIndent)
{
    // Init Live Enum Cases
    QStringList enumLiveCases = QStringList();

    // Get Enum Values Count
    int evCount = aEnumValues.count();
    // Iterate Through Enum Values
    for (int i=0; i<evCount; i++) {
        // Init Enum Value Case Line
        QString evLine = QString("%1%2%2case \"%3\": return %3;\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(aEnumValues[i]);

        //qDebug() << "ComponentInfo::liveCodeGenerateEnumValuecases - aEnumValues[" << i << "]: " << aEnumValues[i] <<  " -> " << evLine;

        // Append To live Enum Cases
        enumLiveCases << evLine;
    }

    return enumLiveCases;
}

//==============================================================================
// Generate Live Code for Designer
//==============================================================================
QString ComponentInfo::generateLiveCode(const bool& aLiveRoot, const bool& aGenerateChildren, const QString& aIndent, const bool& aComponentCode)
{
    // Check Project Model
    if (!mProject) {
        qWarning() << "ComponentInfo::generateLiveCode - NO PROJECT MODEL!!";
        return "";
    }

    // Check Child Count
    if (mIsRoot) {
        // Generate Component Code First
        mProject->generateComponentCode(mBase, aGenerateChildren);

    } else {
        // Get Component ProtoType
        ComponentInfo* proto = mProject->getComponentByName(mName, mType);
        // Check Proto
        if (proto) {
            // Generate Component Code
            mProject->generateComponentCode(proto, true);
        } else {
            qWarning() << "ComponentInfo::generateLiveCode - mName: " << mName << " - NO PROTOTYPE COMPONENT!!";
            // NO PROTOTYPE!!!
            return "";
        }
    }

    qDebug() << "ComponentInfo::generateLiveCode - path: " << componentPath() << " - aLiveRoot: " << aLiveRoot << " - aGenerateChildren: " << aGenerateChildren;

    // Init Live Code
    QString liveCode = QString("%1// Component: %2\n").arg(aIndent).arg(componentPath());
//    // Init Indent Level
//    int indentLevel = 0;
    // Init Current Indent
    QString indent = aIndent;
//    // Fill
//    indent.fill(' ', indentLevel * 4);

    // Add Imports =============================================================

    // Check If Live Root
    if (aLiveRoot) {
        liveCode += liveCodeFormatImports();
    }

    // Add Name ================================================================

    // Get Component Name
    QString clName = liveCodeFormatName(indent);

    // Check Component Name Line
    if (clName.isEmpty()) {
        qCritical() << "ComponentInfo::generateLiveCode - INVALID COMPONENT NAME!!!";
    }

    liveCode += clName;

    // Inc Indent
    indent += DEFAULT_SOURCE_INDENT;

//    // Inc Indent Level
//    indentLevel++;
//    // Increase Indent
//    indent.fill(' ', indentLevel * 4);

    // Init Component ID
    QString cID = liveCodeGenerateID(aLiveRoot);

    // Get Component ID
    QString lccID = liveCodeFormatID(cID, indent);

    // Add ID ==================================================================

    // Check Live Code Component ID
    if (!lccID.isEmpty()) {
        liveCode += lccID;
    }

    // Get Object Name
    QString objectName = liveCodeFormatObjectName(indent);

    // Add Object Name =========================================================

    // Check Object Name
    if (!objectName.isEmpty()) {
        liveCode += objectName;
    }

    // Check ID & Object Name
    if (!lccID.isEmpty() || !objectName.isEmpty()) {
        // Add New Line
        liveCode += "\n";
    }

    // Add Pos =================================================================

    // Check Live Root
    if (!aLiveRoot) {
        liveCode += liveCodeFormatPosition(indent);
    }

    // Add Size ================================================================

    liveCode += liveCodeFormatSize(indent);

    // Add Anchors =============================================================

    // Check Live Root
    if (!aLiveRoot) {
        liveCode += liveCodeFormatAnchors(indent);
    }

    // =========================================================================

    // Init Own Property Value Hook List
    QStringList opvHookList = QStringList();
    // Init Inherited Properties Value Hook List
    QStringList pvHookList = QStringList();
    // Init Enum Hook List
    QStringList enumHookList = QStringList();
    // Init Property Change Hook List
    QStringList pcHookList = QStringList();

    // Get Filtered Property Keys
    QStringList fpKeys = mProject->filteredProperties();

    // Check If Component Code
    if (!aComponentCode && mCategory != "Animation" && mCategory != "Behavior") {
        // Add Global Child Index Map
        liveCode += QString("\n%1%2property string %3: \"%4\"\n").arg(aIndent).arg(DEFAULT_SOURCE_INDENT).arg(DEFAULT_COMPONENT_CHILD_MAP).arg(getGlobalChildIndexMap());
    }

    // Add Own Properties ======================================================

    liveCode += liveCodeFormatOwnProperties(opvHookList, enumHookList, pcHookList, cID, fpKeys, indent, aComponentCode);

    // Add Inherited Properties ================================================

    liveCode += liveCodeFormatInheritedProperties(pvHookList, enumHookList, pcHookList, cID, fpKeys, indent, aComponentCode);

    // =========================================================================

    // Remove Duplicates
    pcHookList.removeDuplicates();

    // Add Signals =============================================================

    liveCode += liveCodeFormatSignals(indent);

    // Add Slots ===============================================================

    liveCode += liveCodeFormatSlots(pcHookList, indent, aComponentCode);

    // Add Hooks for Property Getters And Setters ==============================

    liveCode += liveCodeFormatHooks(opvHookList, pvHookList, enumHookList, indent);

    // Add Functions ===========================================================

    liveCode += liveCodeFormatFunctions(indent);

    // Add Children ============================================================

    // Check If Generate Children
    if (aGenerateChildren) {
        // Generate Children Live Code
        liveCode += liveCodeFormatChildren(indent, aComponentCode);
        // Generate Animations
        liveCode += liveCodeFormatAnimations(indent, aComponentCode);
        // Generate Behaviors
        liveCode += liveCodeFormatBehaviors(indent, aComponentCode);
    }

    // Add States ==============================================================

    liveCode += liveCodeFormatStates(indent);

    // Add Transitions =========================================================

    liveCode += liveCodeFormatTransitions(indent);

    //==========================================================================

    liveCode += QString("%1//...\n\n").arg(indent);

    // Add Closing Bracket
    liveCode += QString("%1}\n").arg(aIndent);

    //qDebug() << "ComponentInfo::generateLiveCode - liveCode: " << liveCode;

    return liveCode;
}

//==============================================================================
// Generate Component Code
//==============================================================================
QString ComponentInfo::generateComponentCode(const bool& aGenerateChildren)
{
    // Check If Component Is Built In
    if (mBuiltIn) {
        return "";
    }

    qDebug() << "ComponentInfo::generateComponentCode - mName: " << mName;

    // Init Indent
    QString indent = DEFAULT_SOURCE_INDENT;

    // Init Component Code
    QString componentCode = QString("// %1 Component\n").arg(mName);

    // Check Type
    if (mType == COMPONENT_TYPE_DATASOURCE) {
        // Add Singleton Marker
        componentCode += QString("pragma Singleton\n");
    }

    // Add Imports =============================================================

    componentCode += liveCodeFormatImports();

    // Add Component Base ======================================================

    componentCode += QString("%1 {\n").arg(mBaseName);

    // Add ID ==================================================================

    // Get ID
    QString idTemp = componentID();
    // Check ID Temp
    if (idTemp.isEmpty()) {
        // Set ID Temp
        idTemp = QString("%1Root").arg(mName);
        // Set First Char Lovercase
        idTemp[0] = idTemp[0].toLower();
    }

    componentCode += QString("%1id: %2\n").arg(DEFAULT_SOURCE_INDENT).arg(idTemp);

    // Init Keys ===============================================================

    // Init Dummies for Keys
    QStringList ophDummy;
    QStringList phDummy;
    QStringList ehDummy;
    QStringList pcDummy;

    // Get Filtered Property Keys
    QStringList fpKeys = mProject->filteredProperties();

    // Add Own Properties ======================================================

    componentCode += liveCodeFormatOwnProperties(ophDummy, ehDummy, pcDummy, idTemp, fpKeys, indent, true);

    // Add Inherited Properties ================================================

    componentCode += liveCodeFormatInheritedProperties(phDummy, ehDummy, pcDummy, idTemp, fpKeys, indent, true);

    // Add Signals =============================================================

    componentCode += liveCodeFormatSignals(indent);

    // Add Slots ===============================================================

    componentCode += liveCodeFormatSlots(pcDummy, indent, true);

    // Add Functions ===========================================================

    componentCode += liveCodeFormatFunctions(indent);

    // Add Children ============================================================

    // Check Generate Children
    if (aGenerateChildren) {
        // Format Children
        componentCode += liveCodeFormatChildren(indent, true);
        // Generate Animations
        componentCode += liveCodeFormatAnimations(indent, true);
        // Generate Behaviors
        componentCode += liveCodeFormatBehaviors(indent, true);
    }

    // Add States ==============================================================

    componentCode += liveCodeFormatStates(indent);

    // Add Transitions =========================================================

    componentCode += liveCodeFormatTransitions(indent);

    // =========================================================================

    componentCode += QString("%1Component.onCompleted: {\n").arg(indent);
    componentCode += QString("%1%1console.log(\"%2 onCompleted\");\n").arg(indent).arg(mName);
    componentCode += QString("%1}\n\n").arg(indent);

    componentCode += QString("%1Component.onDestruction: {\n").arg(indent);
    componentCode += QString("%1%1console.log(\"%2 onDestruction\");\n").arg(indent).arg(mName);
    componentCode += QString("%1}\n").arg(indent);

    // Add Closing Bracket
    componentCode += QString("}\n");

    // ...

    return componentCode;
}

//==============================================================================
// Generate Data Source Live Code
//==============================================================================
QString ComponentInfo::generateDataSourceLiveCode()
{
    // Check Type
    if (mType != COMPONENT_TYPE_DATASOURCE) {
        return "";
    }

    qDebug() << "ComponentInfo::generateDataSourceLiveCode - mName: " << mName;

    // Init Indent
    QString indent = DEFAULT_SOURCE_INDENT;

    // Init Live Code
    QString liveCode = QString("// %1 Component Live Code\n").arg(mName);;

    // Init Component Code
    liveCode = liveCodeFormatImports();

    // Add Data Sources Import =================================================

    liveCode += QString("import datasources 0.1\n\n");

    // Add Item As Name
    liveCode += QString("Item {\n");

    // Add Root ID =============================================================

    // Get ID
    QString idTemp = componentID();
    // Check ID Temp
    if (idTemp.isEmpty()) {
        // Set ID Temp
        idTemp = QString("%1LiveViewerRoot").arg(mName);
        // Set First Char Lovercase
        idTemp[0] = idTemp[0].toLower();
    }

    liveCode += QString("%1id: %2\n\n").arg(indent).arg(idTemp);

    // Add Column For Properties ===============================================

    liveCode += QString("%1Column {\n").arg(indent);
    liveCode += QString("%1%1anchors.fill: parent\n").arg(indent);
    liveCode += QString("%1%1anchors.margins: 16\n").arg(indent);
    liveCode += QString("%1%1spacing: 16\n\n").arg(indent);

    // Add Title

    liveCode += QString("%1%1Text {\n").arg(indent);

    liveCode += QString("%1%1%1font.pixelSize: 32\n").arg(indent);
    liveCode += QString("%1%1%1color: \"#AAFFFFFF\"\n").arg(indent);

    liveCode += QString("%1%1%1text: \"%2\"\n").arg(indent).arg(mName);

    liveCode += QString("%1%1}\n\n").arg(indent);


    // List Data Source Properties

    // Get Property Keys
    QStringList pKeys = componentOwnPropertyKeys();
    // Get Filtered Property Keys
    QStringList fpKeys = mProject->filteredProperties();
    // Init Property Set Hooks
    QStringList spHooks = QStringList();

    // Get Property Keys Count
    int pkCount = pKeys.count();

    // Iterate Through Property Keys
    for (int i=0; i<pkCount; i++) {
        // Check Property Key
        if (fpKeys.indexOf(pKeys[i]) == -1) {
            // Get Property Value
            QString pValue = propertyValue(pKeys[i], true).toString();
            // Add Property To List

            liveCode += QString("%1%1Text {\n").arg(indent);

            liveCode += QString("%1%1%1font.pixelSize: 24\n").arg(indent);
            liveCode += QString("%1%1%1color: \"#77FFFFFF\"\n").arg(indent);

            liveCode += QString("%1%1%1text: \"%2: \" + %3.%2\n").arg(indent).arg(pKeys[i]).arg(mName);

            // ...

            liveCode += QString("%1%1}\n\n").arg(indent);

            // Add Value Setting Hook
            spHooks << QString("%1%1%1case \"%2\": %3.%2 = value; break;\n").arg(indent).arg(pKeys[i]).arg(mName);
        }
    }

    // ...

    // Closing Bracket For Column
    liveCode += QString("%1}\n").arg(indent);

    // ....

    // Add Column For Signals ==================================================

    // Add Column For Slots ====================================================

    // Add Property Setting Hooks ==============================================

    // Get Set Property Hook Count
    int sphCount = spHooks.count();

    // Check Set Property Hooks Count
    if (sphCount > 0) {
        // Add New Line
        liveCode += "\n";
        // Comment Line
        liveCode += QString("%1// Property Set Hook\n").arg(indent);
        // Init Property Update Hook Function Code
        QString propertyHooks = QString("%1function __setProperty(key, value) {\n").arg(indent);
        // Add Console Log
        propertyHooks += QString("%1%1console.log(\"__setProperty - key: \" + key + \" - value: \" + value);\n").arg(indent);
        // Add Key Switch
        propertyHooks += QString("%1%1switch (key) {\n").arg(indent);
        // Add Default Hook
        propertyHooks += QString("%1%1%1default: console.log(\"__setProperty property:\" + key + \" IS NOT DEFINED!\"); break;\n").arg(indent);

        // Iterate Through Own Property Value Hooks
        for (int i=0; i<sphCount; i++) {
            // Append Own Property Vlaue Hook
            propertyHooks += spHooks[i];
        }

        // Add Switch Closing Bracket
        propertyHooks += QString("%1%1}\n").arg(indent);
        // Add Final Bracket
        propertyHooks += QString("%1}\n").arg(indent);

        // Append Property Hooks To Live Code
        liveCode += propertyHooks;

        // Add New Line
        liveCode += "\n";

    }

    // Add Column For Functions ================================================

    // ....

    // Add Closing Bracket
    liveCode += QString("}\n");

    return liveCode;
}

//==============================================================================
// Get Layout Base
//==============================================================================
QString ComponentInfo::layoutBase()
{
    // Check If Category Layout
    if (mBuiltIn && mCategory == COMPONENT_CATEGORY_LAYOUT) {
        return mName;
    }

    // Init Layout Base Name
    return mBase ? mBase->layoutBase() : "";
}

//==============================================================================
// Get Animation Base
//==============================================================================
QString ComponentInfo::animBase()
{
    // Check Category
    if (mCategory != COMPONENT_CATEGORY_ANIMATION) {
        return "";
    }

    // Check If Built In
    if (mBuiltIn) {
        return mName;
    }

    return mBase ? mBase->animBase() : "";
}

//==============================================================================
// Get Built In Base Component Name
//==============================================================================
QString ComponentInfo::builtInBase()
{
    // Check If Built In
    if (mBuiltIn) {
        return mName;
    }

    return mBase ? mBase->builtInBase() : "";
}

//==============================================================================
// Inc Reference Count
//==============================================================================
void ComponentInfo::incRefCount()
{
    // Decrease Child Reference Count
    mRefCount++;

    qDebug() << "ComponentInfo::incRefCount - mName: " << mName << " - mRefCount: " << mRefCount;
}

//==============================================================================
// Release Ref Count
//==============================================================================
void ComponentInfo::releaseRef()
{
    // Decrease Child Reference Count
    mRefCount--;

    qDebug() << "ComponentInfo::releaseRef - mName: " << mName << " - mRefCount: " << mRefCount;

    // Check Ref Count
    if (mRefCount <= 0) {
        // Clear Children
        clearChildren();
        // Clear Animations
        clearAnimations();
        // Clear Behaviors
        clearBehaviors();
    }
}

//==============================================================================
// Get Property
//==============================================================================
QVariant ComponentInfo::componentProperty(const QString& aName)
{
    // Check Property Keys
    if (mProperties.keys().indexOf(aName) >= 0) {
        //qDebug() << "ComponentInfo::componentProperty - aName: " << aName << " - INHERITED";
        return mProperties.value(aName).toString();
    }

    // Check Own Properties First
    if (mOwnProperties.keys().indexOf(aName) >= 0) {
        //qDebug() << "ComponentInfo::componentProperty - aName: " << aName << " - OWN";
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
                //qDebug() << "ComponentInfo::componentProperty - aName: " << aName << " - PROTOTYPE";
                return protoProperty;
            }
        }

        // Check Base Component
        if (mBase) {
            //qDebug() << "ComponentInfo::componentProperty - aName: " << aName << " - BASE";
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
                                         const QVariant& aDefaultValue,
                                         const bool& aReadOnly,
                                         const bool& aDefaultAlias)
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
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING, aDefaultValue.toString(), "", "", "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTBool:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL, aDefaultValue.toString(), "", "", "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTInt:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_INT, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTDouble:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTReal:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL, aDefaultValue.toString(), aMin, aMax, "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTVar:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR, aDefaultValue.toString(), "", "", "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTQtObject:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT, aDefaultValue.toString(), "", "", "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTQtObjectList:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST, aDefaultValue.toString(), "", "", "", aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTEnum:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM, aDefaultValue.toString(), "", "", aEnumValues, aReadOnly);
        break;
        case ComponentInfo::EPropertyType::EPTAlias:
            mOwnProperties[aName] = Utils::composeTypeAndValue(JSON_VALUE_PROPERTY_TYPE_PREFIX_ALIAS, aDefaultValue.toString(), "", "", "", aReadOnly, aDefaultAlias);
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
    //qDebug() << "ComponentInfo::hasProperty - mName: " << mName << " - aName: " << aName;

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
        return mBase->propertyValue(aName, aRaw);
    }

    return QVariant();
}

//==============================================================================
// Set Property Value
//==============================================================================
void ComponentInfo::setPropertyValue(const QString& aName, const QVariant& aValue)
{
    // Check Name
    if (aName.isEmpty()) {
        return;
    }

    // Set Component Property
    setComponentProperty(aName, aValue);
}

//==============================================================================
// Get Property Is Formula or Binding for Value
//==============================================================================
bool ComponentInfo::propertyIsFormula(const QString& aName)
{
    // Get Property Value
    QString pValue = propertyValue(aName, true).toString();

    // Check If It Has Binding Or Formula
    if (Utils::hasBinding(pValue) >= 0 || Utils::hasFormula(pValue) > 0) {
        return true;
    }

    return false;
}

//==============================================================================
// Get Children Loaded
//==============================================================================
bool ComponentInfo::childrenLoaded()
{
    return mChildrenLoaded;
}

//==============================================================================
// Animations Loaded
//==============================================================================
bool ComponentInfo::animationsLoaded()
{
    return mAnimationsLoaded;
}

//==============================================================================
// Behaviors Loaded
//==============================================================================
bool ComponentInfo::behaviorsLoaded()
{
    return mBehaviorsLoaded;
}

//==============================================================================
// Get Child Count
//==============================================================================
int ComponentInfo::childCount()
{
    return mChildComponents.count();
}

//==============================================================================
// Animations Count
//==============================================================================
int ComponentInfo::animsCount()
{
    return mAnimationComponents.count();
}

//==============================================================================
// Behaviors Count
//==============================================================================
int ComponentInfo::behaviorsCount()
{
    return mBehaviorComponents.count();
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
    if (aIndex >= 0 && aIndex < mChildComponents.count()) {
        return mChildComponents[aIndex];
    }

    return NULL;
}

//==============================================================================
// Get Child Info By Child Index Map
//==============================================================================
ComponentInfo* ComponentInfo::childInfo(const QString& aMap)
{
    // Check Map
    if (aMap.isEmpty()) {
        return NULL;
    }

    // Split Map
    QStringList mapList = aMap.split(".");

    // Check Map
    if (mapList[0] != mName) {
        return NULL;
    }

    // Check Map List
    if (mapList.count() < 2) {
        return NULL;
    }

    // Get Map Count
    int mCount = mapList.count();

    // Init Temp Info
    ComponentInfo* tempInfo = childInfo(mapList[1].toInt());

    // Iterate Through Map List
    for (int i=2; i<mCount; i++) {
        // Check Temp Info
        if (tempInfo) {
            // Set Temp Info
            tempInfo = tempInfo->childInfo(mapList[i].toInt());
        }
    }

    return tempInfo;
}

//==============================================================================
// Get Anim Info
//==============================================================================
ComponentInfo* ComponentInfo::animInfo(const int& aIndex)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mAnimationComponents.count()) {
        return mAnimationComponents[aIndex];
    }

    return NULL;
}

//==============================================================================
// Add Child
//==============================================================================
void ComponentInfo::addChild(ComponentInfo* aChild, const bool& aLoadChildren)
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
        // Reset Transition Parent
        aChild->mTransitionParent = NULL;

        // Check Child Component Category
        if (aChild->mCategory == "Animation") {
            // Append Anim
            mAnimationComponents << aChild;

        } else if (aChild->mCategory == "Behavior") {
            // Append Behavior
            mBehaviorComponents << aChild;

        } else {
            // Append Child
            mChildComponents << aChild;
        }

        // Add ID To ID Map
        setChildObjectID(aChild, aChild->componentID());

        // Check If Loading Children
        if (!aLoadChildren) {
            // Set Dirty
            setDirty(true);
        }

        // Check Child Component Category
        if (aChild->mCategory == "Animation") {
            // Emit Animation Added Signal
            emit animationAdded(mAnimationComponents.count() - 1);
            // Emit Anims Count Changed Signal
            emit animsCountChanged(mAnimationComponents.count());

        } else if (aChild->mCategory == "Behavior") {
            // Emit Behavior Added Signal
            emit behaviorAdded(mBehaviorComponents.count() - 1);
            // Emit Behaviors Count Changed Signal
            emit behaviorsCountChanged(mBehaviorComponents.count());
        } else {
            // Emit Child Added
            emit childAdded(mChildComponents.count() - 1);
            // Emit Child Count Changed Signal
            emit childCountChanged(mChildComponents.count());
        }
    }
}

//==============================================================================
// Insert Child
//==============================================================================
void ComponentInfo::insertChild(const int& aIndex, ComponentInfo* aChild, const bool& aMove)
{
    // Check Child Info
    if (aChild) {
        // Reset ProtoType Flag
        aChild->mIsProtoType = false;
        // Reset Transition Parent
        aChild->mTransitionParent = NULL;
        // Set Parent
        aChild->mParent = this;
        // Clear Dirty Flag
        aChild->mDirty = false;
        // Add ID To ID Map
        setChildObjectID(aChild, aChild->componentID());

        // Check Child Component Category
        if (aChild->mCategory == "Animation") {
            // Append Anim
            mAnimationComponents.insert(aIndex, aChild);

        } else if (aChild->mCategory == "Behavior") {
            // Append Behavior
            mBehaviorComponents.insert(aIndex, aChild);

        } else {
            // Insert Child
            mChildComponents.insert(aIndex, aChild);
        }

        // Set Dirty
        setDirty(true);

        // Check If Move
        if (!aMove) {
            qDebug() << "ComponentInfo::insertChild - path: " <<  componentPath() << " <- " << aChild->mName << " - aIndex: " << aIndex;
            // Check Child Component Category
            if (aChild->mCategory == "Animation") {
                // Emit Animation Added Signal
                emit animationAdded(aIndex);

            } else if (aChild->mCategory == "Behavior") {
                // Emit Behavior Added Signal
                emit behaviorAdded(aIndex);

            } else {
                // Emit Child Added
                emit childAdded(aIndex);
            }
        }

        // Check Child Component Category
        if (aChild->mCategory == "Animation") {
            // Emit Anims Count Changed Signal
            emit animsCountChanged(mAnimationComponents.count());

        } else if (aChild->mCategory == "Behavior") {
            // Emit Behaviors Count Changed Signal
            emit behaviorsCountChanged(mBehaviorComponents.count());

        } else {
            // Emit Child Cound Changed Signal
            emit childCountChanged(mChildComponents.count());
        }
    }
}

//==============================================================================
// Remove Child
//==============================================================================
void ComponentInfo::removeChild(ComponentInfo* aChild, const bool& aDelete)
{
    // Check Child
    if (aChild) {
        // Get Category
        QString cCategory = aChild->mCategory;
        // Init Child Index
        int cIndex = -1;
        // Init Component Count
        int cCount = 0;
        // Check Child Component Category
        if (cCategory == "Animation") {
            // Get Animation Index
            cIndex = mAnimationComponents.indexOf(aChild);
            // Get Components Count
            cCount = mAnimationComponents.count();
        } else if (cCategory == "Behavior") {
            // Get Behavior Index
            cIndex = mBehaviorComponents.indexOf(aChild);
            // Get Behaviors Count
            cCount = mBehaviorComponents.count();
        } else {
            // Get Child Index
            cIndex = mChildComponents.indexOf(aChild);
            // Get Childlen Count
            cCount = mChildComponents.count();
        }

        // Check Child Index
        if (cIndex >= 0 && cIndex < cCount) {
            // Init Child Component Info
            ComponentInfo* childComponent = NULL;

            // Check Child Component Category
            if (cCategory == "Animation") {
                // Get Child Animation
                childComponent = mAnimationComponents[cIndex];
                // Emit Anim About To Be Removed
                emit animationAboutToBeRemoved(childComponent);

            } else if (cCategory == "Behavior") {
                // Get Child Behavior
                childComponent = mBehaviorComponents[cIndex];
                // Emit Behavior About To Be Removed
                emit behaviorAboutToBeRemoved(childComponent);

            } else {
                // Get Child Component
                childComponent = mChildComponents[cIndex];;
                // Emit Child About To Be Removed
                emit childComponent->childAboutToBeRemoved(childComponent);
            }


            qDebug() << "ComponentInfo::removeChild - path: " << componentPath() << " - mName: " << childComponent->mName;

            // Remove Child Object From ID Map
            setChildObjectID(childComponent, "");

            // Check Delete
            if (aDelete) {
                // Check Child Component Category
                if (cCategory == "Animation") {
                    // Delete Anim
                    delete mAnimationComponents.takeAt(cIndex);
                } else if (cCategory == "Behavior") {
                    // Delete Behavior
                    delete mBehaviorComponents.takeAt(cIndex);
                } else {
                    // Delete Child
                    delete mChildComponents.takeAt(cIndex);
                }
            } else {
                // Check Child Component Category
                if (cCategory == "Animation") {
                    // Remove Animation
                    mAnimationComponents.removeAt(cIndex);
                } else if (cCategory == "Behavior") {
                    // Remove Behavior
                    mBehaviorComponents.removeAt(cIndex);
                } else {
                    // Remove Child
                    mChildComponents.removeAt(cIndex);
                }
            }

            // Set Dirty
            setDirty(true);

            // Check Child Component Category
            if (cCategory == "Animation") {
                // Emit Animation Removed Signal
                emit animationRemoved(cIndex);
                // Emit Anims Count Changed Signal
                emit animsCountChanged(mAnimationComponents.count());

            } else if (cCategory == "Behavior") {
                // Emit Behavior Removed Signal
                emit behaviorRemoved(cIndex);
                // Emit Behaviors Count Changed Signal
                emit behaviorsCountChanged(mBehaviorComponents.count());
            } else {
                // Emit Child Removed Signal
                emit childRemoved(cIndex);
                // Emit Child Count Changed Signal
                emit childCountChanged(mChildComponents.count());
            }

        } else {
            qWarning() << "ComponentInfo::removeChild - aChild: " << aChild << " - CHILD COMPONENT NOT FOUND!";
        }
    }
}

//==============================================================================
// Remove Animation By Index
//==============================================================================
void ComponentInfo::removeAnimation(const int& aIndex)
{
    // Get Animations Count
    int acCount = mAnimationComponents.count();
    // Check Index
    if (aIndex > 0 && aIndex < acCount) {
        // Delete Animation
        delete mAnimationComponents.takeAt(aIndex);

        // Set Dirty
        setDirty(true);

        // Emit Animation Removed Signal
        emit animationRemoved(aIndex);
        // Emit Anims Count Changed Signal
        emit animsCountChanged(mAnimationComponents.count());
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

    // Check Index
    if (aIndex >= 0 && aIndex < mChildComponents.count()) {
        qDebug() << "ComponentInfo::moveChild - aIndex: " << aIndex << " -> " << newTargetIndex;

        // Move Child
        mChildComponents.move(aIndex, newTargetIndex);

        // Emit Child Moved Signal
        emit childMoved(this, aIndex, this, newTargetIndex);

        // Set Dirty
        setDirty(true);
    }
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
        ComponentInfo* takenChild = aChildInfo->takeChild(aIndex, true);

        qDebug() << "ComponentInfo::moveChild - mName: " << takenChild->mName << " -> " << aTargetChildInfo->componentPath() << " - aTargetIndex: " << aTargetIndex;

        // Reset Anchors
        takenChild->resetAnchors();

        // Reset Pos
        takenChild->setPosX(QString("4"));
        takenChild->setPosY(QString("4"));

        // Insert Child
        aTargetChildInfo->insertChild(aTargetIndex, takenChild, true);

        // Emit Child Moved Signal
        emit childMoved(this, aIndex, aTargetChildInfo, aTargetIndex);
    }
}

//==============================================================================
// Move Animation
//==============================================================================
void ComponentInfo::moveAnimation(const int& aIndex, const int& aTargetIndex)
{
    // Check Indexes
    if (aIndex == aTargetIndex) {
        return;
    }

    // Init New target Index
    int newTargetIndex = aIndex < aTargetIndex ? aTargetIndex - 1 : aTargetIndex;

    // Init New Target Index
    //int newTargetIndex = qBound(0, aTargetIndex, mChildren.count() - 1);

    // Check Index
    if (aIndex >= 0 && aIndex < mAnimationComponents.count()) {
        qDebug() << "ComponentInfo::moveAnimation - aIndex: " << aIndex << " -> " << newTargetIndex;

        // Move Child
        mAnimationComponents.move(aIndex, newTargetIndex);

        // Emit Animation Moved Signal
        emit animationMoved(this, aIndex, this, newTargetIndex);

        // Set Dirty
        setDirty(true);
    }

}

//==============================================================================
// Move Animation
//==============================================================================
void ComponentInfo::moveAnimation(ComponentInfo* aChildInfo, const int& aIndex, ComponentInfo* aTargetChildInfo, const int& aTargetIndex)
{
    // Check Component Info & Target Info
    if (aChildInfo == aTargetChildInfo) {
        // Move Animation
        aChildInfo->moveAnimation(aIndex, aTargetIndex);
    } else {
        // Take Animation
        ComponentInfo* takenAnimation = aChildInfo->takeAnimation(aIndex, true);

        qDebug() << "ComponentInfo::moveAnimation - mName: " << takenAnimation->mName << " -> " << aTargetChildInfo->componentPath() << " - aTargetIndex: " << aTargetIndex;

        // Insert Child
        aTargetChildInfo->insertChild(aTargetIndex, takenAnimation, true);

        // Emit Animation Moved Signal
        emit animationMoved(this, aIndex, aTargetChildInfo, aTargetIndex);
    }
}

//==============================================================================
// Take Child Info
//==============================================================================
ComponentInfo* ComponentInfo::takeChild(const int& aIndex, const bool& aMove)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mChildComponents.count()) {
        // Take Child
        ComponentInfo* takenChild = mChildComponents.takeAt(aIndex);
        // Check Taken Child
        if (takenChild) {
            // Check If Move
            if (!aMove) {
                qDebug() << "ComponentInfo::takeChild - path: " << componentPath() << " - aIndex: " << aIndex;
                // Emit Child About To Be Removed
                emit takenChild->childAboutToBeRemoved(takenChild);
            }

            // Remove Child Object From ID Map
            setChildObjectID(takenChild, "");
            // Set Dirty
            setDirty(true);
            // Check If Moved
            if (!aMove) {
                // Emmit Child Removed Signal
                emit childRemoved(aIndex);
            }
            // Emit Child Cound Changed Signal
            emit childCountChanged(mChildComponents.count());

            return takenChild;
        }
    }

    return NULL;
}

//==============================================================================
// Take Animation
//==============================================================================
ComponentInfo* ComponentInfo::takeAnimation(const int& aIndex, const bool& aMove)
{
    // Check Index
    if (aIndex >= 0 && aIndex < mAnimationComponents.count()) {
        // Take Animation
        ComponentInfo* takenAnimation = mAnimationComponents.takeAt(aIndex);
        // Check Taken Child
        if (takenAnimation) {
            // Check If Move
            if (!aMove) {
                qDebug() << "ComponentInfo::takeAnimation - path: " << componentPath() << " - aIndex: " << aIndex;
                // Emit Child About To Be Removed
                emit takenAnimation->childAboutToBeRemoved(takenAnimation);
            }

            // Remove Child Object From ID Map
            setChildObjectID(takenAnimation, "");
            // Set Dirty
            setDirty(true);
            // Check If Moved
            if (!aMove) {
                // Emmit Animation Removed Signal
                emit animationRemoved(aIndex);
            }
            // Emit Anim Cound Changed Signal
            emit animsCountChanged(mAnimationComponents.count());

            return takenAnimation;
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
    int cIndex = mChildComponents.indexOf(aChildInfo);
    // Find Index
    if (cIndex >= 0) {
        qDebug() << "ComponentInfo::takeChild - path: " << componentPath() << " - mName: " << aChildInfo->mName;

        // Take Child
        ComponentInfo* takenChild = mChildComponents.takeAt(cIndex);

        // Remove Child Object From ID Map
        setChildObjectID(takenChild, "");
        // Emit Child About To Be Removed
        emit takenChild->childAboutToBeRemoved(takenChild);

        // Set Dirty
        setDirty(true);

        // Emmit Child Removed Signal
        emit childRemoved(cIndex);
        // Emit Child Cound Changed Signal
        emit childCountChanged(mChildComponents.count());

        return cIndex;
    }

    return -1;
}

//==============================================================================
// Take Animation Component
//==============================================================================
int ComponentInfo::takeAnimation(ComponentInfo* aChildInfo)
{
    // Get Child Index
    int cIndex = mAnimationComponents.indexOf(aChildInfo);
    // Find Index
    if (cIndex >= 0) {
        qDebug() << "ComponentInfo::takeAnimation - path: " << componentPath() << " - mName: " << aChildInfo->mName;

        // Take Animation
        ComponentInfo* takenAnimation = mAnimationComponents.takeAt(cIndex);

        // Remove Child Object From ID Map
        setChildObjectID(takenAnimation, "");
        // Emit Child About To Be Removed
        emit takenAnimation->childAboutToBeRemoved(takenAnimation);

        // Set Dirty
        setDirty(true);

        // Emmit Animation Removed Signal
        emit animationRemoved(cIndex);
        // Emit Animations Cound Changed Signal
        emit animsCountChanged(mAnimationComponents.count());

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


