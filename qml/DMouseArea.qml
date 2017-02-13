import QtQuick 2.0

import "Style.js" as STYLE

MouseArea {
    id: mouseAreaRoot

    property alias tracerVisible: tracer.visible

    opacity: enabled ? 1.0 : STYLE.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: STYLE.animDuration } }
    visible: opacity > 0.0

    DTracer {
        id: tracer
    }
}
