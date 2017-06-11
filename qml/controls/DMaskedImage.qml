import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../style"

OpacityMask {
    id: maskedImageRoot

    width: maskSource.width
    height: maskSource.height

    property string imageSource: ""
    property var fillMode: Image.Pad

    source: Rectangle {
        width: maskSource.width
        height: maskSource.height
        color: DStyle.colorBorderNoFocus
        visible: false
    }

    maskSource: DImage {
        fillMode: maskedImageRoot.fillMode
        source: maskedImageRoot.imageSource
    }
}
