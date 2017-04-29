import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: propertyEditorRoot

    property ComponentOwnPropertiesModel ownPropertiesModel: propertiesController.ownPropertiesModel

    property alias propertyName: nameEditor.text
    property alias propertyType: typeOption.currentIndex
    property alias propertyDefault: defaultEditor.text

    property bool newProperty: false

    property int propertyIndex: -1

    title: "New Property"

    hideToSide: hideToRight

    creationWidth: 332
    creationHeight: 148

    minWidth: 332
    minHeight: 148

    enableResize: false

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Property Editor
            resetPropertyEditor();
        }

        // Check New State
        if (newState === stateHidden) {
            // Set Focus
            nameEditor.setEditorFocus(false);
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Focus
            nameEditor.setEditorFocus(true, true);
            propertyEditorRoot.clipContent = false;
        }
    }

    // Reset Property Editor
    function resetPropertyEditor() {
        // Check New Property
        if (propertyEditorRoot.newProperty) {
            // Reset Property Name
            propertyEditorRoot.propertyName = "";
            // Reset Property Type
            propertyEditorRoot.propertyType = 0;
            // Reset Default Value
            propertyEditorRoot.propertyDefault = "";
        } else {

        }
    }

    // Check IF Property Valid
    function propertyValid(newText) {
        // Check Own Properties Model
        if (propertyEditorRoot.ownPropertiesModel !== null) {
            return propertyEditorRoot.ownPropertiesModel.propertyValid(newText, propertyEditorRoot.newProperty);
        }

        return false;
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Property Valid
            if (propertyEditorRoot.propertyValid(nameEditor.editedText)) {
                // Set Property Name
                propertyEditorRoot.propertyName = nameEditor.editedText;
                // Emit Accepted Signal
                propertyEditorRoot.accepted();
            } else {
                // Set Invalid Value
                // Set Invalid Value
                nameEditor.invalidValue = true;
            }
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

                onAccepted: {
                    // Check If Property Valid
                    if (propertyEditorRoot.propertyValid(newText)) {
                        // Set Property Name
                        propertyEditorRoot.propertyName = nameEditor.editedText;
                        // Emit Accepted Signal
                        propertyEditorRoot.accepted();
                    } else {
                        // Set Invalid Value
                        nameEditor.invalidValue = true;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    nameEditor.invalidValue = false;
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
                    DPopupItemObject { text: CONSTS.propertyTypes[6] },
                    DPopupItemObject { text: CONSTS.propertyTypes[7] }
                ]

                onZChanged: {
                    parent.z = typeOption.z;
                }

                onItemSelected: {
                    //console.log("DPropertyEditor.typeOption.onItemSelected - currentIndex: " + typeOption.currentIndex);
                    // Set Focus
                    nameEditor.setEditorFocus(true, true);
                    // Switch Selected Index
                    switch (itemIndex) {
                        default:    defaultEditor.text = "";        break;
                        case 1:     defaultEditor.text = "false";   break;
                        case 2:     defaultEditor.text = "0";       break;
                        case 3:
                        case 4:     defaultEditor.text = "0.0";     break;
                        case 5:
                        case 6:     defaultEditor.text = "null";    break;
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

                onTextEdited: {

                }
            }
        }
    }
}
