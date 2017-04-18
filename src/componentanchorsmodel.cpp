#include <QDebug>

#include "componentanchorsmodel.h"
#include "componentinfo.h"
#include "propertiescontroller.h"
#include "constants.h"

//==============================================================================
// Constructor
//==============================================================================
ComponentAnchorsModel::ComponentAnchorsModel(ComponentInfo* aComponent, QObject* aParent)
    : QObject(aParent)
    , mComponent(aComponent)
{
    qDebug() << "ComponentAnchorsModel created.";

    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentAnchorsModel::init()
{
}

//==============================================================================
// Clear
//==============================================================================
void ComponentAnchorsModel::clear()
{
    // ...
}

////==============================================================================
//// Load Component Anchors
////==============================================================================
//void ComponentAnchorsModel::loadComponentAnchors()
//{

//    // ...
//}

////==============================================================================
//// Save Component Anchors
////==============================================================================
//void ComponentAnchorsModel::saveComponentAnchors()
//{
//    //
//}

//==============================================================================
// Get Current Component
//==============================================================================
ComponentInfo* ComponentAnchorsModel::currentComponent()
{
    return mComponent;
}

//==============================================================================
// Set Current Component
//==============================================================================
void ComponentAnchorsModel::setCurrentComponent(ComponentInfo* aComponent)
{
    // Check Current Component
    if (mComponent != aComponent) {
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed
        emit currentComponentChanged(mComponent);
    }
}

//==============================================================================
// Left Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsLeft()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT].toString();
    }

    return "";
}

//==============================================================================
// Set Left Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsLeft(const QString& aAnchorLeft)
{
    // Check Anchors Left
    if (mComponent && anchorsLeft() != aAnchorLeft) {
        // Set Anchors Left
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT] = aAnchorLeft;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Left Changed Signal
        emit anchorsLeftChanged(aAnchorLeft);
    }
}

//==============================================================================
// Right Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsRight()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT].toString();
    }

    return "";
}

//==============================================================================
// Set Right Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsRight(const QString& aAnchorRight)
{
    // Check Anchors Right
    if (mComponent &&  anchorsRight() != aAnchorRight) {
        // Set Anchors Left
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT] = aAnchorRight;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Right Changed Signal
        emit anchorsRightChanged(aAnchorRight);
    }
}

//==============================================================================
// Top Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsTop()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP].toString();
    }

    return "";
}

//==============================================================================
// Set Top Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsTop(const QString& aAnchorTop)
{
    // Check Anchors Top
    if (mComponent && anchorsTop() != aAnchorTop) {
        // Set Anchors Top
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP] = aAnchorTop;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Top Changed Signal
        emit anchorsTopChanged(aAnchorTop);
    }
}

//==============================================================================
// Bottom Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsBottom()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM].toString();
    }

    return "";
}

//==============================================================================
// Set Bottom Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsBottom(const QString& aAnchorBottom)
{
    // Check Anchors Bottom
    if (mComponent && anchorsBottom() != aAnchorBottom) {
        // Set Anchors Bottom
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM] = aAnchorBottom;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Bottom Changed Signal
        emit anchorsBottomChanged(aAnchorBottom);
    }
}

//==============================================================================
// Fill Target
//==============================================================================
QString ComponentAnchorsModel::anchorsFill()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL].toString();
    }

    return "";
}

//==============================================================================
// Set Fill Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsFill(const QString& aAnchorFill)
{
    // Check Anchors Fill
    if (mComponent && anchorsFill() != aAnchorFill) {
        // Set Anchors Fill
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL] = aAnchorFill;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Fill Changed Signal
        emit anchorsFillChanged(aAnchorFill);
    }
}

//==============================================================================
// CenterIn Target
//==============================================================================
QString ComponentAnchorsModel::anchorsCenterIn()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN].toString();
    }

    return "";
}

//==============================================================================
// Set CenterIn Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsCenterIn(const QString& aAnchorCenterIn)
{
    // Check Anchors CenterIn
    if (mComponent && anchorsCenterIn() != aAnchorCenterIn) {
        // Set Anchors CenterIn
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN] = aAnchorCenterIn;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors CenterIn Changed Signal
        emit anchorsCenterInChanged(aAnchorCenterIn);
    }
}

//==============================================================================
// Horizontal Center Target
//==============================================================================
QString ComponentAnchorsModel::horizontalCenter()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER].toString();
    }

    return "";
}

//==============================================================================
// Set Horizontal Center Target
//==============================================================================
void ComponentAnchorsModel::setHorizontalCenter(const QString& aHorizontalCenter)
{
    // Check Anchors Horizontal Center
    if (mComponent && horizontalCenter() != aHorizontalCenter) {
        // Set Anchors Horizontal Center
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER] = aHorizontalCenter;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Horizontal Changed Signal
        emit anchorsHorizontalCenterChanged(aHorizontalCenter);
    }
}

//==============================================================================
// Vertical Center Target
//==============================================================================
QString ComponentAnchorsModel::verticalCenter()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER].toString();
    }

    return "";
}

