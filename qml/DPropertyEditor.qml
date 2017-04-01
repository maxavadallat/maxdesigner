import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: propertyEditorRoot

    property ComponentInfo componentInfo: null

    property alias propertyName: nameEditor.text
    property alias propertyType: typeOption.currentIndex
    property alias propertyDefault: defaultEditor.text

    title: "New Property"

    hideToSide: hideToRight

    creationWidth: 332
    creationHeight: 148

    minWidth: 332
    minHeight: 148

    enableResize: false

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
                    DPopupItemObject { text: CONSTS.propertyTypes[0] },
                    DPopupItemObject { text: CONSTS.propertyTypes[1] },
                    DPopupItemObject { text: CONSTS.propertyTypes[2] },
                    DPopupItemObject { text: CONSTS.propertyTypes[3] },
                    DPopupItemObject { text: CONSTS.propertyTypes[4] },
                    DPopupItemObject { text: CONSTS.propertyTypes[5] },
                    DPopupItemObject { text: CONSTS.propertyTypes[6] }
                ]

                onZChanged: {
                    parent.z = typeOption.z;
                }

                onItemSelected: {
                    // Set Focus
                    nameEditor.setEditorFocus(true, true);
                    // Switch Selected Index
                    switch (itemIndex) {
                        default:    defaultEditor.text = "";        break;
                        case 1:     defaultEditor.text = "0";       break;
                        case 2:     defaultEditor.text = "false";   break;
                        case 3:     defaultEditor.text = "0.0";     break;
                        case 5:     defaultEditor.text = "null";    break;
                    }
                }

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Reset
                            propertyEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            // Set Focus
                            defaultEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: defaultLabel
                width: 58
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "Default:"
            }

            DTextInput {
                id: defaultEditor
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
                            nameEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }
    }
}
