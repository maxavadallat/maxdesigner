import QtQuick 2.0
import QtGraphicalEffects 1.0

import "DConstants.js" as CONSTS
import "style"

DMouseArea {
    id: containerRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    default property alias mainContainer: contentContainer.children

    property bool selected: false

    property int minWidth: 0
    property int minHeight: 0

    property bool showBackground: true
    property bool enableSizeOverlay: true
    property bool enablePosOverlay: true

    property alias backgroundColor: containerBG.color
    property string borderColor: DStyle.colorBorderNoFocus
    property alias radius: containerBG.radius

    property alias clipContent: contentContainer.clip
    property alias enableContent: contentContainer.enabled

    property bool mainDrag: true
    property bool enableDrag: true
    property bool enablePanByKeys: true
    property bool enableResize: true
    property bool setFocusOnResize: false
    property bool rootContainer: false

    property QtObject parentContainer: null

    drag.target: enableDrag ? containerRoot : undefined
    drag.minimumX: 0
    drag.minimumY: 0
    drag.maximumX: parent ? (parent.width - containerRoot.width) : 0
    drag.maximumY: parent ? (parent.height - containerRoot.height) : 0
    drag.threshold: 0
    // For Some re
    drag.filterChildren: true
    //drag.smoothed: true

    signal resizePressed()

    Keys.onPressed: {
        //console.log("DContainer.Keys.onPressed - key: " + event.key);

        switch (event.key) {
            case Qt.Key_Left:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
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
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    containerRoot.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    containerRoot.y += CONSTS.componentMoveStep;
                }
            break;

            // ...
        }
    }

    // Background
    DRectangle {
        id: containerBG
        anchors.fill: parent
        visible: containerRoot.showBackground
        border.color: containerRoot.borderColor
    }

    // THIS IS ONLY FOR THE drag.filterChildren to work
    MouseArea {
        anchors.fill: parent
    }

    // Content Container
    Item {
        id: contentContainer
        anchors.fill: parent
        clip: true
    }

    // Position Indicator
    DPosIndicator {
        id: posIndicator
        anchors.left: parent.left
        anchors.top: parent.top
        enabled: enablePosOverlay
        posX: containerRoot.x
        posY: containerRoot.y
    }

    // Size Indicator
    DSizeIndicator {
        id: sizeIndicator
        anchors.centerIn: parent
        enabled: enableSizeOverlay
        sizeW: containerRoot.width
        sizeH: containerRoot.height
    }

    // Resize Area - Top Left
    DResizeArea {
        id: topLeftResizer
        width: DStyle.resizeAreaSize * 1.5
        height: DStyle.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -DStyle.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Top Center
    DResizeArea {
        id: topResizer
        width: parent.width - DStyle.resizeAreaSize * 2
        height: DStyle.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Top Right
    DResizeArea {
        id: topRightResizer
        width: DStyle.resizeAreaSize * 1.5
        height: DStyle.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -DStyle.resizeAreaSize * 0.5
        anchors.top: parent.top
        anchors.topMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Left
    DResizeArea {
        id: leftResizer
        width: DStyle.resizeAreaSize
        height: parent.height - DStyle.resizeAreaSize * 2
        anchors.left: parent.left
        anchors.leftMargin: -DStyle.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Right
    DResizeArea {
        id: rightResizer
        width: DStyle.resizeAreaSize
        height: parent.height - DStyle.resizeAreaSize * 2
        anchors.right: parent.right
        anchors.rightMargin: -DStyle.resizeAreaSize * 0.5
        anchors.verticalCenter: parent.verticalCenter
        cursorShape: Qt.SizeHorCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Bottom Left
    DResizeArea {
        id: bottomLeftResizer
        width: DStyle.resizeAreaSize * 1.5
        height: DStyle.resizeAreaSize * 1.5
        anchors.left: parent.left
        anchors.leftMargin: -DStyle.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeBDiagCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Bottom Center
    DResizeArea {
        id: bottomResizer
        width: parent.width - DStyle.resizeAreaSize * 2
        height: DStyle.resizeAreaSize
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeVerCursor
        enabled: containerRoot.enableResize

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

    // Resize Area - Bottom Right
    DResizeArea {
        id: bottomRightResizer
        width: DStyle.resizeAreaSize * 1.5
        height: DStyle.resizeAreaSize * 1.5
        anchors.right: parent.right
        anchors.rightMargin: -DStyle.resizeAreaSize * 0.5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -DStyle.resizeAreaSize * 0.5
        cursorShape: Qt.SizeFDiagCursor
        enabled: containerRoot.enableResize

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
