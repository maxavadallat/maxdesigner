import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: propertyItemValueRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property string propertyName: "name"
    property string propertyType: "type"
    property string propertyValue: "value"

    property alias propertyValueMin: propertyValueSpinner.minValue
    property alias propertyValueMax: propertyValueSpinner.maxValue

    property alias editorFocus: propertyValueEditor.editorFocus
    property alias editorEnabled: propertyValueEditor.enabled
    property alias editorMouseSelection: propertyValueEditor.mouseSelection

    property int valueEditorWidth: width - nameLabel.width - DStyle.defaultSpacing

    signal accepted()

    onPropertyValueChanged: {
        // Check Property Value Editor Text
        if (propertyValueEditor.text !== propertyItemValueRoot.propertyValue) {
            // Set Property Value Editor Text
            propertyValueEditor.text = propertyItemValueRoot.propertyValue;
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
                    case CONSTS.propertyTypes[4]:   return false;
                }

                return true;
            }

            onAccepted: {
                propertyItemValueRoot.accepted();
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
        }

        Item {
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
            }
        }
    }
}
