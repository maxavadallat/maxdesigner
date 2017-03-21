import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: stateEditorRoot

    hideToSide: hideToRight

    title: "State Editor"

    creationWidth: 332
    creationHeight: 118

    minWidth: 332
    minHeight: 118

    property ComponentInfo componentInfo: null

    signal accepted()
    signal rejected()

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
            text: "Name:"
        }

        DTextInput {
            id: nameEdit
            width: 168
            anchors.verticalCenter: parent.verticalCenter
        }
    }

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
    }

}
