import QtQuick 2.7
import QtQml.Models 2.2

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeRoot

    width: 300
    height: collapsedHeight

    Behavior on height {
        SequentialAnimation {
            DAnimation {
                duration: nodeTree !== null && nodeTree.currentNode === nodeRoot ? DStyle.animDuration : 0
            }

            ScriptAction {
                script: {
                    nodeTree.currentNode = null;
                }
            }
        }
    }

    // Collapsed Height
    property int collapsedHeight: CONSTS.defaultNodeTreeItemHeight + DStyle.defaultSpacing
    // Expanded Height
    property int expandedHeight: collapsedHeight + childrenColumn.height
    // Default Parent
    default property alias childrenContainerAlias: childrenColumn.children
    // Node's Component Info
    property ComponentInfo componentInfo: null
    // Node is Root
    property bool rootNode: false
    // Node Title Text
    property string title: {
        // Check Component Info
        if (componentInfo !== null) {
            // Check Component ID
            if (componentInfo.componentID !== "") {
                return componentInfo.componentID + ":" + componentInfo.componentName;
            }

            return componentInfo.componentName;
        }

        return "";
    }
    // Node Child Index
    property int childIndex: -1
    // Node's Grabbed Child Index
    property int grabbedChildIndex: -1
    // Node Expanded State
    property bool expanded: false
    // Node Intialized - Component Completed
    property bool nodeInit: false
    // Node Grabbed
    property bool nodeGrabbed: false
    // Parent Node Tree
    property QtObject nodeTree: null
    // Parent Node
    property QtObject parentNode: null
    // Component Info Connections
    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onChildAdded: {
            //console.log("DNodeTreeNode.componentInfoConnections.onChildAdded - aIndex: " + aIndex);
            // Insert Node
            insertNode(aIndex);
            // Expand
            expand();
        }

        onChildMoved: {
            //console.log("DNodeTreeNode.componentInfoConnections.onChildMoved - parent: " + aParentComponent.componentPath + " - aIndex: " + aIndex + " - aTarget: " + aTargetComponent.componentPath + " - aTargetIndex: " + aTargetIndex);

            // Check Parent & Target Component
            if (aParentComponent === aTargetComponent) {
                // Move Node
                moveNode(aIndex, aTargetIndex);
            } else {
                // Remove Node
                removeNode(aIndex);
                // Check Hovering Node Parent
                if (nodeTree.hoverindNodeParent) {
                    // Insert Node
                    nodeTree.hoverindNodeParent.insertNode(aTargetIndex);
                    // Set Current Node For Animating Height
                    nodeTree.currentNode = nodeTree.hoverindNodeParent;
                    // Expand
                    nodeTree.hoverindNodeParent.expand();
                    // Reset Hovering Parent Node
                    nodeTree.hoverindNodeParent = null;
                } else {
                    console.log("DNodeTreeNode.componentInfoConnections.onChildMoved - NULL HOVERING PARENT NODE!!");
                }
            }
        }

        onChildRemoved: {
            //console.log("DNodeTreeNode.componentInfoConnections.onChildRemoved - aIndex: " + aIndex);

            // Remove Node
            removeNode(aIndex);

            // Check Children Column
            if (childNodesModel.count === 0) {
                // Collapse
                collapse();
            }
        }
    }
    // Node Tree Connections
    property Connections nodeTreeConnections: Connections {
        target: nodeTree

        onRemoveEmptyNode: {
            // Remove Empty Node
            removeEmptyNode();
        }
    }
    // Drop Areas Visible
    property bool dropAreasVisible: nodeTree ? nodeTree.nodeGrabbedState : false
    // Child Temp Array for Child Insert
    property var childTemp: []
    // Enable Layer Visibility Button
    property bool enableLayerVisibilityButton: true
    // Enable Drop Areas Visibility
    property bool enableDropAreasVisibility: !nodeGrabbed

    opacity: nodeGrabbed ? 0.5 : 1.0

    clip: true

    Component.onCompleted: {
        // Set Node Init
        nodeRoot.nodeInit = true;

        // ...
    }

    Component.onDestruction: {
        // Clear
        clear();
    }

    onChildIndexChanged: {
        //console.log("DNodeTreeNode.onChildIndexChanged - childIndex: " + childIndex);

        // ...
    }

    onComponentInfoChanged: {
        //console.log("DNodeTreeNode.onComponentInfoChanged - componentName: " + (nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.componentName  + " - childCount: " + nodeRoot.componentInfo.childCount : "NULL"));

        // Clear
        clear();
        // Build Node tree
        buildNodeTree();
    }

    onExpandedChanged: {
        //console.log("DNodeTreeNode.onExpandedChanged - expanded: " + expanded + " - childIndex: " + childIndex);
        // Check If Expanded
        if (nodeRoot.expanded) {
            // Set Height
            nodeRoot.height = Qt.binding(function() {
                // Check Children
                if (childNodesModel.count > 0) {
                    return expandedHeight;
                }

                return collapsedHeight;
            });
        } else {
            // Set Height
            nodeRoot.height = collapsedHeight;
        }

        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    onNodeGrabbedChanged: {
        //console.log("DNodeTreeNode.onNodeGrabbedChanged - nodeGrabbed: " + nodeGrabbed + " - childIndex: " + childIndex);

        // Check Grabbed State
        if (nodeRoot.nodeGrabbed) {
            // Collapse
            collapse();

            // Get Position
            var pX = mapToItem(nodeTree, 0, 0).x;
            var pY = mapToItem(nodeTree, 0, 0).y;

            // Emit Node Grabbed Signal
            nodeTree.nodeGrabbed(pX, pY, nodeRoot.width, nodeRoot.height, nodeRoot.componentInfo, nodeRoot.childIndex);
            // Set Parent Node's Grabbed Child Index
            nodeRoot.parentNode.grabbedChildIndex = nodeRoot.childIndex;

        } else {

            // Emit Node Released Signal
            nodeTree.nodeReleased();
            // Reset Parent Node's Grabbed Child Index
            nodeRoot.parentNode.grabbedChildIndex = -1;

        }
    }

    onGrabbedChildIndexChanged: {
        //console.log("DNodeTreeNode.onGrabbedChildIndexChanged - grabbedChildIndex: " + grabbedChildIndex + " - path: " + title);

        // ...
    }

    // Expand
    function expand() {
        // Check Children
        if (childNodesModel.count > 0) {
            //console.log("DNodeTreeNode.expand");
            // Set Expanded
            nodeRoot.expanded = true;
        }
    }

    // Collapse
    function collapse() {
        //console.log("DNodeTreeNode.collapse");
        // Reset Expanded
        nodeRoot.expanded = false;
    }

    // Build Node Tree
    function buildNodeTree() {
        // Check Component Info
        if (nodeRoot.componentInfo !== null && nodeRoot.nodeTree !== null) {
            // Get Children Count
            var cCount = nodeRoot.componentInfo.childCount;

            //console.log("DNodeTreeNode.buildNodeTree  - componentInfo: " + nodeRoot.componentInfo.componentName + " - cCount: " + cCount);

            // Iterate Through Children
            for (var i=0; i<cCount; i++) {
                // Append Node
                appendNode(i);
            }

            // Check Child  Count
            if (cCount > 0) {
                expand();
            }
        }
    }

    // Append Node
    function appendNode() {
        //console.log("DNodeTreeNode.appendNode");

        // Get New Index
        var newIndex = childNodesModel.count;

        // Create New Node
        var newNode = nodeRoot.nodeTree.createNode(nodeRoot.componentInfo.childInfo(newIndex), nodeRoot);

        // Check New Node
        if (newNode !== null) {
            // Append To Children Node Model
            childNodesModel.append(newNode);
            // Set Width
            newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
            // Set Anchor
            newNode.anchors.right = childrenColumn.right;
            // Set Parent Node
            newNode.parentNode = nodeRoot;
            // Set Child Index
            newNode.childIndex = newIndex;

            // Update Child Indexes
            updateChildIndexes(0);

        }
    }

    // Insert Node
    function insertNode(newNodeIndex) {
        //console.log("DNodeTreeNode.insertNode - newNodeIndex: " + newNodeIndex);

        // Remove Empty Node
        removeEmptyNode();

        // Create New Node
        var newNode = nodeRoot.nodeTree.createNode(nodeRoot.componentInfo.childInfo(newNodeIndex), nodeRoot);

        // Check New Node
        if (newNode !== null) {
            // Append To Children Node Model
            childNodesModel.insert(newNodeIndex, newNode);
            // Set Width
            newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
            // Set Anchor
            newNode.anchors.right = childrenColumn.right;
            // Set Parent Node
            newNode.parentNode = nodeRoot;

            // Update Child Indexes
            updateChildIndexes(0);
        }
    }

    // Remove Node
    function removeNode(nodeIndex) {
        // Get Node Object
        var nodeObject = childNodesModel.get(nodeIndex);
        // Check Node Object
        if (nodeObject !== null) {
            //console.log("DNodeTreeNode.removeNode - nodeIndex: " + nodeIndex);

            // Remove Node Object
            childNodesModel.remove(nodeIndex);
            // Destroy
            nodeObject.destroy();
        }

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Take Node
    function takeNode(nodeIndex) {
        // Get Node Object
        var nodeObject = childNodesModel.get(nodeIndex);

        // Check Node Object
        if (nodeObject !== null) {
            console.log("DNodeTreeNode.takeNode - nodeIndex: " + nodeIndex);

            // Remove Node Object
            childNodesModel.remove(nodeIndex);

            // Update Child Indexes
            updateChildIndexes(0);

            return nodeObject;
        }

        return null;
    }

    // Move Node
    function moveNode(nodeIndex, targetIndex) {
        // Remove Empty Node First
        removeEmptyNode();

        console.log("DNodeTreeNode.moveNode - nodeIndex: " + nodeIndex + " - targetIndex: " + targetIndex);

        // Move Item
        childNodesModel.move(nodeIndex, targetIndex);

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Clear
    function clear() {
        // Iterate Child Nodes Model
        while (childNodesModel.count > 0) {
            // Remove Last Node
            removeNode(childNodesModel.count - 1);
        }
    }

    // Hide Swipe
    function hideSwipe() {
        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    // Insert EMpty Node
    function insertEmptyNode(newNodeIndex) {
        //console.log("DNodeTreeNode.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + nodeRoot.grabbedChildIndex);

        // Init Target Index
        var targetIndex = newNodeIndex;

        // Check Grabbed Child Index & If It's In The Same Node
        if (nodeRoot.grabbedChildIndex !== -1 && nodeRoot.grabbedChildIndex < newNodeIndex) {
            // Dec Target Index
            targetIndex--;
        }

        // Check Target Index
        if (targetIndex === nodeRoot.grabbedChildIndex) {
            console.warn("DNodeTreeNode.insertEmptyNode - SAME ITEM POSITION!");
            return;
        }

        //console.log("DNodeTreeNode.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + nodeRoot.grabbedChildIndex);
        // Set Current Node For Animating Height
        nodeTree.currentNode = nodeRoot;
        // Insert Empty Node
        childNodesModel.insert(newNodeIndex, emptyNode);
        // Set Child Index
        emptyNode.childIndex = newNodeIndex;
        // Show Empty Node
        emptyNode.showEmptyNode();
        // Update
        updateChildIndexes(newNodeIndex);

        // ...
    }

    // Remove Empty Node
    function removeEmptyNode() {
        // Check Empty Node Index
        if (emptyNode.childIndex >= 0) {
            //console.log("DNodeTreeNode.removeEmptyNode - childIndex: " + emptyNode.childIndex);
            // Set Current Node For Animating Height
            nodeTree.currentNode = nodeRoot;
            // Remove Empty Node
            childNodesModel.remove(emptyNode.childIndex);
            // Hide Empty Node
            emptyNode.hideEmptyNode();
            // Reset Empty Node Child Index
            emptyNode.childIndex = -1;
            // Update Child Indexes
            updateChildIndexes(0);
        } else {
            //console.warn("DNodeTreeNode.removeEmptyNode - NO CHILD INDEX!!!!");
        }
    }

    // Update Child Indexes
    function updateChildIndexes(emptyNodeIndex) {
        //console.log("DNodeTreeNode.updateChildIndexes - emptyNodeIndex: " + emptyNodeIndex);

        // Get Children Nodes Count
        var nCount = childNodesModel.count;

        // Iterate Through Child Nodes
        for (var i=emptyNodeIndex; i<nCount; i++) {
            // Set Child Indexes
            var node = childNodesModel.get(i);
            // Set Child Index
            node.childIndex = i;
        }
    }

    // Empty Node
    DNodeTreeEmptyNode {
        id: emptyNode
        width: nodeRoot.width * CONSTS.defaultNodeScaleRatio - CONSTS.defaultNodeTreeItemHeight * 0.5
        anchors.right: parent ? parent.right : undefined
        parentNode: nodeRoot
        nodeTree: nodeRoot.nodeTree

        onEmptyNodeShown: {
            // Ensure Empty Node Visible
            nodeTree.ensureEmptyNodeVisible(emptyNode);
        }
    }

    // Drop Area Container
    Item {
        id: dropAreasContainer
        width: parent.width
        height: nodeRoot.collapsedHeight
        visible: !nodeRoot.nodeGrabbed && nodeRoot.enableDropAreasVisibility //&& nodeRoot.childIndex !== nodeRoot.parentNode.grabbedChildIndex

        DropArea {
            id: topDropArea
            width: parent.width
            height: (parent.height - centerDropArea.height) * 0.5
            anchors.top: parent.top
            visible: !nodeRoot.rootNode

            onEntered: {
                //console.log("DNodeTreeNode.topDropArea.onEntered");
                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    // Restart Hover Time
                    hoverTimer.restart();
                }
            }

            onExited: {
                //console.log("DNodeTreeNode.topDropArea.onExited");
                // Stop Hover Timer
                hoverTimer.running = false;
            }
        }

        DropArea {
            id: centerDropArea
            width: parent.width
            height: parent.height * 0.6
            anchors.verticalCenter: parent.verticalCenter

            onEntered: {
                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    //console.log("DNodeTreeNode.centerDropArea.onEntered");

                    // Restart Hover Time
                    hoverTimer.restart();

                    // Check Keys - New Component
                    if (drag.keys[0] === CONSTS.newComponentDragKey || drag.keys[0] === CONSTS.childComponentDragKey) {

                        // Check Source & Source Parent Component
                        if (drag.source !== null && drag.source.componentParent !== nodeRoot.componentInfo) {
                            //console.log("DNodeTreeNode.centerDropArea.onEntered - ACCEPT!");

                            // Accept Drag
                            drag.accept();
                        }

                    }
                }

                // Set Hovering Parent Node
                nodeTree.hoverindNodeParent = nodeRoot;

                // Emit Remove Empty Node Signal
                nodeTree.removeEmptyNode();
            }

            onDropped: {
                // Check Enable Drop Area Visibility
                if (!nodeRoot.enableDropAreasVisibility) {
                    return;
                }

                // Check Drop Source
                //console.log("DNodeTreeNode.centerDropArea.onDropped - keys: " + drop.keys + " - source: " + drop.source);

                // Get Dragged Component Info
                var draggedComponentInfo = drop.source;

                // Check Drop Source & Component Info
                if (draggedComponentInfo !== null && nodeRoot.componentInfo !== null) {

                    // Check Keys - New Component
                    if (drop.keys[0] === CONSTS.newComponentDragKey) {
                        console.log("DNodeTreeNode.centerDropArea.onDropped - NEW CHILD");

                        // Check Component Info
                        if (nodeRoot.componentInfo.protoType && nodeRoot.componentInfo === draggedComponentInfo) {
                            console.warn("DNodeTreeNode.centerDropArea.onDropped - RECURSIVE!!");
                            return;
                        }

                        // TODO: More Checking

                        // Add Child To Parent Node Component
                        nodeRoot.componentInfo.addChild(draggedComponentInfo.clone());

                        // ...

                    } else if (drop.keys[0] === CONSTS.childComponentDragKey) {

                        // Check Source's Parent
                        if (draggedComponentInfo.componentParent === nodeRoot.componentInfo) {
                            console.warn("DNodeTreeNode.centerDropArea.onDropped - ALREADY A CHILD!");
                            return;
                        }

                        // Check Source
                        if (draggedComponentInfo === nodeRoot.componentInfo) {
                            console.warn("DNodeTreeNode.centerDropArea.onDropped - SAME COMPONENT!");
                            return;
                        }

                        console.log("DNodeTreeNode.centerDropArea.onDropped - CHILD DRAG");

                        // TODO: Add More Checking

                        // Move Child
                        draggedComponentInfo.componentParent.moveChild(draggedComponentInfo.componentParent, nodeTree.grabbedIndex,
                                                                       nodeRoot.componentInfo, nodeRoot.componentInfo.childCount);

                        // ...

                    } else {
                        console.warn("DNodeTreeNode.centerDropArea.onDropped - UNSUPPORTED DROP!");
                    }
                }
            }

            onExited: {
                // Stop Hover Timer
                hoverTimer.running = false;
            }
        }

        DropArea {
            id: bottomDropArea
            width: parent.width
            height: (parent.height - centerDropArea.height) * 0.5
            anchors.bottom: parent.bottom

            onEntered: {
                //console.log("DNodeTreeNode.bottomDropArea.onEntered");
                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    // Restart Hover Time
                    hoverTimer.restart();
                }
            }

            onExited: {
                //console.log("DNodeTreeNode.bottomDropArea.onExited");
                // Stop Hover Timer
                hoverTimer.running = false;
            }
        }
    }

    // Node Container
    Item {
        id: nodeContainer

        width: parent.width
        height: nodeRoot.collapsedHeight
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right

        DMouseArea {
            id: expandButton

            width: height * 0.5
            height: CONSTS.defaultNodeTreeItemHeight
            anchors.verticalCenter: parent.verticalCenter
            visible: nodeRoot.componentInfo && nodeRoot.componentInfo.childCount > 0

            onPressed: {
                // Set Current Node For Animating Height
                nodeTree.currentNode = nodeRoot;
            }

            onClicked: {
                // Check If Expanded
                if (!nodeRoot.expanded) {
                    // Set Expanded
                    nodeRoot.expand();
                } else {
                    // Restore
                    nodeRoot.collapse();
                }
            }

            DText {
                anchors.centerIn: parent
                scale: parent.pressed ? DStyle.pressedScale : 1.0
                rotation: nodeRoot.expanded ? 135 : 0
                Behavior on rotation { DAnimation { } }
                font.pixelSize: DStyle.fontSizeS
                text: "❖"
            }
        }

        // Node Rect
        DRectangle {
            id: nodeRect
            width: parent.width - expandButton.width
            height: CONSTS.defaultNodeTreeItemHeight
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            border.color: {
                // Check Center Drop Area
                if (centerDropArea.containsDrag) {
                    return "yellow";
                }

                return propertiesController.focusedComponent === nodeRoot.componentInfo ? DStyle.colorBorder : DStyle.colorBorderNoFocus;
            }

            smooth: true
            opacity: nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.layerVisible ? 1.0 : 0.5 : 0.0
            Behavior on opacity { DFadeAnimation { } }

            // Node Icon
            DMaskedImage {
                id: nodeIcon
                width: parent.height - DStyle.defaultMargin * 2
                height: width
                anchors.left: parent.left
                anchors.leftMargin: DStyle.defaultMargin
                anchors.verticalCenter: parent.verticalCenter

                imageSource: componentInfo ? CONSTS.nodeIconTypeMap[componentInfo.componentCategory] : ""
            }

            // Title Label
            DText {
                id: titleLabel
                anchors.left: nodeIcon.right
                anchors.leftMargin: DStyle.defaultMargin
                anchors.right: visibilityButton.left
                anchors.rightMargin: DStyle.defaultMargin
                anchors.verticalCenter: parent.verticalCenter
                text: nodeRoot.title
                wrapMode: Text.NoWrap
                elide: Text.ElideMiddle
            }

            // Node Mouse Area
            DMouseArea {
                id: nodeMouseArea
                anchors.fill: parent

                onPressed: {
                    // Check Node Tree
                    if (nodeTree) {
                        // Emit Node Pressed Signal
                        nodeTree.nodePressed(Math.round(mouse.x), Math.round(mouse.y), nodeMouseArea);
                        // Set Current Node For Animating Height
                        //nodeTree.currentNode = nodeRoot;
                    }
                }

                onClicked: {
                    // Set Current Node For Animating Height
                    nodeTree.currentNode = nodeRoot;
                    // Set Focused Component
                    propertiesController.focusedComponent = nodeRoot.componentInfo;
                }

                onDoubleClicked: {
                    // Check If Expanded
                    if (!nodeRoot.expanded) {
                        // Set Expanded
                        nodeRoot.expand();
                    } else {
                        // Collapse
                        nodeRoot.collapse();
                    }
                }

                onPressAndHold: {
                    // Check If Root Node
                    if (!nodeRoot.rootNode) {
                        console.log("DNodeTreeNode.nodeMouseArea.onPressAndHold - START DRAG");
                        // Collapse
                        nodeRoot.collapse();
                        // Set Drop Areas Visibility
                        nodeRoot.enableDropAreasVisibility = false;
                        // Set Grabbed
                        nodeRoot.nodeGrabbed = true;
                    }
                }

                onReleased: {
                    //console.log("DNodeTreeNode.nodeMouseArea.onReleased");
                    // Reset Grabbed
                    nodeRoot.nodeGrabbed = false;
                    // Set Drop Areas Visibility
                    nodeRoot.enableDropAreasVisibility = true;
                }

                onCanceled: {
                    //console.log("DNodeTreeNode.nodeMouseArea.onCanceled");
                    // Reset Grabbed
                    nodeRoot.nodeGrabbed = false;
                }
            }

            // Layer Visibility Button
            DMouseArea {
                id: visibilityButton
                width: parent.height * 0.5
                height: width
                anchors.right: parent.right
                anchors.rightMargin: DStyle.defaultMargin * 2
                anchors.verticalCenter: parent.verticalCenter
                visible: nodeRoot.enableLayerVisibilityButton

                DMaskedImage {
                    anchors.fill: parent
                    anchors.margins: 3
                    imageSource: "qrc:/assets/icons/eye.png"
                    scale: parent.pressed ? DStyle.pressedScale : 1.0
                }

                onClicked:  {
                    // Check Component Info
                    if (nodeRoot.componentInfo !== null) {
                        // Toggle Layer Visibility
                        nodeRoot.componentInfo.layerVisible = !nodeRoot.componentInfo.layerVisible;
                    }
                }
            }

            // Swipe Gesture Area
            DSwipeGesture {
                id: swipeGesture
                anchors.fill: parent
                visible: !nodeRoot.rootNode && nodeRoot.componentInfo !== null
                onActionButtonClicked: {
                    // Check Component Info
                    if (nodeRoot.componentInfo !== null) {
                        // Remove From Parent
                        nodeRoot.componentInfo.removeFromParent();
                    }
                }
            }
        }
    }

    // Child Nodes Object Model
    ObjectModel {
        id: childNodesModel
    }

    // Children Column
    Column {
        id: childrenColumn
        width: parent.width
        anchors.right: parent.right
        anchors.top: nodeContainer.bottom

        Repeater {
            id: nodeRepeater
            model: childNodesModel
        }

        move: Transition {
            PropertyAnimation { properties: "y"; duration: DStyle.animDuration }
        }
    }

    // Hover Timer
    Timer {
        id: hoverTimer
        interval: 200

        onTriggered: {
            // Check Top Area
            if (topDropArea.containsDrag) {
                //console.log("DNodeTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - TOP");

                // Check Parent Node
                if (parentNode !== null) {
                    // Insert Empty Node
                    parentNode.insertEmptyNode(childIndex);
                }

            // Check Center Drop Area
            } else if (centerDropArea.containsDrag) {
                //console.log("DNodeTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - CENTER");

                // Expand
                expand();

            // Check Bottom Drop Area
            } else if (bottomDropArea.containsDrag) {
                //console.log("DNodeTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - BOTTOM");

                // Check Parent Node
                if (parentNode !== null) {
                    // Insert Empty Node
                    parentNode.insertEmptyNode(childIndex + 1);
                }
            } else {

                console.warn("DNodeTreeNode.hoverTimer.onTriggered - UNSUPPORTED EVENT!!");

            }
        }
    }
}
