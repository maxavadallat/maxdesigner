import QtQuick 2.0

import "style"

Canvas {
    id: noContentRoot

    width: 400
    height: 300

    opacity: 0.2

    onPaint: {
        // Get 2D Context
        var ctx = getContext("2d");
        // Reset
        ctx.reset();

        ctx.lineWidth = 1;
        ctx.strokeStyle = Style.colorBorderNoFocus;
        ctx.beginPath();
        ctx.moveTo(0, 0);
        ctx.lineTo(noContentRoot.width, noContentRoot.height);
        ctx.moveTo(noContentRoot.width, 0);
        ctx.lineTo(0, noContentRoot.height);
        ctx.closePath();
        ctx.stroke();
    }
}
