import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DMouseArea {
    id: chRoot

//    x: componentObject ? componentObject.x : 0
//    y: componentObject ? componentObject.y : 0

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

//    width: componentObject ? componentObject.width : CONSTS.defaultPaneWidth
//    height: componentObject ? componentObject.height : CONSTS.defaultPaneHeight

    // Root Container
    property QtObject rootContainer: null
    // Parent Handler
    property QtObject parentHandler: null
    // Global Child Index Map
    property string childIndexMap: ""
    // Component Info
    property ComponentInfo componentInfo: null
    // Component Object
    property QtObject componentObject: null

    // Child Handlers Container
    property QtObject childHandlersContainer: childHandlersContainer
    // Default Container
    default property alias defaultContainer: childHandlersContainer.children

    // Root Content Container
    property alias rootContentContainer: rootContentContainer

    // Component Selected
    property bool selected: false

    // Min Size
    property int minWidth: 0
    property int minHeight: 0
    // MAx Size
    property int maxWidth: 8192
    property int maxHeight: 8192

    // Enable Size Overlay
    property bool enableSizeOverlay: true
    // Enable Pos Overlay
    property bool enablePosOverlay: true

    // Border Color
    property string borderColor: {

        // Check If Selected

        // Check If Hovering

        // Check If Hovering OK

        // Check If Borders Visible
        if (!settingsController.borderVisible) {
            return "transparent";
        }

        // Check If Focused
        if (chRoot.componentInfo !== null && propertiesController.focusedComponent === chRoot.componentInfo) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    property bool rootHandler: false
    property bool mainDrag: false

    // Enable Drag
    property bool enableDrag: true
    // Enable Pan By Keys
    property bool enablePanByKeys: true
    // Enable Resizd
    property bool enableResize: true
    // Set Focus On resize
    property bool setFocusOnResize: false

    // Resize Left Enabled
    property bool resizeLeftEnabled: true
    // Resize Top Enabled
    property bool resizeTopEnabled: true
    // Resize Right Enabled
    property bool resizeRightEnabled: true
    // Resize Bottom Enabled
    property bool resizeBottomEnabled: true

    // Component Layout
    property string componentLayout: ""

//    // Layout Width
//    property int layoutWidth: updateHorizontalLayout()
//    // Layout Height
//    property int layoutHeight: updateVerticalLayout()
//    // Layout Spacing
//    property int layoutSpacing: updateLayoutSpacing()

    // Current Hover Handler
    property QtObject hoverHandler: null
    // Hover Pos X
    property int hoverPosX: 0
    // Hover Pos Y
    property int hoverPosY: 0

    // Drag Source
    property ComponentInfo dragSource: null
    // Drag Key
    property string dragKey: ""

    // Drop Hovering
    property bool dropHovering: (hoverHandler === chRoot)
    // Drop OK
    property bool dropOK: false

    // Update Component Info Enabled
    property bool updateComponentInfoEnabled: false

    property Connections propertiesControllerConnections: Connections {
        target: propertiesController

        // ...
    }

    // Component Info Connections
    property Connections componentInfoConnections: Connections {
        target: chRoot.componentInfo

        // On Child Added
        onChildAdded: {

        }

        // On Child Moved Slot
        onChildMoved: {

        }

        // On Child Removed Slot
        onChildRemoved: {

        }

        // On Child About To Be Removed Slot
        onChildAboutToBeRemoved: {
            // Destroy Handler
            chRoot.destroy();
        }

        // On Pos X Changed Slot
        onPosXChanged: {
            // Check Handler Position
            if (chRoot.x !== aPosX && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.x = aPosX;
            }
        }

        // On Pos Y Changed Slot
        onPosYChanged: {
            // Check Handler Position
            if (chRoot.y !== aPosY && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.y = aPosY;
            }
        }

        // On Pos Z Changed Slot
        onPosZChanged: {
            // Check Handler Position
            if (chRoot.z !== aPosZ && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.z = aPosZ;
            }
        }

        // On Width Changed Slot
        onWidthChanged: {
            // Check Handler Width
            if (chRoot.width !== aWidth && chRoot.updateComponentInfoEnabled) {

            }
        }

        // On Height Changed Slot
        onHeightChanged: {
            // Check Handler Height
            if (chRoot.height !== aHeight && chRoot.updateComponentInfoEnabled) {

            }
        }

        // On Layer VisibilityChanged Slot
        onLayerVisibleChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Left Anchor Changed Slot
        onAnchorsLeftChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Left Anchor Margin Changed Slot
        onAnchorsLeftMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Right Anchor Changed Slot
        onAnchorsRightChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Right Anchor Margin Changed Slot
        onAnchorsRightMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Top Anchor Changed Slot
        onAnchorsTopChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Top Anchor Margin Changed Slot
        onAnchorsTopMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Bottom Anchor Changed Slot
        onAnchorsBottomChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Bottom Anchor Margin Changed Slot
        onAnchorsBottomMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Anchor Margin Changed Slot
        onAnchorsMarginsChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Fill Anchor Changed Slot
        onAnchorsFillChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Center Anchor Changed Slot
        onAnchorsCenterInChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Horizontal Center Anchor Changed Slot
        onAnchorsHorizontalCenterChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Vertical Center Anchor Changed Slot
        onAnchorsVerticalCenterChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Horizontal Center Anchor Offset Changed Slot
        onAnchorsHorizontalOffsetChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Vertical Center Anchor Offset Changed Slot
        onAnchorsVerticalOffsetChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }

        // Component Property Changed Slot
        onComponentPropertyChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {

            }
        }


        // ...

    }

    // Component Object Connections
    property Connections componentObjectConnections: Connections {
        target: componentObject

        onXChanged: chRoot.x = componentObject.x;
        onYChanged: chRoot.y = componentObject.y;
        onWidthChanged: chRoot.width = componentObject.width;
        onHeightChanged: chRoot.height = componentObject.height;

        // ...

    }

    // Drag Target
    //drag.target: enableDrag ? chRoot.componentObject : undefined

