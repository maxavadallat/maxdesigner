import QtQuick 2.0
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeRoot

    width: componentInfo !== null ? parent.width * Math.pow(CONSTS.defaultNodeScaleRatio, componentInfo.depth) : 0
    //width: componentInfo !== null ? parent.width * Math.pow(CONSTS.defaultNodeScaleRatio, componentInfo.depth) : parent.width
    height: CONSTS.defaultNodeTreeItemHeight

    Behavior on height { DAnimation { } }

    property bool nodeInit: false

    property ComponentInfo componentInfo: null

    property Connections componentInfoConnections: Connections {
        target: componentInfo
        onChildAdded: nodeRoot.childAdded(nodeRoot.itemIndex, aIndex);
        onChildMoved: nodeRoot.childMoved(nodeRoot.itemIndex, aIndex, aTarget);
        onChildRemoved: nodeRoot.childRemoved(nodeRoot.itemIndex, aIndex);
    }

    property bool rootNode: false

    property string title: "Title test"

    property bool nodeVisibility: true

    property int parentIndex: -1

    property int itemIndex: -1

    property int childIndex: -1

    property var childIndexes: ""

    property int depth: 0

    property bool expanded: false

    property bool grabbed: false

    property bool topHovered: false
    property bool centerHovered: false
    property bool bottomHovered: false

    property var prevAnchor: undefined

    property int swipeIndex: -1

    z: grabbed ? 1.0 : 0.0

    scale: grabbed ? 1.1 : 1.0

    Behavior on scale { DAnimation { easing.type: Easing.OutBack } }

    visible: height > 0

    //clip: true

    signal itemSelected(var index)
    signal expandItem(var index)
    signal collapseItem(var index)
    signal swipeActivated(var index)
    signal deleteItem(var index)

    signal childAdded(var index, var childIndex)
    signal childMoved(var index, var childIndex, var targetIndex)
    signal childRemoved(var index, var childIndex)

    Component.onCompleted: {
        // Set Node Init
        nodeRoot.nodeInit = true;

        // ...
    }

    onComponentInfoChanged: {
        //console.log("DNodeTreeNode.onComponentInfoChanged - componentName: " + (nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.componentName  + " - childCount: " + nodeRoot.componentInfo.childCount : "NULL"));
//        // Clear
//        clear();
//        // Build Node tree
//        buildNodeTree();
    }

    onSwipeIndexChanged: {
        // Check Swipe Index
        if (swipeIndex !== itemIndex) {
            // Hide Swipe
            hideSwipe();
        }
    }

    onExpandedChanged: {
//        // Check If Expanded
//        if (nodeRoot.expanded) {
//            // Set Height
//            nodeRoot.height = Qt.binding(function() { return CONSTS.defaultNodeTreeItemHeight + childrenColumn.height + DStyle.defaultSpacing; });
//        } else {
//            // Set Height
//            nodeRoot.height = CONSTS.defaultNodeTreeItemHeight;
//        }

        // Hide Swipe
        swipeGesture.hideSwipe();
    }

    onGrabbedChanged: {
//        // Check Grabbed State
//        if (nodeRoot.grabbed) {
//            // set Drag Target
//            nodeMouseArea.drag.target = nodeRoot;
//            // Set Prev Anchor
//            nodeRoot.prevAnchor = anchors.right;
//            // Reset Right Anchor
//            anchors.right = undefined;

//            // Set Drag Active
//            Drag.active = true;

//        } else {
//            // Reset Drag Target
//            nodeMouseArea.drag.target = undefined;
//            // Reset Right Anchor
//            anchors.right = nodeRoot.prevAnchor;

//            // RESet Drag Active
//            Drag.active = false;

//        }
    }

    // Expand
    function expand() {
//        // Check Children
//        if (childrenColumn.children.length > 0) {
//            // Set Expanded
//            nodeRoot.expanded = true;
//        }
    }

    // Collapse
    function collapse() {
//        // Reset Expanded
//        nodeRoot.expanded = false;
    }

//    // Build Node Tree
//    function buildNodeTree() {
//        // Check Component Info
//        if (nodeRoot.componentInfo !== null && nodeRoot.nodeTree !== null) {
//            // Set Title
//            nodeRoot.title = nodeRoot.componentInfo.componentName;

//            // Get Children Count
//            var cCount = nodeRoot.componentInfo.childCount;

//            //console.log("DNodeTreeNode.buildNodeTree  - componentInfo: " + nodeRoot.componentInfo.componentName + " - cCount: " + cCount);

//            // Iterate Through Children
//            for (var i=0; i<cCount; i++) {
//                // Append Node
//                appendNode(i);
//            }
//        }
//    }

//    // Append Node
//    function appendNode(newNodeIndex) {
//        // Get Child Info
//        var newNode = nodeRoot.nodeTree.createNode(nodeRoot.componentInfo.childInfo(newNodeIndex), childrenColumn);
//        // Check New Node
//        if (newNode !== null) {
//            // Set Width
//            newNode.width = Qt.binding(function() { return nodeRoot.width * CONSTS.defaultNodeScaleRatio; });
//            // Set Anchor
//            newNode.anchors.right = childrenColumn.right;
//            // Hide Swipe
//            //newNode.hideSwipe();
//        }
//    }

//    // Insert Node
//    function insertNode(newNodeIndex) {

//        // ...

//    }

