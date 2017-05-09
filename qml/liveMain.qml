import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

Item {
    id: liveRoot

    width: 640
    height: 480

    Connections {
        target: liveController

        onLoadContent: {
            // Set Source
            contentLoader.source = liveContent;
            // Set Active
            contentLoader.active = true;
        }

        onClearContent: {
            // Reset Active
            contentLoader.active = false;
            // Reset Source
            contentLoader.source = "";
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    DLoader {
        id: contentLoader
        anchors.centerIn: parent
        onStatusChanged: {
            // Switch Status
            switch (status) {
                case Loader.Ready:

                break;

                case Loader.Error:

                break;

                case Loader.Loading:

                break;
            }
        }
    }

    DStateSelector {
        id: stateSelector
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}
