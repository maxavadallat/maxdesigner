import QtQuick 2.0
import QtGraphicalEffects 1.0

import "Constants.js" as CONSTS
import "style"

DMouseArea {
    id: containerRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    default property alias mainContainer: contentContainer.children

    //property bool focused: false

    property bool selected: false

    property var model: null

    property int minWidth: 0
    property int minHeight: 0

    property bool showBackground: true
    property bool enableSizeOverlay: true
    property bool enablePosOverlay: true

    property alias backgroundColor: containerBG.color
    property alias border: containerBG.border
    property alias radius: containerBG.radius
    //property alias borderColor: containerBG.border.color

    property alias clipContent: contentContainer.clip
    property alias enableContent: contentContainer.enabled

    property bool mainDrag: true

    property bool setFocusOnResize: true

    property bool rootContainer: false

    property QtObject parentContainer: null

    signal resizePressed()

    onPressed: {
        //console.log("DContainer.onPressed");
//        if (containerRoot.mainDrag && parent.setDragTarget !== undefined) {
//            // Set Drag Target - ASSUMING Parent is MainGrabArea
//            parent.setDragTarget(containerRoot);
//        }
    }

    onReleased: {
        //console.log("DContainer.onReleased");
//        if (containerRoot.mainDrag && parent.clearDragTarget !== undefined) {
//            // Clear Drag Target - ASSUMING Parent is MainGrabArea
//            parent.clearDragTarget();
//        }
    }

    onFocusChanged: {
        //console.log("DContainer.onFocusChanged - focus: " + focus);
    }

    Keys.onPressed: {
        //console.log("DContainer.Keys.onPressed - key: " + event.key);

        switch (event.key) {
            case Qt.Key_Left:
                // Check Auto repeat
                if (event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y += CONSTS.componentMoveStep;
                }
            break;

            // ...
        }
    }

    Keys.onReleased: {
        //console.log("DContainer.Keys.onReleased - key: " + event.key);

        switch (event.key) {
            case Qt.Key_Escape:
                // Check If Root Container
                if (!containerRoot.rootContainer) {
                    // Check Parent Container
                    if (containerRoot.parentContainer) {
                        // Set Focus
                        containerRoot.parentContainer.focus = true;
                    }
                }
            break;

            case Qt.Key_Left:
                // Check Auto repeat
                if (!event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (!event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (!event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (!event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_T:
                settingsController.tracerVisible = !settingsController.tracerVisible;
            break;

            // ...
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
        width: Style.resizeAreaSize * 1.5
        height: Style.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -Style.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: parent.width - Style.resizeAreaSize * 2
        height: Style.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: Style.resizeAreaSize * 1.5
        height: Style.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -Style.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: Style.resizeAreaSize
        height: parent.height - Style.resizeAreaSize * 2
        anchors.left: parent.left
        anchors.leftMargin: -Style.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: Style.resizeAreaSize
        height: parent.height - Style.resizeAreaSize * 2
        anchors.right: parent.right
        anchors.rightMargin: -Style.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: Style.resizeAreaSize * 1.5
        height: Style.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -Style.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: parent.width - Style.resizeAreaSize * 2
        height: Style.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
        width: Style.resizeAreaSize * 1.5
        height: Style.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -Style.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -Style.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                containerRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (containerRoot.setFocusOnResize) {
                // Set Focus
                containerRoot.focus = true;
            }
        }

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
