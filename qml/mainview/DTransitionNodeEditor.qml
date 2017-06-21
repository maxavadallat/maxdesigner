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

    }

    // Update Transition Node
    function updateTransitionNode() {

    }

    // Validate Transition Node
    function validateTransitionNode() {



        return true;
    }

    // Accept Transition Node
    function acceptTransitionNode() {
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

        // Property Name Editor
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
        }
    }

//    // Script Label
//    DText {
//        id: scriptLabel
//        height: scriptEditor.height
//        horizontalAlignment: Text.AlignRight
//        text: "script:"
//        visible: transitionNodeEditorRoot.nodeName === "ScriptAction"
//    }

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
        anchors.bottomMargin: DStyle.defaultMargin

        //height: transitionNodeEditorRoot.height - scriptLabel.height - transitionNodeEditorRoot.titleHeight - DStyle.defaultMargin - DStyle.defaultSpacing * 2
        visible: transitionNodeEditorRoot.nodeName === "ScriptAction"

        onEscapeClicked: {
            // Dismiss Pane
            transitionNodeEditorRoot.dismissPane(true);
        }
    }
}
