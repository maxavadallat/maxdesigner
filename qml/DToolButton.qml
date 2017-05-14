import QtQuick 2.0

import "style"
import "DConstants.js" as CONSTS

DMouseArea {
    id: toolButtonRoot

    width: CONSTS.defaultToolButtonWidth
    height: CONSTS.defaultToolButtonHeight

    property alias source: iconImage.source

//    DRectangle {
//        anchors.fill: parent
//        color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.3)
//        radius: DStyle.defaultRadius
//
//    }

    DImage {
        id: iconImage
        anchors.centerIn: parent
        opacity: 0.7
        scale: parent.pressed ? DStyle.pressedScale : 1.0
    }
}
