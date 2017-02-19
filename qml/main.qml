import QtQuick 2.0

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

    MainGrabArea {
        id: mainGrabArea

        property bool xInit: false
        property bool yInit: false

        Component.onCompleted: {
        }

        onWidthChanged: {
            if (width > 0 && !xInit) {
                xInit = true;
                projectPane.x = STYLE.defaultMargin;
                propertiesPane.x = mainGrabArea.width - propertiesPane.width - STYLE.defaultMargin;

                demoViewContainer.x = (mainGrabArea.width - demoViewContainer.width) / 2
            }
        }

        onHeightChanged: {
            if (height > 0 && !yInit) {
                yInit = true;
                projectPane.y = (mainRoot.height - projectPane.height) / 2;
                propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;

                demoViewContainer.y = (mainRoot.height - demoViewContainer.height) / 2;
            }
        }

        onClicked: {
            // Hide Popups
            mainPopupArea.hidePopups();
        }

        // Project Pane
        ProjectPane {
            id: projectPane
            hideToSide: hideToLeft
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight
        }

        DViewContainer {
            id: demoViewContainer

            DFormulaEditor {
                id: formulaEditor
                x: 50
                y: 50
            }
        }

        DPopupArea {
            id: mainPopupArea
            anchors.fill: parent
        }

    }
}

