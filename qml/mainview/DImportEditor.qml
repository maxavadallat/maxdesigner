import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: importEditorRoot

    property string importName: "import"

    title: "Add Import"

    hideToSide: hideToRight

    creationWidth: 296
    creationHeight: 98

    minWidth: 296
    minHeight: 98

    enableResize: false
    enableHideButton: false

    property bool newImport: true

    property ComponentImportsModel importsModel: propertiesController.importsModel

    state: stateCreate

    onRejected: {
        // Reset Invalid Value
        importEditor.invalidValue = false;

    }

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Import Editor
            resetImportEditor();
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Editor Focus
            importEditor.setEditorFocus(true, true);
        }
    }

    onImportNameChanged: {
        // Check Import Editor Text
        if (importEditor.text !== importEditorRoot.importName) {
            // Set Import Editor Text
            importEditor.text = importEditorRoot.importName;
        }
    }

    // Validate Import
    function importValid(newText) {
        // Check Import Editor Text
        if (importEditorRoot.importsModel !== null) {
            return importEditorRoot.importsModel.importValid(newText);
        }

        return false;
    }

    // Reset Import Editor
    function resetImportEditor() {
        // Reset Import Name
        importEditorRoot.importName = "";
        // Set Invalid Value
        importEditor.invalidValue = false;
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Import Valid
            if (importEditorRoot.importValid(importEditor.editedText)) {
                // Set Import Name
                importEditorRoot.importName = importEditor.editedText;
                // Emit Accepted Signal
                importEditorRoot.accepted();
            } else {
                // Reset Invalid Value
                importEditor.invalidValue = false;
            }
        }
    }

    Row {
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
//        anchors.top: parent.top
//        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 10
        spacing: DStyle.defaultSpacing

        DText {
            id: nameLabel
            //width: propertyLabel.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "import:"
        }

        DTextInput {
            id: importEditor
            width: importEditorRoot.width - nameLabel.width - discButton.width - 48

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Rejected
                        importEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // ...
                    break;
                }
            }

            onAccepted: {
                // Check If Import Valid
                if (importEditorRoot.importValid(newText)) {
                    // Set Import Name
                    importEditorRoot.importName = newText;
                    // Accepted
                    importEditorRoot.accepted();
                } else {
                    // Set Invalid Value
                    importEditor.invalidValue = true;
                }
            }

            onTextEdited: {
                // Reset Invalid Value
                importEditor.invalidValue = false;
            }
        }
    }
}
