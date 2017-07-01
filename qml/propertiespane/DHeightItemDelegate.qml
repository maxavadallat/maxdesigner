import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: heightItemDelegateRoot

    width: 220
    height: DStyle.spinnerHeight

    readonly property int labelWidth: 32
    readonly property int editButtonWidth: 48

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: "purple"
    }

    DFlipable {
        id: heightFlipable
        anchors.fill: parent
        anchors.rightMargin: DStyle.defaultMargin * 2

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
                text: "h:"
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
                text: "h:"
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

    DSwipeGesture {
        id: posYSwipe
        anchors.fill: parent
        actionButtonText: "Implicit"
        enableSwipe: true
        onActionButtonClicked: {

        }
    }
}
