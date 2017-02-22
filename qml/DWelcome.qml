import QtQuick 2.0

import "Style.js" as STYLE

Column {
    id: welcomeRoot
    opacity: 1.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    DText {
        height: 48
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Welcome to Designer!"
        font.pixelSize: STYLE.fontSizeXL
    }

    DRectangle {
        width: 300
        height: 1
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Item {
        width: 256
        height: 8
    }

    DText {
        width: 256
        anchors.horizontalCenter: parent.horizontalCenter
        text: "- Create a New Project: ⌘N"
        font.pixelSize: STYLE.fontSizeL
    }

    DText {
        width: 256
        anchors.horizontalCenter: parent.horizontalCenter
        text: "- Open Project: ⌘O"
        font.pixelSize: STYLE.fontSizeL
    }

    Item {
        width: 256
        height: 8
    }

    DRectangle {
        width: 300
        height: 1
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Item {
        width: 256
        height: 8
    }

    DText {
        //height: 48
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Recent Projects"
        //font.pixelSize: STYLE.fontSizeXL
    }

    // Recent Project List

    ListView {
        id: rpListView
        width: 512
        //height:

        anchors.horizontalCenter: parent.horizontalCenter
        //model: recentProjectsModel

        delegate: DMouseArea {
            id: delegateRoot
            width: rpListView.width
            DText {
                width: parent.width
                elide: Text.ElideMiddle
                text: filePath
                color: delegateRoot.pressed && delegateRoot.containsMouse ? STYLE.colorBorder : STYLE.colorFontDark
            }

            onClicked: {
                //mainController.
            }
        }
    }
}
