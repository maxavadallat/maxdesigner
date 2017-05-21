import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: emptyNodeRoot

    width: 300
    height: 0

    // Child Index
    property int childIndex: -1
    // Parent Node Tree
    property QtObject nodeTree: null
    // Parent Node
    property QtObject parentNode: null

    smooth: true

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

//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "teal"
//    }

    // Animatin On Height
    DAnimation {
        id: heightAnimation

        target: emptyNodeRoot
        property: "height"
        to: CONSTS.defaultNodeTreeItemHeight + DStyle.defaultSpacing;

        onStopped: {
            bgOpacityAnimation.start();
        }
    }

    // Background Rectangle
    DRectangle {
        id: nodeBackground
        width: parent.width
        height: CONSTS.defaultNodeTreeItemHeight
        anchors.verticalCenter: parent.verticalCenter
        border.color: emptyNodeDropArea.containsDrag ? "yellow" : DStyle.colorBorderNoFocus
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
            // Check Drop Keys
            if (drag.keys[0] === CONSTS.newComponentDragKey || drag.keys[0] === CONSTS.childComponentDragKey) {
                //console.log("DNodeTreeEmptyNode.emptyNodeDropArea.onEntered - ACCEPT!");
                // Accept Drag
                drag.accept();
            }
        }

        onDropped: {
            //console.log("DNodeTreeEmptyNode.emptyNodeDropArea.onDropped");

            // Get Dragged Component Info
            var draggedComponentInfo = drop.source;

            // Check Source
            if (parentNode !== null && parentNode.componentInfo !== null && draggedComponentInfo!== null) {
                // Check Keys - New Component
                if (drop.keys[0] === CONSTS.newComponentDragKey) {
                    console.log("DNodeTreeEmptyNode.emptyNodeDropArea.onDropped - NEW CHILD DROP!");

                    // Check Component Info
                    if (parentNode.componentInfo.protoType && parentNode.componentInfo === draggedComponentInfo) {
                        console.warn("DNodeTreeEmptyNode.emptyNodeDropArea.onDropped - RECURSIVE!!");
                        return;
                    }

                    // TODO: More Checking

                    // Add Child To Parent Node Component
                    parentNode.componentInfo.addChild(draggedComponentInfo.clone());

                // Drop Another Child Node
                } else if (drop.keys[0] === CONSTS.childComponentDragKey) {
                    console.log("DNodeTreeEmptyNode.emptyNodeDropArea.onDropped - CHILD DRAG & DROP!");

                    // Move Child
                    draggedComponentInfo.componentParent.moveChild(draggedComponentInfo.componentParent, nodeTree.grabbedIndex,
                                                                   emptyNodeRoot.parentNode.componentInfo, emptyNodeRoot.childIndex);

                    // ...

                } else {
                    console.warn("DNodeTreeEmptyNode.emptyNodeDropArea.onDropped - UNSUPPORTED DROP!");
                }
            }
        }

        onExited: {
            // Destroy Empty Node
            parentNode.removeEmptyNode(childIndex);
        }
    }
}
