import QtQuick 2.0

import "Style.js" as STYLE

Loader {
    anchors.fill: parent
    asynchronous: true
    active: settingsController.tracerVisible
    sourceComponent: Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: STYLE.colorTrace
    }
}
