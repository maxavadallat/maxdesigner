import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DropArea {
    id: dropAreaRoot

    // ...

//    onEntered: {
//        console.log("#### onEntered");

//    }

//    onExited: {
//        console.log("#### onExited");

//    }

//    Rectangle {
//        anchors.fill: parent
//        color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.3)
//        border.color: dropAreaRoot.containsDrag ? "lime" : "transparent"
//    }
}

/*
DMouseArea {
    id: dropAreaRoot

    hoverEnabled: true

    property bool dragHovering: false

    property var dragSource: null

    property Connections systemModelConnections: Connections {
        target: DSystemModel

        onDragStarted: {

        }

        onDragDropped: {
            // Check Drag Hovering
            if (dropAreaRoot.dragHovering) {
                // Emit Dropped Signal
                dropAreaRoot.dropped();
            }
        }
    }

    // Set Visibility Based on Drag Active State
    visible: DSystemModel.dragActive

    signal dropped()

    onDragHoveringChanged: {
        // Check Drag Hovering
        if (dropAreaRoot.dragHovering) {
            // Set Drag Source
            dropAreaRoot.dragSource = DSystemModel.dragSource;
        } else {
            // Reset Drag Source
            dropAreaRoot.dragSource = null;
        }
    }

    onEntered: {
        // Set Drag Hovering
        dropAreaRoot.dragHovering = true;
    }

    onExited: {
        // Reset Drag Hovering
        dropAreaRoot.dragHovering = false;
    }

    onCanceled: {
        // Reset Drag Hovering
        dropAreaRoot.dragHovering = false;
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.3)
        border.color: dropAreaRoot.dragHovering ? "lime" : "transparent"
    }
}
*/
