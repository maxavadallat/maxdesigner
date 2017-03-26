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

    property ComponentInfo componentInfo: null

//    signal accepted()
//    signal rejected()

    state: stateCreate

//    onAccepted: {
//        // Reset
//        signalParameterEditorRoot.reset(false);
//    }

//    onRejected: {
//        // Reset
//        signalParameterEditorRoot.reset(false);
//    }

    onTransitionFinished: {
        if (newState === stateShown) {
            nameEditor.setEditorFocus(true, true);
        }
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            signalParameterEditorRoot.accepted();

            // ...
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
            text: "name:"
        }

        DTextInput {
            id: nameEditor
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
        }
    }
}
