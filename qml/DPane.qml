import QtQuick 2.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DContainer {
    id: paneRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    //Behavior on height { NumberAnimation { duration: STYLE.animDuration } }

    property string title: ""

    property string hideToSide: ""  // "", "left", "right"

    readonly property string hideToLeft: "left"
    readonly property string hideToRight: "right"

    readonly property int contentWidth: paneContent.width

    property int lastShownXOffs: 0

    readonly property string stateShown: "shown"
    readonly property string stateHidden: "hidden"

    readonly property int animDuration: 500

    //default property alias paneContainer: paneContainerColumn.children
    default property alias paneContainer: paneContent.contentContainer

    property alias enablePaneContent: paneContent.enabled

    enableSizeOverlay: false
    enablePosOverlay: false

    clipContent: false

    //clip: false

    //state: stateShown

//    onXChanged: {

//    }

//    onYChanged: {

//    }

    property Connections parentConnections: Connections {
        target: parent

        onWidthChanged: {
            //console.log("DPane.Connections.onWidthChanged - parent.width: " + parent.width);

            // Check State
            if (paneRoot.state === paneRoot.stateHidden) {

            } else {
                // Check X Position
                if (parent.width > 0 && (paneRoot.x + paneRoot.width + STYLE.defaultMargin) > parent.width) {
                    // Adjust X Pos To Stay Visible
                    paneRoot.x = parent.width - (paneRoot.width + STYLE.defaultMargin);
                }
            }
        }

        onHeightChanged: {
            //console.log("DPane.Connections.onHeightChanged - parent.height: " + parent.height);

            // Check Y Position
            if (parent.height > 0 && (paneRoot.y + paneRoot.height + STYLE.defaultMargin) > parent.height) {
                // Adjust Y Pos To Stay Visible
                paneRoot.y = parent.height - (paneRoot.height + STYLE.defaultMargin);
            }

//            // Check State
//            if (paneRoot.state === paneRoot.stateHidden) {

//            } else {
//                // Check Y Position
//                if (parent.height > 0 && (paneRoot.y + paneRoot.height + STYLE.defaultMargin) > parent.height) {
//                    // Adjust Y Pos To Stay Visible
//                    paneRoot.y = parent.height - (paneRoot.height + STYLE.defaultMargin);
//                }
//            }
        }
    }

    onPressed: {
        // Set Drag Target - ASSUMING Parent is MainGrabArea
        parent.setDragTarget(paneRoot);
    }

    onReleased: {
        // Clear Drag Target - ASSUMING Parent is MainGrabArea
        parent.clearDragTarget();
    }

    // Show
    function show() {
        // Set State
        paneRoot.state = stateShown;
    }

    // Hide
    function hide() {
        // Check Hide To Side
        if (paneRoot.hideToSide !== "") {
            // Check Hide To Side
            if (paneRoot.hideToSide === paneRoot.hideToLeft) {
                // Set Last X Offset
                paneRoot.lastShownXOffs = paneRoot.x
            } else {
                // Set Last X Offset
                paneRoot.lastShownXOffs = paneRoot.parent.width - paneRoot.x;
            }

            //console.log("DPane.hide - lastShownXOffs: " + paneRoot.lastShownXOffs);

            // Set State
            paneRoot.state = stateHidden;
        }
    }

    // Background
    DRectangle {
        id: paneBG
        anchors.fill: parent
    }

    // Title
    DText {
        id: titleText
        anchors.left: parent.left
        anchors.leftMargin: STYLE.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: STYLE.defaultMargin
        text: paneRoot.title
    }

    // Content Flickable
    DFlickable {
        id: paneContent
        anchors.fill: parent
        anchors {
            leftMargin: STYLE.defaultMargin
            topMargin: titleText.height + STYLE.defaultMargin * 2
            rightMargin: STYLE.defaultMargin
            bottomMargin: STYLE.defaultMargin
        }
    }

    // Hide Indicator
    Item {
        id: hideShowButton

        width: CONSTS.defaultPaneHideButtonWidth
        height: CONSTS.defaultPaneHideButtonHeight

        anchors.left: paneRoot.hideToSide === paneRoot.hideToLeft ? parent.right : undefined
        anchors.right: paneRoot.hideToSide === paneRoot.hideToRight ? parent.left : undefined
        anchors.verticalCenter: parent.verticalCenter

        visible: paneRoot.hideToSide !== ""

        DText {
            id: hideButtonText
            width: parent.height
            height: parent.width
            anchors.centerIn: parent
            rotation: paneRoot.hideToSide === paneRoot.hideToLeft ? -90 : 90
            //text: paneRoot.state === paneRoot.stateHidden ? paneRoot.title : "•••"
            text: "•••"
            horizontalAlignment: Text.AlignHCenter
            color: buttonMouseArea.pressed ? STYLE.colorBorder : STYLE.colorFontDark
        }

        DMouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: {
                // Check State
                if (paneRoot.state !== stateHidden) {
                    // Set State
                    paneRoot.hide();
                } else {
                    // Set State
                    paneRoot.show();
                }
            }
        }
    }

    states: [
        State {
            name: stateShown

            PropertyChanges { target: paneRoot; x: (paneRoot.hideToSide === paneRoot.hideToLeft ? paneRoot.lastShownXOffs
                                                                                                : paneRoot.parent ? (paneRoot.parent.width - paneRoot.lastShownXOffs)
                                                                                                                  : 0 ) }
        },

        State {
            name: stateHidden

            PropertyChanges { target: paneRoot; x: (paneRoot.hideToSide === paneRoot.hideToLeft ? -paneRoot.width
                                                                                                : paneRoot.parent.width) }
        }
    ]

    transitions: [
        Transition {
            to: stateShown
            SequentialAnimation {
                ScriptAction {
                    script: {
                        hideButtonText.text = "•••";
                    }
                }

                PropertyAnimation { target: paneRoot; properties: "x"; easing.type: Easing.InOutBack; duration: paneRoot.animDuration }
            }
        },

        Transition {
            to: stateHidden
            SequentialAnimation {
                PropertyAnimation { target: paneRoot; properties: "x"; easing.type: Easing.InOutBack; duration: paneRoot.animDuration }
                ScriptAction {
                    script: {
                        hideButtonText.text = paneRoot.title;
                    }
                }
            }
        }
    ]
}
