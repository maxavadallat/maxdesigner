import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: signalItemDelegateRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property string signalName: "signal(...)"

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property bool enableSwipe: true

    property bool itemCurrent: false

    signal itemClicked(var itemIndex)
    signal itemDoubleClicked(var itemIndex)
    signal itemActionClicked(var itemIndex)

    DRectangle {
        anchors.fill: parent
        color: signalItemDelegateRoot.itemCurrent ? DStyle.colorSelectedHighLight : "transparent"
        border.color: "transparent"
        opacity: 0.2
    }

    DText {
        id: signalText
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.NoWrap
        elide: Text.ElideRight
        text: signalItemDelegateRoot.signalName
    }

    DMouseArea {
        id: signalItemMouseArea
        anchors.fill: parent

        onClicked: {
            signalItemDelegateRoot.itemClicked(signalItemDelegateRoot.itemIndex);
        }

        onDoubleClicked: {
            signalItemDelegateRoot.itemDoubleClicked(signalItemDelegateRoot.itemIndex);
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enabled: signalItemDelegateRoot.enableSwipe

        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            signalItemDelegateRoot.itemActionClicked(signalItemDelegateRoot.itemIndex);
        }
    }
}
