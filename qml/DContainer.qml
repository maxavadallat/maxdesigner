import QtQuick 2.0
import QtGraphicalEffects 1.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DMouseArea {
    id: containerRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    default property alias mainContainer: contentContainer.children

    property bool focused: false

    property bool selected: false

    property var model: null

    property int minWidth: 0
    property int minHeight: 0

    property bool showBackground: true
    property bool enableSizeOverlay: true
    property bool enablePosOverlay: true

    property alias backgroundColor: containerBG.color
    property alias border: containerBG.border
    //property alias borderColor: containerBG.border.color

    property alias clipContent: contentContainer.clip
    property alias enableContent: contentContainer.enabled

    property bool mainDrag: true

    onPressed: {
        if (containerRoot.mainDrag && parent.setDragTarget !== undefined) {
            // Set Drag Target - ASSUMING Parent is MainGrabArea
            parent.setDragTarget(containerRoot);
        }
    }

    onReleased: {
        if (containerRoot.mainDrag && parent.clearDragTarget !== undefined) {
            // Clear Drag Target - ASSUMING Parent is MainGrabArea
            parent.clearDragTarget();
        }
    }

    // Background
    DRectangle {
        id: containerBG
        anchors.fill: parent
        visible: containerRoot.showBackground
    }

    Item {
        id: contentContainer
        anchors.fill: parent
        clip: true
    }

    DPosIndicator {
        id: posIndicator
        anchors.left: parent.left
        anchors.top: parent.top
        posX: enablePosOverlay ? containerRoot.x : 0
        posY: enablePosOverlay ? containerRoot.y : 0
    }

    DSizeIndicator {
        id: sizeIndicator
        anchors.centerIn: parent
        sizeW: enableSizeOverlay ? containerRoot.width : 0
        sizeH: enableSizeOverlay ? containerRoot.height : 0
    }

    DResizeArea {
        id: topLeftResizer
        width: STYLE.resizeAreaSize * 1.5
        height: STYLE.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -STYLE.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width + deltaX > containerRoot.minWidth) {
                    parent.x = parent.x - deltaX;
                    parent.width = parent.width + deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height + deltaY > containerRoot.minHeight) {
                    parent.y = parent.y - deltaY;
                    parent.height = parent.height + deltaY;
                }
            }
        }
    }

    DResizeArea {
        id: topResizer
        width: parent.width - STYLE.resizeAreaSize * 2
        height: STYLE.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor

        onPositionChanged: {
            if (pressed) {
                var deltaY = pressPosY - mouse.y;

                if (parent.height + deltaY > containerRoot.minHeight) {
                    parent.y = parent.y - deltaY;
                    parent.height = parent.height + deltaY;
                }
            }
        }
    }

    DResizeArea {
        id: topRightResizer
        width: STYLE.resizeAreaSize * 1.5
        height: STYLE.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -STYLE.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width - deltaX > containerRoot.minWidth) {
                    //parent.x = parent.x - deltaX;
                    parent.width = parent.width - deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height + deltaY > containerRoot.minHeight) {
                    parent.y = parent.y - deltaY;
                    parent.height = parent.height + deltaY;
                }
            }
        }
    }

    DResizeArea {
        id: leftResizer
        width: STYLE.resizeAreaSize
        height: parent.height - STYLE.resizeAreaSize * 2
        anchors.left: parent.left
        anchors.leftMargin: -STYLE.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width + deltaX > containerRoot.minWidth) {
                    parent.x = parent.x - deltaX;
                    parent.width = parent.width + deltaX;
                }
            }
        }
    }

    DResizeArea {
        id: rightResizer
        width: STYLE.resizeAreaSize
        height: parent.height - STYLE.resizeAreaSize * 2
        anchors.right: parent.right
        anchors.rightMargin: -STYLE.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width - deltaX > containerRoot.minWidth) {
                    parent.width = parent.width - deltaX;
                }
            }
        }
    }

    DResizeArea {
        id: bottomLeftResizer
        width: STYLE.resizeAreaSize * 1.5
        height: STYLE.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -STYLE.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width + deltaX > containerRoot.minWidth) {
                    parent.x = parent.x - deltaX;
                    parent.width = parent.width + deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height - deltaY > containerRoot.minHeight) {
                    parent.height = parent.height - deltaY;
                }
            }
        }
    }

    DResizeArea {
        id: bottomResizer
        width: parent.width - STYLE.resizeAreaSize * 2
        height: STYLE.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor

        onPositionChanged: {
            if (pressed) {
                var deltaY = pressPosY - mouse.y;

                if (parent.height - deltaY > containerRoot.minHeight) {
                    parent.height = parent.height - deltaY;
                }
            }
        }
    }

    DResizeArea {
        id: bottomRightResizer
        width: STYLE.resizeAreaSize * 1.5
        height: STYLE.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -STYLE.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -STYLE.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor

        onPositionChanged: {
            if (pressed) {
                var deltaX = pressPosX - mouse.x;

                if (parent.width - deltaX > containerRoot.minWidth) {
                    parent.width = parent.width - deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height - deltaY > containerRoot.minHeight) {
                    parent.height = parent.height - deltaY;
                }
            }
        }
    }
}
