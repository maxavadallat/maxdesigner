import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: formulaEditorRoot

    property string propertyName: ""
    property string propertyValue: ""
    property string propertyType: ""
    property string propertyFormula: ""

    property ComponentOwnPropertiesModel ownPropertiesModel: propertiesController.ownPropertiesModel
    property ComponentPropertiesModel propertiesModel: propertiesController.propertiesModel

    property bool ownProperty: true

    title: propertyName + ":"

    hideToSide: hideToRight

    creationWidth: 358
    creationHeight: 122

    minWidth: 358
    minHeight: 122

    enablePosOverlay: false
    enableSizeOverlay: false

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Property Editor
            resetFormulaEditor();
        }

        // Check New State
        if (newState === stateHidden) {
            // Reset Focus
            formulaEditor.setEditorFocus(false);
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Editor Focus
            formulaEditor.setEditorFocus(true, false);
        }
    }

    // Generate Formula From Property Value
    function generateFormula() {
        // Init Formula Text
        var formulaText = "";

        // Get { First Pos
        var ocbPos = formulaEditorRoot.propertyValue.indexOf("{");
        // Get } Last Pos
        var ccbPos = formulaEditorRoot.propertyValue.lastIndexOf("}");
        // Check Property Value
        if (ocbPos >= 0 && ccbPos > ocbPos) {
            return formulaEditorRoot.propertyValue;
        } else {
            // Set Formula Text
            formulaText = "{<br>    return " + formulaEditorRoot.propertyValue + ";<br>}<br>";
        }

        return formulaText;
    }

    // Reset Formula Editor
    function resetFormulaEditor() {
        // Reset Invalid Source
        formulaEditor.invalidSource = false;
        // Check Property Name
        if (formulaEditorRoot.propertyName !== "") {
            // Check Own Property & Own Properties Model
            if (formulaEditorRoot.ownProperty && formulaEditorRoot.ownPropertiesModel !== null) {
                // Get Property Value
                formulaEditorRoot.propertyValue = formulaEditorRoot.ownPropertiesModel.componentPropertyValue(formulaEditorRoot.propertyName);
                // Generate Property Formula
                formulaEditorRoot.propertyFormula = generateFormula();
            // Check Properties Model
            } else if (formulaEditorRoot.propertiesModel !== null) {
                // Get Property Value
                formulaEditorRoot.propertyValue = formulaEditorRoot.ownPropertiesModel.componentPropertyValue(formulaEditorRoot.propertyName);
                // Generate Property Formula
                formulaEditorRoot.propertyFormula = generateFormula();
            }
        } else {
            // Set Property Formula
            formulaEditorRoot.propertyFormula = "{<br><br>}<br>";
        }

        // Set Source Text
        formulaEditor.setText(formulaEditorRoot.propertyFormula);
    }

    // Check If Formula Source Valid
    function formulaSourceValid() {
        // Init Formula Text
        var formulaText = formulaEditor.getText();
        //formulaText
        console.log("DFormulaEditor.slotSourceValid - formulaText: " + formulaText);

        // Get { First Pos
        var ocbPos = formulaText.indexOf("{");
        // Check { First Pos
        if (ocbPos < 0) {
            return false;
        }

        // Get } Last Pos
        var ccbPos = formulaText.lastIndexOf("}");
        // Check } Last Pos
        if (ccbPos <= ocbPos) {
            return false;
        }

        // ...

        return true;
    }

    DSourceCodeEditor {
        id: formulaEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: formulaEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            formulaEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            formulaEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            formulaEditor.invalidSource = false;
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Formula Valid
            if (formulaEditorRoot.formulaSourceValid()) {
                // Emit Accepted Signal
                formulaEditorRoot.accepted();
            } else {
                // Set Invalid Source
                formulaEditor.invalidSource = true;
            }
        }
    }
}
