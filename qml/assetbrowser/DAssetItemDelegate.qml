import QtQuick 2.0

import "../style"
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

    Rectangle {
        anchors.fill: parent
        //color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.1)
        color: "transparent"
        border.color: {
//            // Check Item Index
//            if (itemIndex === gridCurrentIndex) {
//                return DStyle.colorBorder;
//            }

            return "#FF333333";
        }
    }

    DImage {
        id: assetImage
        anchors.fill: parent
        anchors.margins: DStyle.defaultMargin

        fillMode: {
            // Check If Dir
            if (assetItemDelegateRoot.isDir) {
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
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        spacing: DStyle.defaultSpacing

        DText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: assetItemDelegateRoot.fileName
        }

        DText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: {
                // Check If Dir
                if (assetItemDelegateRoot.isDir) {
                    return ""
                }

                return assetItemDelegateRoot.fileSize + " KB";
            }
        }
    }

    // ...
}
