import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: propertyChangesEditorRoot

    title: "Property Change"

    hideToSide: hideToTop

    creationWidth: 440
    creationHeight: 152

    minWidth: 440
    minHeight: 152

    property ComponentInfo componentInfo: null

    signal accepted()
    signal rejected()

    onAccepted: {
        // Reset
        propertyChangesEditorRoot.reset(false);
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            propertyChangesEditorRoot.accepted();

            // ...
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: targetLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "target:"
            }

            DTextInput {
                id: targetEditor
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: propertyLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "property:"
            }

            DTextInput {
                id: propertyEditor
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: valueLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "value:"
            }

            DTextInput {
                id: valueEditor
            }
        }
    }
}
