import QtQuick 2.0

import "style"
import "DConstants.js" as CONSTS

DControl {
    id: checkBoxRoot

    width: CONSTS.defaultButtonWidth + DStyle.defaultSpacing
    height: CONSTS.defaultButtonHeight + DStyle.defaultSpacing

    property bool rightAligned: false

    property alias text: buttonText.text
    property alias checked: checkBox.checked

    signal pressed()
    signal released()
    signal clicked()

    DText {
        id: buttonText
        anchors.left: checkBoxRoot.rightAligned ? undefined : parent.left
        anchors.right: checkBoxRoot.rightAligned ? parent.right : undefined
        anchors.verticalCenter: parent.verticalCenter
        text: "CheckBox"
        color: checkBoxRoot.focus ? DStyle.colorBorder : DStyle.colorFontDark
        MouseArea {
            anchors.fill: parent
            onClicked: checkBoxRoot.focus = true;
        }
    }

    DEditorBackground {
        id: buttonBG
        width: DStyle.radioButtonRadius * 2
        height: DStyle.radioButtonRadius * 2

        anchors.left: checkBoxRoot.rightAligned ? parent.left : undefined
        anchors.right: checkBoxRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter
        editorFocus: checkBoxRoot.focus
        radius: DStyle.defaultRadius

        DButtonBase {
            id: checkBox
            anchors.fill: parent

            onPressed: checkBoxRoot.pressed();
            onReleased: checkBoxRoot.released();
            onClicked: {
                checkBoxRoot.focus = true;
                checkBoxRoot.clicked();
            }
        }
    }

    DText {
        id: checkMark
        anchors.centerIn: buttonBG
        //anchors.horizontalCenterOffset: 1
        anchors.verticalCenterOffset: 1
        color: DStyle.colorFontLight
        opacity: checkBoxRoot.checked ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        font.pixelSize: DStyle.fontSizeS
        font.bold: true
    }
}
