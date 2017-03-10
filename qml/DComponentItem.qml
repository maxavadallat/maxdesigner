import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "Constants.js" as CONSTS

Item {
    id: componentItemRoot

    width: CONSTS.componentItemWidth
    height: CONSTS.componentItemHeight

    property alias title: componentTitleLabel.text

    property QtObject componentInfo: null

    property bool grabbed: false

    onGrabbedChanged: {
        //console.log("componentItemRoot.onGrabbedChanged - grabbed: " + grabbed);

        // Position Item For Grabbed State
        dragContainer.x = mapToItem(mainGrabArea, dragContainer.hotSpotX, dragContainer.hotSpotY).x - dragContainer.hotSpotX;
        dragContainer.y = mapToItem(mainGrabArea, dragContainer.hotSpotX, dragContainer.hotSpotY).y - dragContainer.hotSpotY;

        // Set Parent For Grabbed State
        dragContainer.parent = grabbed ? mainGrabArea : componentItemRoot
    }

    DRectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: Style.colorBorderNoFocus
        opacity: componentItemRoot.grabbed ? 0.5 : 0.0
    }

    DMouseArea {
        id: dragContainer
        width: componentItemRoot.width
        height: componentItemRoot.height

        drag.target: componentItemRoot.grabbed ? dragContainer : undefined

        Drag.active: componentItemRoot.grabbed

        Drag.hotSpot.x: hotSpotX  //((hotSpotX / scale - width / 2) * scale + width / 2 * scale) + (4 * scale)
        Drag.hotSpot.y: hotSpotY / scale //((hotSpotY / scale - height / 2) * scale + height / 2 * scale) / scale

        Drag.source: componentItemRoot.componentInfo
        Drag.keys: [ CONSTS.newComponentDragKey ]

        cursorShape: componentItemRoot.grabbed ? Qt.ClosedHandCursor : Qt.PointingHandCursor

        property int hotSpotX: 0
        property int hotSpotY: 0

        property int scaleDuration: 500

        onPressed: {
            // Start Loading Delay Timer
            loadingDelayTimer.restart();
            // Set Focus
            dragContainer.focus = true;
        }

        onPressAndHold: {
            // Set Activity Indicator Running State
            loadingIndicator.running = false;
            // Reset Loading Delay Timer Running State
            loadingDelayTimer.running = false;

            // Set Grabbed
            componentItemRoot.grabbed = true;

            // Set Hot Spot
            dragContainer.hotSpotX = mouse.x * scale;
            dragContainer.hotSpotY = mouse.y * scale;
        }

        onReleased: {
            // Check Grabbed State
            if (componentItemRoot.grabbed) {
                // Drop Item
                Drag.drop();
                // Reset Grabbed
                componentItemRoot.grabbed = false;
            }

            // Reset Loading Delay Timer Running State
            loadingDelayTimer.running = false;
            // Set Activity Indicator Running State
            loadingIndicator.running = false;
        }

        onCanceled: {
            // Reset Loading Delay Timer Running State
            loadingDelayTimer.running = false;
            // Set Activity Indicator Running State
            loadingIndicator.running = false;
            // Reset Grabbed
            componentItemRoot.grabbed = false;
        }

        onDoubleClicked: {
            // Reset Loading Delay Timer Running State
            loadingDelayTimer.running = false;
            // Set Activity Indicator Running State
            loadingIndicator.running = false;

            // Open Component
            openFilesModel.openComponent(componentItemRoot.componentInfo);
        }

        Timer {
            id: loadingDelayTimer
            interval: 400
            repeat: false
            onTriggered: {
                // Set Activity Indicator Running State
                loadingIndicator.running = true;
            }
        }

        DRectangle {
            id: dragContainerBG
            anchors.fill: parent
            border.color: dragContainer.focus ? Style.colorBorder : Style.colorBorderNoFocus
        }

        Loader {
            id: componentLoader
            anchors.centerIn: parent
            asynchronous: true
            active: false
            source: ""
        }

        DText {
            id: componentTitleLabel
            width: parent.width
            anchors.centerIn: parent
            font.pixelSize: Style.fontSizeS
            horizontalAlignment: Text.AlignHCenter
            text: "ComponentItem"
        }

        DActivityIndicator {
            id: loadingIndicator
            anchors.fill: parent
            running: false
        }

        states: [
            State {
                name: ""
                when: !componentItemRoot.grabbed

                //PropertyChanges { target: dragContainer; scale: 1.0 }
            },

            State {
                name: "grabbed"
                when: componentItemRoot.grabbed

                PropertyChanges { target: dragContainer; scale: 1.2; z: 0.1 }
            }
        ]

        transitions: [
            Transition {
                from: "grabbed"
                to: ""
                SequentialAnimation {
                    PropertyAction { target: dragContainer; property: "scale"; value: 1.0 }
                    PropertyAction { target: dragContainer; property: "opacity"; value: 0.0 }
                    PropertyAction { target: dragContainer; properties: "x"; value: componentItemRoot.width / 2 }
                    PropertyAction { target: dragContainer; properties: "y"; value: componentItemRoot.height / 2 }
                    PropertyAction { target: dragContainer; properties: "width, height"; value: 0 }
                    ParallelAnimation {
                        DAnimation { target: dragContainer; property: "opacity"; to: 1.0 }
                        DAnimation { target: dragContainer; properties: "x, y, z"; to: 0 }
                        DAnimation { target: dragContainer; property: "width"; to: componentItemRoot.width }
                        DAnimation { target: dragContainer; property: "height"; to: componentItemRoot.height }
                    }
                }
            },

            Transition {
                to: "grabbed"
                SequentialAnimation {
                    PropertyAction { target: dragContainer; property: "z" }
                    DAnimation { target: dragContainer; property: "scale"; duration: dragContainer.scaleDuration; easing.type: Easing.OutElastic }
                }
            }
        ]
    }
}
