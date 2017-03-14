import QtQuick 2.7

import "style"

DControl {
    id: spinnerRoot

    width: DStyle.spinnerWidth
    height: DStyle.spinnerHeight

    property double value: 0.0

    property double step: 1.0

    property double minValue: -100.0
    property double maxValue: 100.0

    signal valueIncreased(var newValue)
    signal valueDecreased(var newValue)
    signal textUpdated(var newValue)

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

    function incValue() {
        var newValue = Math.min(spinnerRoot.value + spinnerRoot.step, spinnerRoot.maxValue);
        if (newValue !== value) {
            valueIncreased(newValue);
        }
    }

    function decValue() {
        var newValue = Math.max(spinnerRoot.value - spinnerRoot.step, spinnerRoot.minValue);
        if (newValue !== value) {
            valueDecreased(newValue);
        }
    }

//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "orange"
//    }

    DTextInput {
        id: textInput

        width: parent.width - buttonsColumn.width
        height: DStyle.spinnerHeight

        editor.inputMethodHints: Qt.ImhDigitsOnly
        editor.horizontalAlignment: TextInput.AlignHCenter
        editor.validator: DoubleValidator {
            bottom: spinnerRoot.minValue
            top: spinnerRoot.maxValue
        }

        pixelSize: DStyle.fontSizeM
        showClearButton: false

        onTextChanged: {
            if (textInput.text === "-") {
                return;
            }

            var newValue = Math.min(spinnerRoot.maxValue, Math.max(spinnerRoot.minValue, Number(textInput.text)));
            if (newValue !== value)
                textUpdated(newValue);
        }

        onKeyEvent: {
            //console.log("DSpinner.textInput.onKeyEvent - event.key: " + event.key);
            // Switch Key
            switch (event.key) {
                case Qt.Key_Down: {
                    // Dec Value
                    spinnerRoot.decValue();
                } break;

                case Qt.Key_Up: {
                    // Inc Value
                    spinnerRoot.incValue();
                } break;

                case Qt.Key_Backspace: {
                    if (textInput.text === "NaN") {
                        textInput.text = "";
                    }
                } break;
            }
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

//            Rectangle {
//                anchors.fill: parent
//                color: "transparent"
//                border.color: "lime"
//            }

            DText {
                anchors.centerIn: parent
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

//            Rectangle {
//                anchors.fill: parent
//                color: "transparent"
//                border.color: "lime"
//            }

            DText {
                anchors.centerIn: parent
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