//==============================================================================
// Set Vertical Center Target
//==============================================================================
void ComponentAnchorsModel::setVerticalCenter(const QString& aVerticalCenter)
{
    // Check Anchors Vertical Center
    if (mComponent && verticalCenter() != aVerticalCenter) {
        // Set Anchors Vertical Center
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER] = aVerticalCenter;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Vertical Changed Signal
        emit anchorsVerticalCenterChanged(aVerticalCenter);
    }
}

//==============================================================================
// Margins
//==============================================================================
QString ComponentAnchorsModel::anchorsMargins()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS].toString();
    }

    return "";
}

//==============================================================================
// Set Margins
//==============================================================================
void ComponentAnchorsModel::setAnchorsMargins(const QString& aAnchorMargins)
{
    // Check Anchors Margins
    if (mComponent && anchorsMargins() != aAnchorMargins) {
        // Set Anchors Margins
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS] = aAnchorMargins;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Margins Changed Signal
        emit anchorsMarginsChanged(aAnchorMargins);
    }
}

//==============================================================================
// Left Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsLeftMargin()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN].toString();
    }

    return "";
}

//==============================================================================
// Set Left Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsLeftMargin(const QString& aAnchorLeftMargin)
{
    // Check Anchors LeftMargin
    if (mComponent && anchorsLeftMargin() != aAnchorLeftMargin) {
        // Set Anchors LeftMargin
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN] = aAnchorLeftMargin;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors LeftMargin Changed Signal
        emit anchorsLeftMarginChanged(aAnchorLeftMargin);
    }
}

//==============================================================================
// Right Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsRightMargin()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN].toString();
    }

    return "";
}

//==============================================================================
// Set Right Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsRightMargin(const QString& aAnchorRightMargin)
{
    // Check Anchors RightMargin
    if (mComponent && anchorsRightMargin() != aAnchorRightMargin) {
        // Set Anchors RightMargin
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN] = aAnchorRightMargin;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors RightMargin Changed Signal
        emit anchorsRightMarginChanged(aAnchorRightMargin);
    }
}

//==============================================================================
// Top Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsTopMargin()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN].toString();
    }

    return "";
}

//==============================================================================
// Set Top Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsTopMargin(const QString& aAnchorTopMargin)
{
    // Check Anchors TopMargin
    if (mComponent && anchorsTopMargin() != aAnchorTopMargin) {
        // Set Anchors TopMargin
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN] = aAnchorTopMargin;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors TopMargin Changed Signal
        emit anchorsTopMarginChanged(aAnchorTopMargin);
    }
}

//==============================================================================
// Bottom Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsBottomMargin()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN].toString();
    }

    return "";
}

//==============================================================================
// Set Bottom Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsBottomMargin(const QString& aAnchorBottomMargin)
{
    // Check Anchors BottomMargin
    if (mComponent && anchorsBottomMargin() != aAnchorBottomMargin) {
        // Set Anchors BottomMargin
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN] = aAnchorBottomMargin;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors BottomMargin Changed Signal
        emit anchorsBottomMarginChanged(aAnchorBottomMargin);
    }
}

//==============================================================================
// Horizontal Center Offset
//==============================================================================
QString ComponentAnchorsModel::anchorsHorizontalOffset()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS].toString();
    }

    return "";
}

//==============================================================================
// Set Horizontal Center Offset
//==============================================================================
void ComponentAnchorsModel::setAnchorsHorizontalOffset(const QString& aAnchorHorizontalOffset)
{
    // Check Anchors Horizontal Offset
    if (mComponent && anchorsHorizontalOffset() != aAnchorHorizontalOffset) {
        // Set Anchors Horizontal Offset
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS] = aAnchorHorizontalOffset;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors HorizontalOffset Changed Signal
        emit anchorsHorizontalOffsetChanged(aAnchorHorizontalOffset);
    }
}

//==============================================================================
// Vertical Center Offset
//==============================================================================
QString ComponentAnchorsModel::anchorsVerticalOffset()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS].toString();
    }

    return "";
}

//==============================================================================
// Set Vertical Center Offset
//==============================================================================
void ComponentAnchorsModel::setAnchorsVerticalOffset(const QString& aAnchorVerticalOffset)
{
    // Check Anchors Vertical Offset
    if (mComponent && anchorsVerticalOffset() != aAnchorVerticalOffset) {
        // Set Anchors Vertical Offset
        mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS] = aAnchorVerticalOffset;
        // Set Component Dirty
        mComponent->setDirty(true);
        // Emit Anchors Vertical Offset Changed Signal
        emit anchorsVerticalOffsetChanged(aAnchorVerticalOffset);
    }
}

//==============================================================================
// Clear Horizontal Anchors
//==============================================================================
void ComponentAnchorsModel::clearHorizontalAnchors()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // ...
}

//==============================================================================
// Clear Vertical Anchors
//==============================================================================
void ComponentAnchorsModel::clearVerticalAnchors()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // ...
}

//==============================================================================
// Clear All Anchors
//==============================================================================
void ComponentAnchorsModel::clearAllAnchors()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // ...
}

//==============================================================================
// Destructor
//==============================================================================
ComponentAnchorsModel::~ComponentAnchorsModel()
{
    // Clear
    clear();

    // ...

    qDebug() << "ComponentAnchorsModel deleted.";
}
