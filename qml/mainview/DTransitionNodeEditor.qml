import QtQuick 2.0

import enginecomponents 0.1

import "../style"
import "../controls"
import "../animations"

DPaneBase {
    id: transitionNodeEditorRoot

    property int nodeType: 0

    //property ComponentInfo componentInfo: null

    title: {
        // Init Type Text
        var typeText = "";

        switch (transitionNodeEditorRoot.nodeType) {
            default:
            case 1:
            case 2: break;
            case 3: typeText = "Property Animation"; break;
            case 4: typeText = "Property Action"; break;
            case 5: typeText = "Script Action"; break;
            case 6: typeText = "Pause Animation"; break;
        }

        return "Transition Node - " + typeText;
    }

    hideToSide: hideToTop

/*
    DPopupItemObject { text: "Add New Node" },
    DPopupItemObject { text: "Add Sequential Animation" },
    DPopupItemObject { text: "Add Parallel Animation" },
    DPopupItemObject { text: "Add Property Animation" },
    DPopupItemObject { text: "Add Property Action" },
    DPopupItemObject { text: "Add Script Action" },
    DPopupItemObject { text: "Add Pause Animation" }
*/

    creationWidth: {
        // Switch Node Type
        switch (transitionNodeEditorRoot.nodeType) {
            case 4: return 300;
            case 5: return 532;
            case 6: return 354;
            default:
        }

        return 556;
    }


    creationHeight: {
        // Switch Node Type
        switch (transitionNodeEditorRoot.nodeType) {
            case 6: return 108;
            default:
        }

        return 152;
    }

    minWidth: creationWidth
    minHeight: creationHeight

    enableResize: false
    enableHideButton: false

    state: stateCreate

//    onAccepted: {
//        // Reset
//        transitionNodeEditorRoot.reset(false);
//    }

//    onRejected: {
//        // Reset
//        transitionNodeEditorRoot.reset(false);
//    }

    onTransitionStarted: {
        if (newState === stateCreate) {
            fieldsFlow.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Switch Node Type
            switch (transitionNodeEditorRoot.nodeType) {
                case 3:
                case 4: targetEditor.setEditorFocus(true, true); break;
                case 5: scriptEditor.setEditorFocus(true, false); break;
                case 6: durationValueEditor.setEditorFocus(true, true); break;
            }

            fieldsFlow.opacity = 1.0;
        }
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            transitionNodeEditorRoot.accepted();

            // ...
        }
    }

    Rectangle {
        anchors.fill: fieldsFlow
        color: "transparent"
        border.color: "purple"
    }

    Flow {
        id: fieldsFlow

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.right: parent.right
        anchors.rightMargin: 88

        spacing: DStyle.defaultSpacing

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        DText {
            id: targetLabel
            width: propertyLabel.width
            height: targetEditor.height
            horizontalAlignment: Text.AlignRight
            text: "target:"
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 4
        }

        DTextInput {
            id: targetEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 4
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

        DText {
            id: propertyLabel
            width: 76
            height: propertyEditor.height
            horizontalAlignment: Text.AlignRight
            text: "property:"
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 4
        }

        DTextInput {
            id: propertyEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 4
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        if (valueEditor.visible) {
                            valueEditor.setEditorFocus(true, true);
                        } else {
                            fromValueEditor.setEditorFocus(true, true);
                        }
                    break;
                }
            }
        }

        DText {
            id: valueLabel
            width: propertyLabel.width
            height: valueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "value:"
            visible: transitionNodeEditorRoot.nodeType === 4
        }

        DTextInput {
            id: valueEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 4
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

        DText {
            id: scriptLabel
            height: scriptEditor.height
            horizontalAlignment: Text.AlignRight
            text: "script:"
            visible: transitionNodeEditorRoot.nodeType === 5
        }

        DSourceCodeEditor {
            id: scriptEditor
            width: transitionNodeEditorRoot.width - 146
            height: transitionNodeEditorRoot.height - 40 - DStyle.defaultMargin
            visible: transitionNodeEditorRoot.nodeType === 5

            onEscapeClicked: {
                // Dismiss Pane
                transitionNodeEditorRoot.dismissPane(true);
            }
        }

        DText {
            id: fromValueLabel
            width: propertyLabel.width
            height: fromValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "from:"
            visible: transitionNodeEditorRoot.nodeType === 3
        }

        DTextInput {
            id: fromValueEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 3
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

        DText {
            id: toValueLabel
            width: propertyLabel.width
            height: toValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "to:"
            visible: transitionNodeEditorRoot.nodeType === 3
        }

        DTextInput {
            id: toValueEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 3
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
            width: durationValueLabel.width + durationValueEditor.width
            height: 8
            visible: transitionNodeEditorRoot.nodeType === 6
        }

        DText {
            id: durationValueLabel
            width: propertyLabel.width
            height: durationValueEditor.height
            horizontalAlignment: Text.AlignRight
            text: "duration:"
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 6
        }

        DTextInput {
            id: durationValueEditor
            width: 120
            visible: transitionNodeEditorRoot.nodeType === 3 || transitionNodeEditorRoot.nodeType === 6
            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionNodeEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        if (transitionNodeEditorRoot.nodeType === 2) {
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

        DText {
            id: easingValueLabel
            width: propertyLabel.width
            height: easingValueOption.height
            horizontalAlignment: Text.AlignRight
            text: "easing:"
            visible: transitionNodeEditorRoot.nodeType === 3
        }

        DOption {
            id: easingValueOption

            visible: transitionNodeEditorRoot.nodeType === 3

            model: [
                { text: "Easing.Linear" },
                { text: "Easing.InQuad" },
                { text: "Easing.OutQuad" },
                { text: "Easing.InOutQuad" },
                { text: "Easing.OutInQuad" },
                { text: "more" }
            ]

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
    }
}
