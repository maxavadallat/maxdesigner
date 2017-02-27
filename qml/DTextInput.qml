import QtQuick 2.0
import QtGraphicalEffects 1.0

import "Style.js" as STYLE

DControl {
    id: textInputRoot

    width: STYLE.textInputWidth
    height: STYLE.textInputHeight

    property alias editor: textInput
    property alias text: textInput.text
    property alias pixelSize: textInput.font.pixelSize

    property bool showClearButton: true

    property bool fixTextSize: false

    property alias wrapMode: textInput.wrapMode

    clip: true

    signal keyEvent(var event)

    // Set Editor Focus
    function setEditorFocus(aFocus) {
        textInput.focus = aFocus;
    }

    DEditorBackground {
        anchors.fill: parent
        editorFocus: editor.focus
    }

    TextInput {
        id: textInput

        width: {
            if (text.length === 0 || !textInputRoot.showClearButton) {
                return parent.width - STYLE.defaultMargin * 2;
            }

            return parent.width - STYLE.defaultMargin * 2.5 - clearButton.width;
        }

        height: parent.height - STYLE.defaultMargin

        Behavior on width { DAnimation { } }

        anchors.left: parent.left
        anchors.leftMargin: STYLE.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        //anchors.verticalCenterOffset: 1

        verticalAlignment: Text.AlignVCenter

        font.pixelSize: fixTextSize ? STYLE.fontSizeL : textInput.height - 6

        selectByMouse: true

        color: STYLE.colorFontLight

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: "purple"
//        }

        Keys.onPressed: {
            // Check if Auto Repeat
            if (event.isAutoRepeat) {
                // Emit Key Event Signal
                textInputRoot.keyEvent(event);
            }
        }

        Keys.onReleased: {
            // Check Key
            if (event.key === Qt.Key_Escape) {
                // Reset Focus
                textInput.focus = false;
            }

            // Emit Key Event Signal
            textInputRoot.keyEvent(event);
        }
    }

    DButton {
        id: clearButton
        width: STYLE.textInputHeight * 0.6
        height: width
        anchors.right: parent.right
        anchors.rightMargin: STYLE.defaultMargin * 0.7
        anchors.verticalCenter: parent.verticalCenter

        opacity: (textInput.text.length > 0 && textInputRoot.showClearButton) ? 1.0 : 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
        text: "X"
        radius: height * 0.5 - 1
        pixelSize: STYLE.fontSizeS

        onClicked: {
            // Clear Text
            textInput.text = "";
        }
    }
}

