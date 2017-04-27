import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: sizeAndPosSectionRoot
    width: 300
    title: "Size & Pos"
    minHeight: sizeAndPosFlow.height
    state: stateClosed

    DFlow {
        id: sizeAndPosFlow
        width: sizeAndPosSectionRoot.width

        Row {
            id: posRow
            spacing: DStyle.defaultSpacing
            Behavior on height { DAnimation { } }
            clip: true

            DText {
                width: 24
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "x: "
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

            DText {
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

        Row {
            id: sizeRow
            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            clip: true

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

            DText {
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
    }
}
