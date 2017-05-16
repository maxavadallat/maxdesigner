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

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

//    // Background Container
//    Rectangle {
//        id: bgContainer
//        anchors.fill: parent

//        color: DStyle.colorMainBG

//        Image {
//            id: bgImage
//            anchors.fill: parent
//            source: "qrc:/assets/images/tron-wide-wallpaper.jpeg"
//            fillMode: Image.PreserveAspectCrop
//            asynchronous: true
//            opacity: 0.1
//        }
//    }

    Rectangle {
        id: screenBorderRect
        width: liveController.screenWidth
        height: liveController.screenHeight
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -20
        color: "transparent"
        border.color: DStyle.colorBorderNoFocus
    }

    DLoader {
        id: contentLoader
        anchors.centerIn: parent
        anchors.verticalCenterOffset: screenBorderRect.anchors.verticalCenterOffset
        anchors.horizontalCenterOffset: screenBorderRect.anchors.horizontalCenterOffset
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

    DImage {
        anchors.centerIn: parent
        source: "qrc:/assets/images/dashboard.png"
    }

    DStateSelector {
        id: stateSelector
    }
}
