import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: posYItemDelegate

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
                width: sizeAndPosSectionRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "y:"
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

    DSwipeGesture {
        id: posYSwipe
        anchors.fill: parent
        actionButtonText: "Implicit"
        enableSwipe: true
        onActionButtonClicked: {

        }
    }
}
