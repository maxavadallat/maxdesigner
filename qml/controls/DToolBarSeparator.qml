import QtQuick 2.0

import "../style"
import "../system/DConstants.js" as CONSTS

Item {
    width: DStyle.defaultSpacing
    height: CONSTS.defaultToolButtonHeight

    DText {
        anchors.centerIn: parent
        rotation: 90
        text: "---"
    }
}
