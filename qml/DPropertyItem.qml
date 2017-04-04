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

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    property bool enableSwipe: true

    //clip: true

    signal itemActionClicked(var itemIndex)
    signal formulaEditClicked(var itemIndex)

    onMarkFordeletionChanged: {
        propertyItemFlipable.front.setEditorFocus(!markFordeletion);
    }

    // Value Flipable
    DFlipable {
        id: propertyItemFlipable
        anchors.fill: parent
        anchors.rightMargin: CONSTS.defaultSwipeAreaWidth
        enabled: !propertyItemRoot.markFordeletion

        flipped: propertyItemRoot.propertyValue.length > 0 && propertyItemRoot.propertyValue[0] === "{"

        front: DPropertyItemValue {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height
            namesColumnWidth: propertyItemRoot.namesColumnWidth
            //editorMouseSelection: false
            //editorFocus: !propertyItemRoot.markFordeletion
            propertyName: propertyItemRoot.propertyName
            propertyType: propertyItemRoot.propertyType
            propertyValue: propertyItemRoot.propertyValue
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
        enabled: propertyItemRoot.enableSwipe

        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            propertyItemRoot.itemActionClicked(propertyItemRoot.itemIndex);
        }
    }
}
