import QtQuick 2.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DMouseArea {
    id: paneRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight


//    onXChanged: {

//    }

//    onYChanged: {

//    }

    onPressed: {
        // Set Drag Target - ASSUMING Parent is MainGrabArea
        parent.setDragTarget(paneRoot);
    }

    onReleased: {
        // Clear Drag Target - ASSUMING Parent is MainGrabArea
        parent.clearDragTarget();
    }

    // Background
    DRectangle {
        id: paneBG
        anchors.fill: parent
    }

    DText {
        id: titleText
        anchors.centerIn: parent
        text: "DContainer"
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

                if (parent.width + deltaX > 0) {
                    parent.x = parent.x - deltaX;
                    parent.width = parent.width + deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height + deltaY > 0) {
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

                if (parent.height + deltaY > 0) {
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

                if (parent.width - deltaX > 0) {
                    //parent.x = parent.x - deltaX;
                    parent.width = parent.width - deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height + deltaY > 0) {
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

                if (parent.width + deltaX > 0) {
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

                if (parent.width - deltaX > 0) {
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

                if (parent.width + deltaX > 0) {
                    parent.x = parent.x - deltaX;
                    parent.width = parent.width + deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height - deltaY > 0) {
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

                if (parent.height - deltaY > 0) {
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

                if (parent.width - deltaX > 0) {
                    parent.width = parent.width - deltaX;
                }

                var deltaY = pressPosY - mouse.y;

                if (parent.height - deltaY > 0) {
                    parent.height = parent.height - deltaY;
                }
            }
        }
    }
}
