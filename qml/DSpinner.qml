import QtQuick 2.0

import "Style.js" as STYLE

DTextInput {
    id: spinnerRoot

    height: STYLE.spinnerHeight

    property double value: 0.0

    property double step: 1.0

    property double minValue: -100.0
    property double maxValue: 100.0

    editor.inputMethodHints: Qt.ImhDigitsOnly
    editor.horizontalAlignment: TextInput.AlignHCenter
    editor.validator: IntValidator { }

    text: Number(spinnerRoot.value)

    signal valueIncreased(var newValue)
    signal valueDecreased(var newValue)

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

    Column {
        id: buttonsColumn
        anchors.right: parent.right
        anchors.rightMargin: STYLE.defaultMargin
        anchors.verticalCenter: parent.verticalCenter

        DMouseArea {
            width: STYLE.spinnerButtonHeight
            height: STYLE.spinnerButtonHeight
            anchors.right: parent.right

            onClicked: {
                incValue();
            }


        }

        DMouseArea {
            width: STYLE.spinnerButtonHeight
            height: STYLE.spinnerButtonHeight
            anchors.right: parent.right

            onClicked: {
                decValue();
            }


        }
    }
}
