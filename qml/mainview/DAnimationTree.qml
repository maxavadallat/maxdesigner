import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: animTreeRoot

    width: 400
    height: 600

    property ComponentInfo rootComponent: null

    property bool nodeTreeInit: false

    default property alias content: rootNode.childrenContainerAlias

    property int nodePressX: 0
    property int nodePressY: 0

    property QtObject dragMouseArea: null

    property DAnimationTreeNode currentNode: null

    property DAnimationTreeNode hoveringNodeParent: null

    property alias nodeGrabbedState: grabbedNode.dragActive
    property alias grabbedIndex: grabbedNode.childIndex
    property alias scrolling: scrollTimer.scrolling

    property bool enableNodeVisibilityChange: false

    signal nodePressed(var posX, var posY, var mouseArea)
    signal nodeGrabbed(var nodeX, var nodeY, var nodeWidth, var nodeHeight, var componentInfo, var grabbedIndex)
    signal nodePosChanged(var nodeX, var nodeY)
    signal nodeReleased()
    signal removeEmptyNode()

    Component.onCompleted: {
        // Set Node Tree Init
        animTreeRoot.nodeTreeInit = true;

        // ...
    }

    onNodePressed: {
        //console.log("DNodeTree.onNodePressed - [" + posX + ":" + posY + "]");

        // Set Node Press X
        animTreeRoot.nodePressX = posX;
        // Set Node Press Y
        animTreeRoot.nodePressY = posY;

        // Set Node Drag Mouse Area
        animTreeRoot.dragMouseArea = mouseArea;

        // ...
    }

    onNodeGrabbed: {
        //console.log("DNodeTree.onNodeGrabbed - grabbedIndex: " + grabbedIndex);

        // Set Interactive State
        animTreeFlickable.interactive = false;

        // Set Drag Target
        animTreeRoot.dragMouseArea.drag.target = grabbedNode;

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
        animTreeFlickable.interactive = true;
        // Reset Drag Target
        animTreeRoot.dragMouseArea.drag.target = undefined;
        // Reset Node Drag Mouse Area
        animTreeRoot.dragMouseArea = null;
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
        var newRectangle = mapToParent(animTreeFlickable.containerColumn, rectangle);

        //console.log("DNodeTree.ensureEmptyNodeVisible - newRectangle[" + Math.round(newRectangle.x) + ":" + Math.round(newRectangle.y) + "]");

        // Flick To Ensure Rectangle Visible
        animTreeFlickable.flick(newRectangle, true);
    }

    // new Node Component
    Component {
        id: newNodeComponent

        DAnimationTreeNode {
            visible: componentInfo !== null
            nodeTree: animTreeRoot
        }
    }

    // Node Tree Flickable
    DFlickable {
        id: animTreeFlickable
        anchors.fill: parent

        DAnimationTreeNode {
            id: rootNode
            width: animTreeFlickable.width
            componentInfo: animTreeRoot.rootComponent
            visible: componentInfo !== null
            nodeTree: animTreeRoot
            isRootNode: true
        }
    }

    // Grabbed Node Overlay
    DAnimationTreeNode {
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

            } else  if (lastY > y && (grabbedNode.centerY) < (animTreeFlickable.height * scrollTimer.panThreshold) && !scrollTimer.scrolling) {

                //console.log("#### cY: " + animTreeFlickable.contentY);

                // Check Content Position
                if (animTreeFlickable.contentY > 0) {

                    // Set Scroll Direction
                    scrollTimer.scrollDirection = false;
                    // Set Scrolling
                    scrollTimer.scrolling = true;
                }

            } else if ((lastY < y) && (grabbedNode.centerY) > (animTreeFlickable.height * (1 - scrollTimer.panThreshold))  && !scrollTimer.scrolling) {

                //console.log("#### cY: " + animTreeFlickable.contentY);

                // Check Content Position
                if (animTreeFlickable.contentY < animTreeFlickable.contentHeight - animTreeFlickable.height) {
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
                animTreeRoot.removeEmptyNode();
            }
        }

        Drag.active: dragActive

        Drag.hotSpot.x: grabbedNode.width * 0.5 //animTreeRoot.nodePressX
        Drag.hotSpot.y: grabbedNode.height * 0.5 //animTreeRoot.nodePressY

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
                if (animTreeFlickable.contentY >= animTreeFlickable.contentHeight - animTreeFlickable.height /*+ grabbedNode.height*/) {
                    // Reset Running
                    running = false;

                    return;
                }
            } else {
                // Check Content Y
                if (animTreeFlickable.contentY <= 0) {
                    // Reset Running
                    running = false;

                    return;
                }
            }

            // Calculate New Content Pos Y
            var newContentY = Math.max(animTreeFlickable.contentY + scrollStep, 0);

            // Set Content Position
            animTreeFlickable.contentY = newContentY;
        }
    }
}
