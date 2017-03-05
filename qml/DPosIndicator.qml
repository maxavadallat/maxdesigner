import QtQuick 2.0
//import QtGraphicalEffects 1.0

import "style"

DRectangle {
    id: posIndicatorRoot

    //width: Style.posIndicatorWidth
    //height: Style.posIndicatorHeight
    width: posOverlay.width + 12
    height: posOverlay.height + 4

    property int posX: 0
    property int posY: 0

    property bool autoHide: true

    border.color: Style.colorBorderTransparent
    radius: 0

    opacity: 0.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    onPosXChanged: {
        showPosIndicator();
    }

    onPosYChanged: {
        showPosIndicator();
    }

    function showPosIndicator() {
        posIndicatorRoot.opacity = 1.0;
        if (posIndicatorRoot.autoHide) {
            hideTimer.restart();
        }
    }

    DText {
        id: posOverlay
        anchors.centerIn: parent
        text: "[" + Math.round(posIndicatorRoot.posX) + ":" + Math.round(posIndicatorRoot.posY) + "]"
        visible: true
    }

//    Glow {
//        id: posOverlayGlow
//        anchors.fill: posOverlay
//        source: posOverlay
//        radius: 4
//        samples: 16
//        color: Style.colorBorder
//    }

    Timer {
        id: hideTimer
        interval: Style.defaultHideTimeout
        onTriggered: {
            posIndicatorRoot.opacity = 0.0;
        }
    }
}
