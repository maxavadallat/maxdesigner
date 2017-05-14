import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeTreeRoot

    width: 400
    height: 600

    property ComponentInfo rootComponent: null

    property Connections propertiesControllerConnections: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Reset Swipe Index
            nodeTreeRoot.swipeIndex = -1;
        }
    }

    property bool nodeTreeInit: false

    property int swipeIndex: -1

//    default property alias content: rootNode.childrenContainerAlias

    Component.onCompleted: {
        // Set Node Tree Init
        nodeTreeRoot.nodeTreeInit = true;

        // ...
    }

    onRootComponentChanged: {
        // Clear
        clear();

        // Check Node Tree Init
        if (nodeTreeRoot.nodeTreeInit) {
            console.log("DNodeTree.onRootComponentChanged - rootComponent: " + (rootComponent !== null ? rootComponent.componentName : "NULL"));
            // Build Node Model
            buildNodeModel();
        }
    }

    // Append Node
    function appendNode(componentInfo, parentIndex, rootNode) {

        // Init New Item
        var newItem = { "title"        : componentInfo.componentPath,
                        "componentInfo": componentInfo,
                        "childIndexes" : "",
                        "parentIndex"  : parentIndex === undefined ? -1 : parentIndex,
                        "rootNode"     : rootNode !== undefined ? rootNode : false,
                        "expanded"     : true };


        // Init Current Node Index
        var cnIndex = nodeListModel.count;

        // Append Item To Model
        nodeListModel.append(newItem);

        // Get Child Count
        var cCount = componentInfo.childCount;
        // Init Child Indexes Temp
        var ciTemp = "";

        // Iterate Through Children
        for (var i=0; i<cCount; i++) {
            // Check Index
            if (i === 0) {
                // Set Child Inexes
                ciTemp = String(nodeListModel.count);
            } else {
                // Append Child Index
                ciTemp += ("," + String(nodeListModel.count));
            }

            // Append Children
            appendNode(componentInfo.childInfo(i), cnIndex);

            //console.log("#### i: " + cnIndex + " - ci: " + nodeListModel.get(cnIndex).childIndexes);

        }

        console.log("DNodeTree.appendNode - i: " + cnIndex + " - pi: " + parentIndex + " - t: " + componentInfo.componentPath + " - ci: " + ciTemp);

        // Update Child Indexes
        nodeListModel.setProperty(cnIndex, "childIndexes", ciTemp);

    }

    // Insert Node
    function insertNode(newIndex, componentInfo, parentIndex) {

        // Init New Item
        var newItem = { "title"        : componentInfo.componentPath,
                        "componentInfo": componentInfo,
                        "childIndexes" : "",
                        "parentIndex"  : parentIndex === undefined ? -1 : parentIndex,
                        "rootNode"     : false,
                        "expanded"     : true };

        // Insert Item To Model
        nodeListModel.insert(newIndex, newItem);
        // Get Child Count
        var cCount = componentInfo.childCount;

        // Iterate Through Children
        for (var i=0; i<cCount; i++) {
            // Insert Children
            insertNode(newIndex + 1 + i, componentInfo.childInfo(i), parentIndex);

            // Set Child Indexes

            // ...
        }
    }

    // Remove Node
    function removeNode(nodeIndex) {
        // Get Model Item Data
        var modelItem = nodeListModel.get(nodeIndex);

        // Check Child Indexes

        // Remove Item from Model
    }

    // Move Node
    function moveNode(nodeIndex, targetIndex) {

        // Mode Node

        // Set Parent Indexes

        // Update Child Indexes

    }

    // Build Model
    function buildNodeModel() {
        // Check Root Component Info
        if (nodeTreeRoot.rootComponent !== null) {
            // Append Root Node
            appendNode(nodeTreeRoot.rootComponent, -1, true);
        }
    }

    // Clear
    function clear() {
        // Clear Model
        nodeListModel.clear();
    }

    // Expand Node
    function expandNode(nodeInex) {
        console.log("DNodeTree.expandNode - nodeInex: " + nodeInex);

        // ...
    }

    // Collapse Node
    function collapseNode(nodeIndex) {
        console.log("DNodeTree.collapseNode - nodeInex: " + nodeInex);

        // ...
    }

    // Handle Child Removed
    function handleChildRemoved(nodeIndex, childIndex) {
        console.log("DNodeTree.handleChildRemoved - nodeIndex: " + nodeIndex + " - childIndex: " + childIndex);

        // Get Node Data
        var nodeData = nodeListModel.get(nodeIndex);

        // Get Child Indexes
        var cIndexes = nodeData.childIndexes;

        // Check Child Indexes
        if (cIndexes.length > 0) {
            // Split Child Indexes
            cIndexes = cIndexes.split(",");

            console.log("DNodeTree.handleChildRemoved - cIndexes: " + cIndexes);

            // Get Child Model Index
            var cnIndex = cIndexes[childIndex];

            console.log("DNodeTree.handleChildRemoved - cnIndex: " + cnIndex);

            // Get Child Node Data
            var childNodeData = nodeListModel.get(cnIndex);

            // Get Child Indexes
            var ccIndexes = childNodeData.childIndexes;

            // Check Child Indexes
            if (ccIndexes.length > 0) {
                // Split
                ccIndexes = ccIndexes.split(",");

                console.log("DNodeTree.handleChildRemoved - ccIndexes: " + ccIndexes + " - length: " + ccIndexes.length);

                // Iterate Through Children
                for (var i=ccIndexes.length - 1; i>=0; i--) {
                    // Handle Child Children Removed
                    handleChildRemoved(cnIndex, i);
                }
            }

            // Check Child Index
            if (childIndex >= 0 && childIndex < cIndexes.length) {
                // Remove Child Index
                cIndexes.splice(childIndex, 1);
                // Update Child Indexes For Node
                nodeListModel.setProperty(nodeIndex, "childIndexes", cIndexes.length > 0 ? cIndexes.join(",") : "");
            }

            // Update Indexes
            updateIndexes(cnIndex, -1);

            // Remove Item
            nodeListModel.remove(cnIndex);

        }
    }

    // Handle Child Added
    function handleChildAdded(nodeIndex, childIndex) {
        console.log("DNodeTree.handleChildAdded - nodeIndex: " + nodeIndex + " - childIndex: " + childIndex);

        // ...

    }

    // Handle Child Moved
    function handleChildMoved(nodeIndex, childIndex, targetIndex) {
        console.log("DNodeTree.handleChildMoved - nodeIndex: " + nodeIndex + " - childIndex: " + childIndex + " - targetIndex: " + targetIndex);

        // ...

    }

    // Update Parent & Child Indexes
    function updateIndexes(nodeIndex, offset) {
        console.log("DNodeTree.updateIndexes - nodeIndex: " + nodeIndex + " - offset: " + offset);

        // Iterate Through Mode
        for (var i=0; i<nodeListModel.count; i++) {
            // Check Index
            if (i !== nodeIndex) {
                // Init Index Updated
                var iUpdated = false;
                // Get Item Data
                var nodeData = nodeListModel.get(i);
                // Get Parent Index
                var parentIndex = nodeData.parentIndex;

                // Check Parent Index
                if (parentIndex > nodeIndex) {
                    // Update Parent Index
                    nodeData.parentIndex = Number(parentIndex) + Number(offset);
                    // Set Index Updated
                    iUpdated = true;
                }

                // Get Child Indexes
                var childIndexes = nodeData.childIndexes;

                // Check Child Indexes
                if (childIndexes.length > 0) {
                    // Split Child Indexes
                    childIndexes = childIndexes.split(",");

                    // Iterate Through Child Indexes
                    for (var n=0; n<childIndexes.length; n++) {
                        // Check Child Index
                        if (childIndexes[n] > nodeIndex) {
                            // Update Child Index
                            childIndexes[n] = Number(childIndexes[n]) + Number(offset);
                            // Set Index Updated
                            iUpdated = true;
                        }
                    }
                }

                // Check Index updated
                if (iUpdated) {
                    console.log("DNodeTree.updateIndexes - nodeIndex: " + i + " - offset: " + offset);
                    // Set Child Indexes
                    nodeData.childIndexes = childIndexes.length > 0 ? childIndexes.join(",") : childIndexes[0];
                    // Set Node List Model Data
                    nodeListModel.set(i, nodeData);
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: -1
        color: "transparent"
        border.color: "purple"
    }

    // Node List Model
    ListModel {
        id: nodeListModel

        // ...
    }

    // Node List View
    DListView {
        id: nodeListView
        anchors.fill: parent

        itemHeight: CONSTS.defaultNodeTreeItemHeight
        spacing: DStyle.defaultSpacing

        addTransition: Transition {
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: DStyle.animDuration }
        }

        model: nodeListModel

        delegate: DNodeTreeNode {
            anchors.right: parent.right

            itemIndex: index

            swipeIndex: nodeTreeRoot.swipeIndex

            rootNode     : model.rootNode
            title        : model.title
            componentInfo: model.componentInfo
            parentIndex  : model.parentIndex
            childIndexes : model.childIndexes
            expanded     : model.expanded

            onSwipeActivated: nodeTreeRoot.swipeIndex = itemIndex;
            onDeleteItem: nodeTreeRoot.removeNode(itemIndex);
            onExpandItem: nodeTreeRoot.expandNode(itemIndex);
            onCollapseItem: nodeTreeRoot.collapseNode(itemIndex);

            onChildAdded: nodeTreeRoot.handleChildAdded(itemIndex, childIndex);
            onChildMoved: nodeTreeRoot.handleChildMoved(itemIndex, childIndex, targetIndex);
            onChildRemoved: nodeTreeRoot.handleChildRemoved(itemIndex, childIndex);
            onItemSelected: nodeListView.ensureItemVisible(itemIndex);
        }
    }
}
