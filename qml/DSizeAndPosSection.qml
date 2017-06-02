import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: sizeAndPosSectionRoot
    width: 300

    // Component Info
    property ComponentInfo componentInfo: propertiesController.focusedComponent

    readonly property int labelWidth: 32
    readonly property int editButtonWidth: 48

    title: "Size & Pos"
    minHeight: sizeAndPosColumn.height
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

    Column {
        id: sizeAndPosColumn
        width: sizeAndPosSectionRoot.width
        spacing: DStyle.defaultSpacing
        move: Transition { }

        Row {
            id: posRow
            height: {
                // Check Focused Component
                if (sizeAndPosSectionRoot.componentInfo && sizeAndPosSectionRoot.componentInfo.isRoot) {
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
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
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
                        id: xLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: {
                            // Check Component Info
                            if (sizeAndPosSectionRoot.componentInfo && sizeAndPosSectionRoot.componentInfo.propertyIsFormula("x")) {
                                return "fx:"
                            }

                            return "x:";
                        }
                    }

                    DSpinner {
                        id: xSpinner
                        width: posXFlipable.width - xLabel.width - DStyle.defaultSpacing
                        anchors.verticalCenter: parent.verticalCenter

                        value: sizeAndPosSectionRoot.componentInfo ? Number(sizeAndPosSectionRoot.componentInfo.posX) : 0

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
                        id: posXBackLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•x:"
                    }

                    DText {
                        id: posXFormulaLabel
                        width: posXFlipable.width - posXBackLabel.width - posXEditButton.width - DStyle.defaultSpacing * 2
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideMiddle
                        text: "{...}"
                    }

                    DButton {
                        id: posXEditButton
                        width: sizeAndPosSectionRoot.editButtonWidth
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
                width: posXFlipable.width//front.width
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
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•y:"
                    }

                    DSpinner {
                        id: ySpinner
                        width: posYFlipable.width - yLabel.width - DStyle.defaultSpacing
                        anchors.verticalCenter: parent.verticalCenter
                        value: sizeAndPosSectionRoot.componentInfo ? Number(sizeAndPosSectionRoot.componentInfo.posY) : 0

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
                        id: posYBackLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•y:"
                    }

                    DText {
                        id: posYFormulaLabel
                        width: posYFlipable.width - posYBackLabel.width - posYEditButton.width - DStyle.defaultSpacing * 2
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideMiddle
                        text: "{...}"
                    }

                    DButton {
                        id: posYEditButton
                        width: sizeAndPosSectionRoot.editButtonWidth
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
            height: sizeAndPosSectionRoot.componentInfo ? DStyle.spinnerHeight : 0
            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            visible: height > 0
            clip: true

            DFlipable {
                id: widthFlipable
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
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
                        id: widthLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•w:"
                    }

                    DSpinner {
                        id: widthSpinner
                        width: widthFlipable.width - widthLabel.width - DStyle.defaultSpacing
                        anchors.verticalCenter: parent.verticalCenter
                        value: sizeAndPosSectionRoot.componentInfo ? Number(sizeAndPosSectionRoot.componentInfo.width) : 0
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
                        id: widthBackLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•w:"
                    }

                    DText {
                        id: widthFormulaLabel
                        width: widthFlipable.width - widthBackLabel.width - widthEditButton.width - DStyle.defaultSpacing * 2
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideMiddle
                        text: "{...}"
                    }

                    DButton {
                        id: widthEditButton
                        width: sizeAndPosSectionRoot.editButtonWidth
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
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
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
                        id: heightLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•h:"
                    }

                    DSpinner {
                        id: heightSpinner
                        width: heightFlipable.width - heightLabel.width - DStyle.defaultSpacing
                        anchors.verticalCenter: parent.verticalCenter
                        value: sizeAndPosSectionRoot.componentInfo ? Number(sizeAndPosSectionRoot.componentInfo.height) : 0
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
                        id: heightBackLabel
                        width: sizeAndPosSectionRoot.labelWidth
                        anchors.verticalCenter: parent.verticalCenter
                        horizontalAlignment: Text.AlignRight
                        text: "•h:"
                    }

                    DText {
                        id: heightFormulaLabel
                        width: heightFlipable.width - heightBackLabel.width - heightEditButton.width - DStyle.defaultSpacing * 2
                        anchors.verticalCenter: parent.verticalCenter
                        elide: Text.ElideMiddle
                        text: "{...}"
                    }

                    DButton {
                        id: heightEditButton
                        width: sizeAndPosSectionRoot.editButtonWidth
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
