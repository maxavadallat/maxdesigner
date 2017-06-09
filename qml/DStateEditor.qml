import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: stateEditorRoot

    property ComponentState componentState: null

    property ComponentStatesModel statesModel: propertiesController.statesModel

    property bool newState: false

    property Connections childPaneConnections: Connections {
        target: childPane

        onAccepted: {
            // Check New Property Change
            if (childPane.newPropertyChange) {
                // Reset New Property Change
                childPane.newPropertyChange = false;
                // Append Property Change
                componentState.appendPropertyChange(childPane.componentPropertyChange);
                // Reset Component Property Change
                childPane.componentPropertyChange = null;

            } else {

                // ...

            }
        }

        onRejected: {
            // Check New Property Change
            if (childPane.newPropertyChange) {
                // Reset New Property Change
                childPane.newPropertyChange = false;
                // Discard New Property Change
                componentState.discardNewPropertyChange();
                // Reset Component Property Change
                childPane.componentPropertyChange = null;

                // ....

            } else {

                // ....

            }
        }
    }

    hideToSide: hideToRight

    title: "State Editor"

    creationWidth: 460
    creationHeight: stateEditorColumn.height + 44

    minWidth: 460
    minHeight: stateEditorColumn.height + 44

    enableResize: true

    resizeTopEnabled: false
    resizeBottomEnabled: false

    enableHideButton: false

    signal newPropertyChange()
    signal editPropertyChange(var index)

    onComponentStateChanged: {
        //console.log("DStateEditor.onComponentStateChanged - name: " + (componentState ? componentState.stateName : ""));

        // Check Child Pane
        if (stateEditorRoot.childPane !== null) {
            // Set Component State
            stateEditorRoot.childPane.componentState = stateEditorRoot.componentState;
        }
    }

    onNewPropertyChange: {
        // Check Child Pane
        if (childPane !== null && componentState !== null) {
            // Set New Property Change
            childPane.newPropertyChange = true;
            // Set Property Change
            childPane.componentPropertyChange = componentState.createNewPropertyChange();
            // Show Child Pane
            childPane.show();
        }
    }

    onEditPropertyChange: {
        // Check Child Pane
        if (childPane !== null && componentState !== null) {
            // Set New Property Change
            childPane.newPropertyChange = false;
            // Set Property Change
            childPane.componentPropertyChange = componentState.getPropertyChange(index);
            // Show Child Pane
            childPane.show();
        }
    }

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {

        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);

            // Reset Creation Height
            stateEditorRoot.creationHeight = Qt.binding(function() { return stateEditorColumn.height + 44; });
            // reset Min Height
            stateEditorRoot.minHeight = Qt.binding(function() { return stateEditorColumn.height + 44; });

        } else if (newState === stateCreate) {
            // Reset Focus
            nameEditor.setEditorFocus(false, false);
            // Reset Focus
            whenEditor.setEditorFocus(false, false);
        }
    }

    onChildTransitionFinished: {
        // Check New State
        if (newState === stateCreate) {
            // Set Editor Focus
            nameEditor.setEditorFocus(true, true);
        }
    }

    onAccepted: {
        // Update Component State
        updateComponentState();

        // Check New State
        if (stateEditorRoot.newState) {
            // Reset New State
            stateEditorRoot.newState = false;
            // Append State
            stateEditorRoot.statesModel.appendState(stateEditorRoot.componentState);
            // ...
        } else {
            // Update Current State

        }
    }

    onRejected: {
        // Check New State
        if (stateEditorRoot.newState) {
            // Reset New State
            stateEditorRoot.newState = false;
            // Discard New State
            stateEditorRoot.statesModel.discardNewState();
        }
    }

    // Get State Valid
    function stateValid() {
        // Check States Model
        if (stateEditorRoot.statesModel !== null) {
            // Check If Valid by the States Model
            if (stateEditorRoot.statesModel.stateValid(nameEditor.editedText, stateEditorRoot.newState)) {
                return true;
            }
        }

        // Set Invalid Value
        nameEditor.invalidValue = true;

        return false;
    }

    // Update Component State
    function updateComponentState() {
        // Check Component State
        if (stateEditorRoot.componentState !== null) {
            console.log("DStateEditor.resetStateEditor");

            // Check State Name
            if (stateEditorRoot.componentState.stateName !== nameEditor.editedText) {
                // Set Name
                stateEditorRoot.componentState.stateName = nameEditor.editedText;
            }

            // Check State When
            if (stateEditorRoot.componentState.stateWhen !== whenEditor.editedText) {
                // Set When
                stateEditorRoot.componentState.stateWhen = whenEditor.editedText;
            }

            // Check State Model
            if (stateEditorRoot.statesModel !== null) {
                // Update Selected State
                stateEditorRoot.statesModel.updateSelectedState();
            }

            // ...
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If State Valid
            if (stateEditorRoot.stateValid()) {
                // Emit Accepted Signal
                stateEditorRoot.accepted();
                // Reset
                stateEditorRoot.dismissPane(true);
            }
        }
    }

    Column {
        id: stateEditorColumn

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2 + discButton.width + 16
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            id: nameRow
            spacing: DStyle.defaultSpacing

            DText {
                id: nameLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "name:"
            }

            DTextInput {
                id: nameEditor
                width: (stateEditorColumn.width - nameLabel.width - whenLabel.width - DStyle.defaultSpacing * 3) * 0.5
                anchors.verticalCenter: parent.verticalCenter
                text: stateEditorRoot.componentState ? stateEditorRoot.componentState.stateName : ""

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            stateEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            whenEditor.setEditorFocus(true, true);
                        break;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    nameEditor.invalidValue = false;
                }

                onAccepted: {
                    // Check If State Valid
                    if (stateEditorRoot.stateValid()) {
                        // Emit Accepted Signal
                        stateEditorRoot.accepted();
                        // Reset
                        stateEditorRoot.dismissPane(true);
                    }
                }
            }

            DText {
                id: whenLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "when:"
            }

            DTextInput {
                id: whenEditor
                width: nameEditor.width
                anchors.verticalCenter: parent.verticalCenter
                text: stateEditorRoot.componentState ? stateEditorRoot.componentState.stateWhen : ""

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            stateEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            nameEditor.setEditorFocus(true, true);
                        break;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    whenEditor.invalidValue = false;
                }

                onAccepted: {
                    // Check If State Valid
                    if (stateEditorRoot.stateValid()) {
                        // Emit Accepted Signal
                        stateEditorRoot.accepted();
                        // Reset
                        stateEditorRoot.dismissPane(true);
                    }
                }
            }
        }

        Item {
            width: parent.width
            height: propertyChangesList.count > 0 ? 2 : 0
            Behavior on height { DAnimation { } }
            visible: height > 0
        }

        Item {
            id: propertyChangesContainer
            width: parent.width
            height: propertyChangesList.count * CONSTS.defaultPaneItemHeight //propertyChangesList.contentHeight
            Behavior on height { DAnimation { } }
            visible: height > 0

            DListView {
                id: propertyChangesList
                anchors.fill: parent

                model: stateEditorRoot.componentState

                delegate: DPropertyChangeDelegate {
                    width: propertyChangesList.width

                    itemIndex: index

                    propertyChangeTarget: pcTarget
                    propertyChangeProperty: pcProperty
                    propertyChangeValue: pcValue

                    onDoubleClicked: {
                        // Emit Edit Property Change Signal
                        stateEditorRoot.editPropertyChange(index);
                    }

                    onItemActionClicked: {
                        // Remove Property Change
                        if (stateEditorRoot.componentState !== null) {
                            // Remove Property Change
                            stateEditorRoot.componentState.removePropertyChange(index);
                        }
                    }
                }
            }
        }

        Item {
            width: parent.width
            height: 2
        }

        DButton {
            width: parent.width
            text: "Add Property Change"
            enabled: {
                // Check Compoennt State
                if (stateEditorRoot.componentState === null) {
                    return false;
                }

                // Check Child Pane
                if (stateEditorRoot.childPane !== null && stateEditorRoot.childPane.state !== stateEditorRoot.childPane.stateCreate) {
                    return false;
                }

                return true;
            }

            onClicked: {
                // Signal New Property Change
                stateEditorRoot.newPropertyChange();
            }
        }
    }
}
