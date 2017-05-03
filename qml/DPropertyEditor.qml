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
    property string propertyValue: ""

    property bool newProperty: true

    property int propertyIndex: -1

    property var enumValues: []
    property var defaultOptionValues: []

    property Connections enumValueEditorConnections: Connections {
        target: childPane

        onRejected: {
            // Set Type Options Enabled
            typeOption.enabled = true;
//            // Set Option Focus
//            typeOption.setOptionFocus(true);
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
        }

        onAccepted: {
            // Set Type Options Enabled
            typeOption.enabled = true;
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
            // Add Enum Value
            propertyEditorRoot.addEnumValue(childPane.enumValue);
        }
    }

    title: "New Property"

    hideToSide: hideToRight

    creationWidth: 332
    creationHeight: propertyFieldsColumn.height + 48//148

    minWidth: 332
    minHeight: propertyFieldsColumn.height + 48//148

    enableResize: false

    signal newEnumValue()

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
            // Set Clip Content
            propertyEditorRoot.clipContent = false;
        } else if (newState === stateCreate) {
            // Reset Property Editor
            resetPropertyEditor();
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
            // Clear Enum Values
            propertyEditorRoot.clearEnumValues();
            // Reset Default Value
            propertyEditorRoot.propertyDefault = "";
            // Reset Child Pane
            propertyEditorRoot.childPane.resetEnumValueEditor();
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

    // Check If New Enum Value Is Valid
    function enumValueValid(newValue) {
        return (propertyEditorRoot.enumValues.indexOf(newValue) < 0);
    }

    // Add New Enum Value
    function addEnumValue(newValue) {
        // Append New Value
        propertyEditorRoot.enumValues.push(newValue);
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Push New Item To Default Option Values
        propertyEditorRoot.defaultOptionValues.push({ text: newValue, checked: true });

        //console.log("addEnumValue - length: " + propertyEditorRoot.defaultOptionValues.length);
        //console.log("addEnumValue - checked: " + propertyEditorRoot.defaultOptionValues[propertyEditorRoot.defaultOptionValues.length - 1].checked);

        // Set Default Value Options Model
        //defaultOption.model = propertyEditorRoot.defaultOptionValues;

//        // Add New Default Option Item
//        defaultOption.model.push({ 'text': newValue });

        // ...
    }

    // Remove Enum Value
    function removeEnumValue(index) {
        // Remove Value
        propertyEditorRoot.enumValues.splice(index, 1);
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Remove Default Option Value
        propertyEditorRoot.defaultOptionValues.splice(index, 1);

        console.log("removeEnumValue - length: " + propertyEditorRoot.defaultOptionValues.length);

        // Set Default Value Options Model
        //defaultOption.model = propertyEditorRoot.defaultOptionValues;

//        // Remove Default Option Item
//        defaultOption.model.splice(index, 1);

        // ...
    }

    // Clear Enum Values
    function clearEnumValues() {
        // Reset Enum Values
        propertyEditorRoot.enumValues = [];
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Clear Items
        propertyEditorRoot.defaultOptionValues.splice(0, propertyEditorRoot.defaultOptionValues.length);
        //propertyEditorRoot.defaultOptionValues.clear();

        console.log("clearEnumValues - length: " + propertyEditorRoot.defaultOptionValues.length);

        // Set Default Value Options Model
        defaultOption.model = propertyEditorRoot.defaultOptionValues;

//        // Remove First Element
//        defaultOption.model = propertyEditorRoot.defaultOptionValues;

        // ...
    }

    DDisc {
        id: discButton
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
        id: propertyFieldsColumn
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2 + discButton.width + 16
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.verticalCenterOffset: titleLabel.height
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            id: nameRow
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
                        propertyEditorRoot.propertyName = newText;
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
            id: typeRow
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
                    DPopupItemObject { text: CONSTS.propertyTypes[7] },
                    DPopupItemObject { text: CONSTS.propertyTypes[8] },
                    DPopupItemObject { text: CONSTS.propertyTypes[9] }
                ]

                onZChanged: {
                    parent.z = typeOption.z;
                }

                onCurrentIndexChanged: {
                    // Switch Selected Index
                    switch (currentIndex) {
                        default:    defaultEditor.text = "";        break;
                        case 1:     defaultEditor.text = "false";   break;
                        case 2:     defaultEditor.text = "0";       break;
                        case 3:
                        case 4:     defaultEditor.text = "0.0";     break;
                        case 5:
                        case 6:     defaultEditor.text = "null";    break;
                        case 8:     /*defaultOption.currentIndex = 0;*/ break;
                    }
                }

                onItemSelected: {
                    //console.log("DPropertyEditor.typeOption.onItemSelected - currentIndex: " + typeOption.currentIndex);
                    // Set Focus
                    nameEditor.setEditorFocus(true, true);
//                    // Switch Selected Index
//                    switch (itemIndex) {
//                        default:    defaultEditor.text = "";        break;
//                        case 1:     defaultEditor.text = "false";   break;
//                        case 2:     defaultEditor.text = "0";       break;
//                        case 3:
//                        case 4:     defaultEditor.text = "0.0";     break;
//                        case 5:
//                        case 6:     defaultEditor.text = "null";    break;
//                    }
                }

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Reset
                            propertyEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            if (typeOption.currentIndex === 8) {
                                // Set Focus
                                defaultOption.setOptionFocus(true);
                            } else {
                                // Set Focus
                                defaultEditor.setEditorFocus(true, true);
                            }
                        break;
                    }
                }
            }
        }

        Item {
            id: enumValuesContainer
            width: propertyFieldsColumn.width
            height: typeOption.currentIndex === 8 ? enumValuesFlow.height : 0
            Behavior on height { DAnimation { } }
            clip: true

            DFlow {
                id: enumValuesFlow
                width: parent.width
                spacing: DStyle.defaultSpacing

                Repeater {
                    id: enumValuesRepeater

                    model: propertyEditorRoot.enumValues

                    delegate: DTag {
                        tagTitle: propertyEditorRoot.enumValues[index]
                        onRemoveClicked: {
                            //console.log("enumValuesRepeater.delegate.onRemoveClicked - index: " + index);
                            // Remove Enum Value
                            propertyEditorRoot.removeEnumValue(index);
                        }
                    }
                }
            }
        }

        DButton {
            id: addEnumValueButton
            width: enumValuesFlow.width
            height: typeOption.currentIndex === 8 ? CONSTS.defaultButtonHeight : 0
            Behavior on height { DAnimation { } }
            visible: height > 0
            text: "Add Enum Value"
            onClicked: {
                // Set Type Options Enabled
                typeOption.enabled = false;
                // Emit New Enum Value Signal
                propertyEditorRoot.newEnumValue();
            }
        }

        Row {
            id: defaultValueRow
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
                visible: typeOption.currentIndex !== 8

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

                onAccepted: {
                    if (propertyValid(nameEditor.editedText)) {
                        // Set Text
                        defaultEditor.text = newText;
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
                    // ...
                }
            }

            DOption {
                id: defaultOption
                //width: propertyEditorRoot.width - 64
                anchors.verticalCenter: parent.verticalCenter
                visible: typeOption.currentIndex === 8
                //model: []

                onZChanged: {
                    parent.z = typeOption.z;
                }

                onCurrentIndexChanged: {
                    // ...
                }

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
