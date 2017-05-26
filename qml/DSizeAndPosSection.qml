import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: sizeAndPosSectionRoot
    width: 300

//    property Connections propertiesControllerConnections: Connections {
//        target: propertiesController

//        onFocusedComponentChanged: {

//        }
//    }

    title: "Size & Pos"
    minHeight: sizeAndPosFlow.height
    state: stateClosed

    // Flip Pos X Editor
    function flipPosXEditor(flipState) {
        // Set Flipped State
        posXFlipable.flipped = flipState;
    }

    // Flip Pos Y Editor
    function flipPosYEditor(flipState) {
        // Set Flipped State
        posYFlipable.flipped = flipState;
    }

    // Flip Wisth Editor
    function flipWidthEditor(flipState) {
        // Set Flipped State
        widthFlipable.flipped = flipState;
    }

    // Flip Height Editor
    function flipHeightEditor(flipState) {
        // Set Flipped State
        heightFlipable.flipped = flipState;
    }

    DFlow {
        id: sizeAndPosFlow
        width: sizeAndPosSectionRoot.width
        move: Transition { }

        Row {
            id: posRow
            height: {
                // Check Focused Component
                if (propertiesController.focusedComponent && propertiesController.focusedComponent.isRoot) {
                    return 0;
                }

                return DStyle.spinnerHeight;
            }

            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            visible: height > 0
            clip: true

            DFlipable {
                id: posXFlipable
                width: front.width
                height: DStyle.spinnerHeight

                onFlippedChanged: {
                    // Check Flipped
                    if (flipped) {
                        // Reset Spinner Focus
                        xSpinner.setSpinnerFocus(false, false);
                    }
                }

                front: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "x:"
                    }

                    DSpinner {
                        id: xSpinner
                        anchors.verticalCenter: parent.verticalCenter

                        value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posX) : 0

                        onValueIncreased: {
                            propertiesController.requestCX(newValue);
                        }

                        onValueDecreased: {
                            propertiesController.requestCX(newValue);
                        }

                        onValueEntered: {
                            propertiesController.requestCX(newValue);
                        }

                        onKeyEvent: {
                            if (event.key === Qt.Key_Tab) {
                                // Set Y Spinner Focus
                                ySpinner.setSpinnerFocus(true, true);
                            }
                        }
                    }
                }

                back: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "x:"
                    }

                    DButton {
                        id: posXEditButton
                        width: DStyle.spinnerWidth
                        height: DStyle.spinnerHeight

                        text: "Edit"
                        onClicked: {
                            // Emit Pos X Edit Launch Signal
                            propertiesPaneRoot.posXEditLaunch();
                        }
                    }
                }
            }

            DFlipable {
                id: posYFlipable
                width: front.width
                height: DStyle.spinnerHeight

                onFlippedChanged: {
                    // Check Flipped
                    if (flipped) {
                        // Reset Spinner Focus
                        ySpinner.setSpinnerFocus(false, false);
                    }
                }

                front: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        id: yLabel
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "y:"
                    }

                    DSpinner {
                        id: ySpinner
                        anchors.verticalCenter: parent.verticalCenter
                        value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posY) : 0

                        onValueIncreased: {
                            propertiesController.requestCY(newValue);
                        }

                        onValueDecreased: {
                            propertiesController.requestCY(newValue);
                        }

                        onValueEntered: {
                            propertiesController.requestCY(newValue);
                        }

                        onKeyEvent: {
                            if (event.key === Qt.Key_Tab) {
                                // Set Width Spinner Focus
                                widthSpinner.setSpinnerFocus(true, true);
                            }
                        }
                    }
                }

                back: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "y:"
                    }

                    DButton {
                        id: posYEditButton
                        width: DStyle.spinnerWidth
                        height: DStyle.spinnerHeight

                        text: "Edit"
                        onClicked: {
                            // Emit Pos Y Edit Launch Signal
                            propertiesPaneRoot.posYEditLaunch();
                        }
                    }
                }
            }
        }

        Row {
            id: sizeRow
            height: propertiesController.focusedComponent ? DStyle.spinnerHeight : 0
            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            visible: height > 0
            clip: true

            DFlipable {
                id: widthFlipable
                width: front.width
                height: DStyle.spinnerHeight

                onFlippedChanged: {
                    // Check Flipped
                    if (flipped) {
                        // Reset Spinner Focus
                        widthSpinner.setSpinnerFocus(false, false);
                    }
                }

                front: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "w:"
                    }

                    DSpinner {
                        id: widthSpinner
                        anchors.verticalCenter: parent.verticalCenter
                        value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.width) : 0
                        minValue: 0

                        onValueIncreased: {
                            propertiesController.requestCWidth(newValue);
                        }

                        onValueDecreased: {
                            propertiesController.requestCWidth(newValue);
                        }

                        onValueEntered: {
                            propertiesController.requestCWidth(newValue);
                        }

                        onKeyEvent: {
                            if (event.key === Qt.Key_Tab) {
                                // Set Height Spinner Focus
                                heightSpinner.setSpinnerFocus(true, true);
                            }
                        }
                    }
                }

                back: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "w:"
                    }

                    DButton {
                        id: widthEditButton
                        width: DStyle.spinnerWidth
                        height: DStyle.spinnerHeight

                        text: "Edit"
                        onClicked: {
                            // Emit Width Edit Launch Signal
                            propertiesPaneRoot.widthEditLaunch();
                        }
                    }
                }
            }

            DFlipable {
                id: heightFlipable
                width: front.width
                height: DStyle.spinnerHeight

                onFlippedChanged: {
                    // Check Flipped
                    if (flipped) {
                        // Reset Spinner Focus
                        heightSpinner.setSpinnerFocus(false, false);
                    }
                }

                front: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        id: hLabel
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "h:"
                    }

                    DSpinner {
                        id: heightSpinner
                        anchors.verticalCenter: parent.verticalCenter
                        value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.height) : 0
                        minValue: 0

                        onValueIncreased: {
                            propertiesController.requestCHeight(newValue);
                        }

                        onValueDecreased: {
                            propertiesController.requestCHeight(newValue);
                        }

                        onValueEntered: {
                            propertiesController.requestCHeight(newValue);
                        }

                        onKeyEvent: {
                            if (event.key === Qt.Key_Tab) {
                                // Check Pos Row height
                                if (posRow.height > 0) {
                                    // Set X Spinner Focus
                                    xSpinner.setSpinnerFocus(true, true);
                                } else {
                                    // Set Width Spinner Focus
                                    widthSpinner.setSpinnerFocus(true, true);
                                }
                            }
                        }
                    }
                }

                back: Row {
                    spacing: DStyle.defaultSpacing

                    DText {
                        width: 24
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "h:"
                    }

                    DButton {
                        id: heightEditButton
                        width: DStyle.spinnerWidth
                        height: DStyle.spinnerHeight

                        text: "Edit"
                        onClicked: {
                            // Emit Height Edit Launch Signal
                            propertiesPaneRoot.heightEditLaunch();
                        }
                    }
                }
            }
        }
    }
}
