import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: signalEditorRoot

    title: "Signal"

    hideToSide: hideToRight

    creationWidth: 332
    creationHeight: 118 + parameterFLow.height

    minWidth: 332
    minHeight: 118 + parameterFLow.height

    enableResize: false

    property ComponentSignal componentSignal: null
    property ComponentSignalsModel signalsModel: propertiesController.signalsModel

    property bool newSignal: true

    property Connections parameterEditorConnections: Connections {
        target: childPane

        onAccepted: {
            // Append Parameter

            // ...
        }
    }

    state: stateCreate

    signal newParameter()
    signal editParameter()

    onTransitionStarted: {
        if (newState === stateShown) {
            // Reset Signal Editor
            resetSignalEditor();
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
        }

        if (newState === stateHidden) {
            // Reset Focus
            nameEditor.setEditorFocus(false);
        }
    }

    onChildTransitionFinished: {
        if (newState === stateCreate) {
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
        }
    }

    onComponentSignalChanged: {
        // Check Name Editor Text
        if (signalEditorRoot.componentSignal !== null && nameEditor.text !== signalEditorRoot.componentSignal.signalName) {
            // Set Name Editor Text
            nameEditor.text = signalEditorRoot.componentSignal.signalName;
        }
    }

    // Check If Signal Valid
    function signalValid() {
        // Check Signals Model
        if (signalEditorRoot.signalsModel !== null) {
            return signalEditorRoot.signalsModel.signalValid(nameEditor.text);
        }

        return false;
    }

    // Reset Signal Editor
    function resetSignalEditor() {
        // Reset Name Text
        nameEditor.text = "";
        // Reset Invalid Value
        nameEditor.invalidValue = false;
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Signal Valid
            if (signalEditorRoot.signalValid()) {
                // ...
                // Emit Accepted Signal
                signalEditorRoot.accepted();
            } else {
                // Set Invalid Value
                nameEditor.invalidValue = true;
            }
        }
    }

    Row {
        id: nameRow
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        DText {
            id: nameLabel
            width: 64
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "name:"
        }

        DTextInput {
            id: nameEditor
            width: signalEditorRoot.width - nameLabel.width - discButton.width - 48
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        signalEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        //propertyEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: {
                // Check If Signal Name Valid
                if (signalEditorRoot.signalValid()) {
                    // ...
                } else {
                    // Set Invalid Value
                    nameEditor.invalidValue = true;
                }
            }

            onTextChanged: {
                // Reset Invalid Value
                nameEditor.invalidValue = false;
            }
        }
    }

    DFlow {
        id: parameterFLow

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: nameRow.bottom
        anchors.topMargin: DStyle.defaultMargin

        Repeater {
            id: parametersRepeater

            model: signalEditorRoot.componentSignal !== null ? signalEditorRoot.componentSignal.signalParameters : undefined

            delegate: DTag {
                tagTitle: signalEditorRoot.componentSignal.signalParameters[index]
                onRemoveClicked: {
                    // Remove Signal Parameter
                    signalEditorRoot.componentSignal.removeSignalParameter(index);
                }

                onDoubleClicked: {
                    signalEditorRoot.editParameter();
                }
            }
        }
    }

    DButton {
        width: nameRow.width
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        text: "Add Parameter"

        onClicked: {
            signalEditorRoot.newParameter();
        }
    }
}
