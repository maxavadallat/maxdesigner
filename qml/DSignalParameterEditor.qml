import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: signalParameterEditorRoot

    title: "Parameter"

    hideToSide: hideToTop

    creationWidth: 272
    creationHeight: 98

    minWidth: 272
    minHeight: 98

    enableResize: false
    enableHideButton: false

    property ComponentSignal componentSignal: null
    property string signalParameter: ""
    property bool newParameter: false

    state: stateCreate

    onSignalParameterChanged: {
        // Check Name Editor Text
        if (parameterEditor.text !== signalParameterEditorRoot.signalParameter) {
            // Set Name Editor Text
            parameterEditor.text = signalParameterEditorRoot.signalParameter;
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            parameterEditor.setEditorFocus(true, true);
        }
    }

    // Check If Parameter Valid
    function parameterValid() {
        if (signalParameterEditorRoot.componentSignal !== null) {
            return signalParameterEditorRoot.componentSignal.parameterValid(parameterEditor.text);
        }

        return false;
    }

    // Reset Signal Parameter Editor
    function resetSignalParameterEditor() {
        // Reset Signal Parameter Text
        parameterEditor.text = "";
        // Reset Invalid Value
        parameterEditor.invalidValue = false;
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Parameter Valid
            if (parameterValid()) {
                // Set Signal Parameter
                signalParameterEditorRoot.signalParameter = parameterEditor.text;
                // Emit Accepted Signal
                signalParameterEditorRoot.accepted();
            } else {
                // Set Invalid Value
                parameterEditor.invalidValue = true;
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
            id: nameLabel
            //width: propertyLabel.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "name:"
        }

        DTextInput {
            id: parameterEditor
            width: 120
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Rejected
                        signalParameterEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // ...
                    break;
                }
            }

            onAccepted: {
                // Check If Parameter Valid
                if (parameterValid()) {
                    // Set Signal Parameter
                    signalParameterEditorRoot.signalParameter = parameterEditor.text;
                    // Emit Accepted Signal
                    signalParameterEditorRoot.accepted();
                } else {
                    // Set Invalid Value
                    parameterEditor.invalidValue = true;
                }
            }

            onTextChanged: {
                // Reset Invalid Value
                parameterEditor.invalidValue = false;
            }
        }
    }
}
