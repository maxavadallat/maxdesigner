import QtQuick 2.0

import enginecomponents 0.1

import "Style.js" as STYLE
import "Constants.js" as CONSTS

DPane {
    id: propertiesPaneRoot

    width: 300
    height: 500

    title: "Properties"

    minWidth: 300
    minHeight: 200

    state: stateShown

    Row {
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
        height: STYLE.defaultSpacing
    }

    DSection {
        width: propertiesPaneRoot.contentWidth
        title: "Size & Pos"
        state: stateOpen
        minHeight: 120

        Row {
            id: posRow
            spacing: STYLE.defaultSpacing

            DText {
                width: 24
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "x:"
            }

            DSpinner {
                anchors.verticalCenter: parent.verticalCenter
            }

            DText {
                width: 24
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "y:"
            }

            DSpinner {
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            id: sizeRow
            spacing: STYLE.defaultSpacing

            DText {
                width: 24
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "w:"
            }

            DSpinner {
                anchors.verticalCenter: parent.verticalCenter
            }

            DText {
                width: 24
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "h:"
            }

            DSpinner {
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    DSection {
        width: propertiesPaneRoot.contentWidth
        title: "Anchors & Margins"
    }

    DSection {
        width: propertiesPaneRoot.contentWidth
        title: "States"
    }

    DSection {
        width: propertiesPaneRoot.contentWidth
        title: "Transitions"
    }

    DSection {
        id: itemSection
        width: propertiesPaneRoot.contentWidth
        title: "Item"

        state: stateOpen

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


/*
    Row {
        id: posRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "x:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "y:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }
    }

    Row {
        id: sizeRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "w:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "h:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }
    }

    Row {
        id: horizontalAnchoringRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing


    }
*/
}
