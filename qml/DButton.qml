import QtQuick 2.0

import "style"
import "Constants.js" as CONSTS

DButtonBase {
    id: buttonRoot

    property string bgColor: "transparent"
    property string highlightColor: Style.colorHighLight
    property string selectedColor: Style.colorSelected
    property alias radius: buttonBg.radius
    property alias pixelSize: buttonText.font.pixelSize

    Rectangle {
        id: buttonBg
        anchors.fill: parent
        color: highlight ? buttonRoot.highlightColor : checked ? buttonRoot.selectedColor : buttonRoot.bgColor
        border.color: highlight ? Style.colorBorder : Style.colorFontDark
        radius: Style.defaultRadius
    }

    DText {
        id: buttonText
        anchors.centerIn: parent
        text: buttonRoot.text
    }
}
