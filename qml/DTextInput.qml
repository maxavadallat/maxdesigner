import QtQuick 2.0
import QtGraphicalEffects 1.0

import "style"

DMouseArea {
    id: textInputRoot

    width: DStyle.textInputWidth
    height: DStyle.textInputHeight

    property alias editor: textInput
    property string text: ""
    property alias editorFocus: textInput.focus
    property alias pixelSize: textInput.font.pixelSize
    property alias wrapMode: textInput.wrapMode
    property alias mouseSelection: textInput.selectByMouse
    property alias horizontalAlignment: textInput.horizontalAlignment
    property alias editedText: textInput.text
    property string placeHolderText: ""

    property bool showClearButton: true
    property bool fixTextSize: false

    property bool invalidValue: false

    property bool userInput: false

    clip: true

    signal keyEvent(var event)
    signal accepted(var newText)
    signal textEdited(var newText)
    signal textCleared();

    onClicked: {
        // Set Focus
        textInput.focus = true;
    }

    onTextChanged: {
        //console.log("DTextInput.onTextChanged - text: " + textInputRoot.text)
        // Reset User Input
        textInputRoot.userInput = false;
        // Set Text Input Text
        textInput.text = textInputRoot.text;
    }

    // Set Editor Focus
    function setEditorFocus(aFocus, aSelect) {
        //console.log("DTextInput.setEditorFocus - aFocus: " + aFocus + " - aSelect: " + aSelect);
        //textInput.activeFocus = aFocus;
        // Set Focus
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
        invalidValue: textInputRoot.invalidValue
    }

    TextInput {
        id: textInput

        width: {
            if (text.length === 0 || !textInputRoot.showClearButton || !textInput.focus) {
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
        font.family: DStyle.instrument101FontName

        selectByMouse: true

        color: focus ? DStyle.colorFontLight : DStyle.colorFontDark

        clip: true

        onTextChanged: {
            //console.log("DTextInput.textInput.onTextChanged - text: " + textInput.text + " - userInput: " + textInputRoot.userInput);
            // Check User Input
            if (!textInputRoot.userInput) {
                // Set User Input
                textInputRoot.userInput = true;
            } else {
                // Emit Text Edited Signal
                textInputRoot.textEdited(textInput.text);
            }
        }

        onAccepted: {
            // Emit Accepted Signal
            textInputRoot.accepted(textInput.text);
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
                    // Reset Text
                    textInput.text = textInputRoot.text;
                break;

                default:
                break;
            }

            // Emit Key Event Signal
            textInputRoot.keyEvent(event);
        }

        DText {
            id: placeHolderTextLabel
            anchors.fill: parent
            horizontalAlignment: textInput.horizontalAlignment
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: textInput.font.pixelSize
            wrapMode: Text.NoWrap
            elide: Text.ElideRight
            opacity: textInput.text.length === 0 ? 0.5 : 0.0
            Behavior on opacity { DFadeAnimation { } }
            visible: opacity > 0.0
            text: textInputRoot.placeHolderText
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
            // Set User Input
            textInputRoot.userInput = true;
            // Clear Text
            textInput.text = "";
            // Emit Accepted Signal
            textInputRoot.textEdited(textInput.text);
            // Emit Text Cleared Signal
            textInputRoot.textCleared();
        }
    }
}

