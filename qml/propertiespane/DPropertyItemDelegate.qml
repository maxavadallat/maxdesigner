import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

Item {
    id: propertyItemRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    Behavior on height { DAnimation { } }

    property string propertyName: "property"
    property string propertyType: "type"
    property string propertyValue: "value"
    property string propertyEnums: ""

    property bool propertyReadOnly: false

    property bool showFormula: false

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property bool enableSwipe: true

    property alias actionButtonText: swipeGesture.actionButtonText

    property bool itemExpanded: false
    property int expandedHeight: CONSTS.defaultPaneItemHeight

    property real propertyStep: {
        // Check Property Type
        if (propertyType === CONSTS.propertyTypes[3] || propertyType === CONSTS.propertyTypes[4]) {
            return 0.1;
        }

        return 1;
    }

    signal itemEditClicked(var itemIndex)
    signal itemActionClicked(var itemIndex)
    signal formulaEditClicked(var itemIndex)
    signal itemValueChanged(var itemIndex, var newValue)

    signal valueOptionShown()
    signal valueOptionClosed()

    onMarkFordeletionChanged: {
        propertyItemFlipable.front.setEditorFocus(!markFordeletion);
    }

    // Value Flipable
    DFlipable {
        id: propertyItemFlipable
        width: parent.width - CONSTS.defaultSwipeAreaWidth
        height: CONSTS.defaultPaneItemHeight

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: propertyItemRoot.itemExpanded ? frontDelegate.valueOptionOffset : 0

        Behavior on anchors.topMargin { DAnimation { } }

        enabled: !propertyItemRoot.markFordeletion && !propertyItemRoot.propertyReadOnly

        flipped: propertyItemRoot.showFormula

        front: DPropertyItemValue {
            id: frontDelegate
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height

            enabled: !propertyItemRoot.propertyReadOnly

            namesColumnWidth: propertyItemRoot.namesColumnWidth
            propertyName: propertyItemRoot.propertyReadOnly ? "•" + propertyItemRoot.propertyName : propertyItemRoot.propertyName
            propertyType: propertyItemRoot.propertyType
            propertyValue: propertyItemRoot.propertyValue
            propertyStep: propertyItemRoot.propertyStep
            propertyEnums: propertyItemRoot.propertyEnums

            onValueChanged: propertyItemRoot.itemValueChanged(itemIndex, newValue);
            onValueOptionZChanged: propertyItemRoot.z = valueOptionZ;

            onValueOptionStateChanged: {
                //console.log("DPropertyItem.onValueOptionStateChanged - valueOptionState: " + valueOptionState);
                // Check State
                if (valueOptionState === "open") {

                    // Set Expanded Height
                    propertyItemRoot.expandedHeight = frontDelegate.valueOptionPopupHeight;

                    //console.log("#### expandedHeight: " + propertyItemRoot.expandedHeight);

                    // Set Item Expanded
                    propertyItemRoot.itemExpanded = true;
                    // Set Root Height
                    propertyItemRoot.height = propertyItemRoot.expandedHeight;

                } else {

                    // Reset Item Expanded
                    propertyItemRoot.itemExpanded = false;
                    // Reset Root Height
                    propertyItemRoot.height = CONSTS.defaultPaneItemHeight;

                }
            }
        }

        back: DPropertyItemFormula {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height

            enabled: !propertyItemRoot.propertyReadOnly

            namesColumnWidth: propertyItemRoot.namesColumnWidth
            propertyName: propertyItemRoot.propertyName
            propertyFormula: propertyItemRoot.propertyValue
            onFormulaEditClicked: {
                // Emit Formula Edit Clicked Signal
                propertyItemRoot.formulaEditClicked(propertyItemRoot.itemIndex);
            }
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enableSwipe: propertyItemRoot.enableSwipe
        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            propertyItemRoot.itemActionClicked(propertyItemRoot.itemIndex);
        }
    }
}
