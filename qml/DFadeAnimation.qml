import QtQuick 2.0

import "Style.js" as STYLE

NumberAnimation {
    property: "opacity"
    duration: STYLE.animDuration * 0.5
}
