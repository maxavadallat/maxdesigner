import QtQuick 2.7
import QtQml.Models 2.2

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: nodeRoot

    width: 300
    height: collapsedHeight

    // Height Behavior
    Behavior on height {
        SequentialAnimation {
            DAnimation {
                duration: transitionEditorRoot !== null && transitionEditorRoot.currentNode === nodeRoot ? DStyle.animDuration : 0
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
    // Node Animation Base
    property string nodeAnimBase: componentInfo !== null ? componentInfo.animBase() : ""
    // Node is Root
    property bool isRootNode: false
    // Node Main Title Text
    property string mainTitle: nodeAnimBase

    // Node Property - Target
    property string nodeTarget: {
        if (componentInfo === null) {
            return "";
        }

        // Get Property
        var temp = componentInfo.propertyValue("target")

        return temp !== undefined ? temp : "";
    }

    // Node Property - Properties:
    property string nodeProperties: {
        if (componentInfo === null) {
            return "";
        }
        // Check Anim Base
        if (nodeAnimBase === "PropertyAction") {
            // Get Property
            var pTemp = componentInfo.propertyValue("property");

            return pTemp !== undefined ? pTemp : "";
        }

        // Get Property
        var psTemp = componentInfo.propertyValue("properties");

        return psTemp !== undefined ? psTemp : "";
    }

    // Node Property - Value
    property string nodeValue: {
        if (componentInfo === null) {
            return "";
        }

        // Get Property
        var pTemp = componentInfo.propertyValue("value");

        return pTemp !== undefined ? pTemp : "";
    }

    // Node Property - Value From
    property string nodeFromValue: {
        if (componentInfo === null) {
            return "";
        }

        // Get Property
        var pTemp = componentInfo.propertyValue("from");

        return pTemp !== undefined ? pTemp : "";
    }

    // Node Property - Value To
    property string nodeToValue: {
        if (componentInfo === null) {
            return "";
        }

        // Get Property
        var pTemp = componentInfo.propertyValue("to");

        return pTemp !== undefined ? pTemp : "";
    }

    // Node Property - Duration
    property string nodeDuration: {
        if (componentInfo === null) {
            return "";
        }

        // Get Property
        var pTemp = componentInfo.propertyValue("duration");

        return pTemp !== undefined ? pTemp : "";
    }

    // ...

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
    // Transition Editor Root
    property QtObject transitionEditorRoot: null
    // Parent Node
    property QtObject parentNode: null
    // Component Info Connections
    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onAnimationAdded: {
            console.log("DTransitionTreeNode.componentInfoConnections.onAnimationAdded - aIndex: " + aIndex);
            // Insert Node
            insertNode(aIndex);
            // Expand
            expand();
        }

        onAnimationMoved: {
            console.log("DTransitionTreeNode.componentInfoConnections.onAnimationMoved - parent: " + aParentComponent.componentPath + " - aIndex: " + aIndex + " - aTarget: " + aTargetComponent.componentPath + " - aTargetIndex: " + aTargetIndex);

            // Check Parent & Target Component
            if (aParentComponent === aTargetComponent) {
                // Move Node
                moveNode(aIndex, aTargetIndex);
            } else {
                // Remove Node
                removeNode(aIndex);
                // Check Hovering Node Parent
                if (transitionEditorRoot.hoveringNodeParent) {
                    // Insert Node
                    transitionEditorRoot.hoveringNodeParent.insertNode(aTargetIndex);
                    // Set Current Node For Animating Height
                    transitionEditorRoot.currentNode = transitionEditorRoot.hoveringNodeParent;
                    // Expand
                    transitionEditorRoot.hoveringNodeParent.expand();
                    // Reset Hovering Parent Node
                    transitionEditorRoot.hoveringNodeParent = null;
                } else {
                    console.log("DTransitionTreeNode.componentInfoConnections.onChildMoved - NULL HOVERING PARENT NODE!!");
                }
            }
        }

        onAnimationRemoved: {
            console.log("DTransitionTreeNode.componentInfoConnections.onAnimationRemoved - aIndex: " + aIndex);
            // Remove Node
            removeNode(aIndex);

            // Check Children Column
            if (animNodesModel.count === 0) {
                // Collapse
                collapse();
            }
        }

        onComponentPropertyChanged: {
            //console.log("DTransitionTreeNode.componentInfoConnections.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // ...

            // Emit Component Info Changed Signal To Update Title Values - TODO: Have a better solution!
            componentInfoChanged();
        }
    }
    // Transition Editor Connections
    property Connections transitionEditorConnections: Connections {
        target: transitionEditorRoot

        onRemoveEmptyNode: {
            // Remove Empty Node
            removeEmptyNode();
        }
    }
    // Drop Areas Visible
    property bool dropAreasVisible: transitionEditorRoot ? transitionEditorRoot.nodeGrabbedState : false
    // Enable Drop Areas Visibility
    property bool enableDropAreasVisibility: !nodeGrabbed
    // Drop OK
    property bool dropOK: false

    opacity: nodeGrabbed ? 0.5 : 1.0

    clip: true

    // On Component Completed
    Component.onCompleted: {
        // Set Node Init
        nodeRoot.nodeInit = true;

        // ...
    }

    // On Component Destruction
    Component.onDestruction: {
        // Clear
        clear();
    }

    // On Child Index Changed Slot
    onChildIndexChanged: {
        //console.log("DTransitionTreeNode.onChildIndexChanged - childIndex: " + childIndex);

        // ...
    }

    // On Component Info Changed Slot
    onComponentInfoChanged: {
        //console.log("DTransitionTreeNode.onComponentInfoChanged - componentName: " + (nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.componentName  + " - animsCount: " + nodeRoot.componentInfo.animsCount : "NULL"));
        // Clear
        nodeRoot.clear();
        // Build Node tree
        nodeRoot.buildNodeTree();
    }

    // On Expanded State Changd Slot
    onExpandedChanged: {
        //console.log("DTransitionTreeNode.onExpandedChanged - expanded: " + expanded + " - childIndex: " + childIndex);
        // Check If Expanded
        if (nodeRoot.expanded) {
            // Set Height
            nodeRoot.height = Qt.binding(function() {
                // Check Children
                if (animNodesModel.count > 0) {
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
        //console.log("DTransitionTreeNode.onNodeGrabbedChanged - nodeGrabbed: " + nodeGrabbed + " - childIndex: " + childIndex);

        // Check Grabbed State
        if (nodeRoot.nodeGrabbed) {
            // Collapse
            collapse();

            // Set Grabbed Node Parent
            nodeRoot.transitionEditorRoot.grabbedNodeParent = nodeRoot.parentNode;

            // Get Position
            var pX = mapToItem(transitionEditorRoot, 0, 0).x;
            var pY = mapToItem(transitionEditorRoot, 0, 0).y;

            // Emit Node Grabbed Signal
            transitionEditorRoot.nodeGrabbed(pX, pY, nodeRoot.width, nodeRoot.height, nodeRoot.componentInfo, nodeRoot.childIndex);

            // Check Parent Node
            if (nodeRoot.parentNode !== null) {
                // Set Parent Node's Grabbed Child Index
                nodeRoot.parentNode.grabbedChildIndex = nodeRoot.childIndex;
            } else {
                // Set Transition Editor Root Grabbed Child Index
                nodeRoot.transitionEditorRoot.grabbedChildIndex = nodeRoot.childIndex;
            }

        } else {
            // Emit Node Released Signal
            transitionEditorRoot.nodeReleased();
            // Check Parent Node
            if (nodeRoot.parentNode !== null) {
                // Reset Parent Node's Grabbed Child Index
                nodeRoot.parentNode.grabbedChildIndex = -1;
            } else {
                // Set Transition Editor Root Grabbed Child Index
                nodeRoot.transitionEditorRoot.grabbedChildIndex = -1;
            }
        }
    }

    onGrabbedChildIndexChanged: {
        //console.log("DTransitionTreeNode.onGrabbedChildIndexChanged - grabbedChildIndex: " + grabbedChildIndex + " - path: " + title);

        // ...
    }

    Keys.onReleased: {
        // Switch Event Key
        switch (event.key) {
            case Qt.Key_Escape:
                // Reset Focus
                nodeRoot.focus = false;
                // Emit Node Focus Lost
                transitionEditorRoot.nodeFocusLost();
                // Reset Current Node
                transitionEditorRoot.currentNode = null;
            break;
        }
    }

    // Expand
    function expand() {
        // Check Children
        if (animNodesModel.count > 0) {
            //console.log("DTransitionTreeNode.expand");
            // Set Expanded
            nodeRoot.expanded = true;
        }
    }

    // Collapse
    function collapse() {
        //console.log("DTransitionTreeNode.collapse");
        // Reset Expanded
        nodeRoot.expanded = false;
    }

    // Build Node Tree
    function buildNodeTree() {
        // Check Component Info
        if (nodeRoot.componentInfo !== null) {
            // Set Title
            //nodeRoot.title = nodeRoot.componentInfo.componentPath;

            // Get Animations Count
            var cCount = nodeRoot.componentInfo.animsCount;

            console.log("DTransitionTreeNode.buildNodeTree  - componentInfo: " + nodeRoot.componentInfo.componentName + " - cCount: " + cCount);

            // Iterate Through Children
            for (var i=0; i<cCount; i++) {
                // Append Node
                appendNode();
            }

            // Check Child  Count
            if (cCount > 0) {
                expand();
            }
        }
    }

    // Append Node
    function appendNode() {
        // Check Transjition Editor Root
        if (nodeRoot.transitionEditorRoot !== null && nodeRoot.componentInfo !== null) {
            // Get New Index
            var newIndex = animNodesModel.count;

            console.log("DTransitionTreeNode.appendNode - newIndex: " + newIndex);

            // Create New Node
            var newNode = nodeRoot.transitionEditorRoot.createNode(nodeRoot.componentInfo.animInfo(newIndex), nodeRoot);

            // Check New Node
            if (newNode !== null) {
                // Append To Children Node Model
                animNodesModel.append(newNode);
                // Set Width
                newNode.width = Qt.binding(function() { return nodeRoot.width - 24; });
                //newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
                // Set Anchor
                newNode.anchors.right = childrenColumn.right;
                // Set Parent Node
                newNode.parentNode = nodeRoot;
                // Set Child Index
                newNode.childIndex = newIndex;
            }
        }
    }

    // Insert Node
    function insertNode(newNodeIndex) {
        // Remove Empty Node
        removeEmptyNode();

        console.log("DTransitionTreeNode.insertNode - newNodeIndex: " + newNodeIndex);

        // Create New Node
        var newNode = nodeRoot.transitionEditorRoot.createNode(nodeRoot.componentInfo.animInfo(newNodeIndex), nodeRoot);

        // Check New Node
        if (newNode !== null) {
            // Append To Children Node Model
            animNodesModel.insert(newNodeIndex, newNode);
            // Set Width
            newNode.width = Qt.binding(function() { return nodeRoot.width - 24; });
            //newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
            // Set Anchor
            newNode.anchors.right = childrenColumn.right;
            // Set Parent Node
            newNode.parentNode = nodeRoot;
            // Set Child Index
            //newNode.childIndex = newNode.index;
            // Hide Swipe
            //newNode.hideSwipe();

            // Update Child Indexes
            updateChildIndexes(0);
        }
    }

    // Remove Node
    function removeNode(nodeIndex) {
        // Get Node Object
        var nodeObject = animNodesModel.get(nodeIndex);
        // Check Node Object
        if (nodeObject !== null) {
            console.log("DTransitionTreeNode.removeNode - nodeIndex: " + nodeIndex);

            // Remove Node Object
            animNodesModel.remove(nodeIndex);
            // Destroy
            nodeObject.destroy();
        }

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Take Node
    function takeNode(nodeIndex) {
        // Get Node Object
        var nodeObject = animNodesModel.get(nodeIndex);

        // Check Node Object
        if (nodeObject !== null) {
            console.log("DTransitionTreeNode.takeNode - nodeIndex: " + nodeIndex);

            // Remove Node Object
            animNodesModel.remove(nodeIndex);

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

        console.log("DTransitionTreeNode.moveNode - nodeIndex: " + nodeIndex + " - targetIndex: " + targetIndex);

        // Move Item
        animNodesModel.move(nodeIndex, targetIndex);

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Clear
    function clear() {
        // Check Model Count
        if (animNodesModel.count > 0) {
            console.log("DTransitionTreeNode.clear");

            // Iterate Child Nodes Model
            while (animNodesModel.count > 0) {
                // Remove Last Node
                removeNode(animNodesModel.count - 1);
            }
        }
    }

    // Hide Swipe
    function hideSwipe() {
        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    // Insert Empty Node
    function insertEmptyNode(newNodeIndex) {
        console.log("DTransitionTreeNode.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + nodeRoot.grabbedChildIndex);

        // Init Target Index
        var targetIndex = newNodeIndex;

        // Check Grabbed Child Index & If It's In The Same Node
        if (nodeRoot.grabbedChildIndex !== -1 && nodeRoot.grabbedChildIndex < newNodeIndex) {
            // Dec Target Index
            targetIndex--;
        }

        // Check Target Index
        if (targetIndex === nodeRoot.grabbedChildIndex) {
            console.warn("DTransitionTreeNode.insertEmptyNode - SAME ITEM POSITION!");
            return;
        }

        //console.log("DTransitionTreeNode.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + nodeRoot.grabbedChildIndex);
        // Set Current Node For Animating Height
        transitionEditorRoot.currentNode = nodeRoot;
        // Insert Empty Node
        animNodesModel.insert(newNodeIndex, emptyNode);
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
            console.log("DTransitionTreeNode.removeEmptyNode - childIndex: " + emptyNode.childIndex);
            // Set Current Node For Animating Height
            nodeRoot.transitionEditorRoot.currentNode = nodeRoot;
            // Remove Empty Node
            animNodesModel.remove(emptyNode.childIndex);
            // Hide Empty Node
            emptyNode.hideEmptyNode();
            // Reset Empty Node Child Index
            emptyNode.childIndex = -1;
            // Update Child Indexes
            updateChildIndexes(0);
        } else {
            //console.warn("DTransitionTreeNode.removeEmptyNode - NO CHILD INDEX!!!!");
        }
    }

    // Update Child Indexes
    function updateChildIndexes(emptyNodeIndex) {
        //console.log("DTransitionTreeNode.updateChildIndexes - emptyNodeIndex: " + emptyNodeIndex);

        // Get Children Nodes Count
        var nCount = animNodesModel.count;

        // Iterate Through Child Nodes
        for (var i=emptyNodeIndex; i<nCount; i++) {
            // Set Child Indexes
            var node = animNodesModel.get(i);
            // Set Child Index
            node.childIndex = i;
        }
    }

    // Empty Node
    DTransitionTreeEmptyNode {
        id: emptyNode
        width: nodeRoot.width - 24 - CONSTS.defaultNodeTreeItemHeight * 0.5
        anchors.right: parent ? parent.right : undefined
        parentNode: nodeRoot
        transitionEditorRoot: nodeRoot.transitionEditorRoot
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
            visible: !nodeRoot.isRootNode

            onEntered: {
                //console.log("DTransitionTreeNode.topDropArea.onEntered");
                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    // Emit Remove Empty Node Signal to Hide Other Empty Nodes
                    nodeRoot.transitionEditorRoot.removeEmptyNode();
                    // Restart Hover Time
                    hoverTimer.restart();
                }
            }

            onExited: {
                //console.log("DTransitionTreeNode.topDropArea.onExited");
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
                // Emit Remove Empty Node Signal
                nodeRoot.transitionEditorRoot.removeEmptyNode();

                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    //console.log("DTransitionTreeNode.centerDropArea.onEntered");

                    // Restart Hover Time
                    hoverTimer.restart();

                    // Reset Drop OK
                    nodeRoot.dropOK = false;

                    // Check Keys - New Component
                    if ((drag.keys[0] === CONSTS.newComponentDragKey || drag.keys[0] === CONSTS.childComponentDragKey) && drag.source !== null) {

                        // Check Source & Source Parent Component
                        if ((nodeRoot.nodeAnimBase === "ParallelAnimation" || nodeRoot.nodeAnimBase === "SequentialAnimation") && drag.source.componentCategory === "Animation") {
                            //console.log("DTransitionTreeNode.centerDropArea.onEntered - ACCEPT!");

                            // Set Drop OK
                            nodeRoot.dropOK = true;

                            // Accept Drag
                            drag.accept();
                        }
                    }
                }

                // Set Hovering Parent Node
                nodeRoot.transitionEditorRoot.hoveringNodeParent = nodeRoot;
            }

            onDropped: {
                // Check Enable Drop Area Visibility
                if (!nodeRoot.enableDropAreasVisibility) {
                    return;
                }

                // Check Drop Source
                //console.log("DTransitionTreeNode.centerDropArea.onDropped - keys: " + drop.keys + " - source: " + drop.source);

                // Get Dragged Component Info
                var draggedComponentInfo = drop.source;

                // Check Drop Source & Component Info
                if (draggedComponentInfo !== null && nodeRoot.componentInfo !== null) {

                    // Check Keys - New Component
                    if (drop.keys[0] === CONSTS.newComponentDragKey && draggedComponentInfo.componentCategory === "Animation") {
                        console.log("DTransitionTreeNode.centerDropArea.onDropped - NEW CHILD");

                        // Check Component Info
                        if (nodeRoot.componentInfo.protoType && nodeRoot.componentInfo === draggedComponentInfo) {
                            console.warn("DTransitionTreeNode.centerDropArea.onDropped - RECURSIVE!!");
                            return;
                        }

                        // TODO: More Checking

                        // Add Child To Parent Node Component
                        nodeRoot.componentInfo.addChild(draggedComponentInfo.clone());

                        // ...

                    } else if (drop.keys[0] === CONSTS.childComponentDragKey) {

                        // Check Source's Parent
                        if (draggedComponentInfo.componentParent === nodeRoot.componentInfo) {
                            console.warn("DTransitionTreeNode.centerDropArea.onDropped - ALREADY A CHILD!");
                            return;
                        }

                        // Check Source
                        if (draggedComponentInfo === nodeRoot.componentInfo) {
                            console.warn("DTransitionTreeNode.centerDropArea.onDropped - SAME COMPONENT!");
                            return;
                        }

                        console.log("DTransitionTreeNode.centerDropArea.onDropped - CHILD DRAG");

                        // TODO: Add More Checking

                        // Init Grabbed Transition Node Component
                        var grabbedTransitionComponent = null;

                        // Take Node

                        // Check Node Parent
                        if (nodeRoot.transitionEditorRoot.grabbedNodeParent === nodeRoot.transitionEditorRoot) {
                            // Take Transition Node
                            grabbedTransitionComponent = nodeRoot.transitionEditorRoot.componentTransition.takeNode(nodeRoot.transitionEditorRoot.grabbedIndex);
                        } else {
                            // Take Transition Node
                            grabbedTransitionComponent = nodeRoot.transitionEditorRoot.grabbedNodeParent.componentInfo.takeChild(nodeRoot.transitionEditorRoot.grabbedIndex, false);
                        }

                        // Append Node
                        nodeRoot.componentInfo.addChild(grabbedTransitionComponent);

                    } else {
                        console.warn("DTransitionTreeNode.centerDropArea.onDropped - UNSUPPORTED DROP!");
                    }
                }

                // Reset Drop OK
                nodeRoot.dropOK = false;

//                // Reset Hovering Parent Node
//                transitionEditorRoot.hoveringNodeParent = null;
            }

            onExited: {
                // Stop Hover Timer
                hoverTimer.running = false;
                // Reset Drop OK
                nodeRoot.dropOK = false;
            }
        }

        DropArea {
            id: bottomDropArea
            width: parent.width
            height: (parent.height - centerDropArea.height) * 0.5
            anchors.bottom: parent.bottom

            onEntered: {
                //console.log("DTransitionTreeNode.bottomDropArea.onEntered");
                // Check Enable Drop Area Visibility
                if (nodeRoot.enableDropAreasVisibility) {
                    // Emit Remove Empty Node Signal to Hide Other Empty Nodes
                    nodeRoot.transitionEditorRoot.removeEmptyNode();
                    // Restart Hover Time
                    hoverTimer.restart();
                }
            }

            onExited: {
                //console.log("DTransitionTreeNode.bottomDropArea.onExited");
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
            visible: nodeRoot.componentInfo && nodeRoot.componentInfo.animsCount > 0

            onPressed: {
                // Set Current Node For Animating Height
                nodeRoot.transitionEditorRoot.currentNode = nodeRoot;
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
                    // Check If Drop OK
                    if (nodeRoot.dropOK) {
                        return DStyle.colorBorderHoverOK;
                    }

                    return DStyle.colorBorderHoverNOK;
                }

                //return propertiesController.focusedComponent === nodeRoot.componentInfo ? DStyle.colorBorder : DStyle.colorBorderNoFocus;
                return nodeRoot.transitionEditorRoot !== null && nodeRoot.transitionEditorRoot.currentNode === nodeRoot ? DStyle.colorBorder : DStyle.colorBorderNoFocus;
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

            // Title Row
            Row {
                id: titleRow

                anchors.left: nodeIcon.right
                anchors.leftMargin: DStyle.defaultMargin
                anchors.right: parent.right
                anchors.rightMargin: DStyle.defaultMargin * 2
                anchors.verticalCenter: parent.verticalCenter

                spacing: DStyle.defaultSpacing

                clip: true

                // Title Label
                DText {
                    id: mainTitleLabel
                    anchors.verticalCenter: parent.verticalCenter
                    wrapMode: Text.NoWrap
                    text: nodeRoot.mainTitle
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeTarget !== ""
                    text: "target:"
                }

                // Target
                DText {
                    id: targetLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeTarget !== ""
                    text: nodeRoot.nodeTarget
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeProperties !== ""
                    text: "properties:"
                }

                // Properties
                DText {
                    id: propertiesLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeProperties !== ""
                    text: nodeRoot.nodeProperties
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeValue !== ""
                    text: "value:"
                }

                // Value
                DText {
                    id: valueLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeValue !== ""
                    text: nodeRoot.nodeValue
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeFromValue !== ""
                    text: "from:"
                }

                // From Value
                DText {
                    id: fromLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeFromValue !== ""
                    text: nodeRoot.nodeFromValue
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeToValue !== ""
                    text: "to:"
                }

                // To Value
                DText {
                    id: toLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeToValue !== ""
                    text: nodeRoot.nodeToValue
                }

                DText {
                    anchors.verticalCenter: parent.verticalCenter
                    visible: nodeRoot.nodeDuration !== ""
                    text: "duration:"
                }

                // Duration
                DText {
                    id: durationLabel
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    wrapMode: Text.NoWrap
                    visible: nodeRoot.nodeDuration !== ""
                    text: nodeRoot.nodeDuration
                }

                // ...

            }

            // Node Mouse Area
            DMouseArea {
                id: nodeMouseArea
                anchors.fill: parent

                onPressed: {
                    // Check Transition Editor Root
                    if (nodeRoot.transitionEditorRoot !== null) {
                        // Emit Node Pressed Signal
                        nodeRoot.transitionEditorRoot.nodePressed(Math.round(mouse.x), Math.round(mouse.y), nodeMouseArea);
                        // Set Current Node For Animating Height
                        //transitionEditorRoot.currentNode = nodeRoot;
                    }
                }

                onClicked: {
                    // Set Current Node For Animating Height
                    nodeRoot.transitionEditorRoot.currentNode = nodeRoot;
                    // Set Focus
                    nodeRoot.focus = true;
                }

                onDoubleClicked: {
                    // Check Node Anim Base
                    if (nodeRoot.nodeAnimBase === "ParallelAnimation" || nodeRoot.nodeAnimBase === "SequentialAnimation") {
                        // Check If Expanded
                        if (!nodeRoot.expanded) {
                            // Set Expanded
                            nodeRoot.expand();
                        } else {
                            // Collapse
                            nodeRoot.collapse();
                        }
                    } else {
                        // Check Transition Editor Root
                        if (nodeRoot.transitionEditorRoot !== null) {
                            // Emit Edit Transition Node
                            nodeRoot.transitionEditorRoot.editTransitionNode(nodeRoot.childIndex);
                        }
                    }
                }

                onPressAndHold: {
                    // Check If Root Node
                    if (!nodeRoot.isRootNode) {
                        console.log("DTransitionTreeNode.nodeMouseArea.onPressAndHold - START DRAG");
                        // Collapse
                        nodeRoot.collapse();
                        // Set Drop Areas Visibility
                        nodeRoot.enableDropAreasVisibility = false;
                        // Set Grabbed
                        nodeRoot.nodeGrabbed = true;
                    }
                }

                onReleased: {
                    //console.log("DTransitionTreeNode.nodeMouseArea.onReleased");
                    // Reset Grabbed
                    nodeRoot.nodeGrabbed = false;
                    // Set Drop Areas Visibility
                    nodeRoot.enableDropAreasVisibility = true;
                }

                onCanceled: {
                    //console.log("DTransitionTreeNode.nodeMouseArea.onCanceled");
                    // Reset Grabbed
                    nodeRoot.nodeGrabbed = false;
                }
            }

            // Swipe Gesture Area
            DSwipeGesture {
                id: swipeGesture
                anchors.fill: parent
                visible: !nodeRoot.isRootNode && nodeRoot.componentInfo !== null

                onActionButtonClicked: {
                    // Check Parent Node
                    if (nodeRoot.componentInfo !== null) {
                        // Remove From Parent
                        nodeRoot.componentInfo.removeFromParent();
                    } else {
                        console.warn("DTransitionTreeNode.swipeGesture.onActionButtonClicked - NULL COMPONENT INFO!!");
                    }
                }
            }
        }
    }

    // Child Nodes Object Model
    ObjectModel {
        id: animNodesModel
    }

    // Children Column
    Column {
        id: childrenColumn
        width: parent.width
        anchors.right: parent.right
        anchors.top: nodeContainer.bottom

        Repeater {
            id: nodeRepeater
            model: animNodesModel
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
                //console.log("DTransitionTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - TOP");

                // Check Parent Node
                if (nodeRoot.parentNode !== null) {
                    // Insert Empty Node
                    nodeRoot.parentNode.insertEmptyNode(childIndex);
                }

            // Check Center Drop Area
            } else if (centerDropArea.containsDrag) {
                //console.log("DTransitionTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - CENTER");

                // Expand
                expand();

            // Check Bottom Drop Area
            } else if (bottomDropArea.containsDrag) {
                //console.log("DTransitionTreeNode.hoverTimer.onTriggered - childIndex: " + nodeRoot.childIndex + " - BOTTOM");

                // Check Parent Node
                if (nodeRoot.parentNode !== null) {
                    // Insert Empty Node
                    nodeRoot.parentNode.insertEmptyNode(childIndex + 1);
                }
            } else {

                console.warn("DTransitionTreeNode.hoverTimer.onTriggered - UNSUPPORTED EVENT!!");

            }
        }
    }
}
