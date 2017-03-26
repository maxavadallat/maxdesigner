import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

DSwipeGesture {
    id: propertyItemRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int itemIndex: 0
    property bool markFordeletion: false
    property bool swipeWasOn: false

    property bool deleteButtonClicked: false
    property bool formulaEditButtonClicked: false

    enableSwipe: true

    swipeDirection: -1
    swipeThreshold: propertyItemRoot.width - deleteButton.width * 0.7
    swipeOnFinalPosX: deleteButton.showPosX

    clip: true

    signal deleteItemClicked(var itemIndex)
    signal formulaEditClicked(var itemIndex)

    onPressed: {
        // Set Behavior Duration
        deleteButton.behaviorDuration = 0;
        // Reset Delete Button Clicked
        propertyItemRoot.deleteButtonClicked = false;
        // Reset Formula Edit Button Clicked
        propertyItemRoot.formulaEditButtonClicked = false;
    }

    onSwipeOnChanged: {
        //console.log("DPropertyItem.onSwipeOnChanged - swipeOn: " + swipeOn);
        if (!propertyItemRoot.pressed) {
            // Set Mark For Deletion
            propertyItemRoot.markFordeletion = propertyItemRoot.swipeOn;
        }

        // Reset Delete Button Clicked
        propertyItemRoot.deleteButtonClicked = false;
        // Reset Formula Edit Button Clicked
        propertyItemRoot.formulaEditButtonClicked = false;
    }

    onSwipePosXChanged: {
        // Set Delete Button Position
        deleteButton.x = propertyItemRoot.swipePosX;
    }

    onReleased: {
        // Set Mark For Deletion
        propertyItemRoot.markFordeletion = propertyItemRoot.swipeOn;
        // Set Behavior Duration
        deleteButton.behaviorDuration = DStyle.animDuration;
        // Bind Delete Button Pos X
        deleteButton.x = Qt.binding(function() {
            return propertyItemRoot.markFordeletion ? deleteButton.showPosX : deleteButton.hiddenPosX;
        })
    }

    onManualDoubleClick: {
        //console.log("DPropertyItem.onManualDoubleClick");
        // Check Delete Button Clicked
        if (!propertyItemRoot.deleteButtonClicked && !propertyItemRoot.formulaEditButtonClicked) {
            // Flip
            propertyItemFlipable.flipped = !propertyItemFlipable.flipped;
        }

        // Reset Delete Button Clicked
        propertyItemRoot.deleteButtonClicked = false;
        // Reset Formula Edit Button Clicked
        propertyItemRoot.formulaEditButtonClicked = false;
    }

    DFlipable {
        id: propertyItemFlipable
        anchors.fill: parent
        handleDoubleClick: false

        front: DPropertyItemValue {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height
            editorMouseSelection: false
            editorFocus: !propertyItemRoot.markFordeletion
        }

        back: DPropertyItemFormula {
            width: propertyItemFlipable.width
            height: propertyItemFlipable.height
            onFormulaEditClicked: {
                // Set Formula Edit Button Clicked
                propertyItemRoot.formulaEditButtonClicked = true;
                // Emit Formula Edit Clicked Signal
                propertyItemRoot.formulaEditClicked(propertyItemRoot.itemIndex);
            }
        }
    }

    // Content Fade Curtain
    Rectangle {
        id: contentfade
        anchors.fill: parent
        color: "#77000000"
        opacity: (deleteButton.hiddenPosX - deleteButton.x) / (deleteButton.hiddenPosX - deleteButton.showPosX)
        visible: opacity > 0.0
    }

    // Delete Button
    DButton {
        id: deleteButton

        x: propertyItemRoot.markFordeletion ? deleteButton.showPosX : deleteButton.hiddenPosX

        Behavior on x { DAnimation { duration: deleteButton.behaviorDuration } }

        property real showPosX: propertyItemRoot.width - deleteButton.width - DStyle.defaultMargin
        property real hiddenPosX: propertyItemRoot.width + DStyle.defaultMargin
        property int behaviorDuration: DStyle.animDuration

        anchors.verticalCenter: parent.verticalCenter

        preventStealing: true

        bgColor: DStyle.colorCancel
        highlightColor: DStyle.colorCancelHighLight
        text: "Delete"

        onClicked: {
            // Set Delete Button Clicked
            propertyItemRoot.deleteButtonClicked = true;

            // Reset Swipe On
            //propertyItemRoot.swipeOn = false;

            // Emit Delete Item Clicked Signal
            propertyItemRoot.deleteItemClicked(propertyItemRoot.itemIndex);
        }
    }
}
