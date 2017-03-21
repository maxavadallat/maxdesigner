import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: propertyEditorRoot

    hideToSide: hideToRight

    title: "New Property"

    creationWidth: 332
    creationHeight: 120

    minWidth: 332
    minHeight: 120

    property ComponentInfo componentInfo: null

    enableResize: false

    signal accepted()
    signal rejected()

    onTransitionStarted: {
        if (newState === stateHidden) {
            // Set Focus
            nameEdit.setEditorFocus(false);
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Focus
            nameEdit.setEditorFocus(true);
        }
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            propertyEditorRoot.accepted();
            // Reset
            propertyEditorRoot.reset(false);

            // ...
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.verticalCenterOffset: titleLabel.height
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: nameLabel
                width: 58
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "Name:"
            }

            DTextInput {
                id: nameEdit
                width: typeOption.width
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: typeLabel
                width: 58
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "Type:"
            }

            DOption {
                id: typeOption
                //width: propertyEditorRoot.width - 64
                anchors.verticalCenter: parent.verticalCenter
                model: [
                    DPopupItemObject { text: "Option 1" },
                    DPopupItemObject { text: "Option 2" },
                    DPopupItemObject { text: "Option 3" },
                    DPopupItemObject { text: "Option 4" },
                    DPopupItemObject { text: "Option 5" }
                ]
            }
        }
    }
}
