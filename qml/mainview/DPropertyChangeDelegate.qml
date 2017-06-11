import QtQuick 2.0

import enginecomponents 0.1

import "../style"
import "../system/DConstants.js" as CONSTS
import "../controls"
import "../animations"

DMouseArea {
    id: propertyChangeDelegateRoot

    width: 300
    height: CONSTS.defaultPaneItemHeight

    property int itemIndex

    property ComponentPropertyChange componentPropertyChange: null

    property string propertyChangeTarget: "target"
    property string propertyChangeProperty: "property"
    property string propertyChangeValue: "value"

    property bool enableSwipe: true

    signal itemActionClicked()

    Row {
        id: propertyChangeDelegateRow
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2

        spacing: DStyle.defaultSpacing

        clip: true

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "target:"
        }

        DText {
            id: targetLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            text: propertyChangeDelegateRoot.propertyChangeTarget
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "property:"
        }

        DText {
            id: propertyLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            text: propertyChangeDelegateRoot.propertyChangeProperty
        }

        DText {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "value:"
        }

        DText {
            id: valueLabel
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            text: propertyChangeDelegateRoot.propertyChangeValue
        }
    }

    // Swipe Gesture Area
    DSwipeGesture {
        id: swipeGesture
        anchors.fill: parent
        enableSwipe: propertyChangeDelegateRoot.enableSwipe
        onActionButtonClicked: {
            //console.log("DPropertyChangeDelegate.swipeGesture.onActionButtonClicked");
            // Emit Item Action Clicked Signal
            propertyChangeDelegateRoot.itemActionClicked(propertyChangeDelegateRoot.itemIndex);
        }
    }
}
