import QtQuick 2.0

import "qrc:/qml/style"
import "../system/DConstants.js" as CONSTS
import "../controls"

DMouseArea {
    id: assetItemDelegateRoot

    width: 300
    height: 200

    property int gridCurrentIndex: -1
    property int itemIndex: -1

    property string filePath: ""
    property bool isDir: false
    property string fileName: ""
    property string fileSize: ""
    property string dimension: ""

    DImage {
        id: assetImage
        anchors.fill: parent
        anchors.leftMargin: DStyle.defaultMargin
        anchors.rightMargin: DStyle.defaultMargin
        anchors.topMargin: DStyle.defaultMargin
        anchors.bottomMargin: DStyle.defaultMargin * 2 + infoColumn.height

        fillMode: {
            // Check If Dir
            if (assetItemDelegateRoot.isDir) {
                return Image.Pad;
            }

            // Check Source Size
            if (sourceSize.width <= width && sourceSize.height <= height) {
                return Image.Pad;
            }

            return Image.PreserveAspectFit;
        }

        source: {
            // Check If Dir
            if (assetItemDelegateRoot.isDir) {
                return "image://fileIcon/" + assetItemDelegateRoot.filePath;
            }

            return "file://" + assetItemDelegateRoot.filePath;
        }
    }

    Column {
        id: infoColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        spacing: DStyle.defaultSpacing

        DText {
            id: nameLabel
            width: assetItemDelegateRoot.width - DStyle.defaultMargin * 2
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: DStyle.fontSizeM
            elide: Text.ElideMiddle
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.NoWrap
            text: assetItemDelegateRoot.fileName
        }
    }
}
