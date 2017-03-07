import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "style"

DPaneBase {
    id: compoenntRootContainerRoot

    width: 600
    height: 400

    property bool explodingMode: false

    title: "Component"

    hideToSide: hideToBottom

    enablePosOverlay: false
    enableSizeOverlay: true

    showTitle: false
    showBackground: false

    clipContent: true

    rootContainer: true

    borderColor: dropArea.hovering || compoenntRootContainerRoot.focus ? Style.colorBorder : Style.colorBorderNoFocus
    radius: 0

    onPressed: {
        compoenntRootContainerRoot.focus = true;
    }

    onWidthChanged: {
        baseCanvas.requestPaint();
    }

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

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_Space:

            break;
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
