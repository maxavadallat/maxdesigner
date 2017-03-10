import QtQuick 2.0

import "style"
import "Constants.js" as CONSTS

DControl {
    id: checkBoxRoot

    width: CONSTS.defaultButtonWidth + Style.defaultSpacing
    height: CONSTS.defaultButtonHeight + Style.defaultSpacing

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
        color: checkBoxRoot.focus ? Style.colorBorder : Style.colorFontDark
        MouseArea {
            anchors.fill: parent
            onClicked: checkBoxRoot.focus = true;
        }
    }

    DEditorBackground {
        id: buttonBG
        width: Style.radioButtonRadius * 2
        height: Style.radioButtonRadius * 2

        anchors.left: checkBoxRoot.rightAligned ? parent.left : undefined
        anchors.right: checkBoxRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter
        editorFocus: checkBoxRoot.focus
        radius: Style.defaultRadius

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
        color: Style.colorFontLight
        opacity: checkBoxRoot.checked ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        font.pixelSize: Style.fontSizeS
        font.bold: true
    }
}
