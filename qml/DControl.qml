import QtQuick 2.0

import "Style.js" as STYLE

Item {
    opacity: enabled ? 1.0 : STYLE.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: STYLE.animDuration } }
    visible: opacity > 0.0
}
