import QtQuick 2.0

import "style"
import "system"

MouseArea {
    id: resizeAreaRoot

    width: {
        // Switch Resize Pos
        switch (resizePos) {
            case "top":
            case "bottom": return parent.width - DStyle.resizeAreaSize * 2;
        }

        return DStyle.resizeAreaSize * 1.5;
    }

    height: {
        // Switch Resize Pos
        switch (resizePos) {
            case "left":
            case "right": return parent.height - DStyle.resizeAreaSize * 2;
        }

        return DStyle.resizeAreaSize * 1.5;
    }

    anchors.left: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "left":
            case "bottomLeft":  return parent.left;
        }

        return undefined;
    }

    anchors.leftMargin: -DStyle.resizeAreaSize * 0.5

    anchors.right: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topRight":
            case "right":
            case "bottomRight":  return parent.right;
        }

        return undefined;
    }

    anchors.rightMargin: -DStyle.resizeAreaSize * 0.5

    anchors.top: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "top":
            case "topRight":    return parent.top;
        }

        return undefined;
    }

    anchors.topMargin: -DStyle.resizeAreaSize * 0.5

    anchors.bottom: {
        // Switch Resize Pos
        switch (resizePos) {
            case "bottomLeft":
            case "bottom":
            case "bottomRight": return parent.bottom;
        }

        return undefined;
    }

    anchors.bottomMargin: -DStyle.resizeAreaSize * 0.5

    anchors.horizontalCenter: {
        // Switch Resize Pos
        switch (resizePos) {
            case "top":
            case "bottom":      return parent.horizontalCenter;
        }

        return undefined;
    }

    anchors.verticalCenter: {
        // Switch Resize Pos
        switch (resizePos) {
            case "left":
            case "right":       return parent.verticalCenter;
        }

        return undefined;
    }

    hoverEnabled: enabled

    visible: enabled

    property QtObject target: null

    property string resizePos: ""   // topLeft, top, topRigth, left, right, bottomLeft, bottom, bottomRight

    property int minWidth: 0
    property int minHeight: 0

    property int maxWidth: 8192
    property int maxHeight: 8192

    property int pressPosX: 0
    property int pressPosY: 0

    property int resizeDirectionWidth: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "left":
            case "bottomLeft":  return 1;

            case "topRight":
            case "right":
            case "bottomRight": return -1;

            case "top":
            case "bottom":
        }

        return 0;
    }

    property int resizeDirectionHeight: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "top":
            case "topRight":    return 1;

            case "bottomLeft":
            case "bottom":
            case "bottomRight": return -1;

            case "left":
            case "right":
        }

        return 0;
    }

    property int reposXDirection: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "left":
            case "bottomLeft":  return 1;
        }

        return 0;
    }

    property int reposYDirection: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "top":
            case "topRight":    return 1;
        }

        return 0;
    }

    preventStealing: true

    cursorShape: {
        // Switch Resize Pos
        switch (resizePos) {
            case "topLeft":
            case "bottomRight": return Qt.SizeFDiagCursor;

            case "top":
            case "bottom":      return Qt.SizeVerCursor;

            case "topRight":
            case "bottomLeft":  return Qt.SizeBDiagCursor;

            case "left":
            case "right":       return Qt.SizeHorCursor;
        }

        return Qt.SizeAllCursor;
    }

    onPressed: {
        //console.log("DResizeArea.onPressed");
        // Set Press Position
        pressPosX = mouse.x;
        pressPosY = mouse.y;
    }

    onPositionChanged: {
        // Check Pressed State
        if (pressed && target !== null && resizePos !== "") {
            console.log("#### DResizeArea.onPositionChanged");

            // Calculate Delta X
            var deltaX = pressPosX - mouse.x;
            // Calculate New Width
            var newWidth = target.width + deltaX * resizeDirectionWidth;
            // Calculate New Pos X
            var newPosX = target.x - deltaX * reposXDirection;

            // Check New Pos
            if (target.x !== newPosX && reposXDirection !== 0) {
                // Set Target Pos X
                target.x = newPosX;
            }

            // Check New Width
            if (target.width !== newWidth && newWidth > resizeAreaRoot.minWidth && newWidth < resizeAreaRoot.maxWidth) {
                // Set Target Width
                target.width = newWidth;
            }

            // Calculate Delta Y
            var deltaY = pressPosY - mouse.y;
            // Calculate New Height
            var newHeight = target.height + deltaY * resizeDirectionHeight;
            // Calculate New Pos Y
            var newPosY = target.y - deltaY * reposYDirection;

            // Check New Pos
            if (target.y !== newPosY && reposYDirection !== 0) {
                // Set Target Pos
                target.y = newPosY;
            }

            // Check New Height
            if (target.height !== newHeight && newHeight > resizeAreaRoot.minHeight && newHeight < resizeAreaRoot.maxHeight) {
                // Set Target Height
                target.height = newHeight;
            }
        }
    }

    DTracer { }
}
