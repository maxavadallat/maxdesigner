import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: heightEditorRoot

    //anchors.verticalCenter: parentPane ? parentPane.verticalCenter : parent ? parent.verticalCenter : undefined

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onUseIHeightChanged: {
            // Reset Height Editor Focus
            heightEditor.setEditorFocus(!componentInfo.useIHeight, false);
            // Set The Cursor Pos To The End
            heightEditor.setCursorPos(heightEditor.length);
        }
    }

    property string newHeight: "0"

    title: "Edit Height:"

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
            // Reset Height Editor
            resetHeightEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Check Use Implicit Size
            if (!heightEditorRoot.componentInfo.useIHeight) {
                // Set Focus
                heightEditor.setEditorFocus(true, false);
                // Set The Cursor Pos To The End
                heightEditor.setCursorPos(heightEditor.length);
            }
        }
    }

    onAccepted: {
        // Check If Implicit Size Set
        if (heightEditorRoot.componentInfo && !heightEditorRoot.componentInfo.useIHeight) {
            // Set Property Value
            heightEditorRoot.componentInfo.setPosX(heightEditorRoot.newPosX);
        }
    }

    // Reset Height Editor
    function resetHeightEditor() {
        // Get Property Type And Value
        var pValue = heightEditorRoot.componentInfo !== null ? heightEditorRoot.componentInfo.propertyValue("height", true) : "0";

        //console.log("DPosXEditor.resetHeightEditor - x:" + pValue);

        // Check First Char
        if (pValue[0] === '$') {
            // Set Source Editor Text
            heightEditor.setText("height: " + pValue.substr(1, pValue.length - 1));
        } else {
            // Set Source Editor Text
            heightEditor.setText("height: " + pValue);
        }

        // Reset New Height
        heightEditorRoot.newHeight = "0";
    }

    // Check If Height Value Valid
    function valueHeightValid() {
        // Check Use Implicit Height
        if (heightEditorRoot.componentInfo && heightEditorRoot.componentInfo.useIHeight) {
            // Reset Height Editor
            //resetHeightEditor();
            return true;
        }

        // Get Height Editor Text
        var pheText = heightEditor.getText();

        // Check  Height Editor Text
        if (pheText.indexOf("height") !== 0) {
            return false;
        }

        // Get First Pos of :
        var cfPos = pheText.indexOf(":");

        // Check Pos
        if (cfPos === -1) {
            return false;
        }

        // Get Property Value Text
        pheText = pheText.substr(cfPos + 1, pheText.length - 1);

        // Check If Number
        if (Number(pheText) === Number.NaN) {
            // Set Height Editor New text
            heightEditorRoot.newHeight = "$" + pheText.trim();
        } else {
            // Set Height Editor New text
            heightEditorRoot.newHeight = pheText.trim();
        }

        return true;
    }

    DSwitch {
        id: implicitHeightSwitch
        width: 148
        anchors.right: heightEditor.right
        anchors.top: parent.top
        anchors.topMargin: 1
        text: "Implicit Height"
        checked: heightEditorRoot.componentInfo ? heightEditorRoot.componentInfo.useIHeight : false
        onClicked: {
            // Toggle USe Implicit Height
            heightEditorRoot.componentInfo.useIHeight = !checked;
        }
    }

    DSourceCodeEditor {
        id: heightEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: heightEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        enabled: {
            // Check Component Info
            if (heightEditorRoot.componentInfo && !heightEditorRoot.componentInfo.useIHeight) {
                return true;
            }

            return false;
        }

        onSourceEditorActivated: {
            // Bring To Front
            heightEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            heightEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            heightEditor.invalidSource = false;
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Formula Valid
            if (heightEditorRoot.valueHeightValid()) {
                // Emit Accepted Signal
                heightEditorRoot.accepted();
            } else {
                // Set Invalid Source
                heightEditor.invalidSource = true;
            }
        }
    }
}
