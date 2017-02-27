import QtQuick 2.0

import "Style.js" as STYLE
import "Constants.js" as CONSTS

DButtonBase {
    id: buttonRoot

    property string bgColor: "transparent"
    property string highlightColor: STYLE.colorHighLight
    property string selectedColor: STYLE.colorSelected
    property alias radius: buttonBg.radius
    property alias pixelSize: buttonText.font.pixelSize

    Rectangle {
        id: buttonBg
        anchors.fill: parent
        color: highlight ? buttonRoot.highlightColor : checked ? buttonRoot.selectedColor : buttonRoot.bgColor
        border.color: highlight ? STYLE.colorBorder : STYLE.colorFontDark
        radius: STYLE.defaultRadius
    }

    DText {
        id: buttonText
        anchors.centerIn: parent
        text: buttonRoot.text
    }
}
