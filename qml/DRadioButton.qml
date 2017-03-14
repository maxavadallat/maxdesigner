import QtQuick 2.0

import "style"

DButtonBase {
    id: radioButtonRoot

    property int buttonIndex: -1

    property bool rightAligned: false

    signal buttonClicked(var index)

    onClicked: {
        //console.log("DRadioButton.onClicked - buttonIndex: " + radioButtonRoot.buttonIndex);
        radioButtonRoot.buttonClicked(radioButtonRoot.buttonIndex);
    }

    DText {
        id: buttonText
        anchors.left: radioButtonRoot.rightAligned ? undefined : parent.left
        anchors.right: radioButtonRoot.rightAligned ? parent.right : undefined
        anchors.verticalCenter: parent.verticalCenter
        text: radioButtonRoot.text
        color: radioButtonRoot.highlight ? DStyle.colorBorder : DStyle.colorFontDark
    }

    DEditorBackground {
        id: buttonBG
        width: DStyle.radioButtonRadius * 2
        height: DStyle.radioButtonRadius * 2

        anchors.left: radioButtonRoot.rightAligned ? parent.left : undefined
        anchors.right: radioButtonRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter

        //bgColor: radioButtonRoot.pressed ? DStyle.colorHighLight : DStyle.colorEditorBG
        //bgColor: "red"
        //highLight: radioButtonRoot.highlight
        editorFocus: radioButtonRoot.highlight

        radius: DStyle.radioButtonRadius
    }

    Rectangle {
        id: buttonRect
        width: radius * 2
        height: radius * 2
        anchors.centerIn: buttonBG
        color: DStyle.colorRadioButton
        radius: DStyle.defaultRadius + 1
        opacity: radioButtonRoot.checked ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        smooth: true
        antialiasing: true
    }
}
