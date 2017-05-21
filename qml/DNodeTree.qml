import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeTreeRoot

    width: 400
    height: 600

    property ComponentInfo rootComponent: null

    property bool nodeTreeInit: false

    default property alias content: rootNode.childrenContainerAlias

    property int nodePressX: 0
    property int nodePressY: 0

    property QtObject dragMouseArea: null

    property DNodeTreeNode currentNode: null

    property alias nodeGrabbedState: grabbedNode.dragActive
    property alias grabbedIndex: grabbedNode.childIndex

    signal nodePressed(var posX, var posY, var mouseArea)
    signal nodeGrabbed(var nodeX, var nodeY, var nodeWidth, var nodeHeight, var componentInfo, var grabbedIndex)
    signal nodePosChanged(var nodeX, var nodeY)
    signal nodeReleased()
    signal removeEmptyNode()

    Component.onCompleted: {
        // Set Node Tree Init
        nodeTreeRoot.nodeTreeInit = true;

        // ...
    }

    onNodePressed: {
        console.log("DNodeTree.onNodePressed - [" + posX + ":" + posY + "]");

        // Set Node Press X
        nodeTreeRoot.nodePressX = posX;
        // Set Node Press Y
        nodeTreeRoot.nodePressY = posY;

        // Set Node Drag Mouse Area
        nodeTreeRoot.dragMouseArea = mouseArea;

        // ...
    }

    onNodeGrabbed: {
        //console.log("DNodeTree.onNodeGrabbed - grabbedIndex: " + grabbedIndex);

        // Set Interactive State
        nodeTreeFlickable.interactive = false;

        // Set Drag Target
        nodeTreeRoot.dragMouseArea.drag.target = grabbedNode;

        // Set Grabbed Index
        grabbedNode.childIndex = grabbedIndex;

        // Set Up Grabbed Node
        grabbedNode.x = nodeX;
        grabbedNode.y = nodeY;

        grabbedNode.width = nodeWidth;
        grabbedNode.height = nodeHeight;

        // Set Component Info
        grabbedNode.componentInfo = componentInfo;
        // Set Visibility
        grabbedNode.visible = true;
        // Scale Up
        grabbedNode.scale = 1.05;

        // Set Drag Active
        grabbedNode.dragActive = true;
    }

    onNodeReleased: {
        //console.log("DNodeTree.onNodeReleased");

        // Reset Drag Active
        grabbedNode.dragActive = false;

        // Set Interactive State
        nodeTreeFlickable.interactive = true;
        // Reset Drag Target
        nodeTreeRoot.dragMouseArea.drag.target = undefined;
        // Reset Node Drag Mouse Area
        nodeTreeRoot.dragMouseArea = null;
        // Reset Scale
        grabbedNode.scale = 1.0;
        // Set Visibility
        grabbedNode.visible = false;
    }

    // Create Node
    function createNode(componentInfo, nodeParent) {
        // Check Component Info
        if (componentInfo !== null) {
            // Create New Node Object
            var newNodeObject = newNodeComponent.createObject(nodeParent);
            // Set Component Info
            newNodeObject.componentInfo = componentInfo;

            return newNodeObject;
        }

        return null;
    }

    // new Node Component
    Component {
        id: newNodeComponent

        DNodeTreeNode {
            visible: componentInfo !== null
            nodeTree: nodeTreeRoot
        }
    }

    // Drag Tracking Mouse Area For Scrolling Node tree Content
    DMouseArea {
        id: dragTrackingMouseArea
        anchors.fill: parent
        hoverEnabled: true
        visible: grabbedNode.dragActive && nodeTreeFlickable.contentHeight > nodeTreeFlickable.height

        onPositionChanged: {
            //console.log("#### DNodeTree.dragTrackingMouseArea.onPositionChanged - mouse: [" + mouse.x + ":" + mouse.y + "]");

            // Check Y Position

            // ...
        }
    }

    // Node Tree Flickable
    DFlickable {
        id: nodeTreeFlickable
        anchors.fill: parent

        DNodeTreeNode {
            id: rootNode
            width: nodeTreeFlickable.width
            componentInfo: nodeTreeRoot.rootComponent
            visible: componentInfo !== null
            nodeTree: nodeTreeRoot
            rootNode: true
        }
    }

    // Grabbed Node Overlay
    DNodeTreeNode {
        id: grabbedNode

        visible: false

        dropAreasVisible: false
        enableLayerVisibilityButton: false
        enableDropAreasVisibility: false

        property bool dragActive: false

        onDragActiveChanged: {
            //console.log("DNodeTree.grabbedNode.onDragActiveChanged - dragActive: " + dragActive);

            // Cheeck Drag Active
            if (dragActive) {
                // Start Drag
                Drag.start();
            } else {
                // Stop Drag
                Drag.drop();

                // Emit Remove Empty Node Signal
                nodeTreeRoot.removeEmptyNode();
            }
        }

        Drag.active: dragActive

        Drag.hotSpot.x: grabbedNode.width * 0.5 //nodeTreeRoot.nodePressX
        Drag.hotSpot.y: grabbedNode.height * 0.5 //nodeTreeRoot.nodePressY

        Drag.source: grabbedNode.componentInfo
        Drag.keys: [ CONSTS.childComponentDragKey ]
    }
}
