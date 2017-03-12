import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "Constants.js" as CONSTS

DPane {
    id: propertiesPaneRoot

    width: 300
    height: 600

    title: "Properties" + (propertiesController.focusedComponent ? (" - " + propertiesController.focusedComponent.componentName) : "")

    minWidth: 300
    minHeight: 200

    enablePaneContent: propertiesController.focusedComponent !== null

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToRight

    borderColor: Style.colorBorder

    //state: stateShown

    property Connections propertiesControllerConnection: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Check Focused Component
            if (propertiesController.focusedComponent !== null) {
                // Open Sections
                sizeAndPosSection.open();

            } else {
                // Close All Sections
                sizeAndPosSection.close();
                anchorsSection.close();
                ownPropertiesSection.close();
                signalsSection.close();
                statesSection.close();
                transitionsSection.close();
            }
        }

        // ...
    }

    property Connections focusedComponentConnection: Connections {
        target: propertiesController.focusedComponent

        onWidthChanged: {
            console.log("PropertiesPane.focusedComponentConnection.onWidthChanged - width: " + propertiesController.focusedComponent.width);
        }

        onHeightChanged: {
            console.log("PropertiesPane.focusedComponentConnection.onHeightChanged - height: " + propertiesController.focusedComponent.height);
        }
    }

    Row {
        id: idRow
        spacing: 2

        DText {
            id: idTitle
            anchors.verticalCenter: parent.verticalCenter
            text: "id:"
        }

        DTextInput {
            width: propertiesPaneRoot.contentWidth - idTitle.width - 2
        }
    }

    Row {
        id: objectNameRow
        spacing: 2

        DText {
            id: objectNameTitle
            //width: propertiesPaneRoot.contentWidth
            anchors.verticalCenter: parent.verticalCenter
            text: "Object Name:"
        }

        DTextInput {
            width: propertiesPaneRoot.contentWidth - objectNameTitle.width - 2
        }
    }

    Item {
        width: 1
        height: Style.defaultSpacing
    }

    DSection {
        id: sizeAndPosSection
        width: propertiesPaneRoot.contentWidth
        title: "Size & Pos"
        minHeight: sizeAndPosFlow.height

        state: stateClosed
        //state: stateOpen

        DFlow {
            id: sizeAndPosFlow
            width: propertiesPaneRoot.contentWidth

            Row {
                id: posRow
                spacing: Style.defaultSpacing

                opacity: {
                    if (propertiesController.focusedComponent && propertiesController.focusedComponent.isRoot) {
                        return 0.0;
                    }

                    return 1.0;
                }

                Behavior on opacity { DFadeAnimation { } }
                visible: opacity > 0.0

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "x: "
                }

                DSpinner {
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posX) : 0
                }

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "y:"
                }

                DSpinner {
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posY) : 0
                }
            }

            Row {
                id: sizeRow
                spacing: Style.defaultSpacing

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "w:"
                }

                DSpinner {
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.width) : 0
                }

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "h:"
                }

                DSpinner {
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.height) : 0
                }
            }
        }
    }

    DSection {
        id: anchorsSection
        width: propertiesPaneRoot.contentWidth
        title: "Anchors & Margins"

        state: stateClosed
        //state: stateOpen

        Row {
            //height: anchorTargetEditor.height
            spacing: Style.defaultMargin * 0.25

            DCheckBox {
                id: anchorFillCheckBox
                width: 40
                rightAligned: true
                text: "fill"
                onClicked: checked = !checked
            }

            Item {
                width: 8
                height: parent.height
            }

            DText {
                id: anchorTargetLabel
                anchors.verticalCenter: parent.verticalCenter
                text: "target:"

            }

            DTextInput {
                width: propertiesPaneRoot.contentWidth - anchorTargetLabel.width - anchorFillCheckBox.width - Style.defaultMargin * 0.5 - 12
                anchors.verticalCenter: parent.verticalCenter
                text: "parent"
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: 210

            DCheckBox {
                width: 52
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                rightAligned: true
                text: "Left"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 60
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: "Right"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 52
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: "Top"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 78
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                text: "Bottom"
                onClicked: checked = !checked;
            }

            Column {
                anchors.centerIn: parent

                DCheckBox {
                    width: 152
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Horizontal Center"
                    onClicked: checked = !checked;
                }

                DCheckBox {
                    width: 78
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Center"
                    onClicked: checked = !checked;
                }

                DCheckBox {
                    width: 152
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Vertical Center"
                    onClicked: checked = !checked;
                }
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: Style.defaultMargin
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - leftMarginSpinner.width - Style.defaultMargin / 2
                text: "leftMargin: "
            }

            DSpinner {
                id: leftMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - rightMarginSpinner.width - Style.defaultMargin / 2
                text: "rightMargin: "
            }

            DSpinner {
                id: rightMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - topMarginSpinner.width - Style.defaultMargin / 2
                text: "topMargin: "
            }

            DSpinner {
                id: topMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - bottomMarginSpinner.width - Style.defaultMargin / 2
                text: "bottomMargin: "
            }

            DSpinner {
                id: bottomMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - horizontalCenterOffsetSpinner.width - Style.defaultMargin / 2
                text: "horizontal center offs: "
            }

            DSpinner {
                id: horizontalCenterOffsetSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - verticalCenterOffsetSpinner.width - Style.defaultMargin / 2
                text: "vertical center offs: "
            }

            DSpinner {
                id: verticalCenterOffsetSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }

    DSection {
        id: ownPropertiesSection
        width: propertiesPaneRoot.contentWidth
        title: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentName : ""
        minHeight: ownPropertiesContainer.height + addOwnPropertyButton.height
        state: stateHidden

        property Connections proppertiesControllerConnection: Connections {
            target: propertiesController

            onFocusedComponentChanged: {
                // Check Focused Component
                if (propertiesController.focusedComponent) {
                    // Open
                    ownPropertiesSection.open();
                } else {
                    // Hide Section
                    ownPropertiesSection.hide();
                }
            }
        }

        // Own Properties
        Item {
            id: ownPropertiesContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        DButton {
            id: addOwnPropertyButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Property"
            onClicked: {

            }
        }
    }

    DSection {
        id: signalsSection
        width: propertiesPaneRoot.contentWidth
        title: "Signals"
        minHeight: signalsContainer.height + addSignalButton.height

        // Signals
        Item {
            id: signalsContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        DButton {
            id: addSignalButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Signal"
        }
    }

    DSection {
        id: statesSection
        width: propertiesPaneRoot.contentWidth
        title: "States"
        minHeight: statesContainer.height + addStateButton.height

        state: stateClosed

        // States
        Item {
            id: statesContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        DButton {
            id: addStateButton
            width: propertiesPaneRoot.contentWidth
            text: "Add State"
        }
    }

    DSection {
        id: transitionsSection
        width: propertiesPaneRoot.contentWidth
        title: "Transitions"
        minHeight: transitionsContainer.height + addTransitionButton.height

        state: stateClosed

        // Transitions
        Item {
            id: transitionsContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        DButton {
            id: addTransitionButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Transition"
        }
    }

    // Parent

    // ...

    DSection {
        id: parentSection
        width: propertiesPaneRoot.contentWidth
        title: "Item"

        state: stateHidden
        //state: stateOpen

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
}
