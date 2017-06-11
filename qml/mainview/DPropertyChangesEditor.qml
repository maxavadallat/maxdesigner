import QtQuick 2.0

import enginecomponents 0.1

import "../style"
import "../controls"
import "../animations"

DPaneBase {
    id: propertyChangesEditorRoot

    anchors.horizontalCenter: parentPane ? parentPane.horizontalCenter : undefined

    property bool newPropertyChange: false

    // Component State
    property ComponentState componentState: null
    // Component State Property Change
    property ComponentPropertyChange componentPropertyChange: null

    title: "Property Change"

    hideToSide: hideToTop

    creationWidth: 400
    creationHeight: 152

    minWidth: 400
    minHeight: 152

    enableResize: true
    enableHideButton: false

    resizeTopEnabled: false
    resizeBottomEnabled: false

    enableDrag: false

    state: stateCreate

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            targetEditor.setEditorFocus(true, true);
        }
    }

    // Check If Property Change Valid
    function propertyChangeValid() {
        // Init Result
        var result = true;

        // Check Target Editor
        if (targetEditor.editedText.length === 0) {
            // Set Invalid Valud
            targetEditor.invalidValue = true;
            // Set Result
            result = false;
        }

        // Check Property Name Editor
        if (propertyEditor.editedText.length === 0) {
            // Set Invalid Value
            propertyEditor.invalidValue = true;
            // Set Result
            result = false;
        }

        // ...

        return result;
    }

    // Update Property Change
    function updatePropertyChange() {
        // Check Property Change
        if (propertyChangesEditorRoot.componentPropertyChange !== null) {
            // Check Target
            if (propertyChangesEditorRoot.componentPropertyChange.propertyChangeTarget !== targetEditor.editedText) {
                // Set Target
                propertyChangesEditorRoot.componentPropertyChange.propertyChangeTarget = targetEditor.editedText;
            }

            // Check Property
            if (propertyChangesEditorRoot.componentPropertyChange.propertyChangeProperty !== propertyEditor.editedText) {
                // Set Property
                propertyChangesEditorRoot.componentPropertyChange.propertyChangeProperty = propertyEditor.editedText;
            }

            // Check Value
            if (propertyChangesEditorRoot.componentPropertyChange.propertyChangeValue !== valueEditor.editedText) {
                // Set Value
                propertyChangesEditorRoot.componentPropertyChange.propertyChangeValue = valueEditor.editedText;
            }

            // Check Component State
            if (propertyChangesEditorRoot.componentState !== null) {
                // Update Selected Property Change
                propertyChangesEditorRoot.componentState.updateSelectedPropertyChange();
            }

            // ...
        }
    }

    // Accept Property Changes
    function acceptPropertyChanges() {
        // Check If Property Change Valid
        if (propertyChangesEditorRoot.propertyChangeValid()) {
            // Update Property Change
            propertyChangesEditorRoot.updatePropertyChange();
            // Emit Accepted Signal
            propertyChangesEditorRoot.accepted();
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: acceptPropertyChanges();
    }

    Column {
        id: proertyChangesColumn
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.right: discButton.left
        anchors.rightMargin: DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            id: targetEditorRow
            spacing: DStyle.defaultSpacing

            DText {
                id: targetLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "target:"
            }

            DTextInput {
                id: targetEditor
                width: propertyEditor.width
                text: propertyChangesEditorRoot.componentPropertyChange ? propertyChangesEditorRoot.componentPropertyChange.propertyChangeTarget : ""

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            propertyEditor.setEditorFocus(true, true);
                        break;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    targetEditor.invalidValue = false;
                }

                onAccepted: {
                    // Accept Property Changes
                    propertyChangesEditorRoot.acceptPropertyChanges();
                }
            }
        }

        Row {
            id: propertyEditorRow
            spacing: DStyle.defaultSpacing

            DText {
                id: propertyLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "property:"
            }

            DTextInput {
                id: propertyEditor
                width: proertyChangesColumn.width - propertyLabel.width - DStyle.defaultSpacing
                text: propertyChangesEditorRoot.componentPropertyChange ? propertyChangesEditorRoot.componentPropertyChange.propertyChangeProperty : ""

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            valueEditor.setEditorFocus(true, true);
                        break;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    propertyEditor.invalidValue = false;
                }

                onAccepted: {
                    // Accept Property Changes
                    propertyChangesEditorRoot.acceptPropertyChanges();
                }
            }
        }

        Row {
            id: valueEditorRow
            spacing: DStyle.defaultSpacing

            DText {
                id: valueLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "value:"
            }

            DTextInput {
                id: valueEditor
                width: propertyEditor.width
                text: propertyChangesEditorRoot.componentPropertyChange ? propertyChangesEditorRoot.componentPropertyChange.propertyChangeValue : ""

                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            targetEditor.setEditorFocus(true, true);
                        break;
                    }
                }

                onTextEdited: {
                    // Reset Invalid Value
                    valueEditor.invalidValue = false;
                }

                onAccepted: {
                    // Accept Property Changes
                    propertyChangesEditorRoot.acceptPropertyChanges();
                }
            }
        }
    }
}
