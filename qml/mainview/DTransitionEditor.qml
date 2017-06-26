import QtQuick 2.0
import QtQml.Models 2.2

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: transitionEditorRoot

    // Current Focused Component
    property ComponentInfo componentInfo: propertiesController.focusedComponent
    // Current Component Transition
    property ComponentTransition componentTransition: null
    // Component Transition Model
    property ComponentTransitionsModel transitionsModel: propertiesController.transitionsModel
    // Component States Model
    property ComponentStatesModel statesModel: propertiesController.statesModel
    // Animation Components Model
    property AnimationComponentsModel animsModel: propertiesController.animComponentsModel

    // States Count
    property int statesCount: statesModel ? statesModel.rowCount() : 0

    // New Transition
    property bool newTransition: false

    // Current Transition Node
    property DTransitionTreeNode currentNode: null
    // Current Transition Node Component Info
    property ComponentInfo currentNodeInfo: currentNode !== null ? currentNode.componentInfo : null
    // Current Transition Node Animation Base
    property string currentNodeAnimBase: currentNodeInfo !== null ? currentNodeInfo.animBase() : ""

    // Child Pane Connections
    property Connections childPaneConnections: Connections {
        target: childPane

        onAccepted: {
            // Check If New Transition Node
            if (childPane.newTransitionNode) {
                // Init Parent MNode Info
                var pnInfo = null;
                // Check Current Node Component Animation Base
                if (transitionEditorRoot.currentNodeAnimBase === "ParallelAnimation" || transitionEditorRoot.currentNodeAnimBase === "SequentialAnimation") {
                    // Set Parent Node Info
                    pnInfo = transitionEditorRoot.currentNodeInfo;
                }

                // Append Transition Node
                componentTransition.appendNode(childPane.transitionNode, pnInfo);
            }

            // ...

            // Enable Add Transition Option
            addTransitionOption.enabled = true;
        }

        onRejected: {
            // Check If New Transition Node
            if (childPane.newTransitionNode) {
                // Discard New Transition Node
                componentTransition.discardNewNode();
            }

            // ....

            // Enable Add Transition Option
            addTransitionOption.enabled = true;
        }
    }

    // Animation Components Model Connections
    property Connections animsModelConnections: Connections {
        target: animsModel

        onItemAdded: {
            //console.log("DTransitionEditor.animsModelConnections.onItemAdded - aIndex: " + aIndex);
            // Append Animation Item
            addTransitionOption.appendItem("Add " + transitionEditorRoot.animsModel.getNameByIndex(aIndex), false);

        }

        onItemRemoved: {
            //console.log("DTransitionEditor.animsModelConnections.onItemRemoved - aIndex: " + aIndex);
            // Remove Item
            addTransitionOption.removeItem(aIndex + 1);
        }

        onAnimationComponentsCleared: {
            // console.log("DTransitionEditor.animsModelConnections.onAnimationComponentsCleared");
            // Clear Transition Animations Option
            addTransitionOption.clearItemModel();
            // Append Initial Item
            addTransitionOption.appendItem("Select Transition To Add", false);
            // Set Current Index
            addTransitionOption.currentIndex = 0;
        }
    }

    // Component Transition Connections
    property Connections componentTransitionConnecitons: Connections {
        target: componentTransition

        onNodeAdded: {
            console.log("DTransitionEditor.componentTransitionConnecitons.onNodeAdded - aParentNode: " + aParentNode + " - aIndex: " + aIndex);

            // Check Parent Node
            if (aParentNode === null) {
                // Insert Node
                insertNode(aIndex);
            } else {

                // ...
            }

            // ...
        }

        onNodeMoved: {
            console.log("DTransitionEditor.componentTransitionConnecitons.onNodeMoved - aParentNode: " + aParentNode + " - aIndex: " + aIndex + " - aTargetNode: " + aTargetNode + " - aTargetIndex: " + aTargetIndex);

            // Check Parent Node & Target Node
            if (aParentNode === null && aTargetNode === null) {
                // Move Node
                moveNode(aIndex, aTargetIndex);

            } else {

                // ...

            }

            // ...
        }

        onNodeRemoved: {
            console.log("DTransitionEditor.componentTransitionConnecitons.onNodeRemoved - aParentNode: " + aParentNode + " - aIndex: " + aIndex);

            // Check Parent Node
            if (aParentNode === null) {
                // Remove Node
                removeNode(aIndex);

            } else {

                // ...

            }

            // ...
        }
    }

    // New Transition Node Component
    property Component newTransitionNodeComponent: Component {
        DTransitionTreeNode {
            transitionEditorRoot: transitionEditorRoot
            parentNode: transitionEditorRoot
        }
    }

    // Node Press Pos X
    property int nodePressX: 0
    // Node Press Pos Y
    property int nodePressY: 0
    // Drag Mouse Area
    property QtObject dragMouseArea: null
    // Grabbed Node Parent
    property QtObject grabbedNodeParent: null
    // Hovering Node Parent Node`
    property QtObject hoveringNodeParent: null
    // Grabbed Child Index
    property int grabbedChildIndex: -1
    // Node Grabbed State
    property alias nodeGrabbedState: grabbedNode.dragActive
    // Grabbed Node Index
    property alias grabbedIndex: grabbedNode.childIndex

    title: "Transition Editor"

    hideToSide: hideToRight

    creationWidth: 460
    creationHeight: transitionEditorColumn.height + 44

    minWidth: 460
    minHeight: transitionEditorColumn.height + 44

    enableResize: true

    resizeTopEnabled: false
    resizeBottomEnabled: false

    enableHideButton: false

    signal newTransitionNode(var animIndex)
    signal editTransitionNode(var nodeIndex)

    signal nodePressed(var posX, var posY, var mouseArea)
    signal nodeGrabbed(var nodeX, var nodeY, var nodeWidth, var nodeHeight, var componentInfo, var grabbedIndex)
    signal nodePosChanged(var nodeX, var nodeY)
    signal nodeReleased()
    signal removeEmptyNode()

    signal nodeFocusLost()

    // On Completed
    Component.onCompleted: {
        // Build Available Anims Option List
        buildAnims();
    }

    // On Transition Started
    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Transition Editor
            resetTransitionEditor();
        }
    }

    // On Transition Finished
    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Option Focus
            fromOption.setOptionFocus(true);
        }
    }

    // On Child Transition Finished Slot
    onChildTransitionFinished: {
        // Check New State
        if (newState === stateCreate) {
            // Set Option Current Index
            addTransitionOption.currentIndex = 0;
            // Set Enabled
            addTransitionOption.enabled = true;
            // Set Option Focus
            addTransitionOption.setOptionFocus(true);
        }
    }

    // On Component Info Changed Slot
    onComponentInfoChanged: {
        console.log("DTransitionEditor.onComponentInfoChanged - componentName: " + (transitionEditorRoot.componentInfo !== null ? transitionEditorRoot.componentInfo.componentName : "NULL"));

        // Clear Transition Nodes
        clearTransitionNodes();
        // Clear From States Option List
        clearFromStates();
        // Clear To States Option List
        clearToStates();

        // Update States Count
        transitionEditorRoot.statesCount = transitionEditorRoot.statesModel ? transitionEditorRoot.statesModel.rowCount() : 0

        // Build From States Option List
        buildFromStates();
        // Build To States Option List
        buildToStates();
        // Build Transition Nodes
        buildTransitionNodes();
    }

    // On Current Node Changed Slot
    onCurrentNodeChanged: {
        // Check Current Node
        if (transitionEditorRoot.currentNode !== null) {
            console.log("DTransitionEditor.onCurrentNodeChanged - currentNode: " + (transitionEditorRoot.currentNode.componentInfo !== null ? transitionEditorRoot.currentNode.componentInfo.componentName : "NULL" ));
        } else {
            console.log("DTransitionEditor.onCurrentNodeChanged - NULL");
        }
    }

    // On New Transition Node Slot
    onNewTransitionNode: {
        // Check Anims Model
        if (animIndex >= 0) {
            // Get Selected Animation Name
            var animName = transitionEditorRoot.animsModel.getNameByIndex(animIndex);

            console.log("DTransitionEditor.onNewTransitionNode - animName: " + animName);

//            // Get Current Node Component Info
//            var cnComponentInfo = transitionEditorRoot.currentNode ? transitionEditorRoot.currentNode.componentInfo : null;

            // Get Current Node Component Info Animation Base
            var cnAnimBase = transitionEditorRoot.currentNodeInfo !== null ? transitionEditorRoot.currentNodeInfo.animBase() : "";

            console.log("DTransitionEditor.onNewTransitionNode - cnAnimBase: " + cnAnimBase);

            // Init Transition Node Component
            var newTransitionNodeComponent = transitionEditorRoot.componentTransition.createNewNode(animName, transitionEditorRoot.currentNodeInfo);

            // Check Anim Name
            if (animName === "SequentialAnimation" || animName === "ParallelAnimation") {
                // Add Animation Component
                transitionEditorRoot.componentTransition.appendNode(newTransitionNodeComponent, transitionEditorRoot.currentNodeInfo);
                // Enable Add Transition Option
                addTransitionOption.enabled = true;
                // Reset Current Index
                addTransitionOption.currentIndex = 0;
            } else {
                // Set New Transition Node
                childPane.newTransitionNode = true;
                // Set Component Transitions
                childPane.componentTransition = transitionEditorRoot.componentTransition;
                // Set Transition Node
                childPane.transitionNode = newTransitionNodeComponent;
                // Show Transition Node Editor
                childPane.show();
            }
        }
    }

    // On Edit Transition Slot
    onEditTransitionNode: {
        // Check Component Transition
        if (transitionEditorRoot.componentTransition !== null) {
            // Disablbe Add Transition Option
            addTransitionOption.enabled = false;
            // Set New Transition Node
            childPane.newTransitionNode = false;
            // Set Transition Node
            childPane.transitionNode = transitionEditorRoot.currentNode.componentInfo;
            // Show Transition Node Editor
            childPane.show();
        }
    }

    // On Accepted Slot
    onAccepted: {
        //console.log("DTransitionEditor.onAccepted");

        // Update Component Transition
        //updateComponentTransition();

        // Check If New Transition
        if (transitionEditorRoot.newTransition) {
            // Append Transition
            transitionEditorRoot.transitionsModel.appendTransition(transitionEditorRoot.componentTransition);
        } else {

        }

        // ...
    }

    // On rejected Slot
    onRejected: {
        //console.log("DTransitionEditor.onRejected");
        // Discard New Transition
        transitionEditorRoot.transitionsModel.discardNewTransition();
    }

    // On Node Presed Slot
    onNodePressed: {
        console.log("#### DTransitionEditor.onNodePressed - [" + posX + ":" + posY + "]");

        // Set Node Press X
        transitionEditorRoot.nodePressX = posX;
        // Set Node Press Y
        transitionEditorRoot.nodePressY = posY;
        // Set Node Drag Mouse Area
        transitionEditorRoot.dragMouseArea = mouseArea;
    }

    // On Node Grabbed Slot
    onNodeGrabbed: {
        console.log("#### DTransitionEditor.onNodeGrabbed - grabbedIndex: " + grabbedIndex);

        // Set Drag Target
        transitionEditorRoot.dragMouseArea.drag.target = grabbedNode;

        // Set Grabbed Index
        grabbedNode.childIndex = grabbedIndex;
        // Set Up Grabbed Node
        grabbedNode.x = nodeX;
        grabbedNode.y = nodeY;

        //grabbedNode.lastY = nodeY;
        // Set Grabbed Node Width
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

    // On Node Released Slot
    onNodeReleased: {
        console.log("#### DTransitionEditor.onNodeReleased");

        // Reset Drag Active
        grabbedNode.dragActive = false;
        // Reset Drag Target
        transitionEditorRoot.dragMouseArea.drag.target = undefined;
        // Reset Node Drag Mouse Area
        transitionEditorRoot.dragMouseArea = null;
        // Reset Scale
        grabbedNode.scale = 1.0;
        // Set Visibility
        grabbedNode.visible = false;
    }

    // On Remove Empty Node Slot
    onRemoveEmptyNode: {
        // Remove Empty Node
        removeEmptyNodeFromNodes();
    }

    // On Node Focus Lost Slot
    onNodeFocusLost: {
        // Set Focus To Add Transition Option
        addTransitionOption.setOptionFocus(true);
    }

    // Build From States Option List
    function buildFromStates() {
        //console.log("DTransitionEditor.buildFromStates");

        // Check Component Info
        if (transitionEditorRoot.componentInfo !== null && transitionEditorRoot.statesCount > 0) {
            //console.log("DTransitionEditor.buildFromStates - statesCount: " + transitionEditorRoot.statesCount);

            // Add Empty State
            fromOption.appendItem("", false);

            // Iterate Through States
            for (var i=0; i<transitionEditorRoot.statesCount; i++) {
                // Add State
                fromOption.appendItem(transitionEditorRoot.statesModel.getState(i).stateName, false);
            }
        }
    }

    // Clear From States Option List
    function clearFromStates() {
        //console.log("DTransitionEditor.clearFromStates");
        // Clear Item Model
        fromOption.clearItemModel();
    }

    // Build To States Option List
    function buildToStates() {
        //console.log("DTransitionEditor.buildToStates");

        // Check Component Info
        if (transitionEditorRoot.componentInfo !== null && transitionEditorRoot.statesCount > 0) {
            //console.log("DTransitionEditor.buildToStates - statesCount: " + transitionEditorRoot.statesCount);

            // Add Empty State
            toOption.appendItem("", false);

            // Iterate Through States
            for (var i=0; i<transitionEditorRoot.statesCount; i++) {
                // Add State
                toOption.appendItem(transitionEditorRoot.statesModel.getState(i).stateName, false);
            }
        }
    }

    // Clear To States Option List
    function clearToStates() {
        //console.log("DTransitionEditor.clearToStates");

        // Clear Item Model
        toOption.clearItemModel();

        // ...
    }

    // Build Anims
    function buildAnims() {
        // Check Count
        if (addTransitionOption.count === 0) {
            // Add Initial Item
            addTransitionOption.appendItem("Select Transition To Add", false);
        }

        // Get Anim Components Model Count
        var acCount = transitionEditorRoot.animsModel ? transitionEditorRoot.animsModel.rowCount() : 0;

        console.log("DTransitionEditor.buildAnims - acCount: " + acCount);

        // Iterate Through Animation COmponents
        for (var i=0; i<acCount; i++) {
            // Append Animation Item
            addTransitionOption.appendItem("Add " + transitionEditorRoot.animsModel.getNameByIndex(i), false);
        }
    }

    // Build Transition Nodes
    function buildTransitionNodes() {
        // Check Component Transition
        if (transitionEditorRoot.componentTransition !== null) {
            // Get Nodes Count
            var tnCount = transitionEditorRoot.componentTransition.nodesCount;

            // Check Nodes Count
            if (tnCount > 0) {
                console.log("DTransitionEditor.buildTransitionNodes - tnCount: " + tnCount);

                // Iterate Through Transition Nodes
                for (var i=0; i<tnCount; i++) {
                    // Insert Node
                    insertNode(i);
                }
            }
        }
    }

    // Clear Transition Nodes
    function clearTransitionNodes() {
        // Check Transition
        if (transitionEditorRoot.componentTransition !== null && transitionNodesModel.count > 0) {
            console.log("DTransitionEditor.clearTransitionNodes");

            // Clear Transition Nodes Model
            transitionNodesModel.clear();
            // ...
        }
    }

    // Reset Transition Editor
    function resetTransitionEditor() {
        console.log("DTransitionEditor.resetTransitionEditor - newTransition: " + transitionEditorRoot.newTransition);

        // Clear Transition Nodes
        clearTransitionNodes();

        // Check Component Transition
        if (transitionEditorRoot.componentTransition !== null) {
            // Set From Option Value
            fromOption.setValue(transitionEditorRoot.componentTransition.fromState);
            // Set To Option Value
            toOption.setValue(transitionEditorRoot.componentTransition.toState);

            // Build Transition Nodes
            buildTransitionNodes();

        } else {
            // Set From Option Current Index
            fromOption.currentIndex = 0;
            // Set To Option Current Index
            toOption.currentIndex = 0;

            // ...
        }

        // Set Add Transition Option Current Index
        addTransitionOption.currentIndex = 0;

        // ...
    }

    // Check If Transition Valid
    function validateTransition() {
        // Compare From & To State
        if (fromOption.currentIndex === toOption.currentIndex) {
            // Set Invalid Value
            fromOption.invalidValue = true;
            // Set Invalid Value
            toOption.invalidValue = true;

            return false;
        }

        return true;
    }

    // Update Component Transition
    function updateComponentTransition() {
        // Check Component Transition
        if (transitionEditorRoot.componentTransition !== null) {
            console.log("DTransitionEditor.updateComponentTransition");

            // Set From State
            transitionEditorRoot.componentTransition.fromState = fromOption.getItemText(fromOption.currentIndex);
            // Set To State
            transitionEditorRoot.componentTransition.toState = toOption.getItemText(toOption.currentIndex);

            // ...

            // Check Transitions Model
            if (transitionEditorRoot.transitionsModel !== null) {
                // Update Selected State
                transitionEditorRoot.transitionsModel.updateSelectedTransition();
            }

            // ...
        }
    }

    // Accept Transition
    function acceptTransition() {
        console.log("DTransitionEditor.acceptTransition");

        // Check If Transition Valid
        if (validateTransition()) {
            // Update Component Transition
            updateComponentTransition();
            // Emit Accepted Signal
            transitionEditorRoot.accepted();
        }
    }

    // Create Node
    function createNode(componentInfo, nodeParent) {
        // Check Component Info
        if (componentInfo !== null) {
            console.log("DTransitionEditor.createNode - componentInfo: " + componentInfo.componentName + " - nodeParent: " + nodeParent);

            // Create New Node Object
            var newNodeObject = newTransitionNodeComponent.createObject(nodeParent);
            // Set Transition Editor Root
            newNodeObject.transitionEditorRoot = transitionEditorRoot;
            // Set Parent Node
            newNodeObject.parentNode = transitionEditorRoot;
            // Set Component Info
            newNodeObject.componentInfo = componentInfo;

            return newNodeObject;
        }

        return null;
    }

    // Inser Transition Node
    function insertNode(newNodeIndex) {
        // Check Compoennt Transition
        if (transitionEditorRoot.componentTransition !== null) {
            console.log("DTransitionEditor.insertNode - newNodeIndex: " + newNodeIndex);

            // Emit Remove Empty Node Signal
            removeEmptyNode();

            // Get Node Component Info
            var ncInfo = transitionEditorRoot.componentTransition.getNode(newNodeIndex);

            // Check Node Component Info
            if (ncInfo !== null) {

                // Create New Node
                var newNode = transitionEditorRoot.createNode(ncInfo, transitionEditorRoot);

                // Check New Node
                if (newNode !== null) {
                    // Append To Children Node Model
                    transitionNodesModel.insert(newNodeIndex, newNode);
                    // Set Width
                    newNode.width = Qt.binding(function() { return transitionNodesColumn.width; });
                    // Update Child Indexes
                    updateChildIndexes(0);
                }
            }
        }
    }

    // Remove Transition Node
    function removeNode(nodeIndex) {
        // Check Empty Node
        if (emptyNode.childIndex <= nodeIndex && transitionEditorRoot.grabbedNodeParent === transitionEditorRoot) {
            // Inc Node Index
            nodeIndex++;
        }

        // Get Node Object
        var nodeObject = transitionNodesModel.get(nodeIndex);
        // Check Node Object
        if (nodeObject !== null) {
            console.log("DTransitionEditor.removeNode - nodeIndex: " + nodeIndex);
            // Remove Node Object
            transitionNodesModel.remove(nodeIndex);
            // Destroy
            nodeObject.destroy();
        }

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Take Node
    function takeNode(nodeIndex) {
        // Get Node Object
        var nodeObject = transitionNodesModel.get(nodeIndex);

        // Check Node Object
        if (nodeObject !== null) {
            console.log("DTransitionEditor.takeNode - nodeIndex: " + nodeIndex);

            // Remove Node Object
            transitionNodesModel.remove(nodeIndex);

            // Update Child Indexes
            updateChildIndexes(0);

            return nodeObject;
        }

        return null;
    }

    // Mode transition Node
    function moveNode(nodeIndex, targetIndex) {
        // Remove Empty Node First
        removeEmptyNode();

        console.log("DTransitionEditor.moveNode - nodeIndex: " + nodeIndex + " - targetIndex: " + targetIndex);

        // Move Item
        transitionNodesModel.move(nodeIndex, targetIndex);

        // Update Child Indexes
        updateChildIndexes(0);
    }

    // Insert Empty Node
    function insertEmptyNode(newNodeIndex) {
        //console.log("DTransitionTreeNode.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + transitionEditorRoot.grabbedChildIndex);

        // Init Target Index
        var targetIndex = newNodeIndex;

        // Check Grabbed Child Index & If It's In The Same Node
        if (transitionEditorRoot.grabbedChildIndex !== -1 && transitionEditorRoot.grabbedChildIndex < newNodeIndex) {
            // Dec Target Index
            targetIndex--;
        }

        // Check Target Index
        if (targetIndex === transitionEditorRoot.grabbedChildIndex) {
            console.warn("DTransitionEditor.insertEmptyNode - SAME ITEM POSITION!");
            return;
        }

        //console.log("DTransitionEditor.insertEmptyNode - newNodeIndex: " + newNodeIndex + " - grabbedChildIndex: " + transitionEditorRoot.grabbedChildIndex);
        // Set Current Node For Animating Height
        transitionEditorRoot.currentNode = null;
        // Insert Empty Node
        transitionNodesModel.insert(newNodeIndex, emptyNode);
        // Set Child Index
        emptyNode.childIndex = newNodeIndex;
        // Show Empty Node
        emptyNode.showEmptyNode();
        // Update
        updateChildIndexes(newNodeIndex);
    }

    // Remove Empty Node
    function removeEmptyNodeFromNodes() {
        // Check Empty Node Index
        if (emptyNode.childIndex >= 0) {
            //console.log("DTransitionEditor.removeEmptyNode - childIndex: " + emptyNode.childIndex);
            // Set Current Node For Animating Height
            transitionEditorRoot.currentNode = null;
            // Remove Empty Node
            transitionNodesModel.remove(emptyNode.childIndex);
            // Hide Empty Node
            emptyNode.hideEmptyNode();
            // Reset Empty Node Child Index
            emptyNode.childIndex = -1;
            // Update Child Indexes
            updateChildIndexes(0);
        } else {
            //console.warn("DTransitionEditor.removeEmptyNode - NO CHILD INDEX!!!!");
        }
    }

    // Updte Child Indexes
    function updateChildIndexes(emptyNodeIndex) {
        // Get Children Nodes Count
        var nCount = transitionNodesModel.count;
        // Iterate Through Child Nodes
        for (var i=emptyNodeIndex; i<nCount; i++) {
            // Set Child Indexes
            var node = transitionNodesModel.get(i);
            // Set Child Index
            node.childIndex = i;
        }
    }

    // Disc Button
    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: acceptTransition();
    }

    Column {
        id: transitionEditorColumn

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: discButton.left
        anchors.rightMargin: DStyle.defaultMargin * 3
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2

        spacing: DStyle.defaultSpacing

        Row {
            id: fromToRow
            spacing: DStyle.defaultSpacing

            DText {
                id: fromLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "From:"
            }

            DOption {
                id: fromOption
                width: (transitionEditorColumn.width - fromLabel.width - toLabel.width - DStyle.defaultSpacing * 3) / 2
                anchors.verticalCenter: parent.verticalCenter

                model: []

                onZChanged: {
                    parent.z = fromOption.z;
                }

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            transitionEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            toOption.setOptionFocus(true);
                        break;
                    }
                }

                onCurrentIndexChanged: {
                    // Reset Invalid Value
                    fromOption.invalidValue = false;
                    // Reset Invalid Value
                    toOption.invalidValue = false;
                }
            }

            DText {
                id: toLabel
                width: fromLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "To:"
            }

            DOption {
                id: toOption
                width: (transitionEditorColumn.width - fromLabel.width - toLabel.width - DStyle.defaultSpacing * 3) / 2
                anchors.verticalCenter: parent.verticalCenter

                model: []

                onZChanged: {
                    parent.z = toOption.z;
                }

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            transitionEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            addTransitionOption.setOptionFocus(true);
                        break;
                    }
                }

                onCurrentIndexChanged: {
                    // Reset Invalid Value
                    fromOption.invalidValue = false;
                    // Reset Invalid Value
                    toOption.invalidValue = false;
                }
            }
        }

        // Place Holder
        Item {
            width: parent.width
            height: 1
        }

        // Transitions Container
        Item {
            id: transitionsContainer
            width: parent.width
            height: transitionNodesColumn.height
            Behavior on height { DAnimation { } }
            opacity: height > 0 ? 1.0 : 0.0
            Behavior on opacity { DFadeAnimation { } }
            visible: opacity > 0.0
            clip: true

            // Child Nodes Object Model
            ObjectModel {
                id: transitionNodesModel

                // ...
            }

            // Transition Nodes Column
            Column {
                id: transitionNodesColumn
                width: parent.width

                // Transition Nodes Repeater
                Repeater {
                    id: nodeRepeater
                    model: transitionNodesModel
                }

                move: Transition {
                    PropertyAnimation { properties: "y"; duration: DStyle.animDuration }
                }
            }
        }

        // No Nodes text
        DText {
            width: parent.width
            opacity: transitionEditorRoot.componentTransition && transitionEditorRoot.componentTransition.nodesCount === 0 ? 1.0 : 0.0
            Behavior on opacity { DFadeAnimation { } }
            visible: opacity > 0.0
            horizontalAlignment: Text.AlignHCenter
            text: "No Transition Nodes"
        }

        // Place Holder
        Item {
            width: parent.width
            height: 1
        }

        DOption {
            id: addTransitionOption
            width: parent.width

            model: []

            showSelector: false

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        fromOption.setOptionFocus(true);
                    break;
                }
            }

            onItemSelected: {
                // Check Item Index
                if (itemIndex > 0) {
                    // Set Enabled
                    addTransitionOption.enabled = false;
                    // Signal New Transition Node
                    transitionEditorRoot.newTransitionNode(itemIndex - 1);
                    // Reset Current Index
                    currentIndex = 0;
                }
            }
        }
    }

    // Empty Node
    DTransitionTreeEmptyNode {
        id: emptyNode
        width: transitionNodesColumn.width - CONSTS.defaultNodeTreeItemHeight * 0.5
        anchors.right: parent ? parent.right : undefined
        transitionEditorRoot: transitionEditorRoot
        parentNode: transitionEditorRoot
    }

    // Grabbed Node Overlay
    DTransitionTreeNode {
        id: grabbedNode

        visible: false

        dropAreasVisible: false
        enableDropAreasVisibility: false

        property bool dragActive: false

        onDragActiveChanged: {
            //console.log("DTransitionEditor.grabbedNode.onDragActiveChanged - dragActive: " + dragActive);

            // Cheeck Drag Active
            if (dragActive) {
                // Start Drag
                Drag.start();
            } else {
                // Stop Drag
                Drag.drop();

                // Emit Remove Empty Node Signal
                transitionEditorRoot.removeEmptyNode();
            }
        }

        Drag.active: dragActive

        Drag.hotSpot.x: grabbedNode.width * 0.5 //transitionEditorRoot.nodePressX
        Drag.hotSpot.y: grabbedNode.height * 0.5 //transitionEditorRoot.nodePressY

        Drag.source: grabbedNode.componentInfo
        Drag.keys: [ CONSTS.childComponentDragKey ]
    }
}
