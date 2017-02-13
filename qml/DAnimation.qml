import QtQuick 2.0

import "Style.js" as STYLE

NumberAnimation {
    duration: STYLE.animDuration
    easing.type: Easing.InOutCubic
}
