import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DPaneBase {
    id: componentRootContainerRoot

    width: 600
    height: 400

    property bool explodingMode: false

    property ComponentInfo componentInfo: null

    property bool updateComponentInfoEnabled: false

    title: "Component" + (componentInfo ? (" - " + componentInfo.componentName  ) : "")

    hideToSide: hideToBottom

    enablePosOverlay: false
    enableSizeOverlay: false

    showTitle: false
    showBackground: false

    clipContent: true

    rootContainer: true

    focusOnShow: true

    enableSizeOverlayOnShow: true

    enableScaling: true

    borderColor: {
        if (dropArea.hovering) {
            return DStyle.colorBorder;
        }

        // Check Focused Component
        if (propertiesController.focusedComponent === componentInfo) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    radius: 0

    // New Child Component
    property Component newComponent: Component {

        DComponentChildContainer {
            width: CONSTS.componentItemWidth
            height: CONSTS.componentItemHeight
        }
    }

    // New State Component
    property Component newState: Component {
        State {

        }
    }

    // New Transition Component
    property Component newTransition: Component {
        Transition {

        }
    }

    // Properties Controller Connection
    property Connections propertiesControllerConnection: Connections {
        target: propertiesController

    }

    // Open Files Model Connection
    property Connections openFilesModelConnection: Connections {
        target: openFilesModel

        onComponentSelected: {
            console.log("DComponentRootContainer.openFilesModelConnection.onComponentSelected - aComponent: " + aComponent);

            // Check Component Info
            if (componentRootContainerRoot.componentInfo === aComponent) {
                // Check State
                if (componentRootContainerRoot.state === componentRootContainerRoot.stateHidden) {
                    // Show
                    componentRootContainerRoot.show();
                } else {
                    // Set Focus
                    componentRootContainerRoot.focus = true;
                    // Bring To Front
                    componentRootContainerRoot.parent.bringToFront(componentRootContainerRoot);
                }
            }

            // ...
        }

        onFileSelected: {
            console.log("DComponentRootContainer.openFilesModelConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.infoPath === aFilePath) {
                // Check State
                if (componentRootContainerRoot.state === componentRootContainerRoot.stateHidden) {
                    // Show
                    componentRootContainerRoot.show();
                } else {
                    // Set Focus
                    componentRootContainerRoot.focus = true;
                    // Bring To Front
                    componentRootContainerRoot.parent.bringToFront(componentRootContainerRoot);
                }
            }

            // ...
        }

        onComponentClosed: {
            console.log("DComponentRootContainer.openFilesModelConnection.onComponentClosed - aComponent: " + aComponent);

            // Check Component Info
            if (componentRootContainerRoot.componentInfo === aComponent) {
                // Reset
                componentRootContainerRoot.reset(true);
            }
        }

        onFileClosed: {
            console.log("DComponentRootContainer.openFilesModelConnection.onFileClosed - aFilePath: " + aFilePath);

            // Check File Path
            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.infoPath === aFilePath) {
                // Reset
                componentRootContainerRoot.reset(true);
            }
        }
    }

    // Component Info Connections
    property Connections componentInfoConnection: Connections {
        target: componentRootContainerRoot.componentInfo

        onRequestContainerClose: {
            console.log("DComponentRootContainer.componentInfoConnection.onRequestContainerClose");

            // Save & Close
            componentRootContainerRoot.reset(true);
            // Reset Focused Component
            propertiesController.focusedComponent = null;

            // ...
        }

        onWidthChanged: {
            // Check Width
            if (componentRootContainerRoot.width !== aWidth) {
                // Calculate Center X
                var centerX = componentRootContainerRoot.x + componentRootContainerRoot.width * 0.5;
                // Set Pos X
                componentRootContainerRoot.x = centerX - aWidth * 0.5;
                // Set Width
                componentRootContainerRoot.width = aWidth;
            }
        }

        onHeightChanged: {
            // Check Height
            if (componentRootContainerRoot.height !== aHeight) {
                // Calculate Center Y
                var centerY = componentRootContainerRoot.y + componentRootContainerRoot.height * 0.5;
                // Set Pos Y
                componentRootContainerRoot.y = centerY - aHeight * 0.5;
                // Set Height
                componentRootContainerRoot.height = aHeight;
            }
        }

        // On Component Property Changed
        onComponentPropertyChanged: {
            console.log("DComponentRootContainer.componentInfoConnection.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // ...
        }

        // ...
    }

    onFocusChanged: {
        //console.log("DComponentRootContainer.onFocusChanged - focus: " + focus);

        // Check Focus & Component Info
        if (focus && componentInfo) {
            // Reset Scale Duration
            componentRootContainerRoot.scaleDuration = 0;

            // Set Focused Component
            propertiesController.focusedComponent = componentRootContainerRoot.componentInfo;

            // Set Focused File
            openFilesModel.focusedFile = componentRootContainerRoot.componentInfo ? componentRootContainerRoot.componentInfo.infoPath : "";

        } else {
            // Set Scale Duration
            componentRootContainerRoot.scaleDuration = 100;
            // Reset Scale Level
            componentRootContainerRoot.scale = 1.0;
        }
    }

    onPressed: {
        //console.log("DComponentRootContainer.onPressed");
        // Set Last Mouse Press Owner
        DSystemModel.lastMousePressOwner = "crcRoot";

        // ...
    }

    onReleased: {
        //console.log("DComponentRootContainer.onReleased");
        // Check Last Mouse Press Owner
        if (DSystemModel.lastMousePressOwner === "crcRoot") {
            // Reset Last Mouse Press Owner
            DSystemModel.lastMousePressOwner = "";
            // Set Focus
            componentRootContainerRoot.focus = true;
        }
    }

    onWidthChanged: {
        //baseCanvas.requestPaint();

        // Check Update Component Info Enabled
        if (componentRootContainerRoot.updateComponentInfoEnabled) {
            // Request Width Change
            propertiesController.requestCWidth(componentRootContainerRoot.width);
        }


        // ...
    }

    onHeightChanged: {
        //baseCanvas.requestPaint();

        // Check Update Component Info Enabled
        if (componentRootContainerRoot.updateComponentInfoEnabled) {
            // Request Height Change
            propertiesController.requestCHeight(componentRootContainerRoot.height);
        }

        // ...
    }

    onTransitionFinished: {
        // Check State
        if (componentRootContainerRoot.state === componentRootContainerRoot.stateShown) {
            // Set Focus
            componentRootContainerRoot.focus = true;
            // Set Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = true;
        } else {
            // Reset Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = false;
        }
    }

    onStateChanged: {
        // Check State
        if (componentRootContainerRoot.state !== componentRootContainerRoot.stateShown) {
            // Reset Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = false;
        }
    }

    // Remove Child Component
    function removeChildComponent(childComponentObject) {
        console.log("DComponentRootContainer.removeChildComponent - childComponentObject: " + childComponentObject);

        // Set Focus
        componentRootContainerRoot.focus = true;

        // Check ComponentInfo
        if (componentRootContainerRoot.componentInfo) {
            // Remove Child
            componentRootContainerRoot.componentInfo.removeChild(childComponentObject.componentInfo);
        }

        // Check Child Object
        if (childComponentObject) {
            // Reset Component Info
            childComponentObject.componentInfo = null;
            // Destroy Child Component Object
            childComponentObject.destroy();
        }

    }

    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: componentRootContainerRoot.focus

        property real scaleMin: 1.0
        property real scaleMax: 2.0
        property real scaleSpeed: 0.05

        onWheel: {
            //console.log("#### delta: " + wheel.angleDelta.y);

            // Check Wheel Delta
            if (wheel.angleDelta.y > 2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale < wheelArea.scaleMax) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Inc Scale Level
                    componentRootContainerRoot.scale += wheelArea.scaleSpeed;
                }
            } else if (wheel.angleDelta.y < -2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale > wheelArea.scaleMin) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Dec Scale Level
                    componentRootContainerRoot.scale -= wheelArea.scaleSpeed;
                }
            }
        }
    }

    DNoContent {
        id: baseCanvas
        anchors.fill: parent
        visible: {
            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.childCount > 0) {
                return false;
            }

            return true;
        }
    }

    DropArea {
        id: dropArea
        anchors.fill: parent

        property bool hovering: false
        property int hoverX: 0
        property int hoverY: 0

        onEntered: {
            // Set Hovering
            hovering = true;

            //hoverX = drag.x;
            //hoverY = drag.y;

            if (drag.keys[0] === CONSTS.newComponentDragKey) {
                //console.log("DComponentRootContainer.dropArea.onEntered - keys: " + drag.keys);
                // Accept Drag
                drag.accept();
            }
        }

        onPositionChanged: {
            hoverX = drag.x;
            hoverY = drag.y;

            //console.log("DComponentRootContainer.dropArea.onPositionChanged - drag:[" + hoverX + ":" + hoverY + "]");

            debugCanvas.requestPaint();
        }

        onExited: {
            // Reset Hovering
            hovering = false;
        }

        onDropped: {
            // Check Source
            if (drop.source === null) {
                console.warn("DComponentRootContainer.dropArea.onDropped - NULL SOURCE!!");
                return;
            }

            console.log("DComponentRootContainer.dropArea.onDropped - source: " + drop.source);
            //console.log("DComponentRootContainer.dropArea.onDropped - dynamicProperties: " + drop.source.dynamicProperties);

            // Reset Hovering
            hovering = false;

            // Reset Previous Scale Level
            componentRootContainerRoot.previousScale = 1.0;

            // Create New Object
            var newObject = newComponent.createObject(paneContainer, { "x": drop.x - CONSTS.componentItemWidth / 2,
                                                                       "y": drop.y - CONSTS.componentItemHeight / 2,
                                                                       "parentContainer": componentRootContainerRoot });
            // Check New Object
            if (newObject) {
                // Set Cloned Component Info
                newObject.componentInfo = drop.source.clone();
                // Add Child
                componentRootContainerRoot.componentInfo.addChild(newObject.componentInfo);
                // Set Focus
                newObject.focus = true;

            } else {
                console.error("DComponentRootContainer.dropArea.onDropped - ERROR CREATING NEW OBJECT!");
            }

            // ...

        }

        Canvas {
            id: debugCanvas
            anchors.fill: parent
            visible: settingsController.tracerVisible && dropArea.hovering
            onPaint: {
                // Get 2D Context
                var ctx = getContext("2d");

                ctx.reset();

                ctx.lineWidth = 1;
                ctx.strokeStyle = "lime";

                ctx.beginPath();
                ctx.moveTo(dropArea.hoverX, 0);
                ctx.lineTo(dropArea.hoverX, dropArea.height);
                ctx.closePath();
                ctx.stroke();

                ctx.beginPath();
                ctx.moveTo(0, dropArea.hoverY);
                ctx.lineTo(dropArea.width, dropArea.hoverY);
                ctx.closePath();
                ctx.stroke();
            }
        }
    }

    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: 0.05
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }

    // ...

}
