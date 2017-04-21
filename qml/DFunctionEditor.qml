import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: functionEditorRoot

    property string functionName: "function"
    property string functionParameters: ""
    property string functionSource: ""

    property ComponentFunction componentFunction: null
    property ComponentFunctionsModel functionsModel: propertiesController.functionsModel
    property bool newFunction: false

    title: "Function"

    hideToSide: hideToRight

    creationWidth: 500
    creationHeight: 360

    minWidth: 500
    minHeight: 360

    enablePosOverlay: false
    enableSizeOverlay: false

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Function Editor
            resetFunctionEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set EDitor Focus
            functionSourceEditor.setEditorFocus(true, false);
        }
    }

    // Reset Function Editor
    function resetFunctionEditor() {
        // Init Source Text
        var sourceText = "";

        // Check Component Function
        if (functionEditorRoot.componentFunction !== null) {
            // Set Function Name
            functionEditorRoot.functionName = functionEditorRoot.componentFunction.functionName;
            // Check Parameters
            if (functionEditorRoot.componentFunction.functionParameters.length > 0) {
                // Set Function Parameters
                functionEditorRoot.functionParameters = functionEditorRoot.componentFunction.functionParameters.join(", ");
            } else {
                // Set Function Parameters
                functionEditorRoot.functionParameters = "";
            }

            // Set Function Source
            functionEditorRoot.functionSource = functionEditorRoot.componentFunction.functionSource;

            // Check Function Name
            if (functionEditorRoot.functionName !== "") {
                // Set Source Text
                sourceText = functionEditorRoot.functionName + "(" + functionEditorRoot.functionParameters + ") {";
                sourceText += functionEditorRoot.functionSource;
                sourceText += "}\n";
            } else {
                // Set SourceText
                sourceText = "newFunction() {\n\n}\n";
            }
        } else {
            // Reset Function Name
            functionEditorRoot.functionName = "";
            // Reset Function Parameters
            functionEditorRoot.functionParameters = "";
            // Reset Function Source
            functionEditorRoot.functionSource = "";
        }

        // Set Source Text
        functionSourceEditor.setText(sourceText);
    }

    // Update Component Function
    function updateComponentFunction() {
        // Check Component Function
        if (functionEditorRoot.componentFunction !== null) {
            // Set Function Name
            functionEditorRoot.componentFunction.functionName = functionEditorRoot.functionName;

            // Check Function Parameters
            if (functionEditorRoot.functionParameters.indexOf(",") > 0) {
                // Set Parameters
                functionEditorRoot.componentFunction.functionParameters = functionEditorRoot.functionParameters.split(",");
            } else {
                // Set Parameters
                functionEditorRoot.componentFunction.functionParameters = "";
            }

            // Set Source
            functionEditorRoot.componentFunction.functionSource = functionEditorRoot.functionSource;
        }
    }

    // Check If Function Source Valid And Parse Elements
    function functionSourceValid() {
        // Get Source Editor Text
        var sText = functionSourceEditor.getText();
        //console.log("DFunctionEditor.functionSourceValid - sText: " + sText);

        // Reset Function Name
        functionEditorRoot.functionName = "";
        // Reset Function Parameters
        functionEditorRoot.functionParameters = "";
        // Reset Function Source
        functionEditorRoot.functionSource = "";

        // Get ( First Pos
        var obfPos = sText.indexOf("(");

        // Check ( First Pos
        if (obfPos < 1) {
            return false;
        }

        // Get ) First Pos
        var cbfPos = sText.indexOf(")");

        // Check ) First Pos
        if (cbfPos < obfPos) {
            return false;
        }

        // Get { Firts Pos
        var ocbfPos = sText.indexOf("{");

        // Check { First Pos
        if (ocbfPos < cbfPos) {
            return false;
        }

        // Get } Last Pos
        var ccblPos = sText.lastIndexOf("}");

        // Check } Last Pos
        if (ccblPos < ocbfPos) {
            return false;
        }

        // Set Function Name
        functionEditorRoot.functionName = sText.substring(0, obfPos).trim();

        // Check ( ) Positions
        if (cbfPos - obfPos === 1) {
            // Set Function Parameters
            functionEditorRoot.functionParameters = "";
        } else {
            // Set Function Parameters
            functionEditorRoot.functionParameters = sText.substring(obfPos + 1, cbfPos - 1).trim();
        }

        // Check { } Positions
        if (ccblPos - ocbfPos === 1) {
            // Set Function Source
            functionEditorRoot.functionSource = "";
        } else {
            // Set Function Source
            functionEditorRoot.functionSource = sText.substring(ocbfPos + 1, ccblPos - 1) + "\n";
        }

        // Check Functions Model
        if (functionEditorRoot.functionsModel !== null) {
            return functionEditorRoot.functionsModel.functionValid(functionName);
        }

        return false;
    }

    DSourceCodeEditor {
        id: functionSourceEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: functionEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: diskButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            functionEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            functionEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Value
            functionSourceEditor.invalidSource = false;
        }
    }

    DDisc {
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check IF Source Valid
            if (functionEditorRoot.functionSourceValid()) {
                // Update Component Function
                updateComponentFunction();
                // Emit Accepted Signal
                functionEditorRoot.accepted();
            } else {
                // Set Invalid Value
                functionSourceEditor.invalidSource = true;
            }
        }
    }
}
