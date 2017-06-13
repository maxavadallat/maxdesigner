import QtQuick 2.0
//import QtGraphicalEffects 1.0

import "qrc:/qml/style"
import "qrc:/qml/animations"

DRectangle {
    id: posIndicatorRoot

    //width: DStyle.posIndicatorWidth
    //height: DStyle.posIndicatorHeight
    width: posOverlay.width + 12
    height: posOverlay.height + 4

    property int posX: 0
    property int posY: 0

    property bool autoHide: true

    border.color: DStyle.colorBorderTransparent
    radius: 0

    opacity: 0.0
    Behavior on opacity { DFadeAnimation { } }
    visible: posIndicatorRoot.enabled && (opacity > 0.0)

    onPosXChanged: {
        showPosIndicator();
    }

    onPosYChanged: {
        showPosIndicator();
    }

    onEnabledChanged: {
        showPosIndicator();
    }

    function showPosIndicator() {
        if (posIndicatorRoot.enabled) {
            posIndicatorRoot.opacity = 1.0;
            if (posIndicatorRoot.autoHide) {
                hideTimer.restart();
            }
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
//        color: DStyle.colorBorder
//    }

    Timer {
        id: hideTimer
        interval: DStyle.defaultHideTimeout
        onTriggered: {
            posIndicatorRoot.opacity = 0.0;
        }
    }
}
