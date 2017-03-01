import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "Style.js" as STYLE

Item {
    id: mainRoot

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

    DWelcome {
        anchors.centerIn: parent
        //opacity: mainController.currentProject ? 0.0 : 1.0
        opacity: 0.0
    }

//    DPopupArea {
//        id: mainPopupArea
//        anchors.fill: parent
//        // ...
//    }

    MainGrabArea {
        id: mainGrabArea

        property bool xInit: false
        property bool yInit: false

        //opacity: mainController.currentProject ? 1.0 : 0.0

//        Component.onCompleted: {
//            projectPane.x = STYLE.defaultMargin;
//            projectPane.y = (mainRoot.height - projectPane.height) / 2;

//            propertiesPane.x = mainRoot.width - width - STYLE.defaultMargin;
//            propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;
//        }

        onWidthChanged: {
            if (width > 0 && !xInit) {
                xInit = true;
                projectPane.x = STYLE.defaultMargin;
                propertiesPane.x = mainGrabArea.width - propertiesPane.width - STYLE.defaultMargin;

                //demoPane.x = (mainGrabArea.width - demoPane.width) / 2;

                //demoContainer.x = (mainGrabArea.width - demoContainer.width) / 2;

                //demoViewContainer.x = (mainGrabArea.width - demoViewContainer.width) / 2;

                componentRootDemo.x = (mainGrabArea.width - componentRootDemo.width) / 2;

                //componentItemDemo.x = (mainGrabArea.width - componentItemDemo.width) / 2;

                //dropAreaDemo.x = (mainGrabArea.width - dropAreaDemo.width) / 2;
            }
        }

        onHeightChanged: {
            if (height > 0 && !yInit) {
                yInit = true;
                projectPane.y = (mainRoot.height - projectPane.height) / 2;
                propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;

                //demoPane.y = (mainRoot.height - demoPane.height) / 2;

                //demoContainer.y = (mainRoot.height - demoContainer.height) / 2;

                //demoViewContainer.y = (mainRoot.height - demoViewContainer.height) / 2;

                componentRootDemo.y = (mainGrabArea.height - componentRootDemo.height) / 2;

                //componentItemDemo.y = 100;

                //dropAreaDemo.y = mainGrabArea.height - dropAreaDemo.height - 32;
            }
        }

//        onClicked: {
//            // Hide Popups
//            //mainPopupArea.hidePopups();
//        }

        // Project Pane
        ProjectPane {
            id: projectPane
            hideToSide: hideToLeft

            //hidden: true
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight

            //hidden: true
        }

        DComponentRootContainer {
            id: componentRootDemo
            width: 400
            height: 300
        }
    }

    DMinimizedComponents {
        id: minimzedComponents
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

