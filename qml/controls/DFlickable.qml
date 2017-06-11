import QtQuick 2.0

import "../style"

Item {
    id: flickableRoot

    width: 300
    height: 400

    default property alias contentContainer: contentContainerColumn.children
    property alias containerColumn: contentContainerColumn
    property alias contentHeight: contentContainerFlickable.contentHeight
    property alias contentY: contentContainerFlickable.contentY
    property bool interactive: true

    clip: true

    // Flick To Ensure Rectangle Visibility
    function flick(rectangle, animated) {
        // Check Content Position
        if (contentContainerFlickable.contentY >= rectangle.y) {
            // Check Animated
            if (animated) {
                // Set From
                contentYAnimation.from = contentContainerFlickable.contentY;
                // Set To
                contentYAnimation.to = rectangle.y;
                // Start Animation
                contentYAnimation.start();

            } else {
                // Set Content Position
                contentContainerFlickable.contentY = rectangle.y;
            }

        // Check Content Position
        } else if (contentContainerFlickable.contentY + contentContainerFlickable.height <= rectangle.y + rectangle.height) {
            // Calculate New Content Position
            var newContentY = rectangle.y + rectangle.height - contentContainerFlickable.height;

            // Check Animated
            if (animated) {
                // Set From
                contentYAnimation.from = contentContainerFlickable.contentY;
                // Set To
                contentYAnimation.to = newContentY;
                // Start Animation
                contentYAnimation.start();

            } else {
                // Set Content Position
                contentContainerFlickable.contentY = newContentY;
            }
        }
    }

    PropertyAnimation {
        id: contentYAnimation
        target: contentContainerFlickable
        property: "contentY"
        duration: DStyle.animDuration * 0.5
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
