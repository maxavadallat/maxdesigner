import QtQuick 2.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DContainer {
    id: paneBaseRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    property string title: ""

    property string hideToSide: ""  // "", "left", "right", "bottom"

    readonly property string hideToLeft: "left"
    readonly property string hideToRight: "right"
    readonly property string hideToBottom: "bottom"

    readonly property string stateCreate: "create"
    readonly property string stateShown: "shown"
    readonly property string stateHidden: "hidden"
    readonly property string stateClosed: "closed"

    property int lastShownX: 0
    property int lastShownY: 0

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
            //console.log("DPane.Connections.onWidthChanged - parent.width: " + parent.width);

            // Check State
            if (paneBaseRoot.state === paneBaseRoot.stateHidden) {

            } else {
                // Check X Position
                if (parent.width > 0 && (paneBaseRoot.x + paneBaseRoot.width + STYLE.defaultMargin) > parent.width) {
                    // Adjust X Pos To Stay Visible
                    paneBaseRoot.x = parent.width - (paneBaseRoot.width + STYLE.defaultMargin);
                }
            }

            // ...
        }

        onHeightChanged: {
            //console.log("DPane.Connections.onHeightChanged - parent.height: " + parent.height);

            // Check Y Position
            if (parent.height > 0 && (paneBaseRoot.y + paneBaseRoot.height + STYLE.defaultMargin) > parent.height) {
                // Adjust Y Pos To Stay Visible
                paneBaseRoot.y = parent.height - (paneBaseRoot.height + STYLE.defaultMargin);
            }

            // ...
        }
    }

    onXChanged: {
        if (paneBaseRoot.state !== stateHidden) {
            paneBaseRoot.lastShownX = paneBaseRoot.x;
        }
    }

    onYChanged: {
        if (paneBaseRoot.state !== stateHidden) {
            paneBaseRoot.lastShownY = paneBaseRoot.y;
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

        // ...
    }

    // Background
    DRectangle {
        id: paneBG
        anchors.fill: parent
        visible: paneBaseRoot.showBackground
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

//        Rectangle {
//            anchors.fill: parent
//            color: "#22FF0000"
//        }
    }

    // Title
    DText {
        id: titleTextLabel
        anchors.left: parent.left
        anchors.leftMargin: STYLE.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: STYLE.defaultMargin
        text: paneBaseRoot.title
        visible: paneBaseRoot.showTitle
    }

    // Hide Indicator
    Item {
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

        visible: paneBaseRoot.hideToSide !== ""

        DText {
            id: hideButtonText
            width: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.width : parent.height
            height: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.height : parent.width
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
            color: buttonMouseArea.pressed ? STYLE.colorBorder : STYLE.colorFontDark
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

    states: [
        State {
            name: stateCreate

            PropertyChanges { target: paneBaseRoot; width: 0; height: 0 }
        },

        State {
            name: stateShown

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.lastShownX; y: paneBaseRoot.lastShownY }
        },

        State {
            name: stateHidden

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.hiddenX; y: paneBaseRoot.hiddenY }
        },

        State {
            name: stateClosed

            PropertyChanges { target: paneBaseRoot; width: 0; height: 0 }
        }
    ]

    transitions: [
        Transition {
            from: stateCreate
            to: stateShown

            SequentialAnimation {

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

        }
    ]
}
