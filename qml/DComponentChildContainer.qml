import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: cccRoot

    property bool grabbed: false

    property ComponentInfo componentInfo: null

    property Connections componentInfoConnections: Connections {
        target: cccRoot.componentInfo

        onComponentIDChanged: {
            // Check Parent Container
            if (parentContainer !== null && parentContainer.setChildComponentID !== undefined) {
                // Set Child Component ID
                parentContainer.setChildComponentID(cccRoot, aID);
            }
        }

        onPosXChanged: {
            // Check Pos
            if (cccRoot.x !== aPosX) {
                // Set Pos X
                cccRoot.x = aPosX;
            }
        }

        onPosYChanged: {
            // Check Pos Y
            if (cccRoot.y !== aPosY) {
                // Set Pos Y
                cccRoot.y = aPosY;
            }
        }

        onWidthChanged: {
            // Check Width
            if (cccRoot.width != aWidth) {
                // Set Width
                cccRoot.width = aWidth;
            }
        }

        onHeightChanged: {
            // Check Height
            if (cccRoot.height !== aHeight) {
                // Set Height
                cccRoot.height = aHeight;
            }
        }

        onAnchorLeftChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorLeftChanged - aLeft: " + aLeft);
            // Set Anchors Left
            cccRoot.anchors.left = cccRoot.parseAnchors(aLeft, true);
            // ...
        }

        // Left Anchor Margin Changed
        onAnchorLeftMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorLeftMarginChanged - aMargin: " + aMargin);
            // Set Left Margin
            cccRoot.anchors.leftMargin = aMargin;
        }

        // Right Anchor Changed
        onAnchorRightChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorRightChanged - aRight: " + aRight);
            // Set Anchors Right
            cccRoot.anchors.right = cccRoot.parseAnchors(aRight, true);
            // ...
        }

        // Right Anchor Margin Changed
        onAnchorRightMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorRightMarginChanged - aMargin: " + aMargin);
            // Set Right Margin
            cccRoot.anchors.rightMargin = aMargin;
        }

        // Top Anchor Changed
        onAnchorTopChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorTopChanged - aTop: " + aTop);
            // Set Anchors Top
            cccRoot.anchors.top = cccRoot.parseAnchors(aTop, true);
        }

        // Top Anchor Margin Changed
        onAnchorTopMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorTopMarginChanged - aMargin: " + aMargin);
            // Set Top Margin
            cccRoot.anchors.topMargin = aMargin;
        }

        // Bottom Anchor Changed
        onAnchorBottomChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorBottomChanged - aBottom: " + aBottom);
            // Set Anchors Botom
            cccRoot.anchors.bottom = cccRoot.parseAnchors(aBottom, true);
        }

        // Bottom Anchor Margin Changed
        onAnchorBottomMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorBottomMarginChanged - aMargin: " + aMargin);
            // Set Bottom Margin
            cccRoot.anchors.bottomMargin = aMargin;
        }

        onAnchorMarginsChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorMarginsChanged - aMargins: " + aMargins);
            // Set Margins
            cccRoot.anchors.margins = aMargins;
        }

        // Fill Anchor Changed
        onAnchorFillChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorFillChanged - aFill: " + aFill);
            // Set Anchors Fill
            cccRoot.anchors.fill = cccRoot.parseAnchors(aFill, false);
        }

        // Fill Anchor Margin Changed
        onAnchorFillMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorFillMarginChanged - aMargin: " + aMargin);
            // Set Anchor Margins
            cccRoot.anchors.margins = aMargin;
        }

        // Center Anchor Changed
        onAnchorCenterInChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorCenterInChanged - aCenterIn: " + aCenterIn);
            // Set Anchors Center In
            cccRoot.anchors.centerIn = cccRoot.parseAnchors(aCenterIn, false);
        }

        // Horizontal Center Anchor Changed
        onAnchorHorizontalCenterChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorHorizontalCenterChanged - aHorizontalCenter: " + aHorizontalCenter);
            // Set Anchors Horizontal Center
            cccRoot.anchors.horizontalCenter = cccRoot.parseAnchors(aHorizontalCenter, true);
        }

        // Vertical Center Anchor Changed
        onAnchorVerticalCenterChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorVerticalCenterChanged - aVerticalCenter: " + aVerticalCenter);
            // Set Anchors Vertical Center
            cccRoot.anchors.verticalCenter = cccRoot.parseAnchors(aVerticalCenter, true);
        }

        // Horizontal Center Anchor Offset Changed
        onAnchorHorizontalCenterOffsetChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorHorizontalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Horizontal Center Offset
            cccRoot.anchors.horizontalCenterOffset = aOffset;
        }

        // Vertical Center Anchor Offset Changed
        onAnchorVerticalCenterOffsetChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorVerticalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Vertical Center Offset
            cccRoot.anchors.verticalCenterOffset = aOffset;
        }

        // Component Property Changed
        onComponentPropertyChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // ...
        }

        // ...
    }

    property bool updateComponentInfoEnabled: false

    property bool selected: false

    backgroundColor: Qt.hsla(Math.random(), 0.5, 0.4, 0.2)

    borderColor: {
        if (cccRoot.selected) {
            return DStyle.colorBorderSelected;
        }

        if (cccRoot.componentInfo !== null && cccRoot.componentInfo === propertiesController.focusedComponent) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    borderMargins: -1

    radius: 0

    enablePosOverlay: true
    enableSizeOverlay: true
    setFocusOnResize: true

    drag.minimumX: -cccRoot.width
    drag.maximumX: parent.width
    drag.minimumY: -cccRoot.height
    drag.maximumY: parent.height

    Component.onDestruction: {
        // Check Component Info
        if (cccRoot.componentInfo !== null) {
            // Set Container
            cccRoot.componentInfo.componentContainer = null;
        }

        // Reset Update Component Info Enabled
        cccRoot.updateComponentInfoEnabled = false;
        // Reset Component Info
        cccRoot.componentInfo = null;
    }

    onComponentInfoChanged: {
        // Check Component Info
        if (cccRoot.componentInfo !== null) {
            // Set Container
            cccRoot.componentInfo.componentContainer = cccRoot;
        }
    }

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_Backspace:
            case Qt.Key_Delete:

                // Check Parent Container
                if (cccRoot.parentContainer && cccRoot.parentContainer.removeChildComponent !== undefined) {
                    // Remove Child Component
                    cccRoot.parentContainer.removeChildComponent(cccRoot);
                } else {
                    // Destroy
                    cccRoot.destroy();
                }
            break;
        }
    }

    onPressed: {
        //console.log("DComponentChildContainer.onPressed");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "cccRoot";
        }

        // ...
    }

    onReleased: {
        //console.log("DComponentChildContainer.onReleased");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "cccRoot") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "";
            // Set Focus
            cccRoot.focus = true;
        }

        // ...
    }

    onFocusChanged: {
        //console.log("DComponentChildContainer.onFocusChanged - focus: " + focus);

        // Check Focus
        if (cccRoot.focus) {
            // Set Focused Componrnt
            propertiesController.focusedComponent = cccRoot.componentInfo;
        }

//        // Set Update Component Info Enabled
//        cccRoot.updateComponentInfoEnabled = cccRoot.focus;

        // ...
    }

    onXChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Position
            if (propertiesController.cX !== cccRoot.x) {
                // Request Component Pos X
                propertiesController.requestCX(cccRoot.x);
            }
        }
    }

    onYChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Position
            if (propertiesController.cY !== cccRoot.y) {
                // Request Component Pos Y
                propertiesController.requestCY(cccRoot.y);
            }
        }
    }

    onWidthChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Width
            if (propertiesController.cWidth !== cccRoot.width) {
                // Request Component Width
                propertiesController.requestCWidth(cccRoot.width);
            }
        }
    }

    onHeightChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Height
            if (propertiesController.cHeight !== cccRoot.height) {
                // Request Component Height
                propertiesController.requestCHeight(cccRoot.height);
            }
        }
    }

    // Parse Anchors
    function parseAnchors(anchorString, needPoint) {
        // Get Anchor Elements
        var anchorElements = anchorString.split(".");

        //console.log("DComponentChildContainer.parseAnchors - anchorElements: " + anchorElements);

        // Get Anchor Target
        var anchorTarget = anchorElements[0];

        // Check Anchor Target
        if (anchorTarget === "") {
            console.log("DComponentChildContainer.parseAnchors - Clearing Anchor");
            return undefined;
        }

        // Get Anchoring Point
        var anchorPoint = anchorElements[1];

        // Check Anchor Target
        if (anchorTarget === "parent") {
            // Set Anchor Target - Morph To Object
            anchorTarget = parentContainer.paneContainer;
        } else {
            // Get Component By ID
            var targetComponent = cccRoot.componentInfo.getChildObject(anchorTarget);
            // Get Anchor Target
            anchorTarget = targetComponent !== null ? targetComponent.componentContainer.mainContainerObject : undefined;
        }

        // Check Anchor Target
        if (anchorTarget === null || anchorTarget === undefined) {
            console.warn("DComponentChildContainer.componentInfoConnections.onAnchorRightChanged - NO SUCH TARGET!");
            return undefined;
        }

        console.log("DComponentChildContainer.parseAnchors - anchorTarget: " + anchorTarget);

        // Check Anchor Point
        if (anchorPoint === "" || anchorPoint === undefined) {
            // Check If Need Anchoring Point
            if (needPoint) {
                console.warn("DComponentChildContainer.parseAnchors - NO ANCHOR POINT DEFINED!");
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
                console.warn("DComponentChildContainer.parseAnchors - anchorPoint: " + anchorPoint + " - INVALID ANCHOR POINT!");
            return undefined;
        }

        return anchorPoint;
    }

    // Component Loader
    DLoader {
        id: componentLoader
        anchors.fill: parent
    }

    // Component Label
    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: 0.05
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }
}
