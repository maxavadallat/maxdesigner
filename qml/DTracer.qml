import QtQuick 2.0

import "style"

Loader {
    anchors.fill: parent
    asynchronous: true
    active: settingsController.tracerVisible
    visible: settingsController.tracerVisible
    sourceComponent: Rectangle {
        anchors.fill: parent
        color: "transparent"//"#22FFFF00"
        border.color: DStyle.colorTrace
    }
}
