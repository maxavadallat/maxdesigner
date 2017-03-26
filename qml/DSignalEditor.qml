import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: signalEditorRoot

    title: "Signal"

    hideToSide: hideToRight

    creationWidth: 332
    creationHeight: 118

    minWidth: 332
    minHeight: 118

    enableResize: false

    property ComponentInfo componentInfo: null

    signal newParameter()
    signal editParameter()

//    onAccepted: {
//        // Reset
//        signalEditorRoot.reset(false);
//    }

//    onRejected: {
//        // Reset
//        signalEditorRoot.reset(false);
//    }

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

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            signalEditorRoot.accepted();

            // ...
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
            id: targetLabel
            width: 64
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "name:"
        }

        DTextInput {
            id: nameEditor
            width: 168
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
        }
    }

    // ...

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
