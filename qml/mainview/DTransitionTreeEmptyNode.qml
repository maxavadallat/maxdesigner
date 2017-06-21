import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: emptyNodeRoot

    width: 300
    height: 0

    // Child Index
    property int childIndex: -1
    // Transition Editor Root
    property QtObject transitionEditorRoot: null
    // Parent Node
    property QtObject parentNode: null

    // Drop OK
    property bool dropOK: false

    smooth: true

    visible: height > 0

    signal emptyNodeShown()

    // Show Empty Node
    function showEmptyNode() {
        // Run Height Animation
        heightAnimation.start();
    }

    // Hide EMpty Node
    function hideEmptyNode() {
        // Reset Opacity
        nodeBackground.opacity = 0.0;
        // Reset Height
        emptyNodeRoot.height = 0;
    }

    // Animatin On Height
    DAnimation {
        id: heightAnimation

        target: emptyNodeRoot
        property: "height"
        to: CONSTS.defaultNodeTreeItemHeight + DStyle.defaultSpacing

        onStopped: {
            // Emit Empty Node Shown Signal
            emptyNodeRoot.emptyNodeShown();
            // Start Background Opacity Animation
            bgOpacityAnimation.start();
        }
    }

    // Background Rectangle
    DRectangle {
        id: nodeBackground
        width: parent.width
        height: CONSTS.defaultNodeTreeItemHeight
        anchors.verticalCenter: parent.verticalCenter
        border.color: emptyNodeDropArea.containsDrag ? emptyNodeRoot.dropOK ? DStyle.colorBorderHoverOK : DStyle.colorBorderHoverNOK : DStyle.colorBorderNoFocus
        opacity: 0.0

        DFadeAnimation {
            id: bgOpacityAnimation
            target: nodeBackground
            to: 1.0
        }

        DText {
            anchors.centerIn: parent
            text: emptyNodeRoot.childIndex
        }
    }

    // Drop Area
    DropArea {
        id: emptyNodeDropArea
        anchors.fill: parent

        onEntered: {
            // Check Height
            if (emptyNodeRoot.height === 0) {
                return;
            }

            // Reset Drop OK
            emptyNodeRoot.dropOK = false;

            // Check Drop Keys
            if ((drag.keys[0] === CONSTS.newComponentDragKey || drag.keys[0] === CONSTS.childComponentDragKey) && drag.source !== null) {

                // Check Source & Source Parent Component
                if (drag.source.componentCategory === "Animation") {
                    //console.log("DAnimationTreeEmptyNode.emptyNodeDropArea.onEntered - ACCEPT!");

                    // Set Drop OK
                    emptyNodeRoot.dropOK = true;

                    // Accept Drag
                    drag.accept();
                }
            }

            // Set Hovering Node Parent
            transitionEditorRoot.hoveringNodeParent = parentNode;
        }

        onDropped: {
            //console.log("DAnimationTreeEmptyNode.emptyNodeDropArea.onDropped");

            // Check Drop OK
            if (!emptyNodeRoot.dropOK) {
                return;
            }

            // Get Dragged Component Info
            var draggedComponentInfo = drop.source;

            // Check Source
            if (parentNode !== null && parentNode.componentInfo !== null && draggedComponentInfo!== null) {
                // Check Keys - New Component
                if (drop.keys[0] === CONSTS.newComponentDragKey) {
                    console.log("DAnimationTreeEmptyNode.emptyNodeDropArea.onDropped - NEW CHILD DROP!");

                    // Check Component Info
                    if (parentNode.componentInfo.protoType && parentNode.componentInfo === draggedComponentInfo) {
                        console.warn("DAnimationTreeEmptyNode.emptyNodeDropArea.onDropped - RECURSIVE!!");
                        return;
                    }

                    // TODO: More Checking

                    // Add Child To Parent Node Component
                    parentNode.componentInfo.insertChild(emptyNodeRoot.childIndex, draggedComponentInfo.clone(), false);

                // Drop Another Child Node
                } else if (drop.keys[0] === CONSTS.childComponentDragKey) {
                    console.log("DAnimationTreeEmptyNode.emptyNodeDropArea.onDropped - CHILD DRAG & DROP!");

                    // TODO: Add More Checking

                    // Check Component Parent
                    if (draggedComponentInfo.componentParent !== null) {
                        // Move Animation
                        draggedComponentInfo.componentParent.moveAnimation(draggedComponentInfo.componentParent, transitionEditorRoot.grabbedIndex,
                                                                           emptyNodeRoot.parentNode.componentInfo, emptyNodeRoot.childIndex);
                    } else {

                        // ...

                    }

                } else {
                    console.warn("DAnimationTreeEmptyNode.emptyNodeDropArea.onDropped - UNSUPPORTED DROP!");
                }
            }

            // Reset Drop OK
            emptyNodeRoot.dropOK = false;

//            // Reset Hovering Parent Node
//            transitionEditorRoot.hoveringNodeParent = null;
        }

        onExited: {
            // Reset Drop OK
            emptyNodeRoot.dropOK = false;
            // Destroy Empty Node
            //parentNode.removeEmptyNode();
        }
    }
}
