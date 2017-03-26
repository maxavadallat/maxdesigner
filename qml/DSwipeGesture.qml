import QtQuick 2.0

import "style"

DMouseArea {
    id: swipeGestureRoot

    property bool enableSwipe: true

    property int swipeThreshold: 0

    property int swipeOnFinalPosX: 0

    property int swipeDirection: -1

    property bool swipeOn: false

    property int pressX: 0
    property int lastPosX: pressX
    property int swipePosX: swipeGestureRoot.swipeDirection < 0 ? swipeGestureRoot.width : 0
    property int swipeLastPosX: swipePosX

    property bool swipeWasOn: false

    property int velocity: 0

    property int deltaX: 0
    property int deltaTime: 0

    property int pressTime: 0

    property bool swiped: false

    property bool dragActive: false

    property int clickCounter: 0

    drag.filterChildren: true

    signal manualDoubleClick()

    onPressedChanged: {
        // Start Double Click Timer
        doubleClickTimer.running = true;

        // Ins Click Counter
        clickCounter++;

        //console.log("DSwipeGesture.onPressedChanged - pressed: " + pressed + " - clickCounter: " + clickCounter);
    }

    onPressed: {
        if (!enableSwipe) {
            return;
        }

        //console.log("DSwipeGesture.onPressed - mouse[" + mouse.x + ":" + mouse.y + "]");
        // Init/Reset Swipe
        resetSwipe(mouse);
    }

    onPositionChanged: {
        // Check If Swipe Enabled
        if (!enableSwipe) {
            return;
        }

        // Check If Pressed
        if (swipeGestureRoot.pressed) {
            //console.log("DSwipeGesture.onPositionChanged - mouse[" + mouse.x + ":" + mouse.y + "]");

            // Calculate Delta X
            swipeGestureRoot.deltaX = mouse.x - swipeGestureRoot.pressX;

            // Check Drag Active
            if (!swipeGestureRoot.dragActive) {
                // Set Drag Active
                swipeGestureRoot.dragActive = true;
            }

            // Check Last Pos X
            if (swipeGestureRoot.lastPosX !== mouse.x) {
                // Set Swiped State
                swipeGestureRoot.swiped = true;
                // Set Swipe PosX
                swipeGestureRoot.swipePosX = swipeGestureRoot.swipeDirection < 0 ? Math.max(swipeGestureRoot.swipeLastPosX + swipeGestureRoot.deltaX, swipeGestureRoot.swipeOnFinalPosX)
                                                                                 : Math.min(swipeGestureRoot.swipeLastPosX + swipeGestureRoot.deltaX, swipeGestureRoot.swipeOnFinalPosX);
                // Set Swipe On
                swipeGestureRoot.swipeOn = swipeGestureRoot.swipeDirection < 0 ? (swipeGestureRoot.swipePosX <= swipeGestureRoot.swipeThreshold)
                                                                               : (swipeGestureRoot.swipePosX >= swipeGestureRoot.swipeThreshold)
            }
        }
    }

    onCanceled: {
        //console.log("#### DSwipeGesture.onCanceled");
        // Reset Swipe Pos
        resetSwipePos();

        // Reset Drag Active
        //swipeGestureRoot.dragActive = false;
    }

    onReleased: {
        // Check If Swipe Enabled
        if (!enableSwipe) {
            return;
        }

        //console.log("DSwipeGesture.onReleased - mouse[" + mouse.x + ":" + mouse.y + "]");
        // Reset Swipe Pos
        resetSwipePos();

        // Reset Drag Active
        swipeGestureRoot.dragActive = false;
    }

    onClicked: {
        // Check If Swipe Enabled
        if (!enableSwipe) {
            return;
        }

        // Check Swiped State
        if (!swipeGestureRoot.swiped) {
            // Reset Swipe State
            swipeGestureRoot.swipeOn = false;
        }

        // Reset Swipe Pos
        resetSwipePos();
    }

    function resetSwipe(mouse) {
        // Reset Swiped
        swipeGestureRoot.swiped = false;
        // Set Press Point
        swipeGestureRoot.pressX = mouse.x;
        // Reset Last Pos
        swipeGestureRoot.lastPosX = swipeGestureRoot.pressX;
        // Reset Delta Time
        swipeGestureRoot.deltaTime = 0;
        // Reset Delta X
        swipeGestureRoot.deltaX = 0;
        // Set Swipe Was On
        swipeGestureRoot.swipeWasOn = swipeGestureRoot.swipeOn;

        // Reset Swipe Pos
        resetSwipePos();
    }

    // Reset Swipe Pos
    function resetSwipePos() {
        // Check Swipe Direction
        if (swipeGestureRoot.swipeDirection < 0) {
            // Check Swipe On
            if (swipeGestureRoot.swipeOn) {
                // Set Swipe Pos X
                swipeGestureRoot.swipePosX = swipeGestureRoot.swipeOnFinalPosX;
            } else {
                // Set Swipe Pos X
                swipeGestureRoot.swipePosX = swipeGestureRoot.width;
            }
        } else {
            // Check Swipe On
            if (swipeGestureRoot.swipeOn) {
                // Set Swipe Pos X
                swipeGestureRoot.swipePosX = swipeGestureRoot.swipeOnFinalPosX;
            } else {
                // Set Swipe Pos X
                swipeGestureRoot.swipePosX = 0;
            }
        }

        // Set Swipe Last Pos X
        swipeGestureRoot.swipeLastPosX = swipeGestureRoot.swipePosX;
    }

    Item {
        id: traceContainer
        anchors.fill: parent
        visible: settingsController.tracerVisible

        Rectangle {
            width: parent.width - swipeGestureRoot.swipeThreshold
            height: parent.height
            anchors.right: swipeGestureRoot.swipeDirection < 0 ? parent.right : undefined
            anchors.left: swipeGestureRoot.swipeDirection > 0 ? parent.left : undefined
            color: "transparent"
            border.color: DStyle.colorTrace
        }

        Rectangle {
            width: parent.width - swipeGestureRoot.swipeOnFinalPosX
            height: parent.height
            anchors.right: swipeGestureRoot.swipeDirection < 0 ? parent.right : undefined
            anchors.left: swipeGestureRoot.swipeDirection > 0 ? parent.left : undefined
            color: "transparent"
            border.color: DStyle.colorTrace
        }

        Rectangle {
            width: swipeGestureRoot.swipeDirection < 0 ? (swipeGestureRoot.width - swipeGestureRoot.swipePosX) : swipeGestureRoot.swipePosX
            height: parent.height * 0.5
            anchors.right: swipeGestureRoot.swipeDirection < 0 ? parent.right : undefined
            anchors.left: swipeGestureRoot.swipeDirection > 0 ? parent.left : undefined
            anchors.verticalCenter: parent.verticalCenter
            color: DStyle.colorTrace
        }
    }

    Timer {
        id: doubleClickTimer
        interval: 300

//        onRunningChanged: {
//            console.log("doubleClickTimer.running: " + running);
//        }

        onTriggered: {
            // Check Click Counter
            if (swipeGestureRoot.clickCounter >= 4) {
                //console.log("DSwipeGesture.doubleClickTimer.onTriggered - clickCounter: " + swipeGestureRoot.clickCounter);
                // Emit Manual Double CLick Signal
                swipeGestureRoot.manualDoubleClick();
            }

            // Reset Click Counter
            swipeGestureRoot.clickCounter = 0;
        }
    }
}
