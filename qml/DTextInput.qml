import QtQuick 2.0
import QtGraphicalEffects 1.0

import "style"

DControl {
    id: textInputRoot

    width: DStyle.textInputWidth
    height: DStyle.textInputHeight

    property alias editor: textInput
    property alias text: textInput.text
    property alias editorFocus: textInput.focus
    property alias pixelSize: textInput.font.pixelSize
    property alias wrapMode: textInput.wrapMode
    property alias mouseSelection: textInput.selectByMouse

    property bool showClearButton: true
    property bool fixTextSize: false

    clip: true

    signal keyEvent(var event)
    signal accepted()

    // Set Editor Focus
    function setEditorFocus(aFocus, aSelect) {
        //console.log("DTextInput.setEditorFocus - aFocus: " + aFocus + " - aSelect: " + aSelect);
        //textInput.activeFocus = aFocus;
        textInput.focus = aFocus;
        //textInput.forceActiveFocus();
        if (aSelect) {
            selectAll();
        }
    }

    function enableMouseSelection(aEnable) {
        textInput.selectByMouse = aEnable;
    }

    function selectAll() {
        textInput.selectAll();
    }

    DEditorBackground {
        anchors.fill: parent
        editorFocus: textInput.activeFocus
    }

    TextInput {
        id: textInput

        width: {
            if (text.length === 0 || !textInputRoot.showClearButton) {
                return parent.width - DStyle.defaultMargin * 2;
            }

            return parent.width - DStyle.defaultMargin * 2.5 - clearButton.width;
        }

        height: parent.height - DStyle.defaultMargin

        Behavior on width { DAnimation { } }

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        //anchors.verticalCenterOffset: 1

        verticalAlignment: Text.AlignVCenter

        font.pixelSize: fixTextSize ? DStyle.fontSizeL : textInput.height - 6

        selectByMouse: true

        color: DStyle.colorFontLight

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: "purple"
//        }

        onAccepted: {
            // Emit Accepted Signal
            textInputRoot.accepted();
        }

        Keys.onPressed: {
            // Check if Auto Repeat
            if (event.isAutoRepeat) {
                // Emit Key Event Signal
                textInputRoot.keyEvent(event);
            }
        }

        Keys.onReleased: {
            // Switch Key
            switch (event.key) {
                case Qt.Key_Escape:
                    // Reset Focus
                    textInput.focus = false;
                break;

                default:
                break;
            }

            // Emit Key Event Signal
            textInputRoot.keyEvent(event);
        }
    }

    DButton {
        id: clearButton
        width: DStyle.textInputHeight * 0.6
        height: width
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 0.7
        anchors.verticalCenter: parent.verticalCenter

        opacity: (textInput.text.length > 0 && textInput.activeFocus && textInputRoot.showClearButton) ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        radius: height * 0.5 - 1
        pixelSize: DStyle.fontSizeS

        onClicked: {
            // Clear Text
            textInput.text = "";
        }
    }
}

