import QtQuick 2.0

import "style"

DButtonBase {
    id: checkBoxRoot

    property bool rightAligned: false

    DText {
        id: buttonText
        anchors.left: checkBoxRoot.rightAligned ? undefined : parent.left
        anchors.right: checkBoxRoot.rightAligned ? parent.right : undefined
        anchors.verticalCenter: parent.verticalCenter
        text: checkBoxRoot.text
        color: checkBoxRoot.highlight ? Style.colorBorder : Style.colorFontDark
    }

    DEditorBackground {
        id: buttonBG
        width: Style.radioButtonRadius * 2
        height: Style.radioButtonRadius * 2

        anchors.left: checkBoxRoot.rightAligned ? parent.left : undefined
        anchors.right: checkBoxRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter
        editorFocus: checkBoxRoot.highlight
        radius: Style.defaultRadius
    }

    DText {
        id: checkMark
        anchors.centerIn: buttonBG
        //anchors.horizontalCenterOffset: 1
        anchors.verticalCenterOffset: 1
        color: Style.colorRadioButton
        opacity: checkBoxRoot.checked ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        font.pixelSize: Style.fontSizeS
        font.bold: true
    }
}
