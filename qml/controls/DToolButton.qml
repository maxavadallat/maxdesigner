import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../style"
import "../system/DConstants.js" as CONSTS

DButtonBase {
    id: toolButtonRoot

    width: CONSTS.defaultToolButtonWidth
    height: CONSTS.defaultToolButtonHeight

    property alias source: iconImage.source

    text: ""

    Item {
        anchors.centerIn: parent
        scale: parent.pressed ? DStyle.pressedScale : 1.0

        DImage {
            id: iconImage
            anchors.centerIn: parent
            opacity: 0.7
        }

        Glow {
            anchors.fill: iconImage
            radius: DStyle.defaultGlowRadius
            samples: DStyle.defaultGlowSamples
            spread: DStyle.defaultGlowSpread
            color: DStyle.colorFontDark
            source: iconImage
            visible: toolButtonRoot.checked
        }
    }
}
