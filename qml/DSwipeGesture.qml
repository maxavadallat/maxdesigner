import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: swipeGestureRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property bool enableSwipe: true

    property bool swipeOn: (actionButtonContainer.x === actionButtonContainer.swipeMinX)

    property string actionButtonText: "Delete"
    property string actionButtonColor: DStyle.colorCancel
    property string actionButtonHiglightColor: DStyle.colorCancelHighLight

    clip: true

    signal actionButtonClicked()

    onSwipeOnChanged: {
        if (swipeOn) {
            focus = true;
        }
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Escape) {
            hideSwipe();
        }
    }

    // Hide Swipe
    function hideSwipe() {
        // Start Hide Swipe Animation
        hideSwipeAnimation.start();
    }

    // Hide Swipe Area
    DMouseArea {
        anchors.fill: parent
        visible: swipeOn
        onClicked: {
            hideSwipe();
        }
    }

    // Content Fade Curtain
    Rectangle {
        id: contentfade
        anchors.fill: parent
        color: "#AA000000"
        opacity: (actionButtonContainer.swipeMaxX - actionButtonContainer.x) / actionButtonContainer.swipeRange
        visible: opacity > 0.0
    }

    // Action Button Area
    DMouseArea {
        id: actionButtonContainer

        x: parent.width - 16

        width: CONSTS.defaultButtonWidth + 64
        height: parent.height

        readonly property int swipeMinX: swipeGestureRoot.width - actionButtonContainer.width
        readonly property int swipeMaxX: swipeGestureRoot.width - CONSTS.defaultSwipeAreaWidth
        readonly property int swipeRange: swipeMaxX - swipeMinX

        property real minimumVelocity: 200//1000

        property int lastX: 0
        property real lastTime: 0
        property int velocity: 0

        preventStealing: !swipeGestureRoot.swipeOn

        drag.target: actionButtonContainer
        drag.axis: Drag.XAxis
        drag.minimumX: swipeMinX
        drag.maximumX: swipeMaxX
        drag.threshold: 0

        drag.filterChildren: true

        onClicked: {
            hideSwipe();
        }

        onPressed:  {
            // Stop Easing Animation
            easingAnimation.stop();
            // Set Last X
            lastX = actionButtonContainer.x;
            // Set Last Time
            lastTime = new Date().valueOf();
        }

        onReleased: {
            // Get New Time
            var now = new Date().valueOf();
            // Calculate Time Delta
            var timeDelta = now - lastTime;
            // Calculate Pos Delta
            var posDelta = lastX - actionButtonContainer.x;

            // Check Time Delta
            if (timeDelta > 0) {
                // Calculate Velocity
                velocity = Math.round((1000 * posDelta) / timeDelta);
            }

            // Ease Content Pos
            easeContentPos();
        }

        // Ease Content Pos
        function easeContentPos() {
            // Set Easing Curve Start
            easingAnimation.from = actionButtonContainer.x
            // Init New End Pos
            var newEndPos = 0;

            // Check Velocity
            if (velocity > minimumVelocity) {
                // Set New End Pos
                newEndPos = swipeMinX;
                // Set Easing Type
                easingAnimation.easing.type = Easing.OutBack;
            } else if (velocity < -minimumVelocity) {
                // Set New End Pos
                newEndPos = swipeMaxX;
                // Set Easing Type
                easingAnimation.easing.type = Easing.InBack;
            } else {
                // Check Position
                if (actionButtonContainer.x > swipeMinX + swipeRange * 0.5) {
                    // Set New End Pos
                    newEndPos = swipeMaxX;
                    // Set Easing Type
                    easingAnimation.easing.type = Easing.InBack;
                } else {
                    // Set New End Pos
                    newEndPos = swipeMinX;
                    // Set Easing Type
                    easingAnimation.easing.type = Easing.OutBack;
                }
            }

            // Set Easing Curve End Position
            easingAnimation.to = newEndPos;
            // Start Easing
            easingAnimation.start();
        }

        MouseArea {
            anchors.fill: parent
        }

        DButton {
            id: actionButton
            anchors.right: parent.right
            anchors.rightMargin: DStyle.defaultMargin * 2
            anchors.verticalCenter: parent.verticalCenter
            bgColor: actionButtonColor
            highlightColor: actionButtonHiglightColor
            text: actionButtonText
            onClicked: {
                //console.log("DSwipeGesture.actionButton.onClicked");
                swipeGestureRoot.actionButtonClicked();
            }
        }

        NumberAnimation on x {
            id: hideSwipeAnimation
            to: actionButtonContainer.swipeMaxX
            duration: DStyle.animDuration
            easing.type: Easing.OutBack
        }

        NumberAnimation on x {
            id: easingAnimation
            to: {
                // Check Position
                if (actionButtonContainer.x > actionButtonContainer.swipeMinX + actionButtonContainer.swipeRange * 0.5) {
                    return actionButtonContainer.swipeMaxX;
                }

                return actionButtonContainer.swipeMinX;
            }
            duration: DStyle.animDuration
            easing.type: Easing.OutBack
        }
    }
}
