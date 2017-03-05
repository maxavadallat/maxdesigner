import QtQuick 2.0

import "style"
import "Constants.js" as CONSTS

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
