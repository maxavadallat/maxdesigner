import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: enumValueEditorRoot

    title: "New Value"

    hideToSide: hideToTop

    creationWidth: 272
    creationHeight: 98

    minWidth: 272
    minHeight: 98

    enableResize: false
    enableHideButton: false

    property string enumValue: ""

    property bool newEnumValue: false

    state: stateCreate

    onEnumValueChanged: {
        // Check Name Editor Text
        if (enumValueEditor.text !== enumValueEditorRoot.enumValue) {
            // Set Name Editor Text
            enumValueEditor.text = enumValueEditorRoot.enumValue;
        }
    }

    onTransitionFinished: {
        // Check State
        if (newState === stateShown) {
            // Set Editor Focus
            enumValueEditor.setEditorFocus(true, true);
        }
    }

    // Check If Enum Value Valid
    function enumValueValid(newText) {
        return parentPane.enumValueValid(newText);
    }

    // Reset Enum Value Editor
    function resetEnumValueEditor() {
        // Reset Enum Value Text
        enumValueEditor.text = "";
        // Reset Invalid Value
        enumValueEditor.invalidValue = false;
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Enum Value Valid
            if (enumValueValid(enumValueEditor.editedText)) {
                // Set Enum Value
                enumValueEditorRoot.enumValue = enumValueEditor.editedText;
                // Emit Accepted Signal
                enumValueEditorRoot.accepted();
            } else {
                // Set Invalid Value
                enumValueEditor.invalidValue = true;
            }
        }
    }

    Row {
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 10
        spacing: DStyle.defaultSpacing

        DText {
            id: valueLabel
            //width: propertyLabel.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "value:"
        }

        DTextInput {
            id: enumValueEditor
            width: 120
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Rejected
                        enumValueEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // ...
                    break;
                }
            }

            onAccepted: {
                // Check If Parameter Valid
                if (enumValueValid(newText)) {
                    // Set Enum Value
                    enumValueEditorRoot.enumValue = newText;
                    // Emit Accepted Signal
                    enumValueEditorRoot.accepted();
                } else {
                    // Set Invalid Value
                    enumValueEditor.invalidValue = true;
                }
            }

            onTextEdited: {
                // Reset Invalid Value
                enumValueEditor.invalidValue = false;
            }
        }
    }
}
