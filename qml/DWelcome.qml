import QtQuick 2.0

import "style"

Column {
    id: welcomeRoot

    readonly property string stateShown: "shown"
    readonly property string stateHidden: "hidden"

    opacity: 1.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    // Show
    function show() {
        // Set State
        welcomeRoot.state = welcomeRoot.stateShown;
    }

    // Hide
    function hide() {
        // Set State
        welcomeRoot.state = welcomeRoot.stateHidden;
    }

    DText {
        height: 48
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Welcome to Designer!"
        font.pixelSize: DStyle.fontSizeXL
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
        font.pixelSize: DStyle.fontSizeL
    }

    DText {
        width: 256
        anchors.horizontalCenter: parent.horizontalCenter
        text: "- Open Project: ⌘O"
        font.pixelSize: DStyle.fontSizeL
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
        visible: rpListView.count > 0
    }

    DText {
        //height: 48
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Recent Projects"
        //font.pixelSize: DStyle.fontSizeXL
        visible: rpListView.count > 0
    }

    // Recent Project List
    ListView {
        id: rpListView
        width: 512
        height: Math.min(contentHeight, delegateHeight * 5)

        property int delegateHeight: DStyle.fontSizeL

        anchors.horizontalCenter: parent.horizontalCenter
        model: recentProjectsModel

        delegate: DMouseArea {
            id: delegateRoot

            width: rpListView.width
            height: rpListView.delegateHeight

            property bool hovering: false

            hoverEnabled: true

            DText {
                id: titleText
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideMiddle
                horizontalAlignment: Text.AlignHCenter
                text: filePath
                color: delegateRoot.pressed && delegateRoot.hovering ? DStyle.colorBorder : DStyle.colorFontDark
            }

            onEntered: {
                delegateRoot.hovering = true;
            }

            onExited: {
                delegateRoot.hovering = false;
            }

            onCanceled: {
                delegateRoot.hovering = false;
            }

            onClicked: {
                // Open Project
                mainController.openProject(filePath);
            }
        }
    }

    states: [
        State {
            name: welcomeRoot.stateShown

            PropertyChanges { target: welcomeRoot; opacity: 1.0 }
        },

        State {
            name: welcomeRoot.stateHidden

            PropertyChanges { target: welcomeRoot; opacity: 0.0 }
        }
    ]

    transitions: [
        Transition {
            to: welcomeRoot.stateShown

            SequentialAnimation {
                PauseAnimation { duration: 600 }
                DFadeAnimation { target: welcomeRoot }
            }
        },

        Transition {
            to: welcomeRoot.stateHidden

            SequentialAnimation {
                //PauseAnimation { duration: 200 }
                DFadeAnimation { target: welcomeRoot }
            }
        }
    ]
}
