import QtQuick 2.7

import "style"
import "Constants.js" as CONSTS

GridView {
    id: gridRoot

    add: Transition {
        SequentialAnimation {
            alwaysRunToEnd: true
            PauseAnimation { duration: 200 }
            DAnimation { properties: "opacity, scale"; from: 0.0; to: 1.0; easing.type: Easing.OutBack }
        }
    }

    addDisplaced: Transition {
        DAnimation { properties: "x, y" }
    }

    move: Transition {
        DAnimation { properties: "x, y" }
    }

    moveDisplaced: Transition {
        DAnimation { properties: "x, y" }
    }

    remove: Transition {
        ParallelAnimation {
            alwaysRunToEnd: true
            DAnimation { properties: "width"; to: 0 }
            DAnimation { properties: "height"; to: 0 }
        }
    }

    removeDisplaced: Transition {
        DAnimation { properties: "x, y" }
    }

    // ...
}
