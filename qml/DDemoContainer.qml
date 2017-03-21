import QtQuick 2.0
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DRectangle {
    id: demoContainerRoot

    width: 800
    height: 800

    clip: true
    focus: true

    border.color: demoContainerRoot.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

    Keys.onReleased: {
        switch (event.key) {

            case Qt.Key_F8:
                settingsController.slowMotion = !settingsController.slowMotion;
            break;

            case Qt.Key_T:
                settingsController.tracerVisible = !settingsController.tracerVisible;
            break;

            // ...
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            demoContainerRoot.focus = true;
        }
    }

    DDisc {
        anchors.centerIn: parent
        width: 512
        height: 512
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32

        spacing: DStyle.defaultSpacing

        DButton {
            width: 128
            text: propertyEditor.state === propertyEditor.stateCreate ? "Create Property" : "Reset Property"

            onClicked: {
                if (propertyEditor.state === propertyEditor.stateCreate) {
                    propertyEditor.show();
                } else {
                    propertyEditor.reset(false);
                }
            }
        }

        DButton {
            width: 128
            text: stateEditor.state === stateEditor.stateCreate ? "Create State" : "Reset State"

            onClicked: {
                if (stateEditor.state === stateEditor.stateCreate) {
                    stateEditor.show();
                } else {
                    stateEditor.reset(false);
                }
            }
        }

        DButton {
            width: 168
            text: transitionEditor.state === transitionEditor.stateCreate ? "Create Transition" : "Reset Transition"

            onClicked: {
                if (transitionEditor.state === transitionEditor.stateCreate) {
                    transitionEditor.show();
                } else {
                    transitionEditor.reset(false);
                }
            }
        }

        DButton {
            width: 188
            text: propertyChangesEditor.state === propertyChangesEditor.stateCreate ? "Create Property Changes" : "Reset Property Changes"

            onClicked: {
                if (propertyChangesEditor.state === propertyChangesEditor.stateCreate) {
                    propertyChangesEditor.show();
                } else {
                    propertyChangesEditor.reset(false);
                }
            }
        }

        // ...

    }

    // Property Editor
    DPropertyEditor {
        id: propertyEditor

        //initialX: propertiesPane.x
        //initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

        state: stateCreate
    }

    // State Editor
    DStateEditor {
        id: stateEditor

        state: stateCreate
    }

    DPropertyChangesEditor {
        id: propertyChangesEditor

        state: stateCreate
    }

    // Transition Editor
    DTransitionEditor {
        id: transitionEditor

        state: stateCreate
    }



/*
    DOption {
        anchors.centerIn: parent

        currentIndex: 0

        model: [
            DPopupItemObject { text: "Option 1" },
            DPopupItemObject { text: "Option 2" },
            DPopupItemObject { text: "Option 3" },
            DPopupItemObject { text: "Option 4" },
            DPopupItemObject { text: "Option 5" }
        ]
    }
*/
/*
    DCarousel {
        id: carouselDemo

        width: 400
        height: 300

        itemScale: 0.4
        delegateScale: 0.3
        visibleItems: 5
        showTitle: false

        anchors.centerIn: parent

        model: ListModel {
            ListElement {
                demoTitle: "Title 1"
            }
            ListElement {
                demoTitle: "Title 2"
            }
            ListElement {
                demoTitle: "Title 3"
            }
            ListElement {
                demoTitle: "Title 4"
            }
            ListElement {
                demoTitle: "Title 5"
            }
            ListElement {
                demoTitle: "Title 6"
            }
            ListElement {
                demoTitle: "Title 7"
            }
        }

        contentDelegate: DCarouselDelegate {
            itemTitle: itemData ? itemData.demoTitle : ""

            DRectangle {
                anchors.fill: parent
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
            }

            DText {
                anchors.centerIn: parent
                text: itemData ? itemData.demoTitle : ""
            }
        }
    }
*/
/*
    Component {
        id: demoComponent

        DRectangle {
            width: 128
            height: 96
        }
    }

    DButton {
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        text: "Test"
        onClicked: {
            var newObject = demoComponent.createObject(demoFlow.flowItem);
        }
    }

    Rectangle {
        anchors.fill: demoFlow
        color: "transparent"
        border.color: "purple"
    }

    DFlow {
        id: demoFlow
        width: 400
        anchors.centerIn: parent
    }
*/
//    DSourceContainer {
//        id: sourceContainerDemo
//        width: 600
//        height: 500
//        anchors.centerIn: parent
//    }

//    DActivityIndicator {
//        width: 420
//        height: 420
//        anchors.centerIn: parent
//        running: true
//    }

//    DColorTest {
//        id: colorTest
//    }

}
