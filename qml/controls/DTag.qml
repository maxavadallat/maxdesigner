import QtQuick 2.7

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"

DRectangle {
    id: tagRoot

    width: tagLabel.width + deleteButton.width + DStyle.defaultMargin
    height: CONSTS.defaultButtonHeight

    property string tagTitle: "Tag"

    property int maxWidth: 1024

    radius: DStyle.defaultRadius * 2

    signal removeClicked()
    signal doubleClicked()

    DRectangle {
        anchors.fill: parent
        radius: parent.radius
        border.color: "transparent"
        color: DStyle.colorBorderNoFocus
        opacity: 0.2
    }

    DMouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            tagRoot.doubleClicked();
        }
    }

    TextMetrics {
        id: tagLabelMetrics
        font: tagLabel.font
        text: tagRoot.tagTitle
    }

    DText {
        id: tagLabel

        width: Math.min(tagLabelMetrics.boundingRect.width + 4, tagRoot.maxWidth - deleteButton.width + DStyle.defaultMargin)

        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter

        wrapMode: Text.NoWrap
        elide: Text.ElideMiddle

        text: tagRoot.tagTitle
    }

    DMouseArea {
        id: deleteButton
        width: parent.height
        height: parent.height
        anchors.right: parent.right

        scale: pressed ? 0.9 : 1.0

        DRectangle {
            width: parent.width * 0.7
            height: parent.height * 0.7
            anchors.centerIn: parent
            color: parent.pressed ? DStyle.colorHighLight : "transparent"
            border.color: "transparent"
            radius: width * 0.5

            DText {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -1
                text: "x"
            }
        }

        onClicked: {
            tagRoot.removeClicked();
        }
    }
}
