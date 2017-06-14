import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"

Item {
    id: liveRoot

    width: liveController.screenWidth
    height: liveController.screenHeight

    Connections {
        target: liveController

        onLiveMainChanged: {
            // Check Live Main
            if (liveController.liveMain !== "") {
                // Set Active
                contentLoader.active = true;
            } else {
                // Set Active
                contentLoader.active = false;
            }
        }
    }

    // Background Rect
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

    // Screen Border Rect
    Rectangle {
        id: screenBorderRect
        width: liveController.screenWidth
        height: liveController.screenHeight
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 0
        color: "transparent"
        border.color: DStyle.colorBorderNoFocus

        // Content Loader
        DLoader {
            id: contentLoader
            anchors.centerIn: parent
//            anchors.verticalCenterOffset: screenBorderRect.anchors.verticalCenterOffset
//            anchors.horizontalCenterOffset: screenBorderRect.anchors.horizontalCenterOffset

            source: liveController.liveMain.length > 0 ? "file://" + liveController.liveMain : ""

            onStatusChanged: {
                // Switch Status
                switch (status) {
                    case Loader.Ready:
                        console.log("liveMain.contentLoader.onStatusChanged - READY!");
                    break;

                    case Loader.Error:
                        console.warn("liveMain.contentLoader.onStatusChanged - status: " + status + " - ERROR LOADING CONTENT!!");
                    break;

                    case Loader.Loading:

                    break;
                }
            }
        }
    }

    // Error Text
    DText {
        anchors.centerIn: parent
        font.pixelSize: DStyle.fontSizeXXL
        text: "Error Loading Live Content... X ("
        visible: contentLoader.status === Loader.Error
    }

    // Dashboard Image
    DImage {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 22
        //source: "qrc:/assets/images/dashboard.png"
        source: "file://" + propertiesController.currentProject.dashboard
        visible: settingsController.showDashboard
    }

    // State Selector
    DStateSelector {
        id: stateSelector

        componentInfo: liveController.currentComponent

        onSelectedStateChanged: {
            // Check Content Loader's Item
            if (contentLoader.item !== null) {
                console.log("liveMain.stateSelector.onSelectedStateChanged - selectedState: " + stateSelector.selectedState);
                // Set State
                contentLoader.item.state = stateSelector.selectedState;
            }
        }
    }
}
