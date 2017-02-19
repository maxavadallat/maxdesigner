import QtQuick 2.0

import "Style.js" as STYLE

DMouseArea {
    id: popupItemRoot

    width: STYLE.defaultPopupWidth + STYLE.defaultMargin * 2
    height: itemTextLabel.text === "-" ? (STYLE.popupItemHeight * 0.5) : STYLE.popupItemHeight

    property int itemIndex: -1

    property alias text: itemTextLabel.text

    property bool subMenuItem: false

    property bool selected: false

    property int textWidth: itemTextLabel.text !== "-" ? itemTextLabel.width : STYLE.defaultPopupWidth

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
        color: popupItemRoot.selected && itemTextLabel.text !== "-" ? STYLE.colorSelectedHighLight : "transparent"
    }

    DText {
        id: itemTextLabel
        anchors.left: parent.left
        anchors.leftMargin: STYLE.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        visible: text !== "-"
    }

    DText {
        id: subMenuItemIndicator
        anchors.right: parent.right
        anchors.rightMargin: STYLE.defaultMargin
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
        interval: STYLE.popupItemHoverTimeout
        onTriggered: {
            popupItemRoot.subMenuItemSelected(itemIndex);
        }
    }
}
