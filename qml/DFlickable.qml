import QtQuick 2.0

import "style"

Item {
    id: flickableRoot

    width: 300
    height: 400

    default property alias contentContainer: contentContainerColumn.children

    property alias contentHeight: contentContainerFlickable.contentHeight

    clip: true

    Flickable {
        id: contentContainerFlickable
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        pixelAligned: true
        contentWidth: contentContainerColumn.width
        contentHeight: contentContainerColumn.height
        interactive: contentHeight > height

        Column {
            id: contentContainerColumn
            width: parent.width
            spacing: DStyle.defaultSpacing
        }
    }

    DScrollIndicator {
        x: parent.width - width
        viewSize: contentContainerFlickable.height
        viewContentSize: contentContainerFlickable.contentHeight
        viewContentPos: contentContainerFlickable.contentY
    }
}
