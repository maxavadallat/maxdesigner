import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: propertyItemFormuleRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int namesColumnWidth: 200

    property string propertyName: "name"
    property string propertyFormula: "Formula"

    signal formulaEditClicked()

    Row {
        id: propertyItemFormulaRow
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        spacing: DStyle.defaultSpacing

        DText {
            id: formulaTitleLabel
            width: propertyItemFormuleRoot.namesColumnWidth
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: propertyItemFormuleRoot.propertyName + ":"
        }

        DText {
            id: formulaLabel
            width: propertyItemFormuleRoot.width - formulaTitleLabel.width - editFormulaButton.width - DStyle.defaultSpacing * 2
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            text: "{...}"//propertyItemFormuleRoot.propertyFormula
            wrapMode: Text.NoWrap
            maximumLineCount: 1
            elide: Text.ElideMiddle
        }

        DButton {
            id: editFormulaButton
            width: 48
            anchors.verticalCenter: parent.verticalCenter
            text: "Edit"
            onClicked: propertyItemFormuleRoot.formulaEditClicked();
        }
    }
}
