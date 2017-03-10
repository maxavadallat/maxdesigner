import QtQuick 2.0

import "style"
import "Constants.js" as CONSTS

Flow {
    id: flowRoot

    property int cellWidth: CONSTS.componentItemWidth
    property int cellHeight: CONSTS.componentItemHeight

    spacing: Style.defaultSpacing

//    add: Transition {
//        SequentialAnimation {
//            alwaysRunToEnd: true
//            PauseAnimation { duration: 200 }
//            DAnimation { properties: "opacity, scale"; from: 0.0; to: 1.0; /*easing.type: Easing.OutBack*/ }
//        }
//    }

    move: Transition {
        DAnimation { properties: "x, y" }
    }
}
