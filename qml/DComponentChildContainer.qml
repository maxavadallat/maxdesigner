import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DContainer {
    id: cccRoot

    property bool grabbed: false

    property ComponentInfo componentInfo: null

    backgroundColor: Qt.hsla(Math.random(), 0.5, 0.4, 0.2)
    borderColor: cccRoot.selected ? DStyle.colorBorderSelected : cccRoot.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus
    radius: 0

    enablePosOverlay: true
    enableSizeOverlay: true

    Component.onCompleted: {

    }

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_Backspace:
            case Qt.Key_Delete:

                // ...

                // Destroy
                cccRoot.destroy();

            break;
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent

        drag.target: cccRoot.grabbed ? cccRoot : undefined

        cursorShape: cccRoot.grabbed ? Qt.ClosedHandCursor : Qt.PointingHandCursor

        onPressed: {
            // Set Selected
            cccRoot.focus = true;
            // Check Modifiers
            if (mouse.modifiers === Qt.ShiftModifier) {
                // Toggle Selected
                cccRoot.selected = !cccRoot.selected;
            } else {
                // Set Grabbed
                cccRoot.grabbed = true;
            }
        }

        onReleased: {
            // Reset Grabbed
            cccRoot.grabbed = false;
        }

        onCanceled: {
            // Reset Grabbed
            cccRoot.grabbed = false;
        }
    }

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
        font.pixelSize: 64
        text: componentInfo ? componentInfo.componentName : ""
    }
}
