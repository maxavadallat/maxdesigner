import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

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
            property alias title: titleLabel.text
            width: CONSTS.componentItemWidth
            height: CONSTS.componentItemHeight

            DText {
                id: titleLabel
                anchors.centerIn: parent
                text: componentInfo ? componentInfo.componentName : ""
            }
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

        // ...
    }

    onFocusChanged: {
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
        componentRootContainerRoot.focus = true;
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

    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: componentRootContainerRoot.focus

        onWheel: {
            //console.log("#### delta: " + wheel.angleDelta.y);

            // Check Wheel Delta
            if (wheel.angleDelta.y > 2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale < 1.5) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Inc Scale Level
                    componentRootContainerRoot.scale += 0.025;
                }
            } else if (wheel.angleDelta.y < -2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale > 1.0) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Dec Scale Level
                    componentRootContainerRoot.scale -= 0.025;
                }
            }
        }
    }

    DNoContent {
        id: baseCanvas
        anchors.fill: parent
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
                                                                       "focus": true,
                                                                       "parentContainer": componentRootContainerRoot });

//            // Set Cloned Component Info
//            newObject.componentInfo = drop.source.clone();
//            // Add Child
//            componentRootContainerRoot.componentInfo.addChild(newObject.componentInfo);


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

    // ...

}
