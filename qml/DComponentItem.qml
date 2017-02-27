import QtQuick 2.0

import enginecomponents 0.1

import "Style.js" as STYLE
import "Constants.js" as CONSTS

Item {
    id: componentItemRoot

    width: CONSTS.componentItemWidth
    height: CONSTS.componentItemHeight

    property alias title: componentTitleLabel.text

    property QtObject componentInfo: null

    DRectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: STYLE.colorBorderNoFocus
        opacity: dragContainer.grabbed ? 0.5 : 0.0
    }

    DMouseArea {
        id: dragContainer
        width: componentItemRoot.width
        height: componentItemRoot.height

        property bool grabbed: false

        drag.target: grabbed ? dragContainer : undefined

        //preventStealing: grabbed

        Drag.active: grabbed
        Drag.hotSpot.x: hotSpotX
        Drag.hotSpot.y: hotSpotY
        Drag.source: componentItemRoot.componentInfo

        property int hotSpotX: 0
        property int hotSpotY: 0

        property int scaleDuration: 500

        onGrabbedChanged: {
            //console.log("DComponentItem.dragContainer.onGrabbedChanged - grabbed: " + grabbed);
        }

        onPressed: {
//            // Set Grabbed
//            dragContainer.grabbed = true;
//            // Set Hot Spot
//            dragContainer.hotSpotX = mouse.x;
//            dragContainer.hotSpotY = mouse.y;

            // Set Activity Indicator Running State
            loadingIndicator.running = true;
        }

        onPressAndHold: {
            // Set Activity Indicator Running State
            loadingIndicator.running = false;

            // Set Grabbed
            dragContainer.grabbed = true;
            // Set Hot Spot
            dragContainer.hotSpotX = mouse.x;
            dragContainer.hotSpotY = mouse.y;
        }

        onReleased: {
            // Set Activity Indicator Running State
            loadingIndicator.running = false;
            // Reset Grabbed
            dragContainer.grabbed = false;
        }

        onCanceled: {
            // Set Activity Indicator Running State
            loadingIndicator.running = false;
            // Reset Grabbed
            dragContainer.grabbed = false;
        }

        DRectangle {
            id: dragContainerBG
            anchors.fill: parent
            border.color: dragContainer.pressed ? STYLE.colorBorder : STYLE.colorBorderNoFocus
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
            anchors.centerIn: parent
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
                when: !dragContainer.grabbed

                //PropertyChanges { target: dragContainer; scale: 1.0 }
            },

            State {
                name: "grabbed"
                when: dragContainer.grabbed

                PropertyChanges { target: dragContainer; scale: 1.2 }
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
                        DAnimation { target: dragContainer; properties: "x, y"; to: 0 }
                        DAnimation { target: dragContainer; property: "width"; to: componentItemRoot.width }
                        DAnimation { target: dragContainer; property: "height"; to: componentItemRoot.height }
                    }
                }
            },

            Transition {
                to: "grabbed"
                SequentialAnimation {
                    DAnimation { target: dragContainer; property: "scale"; duration: dragContainer.scaleDuration; easing.type: Easing.OutElastic }
                }
            }
        ]
    }
}
