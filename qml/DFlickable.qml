import QtQuick 2.0

import "style"

Item {
    id: flickableRoot

    width: 300
    height: 400

    default property alias contentContainer: contentContainerColumn.children

    property alias contentHeight: contentContainerFlickable.contentHeight
    property alias contentY: contentContainerFlickable.contentY
    property bool interactive: true

    clip: true

    // Flick To Ensure Rectangle Visibility
    function flick(rectangle) {
        // Check Content Position
        if (contentContainerFlickable.contentY >= rectangle.y) {
            // Set Content Position
            contentContainerFlickable.contentY = rectangle.y;
        // Check Content Position
        } else if (contentContainerFlickable.contentY + contentContainerFlickable.height <= rectangle.y + rectangle.height) {
            // Set Content Position
            contentContainerFlickable.contentY = rectangle.y + rectangle.height - contentContainerFlickable.height;
        }
    }

    Flickable {
        id: contentContainerFlickable
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        pixelAligned: true
        contentWidth: contentContainerColumn.width
        contentHeight: contentContainerColumn.height
        interactive: flickableRoot.interactive && (contentHeight > height)

        Column {
            id: contentContainerColumn
            width: contentContainerFlickable.width
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
