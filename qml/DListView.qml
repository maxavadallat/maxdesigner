import QtQuick 2.0

import "style"

DControl {
    id: listViewRoot

    property alias model: listView.model
    property alias delegate: listView.delegate

    ListView {
        id: listView
        anchors.fill: parent

    }

    DScrollIndicator {
        id: scrollIndicator
        x: parent.width - width
        viewSize: listView.height
        viewContentPos: listView.contentY
        viewContentSize: listView.contentHeight
    }
}
