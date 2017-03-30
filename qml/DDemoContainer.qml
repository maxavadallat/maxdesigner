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

    DPropertyItem {
        id: opiDelegateRoot
        width: 300
        anchors.centerIn: parent
    }

    Flow {
        anchors.left: parent.left
        anchors.leftMargin: 32
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32

        layoutDirection: Qt.RightToLeft

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
            text: signalEditor.state === signalEditor.stateCreate ? "Create Signal" : "Reset Signal"

            onClicked: {
                if (signalEditor.state === signalEditor.stateCreate) {
                    signalEditor.show();
                } else {
                    signalEditor.reset(false);
                }
            }
        }

        DButton {
            width: 196
            text: signalParameterEditor.state === signalParameterEditor.stateCreate ? "Create Signal Parameter" : "Reset Signal Parameter"

            onClicked: {
                if (signalParameterEditor.state === signalParameterEditor.stateCreate) {
                    signalParameterEditor.show();
                } else {
                    signalParameterEditor.reset(false);
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
            width: 196
            text: propertyChangesEditor.state === propertyChangesEditor.stateCreate ? "Create Property Changes" : "Reset Property Changes"

            onClicked: {
                if (propertyChangesEditor.state === propertyChangesEditor.stateCreate) {
                    propertyChangesEditor.show();
                } else {
                    propertyChangesEditor.reset(false);
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
            width: 196
            text: transitionNodeEditor.state === transitionNodeEditor.stateCreate ? "Create Transition Node" : "Reset Transition Node"

            onClicked: {
                if (transitionNodeEditor.state === transitionNodeEditor.stateCreate) {
                    transitionNodeEditor.show();
                } else {
                    transitionNodeEditor.reset(false);
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

    // Signal Editor
    DSignalEditor {
        id: signalEditor

        state: stateCreate

        childPane: signalParameterEditor

        onNewParameter: {
            // Show Signal Parameter Editor
            signalParameterEditor.show();
        }
    }

    // Signal Parameter Editor
    DSignalParameterEditor {
        id: signalParameterEditor

        state: stateCreate

        parentPane: signalEditor

        initialX: signalEditor.x + signalEditor.width * 0.5
        initialY: signalEditor.y + signalEditor.height

        creationX: initialX - signalParameterEditor.width * 0.5
        creationY: initialY + 32
    }

    // State Editor
    DStateEditor {
        id: stateEditor

        state: stateCreate

        childPane: propertyChangesEditor

        onNewPropertyChange: {
            // Show Property Changes Editor
            propertyChangesEditor.show();
        }
    }

    // Property Changes Editor
    DPropertyChangesEditor {
        id: propertyChangesEditor

        state: stateCreate

        parentPane: stateEditor

        initialX: stateEditor.x + stateEditor.width * 0.5
        initialY: stateEditor.y + stateEditor.height

        creationX: initialX - propertyChangesEditor.width * 0.5
        creationY: initialY + 32
    }

    // Transition Editor
    DTransitionEditor {
        id: transitionEditor

        state: stateCreate

        childPane: transitionNodeEditor

        onNewTransitionNode: {
            // Set Node Type
            transitionNodeEditor.nodeType = nodeType;
            // Check Node Type
            if (nodeType > 2) {
                // Show Transition Node Editor
                transitionNodeEditor.show();
            }
        }
    }

    // Transition Node Editor
    DTransitionNodeEditor {
        id: transitionNodeEditor

        state: stateCreate

        parentPane: transitionEditor

        initialX: transitionEditor.x + transitionEditor.width * 0.5
        initialY: transitionEditor.y + transitionEditor.height

        creationX: initialX - transitionNodeEditor.width * 0.5
        creationY: initialY + 32
    }

/*
    Column {
        anchors.centerIn: parent
        spacing: DStyle.defaultSpacing

        DButton {
            //onClicked: checked = !checked;
            //enabled: propertiesPaneRoot.parent.enabled
            enabled: parent.enabled
        }

        DButton {
            //onClicked: checked = !checked;
            checked: true
            enabled: parent.enabled
        }

        DCheckBox {
            text: "CheckBox"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DCheckBox {
            rightAligned: true
            text: "CheckBox"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DSwitch {
            text: "Switch"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DSwitch {
            rightAligned: true
            text: "Switch"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DRadioButtonGroup {
            model: [
                DRadioButtonGroupItem { title: "Item 1" },
                DRadioButtonGroupItem { title: "Item 2" },
                DRadioButtonGroupItem { title: "Item 3" },
                DRadioButtonGroupItem { title: "Item 4" }
            ]

            onButtonSelected: {
                //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
                // Set Current Index
                currentIndex = buttonIndex;
            }
        }

        DRadioButtonGroup {
            rightAligned: true
            model: [
                DRadioButtonGroupItem { title: "Item 1" },
                DRadioButtonGroupItem { title: "Item 2" },
                DRadioButtonGroupItem { title: "Item 3" },
                DRadioButtonGroupItem { title: "Item 4" }
            ]

            onButtonSelected: {
                //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
                // Set Current Index
                currentIndex = buttonIndex;
            }
        }

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
