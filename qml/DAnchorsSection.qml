import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

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

            onAccepted: {
                // Clear Other Anchors
                propertiesController.anchorsModel.anchorsCenterIn = "";
                propertiesController.anchorsModel.horizontalCenter = "";
                propertiesController.anchorsModel.verticalCenter = "";
                propertiesController.anchorsModel.anchorsLeft = "";
                propertiesController.anchorsModel.anchorsRight = "";
                propertiesController.anchorsModel.anchorsTop = "";
                propertiesController.anchorsModel.anchorsBottom = "";

                // Set Fill Target
                propertiesController.anchorsModel.anchorsFill = newText;
            }
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

            onAccepted: {
                // Clear Other Anchors
                propertiesController.anchorsModel.anchorsFill = "";
                propertiesController.anchorsModel.anchorsCenterIn = "";
                propertiesController.anchorsModel.horizontalCenter = "";

                // Set Left Target
                propertiesController.anchorsModel.anchorsLeft = newText;
            }
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

            onAccepted: {
                // Clear Other Anchors
                propertiesController.anchorsModel.anchorsFill = "";
                propertiesController.anchorsModel.anchorsCenterIn = "";
                propertiesController.anchorsModel.horizontalCenter = "";

                // Set Right Target
                propertiesController.anchorsModel.anchorsRight = newText;
            }
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

            onAccepted: {
                // Clear Other Anchors
                propertiesController.anchorsModel.anchorsFill = "";
                propertiesController.anchorsModel.anchorsCenterIn = "";
                propertiesController.anchorsModel.verticalCenter = "";

                // Set Top Target
                propertiesController.anchorsModel.anchorsTop = newText;
            }
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

            onAccepted: {
                // Clear Other Anchors
                propertiesController.anchorsModel.anchorsFill = "";
                propertiesController.anchorsModel.anchorsCenterIn = "";
                propertiesController.anchorsModel.verticalCenter = "";

                // Set Bottom Target
                propertiesController.anchorsModel.anchorsBottom = newText;
            }
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

                onAccepted: {
                    // Clear Other Anchors
                    propertiesController.anchorsModel.anchorsFill = "";
                    propertiesController.anchorsModel.anchorsCenterIn = "";
                    propertiesController.anchorsModel.anchorsLeft = "";
                    propertiesController.anchorsModel.anchorsRight = "";

                    // Set Horizontal Center Target
                    propertiesController.anchorsModel.horizontalCenter = newText;
                }
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

                onAccepted: {
                    // Clear Other Anchors
                    propertiesController.anchorsModel.anchorsFill = "";
                    propertiesController.anchorsModel.anchorsLeft = "";
                    propertiesController.anchorsModel.anchorsRight = "";
                    propertiesController.anchorsModel.anchorsTop = "";
                    propertiesController.anchorsModel.anchorsBottom = "";

                    // Set Center In Target
                    propertiesController.anchorsModel.anchorsCenterIn = newText;
                }
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

                onAccepted: {
                    // Clear Other Anchors
                    propertiesController.anchorsModel.anchorsFill = "";
                    propertiesController.anchorsModel.anchorsCenterIn = "";
                    propertiesController.anchorsModel.anchorsTop = "";
                    propertiesController.anchorsModel.anchorsBottom = "";

                    // Set Vertical Center Target
                    propertiesController.anchorsModel.verticalCenter = newText;
                }
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
            onKeyEvent: {
                if (event.key === Qt.Key_Tab) {
                    leftMarginSpinner.setSpinnerFocus(true, true);
                }
            }
        }
    }
}
