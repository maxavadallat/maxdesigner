import QtQuick 2.0

import "style"

Item {
    id: sectionRoot

    width: 200
    height: DStyle.headerHeight

    property string title: "Section"

    property int minHeight: 200

    readonly property int openedHeight: Math.max(contentFlickable.contentHeight + sectionHeader.height + DStyle.defaultMargin * 2, minHeight)

    default property alias contentContainer: contentFlickable.contentContainer

    property alias titleBgColor: titleBGRect.color
    property string bgColor: "transparent"

    readonly property string stateOpen: "open"
    readonly property string stateClosed: "closed"
    readonly property string stateHidden: "hidden"

    property alias clipContent: contentFlickable.clip

    clip: false

    visible: opacity > 0.0

    function open() {
        // Set State
        sectionRoot.state = sectionRoot.stateOpen;
    }

    function close() {
        // Set State
        sectionRoot.state = sectionRoot.stateClosed;
    }

    function hide() {
        // Set State
        sectionRoot.state = sectionRoot.stateHidden;
    }

    DMouseArea {
        id: sectionHeader
        width: parent.width
        height: DStyle.headerHeight

        preventStealing: false

//        onClicked: {
//            if (sectionRoot.state === sectionRoot.stateOpen) {
//                close();
//            } else {
//                open();
//            }
//        }

        onReleased: {
            if (sectionRoot.state === sectionRoot.stateOpen) {
                close();
            } else {
                open();
            }
        }

        DRectangle {
            id: titleBGRect
            anchors.fill: parent
            color: DStyle.colorFontDark
            border.color: "transparent"
            opacity: 0.2
        }

        Row {
            id: titleRow
            height: parent.height

            // Indicator
            DText {
                id: indicator
                width: DStyle.headerHeight
                height: DStyle.headerHeight
                horizontalAlignment: Text.AlignHCenter
                text: sectionRoot.state === sectionRoot.stateOpen ? "-" : "+"
                font.bold: true
                color: sectionHeader.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            }

            // Title
            DText {
                id: titleText
                height: DStyle.headerHeight
                text: sectionRoot.title
                color: sectionHeader.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            }
        }
    }

    // Content
    DFlickable {
        id: contentFlickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: sectionHeader.bottom
        anchors.topMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        clip: true
    }

    states: [
        State {
            name: sectionRoot.stateHidden
            PropertyChanges { target: sectionRoot; height: 0; opacity: 0.0 }
        },

        State {
            name: sectionRoot.stateClosed
            PropertyChanges { target: sectionRoot; height: DStyle.headerHeight; opacity: 1.0 }
        },

        State {
            name: sectionRoot.stateOpen
            PropertyChanges { target: sectionRoot; height: sectionRoot.openedHeight; opacity: 1.0 }
        }
    ]

    transitions: [
        Transition {
            to: sectionRoot.stateHidden

            SequentialAnimation {
                DAnimation { target: sectionRoot; properties: "height, opacity" }
            }
        },

        Transition {
            to: sectionRoot.stateClosed

            SequentialAnimation {
                DAnimation { target: sectionRoot; properties: "height, opacity" }
            }
        },

        Transition {
            to: sectionRoot.stateOpen

            SequentialAnimation {
                DAnimation { target: sectionRoot; properties: "height, opacity" }
            }
        }
    ]
}
