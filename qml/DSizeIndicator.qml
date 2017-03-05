import QtQuick 2.0
//import QtGraphicalEffects 1.0

import "style"

DRectangle {
    id: sizeIndicatorRoot

    //width: Style.sizeIndicatorWidth
    //height: Style.sizeIndicatorHeight

    width: sizeOverlay.width + 12
    height: sizeOverlay.height + 4

    property int sizeW: 0
    property int sizeH: 0

    property bool autoHide: true

    border.color: Style.colorBorderTransparent
    radius: 0

    opacity: 0.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    onSizeWChanged: {
        showSizeIndicator();
    }

    onSizeHChanged: {
        showSizeIndicator();
    }

    function showSizeIndicator() {
        sizeIndicatorRoot.opacity = 1.0;
        if (sizeIndicatorRoot.autoHide) {
            hideTimer.restart();
        }
    }

    DText {
        id: sizeOverlay
        anchors.centerIn: parent
        text: "[" + sizeIndicatorRoot.sizeW + "x" + sizeIndicatorRoot.sizeH + "]"
        //visible: false
    }

//    Glow {
//        id: sizeOverlayGlow
//        anchors.fill: sizeOverlay
//        source: sizeOverlay
//        radius: 4
//        samples: 16
//        color: Style.colorBorder
//    }

    Timer {
        id: hideTimer
        interval: Style.defaultHideTimeout
        onTriggered: {
            sizeIndicatorRoot.opacity = 0.0;
        }
    }
}
