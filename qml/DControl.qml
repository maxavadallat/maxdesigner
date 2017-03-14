import QtQuick 2.0

import "style"

Item {
    opacity: enabled ? 1.0 : DStyle.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: DStyle.animDuration } }
    visible: opacity > 0.0
}
