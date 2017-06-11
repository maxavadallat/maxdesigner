import QtQuick 2.0

import "../system/DConstants.js" as CONSTS
import "../style"
import "../controls"

Item {
    id: propertyItemValueRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property string propertyName: "name"
    property string propertyType: "type"
    property string propertyValue: "value"
    property string propertyEnums: ""

    property bool propertyIsFormula: false
    property bool propertyIsBinding: false

    property alias propertyValueMin: propertyValueSpinner.minValue
    property alias propertyValueMax: propertyValueSpinner.maxValue

    property alias editorFocus: propertyValueEditor.editorFocus
    property alias editorEnabled: propertyValueEditor.enabled
    property alias editorMouseSelection: propertyValueEditor.mouseSelection

    property int valueEditorWidth: width - nameLabel.width - DStyle.defaultSpacing

    property real propertyStep: 1

    property bool propertyItemValueInit: false

    property alias valueOptionState: propertyValueOption.state
    property alias valueOptionZ: propertyValueOption.z
    property int valueOptionPopupHeight: (propertyValueOption.count * DStyle.popupItemHeight + DStyle.defaultMargin * 4)
    property int valueOptionOffset: propertyValueOption.optionOffset

    signal accepted()
    signal valueChanged(var newValue)

    Component.onCompleted: {
        //console.log("DPropertyItemValue.onCompleted - propertyName: " + propertyName + " - propertyType: " + propertyType + " - propertyValue: " + propertyValue);

        // Set Up Property Value Options
        setupPropertyValueOptions();
        // Set Property Item Value Init
        propertyItemValueRoot.propertyItemValueInit = true;
    }

    onPropertyValueChanged: {
        // Check If Formula Or binding
        if (propertyItemValueRoot.propertyIsFormula || propertyItemValueRoot.propertyIsBinding) {
            return;
        }

        // Switch Property Type
        switch (propertyType) {
            default:
                // Check Property Value Editor Text
                if (propertyValueEditor.text !== propertyItemValueRoot.propertyValue) {
                    // Set Property Value Editor Text
                    propertyValueEditor.text = propertyItemValueRoot.propertyValue;
                }
            break;

            case CONSTS.propertyTypes[2]:
            case CONSTS.propertyTypes[3]:
            case CONSTS.propertyTypes[4]:
                // Set Spinner Value
                propertyValueSpinner.value = Number(propertyItemValueRoot.propertyValue);
            break;

            case CONSTS.propertyTypes[8]:
                // Check Value
                if (propertyValueOption.getItemText(propertyValueOption.currentIndex) !== propertyItemValueRoot.propertyValue) {
                    // Set Option Value
                    propertyValueOption.setValue(propertyItemValueRoot.propertyValue);
                }
            break;
        }
    }

    onPropertyEnumsChanged: {
        // Check Property Item Value Init
        if (propertyItemValueRoot.propertyItemValueInit) {
            // Set Up Property Value Options
            setupPropertyValueOptions();
        }
    }

    // Set Editor Focus
    function setEditorFocus(aFocus) {
        //console.log("DPropertyItemValue.setEditorFocus - aFocus: " + aFocus);
        // Set Value Editor Focus
        propertyValueEditor.setEditorFocus(aFocus, false);
    }

    // Enable Mouse Selection
    function enableMouseSelection(aEnable) {
        //console.log("DPropertyItemValue.enableMouseSelection - aEnable: " + aEnable);
        // Set Mouse Selection
        propertyValueEditor.mouseSelection = aEnable;
    }

    // Set Up Property Value Options
    function setupPropertyValueOptions() {
        // Clear Items
        propertyValueOption.clearItemModel();

        // Check Property Enums
        if (propertyItemValueRoot.propertyEnums.length > 0) {
            // Get Enum Elements
            var enumElements = propertyItemValueRoot.propertyEnums.split(",");
            // Iterate Through Elements
            for (var i=0; i<enumElements.length; i++) {
                // Append Item
                propertyValueOption.appendItem(enumElements[i]);
            }

            // Set Value
            propertyValueOption.setValue(propertyItemValueRoot.propertyValue);
        }
    }

    Row {
        id: propertyItemValueRow
        //anchors.right: parent.right
        //anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        spacing: DStyle.defaultSpacing

        DText {
            id: nameLabel
            width: propertyItemValueRoot.namesColumnWidth
            //width: propertyItemValueRoot.width - propertyValueEditor.width - DStyle.defaultSpacing - DStyle.defaultMargin * 2
            anchors.verticalCenter: parent.verticalCenter
            text: propertyItemValueRoot.propertyName + ":"
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideMiddle
            wrapMode: Text.NoWrap
        }

        DTextInput {
            id: propertyValueEditor
            width: propertyItemValueRoot.valueEditorWidth
            anchors.verticalCenter: parent.verticalCenter
            text: propertyItemValueRoot.propertyValue
            visible: {
                // Switch Property Type
                switch (propertyItemValueRoot.propertyType) {
                    case CONSTS.propertyTypes[1]:
                    case CONSTS.propertyTypes[2]:
                    case CONSTS.propertyTypes[3]:
                    case CONSTS.propertyTypes[4]:
                    case CONSTS.propertyTypes[8]: return false;
                }

                return true;
            }

            onAccepted: {
                // Check New Value
                if (propertyItemValueRoot.propertyValue !== newText) {
                    // Emit Value Changed Signal
                    propertyItemValueRoot.valueChanged(newText);
                }
            }
        }

        DSpinner {
            id: propertyValueSpinner
            width: propertyItemValueRoot.valueEditorWidth
            visible: {
                // Switch Property Type
                switch (propertyItemValueRoot.propertyType) {
                    case CONSTS.propertyTypes[2]:
                    case CONSTS.propertyTypes[3]:
                    case CONSTS.propertyTypes[4]:   return true;
                }

                return false;
            }

            step: propertyItemValueRoot.propertyStep

            //value: !propertyItemValueRoot.propertyIsFormula ? Number(propertyItemValueRoot.propertyValue) : Number(0);

            onValueIncreased: {
                // Emit Value Changed Signal
                propertyItemValueRoot.valueChanged(newValue);
            }

            onValueDecreased: {
                // Emit Value Changed Signal
                propertyItemValueRoot.valueChanged(newValue);
            }

            onValueEntered: {
                // Check New Value
                if (propertyItemValueRoot.propertyValue !== newValue) {
                    // Emit Value Changed Signal
                    propertyItemValueRoot.valueChanged(newValue);
                }
            }
        }

        Item {
            id: propertyValueSwitchContaniner
            width: propertyItemValueRoot.valueEditorWidth
            height: CONSTS.defaultButtonHeight

            visible: {
                // Check Property Type
                if (propertyItemValueRoot.propertyType === CONSTS.propertyTypes[1]) {
                    return true;
                }

                return false;
            }

            DSwitch {
                id: propertyValueSwitch
                width: DStyle.switchWidth
                anchors.right: parent.right
                text: ""
                checked: propertyItemValueRoot.propertyValue === "true"
                onClicked: {
                    // Emit Value Changed Signal
                    propertyItemValueRoot.valueChanged(!checked);
                }
            }
        }

        Item {
            id: propertyValueOptionContainer
            width: propertyItemValueRoot.valueEditorWidth
            height: CONSTS.defaultButtonHeight

            visible: {
                // Check Property Type
                if (propertyItemValueRoot.propertyType === CONSTS.propertyTypes[8]) {
                    return true;
                }

                return false;
            }

            DOption {
                id: propertyValueOption
                width: parent.width

                onCurrentIndexChanged: {
                    // Get New Option Value
                    var newValue = propertyValueOption.getItemText(propertyValueOption.currentIndex);
                    // Check New Value
                    if (propertyItemValueRoot.propertyValue !== newValue) {
                        //console.log("DPropertyItemValue.propertyValueOption.onCurrentIndexChanged - currentIndex: " + propertyValueOption.currentIndex + " - newValue: " + newValue);
                        // Emit Value Changed Signal
                        propertyItemValueRoot.valueChanged(newValue);
                    }
                }
            }
        }
    }
}
