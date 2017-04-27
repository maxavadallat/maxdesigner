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

//==============================================================================
// Emit AnchorSignals
//==============================================================================
void ComponentAnchorsModel::emitAnchorSignals()
{
    // Check Component
    if (!mComponent) {
        return;
    }

    // Left Anchor Target Changed Signal
    emit anchorsLeftChanged(anchorsLeft());
    // Right Anchor Target Changed Signal
    emit anchorsRightChanged(anchorsRight());
    // Top Anchor Target Changed Signal
    emit anchorsTopChanged(anchorsTop());
    // Bottom Anchor Target Changed Signal
    emit anchorsBottomChanged(anchorsBottom());
    // Fill Target Changed Signal
    emit anchorsFillChanged(anchorsFill());
    // CenterIn Target Changed Signal
    emit anchorsCenterInChanged(anchorsCenterIn());
    // Horizontal Center Target Changed Signal
    emit anchorsHorizontalCenterChanged(horizontalCenter());
    // Vertical Center Target Changed Signal
    emit anchorsVerticalCenterChanged(verticalCenter());
    // Margins Changed Signal
    emit anchorsMarginsChanged(anchorsMargins());
    // Left Margin Changed Signal
    emit anchorsLeftMarginChanged(anchorsLeftMargin());
    // Right Margin Changed Signal
    emit anchorsRightMarginChanged(anchorsRightMargin());
    // Top Margin Changed Signal
    emit anchorsTopMarginChanged(anchorsTopMargin());
    // Bottom Margin Changed Signal
    emit anchorsBottomMarginChanged(anchorsBottomMargin());
    // Horizontal Center Offset Changed Signal
    emit anchorsHorizontalOffsetChanged(anchorsHorizontalOffset());
    // Vertical Center Offset Changed Signal
    emit anchorsVerticalOffsetChanged(anchorsVerticalOffset());
}

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
        qDebug() << "ComponentAnchorsModel::setCurrentComponent - mComponent: " << (mComponent ? mComponent->mName : "NULL");
        // Set Current Component
        mComponent = aComponent;
        // Emit Current Component Changed
        emit currentComponentChanged(mComponent);
        // Emit Anchor signals
        emitAnchorSignals();
    }
}

//==============================================================================
// Left Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsLeft()
{
    // Check Current Component
    if (mComponent) {
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT).toString();
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
        // Check If Value Empty
        if (aAnchorLeft.isEmpty()) {
            // Clear Anchor Left
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT);
        } else {
            // Set Anchors Left
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT] = aAnchorLeft;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT).toString();
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
        // Check If Value Empty
        if (aAnchorRight.isEmpty()) {
            // Clear Anchor Right
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT);
        } else {
            // Set Anchors Left
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT] = aAnchorRight;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP).toString();
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
        // Check If Value Empty
        if (aAnchorTop.isEmpty()) {
            // Clear Anchor Top
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP);
        } else {
            // Set Anchors Top
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP] = aAnchorTop;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM).toString();
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
        // Check If Value Empty
        if (aAnchorBottom.isEmpty()) {
            // Clear Anchor Bottom
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM);
        } else {
            // Set Anchors Bottom
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM] = aAnchorBottom;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL).toString();
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
        // Check If Value Empty
        if (aAnchorFill.isEmpty()) {
            // Clear Anchor Fill
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL);
        } else {
            // Set Anchors Fill
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL] = aAnchorFill;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN).toString();
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
        // Check If Value Empty
        if (aAnchorCenterIn.isEmpty()) {
            // Clear Anchor Center In
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN);
        } else {
            // Set Anchors CenterIn
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN] = aAnchorCenterIn;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER).toString();
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
        // Check If Value Empty
        if (aHorizontalCenter.isEmpty()) {
            // Clear Anchor Horizontal Center
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER);
        } else {
            // Set Anchors Horizontal Center
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER] = aHorizontalCenter;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER).toString();
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
        // Check If Value Empty
        if (aVerticalCenter.isEmpty()) {
            // Clear Anchor Vertical Center
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER);
        } else {
            // Set Anchors Vertical Center
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER] = aVerticalCenter;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS).toString();
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
        // Check If Value Empty
        if (aAnchorMargins.isEmpty()) {
            // Clear Anchor Margins
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS);
        } else {
            // Set Anchors Margins
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS] = aAnchorMargins;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN).toString();
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
        // Check If Value Empty
        if (aAnchorLeftMargin.isEmpty()) {
            // Clear Anchor Left Margin
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN);
        } else {
            // Set Anchors LeftMargin
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN] = aAnchorLeftMargin;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN).toString();
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
        // Check If Value Empty
        if (aAnchorRightMargin.isEmpty()) {
            // Clear Anchor Right Margin
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN);
        } else {
            // Set Anchors RightMargin
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN] = aAnchorRightMargin;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN).toString();
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
        // Check If Value Empty
        if (aAnchorTopMargin.isEmpty()) {
            // Clear Anchor Top Margin
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN);
        } else {
            // Set Anchors TopMargin
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN] = aAnchorTopMargin;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN).toString();
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
        // Check If Value Empty
        if (aAnchorBottomMargin.isEmpty()) {
            // Clear Anchor Bottom Margin
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN);
        } else {
            // Set Anchors BottomMargin
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN] = aAnchorBottomMargin;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS).toString();
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
        // Check If Value Empty
        if (aAnchorHorizontalOffset.isEmpty()) {
            // Clear Anchor Horizontal Center Offset
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS);
        } else {
            // Set Anchors Horizontal Offset
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS] = aAnchorHorizontalOffset;
        }
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
        return mComponent->mAnchors.value(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS).toString();
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
        // Check If Value Empty
        if (aAnchorVerticalOffset.isEmpty()) {
            // Clear Anchor Vertical Center Offset
            mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS);
        } else {
            // Set Anchors Vertical Offset
            mComponent->mAnchors[JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS] = aAnchorVerticalOffset;
        }
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

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN);


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

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN);

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

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER);
    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN);

    mComponent->mAnchors.remove(JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL);

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
