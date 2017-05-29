import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: stateItemRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int itemIndex: -1

    property string stateName: "name"
    property string stateWhen: "when"
    property string statePropertyChanges: ""

    property bool enableSwipe: true

    signal itemActionClicked(var index)
    signal itemDoubleClicked(var index)

    // ...

    Row {
        id: stateItemRow
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        spacing: DStyle.defaultSpacing

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "name:"
        }

        DText {
            id: nameLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            text: stateItemRoot.stateName
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            visible: stateItemRoot.stateWhen !== ""
            text: "when:"
        }

        DText {
            id: whenLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            visible: stateItemRoot.stateWhen !== ""
            text: stateItemRoot.stateWhen
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            visible: stateItemRoot.statePropertyChanges !== ""
            text: "changes:"
        }

        DText {
            id: propertyChangesLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            visible: stateItemRoot.statePropertyChanges !== ""
            text: stateItemRoot.statePropertyChanges
        }
    }

    DMouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            // Emit Item Double Clicked Signal
            stateItemRoot.itemDoubleClicked(stateItemRoot.itemIndex);
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enableSwipe: stateItemRoot.enableSwipe
        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            stateItemRoot.itemActionClicked(stateItemRoot.itemIndex);
        }
    }
}
