import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQml.Models 2.2

import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../system"
import "../controls"
import "../animations"

DContainer {
    id: demoContainerRoot

    width: 1400
    height: 800

    clip: true

    enablePosOverlay: false
    enableSizeOverlay: false

    drag.filterChildren: false

    minWidth: 800
    minHeight: 800

    property int contentWidth: 400

    // Bring To Front
    function bringToFront(item) {
        // Check Item
        if (item === null || item === undefined) {
            return;
        }

        // Get Item Position
        var posX = item.x;
        var posY = item.y;

        // Set Item Parent To null To Remove From Children
        item.parent = null;
        // Set Item Parent To Bring To Front
        item.parent = demoContainerRoot;

        // Set Item Position
        item.x = posX;
        item.y = posY;
    }

    Component.onCompleted: {
//        // Open Project
//        mainController.openProject("/Users/max/Dev/Temp/myproject/myproject.json");

//        // Select Component
//        var focusedComponent = propertiesController.selectComponent("TestView");

//        // Set Component
//        demoComponentRootContainer.componentInfo = focusedComponent;

//        demoComponentRootContainer.initialX = 0;
//        demoComponentRootContainer.initialY = demoContainerRoot.height * 0.5;

//        demoComponentRootContainer.creationWidth = demoComponentRootContainer.componentInfo.width;
//        demoComponentRootContainer.creationHeight = demoComponentRootContainer.componentInfo.height;

//        demoComponentRootContainer.creationX = demoComponentRootContainer.parentWidth * 0.5 - demoComponentRootContainer.creationWidth * 0.5;
//        demoComponentRootContainer.creationY = demoComponentRootContainer.parentHeight * 0.5 - demoComponentRootContainer.creationHeight * 0.5;

//        // Show Demo Container
//        demoComponentRootContainer.show();
    }

//    DPaneSeparator {
//        id: paneSeparatorVertical
//        vertical: true
//    }

//    DPaneSeparator {
//        id: paneSeparatorHorizontal
//    }

//    DRectangle {
//        id: demoRectangle

//        width: 400
//        height: 300

//        anchors.centerIn: parent

//        states: [
//            State {
//                name: "state1"
//                PropertyChanges { target: demoRectangle; height: 100  }
//            },

//            State {
//                name: "state2"
//                PropertyChanges { target: demoRectangle; height: 200  }
//            },

//            State {
//                name: "state3"
//                PropertyChanges { target: demoRectangle; height: 300  }
//            },

//            State {
//                name: "state4"
//                PropertyChanges { target: demoRectangle; height: 400  }
//            }
//        ]

//       transitions: Transition {
//           //PropertyAnimation { target: demoRectangle; property: "height"; duration: 200 }
//           NumberAnimation { property: "height"; duration: 200 }
//       }
//    }

//    Row {
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: DStyle.defaultMargin * 4
//        spacing: DStyle.defaultSpacing

//        DButton {
//            width: 140
//            text: "state1"
//            onClicked: {
//                demoRectangle.state = "state1";
//            }
//        }

//        DButton {
//            width: 140
//            text: "state2"
//            onClicked: {
//                demoRectangle.state = "state2";
//            }
//        }

//        DButton {
//            width: 140
//            text: "state3"
//            onClicked: {
//                demoRectangle.state = "state3";
//            }
//        }

//        DButton {
//            width: 140
//            text: "state4"
//            onClicked: {
//                demoRectangle.state = "state4";
//            }
//        }

//    }

//    DComponentRootContainer {
//        id: demoComponentRootContainer

//        parentWidth: demoContainerRoot.width
//        parentHeight: demoContainerRoot.height
//    }

//    DButton {
//        width: 140
//        anchors.right: parent.right
//        anchors.rightMargin: 32
//        anchors.verticalCenter: parent.verticalCenter
//        text: "Rebuild Content"
//        onClicked: {
//            demoComponentRootContainer.rebuildContent();
//        }
//    }

//    DStateSelector {
//        id: demoStateSelector

//        componentInfo: propertiesController.focusedComponent

//        onSelectedStateChanged: {
//            console.log("liveMain.stateSelector.onSelectedStateChanged - selectedState: " + selectedState);

//            // Check Focused Component
//            if (propertiesController.focusedComponent !== null) {
//                // Set State
//                propertiesController.focusedComponent.componentState = selectedState;
//            }
//        }
//    }

    // ...
}
