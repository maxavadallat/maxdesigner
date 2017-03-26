import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: propertyEditorRoot

    hideToSide: hideToRight

    title: "New Property"

    creationWidth: 332
    creationHeight: 118

    minWidth: 332
    minHeight: 118

    enableResize: false

    property ComponentInfo componentInfo: null

    onTransitionStarted: {
        if (newState === stateHidden) {
            // Set Focus
            nameEditor.setEditorFocus(false);
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Focus
            nameEditor.setEditorFocus(true, true);
        }
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            propertyEditorRoot.accepted();

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
                id: nameEditor
                width: typeOption.width
                anchors.verticalCenter: parent.verticalCenter
                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Reset
                            propertyEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            // Set Focus
                            typeOption.setOptionFocus(true);
                        break;
                    }
                }
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
                    DPopupItemObject { text: "string" },
                    DPopupItemObject { text: "int" },
                    DPopupItemObject { text: "bool" },
                    DPopupItemObject { text: "double" },
                    DPopupItemObject { text: "var" },
                    DPopupItemObject { text: "QtObject" }
                ]

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Reset
                            propertyEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            // Set Focus
                            nameEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }
    }
}
