import QtQuick 2.0

import "Constants.js" as CONSTS
import "style"

DContainer {
    id: paneBaseRoot

    width: creationWidth
    height: creationHeight

    property string title: ""

    property string hideToSide: ""  // "", "left", "right", "bottom"

    readonly property string hideToLeft: "left"
    readonly property string hideToRight: "right"
    readonly property string hideToBottom: "bottom"

    readonly property string stateCreate: "create"
    readonly property string stateShown: "shown"
    readonly property string stateHidden: "hidden"
    readonly property string stateClosed: "closed"

    property bool dragActive: false

    property int lastShownX: 0
    property int lastShownY: 0

    property int initialX: 0
    property int initialY: 0

    property int creationX: 0
    property int creationY: 0

    property int creationWidth: 0
    property int creationHeight: 0

    property int parentWidth: 0
    property int parentHeight: 0

    property int resetWidth: 0

    property bool transitioning: false

    property int hiddenX: {
        switch (hideToSide) {
            case hideToLeft:    return -paneBaseRoot.width;
            case hideToRight:   return paneBaseRoot.parent ? paneBaseRoot.parent.width : paneBaseRoot.x;
        }

        return paneBaseRoot.x;
    }

    property int hiddenY: {
        switch (hideToSide) {
            case hideToBottom:  return paneBaseRoot.parent ? paneBaseRoot.parent.height : paneBaseRoot.y;
        }

        return paneBaseRoot.y;
    }

    readonly property int animDuration: 500

    property alias paneContainer: contentContainer
    default property alias paneContainerChildren: contentContainer.children


    property alias enablePaneContent: contentContainer.enabled

    property alias titleLabel: titleTextLabel

    property bool showBackground: true

    property bool showTitle: true

    property alias topMouseAreaVisible: topMouseArea.visible

    enableSizeOverlay: false
    enablePosOverlay: false

    clipContent: false

    property Connections parentConnections: Connections {
        target: parent

        onWidthChanged: {

            // ...
        }

        onHeightChanged: {

            // ...
        }
    }

    onXChanged: {
//        if (transitioning)
//            return;

        // Check State
        if (paneBaseRoot.state === paneBaseRoot.stateShown) {
            //console.log("DPaneBase.onXChanged - x: " + x);

            if (paneBaseRoot.dragActive) {
                //console.log("DPaneBase.onXChanged - x: " + x);

                // Adjust Las Shown X
                paneBaseRoot.lastShownX = paneBaseRoot.x;
            }
        }
    }

    onYChanged: {
//        if (transitioning)
//            return;

        // Check State
        if (paneBaseRoot.state === paneBaseRoot.stateShown) {

            //console.log("DPaneBase.onYChanged - y: " + y);

            if (paneBaseRoot.dragActive) {
                //console.log("DPaneBase.onYChanged - y: " + y);

                // Adjust Las Shown Y
                paneBaseRoot.lastShownY = paneBaseRoot.y;
            }
        }
    }

    onWidthChanged: {
        // Check State
        if (paneBaseRoot.state === paneBaseRoot.stateShown) {
            // Update Creation Width
            paneBaseRoot.creationWidth = paneBaseRoot.width;
        }
    }

    onHeightChanged: {
        // Check State
        if (paneBaseRoot.state === paneBaseRoot.stateShown) {
            // Update Creation Height
            paneBaseRoot.creationHeight = paneBaseRoot.height;
        }
    }

    onPressed: {
        //console.log("DPaneBase.onPressed");
        // Set Drag Target - ASSUMING Parent is MainGrabArea
        parent.setDragTarget(paneBaseRoot);
    }

    onReleased: {
        //console.log("DPaneBase.onReleased");
        // Clear Drag Target - ASSUMING Parent is MainGrabArea
        //parent.clearDragTarget();
    }

    onResizePressed: {
        paneBaseRoot.parent.setDragTarget(paneBaseRoot);
    }

    // Reset To Create State
    function reset() {
        // Check Hide To Sie
        if (paneBaseRoot.hideToSide === paneBaseRoot.hideToLeft || paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom) {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.x + paneBaseRoot.width - paneBaseRoot.initialX;
        } else {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.initialX - paneBaseRoot.x;
        }

        //console.log("DPaneBase.reset - resetWidth: " + resetWidth);

        // Set State
        paneBaseRoot.state = stateCreate;
    }

    // Show
    function show() {
        // Set State
        paneBaseRoot.state = stateShown;
    }

    // Hide
    function hide() {
        // Set State
        paneBaseRoot.state = stateHidden;
    }

    function close() {
        // Set State
        paneBaseRoot.state = stateClosed;
    }

    // Content Container
    Item {
        id: contentContainer
        anchors.fill: parent
    }

    MouseArea {
        id: topMouseArea
        anchors.fill: parent

        visible: paneBaseRoot.focus

        onPressed: {
            //console.log("DPaneBase.topMouseArea.onPressed");
            // Set Drag Target - ASSUMING Parent is MainGrabArea
            paneBaseRoot.parent.setDragTarget(paneBaseRoot);
            mouse.accepted = false;
        }

        onReleased: {
            //console.log("DPaneBase.topMouseArea.onReleased");
            // Set Drag Target - ASSUMING Parent is MainGrabArea
            paneBaseRoot.parent.clearDragTarget();
            mouse.accepted = false;
        }
    }

    // Title
    DText {
        id: titleTextLabel
        anchors.left: parent.left
        anchors.leftMargin: Style.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: Style.defaultMargin
        text: paneBaseRoot.title
        Behavior on opacity { DFadeAnimation { } }
        opacity: 0.0
        visible: paneBaseRoot.showTitle && opacity > 0.0
    }

    // Hide Indicator
    DControl {
        id: hideShowButton

        parent: paneBaseRoot

        width: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? CONSTS.defaultPaneHideButtonHeight : CONSTS.defaultPaneHideButtonWidth
        height: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? CONSTS.defaultPaneHideButtonWidth : CONSTS.defaultPaneHideButtonHeight

        anchors.left: paneBaseRoot.hideToSide === paneBaseRoot.hideToLeft ? parent.right : undefined
        anchors.right: paneBaseRoot.hideToSide === paneBaseRoot.hideToRight ? parent.left : undefined
        anchors.bottom: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.top : undefined

        anchors.horizontalCenter: {
            if (paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom) {
                return parent.horizontalCenter;
            }

            return undefined;
        }

        anchors.verticalCenter: {
            switch (paneBaseRoot.hideToSide) {
                case paneBaseRoot.hideToLeft:
                case paneBaseRoot.hideToRight:  return parent.verticalCenter;
            }

            return undefined;
        }

        Behavior on opacity { DFadeAnimation { } }
        opacity: 0.0
        visible: paneBaseRoot.hideToSide !== "" && opacity > 0.0

        DText {
            id: hideButtonText
//            width: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.width : parent.height
//            height: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.height : parent.width
            anchors.centerIn: parent
            rotation: {
                switch (paneBaseRoot.hideToSide) {
                    case paneBaseRoot.hideToLeft:   return -90;
                    case paneBaseRoot.hideToRight:  return 90;
                }

                return 0;
            }

            text: "•••"

            horizontalAlignment: Text.AlignHCenter
            color: buttonMouseArea.pressed ? Style.colorBorder : Style.colorFontDark
        }

        DMouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: {
                // Check State
                if (paneBaseRoot.state !== stateHidden) {
                    // Set State
                    paneBaseRoot.hide();
                } else {
                    // Set State
                    paneBaseRoot.show();
                }
            }
        }
    }

    Item {
        id: dummy
        visible: false
    }

    states: [
        State {
            name: ""
        },

        State {
            name: stateCreate

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.initialX; y: paneBaseRoot.initialY; width: 0; height: 0 }
            PropertyChanges { target: titleTextLabel; opacity: 0.0 }
            PropertyChanges { target: hideShowButton; opacity: 0.0 }
        },

        State {
            name: stateShown

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.lastShownX; y: paneBaseRoot.lastShownY }
            PropertyChanges { target: paneBaseRoot; width: paneBaseRoot.creationWidth; height: paneBaseRoot.creationHeight }
            PropertyChanges { target: titleTextLabel; opacity: 1.0 }
            PropertyChanges { target: hideShowButton; opacity: 1.0 }
        },

        State {
            name: stateHidden

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.hiddenX; y: paneBaseRoot.hiddenY }
            PropertyChanges { target: paneBaseRoot; width: paneBaseRoot.creationWidth; height: paneBaseRoot.creationHeight }
            PropertyChanges { target: titleTextLabel; opacity: 1.0 }
            PropertyChanges { target: hideShowButton; opacity: 1.0 }
        },

        State {
            name: stateClosed

            PropertyChanges { target: paneBaseRoot; width: 0; height: 0 }
            PropertyChanges { target: titleTextLabel; opacity: 0.0 }
            PropertyChanges { target: hideShowButton; opacity: 0.0 }
        }
    ]

    transitions: [
        Transition {
            //from: ""
            to: stateCreate

            SequentialAnimation {
                ParallelAnimation {
                    PropertyAction { target: paneBaseRoot; properties: "width, height"; value: 0 }
                    PropertyAction { target: paneBaseRoot; property: "x"; value: paneBaseRoot.initialX }
                    PropertyAction { target: paneBaseRoot; property: "y"; value: paneBaseRoot.initialY }
                    DFadeAnimation { target: titleTextLabel; to: 0.0 }
                    DFadeAnimation { target: hideShowButton; to: 0.0 }
                }
            }
        },

        Transition {
            from: stateCreate
            to: stateShown

            SequentialAnimation {

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: true }

                PauseAnimation { duration: 200 }

                PropertyAction { target: paneBaseRoot; property: "focus"; value: true }

                PropertyAction { target: paneBaseRoot; property: "height"; value: 1 }
                PropertyAction { target: paneBaseRoot; property: "x"; value: paneBaseRoot.initialX }
                PropertyAction { target: paneBaseRoot; property: "y"; value: paneBaseRoot.initialY }

                ParallelAnimation {
                    DAnimation { target: hideToSide === hideToLeft ? paneBaseRoot : dummy; property: "width"; to: paneBaseRoot.creationX + paneBaseRoot.creationWidth }

                    DAnimation { target: hideToSide === hideToRight ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.creationX }
                    DAnimation { target: hideToSide === hideToRight ? paneBaseRoot : dummy; property: "width"; to: paneBaseRoot.parentWidth - paneBaseRoot.creationX }

                    DAnimation { target: hideToSide === hideToBottom ? paneBaseRoot : dummy; property: "width"; to: paneBaseRoot.creationX + paneBaseRoot.creationWidth - paneBaseRoot.initialX }
                }

                ParallelAnimation {
                    DAnimation { target: paneBaseRoot; property: "width"; to: paneBaseRoot.creationWidth }
                    DAnimation { target: paneBaseRoot; property: "x"; to: paneBaseRoot.creationX }
                }

                ParallelAnimation {
                    DAnimation { target: paneBaseRoot; property: "y"; to: paneBaseRoot.creationY }
                    DAnimation { target: paneBaseRoot; property: "height"; to: paneBaseRoot.creationHeight }
                }

                PropertyAction { target: titleTextLabel; property: "opacity"; value: 1.0 }
                PropertyAction { target: hideShowButton; property: "opacity"; value: 1.0 }

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: false }
            }
        },

        Transition {
            from: stateShown
            to: stateCreate

            SequentialAnimation {

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: true }

                PropertyAction { target: titleTextLabel; property: "opacity"; value: 0.0 }
                PropertyAction { target: hideShowButton; property: "opacity"; value: 0.0 }

                ParallelAnimation {
                    DAnimation { target: paneBaseRoot; property: "y"; to: paneBaseRoot.y + paneBaseRoot.height / 2 }
                    DAnimation { target: paneBaseRoot; property: "height"; to: 1 }
                }

                ParallelAnimation {
                    DAnimation { target: paneBaseRoot; property: "width"; to: paneBaseRoot.resetWidth }
                    DAnimation { target: hideToSide === hideToLeft ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.initialX }
                    DAnimation { target: hideToSide === hideToBottom ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.initialX }
                }

                ParallelAnimation {
                    DAnimation { target: paneBaseRoot; property: "width"; to: 0 }
                    DAnimation { target: paneBaseRoot; property: "x"; to: paneBaseRoot.initialX }
                }

                PropertyAction { target: paneBaseRoot; property: "height"; value: 0 }

                // ...

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: false }
            }
        },

        Transition {
            from: stateHidden
            to: stateShown

            SequentialAnimation {
                ScriptAction {
                    script: {
                        // Set Drag Target
                        paneBaseRoot.parent.setDragTarget(paneBaseRoot);
                        // Clear Drag Target
                        paneBaseRoot.parent.clearDragTarget();
                        // Set Hide Button Text
                        hideButtonText.text = "•••";
                    }
                }

                PropertyAnimation { target: paneBaseRoot; properties: "x, y"; easing.type: Easing.InOutBack; duration: paneBaseRoot.animDuration }
            }
        },

        Transition {
            //from: stateShown
            to: stateHidden

            SequentialAnimation {
                PropertyAnimation { target: paneBaseRoot; properties: "x, y"; easing.type: Easing.InOutBack; duration: paneBaseRoot.animDuration }

                ScriptAction {
                    script: {
                        // Set Hide Button Text
                        hideButtonText.text = paneBaseRoot.title;
                    }
                }
            }
        },

        Transition {
            to: stateClosed

            SequentialAnimation {

            }
        }
    ]
}
