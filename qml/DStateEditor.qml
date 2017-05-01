import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: stateEditorRoot

    property ComponentState componentState: null
    property ComponentStatesModel statesModel: propertiesController.statesModel
    property bool newState: false

    hideToSide: hideToRight

    title: "State Editor"

    creationWidth: 460
    creationHeight: 118

    minWidth: 460
    minHeight: 118

    enableResize: false

    signal newPropertyChange()
    signal editPropertyChange()

    onTransitionFinished: {
        if (newState === stateShown) {
            nameEditor.setEditorFocus(true, true);
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
            stateEditorRoot.accepted();
            // Reset
            stateEditorRoot.reset(false);

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
            id: nameLabel
            //width: 58
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "name:"
        }

        DTextInput {
            id: nameEditor
            width: 128
            anchors.verticalCenter: parent.verticalCenter
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        stateEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        whenEditor.setEditorFocus(true, true);
                    break;
                }
            }
        }

        DText {
            id: whenLabel
            //width: 58
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "when:"
        }

        DTextInput {
            id: whenEditor
            width: 128
            anchors.verticalCenter: parent.verticalCenter
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        stateEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        nameEditor.setEditorFocus(true, true);
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
//        anchors.top: nameRow.bottom
//        anchors.topMargin: DStyle.defaultMargin
//        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        text: "Add Property Change"

        onClicked: {
            // Signal New Property Change
            stateEditorRoot.newPropertyChange();
        }
    }

}
