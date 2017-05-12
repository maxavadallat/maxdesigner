import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: nodeRoot

    width: 300
    height: CONSTS.defaultNodeTreeItemHeight

    Behavior on height { DAnimation { duration: 0 } }

    property ComponentInfo componentInfo: null

    property bool rootNode: false

    property string title: "Title test"

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
            appendNode(aIndex);
        }

        onChildMoved: {

            // ...

        }

        onChildRemoved: {
            // Remove Node
            removeNode(aIndex);
        }
    }

    // Parent Node Tree
    property var nodeTree: null

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
            nodeRoot.height = Qt.binding(function() { return CONSTS.defaultNodeTreeItemHeight + childrenColumn.height + DStyle.defaultSpacing; });
        } else {
            // Set Height
            nodeRoot.height = CONSTS.defaultNodeTreeItemHeight;
        }

        // Hide Swipe
        swipeGesture.hideSwipe();
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
            nodeRoot.title = nodeRoot.componentInfo.componentName;

            // Get Children Count
            var cCount = nodeRoot.componentInfo.childCount;

            //console.log("DNodeTreeNode.buildNodeTree  - componentInfo: " + nodeRoot.componentInfo.componentName + " - cCount: " + cCount);

            // Iterate Through Children
            for (var i=0; i<cCount; i++) {
                // Append Node
                appendNode(i);
            }
        }
    }

    // Append Node
    function appendNode(newNodeIndex) {
        // Get Child Info
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

        // ...

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

    // Start Drag
    function startDrag() {

    }

    // Finish Drag
    function finishDrag() {

    }

    function extendTop() {

    }

    function extendBottom() {

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
//                text: nodeRoot.expanded ? "-" : "+"
            }
        }
    }

    DropArea {
        id: topDropArea
        width: parent.width
        height: (parent.height - centerDropArea.height) * 0.5
        anchors.top: parent.top

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "#FF222222"
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
            border.color: "#FF222222"
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
            border.color: "#FF222222"
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

    Item {
        id: nodeContainer

        width: parent.width - expandButtonContainer.width
        height: CONSTS.defaultNodeTreeItemHeight
        anchors.left: expandButtonContainer.right

        DRectangle {
            id: nodeRect
            width: parent.width
            height: parent.height
            border.color: propertiesController.focusedComponent === nodeRoot.componentInfo ? DStyle.colorBorder : DStyle.colorBorderNoFocus
            smooth: true

            Rectangle {
                id: nodeIcon
                width: parent.height - DStyle.defaultMargin * 2
                height: width
                anchors.left: parent.left
                anchors.leftMargin: DStyle.defaultMargin
                anchors.verticalCenter: parent.verticalCenter
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
            }

            DText {
                id: titleLable
                anchors.left: nodeIcon.right
                anchors.leftMargin: DStyle.defaultMargin
                anchors.right: parent.right
                anchors.rightMargin: DStyle.defaultMargin
                anchors.verticalCenter: parent.verticalCenter
                text: nodeRoot.title
                wrapMode: Text.NoWrap
                elide: Text.ElideMiddle
            }

            DMouseArea {
                id: nodeMouseArea
                anchors.fill: parent

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
                    // Collapse
                    nodeRoot.collapse();

                    // Set Grabbed
                    nodeRoot.grabbed = true;
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

//            // Delete Button
//            DMouseArea {
//                id: deleteButton
//                width: parent.height * 0.4
//                height: width
//                anchors.right: parent.right
//                anchors.rightMargin: DStyle.defaultMargin
//                anchors.verticalCenter: parent.verticalCenter

//                DRectangle {
//                    width: parent.width
//                    height: parent.height
//                    anchors.centerIn: parent
//                    color: parent.pressed ? DStyle.colorHighLight : DStyle.colorBG
//                    border.color: parent.pressed ? DStyle.colorBorderNoFocus : "transparent"
//                    radius: width * 0.4
//                    scale: parent.pressed ? DStyle.pressedScale : 1.0

//                    DText {
//                        anchors.centerIn: parent
//                        anchors.verticalCenterOffset: -1
//                        text: "x"
//                        font.pixelSize: DStyle.fontSizeS
//                    }
//                }

//                onClicked: {

//                }
//            }

            // Swipe Gesture Area
            DSwipeGesture {
                id: swipeGesture
                anchors.fill: parent
                onActionButtonClicked: {
                    // Remove Node

                    // ...
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
