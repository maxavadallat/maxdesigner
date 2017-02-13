import QtQuick 2.0

import "Style.js" as STYLE
import "Constants.js" as CONSTS

DButtonBase {
    id: buttonRoot

    Rectangle {
        anchors.fill: parent
        color: highlight ? STYLE.colorHighLight : checked ? STYLE.colorSelected : "transparent"
        border.color: highlight ? STYLE.colorBorder : STYLE.colorFontDark
        radius: STYLE.defaultRadius
    }

    DText {
        anchors.centerIn: parent
        text: buttonRoot.text
    }
}
