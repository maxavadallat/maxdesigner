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

    property int nodePosX: 0
    property int nodePosY: 0

    property DNodeTreeNode currentNode: null

    signal nodePressed(var posX, var posY)
    signal nodeGrabbed(var nodeX, var nodeY, var nodeWidth, var nodeHeight, var componentInfo)
    signal nodePosChanged(var nodeX, var nodeY)
    signal nodeReleased()

    Component.onCompleted: {
        // Set Node Tree Init
        nodeTreeRoot.nodeTreeInit = true;

        // ...
    }

//    onRootComponentChanged: {
//        // Check Node Tree Init
//        if (nodeTreeRoot.nodeTreeInit) {
//            console.log("DNodeTree.onRootComponentChanged - rootComponent: " + (rootComponent !== null ? rootComponent.componentName : "NULL"));
//        }
//    }

    onNodePressed: {
        //console.log("DNodeTree.onNodePressed - [" + posX + ":" + posY + "]");

        // Set Node Press X
        nodeTreeRoot.nodePressX = posX;
        // Set Node Press Y
        nodeTreeRoot.nodePressY = posY;

        // ...
    }

    onNodeGrabbed: {
        //console.log("DNodeTree.onNodeGrabbed - [" + nodeX + ":" + nodeY + "]");

        // Set Interactive State
        nodeTreeFlickable.interactive = false;

        // Store Node Pos X
        nodeTreeRoot.nodePosX = nodeX;
        nodeTreeRoot.nodePosY = nodeY;

        // Set Up Grabbed Node
        grabbedNode.x = nodeX;//nodeTreeRoot.width - nodeWidth;
        grabbedNode.y = nodeY;

        grabbedNode.width = nodeWidth;
        grabbedNode.height = nodeHeight;

        // Set Component Info
        grabbedNode.componentInfo = componentInfo;

        // Set Visibility
        grabbedNode.visible = true;

        grabbedNode.dragActive = true;

        //grabbedNode.scale = 1.1;
    }

    onNodePosChanged: {
        //console.log("DNodeTree.onNodePosChanged - [" + nodeX + ":" + nodeY + "]");

        // Set Grabbed Node Pos
        grabbedNode.x = nodeTreeRoot.nodePosX + nodeX - nodeTreeRoot.nodePressX;
        grabbedNode.y = nodeTreeRoot.nodePosY + nodeY - nodeTreeRoot.nodePressY;

        // ...

    }

    onNodeReleased: {
        // Reset Scale
        grabbedNode.scale = 1.0;
        // Set Visibility
        grabbedNode.visible = false;

        // Set Interactive State
        nodeTreeFlickable.interactive = true;

        // Reset Drag Active
        grabbedNode.dragActive = false;
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

    Component {
        id: newNodeComponent

        DNodeTreeNode {
            visible: componentInfo !== null
            nodeTree: nodeTreeRoot
        }
    }

//    Rectangle {
//        anchors.fill: parent
//        anchors.margins: -1
//        color: "transparent"
//        border.color: "purple"
//    }

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

    DNodeTreeNode {
        id: grabbedNode
        visible: false
        hideDropAreas: true
        enableLayerVisibilityButton: false

        property bool dragActive: false

        Drag.active: dragActive

        Drag.hotSpot.x: nodeTreeRoot.nodePressX
        Drag.hotSpot.y: nodeTreeRoot.nodePressY - 2

        Drag.source: grabbedNode.componentInfo
        Drag.keys: [ CONSTS.childComponentDragKey ]
    }
}
