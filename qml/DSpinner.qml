import QtQuick 2.7

import "style"

DControl {
    id: spinnerRoot

    width: DStyle.spinnerWidth
    height: DStyle.spinnerHeight

    property double value: 0.0

    property double step: 1.0

    property double minValue: -Number.MAX_VALUE
    property double maxValue: Number.MAX_VALUE

    signal valueIncreased(var newValue)
    signal valueDecreased(var newValue)
    signal valueEntered(var newValue)
    signal valueEdited(var newValue)
    signal keyEvent(var event)

    Component.onCompleted: {
        // Set Text
        textInput.text = String(spinnerRoot.value);
    }

    onValueChanged: {
        if (Number(textInput.text) !== spinnerRoot.value) {
            // Set Text
            textInput.text = String(spinnerRoot.value);
        }
    }

    // Increase Value
    function incValue() {
        // Calculate New Value
        var newValue = Math.min(spinnerRoot.value + spinnerRoot.step, spinnerRoot.maxValue);
        // Check New Value
        if (newValue !== value) {
            valueIncreased(newValue);
        }
    }

    // Decrease Value
    function decValue() {
        // Calculate New Value
        var newValue = Math.max(spinnerRoot.value - spinnerRoot.step, spinnerRoot.minValue);
        // Check New Value
        if (newValue !== value) {
            valueDecreased(newValue);
        }
    }

    // Set Spinner Focus
    function setSpinnerFocus(aFocus, aSelect) {
        textInput.setEditorFocus(aFocus, aSelect);
    }

    DTextInput {
        id: textInput

        width: parent.width
        height: DStyle.spinnerHeight

        editor.inputMethodHints: Qt.ImhDigitsOnly
        editor.horizontalAlignment: TextInput.AlignHCenter
        editor.validator: DoubleValidator {
            bottom: spinnerRoot.minValue
            top: spinnerRoot.maxValue
        }

        pixelSize: DStyle.fontSizeM
        showClearButton: false

        onAccepted: {
            // Calculate New Value
            var newValue = Math.min(spinnerRoot.maxValue, Math.max(spinnerRoot.minValue, Number(newText)));
            // Check New Value
            if (newValue !== value) {
                // Emit Value Entered Signal
                valueEntered(newValue);
            }
        }

        onTextEdited: {
            if (newText === "-") {
                return;
            }

            // Calculate New Value
            var newValue = Math.min(spinnerRoot.maxValue, Math.max(spinnerRoot.minValue, Number(newText)));

            // Check New Value
            if (newValue !== value) {
                // Emit Value Edited Signal
                valueEdited(newValue);
            }
        }

        onKeyEvent: {
            //console.log("DSpinner.textInput.onKeyEvent - event.key: " + event.key);
            // Switch Key
            switch (event.key) {
                case Qt.Key_Down:
                    // Dec Value
                    spinnerRoot.decValue();
                break;

                case Qt.Key_Up:
                    // Inc Value
                    spinnerRoot.incValue();
                break;

                case Qt.Key_Backspace:
                    if (textInput.text === "NaN") {
                        textInput.text = "";
                    }
                break;

                case Qt.Key_Escape:
                    textInput.text = String(spinnerRoot.value);
                break;

                default: spinnerRoot.keyEvent(event);
            }
        }

        Column {
            id: buttonsColumn
            width: DStyle.spinnerButtonWidth

            anchors.right: parent.right
            //anchors.rightMargin: DStyle.defaultMargin
            anchors.verticalCenter: parent.verticalCenter

            DMouseArea {
                width: DStyle.spinnerButtonWidth
                height: DStyle.spinnerButtonHeight
                anchors.right: parent.right

                onClicked: {
                    // Set Focus To Text Input
                    textInput.setEditorFocus(true);
                    // Inc Value
                    spinnerRoot.incValue();
                }

                onPressAndHold: {
                    // Set Focus To Text Input
                    textInput.setEditorFocus(true);
                    // Start Repeat Timer
                    incTimer.running = true;
                }

                onReleased: {
                    // Stop Repeat Timer
                    incTimer.running = false;
                }

                DText {
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: 2
                    text: "+"
                    color: parent.pressed ? DStyle.colorBorder : DStyle.colorFontDark
                }

                Timer {
                    id: incTimer
                    repeat: true
                    interval: DStyle.spinnerButtonTimer
                    onTriggered: {
                        spinnerRoot.incValue();
                    }
                }
            }

            DMouseArea {
                width: DStyle.spinnerButtonWidth
                height: DStyle.spinnerButtonHeight
                anchors.right: parent.right

                onClicked: {
                    // Set Focus To Text Input
                    textInput.setEditorFocus(true);
                    // Dec Value
                    spinnerRoot.decValue();
                }

                onPressAndHold: {
                    // Set Focus To Text Input
                    textInput.setEditorFocus(true);
                    // Start Repeat Timer
                    decTimer.running = true;
                }

                onReleased: {
                    // Stop Repeat Timer
                    decTimer.running = false;
                }

                DText {
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: -3
                    text: "-"
                    color: parent.pressed ? DStyle.colorBorder : DStyle.colorFontDark
                }

                Timer {
                    id: decTimer
                    repeat: true
                    interval: DStyle.spinnerButtonTimer
                    onTriggered: {
                        spinnerRoot.decValue();
                    }
                }
            }
        }
    }
}