//    // Remove Node
//    function removeNode(nodeIndex) {
//        // Destroy Node
//        childrenColumn.children[nodeIndex].destroy();
//    }

//    // Clear
//    function clear() {
//        // Get Children Column Children Count
//        var cccCount = childrenColumn.children.length;

//        // Check Count
//        if (cccCount > 0) {
//            //console.log("DNodeTreeNode.clear  - cccCount: " + cccCount);

//            // Iterate Through Children
//            for (var i=cccCount-1; i>=0; i--) {
//                // Destroy Child
//                childrenColumn.children[i].destroy();
//            }
//        }
//    }

    // Hide Swipe
    function hideSwipe() {
        // Hide Swipe
        swipeGesture.hideSwipe();
    }

//    // Start Drag
//    function startDrag() {

//    }

//    // Finish Drag
//    function finishDrag() {

//    }

//    function extendTop() {

//    }

//    function extendBottom() {

//    }

//    // Top Drop Area
//    DropArea {
//        id: topDropArea
//        width: parent.width
//        height: (parent.height - centerDropArea.height) * 0.5
//        anchors.top: parent.top

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: parent.containsDrag ? "orange" : "#FF222222"
//        }

//        onEntered: {
//            // Restart Hover Time
//            hoverTimer.restart();
//        }

//        onExited: {
//            // Stop Hover Timer
//            hoverTimer.running = false;
//        }
//    }
//    // Center Drop Area
//    DropArea {
//        id: centerDropArea
//        width: parent.width
//        height: parent.height * 0.7
//        anchors.verticalCenter: parent.verticalCenter

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: parent.containsDrag ? "orange" : "#FF222222"
//        }

//        onEntered: {
//            // Restart Hover Time
//            hoverTimer.restart();
//        }

//        onExited: {
//            // Stop Hover Timer
//            hoverTimer.running = false;
//        }
//    }
//    // Bottom Drop Area
//    DropArea {
//        id: bottomDropArea
//        width: parent.width
//        height: (parent.height - centerDropArea.height) * 0.5
//        anchors.bottom: parent.bottom

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: parent.containsDrag ? "orange" : "#FF222222"
//        }

//        onEntered: {
//            // Restart Hover Time
//            hoverTimer.restart();
//        }

//        onExited: {
//            // Stop Hover Timer
//            hoverTimer.running = false;
//        }
//    }

//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "orange"
//    }

    // Node Container
    Item {
        id: nodeContainer

        anchors.fill: parent

        // Expand Button
        Item {
            id: expandButtonContainer
            width: height * 0.5
            height: parent.height
            visible: nodeRoot.childIndexes.length > 0

            DMouseArea {
                id: expandButton

                width: parent.height * 0.5
                height: width

                anchors.centerIn: parent

                onClicked: {
                    // Check If Expanded
                    if (!nodeRoot.expanded) {
                        // Set Expanded
                        //nodeRoot.expand();

                        // Emit Expand Item Signal
                        nodeRoot.expandItem(nodeRoot.itemIndex);
                    } else {
                        // Restore
                        //nodeRoot.collapse();
                        // Emit Collapse Item Signal
                        nodeRoot.collapseItem(nodeRoot.itemIndex);
                    }
                }

                DText {
                    anchors.centerIn: parent
                    scale: parent.pressed ? DStyle.pressedScale : 1.0
                    rotation: nodeRoot.expanded ? 135 : 0
                    Behavior on rotation { DAnimation { } }
                    font.pixelSize: DStyle.fontSizeS
                    text: "❖"
    //                text: nodeRoot.expanded ? "-" : "+"
                }
            }
        }

        // Node Rectangle
        DRectangle {
            id: nodeRect
            width: parent.width - expandButtonContainer.width
            height: parent.height
            anchors.right: parent.right
            border.color: propertiesController.focusedComponent === nodeRoot.componentInfo ? DStyle.colorBorder : DStyle.colorBorderNoFocus
            smooth: true

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
                opacity: nodeRoot.componentInfo !== null ? nodeRoot.componentInfo.layerVisible ? 1.0 : 0.3 : 1.0
            }

            // Node Mouse Area
            DMouseArea {
                id: nodeMouseArea
                anchors.fill: parent

                onPressed: {
                    // Emit Item Selected Signal
                    nodeRoot.itemSelected(itemIndex);
                }

                onClicked: {
                    // Set Focus
                    //nodeRect.focus = true;

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

                OpacityMask {
                    id: buttonMask
                    anchors.fill: parent
                    anchors.margins: 3
                    opacity: {
                        // Check Component Info
                        if (nodeRoot.componentInfo !== null) {
                            return nodeRoot.componentInfo.layerVisible ? 0.8 : 0.3;
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
                    // Toggle Layer Visibility
                    nodeRoot.componentInfo.layerVisible = !nodeRoot.componentInfo.layerVisible;
                }
            }

            // Swipe Gesture Area
            DSwipeGesture {
                id: swipeGesture
                anchors.fill: parent
                visible: !nodeRoot.rootNode

                onSwipeStarted: {
                    // Emit Swipe Activated Signal
                    nodeRoot.swipeActivated(nodeRoot.itemIndex);
                }

                onSwipeFinished: {
                    // ...
                }

                onActionButtonClicked: {
                    // Emit Delete Item Signal
                    //nodeRoot.deleteItem(nodeRoot.itemIndex);

                    // Remove Child From Parent
                    componentInfo.removeFromParent();
                }
            }
        }
    }

    // Hover Timer
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
