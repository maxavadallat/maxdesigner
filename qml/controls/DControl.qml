import QtQuick 2.0

import "qrc:/qml/style"
import "qrc:/qml/animations"

Item {
    opacity: enabled ? 1.0 : DStyle.disabledOpacity
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0
}
