import QtQuick 2.0

import "../system/DConstants.js" as CONSTS
import "../style"

DButtonBase {
    id: buttonRoot

    property string bgColor: "transparent"
    property string highlightColor: DStyle.colorHighLight
    property string selectedColor: DStyle.colorSelected
    property alias radius: buttonBg.radius
    property alias pixelSize: buttonText.font.pixelSize
    property alias border: buttonBg.border

    Rectangle {
        id: buttonBg
        anchors.fill: parent
        color: highlight ? buttonRoot.highlightColor : checked ? buttonRoot.selectedColor : buttonRoot.bgColor
        border.color: highlight ? DStyle.colorBorder : DStyle.colorFontDark
        radius: DStyle.defaultRadius
    }

    DText {
        id: buttonText
        anchors.centerIn: parent
        text: buttonRoot.text
    }
}
