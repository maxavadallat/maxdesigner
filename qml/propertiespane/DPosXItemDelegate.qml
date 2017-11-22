import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: posXItemDelegateRoot

    width: 220
    height: DStyle.spinnerHeight

    readonly property int labelWidth: 32
    readonly property int editButtonWidth: 48

    property ComponentInfo componentInfo: propertiesController.focusedComponent
    property QtObject currentHandler: propertiesController.currentHandler

    signal tabKeyPressed()

    // Set FLipped State
    function setFlipX(aFlipped) {
        // Set Flipped State
        posXFlipable.flipped = aFlipped;
    }

    // Set Editor Focus
    function setEditorFocus(aFocus) {
        // Set Spinner Focus
        xSpinner.setSpinnerFocus(aFocus, aFocus);
    }

    DFlipable {
        id: posXFlipable
        anchors.fill: parent
        anchors.rightMargin: DStyle.defaultMargin * 2

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
                width: posXItemDelegateRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: {
                    // Check Component Info
                    if (posXItemDelegateRoot.componentInfo && posXItemDelegateRoot.componentInfo.propertyIsFormula("x")) {
                        return "fx:"
                    }

                    // Check For Implicit Pos X
                    if (posXItemDelegateRoot.componentInfo && posXItemDelegateRoot.componentInfo.useIPosX) {
                        return "ix:"
                    }

                    return "x:"; // •
                }
            }

            DSpinner {
                id: xSpinner
                width: posXFlipable.width - xLabel.width - DStyle.defaultSpacing
                anchors.verticalCenter: parent.verticalCenter
                //value: posXItemDelegateRoot.componentInfo ? Number(posXItemDelegateRoot.componentInfo.posX) : 0
                value: posXItemDelegateRoot.currentHandler ? Math.round(posXItemDelegateRoot.currentHandler.x) : 0

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
                        // Emit Tab Key Pressed Signal
                        posXItemDelegateRoot.tabKeyPressed();
//                        // Set X Spinner Focus
//                        xSpinner.setSpinnerFocus(true, true);
                    }
                }
            }
        }

        back: Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: posXBackLabel
                width: posXItemDelegateRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "x:"
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
                width: posXItemDelegateRoot.editButtonWidth
                height: DStyle.spinnerHeight

                text: "Edit"
                onClicked: {
                    // Emit Pos X Edit Launch Signal
                    propertiesPaneRoot.posXEditLaunch();
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
