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
            width: 1024
            height: 640
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -256
            source: "qrc:/assets/images/background02.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    DWelcome {
        anchors.centerIn: parent
        //opacity: mainController.currentProject ? 0.0 : 1.0
        opacity: 0.0
    }

    MainGrabArea {
        id: mainGrabArea

        property bool xInit: false
        property bool yInit: false

        //opacity: mainController.currentProject ? 1.0 : 0.0

        onWidthChanged: {
            if (width > 0 && !xInit) {
                xInit = true;
                projectPane.x = STYLE.defaultMargin;
                propertiesPane.x = mainGrabArea.width - propertiesPane.width - STYLE.defaultMargin;

                componentItemDemo.x = (mainGrabArea.width - componentItemDemo.width) / 2;

                dropAreaDemo.x = (mainGrabArea.width - dropAreaDemo.width) / 2;
            }
        }

        onHeightChanged: {
            if (height > 0 && !yInit) {
                yInit = true;
                projectPane.y = (mainRoot.height - projectPane.height) / 2;
                propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;

                componentItemDemo.y = (mainGrabArea.height - componentItemDemo.height) / 2;

                dropAreaDemo.y = mainGrabArea.height - dropAreaDemo.height - 32;
            }
        }

        // Project Pane
        ProjectPane {
            id: projectPane
            hideToSide: hideToLeft

            enablePaneContent: true
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight

            enablePaneContent: true
        }

        DComponentItem {
            id: componentItemDemo
        }

        DropArea {
            id: dropAreaDemo
            width: 320
            height: 200

            property bool hovering: false

            onEntered: {
                hovering = true;

            }

            onExited: {
                hovering = false;
            }

            onDropped: {
                // ...
            }

            Rectangle {
                anchors.fill: parent
                color: Qt.hsla(Math.random(), 0.5, 0.5, 0.3)
                border.color: dropAreaDemo.hovering ? STYLE.colorBorder : STYLE.colorBorderNoFocus
                radius: STYLE.defaultRadius
            }
        }

    }

    DMinimizedComponents {
        id: minimzedComponents
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

