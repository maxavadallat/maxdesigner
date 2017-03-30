import QtQuick 2.0

import "style"

DControl {
    id: listViewRoot

    property alias model: listView.model
    property alias delegate: listView.delegate
    property alias count: listView.count
    property alias currentIndex: listView.currentIndex

    clip: true

    ListView {
        id: listView
        anchors.fill: parent

        add: Transition {
            NumberAnimation {
                properties: "height"; duration: DStyle.animDuration
            }
        }

        addDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"; duration: DStyle.animDuration
            }
        }

        move: Transition {
            NumberAnimation {
                properties: "x, y"; duration: DStyle.animDuration
            }
        }

        moveDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"; duration: DStyle.animDuration
            }
        }

        remove: Transition {
            NumberAnimation {
                properties: "height"; duration: DStyle.animDuration
            }
        }

        removeDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"; duration: DStyle.animDuration
            }
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
