import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: propertyItemFormuleRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property string propertyFormula: "Formula"

    signal formulaEditClicked()

    Row {
        id: propertyItemFormulaRow
        anchors.centerIn: parent
        spacing: DStyle.defaultSpacing

        DText {
            id: formulaTitleLabel
            width: propertyItemFormuleRoot.namesColumnWidth
            anchors.verticalCenter: parent.verticalCenter
            text: "formula:"
        }

        DText {
            id: formulaLabel
            width: propertyItemFormuleRoot.width - formulaTitleLabel.width - editFormulaButton.width - DStyle.defaultSpacing * 2 - DStyle.defaultMargin * 2
            anchors.verticalCenter: parent.verticalCenter
            text: propertyItemFormuleRoot.propertyFormula
            elide: Text.ElideRight
        }

        DButton {
            id: editFormulaButton
            width: 64
            anchors.verticalCenter: parent.verticalCenter
            text: "Edit"
            onClicked: propertyItemFormuleRoot.formulaEditClicked();
        }
    }
}
