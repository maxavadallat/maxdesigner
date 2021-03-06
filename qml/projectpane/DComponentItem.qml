import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: componentItemRoot

    width: CONSTS.componentItemWidth
    height: CONSTS.componentItemHeight

    property string title: "Component"
    property bool builtIn: false
    property bool visual: true
    property bool dirty: false

    property ComponentInfo componentInfo: null

    property bool grabbed: false

    onGrabbedChanged: {
        //console.log("componentItemRoot.onGrabbedChanged - grabbed: " + grabbed);

        // Check Grabbed
        if (grabbed) {
            // Start Drag
            Drag.start();
        } else {
            // Drop Drag
            Drag.drop();
        }

        // Position Item For Grabbed State
        dragContainer.x = mapToItem(mainGrabArea, dragContainer.hotSpotX, dragContainer.hotSpotY).x - dragContainer.hotSpotX;
        dragContainer.y = mapToItem(mainGrabArea, dragContainer.hotSpotX, dragContainer.hotSpotY).y - dragContainer.hotSpotY;

        // Set Parent For Grabbed State
        dragContainer.parent = grabbed ? mainGrabArea : componentItemRoot
    }

    DRectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: DStyle.colorBorderNoFocus
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

            color: {
                // Check Component Info
                if (componentItemRoot.componentInfo !== null && componentItemRoot.componentInfo.builtIn) {
                    return DStyle.colorComponentBuiltIn;
                }

                // TODO: Add Colors for different Component Types

                return "transparent";
            }

            border.color: dragContainer.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus
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
            width: parent.width - DStyle.defaultMargin
            anchors.centerIn: parent
            //font.pixelSize: DStyle.fontSizeXS
            fontSizeMode: Text.HorizontalFit
            minimumPixelSize: DStyle.fontSizeXS
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
            clip: true
            text: componentItemRoot.title
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

    // Dirty Indicator
    Rectangle {
        width: 4
        height: 4
        z: 0.1
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        radius: width * 0.5
        color: DStyle.colorBorder
        visible: componentItemRoot.dirty
    }
}
