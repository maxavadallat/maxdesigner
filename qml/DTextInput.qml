import QtQuick 2.0
import QtGraphicalEffects 1.0

import "Style.js" as STYLE

DControl {
    id: textInputRoot

    width: 240
    height: STYLE.textInputHeight

    property alias editor: textInput
    property alias text: textInput.text

    DEditorBackground {
        anchors.fill: parent
        editorFocus: editor.focus
    }

    TextInput {
        id: textInput

        width: parent.width - STYLE.defaultMargin - 2
        height: parent.height - STYLE.defaultMargin - 2

        anchors.centerIn: parent
        anchors.verticalCenterOffset: 1

        font.pixelSize: textInput.height - 6

        selectByMouse: true

        color: STYLE.colorFontLight


//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: "purple"
//        }
    }
}

