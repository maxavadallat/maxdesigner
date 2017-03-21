#include <QDebug>

#include "componentanchorsmodel.h"
#include "componentinfo.h"
#include "constants.h"

//==============================================================================
// From JSON Object
//==============================================================================
ComponentAnchorsModel* ComponentAnchorsModel::fromJSONObject(ComponentInfo* aComponent, const QJsonObject& aObject)
{
    // Init New Anchors Model
    ComponentAnchorsModel* newAnchorsModel = new ComponentAnchorsModel(aComponent);

    // Load Component Anchors
    newAnchorsModel->loadComponentAnchors(aObject);

    return newAnchorsModel;
}

//==============================================================================
// Constructor
//==============================================================================
ComponentAnchorsModel::ComponentAnchorsModel(ComponentInfo* aComponent, QObject* aParent)
    : QObject(aParent)
    , mComponent(aComponent)
{
    // Init
    init();
}

//==============================================================================
// Init
//==============================================================================
void ComponentAnchorsModel::init()
{
    // ...
}

//==============================================================================
// Clear
//==============================================================================
void ComponentAnchorsModel::clear()
{
    // ...
}

//==============================================================================
// Load Component Anchors
//==============================================================================
void ComponentAnchorsModel::loadComponentAnchors(const QJsonObject& aObject)
{
    if (aObject.isEmpty()) {
        return;
    }

    // ...
}

//==============================================================================
// Save Component Anchors
//==============================================================================
void ComponentAnchorsModel::saveComponentAnchors()
{
    //
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
    return mAnchorLeft;
}

//==============================================================================
// Set Left Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsLeft(const QString& aAnchorLeft)
{
    // Check Anchors Left
    if (mAnchorLeft != aAnchorLeft) {
        // Set Anchors Left
        mAnchorLeft = aAnchorLeft;
        // Emit Anchors Left Changed Signal
        emit anchorsLeftChanged(mAnchorLeft);
    }
}

//==============================================================================
// Right Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsRight()
{
    return mAnchorRight;
}

//==============================================================================
// Set Right Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsRight(const QString& aAnchorRight)
{
    // Check Anchors Right
    if (mAnchorRight != aAnchorRight) {
        // Set Anchors Right
        mAnchorRight = aAnchorRight;
        // Emit Anchors Right Changed Signal
        emit anchorsRightChanged(mAnchorRight);
    }
}

//==============================================================================
// Top Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsTop()
{
    return mAnchorTop;
}

//==============================================================================
// Set Top Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsTop(const QString& aAnchorTop)
{
    // Check Anchors Top
    if (mAnchorTop != aAnchorTop) {
        // Set Anchors Top
        mAnchorTop = aAnchorTop;
        // Emit Anchors Top Changed Signal
        emit anchorsTopChanged(mAnchorTop);
    }
}

//==============================================================================
// Bottom Anchor Target
//==============================================================================
QString ComponentAnchorsModel::anchorsBottom()
{
    return mAnchorBottom;
}

//==============================================================================
// Set Bottom Anchor Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsBottom(const QString& aAnchorBottom)
{
    // Check Anchors Bottom
    if (mAnchorBottom != aAnchorBottom) {
        // Set Anchors Bottom
        mAnchorBottom = aAnchorBottom;
        // Emit Anchors Bottom Changed Signal
        emit anchorsBottomChanged(mAnchorBottom);
    }
}

//==============================================================================
// Fill Target
//==============================================================================
QString ComponentAnchorsModel::anchorsFill()
{
    return mAnchorFill;
}

//==============================================================================
// Set Fill Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsFill(const QString& aAnchorFill)
{
    // Check Anchors Fill
    if (mAnchorFill != aAnchorFill) {
        // Set Anchors Fill
        mAnchorFill = aAnchorFill;
        // Emit Anchors Fill Changed Signal
        emit anchorsFillChanged(mAnchorFill);
    }
}

//==============================================================================
// CenterIn Target
//==============================================================================
QString ComponentAnchorsModel::anchorsCenterIn()
{
    return mAnchorCenterIn;
}

//==============================================================================
// Set CenterIn Target
//==============================================================================
void ComponentAnchorsModel::setAnchorsCenterIn(const QString& aAnchorCenterIn)
{
    // Check Anchors CenterIn
    if (mAnchorCenterIn != aAnchorCenterIn) {
        // Set Anchors CenterIn
        mAnchorCenterIn = aAnchorCenterIn;
        // Emit Anchors CenterIn Changed Signal
        emit anchorsCenterInChanged(mAnchorCenterIn);
    }
}

//==============================================================================
// Margins
//==============================================================================
QString ComponentAnchorsModel::anchorsMargins()
{
    return mAnchorMargins;
}

