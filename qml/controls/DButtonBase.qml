import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"

DMouseArea {
    id: buttonBaseRoot

    width: CONSTS.defaultButtonWidth
    height: CONSTS.defaultButtonHeight

    // Button Text
    property string text: "Button"

    // Checked State
    property bool checked: false
    // Highlighted State
    property bool highlight: false

    onPressed: {
        // Set highlight
        buttonBaseRoot.highlight = true;
    }

    onReleased: {
        // Reset highlight
        buttonBaseRoot.highlight = false;
    }

    onCanceled: {
        // Reset highlight
        buttonBaseRoot.highlight = false;
    }
}