//    // Drag Minimum
//    drag.minimumX: 0
//    drag.minimumY: 0
//    // Drag Maximum
//    drag.maximumX: parent ? (parent.width - chRoot.width) : 0
//    drag.maximumY: parent ? (parent.height - chRoot.height) : 0

    // Drag Axis
    drag.axis: {
        // Check Component Info
        if (chRoot.componentInfo !== null) {

            // ...

        }

        return Drag.XandYAxis;
    }

    // Drag Threshold
    drag.threshold: CONSTS.defaultDragThreshold
    // Drag Filter Children
    drag.filterChildren: true

    // Resize Pressed Signal
    signal resizePressed()

    Component.onDestruction: {
        // Set Update Component Info Enabled
        chRoot.updateComponentInfoEnabled = false;

//        // Check Component Info
//        if (chRoot.componentInfo !== null) {
//            // Remove From Parent
//            chRoot.componentInfo.removeFromParent();
//        }
    }

    onXChanged: updateComponentPosX(x)
    onYChanged: updateComponentPosY(y);
    onWidthChanged: updateComponentWidth(width);
    onHeightChanged: updateComponentHeight(height);

    // On Component Info Changed Slot
    onComponentInfoChanged: {
        // Check Component Info
        if (chRoot.componentInfo !== null) {
            // Set Container/Handler
            chRoot.componentInfo.componentContainer = chRoot;
        }
    }

    // On Pressed Slot
    onPressed: {
        // Check If Drag Enabled
        if (chRoot.enableDrag) {
            // Set Drag Target
            drag.target = chRoot.componentObject;
        }
    }

    // On Released Slot
    onReleased: {
        // reset Drag Target
        drag.target = undefined;
    }

    // On Clicked Slot
    onClicked: {
        // Check Component Info
        if (chRoot.componentInfo !== null) {
            // Set Focused Component
            propertiesController.focusedComponent = chRoot.componentInfo;
        }
    }

    // Keys Pressed Slot
    Keys.onPressed: {
        // Switch Key
        switch (key) {

        }
    }

    // Keys Released Slot
    Keys.onReleased: {
        // Switch Key
        switch (key) {

        }
    }

    // Update Component Pos X
    function updateComponentPosX(posX) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled) {

        }
    }

    // Update Component Pos Y
    function updateComponentPosY(posY) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled) {

        }
    }

    // Update Component Width
    function updateComponentWidth(width) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled ) {

        }
    }

    // Update Component Height
    function updateComponentHeight(height) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled) {

        }
    }

    // Set Anchoring
    function setAnchoring() {
        // Check Component Info
        if (chRoot.componentInfo !== null && !chRoot.componentIsRoot) {
            console.log("DComponentHandler.setAnchoring - path: " + chRoot.componentInfo.componentPath);
//            // Set Anchor Fill
//            if (chRoot.componentInfo.anchorsFill !== "") {
//                // Set Fill Anchor
//                chRoot.anchors.fill = parseAnchors(chRoot.componentInfo.anchorsFill, false);
//            } else if (chRoot.componentInfo.anchorsCenterIn !== "") {
//                // Set Center In Anchor
//                chRoot.anchors.centerIn = parseAnchors(chRoot.componentInfo.anchorsCenterIn, false);
//            } else {

//                // Check Anchor Horizotal Center
//                if (chRoot.componentInfo.horizontalCenter !== "") {
//                    // Set Horizontal Center
//                    chRoot.anchors.horizontalCenter = parseAnchors(chRoot.componentInfo.horizontalCenter, true);
//                } else {
//                    // Set Left Anchor
//                    chRoot.anchors.left = parseAnchors(chRoot.componentInfo.anchorsLeft, true);
//                    // Set Right Anchor
//                    chRoot.anchors.right = parseAnchors(chRoot.componentInfo.anchorsRight, true);
//                }

//                // Check Anchor Vertical Center
//                if (chRoot.componentInfo.verticalCenter !== "") {
//                    // Set Vertical Center
//                    chRoot.anchors.verticalCenter = parseAnchors(chRoot.componentInfo.verticalCenter, true);
//                } else {
//                    // Set Top Anchor
//                    chRoot.anchors.top = parseAnchors(chRoot.componentInfo.anchorsTop, true);
//                    // Set Bottom Anchor
//                    chRoot.anchors.bottom = parseAnchors(chRoot.componentInfo.anchorsBottom, true);
//                }
//            }

//            // Check Margins
//            if (chRoot.componentInfo.anchorsMargins !== "") {
//                // Set Margins
//                chRoot.anchors.margins = Number(chRoot.componentInfo.anchorsMargins);
//            } else {
//                // Set Left, Right, Top, Botton Margin
//                chRoot.anchors.leftMargin = Number(chRoot.componentInfo.anchorsLeftMargin);
//                chRoot.anchors.rightMargin = Number(chRoot.componentInfo.anchorsRightMargin);
//                chRoot.anchors.topMargin = Number(chRoot.componentInfo.anchorsTopMargin);
//                chRoot.anchors.bottomMargin = Number(chRoot.componentInfo.anchorsBottomMargin);
//            }

//            // Set Horizontal Center Ofset
//            chRoot.anchors.horizontalCenterOffset = Number(chRoot.componentInfo.anchorsHorizontalOffset);
//            // Set Vertical Center Offset
//            chRoot.anchors.verticalCenterOffset = Number(chRoot.componentInfo.anchorsVerticalOffset);
        }
    }

    // Parse Anchors
    function parseAnchors(anchorString, needPoint) {
        // Get Anchor Elements
        var anchorElements = anchorString.split(".");

        //console.log("DComponentHandler.parseAnchors - anchorElements: " + anchorElements);

        // Get Anchor Target
        var anchorTarget = anchorElements[0];

        // Check Anchor Target
        if (anchorTarget === "") {
            //console.log("DComponentHandler.parseAnchors - Clearing Anchor");
            return undefined;
        }

        // Get Anchoring Point
        var anchorPoint = anchorElements[1];

        // Check Anchor Target
        if (anchorTarget === "parent") {
            // Set Anchor Target - Morph To Object
            anchorTarget = chRoot.parentHandler;
        } else {
            // Get Component By ID
            var targetComponent = chRoot.componentInfo.getChildObject(anchorTarget);

            // TODO: Double Check!!

            // Get Anchor Target
            anchorTarget = targetComponent !== null ? targetComponent.componentContainer : undefined;
        }

        // Check Anchor Target
        if (anchorTarget === null || anchorTarget === undefined) {
            console.warn("DComponentHandler.componentInfoConnections.onAnchorRightChanged - NO SUCH TARGET!");
            return undefined;
        }

        //console.log("DComponentHandler.parseAnchors - anchorTarget: " + anchorTarget);

        // Check Anchor Point
        if (anchorPoint === "" || anchorPoint === undefined) {
            // Check If Need Anchoring Point
            if (needPoint) {
                console.warn("DComponentHandler.parseAnchors - NO ANCHOR POINT DEFINED!");
                return undefined;
            }

            return anchorTarget;
        }

        // Switch Anchor Point
        switch (anchorPoint) {
            case "left":                anchorPoint = anchorTarget.left;                break;
            case "right":               anchorPoint = anchorTarget.right;               break;
            case "top":                 anchorPoint = anchorTarget.top;                 break;
            case "bottom":              anchorPoint = anchorTarget.bottom;              break;
            case "horizontalCenter":    anchorPoint = anchorTarget.horizontalCenter;    break;
            case "verticalCenter":      anchorPoint = anchorTarget.verticalCenter;      break;

            default:
                console.warn("DComponentHandler.parseAnchors - anchorPoint: " + anchorPoint + " - INVALID ANCHOR POINT!");
            return undefined;
        }

        return anchorPoint;
    }

    function insertChild() {

    }

    function removeChild() {

    }

    function moveChild() {

    }

    function getHoveringHandler(posX, posY, parentHandler) {

    }

    function checkDragSource(dragSource, dragKey) {

    }

    function makeDrop(drop) {

    }

    function updateLayoutSpacing() {

    }

    function updateHorizontalLayout() {

    }

    function updateVerticalLayout() {

    }

    // Border Rectangle
    DRectangle {
        id: borderRectangle
        anchors.fill: parent
        anchors.margins: -1
        //color: "transparent"
        //color: "#22777700"
        color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.2)
        border.color: chRoot.borderColor
        radius: 0
    }

    // Root
    Item {
        id: rootContentContainer
        anchors.fill: parent
    }

