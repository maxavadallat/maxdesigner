import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: formulaEditorRoot

    property string propertyName: ""
    property string propertyValue: ""
    property string propertyType: ""
    property string propertyFormula: ""

    property ComponentInfo componentInfo: propertiesController.focusedComponent
//    property ComponentOwnPropertiesModel ownPropertiesModel: propertiesController.ownPropertiesModel
//    property ComponentPropertiesModel propertiesModel: propertiesController.propertiesModel

    property bool ownProperty: true

    title: "Edit Property"

    hideToSide: hideToRight

    creationWidth: 400
    creationHeight: 200

    minWidth: 400
    minHeight: 200

    enablePosOverlay: false
    enableSizeOverlay: false

    enableDrag: true
    enableResize: true

    enableHideButton: false

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Property Editor
            resetFormulaEditor();
        }

        // Check New State
        if (newState === stateHidden) {
            // Reset Focus
            formulaEditor.setEditorFocus(false, false);
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Editor Focus
            formulaEditor.setEditorFocus(true, false);
        }
    }

    onComponentInfoChanged: {
        // Close Formula Editor
        formulaEditorRoot.rejected();
    }

//    // Generate Formula From Property Value
//    function generateFormula() {

//        // Init Formula Text
//        var formulaText = "";

//        // Get { First Pos
//        var ocbPos = formulaEditorRoot.propertyValue.indexOf("{");
//        // Get } Last Pos
//        var ccbPos = formulaEditorRoot.propertyValue.lastIndexOf("}");
//        // Check Property Value
//        if (ocbPos >= 0 && ccbPos > ocbPos) {
//            return formulaEditorRoot.propertyValue;
//        } else {
//            // Set Formula Text
//            formulaText = "{<br>    return " + formulaEditorRoot.propertyValue + ";<br>}<br>";
//        }

//        return formulaText;
//    }

    // Reset Formula Editor
    function resetFormulaEditor() {
        // Reset Invalid Source
        formulaEditor.invalidSource = false;

        // Check Component Info
        if (formulaEditorRoot.componentInfo === null) {
            formulaEditor.setText("");
            return false;
        }

        // Get Property Value
        var pValue = formulaEditorRoot.componentInfo.propertyValue(formulaEditorRoot.propertyName, true);

        // Set Formula Editor Text
        formulaEditor.setText(formulaEditorRoot.propertyName + ": " + (pValue.charCodeAt(0) === 16 ? pValue.substr(1) : pValue));

        // ...
    }

    // Check If Formula Source Valid
    function formulaSourceValid() {
        // Init Formula Text
        var formulaText = formulaEditor.getText();
        //formulaText
        //console.log("DFormulaEditor.formulaSourceValid - formulaText: " + formulaText);

        // Check Formula Text
        if (!formulaText.startsWith(formulaEditorRoot.propertyName)) {
            return false;
        }

        // Get Colon First Index
        var cfIndex = formulaText.indexOf(":");

        // Check Colon Index
        if (cfIndex === -1) {
            return false;
        }

        // TODO: More Checking

        // Set Property Formula
        formulaEditorRoot.propertyFormula = String.fromCharCode(16) + formulaText.substr(cfIndex + 1).trim();

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

        onSourceEditorActivated: formulaEditorRoot.bringToFront();
        onEscapeClicked: formulaEditorRoot.rejected();
        onSourceTextChanged: formulaEditor.invalidSource = false;
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
