import QtQuick 2.0

import "Style.js" as STYLE

DButtonBase {
    id: checkBoxRoot

    property bool rightAligned: false

    DText {
        id: buttonText
        anchors.left: checkBoxRoot.rightAligned ? undefined : parent.left
        anchors.right: checkBoxRoot.rightAligned ? parent.right : undefined
        anchors.verticalCenter: parent.verticalCenter
        text: checkBoxRoot.text
        color: checkBoxRoot.highlight ? STYLE.colorBorder : STYLE.colorFontDark
    }

    DEditorBackground {
        id: buttonBG
        width: STYLE.radioButtonRadius * 2
        height: STYLE.radioButtonRadius * 2

        anchors.left: checkBoxRoot.rightAligned ? parent.left : undefined
        anchors.right: checkBoxRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter
        editorFocus: checkBoxRoot.highlight
        radius: STYLE.defaultRadius
    }

    DText {
        id: checkMark
        anchors.centerIn: buttonBG
        //anchors.horizontalCenterOffset: 1
        anchors.verticalCenterOffset: 1
        color: STYLE.colorRadioButton
        opacity: checkBoxRoot.checked ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        font.pixelSize: STYLE.fontSizeS
        font.bold: true
    }
}
