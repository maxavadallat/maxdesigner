import QtQuick 2.0

import "style"
import "DConstants.js" as CONSTS

DControl {
    id: listViewRoot

    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias count: listView.count
    property alias currentIndex: listView.currentIndex

    property int itemHeight: CONSTS.defaultPaneItemHeight

    clip: true

    ListView {
        id: listView
        anchors.fill: parent
        highlightFollowsCurrentItem: true

        add: Transition {
            ParallelAnimation {
                NumberAnimation { property: "height"; from: 0; to: listViewRoot.itemHeight; duration: DStyle.animDuration }
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: DStyle.animDuration }
            }
        }

        addDisplaced: Transition {
            NumberAnimation { properties: "x, y"; duration: DStyle.animDuration }
        }

        move: Transition {
            NumberAnimation { properties: "x, y"; duration: DStyle.animDuration }
        }

        moveDisplaced: Transition {
            NumberAnimation { properties: "x, y"; duration: DStyle.animDuration }
        }

        remove: Transition {
            NumberAnimation { properties: "height, opacity"; to: 0; duration: DStyle.animDuration }
        }

        removeDisplaced: Transition {
            NumberAnimation { properties: "x, y"; duration: DStyle.animDuration }
        }
    }

    DScrollIndicator {
        id: scrollIndicator
        x: parent.width - width
        viewSize: listView.height
        viewContentPos: listView.contentY
        viewContentSize: listView.contentHeight
    }
}
