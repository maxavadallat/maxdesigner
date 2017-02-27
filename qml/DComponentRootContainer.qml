import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DPaneBase {
    id: compoenntRootContainerRoot

    title: "Component"

    hideToSide: hideToBottom

    enablePosOverlay: false
    enableSizeOverlay: true

    showTitle: false
    showBackground: false

    Canvas {
        id: baseCanvas
        anchors.fill: parent
        onPaint: {
            // Get 2D Context
            var ctx = getContext("2d");

            ctx.lineWidth = 1;
            ctx.strokeStyle = STYLE.colorBorderNoFocus;
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(baseCanvas.width, baseCanvas.height);
            ctx.moveTo(baseCanvas.width, 0);
            ctx.lineTo(0, baseCanvas.height);
            ctx.closePath();
            ctx.stroke();
        }
    }

    // ...

}
