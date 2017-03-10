import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "style"

DPaneBase {
    id: compoenntRootContainerRoot

    width: 600
    height: 400

    property bool explodingMode: false

    property QtObject componentInfo: null

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

    borderColor: dropArea.hovering || compoenntRootContainerRoot.focus ? Style.colorBorder : Style.colorBorderNoFocus
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

        onFileSelected: {
            console.log("DComponentRootContainer.openFilesModelConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (compoenntRootContainerRoot.componentInfo.infoPath === aFilePath) {
                // Set Focus
                compoenntRootContainerRoot.focus = true;
            }

            // ...
        }
    }

    // Component Info Connections
    property Connections componentInfoConnection: Connections {
        target: compoenntRootContainerRoot.componentInfo

        onRequestContainerClose: {
            console.log("DComponentRootContainer.componentInfoConnection.onRequestContainerClose");

            // Save & Close
            compoenntRootContainerRoot.reset(true);
            // Reset Focused Component
            propertiesController.focusedComponent = null;

            // ...
        }
    }

    onFocusChanged: {
        // Check Focus & Component Info
        if (focus && componentInfo) {
//            // Check Previous Scale Level
//            if (compoenntRootContainerRoot.previousScale !== compoenntRootContainerRoot.scale) {
//                // Set Scale Duration
//                compoenntRootContainerRoot.scaleDuration = 100;
//                // Reset Scale
//                compoenntRootContainerRoot.scale = compoenntRootContainerRoot.previousScale;
//            } else {
//                // Reset Scale Duration
//                compoenntRootContainerRoot.scaleDuration = 0;
//            }

            // Reset Scale Duration
            compoenntRootContainerRoot.scaleDuration = 0;

            // Set Focused Component
            propertiesController.focusedComponent = compoenntRootContainerRoot.componentInfo;
        } else {
            // Reset Focused Component
            //propertiesController.focusedComponent = null;

            // Set Scale Duration
            compoenntRootContainerRoot.scaleDuration = 100;
//            // Save Previous Scale
//            compoenntRootContainerRoot.previousScale = compoenntRootContainerRoot.scale;
            // Reset Scale Level
            compoenntRootContainerRoot.scale = 1.0;
        }
    }

    onPressed: {
        compoenntRootContainerRoot.focus = true;
    }

    onWidthChanged: {
        baseCanvas.requestPaint();

        //propertiesController.requestCWidth()

        // ...
    }

    onHeightChanged: {

        // ...
    }

    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: compoenntRootContainerRoot.focus

        onWheel: {
            //console.log("#### delta: " + wheel.angleDelta.y);

            // Check Wheel Delta
            if (wheel.angleDelta.y > 2) {
                // Check Enable Scaling & Scale level
                if (compoenntRootContainerRoot.enableScaling && compoenntRootContainerRoot.scale < 1.5) {
                    // Reset Scale Duration
                    compoenntRootContainerRoot.scaleDuration = 0;
                    // Inc Scale Level
                    compoenntRootContainerRoot.scale += 0.025;
                }
            } else if (wheel.angleDelta.y < -2) {
                // Check Enable Scaling & Scale level
                if (compoenntRootContainerRoot.enableScaling && compoenntRootContainerRoot.scale > 1.0) {
                    // Reset Scale Duration
                    compoenntRootContainerRoot.scaleDuration = 0;
                    // Dec Scale Level
                    compoenntRootContainerRoot.scale -= 0.025;
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
            console.log("DComponentRootContainer.dropArea.onDropped - source: " + drop.source);

            // Reset Hovering
            hovering = false;

            // Reset Previous Scale Level
            compoenntRootContainerRoot.previousScale = 1.0;

            // Create New Object
            var newObject = newComponent.createObject(paneContainer, { "x": drop.x - CONSTS.componentItemWidth / 2,
                                                                       "y": drop.y - CONSTS.componentItemHeight / 2,
                                                                       "focus": true,
                                                                       "parentContainer": compoenntRootContainerRoot });

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
