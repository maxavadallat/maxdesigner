import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/controls"

Item {
    id: transitionItemRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int itemIndex: -1

    property string stateFrom: "from"
    property string stateTo: "to"
    property int nodesCount: 0

    property bool enableSwipe: true

    signal itemActionClicked(var index)
    signal itemClicked(var index)
    signal itemDoubleClicked(var index)

    // ...

    Row {
        id: transitionItemRow
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        spacing: DStyle.defaultSpacing

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            visible: transitionItemRoot.stateFrom !== ""
            text: "from:"
        }

        DText {
            id: fromLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            visible: transitionItemRoot.stateFrom !== ""
            text: transitionItemRoot.stateFrom
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            visible: transitionItemRoot.stateTo !== ""
            text: "to:"
        }

        DText {
            id: toLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            visible: transitionItemRoot.stateTo !== ""
            text: transitionItemRoot.stateTo
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            visible: transitionItemRoot.nodesCount > 0
            text: "nodes:"
        }

        DText {
            id: nodesLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            visible: transitionItemRoot.nodesCount > 0
            text: "{ ... }"
        }
    }

    DMouseArea {
        anchors.fill: parent

        onClicked: {
            // Emit Item Clicked Signal
            transitionItemRoot.itemClicked(transitionItemRoot.itemIndex);
        }

        onDoubleClicked: {
            // Emit Item Double Clicked Signal
            transitionItemRoot.itemDoubleClicked(transitionItemRoot.itemIndex);
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enableSwipe: transitionItemRoot.enableSwipe
        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            transitionItemRoot.itemActionClicked(transitionItemRoot.itemIndex);
        }
    }

}
