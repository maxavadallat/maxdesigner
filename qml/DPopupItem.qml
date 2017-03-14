import QtQuick 2.0

import "style"

DMouseArea {
    id: popupItemRoot

    width: DStyle.defaultPopupWidth + DStyle.defaultMargin * 2
    height: itemTextLabel.text === "-" ? (DStyle.popupItemHeight * 0.5) : DStyle.popupItemHeight

    property int itemIndex: -1

    property alias text: itemTextLabel.text

    property bool subMenuItem: false

    property bool selected: false

    property int textWidth: itemTextLabel.text !== "-" ? itemTextLabel.width : DStyle.defaultPopupWidth

    hoverEnabled: true

    acceptedButtons: { Qt.LeftButton }

    signal itemClicked(var index)
    signal subMenuItemSelected(var index)

    onEntered: {
        if (subMenuItem && containsMouse) {
            hoverTimer.running = true;
        }
    }

    onExited: {
        hoverTimer.running = false;
    }

    onCanceled: {
        hoverTimer.running = false;
    }

    onClicked: {
        if (popupItemRoot.subMenuItem && hoverTimer.running) {
            hoverTimer.running = false;
            popupItemRoot.subMenuItemSelected(itemIndex);
        } else {
            popupItemRoot.itemClicked(itemIndex);
        }
    }

    Rectangle {
        anchors.fill: parent
        color: popupItemRoot.selected && itemTextLabel.text !== "-" ? DStyle.colorSelectedHighLight : "transparent"
    }

    DText {
        id: itemTextLabel
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        visible: text !== "-"
    }

    DText {
        id: subMenuItemIndicator
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -1
        text: ">"
        visible: popupItemRoot.subMenuItem
    }

    Rectangle {
        width: parent.width
        height: 1
        anchors.verticalCenter: parent.verticalCenter
        visible: itemTextLabel.text === "-"
    }

    Timer {
        id: hoverTimer
        interval: DStyle.popupItemHoverTimeout
        onTriggered: {
            popupItemRoot.subMenuItemSelected(itemIndex);
        }
    }
}
