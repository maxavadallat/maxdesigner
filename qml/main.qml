import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "style"

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
            //console.log("main.Connections.mainController.onCurrentProjectChanged - currentProject: " + mainController.currentProject);

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

        color: Style.colorMainBG

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
            source: settingsController.designerMode === "Developer" ? "qrc:/assets/images/tron-wallpaper-23.jpeg"
                                                                    : "qrc:/assets/images/tron-wallpaper-27.jpeg"
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

        anchors.fill: parent

        // Project Pane
        ProjectPane {
            id: projectPane

            initialX: 0
            initialY: mainGrabArea.height / 2

            creationWidth: 360
            creationHeight: 600

            creationX: Style.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: projectPane.creationX
            lastShownY: projectPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane

            initialX: mainGrabArea.width
            initialY: mainGrabArea.height / 2

            creationWidth: 300
            creationHeight: 600

            creationX: parentWidth - creationWidth - Style.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: propertiesPane.creationX
            lastShownY: propertiesPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        DComponentRootContainer {
            id: componentRootContainer

            initialX: projectPane.x + projectPane.width
            initialY: Math.max(Math.min(mainGrabArea.height / 2, projectPane.y + projectPane.height - Style.defaultMargin), projectPane.y + Style.defaultMargin)

            creationWidth: 600
            creationHeight: 400

            creationX: parentWidth / 2 - creationWidth / 2
            creationY: initialY - creationHeight / 2

            lastShownX: componentRootContainer.creationX
            lastShownY: componentRootContainer.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        DFormulaEditor {
            id: formulaEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(mainGrabArea.height / 2, propertiesPane.y + propertiesPane.height - Style.defaultMargin), propertiesPane.y + Style.defaultMargin)

            creationWidth: 320
            creationHeight: 200

            creationX: parentWidth / 2 - creationWidth / 2 + 100
            creationY: initialY - creationHeight / 2 + 150

            lastShownX: formulaEditor.creationX
            lastShownY: formulaEditor.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
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

//    DColorTest {
//        id: colorTest
//    }
}

