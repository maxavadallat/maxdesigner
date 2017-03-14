import QtQuick 2.0

import "style"

Canvas {
    id: noContentRoot

    width: 400
    height: 300

//    Behavior on width { DAnimation { } }
//    Behavior on height { DAnimation { } }

    opacity: 0.2
    visible: opacity > 0.0

    onPaint: {
        // Get 2D Context
        var ctx = getContext("2d");
        // Reset
        ctx.reset();

        ctx.lineWidth = 1;
        ctx.strokeStyle = DStyle.colorBorderNoFocus;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(noContentRoot.width, noContentRoot.height);
        ctx.moveTo(noContentRoot.width, 0);
        ctx.lineTo(0, noContentRoot.height);
        ctx.closePath();
        ctx.stroke();
    }
}
