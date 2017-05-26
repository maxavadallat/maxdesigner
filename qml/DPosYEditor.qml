import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: posYEditorRoot

    //anchors.verticalCenter: parentPane ? parentPane.verticalCenter : parent ? parent.verticalCenter : undefined

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onUseIPosYChanged: {
            // Reset Y Editor Focus
            posYEditor.setEditorFocus(!componentInfo.useIPosY, false);
            // Set The Cursor Pos To The End
            posYEditor.setCursorPos(posYEditor.length);
        }
    }

    property string newPosY: "0"

    title: "Edit Y:"

    hideToSide: hideToRight

    creationWidth: 358
    creationHeight: 122

    minWidth: 358
    minHeight: 122

    enablePosOverlay: false
    enableSizeOverlay: false

    enableHideButton: false

    enableDrag: false

    resizeRightEnabled: false

    // ...

    onComponentInfoChanged: {

    }

    onTransitionStarted: {
        // Check New State
        if (newState === stateShown) {
            // Reset Pos Y Editor
            resetPosYEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Check Use Implicit Size
            if (!posYEditorRoot.componentInfo.useIPosY) {
                // Set Focus
                posYEditor.setEditorFocus(true, false);
                // Set The Cursor Pos To The End
                posYEditor.setCursorPos(posYEditor.length);
            }
        }
    }

    onAccepted: {
        // Check If Implicit Size Set
        if (posYEditorRoot.componentInfo && !posYEditorRoot.componentInfo.useIPosY) {
            // Set Property Value
            posYEditorRoot.componentInfo.setPosY(posYEditorRoot.newPosY);
        }
    }

    // Reset Pos Y Editor
    function resetPosYEditor() {
        // Get Property Type And Value
        var pValue = posYEditorRoot.componentInfo !== null ? posYEditorRoot.componentInfo.propertyValue("y", true) : "0";

        //console.log("DPosYEditor.resetPosYEditor - y:" + pValue);

        // Check First Char
        if (pValue[0] === '$') {
            // Set Source Editor Text
            posYEditor.setText("y: " + pValue.substr(1, pValue.length - 1));
        } else {
            // Set Source Editor Text
            posYEditor.setText("y: " + pValue);
        }

        // Reset New Pos Y
        posYEditorRoot.newPosY = "0";
    }

    // Check If Pos Y Value Valid
    function valueYValid() {
        // Check Use Implicit Pos Y
        if (posYEditorRoot.componentInfo && posYEditorRoot.componentInfo.useIPosY) {
            // Reset Pos Y Editor
            //resetPosYEditor();
            return true;
        }

        // Get Pos Y Editor Text
        var pyeText = posYEditor.getText();

        // Check  Pos Y Editor Text
        if (pyeText[0] !== 'y') {
            return false;
        }

        // Get First Pos of :
        var cfPos = pyeText.indexOf(":");

        // Check Pos
        if (cfPos === -1) {
            return false;
        }

        // Get Property Value Text
        pyeText = pyeText.substr(cfPos + 1, pyeText.length - 1);

        // Check If Number
        if (Number(pyeText) === Number.NaN) {
            // Set Pos Y Editor New text
            posYEditorRoot.newPosY = "$" + pyeText.trim();
        } else {
            // Set Pos Y Editor New text
            posYEditorRoot.newPosY = pyeText.trim();
        }

        return true;
    }

    DSwitch {
        id: implicitPosYSwitch
        width: 158
        anchors.right: posYEditor.right
        anchors.top: parent.top
        anchors.topMargin: 1
        text: "Implicit Pos Y"
        checked: posYEditorRoot.componentInfo ? posYEditorRoot.componentInfo.useIPosY : false
        onClicked: {
            // Toggle USe Implicit Pos Y
            posYEditorRoot.componentInfo.useIPosY = !checked;
        }
    }

    DSourceCodeEditor {
        id: posYEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: posYEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        enabled: {
            // Check Component Info
            if (posYEditorRoot.componentInfo && !posYEditorRoot.componentInfo.useIPosY) {
                return true;
            }

            return false;
        }

        onSourceEditorActivated: {
            // Bring To Front
            posYEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            posYEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            posYEditor.invalidSource = false;
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Formula Valid
            if (posYEditorRoot.valueYValid()) {
                // Emit Accepted Signal
                posYEditorRoot.accepted();
            } else {
                // Set Invalid Source
                posYEditor.invalidSource = true;
            }
        }
    }
}
