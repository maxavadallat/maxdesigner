import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: enumValueEditorRoot

    anchors.horizontalCenter: parentPane ? parentPane.horizontalCenter : undefined

    title: "New Value"

    hideToSide: hideToTop

    creationWidth: 400
    creationHeight: 98

    minWidth: 400
    minHeight: 98

    enableDrag: false

    enableResize: true
    enableHideButton: false

    resizeTopEnabled: false
    resizeBottomEnabled: false

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
        id: discButton
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
            width: enumValueEditorRoot.width - discButton.width - valueLabel.width - 32 - DStyle.defaultMargin * 3
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
