import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/controls"

Item {
    id: slotItemDelegateRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property string slotName: "onNewSlot: {...}"

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property bool enableSwipe: true

    property bool itemCurrent: false

    signal itemClicked(var itemIndex)
    signal itemDoubleClicked(var itemIndex)
    signal itemActionClicked(var itemIndex)

    DRectangle {
        anchors.fill: parent
        color: slotItemDelegateRoot.itemCurrent ? DStyle.colorSelectedHighLight : "transparent"
        border.color: "transparent"
        opacity: 0.2
    }

    DText {
        id: slotText
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.NoWrap
        elide: Text.ElideRight
        text: slotItemDelegateRoot.slotName
    }

    DMouseArea {
        id: slotItemMouseArea
        anchors.fill: parent

        onClicked: {
            slotItemDelegateRoot.itemClicked(slotItemDelegateRoot.itemIndex);
        }

        onDoubleClicked: {
            slotItemDelegateRoot.itemDoubleClicked(slotItemDelegateRoot.itemIndex);
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enabled: slotItemDelegateRoot.enableSwipe

        onActionButtonClicked: {
            //console.log("DPropertyItem.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            slotItemDelegateRoot.itemActionClicked(slotItemDelegateRoot.itemIndex);
        }
    }
}
