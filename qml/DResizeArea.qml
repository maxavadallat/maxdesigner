import QtQuick 2.0

import "style"
import "system"

MouseArea {
    id: resizeAreaRoot

    hoverEnabled: enabled
    visible: enabled

    property int pressPosX: 0
    property int pressPosY: 0

    preventStealing: true

    cursorShape: Qt.SizeAllCursor

    onPressed: {
        //console.log("DResizeArea.onPressed");
        // Set Last Mouse Press Owner
        DSystemModel.lastMousePressOwner = "raRoot";
        // Set Press Position
        pressPosX = mouse.x;
        pressPosY = mouse.y;
    }

    onReleased: {
        // Check Last Mouse Press Owner
        if (DSystemModel.lastMousePressOwner === "raRoot") {
            // Reset Last Mouse Press Owner
            DSystemModel.lastMousePressOwner = "";
        }
    }

    DTracer { }
}
