import QtQuick 2.7

import "qrc:/qml/style"
import "qrc:/qml/animations"

MouseArea {
    id: mouseAreaRoot

    property bool hidden: false

    opacity: mouseAreaRoot.hidden ? 0.0 : (mouseAreaRoot.enabled ? 1.0 : DStyle.disabledOpacity)
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    DTracer { }
}
