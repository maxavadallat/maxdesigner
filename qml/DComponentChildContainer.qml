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
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorLeftChanged - aLeft: " + aLeft);

            // ...
        }

        // Left Anchor Margin Changed
        onAnchorLeftMarginChanged: {
            // Set Left Margin
            cccRoot.anchors.leftMargin = aMargin;
        }

        // Right Anchor Changed
        onAnchorRightChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorRightChanged - aRight: " + aRight);

            // ...
        }

        // Right Anchor Margin Changed
        onAnchorRightMarginChanged: {
            // Set Right Margin
            cccRoot.anchors.rightMargin = aMargin;
        }

        // Top Anchor Changed
        onAnchorTopChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorTopChanged - aTop: " + aTop);

            // ...
        }

        // Top Anchor Margin Changed
        onAnchorTopMarginChanged: {
            // Set Top Margin
            cccRoot.anchors.topMargin = aMargin;
        }

        // Bottom Anchor Changed
        onAnchorBottomChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorBottomChanged - aBottom: " + aBottom);

            // ...
        }

        // Bottom Anchor Margin Changed
        onAnchorBottomMarginChanged: {
            // Set Bottom Margin
            cccRoot.anchors.bottomMargin = aMargin;
        }

        // Fill Anchor Changed
        onAnchorFillChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorFillChanged - aFill: " + aFill);

            // ...
        }

        // Fill Anchor Margin Changed
        onAnchorFillMarginChanged: {
            // Set Anchor Margins
            cccRoot.anchors.margins = aMargin;
        }

        // Center Anchor Changed
        onAnchorCenterInChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorCenterInChanged - aCenterIn: " + aCenterIn);

            // ...
        }

        // Horizontal Center Anchor Changed
        onAnchorHorizontalCenterChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorHorizontalCenterChanged - aHorizontalCenter: " + aHorizontalCenter);

            // ...
        }

        // Vertical Center Anchor Changed
        onAnchorVerticalCenterChanged: {
            console.log("DComponentChildContainer.componentInfoConnections.onAnchorVerticalCenterChanged - aVerticalCenter: " + aVerticalCenter);

            // ...
        }

        // Horizontal Center Anchor Offset Changed
        onAnchorHorizontalCenterOffsetChanged: {
            // Set Horizontal Center Offset
            cccRoot.anchors.horizontalCenterOffset = aOffset;
        }

        // Vertical Center Anchor Offset Changed
        onAnchorVerticalCenterOfsetChanged: {
            // Set Vertical Center Offset
            cccRoot.anchors.verticalCenterOffset = aOffset;
        }

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

    radius: 0

    enablePosOverlay: true
    enableSizeOverlay: true
    setFocusOnResize: true

    drag.minimumX: -cccRoot.width
    drag.maximumX: parent.width
    drag.minimumY: -cccRoot.height
    drag.maximumY: parent.height

    Component.onDestruction: {
        // Reset Component Info
        cccRoot.componentInfo = null;
        // Reset Update Component Info Enabled
        cccRoot.updateComponentInfoEnabled = false;
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
        // Set Last Mouse Press Owner
        DSystemModel.lastMousePressOwner = "cccRoot";

        // ...
    }

    onReleased: {
        //console.log("DComponentChildContainer.onReleased");

        // Check Last Mouse Press Owner
        if (DSystemModel.lastMousePressOwner === "cccRoot") {
            // Reset Last Mouse Press Owner
            DSystemModel.lastMousePressOwner = "";

            // Set Focus
            cccRoot.focus = true;

//            // Check Modifier Keys
//            if (mouse.modifiers | Qt.ShiftModifier) {
//                // Toggle Selected
//                cccRoot.selected = !cccRoot.selected;

//            } else {
//                // Set Focus
//                cccRoot.focus = true;
//            }
        }
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
            // Request Component Pos X
            propertiesController.requestCX(cccRoot.x);
        }
    }

    onYChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Request Component Pos Y
            propertiesController.requestCY(cccRoot.y);
        }
    }

    onWidthChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Request Component Width
            propertiesController.requestCWidth(cccRoot.width);
        }
    }

    onHeightChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Request Component Height
            propertiesController.requestCHeight(cccRoot.height);
        }
    }

    // ...

    Loader {
        id: componentLoader
        anchors.fill: parent
        asynchronous: true
        active: false
    }

    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: 0.05
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }
}
