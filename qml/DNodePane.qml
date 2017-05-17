import QtQuick 2.0
import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DContainer {
    id: nodePaneRoot

    anchors.verticalCenter: parent.verticalCenter

    property ComponentInfo componentInfo: null

    property string title: componentInfo !== null ? componentInfo.componentName : "NULL"

    property int initialX: 0
    property int initialY: parent ? parent.height * 0.5 : 0

    property int initialWidth: 0
    property int initialHeight: 0

    property int creationX: initialX - creationWidth - DStyle.defaultMargin
    property int creationY: initialY - creationHeight * 0.5

    property int creationWidth: 320
    property int creationHeight: 400

    readonly property string stateCreate: "create"
    readonly property string stateShown: "shown"

    minWidth: 320
    minHeight: 400

    enablePosOverlay: false
    enableSizeOverlay: false

    resizeRightEnabled: false

    state: stateCreate

    enableDrag: false

    signal transitionStarted(var newState)
    signal transitionFinished(var newState)

    onTransitionStarted: {
        // Check New State
        if (newState !== stateShown) {
            // Reset Opacity
            nodeTree.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Opacity
            nodeTree.opacity = 1.0;
        }
    }

    // Title Label
    DText {
        id: titleLabel
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: DStyle.defaultMargin
        text: nodePaneRoot.title
    }

    // Node tree
    DNodeTree {
        id: nodeTree
        anchors.fill: parent
        anchors.leftMargin: DStyle.defaultMargin * 2
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.bottomMargin: DStyle.defaultMargin * 2
        rootComponent: nodePaneRoot.componentInfo
        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

//        onNodeGrabbed: {
//            // Disable Drag by Setting Drag Threshold
//            drag.threshold = Math.max(nodePaneRoot.width, nodePaneRoot.height);
//        }

//        onNodeReleased: {
//            // Reset Drag Threshold for the pane
//            drag.threshold = CONSTS.defaultDragThreshold;
//        }
    }

    // Hide/Show Button
    DMouseArea {
        id: hideShowButton

        parent: nodePaneRoot

        width: CONSTS.defaultPaneHideButtonWidth
        height: CONSTS.defaultPaneHideButtonHeight

        anchors.right: parent.left
        anchors.verticalCenter: parent.verticalCenter

        DText {
            anchors.centerIn: parent
            rotation: 90
            horizontalAlignment: Text.AlignHCenter
            color: parent.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            text: "•••"
        }

        onClicked: {
            // Check State
            if (nodePaneRoot.state === stateShown) {
                // Set State
                nodePaneRoot.state = stateCreate;
            } else {
                // Set State
                nodePaneRoot.state = stateShown;
            }
        }
    }

    states: [
        // Create State
        State {
            name: stateCreate

            PropertyChanges { target: nodePaneRoot; x: initialX; y: initialY; width: initialWidth; height: initialHeight }
        },

        // Shown State
        State {
            name: stateShown

            PropertyChanges { target: nodePaneRoot; x: nodePaneRoot.creationX; y: nodePaneRoot.creationY }
            PropertyChanges { target: nodePaneRoot; width: nodePaneRoot.creationWidth; height: nodePaneRoot.creationHeight }

        }
    ]

    transitions: [
        // To Shown
        Transition {
            to: stateShown

            SequentialAnimation {
                // Emit Transition Started Signal
                ScriptAction { script: { nodePaneRoot.transitionStarted(state); } }

                PropertyAction { target: nodePaneRoot; property: "height"; value: 1 }

                PropertyAction { target: nodePaneRoot; property: "x"; value: nodePaneRoot.initialX }
                PropertyAction { target: nodePaneRoot; property: "y"; value: nodePaneRoot.initialY }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "x"; to: nodePaneRoot.creationX }
                    DAnimation { target: nodePaneRoot; property: "width"; to: nodePaneRoot.initialX - nodePaneRoot.creationX }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width" }
                    DAnimation { target: nodePaneRoot; property: "x" }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "y" }
                    DAnimation { target: nodePaneRoot; property: "height" }
                }

                // Emit Transition Finished Signal
                ScriptAction { script: { nodePaneRoot.transitionFinished(state); } }
            }
        },
        // To Create
        Transition {
            to: stateCreate

            SequentialAnimation {
                // Emit Transition Started Signal
                ScriptAction { script: { nodePaneRoot.transitionStarted(state); } }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "y"; to: nodePaneRoot.y + nodePaneRoot.height * 0.5 }
                    DAnimation { target: nodePaneRoot; property: "height"; to: 1 }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width"; to: -nodePaneRoot.x }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width"; to: 0 }
                    DAnimation { target: nodePaneRoot; property: "x"; to: nodePaneRoot.initialX }
                }

                ParallelAnimation {
                    PropertyAction { target: nodePaneRoot; property: "height"; value: 0 }
                }

                // Emit Transition Finished Signal
                ScriptAction { script: { nodePaneRoot.transitionFinished(state); } }
            }
        }
    ]
}
