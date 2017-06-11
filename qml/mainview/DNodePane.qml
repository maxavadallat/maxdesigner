import QtQuick 2.0
import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../controls"
import "../animations"

DContainer {
    id: nodePaneRoot

    width: initialWidth
    height: initialHeight

    anchors.right: parent.right
    anchors.rightMargin: paneRightMargin
    anchors.verticalCenter: parent.verticalCenter

    property int paneRightMargin: 0

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

    // Show Nodes
    function showNodes() {
        // Set State
        nodePaneRoot.state = stateShown;
    }

    // Hide Nodes
    function hideNodes() {
        // Set State
        nodePaneRoot.state = stateCreate;
    }

    // Title Label
    DText {
        id: titleLabel
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: DStyle.defaultMargin
        text: nodePaneRoot.title
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0
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
            text: "••"
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

            PropertyChanges { target: nodePaneRoot; width: initialWidth; height: initialHeight }
            PropertyChanges { target: nodePaneRoot; paneRightMargin: 0 }
        },

        // Shown State
        State {
            name: stateShown

            PropertyChanges { target: nodePaneRoot; width: nodePaneRoot.creationWidth; height: nodePaneRoot.creationHeight }
            PropertyChanges { target: nodePaneRoot; paneRightMargin: DStyle.defaultMargin }
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

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width"; to: nodePaneRoot.creationWidth + DStyle.defaultMargin }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width" }
                    DAnimation { target: nodePaneRoot; property: "paneRightMargin" }
                }

                ParallelAnimation {
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

                ScriptAction {
                    script: {
                        // Emit Transition Started Signal
                        nodePaneRoot.transitionStarted(state);
                        // Update CreationWidth
                        nodePaneRoot.creationWidth = nodePaneRoot.width;
                    }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "height"; to: 1 }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width"; to: nodePaneRoot.creationWidth + DStyle.defaultMargin }
                    DAnimation { target: nodePaneRoot; property: "paneRightMargin" }
                }

                ParallelAnimation {
                    DAnimation { target: nodePaneRoot; property: "width"; to: 0 }
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
