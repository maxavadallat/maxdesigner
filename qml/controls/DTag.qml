import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"

DRectangle {
    id: tagRoot

    width: tagLabel.width + deleteButton.width + DStyle.defaultMargin * 3
    height: CONSTS.defaultButtonHeight

    property string tagTitle: "Tag"

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

    DText {
        id: tagLabel
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
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
