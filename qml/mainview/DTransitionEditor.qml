import QtQuick 2.0

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
    property AnimationComponentsModel animsModel: mainController.animationsModel

    // States Count
    property int statesCount: statesModel ? statesModel.rowCount() : 0

    // New Transition
    property bool newTransition: false

    // Child Pane Connections
    property Connections childPaneConnections: Connections {
        target: childPane

        onAccepted: {

            // ...
        }

        onRejected: {

            // ....

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
            addTransitionOption.removeItem(aIndex);
        }
    }

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

    signal newTransitionNode(var nodeType)
    signal editTransitionNode()

    Component.onCompleted: {
        // Build Anims
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
        // Clear Transitions
        clearTransitions();
        // Clear From States Option List
        clearFromStates();
        // Clear To States Option List
        clearToStates();

        // Update States Count
        transitionEditorRoot.statesCount = transitionEditorRoot.statesModel ? transitionEditorRoot.statesModel.rowCount() : 0

        // ...

        // Build From States Option List
        buildFromStates();
        // Build To States Option List
        buildToStates();
        // Build Transitions
        buildTransitions();

        // ...
    }

    // On Accepted Slot
    onAccepted: {
        console.log("DTransitionEditor.onAccepted");

        // Check If New Transition
        if (transitionEditorRoot.newTransition) {
            // Append Transition
            transitionEditorRoot.transitionsModel.appendTransition(transitionEditorRoot.componentTransition);
        } else {

        }

        // ...
    }

    onRejected: {
        //console.log("DTransitionEditor.onRejected");
        // Discard New Transition
        transitionEditorRoot.transitionsModel.discardNewTransition();
    }

    // Build From States Option List
    function buildFromStates() {
        //console.log("DTransitionEditor.buildFromStates");

        // Check Component Info
        if (transitionEditorRoot.componentInfo !== null && transitionEditorRoot.statesCount > 0) {
            console.log("DTransitionEditor.buildFromStates - statesCount: " + transitionEditorRoot.statesCount);

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
        console.log("DTransitionEditor.clearFromStates");
        // Clear Item Model
        fromOption.clearItemModel();
    }

    // Build To States Option List
    function buildToStates() {
        //console.log("DTransitionEditor.buildToStates");

        // Check Component Info
        if (transitionEditorRoot.componentInfo !== null && transitionEditorRoot.statesCount > 0) {
            console.log("DTransitionEditor.buildToStates - statesCount: " + transitionEditorRoot.statesCount);

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
        console.log("DTransitionEditor.clearToStates");

        // Clear Item Model
        toOption.clearItemModel();

        // ...
    }

    // Build Anims
    function buildAnims() {
        // Get Anim Components Model Count
        var acCount = transitionEditorRoot.animsModel ? transitionEditorRoot.animsModel.rowCount() : 0;

        console.log("#### DTransitionEditor.buildAnims - acCount: " + acCount);

        // Iterate Through Animation COmponents
        for (var i=0; i<acCount; i++) {
            // Append Animation Item
            addTransitionOption.appendItem("Add " + transitionEditorRoot.animsModel.getNameByIndex(i), false);
        }
    }

    // Build Transitions
    function buildTransitions() {
        // Check Component Info
        if (transitionEditorRoot.componentInfo !== null && transitionEditorRoot.statesCount > 0) {
            console.log("DTransitionEditor.buildTransitions");

            // ...
        }
    }

    // Clear Transitions
    function clearTransitions() {
        console.log("DTransitionEditor.clearTransitions");

        // ...
    }


    // Reset Transition Editor
    function resetTransitionEditor() {
        console.log("DTransitionEditor.resetTransitionEditor");

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


    // Disc Button
    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Transition Valid
            if (validateTransition()) {

                // Emit Accepted Signal
                transitionEditorRoot.accepted();

                // ...

            }
        }
    }

    Column {
        id: transitionEditorColumn

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2 + discButton.width + 16
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            id: fromToRow
            anchors.left: parent.left
            anchors.leftMargin: DStyle.defaultMargin
            spacing: DStyle.defaultSpacing

            property int optionWidth: 132

            DText {
                id: fromLabel
                //width: 48
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "From:"
            }

            DOption {
                id: fromOption
                width: fromToRow.optionWidth
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
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "To:"
            }

            DOption {
                id: toOption
                width: fromToRow.optionWidth
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
            height: 2
            //height: transitionsList.count > 0 ? 2 : 0
            Behavior on height { DAnimation { } }
            visible: height > 0
        }

        // Transitions Container
        Item {
            id: transitionsContainer
            width: parent.width
            //height: transitionsList.count * CONSTS.defaultPaneItemHeight //propertyChangesList.contentHeight
            Behavior on height { DAnimation { } }
            visible: height > 0

            // Transition Nodes

                // Model

                // Delegate


            //}
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
            height: 2
        }

        DOption {
            id: addTransitionOption
            width: fromToRow.width
            anchors.left: parent.left
            anchors.leftMargin: DStyle.defaultMargin

            model: []

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
                // Check Selected Item Index
                if (itemIndex === 0) {
                    return;
                }

                // Check Selected Item Index
                if (itemIndex > 2) {
                    // Set Enabled
                    addTransitionOption.enabled = false;
                }

                // Signal New Transition Node
                transitionEditorRoot.newTransitionNode(itemIndex);
            }
        }
    }
}
