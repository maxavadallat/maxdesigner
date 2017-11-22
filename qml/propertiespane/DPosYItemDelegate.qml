import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: posYItemDelegateRoot

    width: 220
    height: DStyle.spinnerHeight

    readonly property int labelWidth: 32
    readonly property int editButtonWidth: 48

    property ComponentInfo componentInfo: propertiesController.focusedComponent
    property QtObject currentHandler: propertiesController.currentHandler

    signal tabKeyPressed()

    // Set FLipped State
    function setFlipY(aFlipped) {
        // Set Flipped State
        posYFlipable.flipped = aFlipped;
    }

    // Set Editor Focus
    function setEditorFocus(aFocus) {
        // Set Spinner Focus
        ySpinner.setSpinnerFocus(aFocus, aFocus);
    }

    // Pos Y Editor Flippable
    DFlipable {
        id: posYFlipable
        anchors.fill: parent
        anchors.rightMargin: DStyle.defaultMargin * 2

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
                width: posYItemDelegateRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: {
                    // Check Component Info
                    if (posYItemDelegateRoot.componentInfo && posYItemDelegateRoot.componentInfo.propertyIsFormula("y")) {
                        return "fy:"
                    }

                    // Check For Implicit Pos Y
                    if (posYItemDelegateRoot.componentInfo && posYItemDelegateRoot.componentInfo.useIPosY) {
                        return "iy:"
                    }

                    return "y:"; // •
                }
            }

            DSpinner {
                id: ySpinner
                width: posYFlipable.width - yLabel.width - DStyle.defaultSpacing
                anchors.verticalCenter: parent.verticalCenter
                //value: posYItemDelegateRoot.componentInfo ? Number(posYItemDelegateRoot.componentInfo.posY) : 0
                value: posYItemDelegateRoot.currentHandler ? Math.round(posYItemDelegateRoot.currentHandler.y) : 0

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
                        // Emit Tab Key Pressed Signal
                        posYItemDelegateRoot.tabKeyPressed();
//                        // Set Y Spinner Focus
//                        ySpinner.setSpinnerFocus(true, true);
                    }
                }
            }
        }

        back: Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: posYBackLabel
                width: posYItemDelegateRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "y:"
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
                width: posYItemDelegateRoot.editButtonWidth
                height: DStyle.spinnerHeight

                text: "Edit"
                onClicked: {
                    // Emit Pos Y Edit Launch Signal
                    propertiesPaneRoot.posYEditLaunch();
                }
            }
        }
    }

    DSwipeGesture {
        id: posYSwipe
        anchors.fill: parent
        actionButtonText: "Implicit"

        enableSwipe: {
            return false;
        }

        onActionButtonClicked: {

        }
    }
}