//    // THIS IS ONLY FOR THE drag.filterChildren to work
//    MouseArea {
//        id: dragHelper
//        anchors.fill: parent
//        onClicked: {
//            // Set Focused Component
//            propertiesController.focusedComponent = chRoot.componentInfo;
//        }
//    }

    // Drop Area For Child Components
    DDropArea {
        id: dropArea
        anchors.fill: parent

        onEntered: {
            // Set Drag Source
            chRoot.dragSource = drag.source;
            // Set Drag Key
            chRoot.dragKey = drag.keys[0];

            // Accept Drag
            drag.accept();

            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler === null) {
                // Set Initial Hover Container
                chRoot.rootContainer.hoverHandler = chRoot;
            }

            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler !== null) {
                // Check Drag Source by Current Hovered Container
                chRoot.rootContainer.hoverHandler.checkDragSource(chRoot.dragSource, chRoot.dragKey);
            }
        }

        onDropped: {
            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler !== null) {
                // Make The Drop
                chRoot.rootContainer.hoverHandler.makeDrop(drop);
                // Reset Hover Container
                chRoot.rootContainer.hoverHandler = null;
            }
        }

        onExited: {
            // Reset Drop Hover OK
            chRoot.dropHoverOK = false;
            // Reset Hover Container
            chRoot.rootContainer.hoverHandler = null;
            // Reset Drag Source
            chRoot.dragSource = null;
            // Reset Drag Key
            chRoot.dragKey = "";
        }
    }

    // Child Handlers Container
    Item {
        id: childHandlersContainer
        anchors.fill: parent

        // ...
    }

    // Component Label
    DText {
        id: componentLabel
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: CONSTS.componentNamesOpacity
        font.pixelSize: 48 // TODO: Manage Size
        text: chRoot.componentInfo ? chRoot.componentInfo.componentName : ""
    }

    // Position Indicator
    DPosIndicator {
        id: posIndicator
        anchors.left: parent.left
        anchors.top: parent.top
        enabled: enablePosOverlay
        posX: chRoot.x
        posY: chRoot.y
    }

    // Size Indicator
    DSizeIndicator {
        id: sizeIndicator
        anchors.centerIn: parent
        enabled: enableSizeOverlay
        sizeW: chRoot.width
        sizeH: chRoot.height
    }

    // Resize Area - Top Left
    DResizeArea {
        id: topLeftResizer
        resizePos: "topLeft"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeLeftEnabled && chRoot.resizeTopEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Top Center
    DResizeArea {
        id: topResizer
        resizePos: "top"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeTopEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Top Right
    DResizeArea {
        id: topRightResizer
        resizePos: "topRight"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeTopEnabled && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Left
    DResizeArea {
        id: leftResizer
        resizePos: "left"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeLeftEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Right
    DResizeArea {
        id: rightResizer
        resizePos: "right"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Left
    DResizeArea {
        id: bottomLeftResizer
        resizePos: "bottomLeft"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled && chRoot.resizeLeftEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Center
    DResizeArea {
        id: bottomResizer
        resizePos: "bottom"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Right
    DResizeArea {
        id: bottomRightResizer
        resizePos: "bottomRight"
        target: parent
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }
}
