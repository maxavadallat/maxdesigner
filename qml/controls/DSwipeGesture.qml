import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/animations"

Item {
    id: swipeGestureRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property bool enableSwipe: true

    property bool swipeOn: (actionButtonContainer.x === swipeGestureRoot.swipeMinX)

    property int swipeMinX: swipeGestureRoot.width - actionButtonContainer.width
    property int swipeMaxX: swipeGestureRoot.width - CONSTS.defaultSwipeAreaWidth
    property int swipeRange: swipeGestureRoot.swipeMaxX - swipeGestureRoot.swipeMinX

    property string actionButtonText: "Delete"
    property string actionButtonColor: DStyle.colorCancel
    property string actionButtonHiglightColor: DStyle.colorCancelHighLight

    readonly property int handleWidth: 16

    property bool swipeActive: false

    clip: true

    signal swipeStarted()
    signal swipeFinished()
    signal actionButtonClicked()

    onWidthChanged: {
        // Set Action Button Container Position
        actionButtonContainer.x = swipeGestureRoot.width - 16;
    }

    onSwipeOnChanged: {
        // Check Swipe On
        if (swipeOn) {
            // Set Focus
            focus = true;
        }
    }

    Keys.onReleased: {
        // Check Key Event
        if (event.key === Qt.Key_Escape) {
            // Hide Swipe
            hideSwipe();
        }
    }

    // Hide Swipe
    function hideSwipe() {
        // Start Hide Swipe Animation
        hideSwipeAnimation.start();
    }

    // System Model Connection
    Connections {
        target: DSystemModel

        onCancelMarkForDeletion: {
            // Hide Swipe
            hideSwipe();
        }
    }

    // Hide Swipe Area
    DMouseArea {
        anchors.fill: parent
        visible: swipeOn

        onClicked: {
            // Hide Swipe
            hideSwipe();
        }
    }

    // Content Fade Curtain
    Rectangle {
        id: contentfade
        anchors.fill: parent
        color: "#AA000000"
        opacity: (swipeGestureRoot.swipeMaxX - actionButtonContainer.x) / swipeGestureRoot.swipeRange
        visible: opacity > 0.0
    }

    // Action Button Area
    DMouseArea {
        id: actionButtonContainer

        width: CONSTS.defaultButtonWidth + 64
        height: parent.height

        anchors.right: parent.right
        anchors.rightMargin: swipeGestureRoot.handleWidth - width

        property real minimumVelocity: 200//1000

        property int lastX: 0
        property real lastTime: 0
        property int velocity: 0

        visible: swipeGestureRoot.enableSwipe

        preventStealing: !swipeGestureRoot.swipeOn

        drag.target: actionButtonContainer
        drag.axis: Drag.XAxis
        drag.minimumX: swipeMinX
        drag.maximumX: swipeMaxX
        drag.threshold: 0

        drag.filterChildren: true

        onXChanged: {
            // Check If Swipe Active
            if (pressed && !swipeGestureRoot.swipeActive) {
                // Set Swipe Active
                swipeGestureRoot.swipeActive = true;
                // Emit Swipe Started Signal
                swipeGestureRoot.swipeStarted();
            }
        }

        onClicked: {
            hideSwipe();
        }

        onPressed:  {
            // Reset Right Anchoring
            actionButtonContainer.anchors.right = undefined;
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
            easingAnimation.to = Math.round(newEndPos);
            // Start Easing
            easingAnimation.start();
        }

        MouseArea {
            anchors.fill: parent
        }

        DText {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            opacity: actionButtonContainer.x < swipeGestureRoot.swipeMaxX ? 0.0 : 0.5
            Behavior on opacity { DFadeAnimation { } }
            rotation: 90
            text: "---"
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
            to: swipeGestureRoot.swipeMaxX
            duration: DStyle.animDuration
            easing.type: Easing.OutBack

            onStopped: {
                // reset Swipe Active
                swipeGestureRoot.swipeActive = false;
                // Emit Swipe Finshed
                swipeGestureRoot.swipeFinished();
            }
        }

        NumberAnimation on x {
            id: easingAnimation
            to: {
                // Check Position
                if (actionButtonContainer.x > swipeGestureRoot.swipeMinX + swipeGestureRoot.swipeRange * 0.5) {
                    return swipeGestureRoot.swipeMaxX;
                }

                return swipeGestureRoot.swipeMinX;
            }
            duration: DStyle.animDuration
            easing.type: Easing.OutBack

            onStopped: {
                // reset Swipe Active
                swipeGestureRoot.swipeActive = false;
                // Emit Swipe Finshed
                swipeGestureRoot.swipeFinished();
            }
        }
    }
}
