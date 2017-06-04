import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: propertyEditorRoot

    property ComponentOwnPropertiesModel ownPropertiesModel: propertiesController.ownPropertiesModel

    property string propertyName: ""
    property int propertyType: 0
    property string propertyMin: ""
    property string propertyMax: ""
    property string propertyEnums: ""
    property string propertyDefault: ""
    property bool propertyReadOnly: false
    property bool propertyDefaultAlias: false

    property bool newProperty: true

    property int propertyIndex: -1

    property var enumValues: []

    property int labelsWidth: 78

    property Connections enumValueEditorConnections: Connections {
        target: childPane

        onRejected: {
            // Set Type Options Enabled
            typeOption.enabled = true;
            // Set Button Enabled State
            addEnumValueButton.enabled = true;
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
        }

        onAccepted: {
            // Set Type Options Enabled
            typeOption.enabled = true;
            // Set Button Enabled State
            addEnumValueButton.enabled = true;
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
            // Add Enum Value
            propertyEditorRoot.addEnumValue(childPane.enumValue);
        }
    }

    title: "New Property"

    hideToSide: hideToRight

    creationWidth: 360
    creationHeight: propertyFieldsColumn.height + 48//148

    minWidth: 360
    minHeight: propertyFieldsColumn.height + 48//148

    enableResize: true

    enableHideButton: false

    resizeRightEnabled: false
    resizeTopEnabled: false
    resizeBottomEnabled: false

    signal newEnumValue()

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Property Editor
            //resetPropertyEditor();
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

            // Reset Creation Height
            propertyEditorRoot.creationHeight = Qt.binding(function() { return propertyFieldsColumn.height + 48; });
            // reset Min Height
            propertyEditorRoot.minHeight = Qt.binding(function() { return propertyFieldsColumn.height + 48; });

        } else if (newState === stateCreate) {
            // Reset Property Editor
            resetPropertyEditor();
        }
    }

    // Reset Property Editor
    function resetPropertyEditor() {
        console.log("DPropertyEditor.resetPropertyEditor");
        // Reset Type Option
        typeOption.currentIndex = 0;
        // Reset Property Name
        propertyEditorRoot.propertyName = "";
        // Set Property Type
        propertyEditorRoot.propertyType = typeOption.currentIndex;
        // Set Min Value
        propertyEditorRoot.propertyMin = "";
        // Set Max Value
        propertyEditorRoot.propertyMax = "";
        // Set Enum Values
        propertyEditorRoot.propertyEnums = "";
        // Reset Default Value
        propertyEditorRoot.propertyDefault = "";
        // Reset Read Only
        propertyEditorRoot.propertyReadOnly = false;
        // Reset Default Alias
        propertyEditorRoot.propertyDefaultAlias = false;
        // Clear Enum Values
        propertyEditorRoot.clearEnumValues();
        // Reset Child Pane
        propertyEditorRoot.childPane.resetEnumValueEditor();
        // Reset Default Bool Value Switch
        defaultSwitch.checked = false;
        // Reset Read Only Switch
        readOnlySwitch.checked = false;
        // Reset Default ALias Switch
        defaultAliasSwitch.checked = false;

        // ...
    }

    // Check IF Property Valid
    function propertyValid(newText, newDefaultText) {
        // Check Type Option
        if (typeOption.currentIndex === 9) {
            // Check If Defaullt Value Is Empty
            if (defaultEditor.editedText.length === 0) {
                // Set Default Value Invalid
                defaultEditor.invalidValue = true;

                return false;
            }
        }

        // Check Own Properties Model
        if (propertyEditorRoot.ownPropertiesModel !== null) {
            return propertyEditorRoot.ownPropertiesModel.propertyValid(newText, propertyEditorRoot.newProperty);
        }

        // Set Invalid Value
        nameEditor.invalidValue = true;

        return false;
    }

    // Check If New Enum Value Is Valid
    function enumValueValid(newValue) {
        // Check Length
        if (newValue.length === 0) {
            return false;
        }

        return (propertyEditorRoot.enumValues.indexOf(newValue) < 0);
    }

    // Add New Enum Value
    function addEnumValue(newValue) {
        // Append New Value
        propertyEditorRoot.enumValues.push(newValue);
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Append Default Value Item
        defaultOption.appendItem(newValue, false);
    }

    // Remove Enum Value
    function removeEnumValue(index) {
        // Remove Value
        propertyEditorRoot.enumValues.splice(index, 1);
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Remove Default Value Item
        defaultOption.removeItem(index);
    }

    // Clear Enum Values
    function clearEnumValues() {
        // Reset Enum Values
        propertyEditorRoot.enumValues = [];
        // Emit Enum Values Changed Signal
        propertyEditorRoot.enumValuesChanged();

        // Clear Item Model
        defaultOption.clearItemModel();
    }

    // Update Property Values
    function updatePropertyValues() {
        // Set Property Name
        propertyEditorRoot.propertyName = nameEditor.editedText;
        // Set Property Type
        propertyEditorRoot.propertyType = typeOption.currentIndex;
        // Set Min Value
        propertyEditorRoot.propertyMin = valueMinEditor.editedText;
        // Set Max Value
        propertyEditorRoot.propertyMax = valueMaxEditor.editedText;
        // Set Enum Values
        propertyEditorRoot.propertyEnums = defaultOption.exportItems();

        // Switch Type Option Current Index
        switch (typeOption.currentIndex) {
            default: propertyEditorRoot.propertyDefault = defaultEditor.editedText;                             break;
            case 1: propertyEditorRoot.propertyDefault = defaultSwitch.checked ? "true" : "false";              break;
            case 8: propertyEditorRoot.propertyDefault = defaultOption.getItemText(defaultOption.currentIndex); break;
        }

        // Set Property Read Only
        propertyEditorRoot.propertyReadOnly = readOnlySwitch.checked;
        // Set Property Default Alias
        propertyEditorRoot.propertyDefaultAlias = defaultAliasSwitch.checked;

        // ...
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Property Valid
            if (propertyEditorRoot.propertyValid(nameEditor.editedText, defaultEditor.editedText)) {
                // Update Property Values
                propertyEditorRoot.updatePropertyValues();
                // Set Property Name
                //propertyEditorRoot.propertyName = nameEditor.editedText;
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
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            id: nameRow
            spacing: DStyle.defaultSpacing

            DText {
                id: nameLabel
                width: propertyEditorRoot.labelsWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "Name:"
            }

            DTextInput {
                id: nameEditor
                width: propertyFieldsColumn.width - propertyEditorRoot.labelsWidth - DStyle.defaultSpacing * 2 //typeOption.width
                anchors.verticalCenter: parent.verticalCenter
                text: propertyEditorRoot.propertyName

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
                    if (propertyEditorRoot.propertyValid(newText, defaultEditor.editedText)) {
                        // Update Property Values
                        propertyEditorRoot.updatePropertyValues();
                        // Set Property Name
                        //propertyEditorRoot.propertyName = newText;
                        // Emit Accepted Signal
                        propertyEditorRoot.accepted();
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
                width: propertyEditorRoot.labelsWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "Type:"
            }

            DOption {
                id: typeOption
                width: nameEditor.width
                anchors.verticalCenter: parent.verticalCenter

                model: [
                    { text: CONSTS.propertyTypes[0] },
                    { text: CONSTS.propertyTypes[1] },
                    { text: CONSTS.propertyTypes[2] },
                    { text: CONSTS.propertyTypes[3] },
                    { text: CONSTS.propertyTypes[4] },
                    { text: CONSTS.propertyTypes[5] },
                    { text: CONSTS.propertyTypes[6] },
                    { text: CONSTS.propertyTypes[7] },
                    { text: CONSTS.propertyTypes[8] },
                    { text: CONSTS.propertyTypes[9] }
                ]

                onZChanged: {
                    // Set Parent Z
                    parent.z = typeOption.z;
                }

                onCurrentIndexChanged: {
                    // Switch Selected Index
                    switch (currentIndex) {
                        default:    defaultEditor.text = "";            break;
                        case 1:     defaultEditor.text = "false";       break;
                        case 2:     defaultEditor.text = "0";           break;
                        case 3:
                        case 4:     defaultEditor.text = "0.0";         break;
                        case 5:
                        case 6:     defaultEditor.text = "null";        break;
                        case 8:     /*defaultOption.currentIndex = 0;*/ break;
                        case 9:     defaultAliasSwitch.checked = false; break;
                    }
                }

                onItemSelected: {
                    //console.log("DPropertyEditor.typeOption.onItemSelected - currentIndex: " + typeOption.currentIndex);
                    // Set Focus
                    nameEditor.setEditorFocus(true, true);
                }

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Reset
                            propertyEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            // Switch Type Selector Option Current Index
                            switch (typeOption.currentIndex) {
                                case 2:
                                case 3:
                                case 4:
                                    // Set Focus
                                    valueMinEditor.setEditorFocus(true, true);
                                break;

                                case 8:
                                    // Set Focus
                                    defaultOption.setOptionFocus(true);
                                break;

                                default:
                                    // Set Focus
                                    defaultEditor.setEditorFocus(true, true);
                                break;
                            }
                        break;
                    }
                }
            }
        }

        Item {
            id: valueMinMaxContainer
            width: propertyFieldsColumn.width

            height: {
                // Switch Property Type Ooption Current Index
                switch (typeOption.currentIndex) {
                    case 2:
                    case 3:
                    case 4: return DStyle.textInputHeight;
                }

                return 0;
            }

            Behavior on height { DAnimation { } }
            visible: height > 0
            clip: true

            Row {
                spacing: DStyle.defaultSpacing

                DText {
                    id: valueMinLabel
                    width: propertyEditorRoot.labelsWidth
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "Min:"
                }

                DTextInput {
                    id: valueMinEditor
                    width: (nameEditor.width - valueMaxLabel.width - DStyle.defaultSpacing * 2) * 0.5

                    onAccepted: {

                    }

                    onKeyEvent: {
                        switch (event.key) {
                            case Qt.Key_Escape:
                                // Reset
                                propertyEditorRoot.dismissPane(true);
                            break;

                            case Qt.Key_Tab:
                                valueMaxEditor.setEditorFocus(true, true);
                            break;
                        }
                    }
                }

                DText {
                    id: valueMaxLabel
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "Max:"
                }

                DTextInput {
                    id: valueMaxEditor
                    width: valueMinEditor.width

                    onAccepted: {

                    }

                    onKeyEvent: {
                        switch (event.key) {
                            case Qt.Key_Escape:
                                // Reset
                                propertyEditorRoot.dismissPane(true);
                            break;

                            case Qt.Key_Tab:
                                 defaultEditor.setEditorFocus(true, true);
                            break;
                        }
                    }
                }
            }
        }

        Item {
            id: enumValuesContainer
            width: propertyFieldsColumn.width
            height: typeOption.currentIndex === 8 ? enumValuesFlow.height : 0
            Behavior on height { DAnimation { } }
            visible: height > 0
            clip: true

            DFlow {
                id: enumValuesFlow
                width: nameEditor.width
                anchors.right: parent.right
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
            width: nameEditor.width//enumValuesFlow.width
            height: typeOption.currentIndex === 8 ? CONSTS.defaultButtonHeight : 0
            anchors.right: parent.right
            Behavior on height { DAnimation { } }
            visible: height > 0
            text: "Add Enum Value"
            onClicked: {
                // Check Child Pane
                if (propertyEditorRoot.childPane !== null) {
                    // Set Type Options Enabled
                    typeOption.enabled = false;
                    // Set Button Enabled State
                    addEnumValueButton.enabled = false;
                    // Set New Enum Value
                    propertyEditorRoot.childPane.newEnumValue = true;
                    // Show Enum Value Editor
                    propertyEditorRoot.childPane.show();
                }
            }
        }

        Row {
            id: defaultValueRow
            spacing: DStyle.defaultSpacing

            DText {
                id: defaultLabel
                width: propertyEditorRoot.labelsWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: typeOption.currentIndex === 9 ? "Value:" : "Default:"
            }

            DTextInput {
                id: defaultEditor
                width: nameEditor.width
                anchors.verticalCenter: parent.verticalCenter
                visible: typeOption.currentIndex !== 8 && typeOption.currentIndex !== 1
                text: propertyEditorRoot.propertyDefault

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
                    // Check If Property Valid
                    if (propertyValid(nameEditor.editedText, newText)) {
                        // Update Property Values
                        propertyEditorRoot.updatePropertyValues();
//                        // Set Text
//                        defaultEditor.text = newText;
//                        // Set Property Name
//                        propertyEditorRoot.propertyName = nameEditor.editedText;
                        // Emit Accepted Signal
                        propertyEditorRoot.accepted();
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    defaultEditor.invalidValue = false;
                }
            }

            DOption {
                id: defaultOption
                width: nameEditor.width
                anchors.verticalCenter: parent.verticalCenter
                visible: typeOption.currentIndex === 8

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

            DSwitch {
                id: defaultSwitch
                width: nameEditor.width
                anchors.verticalCenter: parent.verticalCenter
                text: ""
                visible: typeOption.currentIndex === 1
                onClicked: checked = !checked
            }
        }

        Row {
            id: readOnlyRow
            spacing: DStyle.defaultSpacing

            DText {
                width: propertyEditorRoot.labelsWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "ReadOnly:"
            }

            DSwitch {
                id: readOnlySwitch
                width: nameEditor.width
                text: ""
                onClicked: {
                    checked = !checked;
                }
            }
        }

        Row {
            id: defaultAliasRow
            height: typeOption.currentIndex === 9 ? defaultAliasSwitch.height : 0
            Behavior on height { DAnimation { } }
            visible: height > 0
            clip: true
            spacing: DStyle.defaultSpacing

            DText {
                width: propertyEditorRoot.labelsWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "default"
            }

            DSwitch {
                id: defaultAliasSwitch
                width: nameEditor.width
                text: "alias"
                onClicked: {
                    checked = !checked;
                }
            }
        }
    }
}
