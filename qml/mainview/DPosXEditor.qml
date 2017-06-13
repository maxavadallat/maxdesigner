import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: posXEditorRoot

    //anchors.verticalCenter: parentPane ? parentPane.verticalCenter : parent ? parent.verticalCenter : undefined

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onUseIPosXChanged: {
            // Reset Focus X Editor Focus
            posXEditor.setEditorFocus(!componentInfo.useIPosX, false);
            // Set The Cursor Pos To The End
            posXEditor.setCursorPos(posXEditor.length);
        }
    }

    property string newPosX: "0"

    title: "Edit X:"

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
            // Reset Pos X Editor
            resetPosXEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Check Use Implicit Size
            if (!posXEditorRoot.componentInfo.useIPosX) {
                // Set Focus
                posXEditor.setEditorFocus(true, false);
                // Set The Cursor Pos To The End
                posXEditor.setCursorPos(posXEditor.length);
            }
        }
    }

    onAccepted: {
        // Check If Implicit Size Set
        if (posXEditorRoot.componentInfo && !posXEditorRoot.componentInfo.useIPosX) {
            // Set Property Value
            posXEditorRoot.componentInfo.setPosX(posXEditorRoot.newPosX);
        }
    }

    // Reset Pos X Editor
    function resetPosXEditor() {
        // Get Property Type And Value
        var pValue = posXEditorRoot.componentInfo !== null ? posXEditorRoot.componentInfo.propertyValue("x", true) : "0";

        //console.log("DPosXEditor.resetPosXEditor - x:" + pValue);

        // Check First Char
        if (pValue[0] === '$') {
            // Set Source Editor Text
            posXEditor.setText("x: " + pValue.substr(1, pValue.length - 1));
        } else {
            // Set Source Editor Text
            posXEditor.setText("x: " + pValue);
        }

        // Reset New Pos X
        posXEditorRoot.newPosX = "0";
    }

    // Check If Pos X Value Valid
    function valueXValid() {
        // Check Use Implicit Pos X
        if (posXEditorRoot.componentInfo && posXEditorRoot.componentInfo.useIPosX) {
            // Reset Pos X Editor
            //resetPosXEditor();
            return true;
        }

        // Get Pos X Editor Text
        var pxeText = posXEditor.getText();

        // Check  Pos X Editor Text
        if (pxeText[0] !== 'x') {
            return false;
        }

        // Get First Pos of :
        var cfPos = pxeText.indexOf(":");

        // Check Pos
        if (cfPos === -1) {
            return false;
        }

        // Get Property Value Text
        pxeText = pxeText.substr(cfPos + 1, pxeText.length - 1);

        // Check If Number
        if (Number(pxeText) === Number.NaN) {
            // Set Pos X Editor New text
            posXEditorRoot.newPosX = "$" + pxeText.trim();
        } else {
            // Set Pos X Editor New text
            posXEditorRoot.newPosX = pxeText.trim();
        }

        return true;
    }

    DSwitch {
        id: implicitPosXSwitch
        width: 158
        anchors.right: posXEditor.right
        anchors.top: parent.top
        anchors.topMargin: 1
        text: "Implicit Pos X"
        checked: posXEditorRoot.componentInfo ? posXEditorRoot.componentInfo.useIPosX : false
        onClicked: {
            // Toggle USe Implicit Pos X
            posXEditorRoot.componentInfo.useIPosX = !checked;
        }
    }

    DSourceCodeEditor {
        id: posXEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: posXEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        enabled: {
            // Check Component Info
            if (posXEditorRoot.componentInfo && !posXEditorRoot.componentInfo.useIPosX) {
                return true;
            }

            return false;
        }

        onSourceEditorActivated: {
            // Bring To Front
            posXEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            posXEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            posXEditor.invalidSource = false;
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Formula Valid
            if (posXEditorRoot.valueXValid()) {
                // Emit Accepted Signal
                posXEditorRoot.accepted();
            } else {
                // Set Invalid Source
                posXEditor.invalidSource = true;
            }
        }
    }
}
