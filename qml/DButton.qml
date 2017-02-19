import QtQuick 2.0

import "Style.js" as STYLE
import "Constants.js" as CONSTS

DButtonBase {
    id: buttonRoot

    property string defaultBgColor: "transparent"
    property alias radius: buttonBg.radius
    property alias pixelSize: buttonText.font.pixelSize

    Rectangle {
        id: buttonBg
        anchors.fill: parent
        color: highlight ? STYLE.colorHighLight : checked ? STYLE.colorSelected : buttonRoot.defaultBgColor
        border.color: highlight ? STYLE.colorBorder : STYLE.colorFontDark
        radius: STYLE.defaultRadius
    }

    DText {
        id: buttonText
        anchors.centerIn: parent
        text: buttonRoot.text
    }
}
