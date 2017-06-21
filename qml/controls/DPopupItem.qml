import QtQuick 2.0

import "qrc:/qml/style"

DMouseArea {
    id: popupItemRoot

    width: DStyle.defaultPopupWidth + DStyle.defaultMargin * 2
    height: itemHeight

    property int itemHeight: itemTextLabel.text === "-" ? (DStyle.popupItemHeight * 0.5) : DStyle.popupItemHeight

    property int itemIndex: -1

    property string text: "option"

    property bool subMenuItem: false

    property bool selected: false

    property bool checked: false

    property bool showSelector: true

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
        width: popupItemRoot.width - (checkedIndicator.visible ? popupItemRoot.height : DStyle.defaultMargin * 2)
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        visible: text !== "-"
        elide: Text.ElideMiddle
        wrapMode: Text.NoWrap
        text: popupItemRoot.text
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

    DText {
        id: checkedIndicator
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -2
        text: "•"
        font.pixelSize: DStyle.fontSizeXL
        visible: popupItemRoot.checked && popupItemRoot.showSelector
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
