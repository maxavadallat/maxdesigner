import QtQuick 2.0

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS

DControl {
    id: listViewRoot

    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias count: listView.count
    property alias currentIndex: listView.currentIndex
    property alias contentY: listView.contentY
    property alias contentHeight: listView.contentHeight
    property int itemHeight: CONSTS.defaultPaneItemHeight

    property alias spacing: listView.spacing
    property alias addTransition: listView.add
    property alias addDisplacedTransition: listView.addDisplaced
    property alias moveTransition: listView.move
    property alias removeTransition: listView.remove
    property alias removeDisplacedTransition: listView.removeDisplaced
    property alias highlight: listView.highlight

    clip: true

    // Ensure Item Visible
    function ensureItemVisible(index) {
        // Position View At Index
        listView.positionViewAtIndex(index, ListView.Contain);
    }

    ListView {
        id: listView
        anchors.fill: parent

        highlightFollowsCurrentItem: true
        interactive: contentHeight > height

        add: Transition {
            ParallelAnimation {
                NumberAnimation { property: "height"; from: 0; to: listViewRoot.itemHeight; duration: DStyle.animDuration }
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: DStyle.animDuration }
            }
        }

        // SHOULD NOT OVERRIDE THIS!!! FUCKS UP MANY THINGS!!!
//        populate: Transition {
//            NumberAnimation { duration: DStyle.animDuration }
//        }

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
