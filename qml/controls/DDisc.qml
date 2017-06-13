import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/animations"

DMouseArea {
    id: discRoot

    width: CONSTS.defaultDiscWidth
    height: CONSTS.defaultDiscHeight

    property bool hovering: false

    hoverEnabled: true

    onEntered: {
        discRoot.hovering = true;
    }

    onExited: {
        discRoot.hovering = false;
    }

    onCanceled: {
        discRoot.hovering = false;
    }

    DImage {
        id: discImage
        width: parent.width * 1.2
        height: parent.height * 1.2
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -0.01 * width
        anchors.verticalCenterOffset: -0.012 * height
        fillMode: Image.PreserveAspectFit
        source: "qrc:/assets/images/blue-disc.png"
        scale: parent.pressed ? 0.9 : 1.0
        opacity: parent.hovering ? 0.8 : 0.2
        Behavior on opacity { DFadeAnimation { } }
        Behavior on scale { DFadeAnimation { property: "scale" } }
        smooth: true
        antialiasing: true
    }


}