//==============================================================================
// Set Margins
//==============================================================================
void ComponentAnchorsModel::setAnchorsMargins(const QString& aAnchorMargins)
{
    // Check Anchors Margins
    if (mAnchorMargins != aAnchorMargins) {
        // Set Anchors Margins
        mAnchorMargins = aAnchorMargins;
        // Emit Anchors Margins Changed Signal
        emit anchorsMarginsChanged(mAnchorMargins);
    }
}

//==============================================================================
// Left Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsLeftMargin()
{
    return mAnchorLeftMargin;
}

//==============================================================================
// Set Left Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsLeftMargin(const QString& aAnchorLeftMargin)
{
    // Check Anchors LeftMargin
    if (mAnchorLeftMargin != aAnchorLeftMargin) {
        // Set Anchors LeftMargin
        mAnchorLeftMargin = aAnchorLeftMargin;
        // Emit Anchors LeftMargin Changed Signal
        emit anchorsLeftMarginChanged(mAnchorLeftMargin);
    }
}

//==============================================================================
// Right Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsRightMargin()
{
    return mAnchorRightMargin;
}

//==============================================================================
// Set Right Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsRightMargin(const QString& aAnchorRightMargin)
{
    // Check Anchors RightMargin
    if (mAnchorRightMargin != aAnchorRightMargin) {
        // Set Anchors RightMargin
        mAnchorRightMargin = aAnchorRightMargin;
        // Emit Anchors RightMargin Changed Signal
        emit anchorsRightMarginChanged(mAnchorRightMargin);
    }
}

//==============================================================================
// Top Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsTopMargin()
{
    return mAnchorTopMargin;
}

//==============================================================================
// Set Top Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsTopMargin(const QString& aAnchorTopMargin)
{
    // Check Anchors TopMargin
    if (mAnchorTopMargin != aAnchorTopMargin) {
        // Set Anchors TopMargin
        mAnchorTopMargin = aAnchorTopMargin;
        // Emit Anchors TopMargin Changed Signal
        emit anchorsTopMarginChanged(mAnchorTopMargin);
    }
}

//==============================================================================
// Bottom Margin
//==============================================================================
QString ComponentAnchorsModel::anchorsBottomMargin()
{
    return mAnchorBottomMargin;
}

//==============================================================================
// Set Bottom Margin
//==============================================================================
void ComponentAnchorsModel::setAnchorsBottomMargin(const QString& aAnchorBottomMargin)
{
    // Check Anchors BottomMargin
    if (mAnchorBottomMargin != aAnchorBottomMargin) {
        // Set Anchors BottomMargin
        mAnchorBottomMargin = aAnchorBottomMargin;
        // Emit Anchors BottomMargin Changed Signal
        emit anchorsBottomMarginChanged(mAnchorBottomMargin);
    }
}

//==============================================================================
// Horizontal Center Offset
//==============================================================================
QString ComponentAnchorsModel::anchorsHorizontalOffset()
{
    return mAnchorHorizontalOffset;
}

//==============================================================================
// Set Horizontal Center Offset
//==============================================================================
void ComponentAnchorsModel::setAnchorsHorizontalOffset(const QString& aAnchorHorizontalOffset)
{
    // Check Anchors HorizontalOffset
    if (mAnchorHorizontalOffset != aAnchorHorizontalOffset) {
        // Set Anchors HorizontalOffset
        mAnchorHorizontalOffset = aAnchorHorizontalOffset;
        // Emit Anchors HorizontalOffset Changed Signal
        emit anchorsHorizontalOffsetChanged(mAnchorHorizontalOffset);
    }
}

//==============================================================================
// Vertical Center Offset
//==============================================================================
QString ComponentAnchorsModel::anchorsVerticalOffset()
{
    return mAnchorVerticalOffset;
}

//==============================================================================
// Set Vertical Center Offset
//==============================================================================
void ComponentAnchorsModel::setAnchorsVerticalOffset(const QString& aAnchorVerticalOffset)
{
    // Check Anchors VerticalOffset
    if (mAnchorVerticalOffset != aAnchorVerticalOffset) {
        // Set Anchors VerticalOffset
        mAnchorVerticalOffset = aAnchorVerticalOffset;
        // Emit Anchors VerticalOffset Changed Signal
        emit anchorsVerticalOffsetChanged(mAnchorVerticalOffset);
    }
}

//==============================================================================
// To JSON Object
//==============================================================================
QJsonObject ComponentAnchorsModel::toJSONObject()
{
    // Init New JSON Object
    QJsonObject newObject;

    // ...

    return newObject;
}

//==============================================================================
// Destructor
//==============================================================================
ComponentAnchorsModel::~ComponentAnchorsModel()
{
    // Clear
    clear();

    // ...
}
