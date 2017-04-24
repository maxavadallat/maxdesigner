import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: propertyItemRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property string propertyName: "property"
    property string propertyType: "type"
    property string propertyValue: "value"

    property bool showFormula: false

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property bool enableSwipe: true

    property alias actionButtonText: swipeGesture.actionButtonText

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

    onMarkFordeletionChanged: {
        propertyItemFlipable.front.setEditorFocus(!markFordeletion);
    }

    // Value Flipable
    DFlipable {
        id: propertyItemFlipable
        anchors.fill: parent
        anchors.rightMargin: CONSTS.defaultSwipeAreaWidth
        enabled: !propertyItemRoot.markFordeletion

        flipped: propertyItemRoot.showFormula

        front: DPropertyItemValue {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height
            namesColumnWidth: propertyItemRoot.namesColumnWidth
            propertyName: propertyItemRoot.propertyName
            propertyType: propertyItemRoot.propertyType
            propertyValue: propertyItemRoot.propertyValue
            propertyStep: propertyItemRoot.propertyStep
            onValueChanged: propertyItemRoot.itemValueChanged(itemIndex, newValue);
        }

        back: DPropertyItemFormula {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height
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
