import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

Item {
    id: functionItemDelegateRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property string functionName: "function() {...}"

    property int itemIndex: -1

    property bool markFordeletion: swipeGesture.swipeOn

    property bool enableSwipe: true

    property bool itemCurrent: false

    signal itemClicked(var itemIndex)
    signal itemDoubleClicked(var itemIndex)
    signal itemActionClicked(var itemIndex)

    DRectangle {
        anchors.fill: parent
        color: functionItemDelegateRoot.itemCurrent ? DStyle.colorSelectedHighLight : "transparent"
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
        elide: Text.ElideMiddle
        text: functionItemDelegateRoot.functionName
    }

    DMouseArea {
        id: functionItemMouseArea
        anchors.fill: parent

        onClicked: {
            functionItemDelegateRoot.itemClicked(functionItemDelegateRoot.itemIndex);
        }

        onDoubleClicked: {
            functionItemDelegateRoot.itemDoubleClicked(functionItemDelegateRoot.itemIndex);
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enabled: functionItemDelegateRoot.enableSwipe

        onActionButtonClicked: {
            //console.log("DFunctionItemDelegate.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            functionItemDelegateRoot.itemActionClicked(functionItemDelegateRoot.itemIndex);
        }
    }
}
