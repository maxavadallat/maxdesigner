import QtQuick 2.0

import "style"

Item {
    opacity: enabled ? 1.0 : Style.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: Style.animDuration } }
    visible: opacity > 0.0
}
