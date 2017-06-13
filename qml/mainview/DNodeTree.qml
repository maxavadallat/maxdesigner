import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

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

    property DNodeTreeNode hoverindNodeParent: null

    property alias nodeGrabbedState: grabbedNode.dragActive
    property alias grabbedIndex: grabbedNode.childIndex
    property alias scrolling: scrollTimer.scrolling

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
        //console.log("DNodeTree.onNodePressed - [" + posX + ":" + posY + "]");

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
        grabbedNode.lastY = nodeY;

        grabbedNode.width = nodeWidth;

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

    // Map To Parent
    function mapToParent(parentObject, rectangle) {
        // Init New Rectangle
        var newRectangle = { "x": rectangle.x, "y": rectangle.y, "width": rectangle.height, "height": rectangle.height };
        // Get Rectangle Parent
        var rectParent = rectangle.parent;

        // Iterate Through Parents
        while (rectParent !== undefined && rectParent !== null && rectParent !== parentObject) {

            // Add Parent's X & Y To New Rectangle Position
            newRectangle.x += rectParent.x;
            newRectangle.y += rectParent.y;

            // Set Parent
            rectParent = rectParent.parent;
        }

        return newRectangle;
    }

    // Ensure Empty Node Visible
    function ensureEmptyNodeVisible(rectangle) {
        //console.log("DNodeTree.ensureEmptyNodeVisible - recangle[" + Math.round(rectangle.x) + ":" + Math.round(rectangle.y) + "]");

        // Get Mapped Rectangle
        var newRectangle = mapToParent(nodeTreeFlickable.containerColumn, rectangle);

        //console.log("DNodeTree.ensureEmptyNodeVisible - newRectangle[" + Math.round(newRectangle.x) + ":" + Math.round(newRectangle.y) + "]");

        // Flick To Ensure Rectangle Visible
        nodeTreeFlickable.flick(newRectangle, true);
    }

    // new Node Component
    Component {
        id: newNodeComponent

        DNodeTreeNode {
            visible: componentInfo !== null
            nodeTree: nodeTreeRoot
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
        property int centerY: y + height * 0.5
        property int lastY: 0

        onYChanged: {
            //console.log("#### y: " + y + height * 0.5);

            if (scrollTimer.scrolling) {
                // Check Scroll Direction
                if (!scrollTimer.scrollDirection && y > lastY || scrollTimer.scrollDirection && y < lastY) {

                    //Reset Scrolling
                    scrollTimer.scrolling = false;
                }

            } else  if (lastY > y && (grabbedNode.centerY) < (nodeTreeFlickable.height * scrollTimer.panThreshold) && !scrollTimer.scrolling) {

                //console.log("#### cY: " + nodeTreeFlickable.contentY);

                // Check Content Position
                if (nodeTreeFlickable.contentY > 0) {

                    // Set Scroll Direction
                    scrollTimer.scrollDirection = false;
                    // Set Scrolling
                    scrollTimer.scrolling = true;
                }

            } else if ((lastY < y) && (grabbedNode.centerY) > (nodeTreeFlickable.height * (1 - scrollTimer.panThreshold))  && !scrollTimer.scrolling) {

                //console.log("#### cY: " + nodeTreeFlickable.contentY);

                // Check Content Position
                if (nodeTreeFlickable.contentY < nodeTreeFlickable.contentHeight - nodeTreeFlickable.height) {
                    // Set Scroll Direction
                    scrollTimer.scrollDirection = true;
                    // Set Scrolling
                    scrollTimer.scrolling = true;
                }

            } else {
                //Reset Scrolling
                scrollTimer.scrolling = false;
            }

            // Set Last Y
            lastY = y;
        }

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

    // Scroll Timer
    Timer {
        id: scrollTimer

        property int panOffset: 0
        property real panThreshold: 0.2
        property bool scrolling: false
        property bool scrollDirection: false
        property int scrollStep: scrollDirection ? 4 : -4

        interval: 1000 / 120
        repeat: true

        onScrollingChanged: {
            //console.log("DNodeTree.scrollTimer.onScrollingChanged - scrolling: " + scrolling);
            // Check Scrolling
            if (scrolling) {
                // Restart
                restart();
            } else {
                // Reset Running
                running = false;
            }
        }

        onTriggered: {
            //console.log("DNodeTree.scrollTimer.onScrollingChanged - onTriggered");

            // Check Scroll Direction
            if (scrollDirection) {
                // Check Content Y
                if (nodeTreeFlickable.contentY >= nodeTreeFlickable.contentHeight - nodeTreeFlickable.height /*+ grabbedNode.height*/) {
                    // Reset Running
                    running = false;

                    return;
                }
            } else {
                // Check Content Y
                if (nodeTreeFlickable.contentY <= 0) {
                    // Reset Running
                    running = false;

                    return;
                }
            }

            // Calculate New Content Pos Y
            var newContentY = Math.max(nodeTreeFlickable.contentY + scrollStep, 0);

            // Set Content Position
            nodeTreeFlickable.contentY = newContentY;
        }
    }
}
