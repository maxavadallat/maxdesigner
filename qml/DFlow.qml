import QtQuick 2.7

import "style"
import "DConstants.js" as CONSTS

Flow {
    id: flowRoot

    width: 300

    spacing: DStyle.defaultSpacing

    populate: Transition {
        DAnimation { properties: "height" }
    }

    move: Transition {
        DAnimation { properties: "x, y" }
    }

}

