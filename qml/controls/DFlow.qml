import QtQuick 2.7

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/animations"

Flow {
    id: flowRoot

    width: 300

    spacing: DStyle.defaultSpacing

//    add: Transition {
//        SequentialAnimation {
//            alwaysRunToEnd: true
//            PauseAnimation { duration: 200 }
//            DAnimation { properties: "opacity, scale"; from: 0.0; to: 1.0; /*easing.type: Easing.OutBack*/ }
//        }
//    }

    populate: Transition {
        DAnimation { property: "height" }
    }

    move: Transition {
        DAnimation { properties: "x, y" }
    }

}

