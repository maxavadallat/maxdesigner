import QtQuick 2.0
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeRoot

    width: 300
    height: CONSTS.defaultNodeTreeItemHeight

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

    property ComponentInfo componentInfo: null

    property bool rootNode: false

    property string title: componentInfo !== null ? componentInfo.componentPath : "Title test"

    property int childIndex: -1

    default property alias childrenContainerAlias: childrenColumn.children

    property bool expanded: false

    property bool nodeInit: false

    property bool grabbed: false

    property bool topHovered: false
    property bool centerHovered: false
    property bool bottomHovered: false

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onChildAdded: {
            // Append Node
            //appendNode(aIndex);

            // Insert Node
            insertNode(aIndex);

            // Expand
            expand();
        }

        onChildMoved: {

            // ...

        }

        onChildRemoved: {
            // Remove Node
            removeNode(aIndex);
            // Check Children Column
            if (childrenColumn.children.length === 0) {
                // Collapse
                collapse();
            }
        }
    }

    // Parent Node Tree
    property var nodeTree: null

    property bool hideDropAreas: false

    property var childTemp: []

    property bool enableLayerVisibilityButton: true

    opacity: grabbed ? 0.5 : 1.0

    clip: true

    Component.onCompleted: {
        // Set Node Init
        nodeRoot.nodeInit = true;

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
        // Check If Expanded
        if (nodeRoot.expanded) {
            // Set Height
            nodeRoot.height = Qt.binding(function() {
                // Check Children
                if (childrenColumn.children.length > 0) {
                    return CONSTS.defaultNodeTreeItemHeight + childrenColumn.height + DStyle.defaultSpacing;
                }

                return CONSTS.defaultNodeTreeItemHeight;
            });
        } else {
            // Set Height
            nodeRoot.height = CONSTS.defaultNodeTreeItemHeight;
        }

        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    onGrabbedChanged: {
        // Check Grabbed State
        if (nodeRoot.grabbed) {
            // Collapse
            collapse();
            // Get Position
            var pX = mapToItem(nodeTree, 0, 0).x;
            var pY = mapToItem(nodeTree, 0, 0).y;
            // Emit Node Grabbed Signal
            nodeTree.nodeGrabbed(pX, pY, nodeRoot.width, nodeRoot.height, nodeRoot.componentInfo);
        } else {
            // Emit Node Released Signal
            nodeTree.nodeReleased();
        }
    }

    // Expand
    function expand() {
        // Check Children
        if (childrenColumn.children.length > 0) {
            // Set Expanded
            nodeRoot.expanded = true;
        }
    }

    // Collapse
    function collapse() {
        // Reset Expanded
        nodeRoot.expanded = false;
    }

    // Build Node Tree
    function buildNodeTree() {
        // Check Component Info
        if (nodeRoot.componentInfo !== null && nodeRoot.nodeTree !== null) {
            // Set Title
            //nodeRoot.title = nodeRoot.componentInfo.componentPath;

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
    function appendNode(newNodeIndex) {
        // Create New Node
        var newNode = nodeRoot.nodeTree.createNode(nodeRoot.componentInfo.childInfo(newNodeIndex), childrenColumn);

        // Check New Node
        if (newNode !== null) {
            // Set Width
            newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
            // Set Anchor
            newNode.anchors.right = childrenColumn.right;
            // Hide Swipe
            //newNode.hideSwipe();
        }
    }

    // Insert Node
    function insertNode(newNodeIndex) {
        // Iterate Through Child Nodes
        for (var i=childrenColumn.children.length-1; i>=newNodeIndex; i--) {
            // Take Children Out Temporarily
            childTemp.push(childrenColumn.children[i]);
            // Set Parent Temporarily
            childTemp[childTemp.length-1].parent = nodeRoot;
        }

        // Append Node
        appendNode(newNodeIndex);

        // Add Temporarily Removed Items To ChildrenColumn
        while (childTemp.length > 0) {
            // Get Last Item
            var lastItem = childTemp.pop();
            // Set Parent
            lastItem.parent = childrenColumn;
        }
    }

    // Remove Node
    function removeNode(nodeIndex) {
        // Destroy Node
        childrenColumn.children[nodeIndex].destroy();
    }

    // Clear
    function clear() {
        // Get Children Column Children Count
        var cccCount = childrenColumn.children.length;

        // Check Count
        if (cccCount > 0) {
            //console.log("DNodeTreeNode.clear  - cccCount: " + cccCount);

            // Iterate Through Children
            for (var i=cccCount-1; i>=0; i--) {
                // Destroy Child
                childrenColumn.children[i].destroy();
            }
        }
    }

    // Hide Swipe
    function hideSwipe() {
        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    // Extend Top For Component Drop
    function extendTop() {
        // ...
    }

    // Collapse Top Drop Area
    function collapseTop() {

    }

    // Extend Bottom For Component Drop
    function extendBottom() {
        // ...
    }

    // Collapse Bottom Drop Area
    function collapseBottom() {

    }

//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "orange"
//    }

    Item {
        id: expandButtonContainer
        width: height * 0.5
        height: CONSTS.defaultNodeTreeItemHeight
        visible: childrenColumn.children.length > 0

        DMouseArea {
            id: expandButton

            width: parent.height * 0.5
            height: width

            anchors.centerIn: parent

            onPressed: {
                // Set Current Node
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
    }

    Item {
        id: dropAreasContainer
        width: parent.width
        height: CONSTS.defaultNodeTreeItemHeight
        visible: !nodeRoot.hideDropAreas && !nodeRoot.grabbed

        DropArea {
            id: topDropArea
            width: parent.width
            height: (parent.height - centerDropArea.height) * 0.5
            anchors.top: parent.top

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: parent.containsDrag ? "orange" : "#FF222222"
            }

            onEntered: {
                // Restart Hover Time
                hoverTimer.restart();
            }

            onExited: {
                // Stop Hover Timer
                hoverTimer.running = false;
            }
        }

        DropArea {
            id: centerDropArea
            width: parent.width
            height: parent.height * 0.7
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: parent.containsDrag ? "orange" : "#FF222222"
            }

            onEntered: {
                // Restart Hover Time
                hoverTimer.restart();
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

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: parent.containsDrag ? "orange" : "#FF222222"
            }

            onEntered: {
                // Restart Hover Time
                hoverTimer.restart();
            }

            onExited: {
                // Stop Hover Timer
                hoverTimer.running = false;
            }
        }
    }

    // Node Container
    Item {
        id: nodeContainer

        width: parent.width - expandButtonContainer.width
        height: CONSTS.defaultNodeTreeItemHeight
        anchors.left: expandButtonContainer.right

        // Node Rect
        DRectangle {
            id: nodeRect
            width: parent.width
            height: parent.height
            border.color: propertiesController.focusedComponent === nodeRoot.componentInfo ? DStyle.colorBorder : DStyle.colorBorderNoFocus
            smooth: true
//            z: nodeRoot.grabbed ? 1.0 : 0.0
//            scale: nodeRoot.grabbed ? 1.1 : 1.0
//            Behavior on scale { DAnimation { } }

            // Node Icon
            Rectangle {
                id: nodeIcon
                width: parent.height - DStyle.defaultMargin * 2
                height: width
                anchors.left: parent.left
                anchors.leftMargin: DStyle.defaultMargin
                anchors.verticalCenter: parent.verticalCenter
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
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
                opacity: nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.layerVisible ? 1.0 : 0.5 : 0.0
            }

            // Node Mouse Area
            DMouseArea {
                id: nodeMouseArea
                anchors.fill: parent

                onPressed: {
                    //console.log("nx: " + nodeRoot.x + " - ny: " + nodeRoot.y);

                    // Emit Node Pressed Signal
                    nodeTree.nodePressed(Math.round(mouse.x), Math.round(mouse.y));
                }

                onClicked: {
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
                        // Collapse
                        nodeRoot.collapse();
                        // Set Grabbed
                        nodeRoot.grabbed = true;
                    }
                }

                onPositionChanged: {
                    // Check If Grabbed
                    if (nodeRoot.grabbed) {
                        // Emit Node Pos Changed Signal
                        nodeTree.nodePosChanged(Math.round(mouse.x), Math.round(mouse.y));
                    }
                }

                onReleased: {
                    // Reset Grabbed
                    nodeRoot.grabbed = false;
                }

                onCanceled: {
                    // Reset Grabbed
                    nodeRoot.grabbed = false;
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

                OpacityMask {
                    id: buttonMask
                    anchors.fill: parent
                    anchors.margins: 3
                    opacity: {
                        // Check Component Info
                        if (nodeRoot.componentInfo !== null) {
                            return nodeRoot.componentInfo.layerVisible ? 0.8 : 0.5;
                        }

                        return 0.0;
                    }

                    Behavior on opacity { DFadeAnimation { } }

                    source: Rectangle {
                        width: buttonMask.width
                        height: buttonMask.height
                        color: DStyle.colorBorderNoFocus
                        visible: false
                    }

                    maskSource: DImage {
                        width: buttonMask.width
                        height: buttonMask.height
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/assets/icons/eye.png"
                    }

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
                visible: !nodeRoot.rootNode
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

    Column {
        id: childrenColumn
        width: parent.width
        anchors.top: nodeContainer.bottom
        anchors.topMargin: DStyle.defaultSpacing
        spacing: DStyle.defaultSpacing

        // ...
    }

    Timer {
        id: hoverTimer
        interval: 1000
        onTriggered: {
            // Check Top Area
            if (topDropArea.containsDrag) {
                // Extend Top
                extendTop();
            } else if (centerDropArea.containsDrag) {

                // Expand
                expand();

            } else if (bottomDropArea.containsDrag) {
                // Extend Bottom
                extendBottom();
            }
        }
    }
}
