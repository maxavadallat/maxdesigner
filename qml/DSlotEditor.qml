import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: slotEditorRoot

    property string slotName: ""
    property string slotSource: ""

    property ComponentSlot componentSlot: null
    property ComponentSlotsModel slotsModel: propertiesController.slotsModel

    property bool newSlot: false

    title: "Slot"

    hideToSide: hideToRight

    creationWidth: 500
    creationHeight: 320

    minWidth: 500
    minHeight: 320

    enablePosOverlay: false
    enableSizeOverlay: false

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset SLot Editor
            resetSlotEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set EDitor Focus
            slotSourceEditor.setEditorFocus(true, false);
        }
    }

    // Reset Slot Editor
    function resetSlotEditor() {
        // Init Source Text
        var sourceText = "";
        // Check Component Slot
        if (slotEditorRoot.componentSlot !== null) {
            // Check Slot Name
            if (slotEditorRoot.componentSlot.slotName !== "") {
                // Set Source Text
                sourceText = slotEditorRoot.componentSlot.slotName + ": {";
                sourceText += (slotEditorRoot.componentSlot.slotSource + "}\n");
            } else {
                // Set Source
                sourceText = "onNewSlot: {\n\n}\n";
            }
        } else {
            // ...
        }

        // Set Source Text
        slotSourceEditor.setText(sourceText);
    }

    // Update Component Slot
    function updateComponentSlot() {
        // Check Component Slot
        if (slotEditorRoot.componentSlot !== null) {
            // Set SLot Name
            slotEditorRoot.componentSlot.slotName = slotEditorRoot.slotName;
            // Set Slot Source
            slotEditorRoot.componentSlot.slotSource = slotEditorRoot.slotSource;
        }
    }

    // Check If Slot Source Valid
    function slotSourceValid() {
        // Get Source Text
        var sText = slotSourceEditor.getText().trim();

        console.log("DSlotEditor.slotSourceValid - sText: " + sText);
        // Get Colon Position
        var colonPos = sText.indexOf(":");
        // Check Colon Position
        if (colonPos < 1 ) {
            return false;
        }

        // Get SLot Elements
        var sElements = sText.split(":");

        // Get Opening Bracket Pos
        var obPos = sElements[1].indexOf("{");
        // Check Opening Bracket Pos
        if (obPos < 0) {
            return false;
        }

        // Get Closing Bracket Pos
        var cbPos = sElements[1].lastIndexOf("}");
        // Check CLosing Bracket Pos
        if (cbPos < obPos) {
            return false;
        }

        // Set Slot Name
        slotEditorRoot.slotName = sElements[0];
        // Check Bracket Positions
        if (cbPos - obPos === 1) {
            // Set SLot Source
            slotEditorRoot.slotSource = "\n";
        } else {
            // Set SLot Source
            slotEditorRoot.slotSource = sElements[1].substring(obPos + 1, cbPos - 1) + "\n";
        }

        // Check Compoennt Slot Model
        if (slotEditorRoot.slotsModel !== null) {
            return slotEditorRoot.slotsModel.slotValid(slotEditorRoot.slotName);
        }

        // ...

        return false;
    }

    // ...

    DSourceCodeEditor {
        id: slotSourceEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: slotEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: diskButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            slotEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            slotEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            slotSourceEditor.invalidSource = false;
        }
    }

    DDisc {
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            if (slotSourceValid()) {
                // Parse Slot Source
                updateComponentSlot();
                // Emit Accepted Signal
                slotEditorRoot.accepted();
            } else {
                // Set Invalid Source
                slotSourceEditor.invalidSource = true;
            }
        }
    }
}
