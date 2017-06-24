import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: transitionNodeEditorRoot

    // Component Info
    property ComponentInfo componentInfo: propertiesController.focusedComponent
    // Transitions Model
    property ComponentTransitionsModel transitionsModel: propertiesController.transitionsModel
    // Component Transition
    property ComponentTransition componentTransition: null
    // Transition Node - Animation Component
    property ComponentInfo transitionNode: null
    // Node Name
    property string nodeName: transitionNode !== null ? transitionNode.animBase() : "NULL"
    // New Transition Node
    property bool newTransitionNode: false

    title: "Transition Node - " + nodeName

    hideToSide: hideToTop

    creationWidth: {
        // Switch Node Name
        switch (transitionNodeEditorRoot.nodeName) {
//            case "PropertyAnimation":   return 282;
            case "PropertyAction":      return 360;
            case "PauseAnimation":      return 360;
//            case "ScriptAction":        return 282;
        }

        return 500;
    }

    creationHeight: {
        // Switch Node Name
        switch (transitionNodeEditorRoot.nodeName) {
            case "PropertyAnimation":   return 292;
            case "PropertyAction":      return 176;
            case "PauseAnimation":      return 118;
            case "ScriptAction":        return 282;
        }

        return 260;
    }

    minWidth: creationWidth
    minHeight: creationHeight

    enableResize: true
    enableHideButton: false

    resizeTopEnabled: false
    resizeBottomEnabled: nodeName === "ScriptAction"

    state: stateCreate

    onTransitionStarted: {
        // Check New State
        if (newState === stateCreate) {
            // Set Fields Flow Opacity
            fieldsFlow.opacity = 0.0;

            // Reset Editor's Focus
            targetEditor.setEditorFocus(false, false);
            propertyEditor.setEditorFocus(false, false);
            valueEditor.setEditorFocus(false, false);
            fromValueEditor.setEditorFocus(false, false);
            toValueEditor.setEditorFocus(false, false);
            curveValueEditor.setEditorFocus(false, false);
            scriptEditor.setEditorFocus(false, false);
            durationValueEditor.setEditorFocus(false, false);

        } else if (newState === stateShown) {
            // Reset Transition Node Editor
            resetTransitionNodeEditor();
        }
    }

    onTransitionFinished: {
        // Check New State
        if (newState === stateShown) {
            // Set Fields Flow Opacity
            fieldsFlow.opacity = 1.0;

            // Switch Node Name
            switch (transitionNodeEditorRoot.nodeName) {
                case "PropertyAnimation":
                case "PropertyAction":
                    // Set Editor Focus
                    targetEditor.setEditorFocus(true, false);
                break;

                case "ScriptAction":
                    scriptEditor.setEditorFocus(true, false);
                break;

                case "PauseAnimation":
                    durationValueEditor.setEditorFocus(true, false);
                break;
            }
        }
    }

    onTransitionNodeChanged: {
        // Check Transition Node
        if (transitionNodeEditorRoot.transitionNode !== null) {
            console.log("#### DTransitionNodeEditor.onTransitionNodeChanged - name: " + transitionNodeEditorRoot.transitionNode.componentName);

            // ...
        }
    }

    // Reset Transition Node Editor
    function resetTransitionNodeEditor() {
        // Reset Invalid Value Of Property Editor
        propertyEditor.invalidValue = false;

        // Check Transition Node
        if (transitionNodeEditorRoot.transitionNode !== null) {
            // Switch Node Name
            switch (transitionNodeEditorRoot.nodeName) {
                case "PropertyAnimation":
                    // Set Target Editor Text
                    targetEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("target"));
                    // Set Property Editor Text
                    propertyEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("properties"));
                    // Set From Value Editor Text
                    fromValueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("from"));
                    // Set To Value Editor Text
                    toValueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("to"));
                    // Set Duration EDitor Text
                    durationValueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("duration"));

                    // Get Esing Type Enums
                    var easingTypes = transitionNodeEditorRoot.transitionNode.propertyEnums("easing.type");
                    // Clear Easing Value Option
                    easingValueOption.clearItemModel();
                    // Get Easing Types Count
                    var etCount = easingTypes.length;
                    // Iterate Through Easing Types
                    for (var i=0; i<etCount; i++) {
                        // Add Easing Type Values
                        easingValueOption.appendItem(easingTypes[i]);
                    }

                    // Set Easing Type Option
                    easingValueOption.setValue(transitionNodeEditorRoot.transitionNode.propertyValue("easing.type"));
                    // Set Easing Curve Editor Text
                    curveValueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("easing.bezierCurve"));
                break;

                case "PropertyAction":
                    // Set Target Editor Text
                    targetEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("target"));
                    // Set Property Editor Text
                    propertyEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("property"));
                    // Set Value Editor Text
                    valueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("value"));
                break;

                case "PauseAnimation":
                    // Set Duration EDitor Text
                    durationValueEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("duration"));
                break;

                case "ScriptAction":
                    // Sety Script Editor Text
                    scriptEditor.setText(transitionNodeEditorRoot.transitionNode.propertyValue("script"));
                break;
            }
        }
    }

    // Update Transition Node
    function updateTransitionNode() {
        // Check Transition Node
        if (transitionNodeEditorRoot.transitionNode !== null) {
            console.log("DTransitionNodeEditor.updateTransitionNode");

            // Switch Node Name
            switch (transitionNodeEditorRoot.nodeName) {
                case "PropertyAnimation":
                    // Set Target
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("target", targetEditor.editedText);
                    // Set Properties
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("properties", propertyEditor.editedText);
                    // Set Value From
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("from", fromValueEditor.editedText);
                    // Set Value To
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("to", toValueEditor.editedText);
                    // Set Duration
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("duration", durationValueEditor.editedText);
                    // Set Easing Type
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("easing.type", easingValueOption.getItemText(easingValueOption.currentIndex));
                    // Set Easing Curve
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("easing.bezierCurve", curveValueEditor.editedText);
                break;

                case "PropertyAction":
                    // Set Target
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("target", targetEditor.editedText);
                    // Set Property
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("property", propertyEditor.editedText);
                    // Set Value
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("value", valueEditor.editedText);
                break;

                case "PauseAnimation":
                    // Set Duration
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("duration", durationValueEditor.editedText);
                break;

                case "ScriptAction":
                    // Set Script
                    transitionNodeEditorRoot.transitionNode.setPropertyValue("script", scriptEditor.getText());
                break;
            }
        }
    }

    // Validate Transition Node
    function validateTransitionNode() {
        // Check Transition Node
        if (transitionNodeEditorRoot.transitionNode !== null) {
            // Switch Node Name
            switch (transitionNodeEditorRoot.nodeName) {
                case "PropertyAnimation":
                    // Check Property Editor Text
                    if (propertyEditor.editedText === "") {
                        // Set Invalid Value
                        propertyEditor.invalidValue = true;
                        // Set Focus
                        propertyEditor.setEditorFocus(true, false)

                        return false;
                    }
                break;

                case "PropertyAction":
                    // Check Property Editor Text
                    if (propertyEditor.editedText === "") {
                        // Set Invalid Value
                        propertyEditor.invalidValue = true;
                        // Set Focus
                        propertyEditor.setEditorFocus(true, false)

                        return false;
                    }
                break;

                case "PauseAnimation":

                break;

                case "ScriptAction":

                break;
            }

            return true;
        }

        return false;
    }

    // Accept Transition Node
    function acceptTransitionNode() {
        console.log("DTransitionNodeEditor.acceptTransitionNode");

        // Check If TransitionNode Valid
        if (validateTransitionNode()) {
            // Update TransitionNode
            updateTransitionNode();
            // Emit Accepted Signal
            transitionNodeEditorRoot.accepted();
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: acceptTransitionNode();
    }

    // Transition Fileds Flow
    Flow {
        id: fieldsFlow

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 3
        anchors.right: discButton.left
        anchors.rightMargin: DStyle.defaultMargin * 3

        spacing: DStyle.defaultSpacing

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        // Target Label
        DText {
            id: targetLabel
            width: propertyLabel.width
            height: targetEditor.height
            horizontalAlignment: Text.AlignRight
            text: "target:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction" || transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        // Target Editor
        DTextInput {
            id: targetEditor
            width: fieldsFlow.width - targetLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction" || transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        propertyEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

        // Property Label
        DText {
            id: propertyLabel
            //width: 76
            height: propertyEditor.height
            horizontalAlignment: Text.AlignRight
            text: "property:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction" || transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        // Property/Properties Name Editor
        DTextInput {
            id: propertyEditor
            width: fieldsFlow.width - propertyLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction" || transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // Check If Value Editor Visible
                        if (valueEditor.visible) {
                            // Set Editor Focus
                            valueEditor.setEditorFocus(true, true);
                        } else {
                            // Set Editor Focus
                            fromValueEditor.setEditorFocus(true, true);
                        }
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

        // Value Label
        DText {
            id: valueLabel
            width: propertyLabel.width
            height: valueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "value:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction"
        }

        // Value Editor
        DTextInput {
            id: valueEditor
            width: fieldsFlow.width - valueLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAction"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        targetEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

        // From Label
        DText {
            id: fromValueLabel
            width: propertyLabel.width
            height: fromValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "from:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        // From Value Editor
        DTextInput {
            id: fromValueEditor
            width: (fieldsFlow.width - fromValueLabel.width - toValueLabel.width - DStyle.defaultSpacing * 3) / 2
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        toValueEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

        // To Value Label
        DText {
            id: toValueLabel
            width: fromValueLabel.width
            height: toValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "to:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        // To Value Editor
        DTextInput {
            id: toValueEditor
            width: (fieldsFlow.width - fromValueLabel.width - toValueLabel.width - DStyle.defaultSpacing * 3) / 2
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        durationValueEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

        // Spacer
        Item {
            width: fieldsFlow.width
            height: 4
            visible: transitionNodeEditorRoot.nodeName === "PauseAnimation"
        }

        // Duration Label
        DText {
            id: durationValueLabel
            width: propertyLabel.width
            height: durationValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "duration:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation" || transitionNodeEditorRoot.nodeName === "PauseAnimation"
        }

        DTextInput {
            id: durationValueEditor
            width: fieldsFlow.width - durationValueLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation" || transitionNodeEditorRoot.nodeName === "PauseAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // Check Visibility
                        if (easingValueOption.visible) {
                            // Set Option Focus
                            easingValueOption.setOptionFocus(true);
                        }
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }

//        // Spacer
//        Item {
//            width: durationValueLabel.width + durationValueEditor.width
//            height: 16
//            visible: transitionNodeEditorRoot.nodeType === 5
//        }

        // Easing Label
        DText {
            id: easingValueLabel
            width: propertyLabel.width
            height: easingValueOption.height
            horizontalAlignment: Text.AlignRight
            text: "easing:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        // Easing Option
        DOption {
            id: easingValueOption
            width: fieldsFlow.width - easingValueLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            model: []

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // Set Editor Focus
                        curveValueEditor.setEditorFocus(true, true);
                    break;
                }
            }
        }

        // Easing Label
        DText {
            id: curveValueLabel
            width: propertyLabel.width
            height: curveValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "curve:"
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"
        }

        DTextInput {
            id: curveValueEditor
            width: fieldsFlow.width - curveValueLabel.width - DStyle.defaultSpacing
            visible: transitionNodeEditorRoot.nodeName === "PropertyAnimation"

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        // Set Editor Focus
                        targetEditor.setEditorFocus(true, true);
                    break;
                }
            }

            onAccepted: acceptTransitionNode();
        }
    }

    // Script Editor
    DSourceCodeEditor {
        id: scriptEditor

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: discButton.left
        anchors.rightMargin: DStyle.defaultMargin * 3
        anchors.top:  transitionNodeEditorRoot.titleLabel.bottom
        anchors.topMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin * 1.5

        visible: transitionNodeEditorRoot.nodeName === "ScriptAction"

        onEscapeClicked: {
            // Dismiss Pane
            transitionNodeEditorRoot.dismissPane(true);
        }
    }
}
