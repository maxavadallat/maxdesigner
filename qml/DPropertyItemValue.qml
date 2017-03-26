import QtQuick 2.7

import "DConstants.js" as CONSTS
import "style"

Item {
    id: propertyItemValueRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int nameLabelWidth: 96

    property string propertyName: "name"
    property string propertyType: "type"
    property string propertyValue: "value"

    property alias editorFocus: propertyValueEditor.editorFocus
    property alias editorEnabled: propertyValueEditor.enabled
    property alias editorMouseSelection: propertyValueEditor.mouseSelection

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
        console.log("DPropertyItemValue.setEditorFocus - aFocus: " + aFocus);
        // Set Value Editor Focus
        propertyValueEditor.setEditorFocus(false, false);
    }

    // Enable Mouse Selection
    function enableMouseSelection(aEnable) {
        console.log("DPropertyItemValue.enableMouseSelection - aEnable: " + aEnable);
        // Set Mouse Selection
        propertyValueEditor.mouseSelection = aEnable;
    }


    Rectangle {
        anchors.fill: parent
        color: "transparent"
        //color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
        border.color: "purple"
    }

    Row {
        id: propertyItemValueRow
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        spacing: DStyle.defaultSpacing

        DText {
            id: nameLabel
            width: propertyItemValueRoot.nameLabelWidth
            //width: propertyItemValueRoot.width - propertyValueEditor.width - DStyle.defaultSpacing - DStyle.defaultMargin * 2
            anchors.verticalCenter: parent.verticalCenter
            text: propertyItemValueRoot.propertyName + ":"
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideMiddle
            wrapMode: Text.NoWrap
        }

        DTextInput {
            id: propertyValueEditor
            width: propertyItemValueRoot.width - nameLabel.width - DStyle.defaultSpacing - DStyle.defaultMargin * 2
            anchors.verticalCenter: parent.verticalCenter
            text: propertyItemValueRoot.propertyValue
            onAccepted: {
                propertyItemValueRoot.accepted();
            }
        }
    }
}
