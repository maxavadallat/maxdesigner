import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: widthItemDelegateRoot

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
        id: widthFlipable
        anchors.fill: parent
        anchors.rightMargin: DStyle.defaultMargin * 2

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
                text: "w:"
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
                text: "w:"
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

    DSwipeGesture {
        id: posYSwipe
        anchors.fill: parent
        actionButtonText: "Implicit"
        enableSwipe: true
        onActionButtonClicked: {

        }
    }
}
