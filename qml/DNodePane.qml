import QtQuick 2.0
import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DPaneBase {
    id: nodePaneRoot

    property ComponentInfo componentInfo: null

    title: componentInfo !== null ? componentInfo.componentName : "NULL"

    hideToSide: hideToRight

    creationWidth: 320
    creationHeight: 400

    minWidth: 320
    minHeight: 400

    enablePosOverlay: false
    enableSizeOverlay: false

    hideAction: hideActionReset

    hideButtonVisibleOnCreate: true

    resizeRightEnabled: false

    state: stateCreate

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

            // Check Parent Pane
            if (nodePaneRoot.parentPane !== null) {

            }
        }
    }

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

        onNodeGrabbed: {
            // Disable Drag by Setting Drag Threshold
            drag.threshold = Math.max(nodePaneRoot.width, nodePaneRoot.height);
        }

        onNodeReleased: {
            // Reset Drag Threshold for the pane
            drag.threshold = CONSTS.defaultDragThreshold;
        }
    }
}
