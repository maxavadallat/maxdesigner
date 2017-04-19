import QtQuick 2.0

import "style"
import "DConstants.js" as CONSTS

Item {
    id: flowRoot

    width: 300
    height: flow.height

    Behavior on width { DAnimation { } }
    Behavior on height { DAnimation { } }

    default property alias contentContainer: flow.children
    property alias spacing: flow.spacing
    property alias flowItem: flow

    clip: true

    Flow {
        id: flow
        width: flowRoot.width

        property int cellWidth: CONSTS.componentItemWidth
        property int cellHeight: CONSTS.componentItemHeight

        spacing: DStyle.defaultSpacing

    //    add: Transition {
    //        SequentialAnimation {
    //            alwaysRunToEnd: true
    //            PauseAnimation { duration: 200 }
    //            DAnimation { properties: "opacity, scale"; from: 0.0; to: 1.0; /*easing.type: Easing.OutBack*/ }
    //        }
    //    }

        populate: Transition {
            DAnimation { properties: "height" }
        }

        move: Transition {
            DAnimation { properties: "x, y" }
        }
    }
}

