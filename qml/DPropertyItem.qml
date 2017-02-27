import QtQuick 2.0

import "Style.js" as STYLE

DSwipeGesture {
    id: propertyItemRoot

    property int itemIndex: 0

    default property alias contentChildren: contentContainer.children

    enableSwipe: true

    swipeDirection: -1
    swipeThreshold: propertyItemRoot.width - deleteButton.width * 0.7
    swipeOnFinalPosX: deleteButton.showPosX

    property bool markFordeletion: false

    property bool swipeWasOn: false

    clip: true

    signal deleteItemClicked(var itemIndex)

    onPressed: {
        // Set Behavior Duration
        deleteButton.behaviorDuration = 0;
    }

    onSwipeOnChanged: {
        //console.log("DPropertyItem.onSwipeOnChanged - swipeOn: " + swipeOn);
        if (!propertyItemRoot.pressed) {
            // Set Mark For Deletion
            propertyItemRoot.markFordeletion = propertyItemRoot.swipeOn;
        }
    }

    onDeltaXChanged: {
//        if (pressed) {
//            if (swipeWasOn) {
//                deleteButton.x = Math.min(deleteButton.showPosX + propertyItemRoot.deltaX, deleteButton.hiddenPosX);
//            } else {
//                deleteButton.x = Math.max(deleteButton.hiddenPosX + propertyItemRoot.deltaX, deleteButton.showPosX);
//            }
//        }
    }

    onSwipePosXChanged: {
        deleteButton.x = propertyItemRoot.swipePosX;
    }

    onReleased: {
        //console.log("DPropertyItem.onReleased");
        // Set Mark For Deletion
        propertyItemRoot.markFordeletion = propertyItemRoot.swipeOn;
        // Set Behavior Duration
        deleteButton.behaviorDuration = STYLE.animDuration;
        // Bind Delete Button Pos X
        deleteButton.x = Qt.binding(function() {
            return propertyItemRoot.markFordeletion ? deleteButton.showPosX : deleteButton.hiddenPosX;
        })
    }

    // Content Container
    Item {
        id: contentContainer
        anchors.fill: parent
        enabled: !propertyItemRoot.markFordeletion

        DCheckBox {
            anchors.centerIn: parent
            text: "Checkbox"
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: swipeOn ? "orange" : "gray"
        radius: STYLE.defaultRadius
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

        property real showPosX: propertyItemRoot.width - deleteButton.width - STYLE.defaultMargin
        property real hiddenPosX: propertyItemRoot.width + STYLE.defaultMargin
        property int behaviorDuration: STYLE.animDuration

        anchors.verticalCenter: parent.verticalCenter

        preventStealing: true

        bgColor: STYLE.colorCancel
        highlightColor: STYLE.colorCancelHighLight
        text: "Delete"

        onXChanged: {
//            console.log("DPropertyItem.deleteButton.onXChanged - hpx: " + (deleteButton.hiddenPosX));
//            console.log("DPropertyItem.deleteButton.onXChanged - spx: " + (deleteButton.showPosX));
//            console.log("DPropertyItem.deleteButton.onXChanged - hpx - x: " + (deleteButton.hiddenPosX - deleteButton.x));
        }

        onClicked: {
            // Reset Swipe On
            propertyItemRoot.swipeOn = false;
            // Reset Mark For Deletion
            //propertyItemRoot.markFordeletion = false;
            // Emit Delete Item Clicked Signal
            propertyItemRoot.deleteItemClicked(propertyItemRoot.itemIndex);
        }
    }
}
