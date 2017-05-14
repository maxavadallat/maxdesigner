import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

Item {
    id: liveRoot

    width: liveController.screenWidth
    height: liveController.screenHeight

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


    // Background Container
    Rectangle {
        id: bgContainer
        anchors.fill: parent

        color: DStyle.colorMainBG

        Image {
            id: bgImage
            anchors.fill: parent
            source: "qrc:/assets/images/tron-wide-wallpaper.jpeg"
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            opacity: 0.1
        }
    }

    Rectangle {
        width: liveController.screenWidth
        height: liveController.screenHeight
        anchors.centerIn: parent
        color: "transparent"
        border.color: DStyle.colorBorderNoFocus
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
                    console.warn("liveMain.contentLoader.onStatusChanged - status: " + status + " - ERROR LOADING CONTENT!!");
                break;

                case Loader.Loading:

                break;
            }
        }
    }

    DStateSelector {
        id: stateSelector
    }
}
