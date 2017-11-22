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
    property QtObject currentHandler: propertiesController.currentHandler

    signal tabKeyPressed()

    // Set FLipped State
    function setFlipHeight(aFlipped) {
        // Set Flipped State
        heightFlipable.flipped = aFlipped;
    }

    // Set Editor Focus
    function setEditorFocus(aFocus) {
        // Set Spinner Focus
        heightSpinner.setSpinnerFocus(aFocus, aFocus);
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
                width: heightItemDelegateRoot.labelWidth
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: {
                    // Check Component Info
                    if (heightItemDelegateRoot.componentInfo && heightItemDelegateRoot.componentInfo.propertyIsFormula("h")) {
                        return "fh:"
                    }

                    // Check For Implicit Height
                    if (heightItemDelegateRoot.componentInfo && heightItemDelegateRoot.componentInfo.useIHeight) {
                        return "ih:"
                    }

                    return "h:"; // •
                }
            }

            DSpinner {
                id: heightSpinner
                width: heightFlipable.width - heightLabel.width - DStyle.defaultSpacing
                anchors.verticalCenter: parent.verticalCenter
                //value: heightItemDelegateRoot.componentInfo ? Number(heightItemDelegateRoot.componentInfo.height) : 0
                value: heightItemDelegateRoot.currentHandler ? Math.round(heightItemDelegateRoot.currentHandler.height) : 0
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
                        // Emit Tab Key Pressed Signal
                        heightItemDelegateRoot.tabKeyPressed();
//                        // Check Pos Row height
//                        if (posRow.height > 0) {
//                            // Set X Spinner Focus
//                            xSpinner.setSpinnerFocus(true, true);
//                        } else {
//                            // Set Width Spinner Focus
//                            widthSpinner.setSpinnerFocus(true, true);
//                        }
                    }
                }
            }
        }

        back: Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: heightBackLabel
                width: heightItemDelegateRoot.labelWidth
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
                width: heightItemDelegateRoot.editButtonWidth
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

        enableSwipe: {
            // Check Component Info
            if (heightItemDelegateRoot.componentInfo) {
                // Check If Already Use Implicit Height
                if (heightItemDelegateRoot.componentInfo.useIHeight) {
                    return false;
                }

                // Get Built In Base Component
                var biBase = heightItemDelegateRoot.componentInfo.builtInBase();

                // Check Built In Base Component
                if (biBase === "Text" || biBase === "Image" || biBase === "Row" || biBase === "Column" || biBase === "Flow") {
                    return true;
                }
            }

            return false;
        }

        onActionButtonClicked: {
            // Set Use Implicit Height
            heightItemDelegateRoot.componentInfo.useIHeight = true;
        }
    }
}
