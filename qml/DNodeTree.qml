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

    Rectangle {
        anchors.fill: parent
        anchors.margins: -1
        color: "transparent"
        border.color: "purple"
    }

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
}
