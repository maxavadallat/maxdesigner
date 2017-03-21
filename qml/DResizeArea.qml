import QtQuick 2.0

import "style"

MouseArea {
    id: mouseAreaRoot

    hoverEnabled: enabled
    visible: enabled

    property int pressPosX: 0
    property int pressPosY: 0

    onPressed: {
        pressPosX = mouse.x;
        pressPosY = mouse.y;
    }

    preventStealing: true

    cursorShape: Qt.SizeAllCursor

    DTracer { }
}
