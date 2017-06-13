import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"

DSection {
    id: anchorsSectionRoot
    width: 300
    property int editorsWidth: (anchorsSectionRoot.width - DStyle.defaultMargin * 4) / 3
    title: "Anchors & Margins"
    state: stateClosed

    Item {
        width: anchorsSectionRoot.width
        height: 48

        DTextInput {
            id: fillTargetEditor
            width: anchorsSectionRoot.editorsWidth
            anchors.horizontalCenter: parent.horizontalCenter
            placeHolderText: "Fill"
            text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsFill : ""

            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    centerInTargetEditor.setEditorFocus(true, true);
                }
            }

            onAccepted: propertiesController.anchorsModel.anchorsFill = newText;
            onTextCleared: propertiesController.anchorsModel.anchorsFill = "";
        }
    }

    Item {
        width: anchorsSectionRoot.width
        height: 210

        DTextInput {
            id: leftTargetEditor
            width: anchorsSectionRoot.editorsWidth
            anchors.left: parent.left
            //anchors.leftMargin: DStyle.defaultMargin
            anchors.verticalCenter: parent.verticalCenter
            placeHolderText: "Left"
            text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsLeft : ""

            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    topTargetEditor.setEditorFocus(true, true);
                }
            }

            onAccepted: propertiesController.anchorsModel.anchorsLeft = newText;
            onTextCleared:propertiesController.anchorsModel.anchorsLeft = "";
        }

        DTextInput {
            id: rightTargetEditor
            width: anchorsSectionRoot.editorsWidth
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            placeHolderText: "Right"
            horizontalAlignment: TextInput.AlignRight
            text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsRight : ""

            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    bottomTargetEditor.setEditorFocus(true, true);
                }
            }

            onAccepted: propertiesController.anchorsModel.anchorsRight = newText;
            onTextCleared: propertiesController.anchorsModel.anchorsRight = "";
        }

        DTextInput {
            id: topTargetEditor
            width: anchorsSectionRoot.editorsWidth
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            placeHolderText: "Top"
            horizontalAlignment: TextInput.AlignHCenter
            text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsTop : ""

            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    rightTargetEditor.setEditorFocus(true, true);
                }
            }

            onAccepted: propertiesController.anchorsModel.anchorsTop = newText;
            onTextCleared: propertiesController.anchorsModel.anchorsTop = "";
        }

        DTextInput {
            id: bottomTargetEditor
            width: anchorsSectionRoot.editorsWidth
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            placeHolderText: "Bottom"
            horizontalAlignment: TextInput.AlignHCenter
            text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsBottom : ""

            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    leftTargetEditor.setEditorFocus(true, true);
                }
            }

            onAccepted: propertiesController.anchorsModel.anchorsBottom = newText;
            onTextCleared: propertiesController.anchorsModel.anchorsBottom = "";
        }

        Column {
            anchors.centerIn: parent
            spacing: DStyle.defaultSpacing

            DTextInput {
                id: horizontalCenterTargetEditor
                width: anchorsSectionRoot.editorsWidth
                anchors.horizontalCenter: parent.horizontalCenter
                placeHolderText: "Horizontal Center"
                horizontalAlignment: TextInput.AlignHCenter
                text: propertiesController.anchorsModel ? propertiesController.anchorsModel.horizontalCenter : ""

                onKeyEvent: {
                    if (event.key === Qt.Key_Tab) {
                        verticalCenterTargetEditor.setEditorFocus(true, true);
                    }
                }

                onAccepted: propertiesController.anchorsModel.horizontalCenter = newText;
                onTextCleared:propertiesController.anchorsModel.horizontalCenter = "";
            }

            DTextInput {
                id: centerInTargetEditor
                width: anchorsSectionRoot.editorsWidth
                anchors.horizontalCenter: parent.horizontalCenter
                placeHolderText: "Center In"
                horizontalAlignment: TextInput.AlignHCenter
                text: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsCenterIn : ""

                onKeyEvent: {
                    if (event.key === Qt.Key_Tab) {
                        fillTargetEditor.setEditorFocus(true, true);
                    }
                }

                onAccepted: propertiesController.anchorsModel.anchorsCenterIn = newText;
                onTextCleared: propertiesController.anchorsModel.anchorsCenterIn = "";
            }

            DTextInput {
                id: verticalCenterTargetEditor
                width: anchorsSectionRoot.editorsWidth
                anchors.horizontalCenter: parent.horizontalCenter
                placeHolderText: "Vertical Center"
                horizontalAlignment: TextInput.AlignHCenter
                text: propertiesController.anchorsModel ? propertiesController.anchorsModel.verticalCenter : ""

                onKeyEvent: {
                    if (event.key === Qt.Key_Tab) {
                        horizontalCenterTargetEditor.setEditorFocus(true, true);
                    }
                }

                onAccepted: propertiesController.anchorsModel.verticalCenter = newText;
                onTextCleared: propertiesController.anchorsModel.verticalCenter = "";
            }
        }
    }

    Item {
        width: anchorsSectionRoot.width
        height: DStyle.defaultMargin
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - leftMarginSpinner.width - DStyle.defaultMargin / 2
            text: "leftMargin: "
        }

        DSpinner {
            id: leftMarginSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsLeftMargin : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsLeftMargin = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsLeftMargin = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsLeftMargin = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsLeftMargin = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    rightMarginSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - rightMarginSpinner.width - DStyle.defaultMargin / 2
            text: "rightMargin: "
        }

        DSpinner {
            id: rightMarginSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsRightMargin : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsRightMargin = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsRightMargin = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsRightMargin = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsRightMargin = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    topMarginSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - topMarginSpinner.width - DStyle.defaultMargin / 2
            text: "topMargin: "
        }

        DSpinner {
            id: topMarginSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsTopMargin : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsTopMargin = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsTopMargin = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsTopMargin = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsTopMargin = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    bottomMarginSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - bottomMarginSpinner.width - DStyle.defaultMargin / 2
            text: "bottomMargin: "
        }

        DSpinner {
            id: bottomMarginSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsBottomMargin : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsBottomMargin = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsBottomMargin = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsBottomMargin = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsBottomMargin = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    horizontalCenterOffsetSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - horizontalCenterOffsetSpinner.width - DStyle.defaultMargin / 2
            text: "horizontal center offs: "
        }

        DSpinner {
            id: horizontalCenterOffsetSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsHorizontalOffset : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsHorizontalOffset = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsHorizontalOffset = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsHorizontalOffset = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsHorizontalOffset = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    verticalCenterOffsetSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }

    Row {
        DText {
            width: anchorsSectionRoot.width - verticalCenterOffsetSpinner.width - DStyle.defaultMargin / 2
            text: "vertical center offs: "
        }

        DSpinner {
            id: verticalCenterOffsetSpinner
            anchors.verticalCenter: parent.verticalCenter
            value: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsVerticalOffset : 0
            onValueIncreased: propertiesController.anchorsModel.anchorsVerticalOffset = newValue;
            onValueDecreased: propertiesController.anchorsModel.anchorsVerticalOffset = newValue;
            onValueEdited: propertiesController.anchorsModel.anchorsVerticalOffset = newValue;
            onValueEntered: propertiesController.anchorsModel.anchorsVerticalOffset = newValue;
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    leftMarginSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }
}
