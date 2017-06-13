import QtQuick 2.0

import "qrc:/qml/style"
import "qrc:/qml/animations"

Rectangle {
    color: DStyle.colorBG
    border.color: DStyle.colorBorderNoFocus
    radius: DStyle.defaultRadius
    opacity: enabled ? 1.0 : DStyle.disabledOpacity
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0
}
