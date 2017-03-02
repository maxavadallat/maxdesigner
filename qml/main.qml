import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "Style.js" as STYLE

Item {
    id: mainRoot

    focus: true

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_T:
                settingsController.tracerVisible = !settingsController.tracerVisible;
            break;
        }
    }

    // Connections - Main Controller
    Connections {
        target: mainController

        onCurrentProjectChanged: {
            console.log("main.Connections.mainController.onCurrentProjectChanged - currentProject: " + mainController.currentProject);

            // Check Current Project
            if (mainController.currentProject != null) {
                // Hide Welcome Screen
                welcomScreen.hide();
                // Show Project Pane
                projectPane.show();
                // Show Properties Pane
                propertiesPane.show();
            } else {
                // Reset Project Pane
                projectPane.reset();
                // Reset Properties Pane
                propertiesPane.reset();
                // Show Welcome Screen
                welcomScreen.show();
            }
        }
    }

    Rectangle {
        id: bgContainer
        anchors.fill: parent

        color: STYLE.colorMainBG

        Image {
            id: bgImage
//            width: 1024
//            height: 640
//            anchors.right: parent.right
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: -256
//            fillMode: Image.PreserveAspectFit
//            source: "qrc:/assets/images/background02.png"
            anchors.fill: parent
            source: "qrc:/assets/images/tron-wallpaper-23.jpeg"
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            opacity: 0.1
        }
    }

//    DPopupArea {
//        id: mainPopupArea
//        anchors.fill: parent
//        // ...
//    }

    MainGrabArea {
        id: mainGrabArea

        // Project Pane
        ProjectPane {
            id: projectPane
            hideToSide: hideToLeft

            initialX: 0
            initialY: mainGrabArea.height / 2

            creationWidth: 360
            creationHeight: 600

            creationX: STYLE.defaultMargin * 2
            creationY: mainGrabArea.height / 2 - creationHeight / 2

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight

            initialX: mainGrabArea.width
            initialY: mainGrabArea.height / 2

            creationWidth: 300
            creationHeight: 600

            creationX: mainGrabArea.width - creationWidth - STYLE.defaultMargin * 2
            creationY: mainGrabArea.height / 2 - creationHeight / 2

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        DComponentRootContainer {
            id: componentRootDemo

            initialX: projectPane.x + projectPane.width
            initialY: Math.max(Math.min(mainGrabArea.height / 2, projectPane.y + projectPane.height - STYLE.defaultMargin), projectPane.y + STYLE.defaultMargin)

            creationWidth: 600
            creationHeight: 400

            creationX: mainGrabArea.width / 2 - creationWidth / 2
            //creationY: mainGrabArea.height / 2 - creationHeight / 2
            creationY: initialY - creationHeight / 2

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate

            enableSizeOverlay: false
            enablePosOverlay: false
        }
    }

    DWelcome {
        id: welcomScreen
        anchors.centerIn: parent
        state: stateShown
        //state: stateHidden
    }

    DMinimizedComponents {
        id: minimzedComponents
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

