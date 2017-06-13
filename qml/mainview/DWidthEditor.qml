import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"

DPaneBase {
    id: widthEditorRoot

    //anchors.verticalCenter: parentPane ? parentPane.verticalCenter : parent ? parent.verticalCenter : undefined

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        onUseIWidthChanged: {
            // Reset Width Editor Focus
            widthEditor.setEditorFocus(!componentInfo.useIWidth, false);
            // Set The Cursor Pos To The End
            widthEditor.setCursorPos(widthEditor.length);
        }
    }

    property string newWidth: "0"

    title: "Edit Width:"

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
            // Reset Width Editor
            resetWidthEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Check Use Implicit Size
            if (!widthEditorRoot.componentInfo.useIWidth) {
                // Set Focus
                widthEditor.setEditorFocus(true, false);
                // Set The Cursor Pos To The End
                widthEditor.setCursorPos(widthEditor.length);
            }
        }
    }

    onAccepted: {
        // Check If Implicit Size Set
        if (widthEditorRoot.componentInfo && !widthEditorRoot.componentInfo.useIWidth) {
            // Set Property Value
            widthEditorRoot.componentInfo.setPosX(widthEditorRoot.newPosX);
        }
    }

    // Reset Width Editor
    function resetWidthEditor() {
        // Get Property Type And Value
        var pValue = widthEditorRoot.componentInfo !== null ? widthEditorRoot.componentInfo.propertyValue("width", true) : "0";

        //console.log("DPosXEditor.resetWidthEditor - x:" + pValue);

        // Check First Char
        if (pValue[0] === '$') {
            // Set Source Editor Text
            widthEditor.setText("width: " + pValue.substr(1, pValue.length - 1));
        } else {
            // Set Source Editor Text
            widthEditor.setText("width: " + pValue);
        }

        // Reset New Width
        widthEditorRoot.newWidth = "0";
    }

    // Check If Width Value Valid
    function valueWidthValid() {
        // Check Use Implicit Width
        if (widthEditorRoot.componentInfo && widthEditorRoot.componentInfo.useIWidth) {
            // Reset Width Editor
            //resetWidthEditor();
            return true;
        }

        // Get Width Editor Text
        var pweText = widthEditor.getText();

        // Check  Width Editor Text
        if (pweText.indexOf("width") !== 0) {
            return false;
        }

        // Get First Pos of :
        var cfPos = pweText.indexOf(":");

        // Check Pos
        if (cfPos === -1) {
            return false;
        }

        // Get Property Value Text
        pweText = pweText.substr(cfPos + 1, pweText.length - 1);

        // Check If Number
        if (Number(pweText) === Number.NaN) {
            // Set Width Editor New text
            widthEditorRoot.newWidth = "$" + pweText.trim();
        } else {
            // Set Width Editor New text
            widthEditorRoot.newWidth = pweText.trim();
        }

        return true;
    }

    DSwitch {
        id: implicitWidthSwitch
        width: 148
        anchors.right: widthEditor.right
        anchors.top: parent.top
        anchors.topMargin: 1
        text: "Implicit Width"
        checked: widthEditorRoot.componentInfo ? widthEditorRoot.componentInfo.useIWidth : false
        onClicked: {
            // Toggle USe Implicit Width
            widthEditorRoot.componentInfo.useIWidth = !checked;
        }
    }

    DSourceCodeEditor {
        id: widthEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: widthEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        enabled: {
            // Check Component Info
            if (widthEditorRoot.componentInfo && !widthEditorRoot.componentInfo.useIWidth) {
                return true;
            }

            return false;
        }

        onSourceEditorActivated: {
            // Bring To Front
            widthEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            widthEditorRoot.rejected();
        }

        onSourceTextChanged: {
            // Reset Invalid Source
            widthEditor.invalidSource = false;
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Check If Formula Valid
            if (widthEditorRoot.valueWidthValid()) {
                // Emit Accepted Signal
                widthEditorRoot.accepted();
            } else {
                // Set Invalid Source
                widthEditor.invalidSource = true;
            }
        }
    }
}
