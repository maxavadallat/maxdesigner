import QtQuick 2.0

import "Style.js" as STYLE

MouseArea {
    id: mouseAreaRoot

    hoverEnabled: true

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
