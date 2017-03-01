import QtQuick 2.0

import "Style.js" as STYLE

Item {
    id: sectionRoot

    width: 200
    height: STYLE.headerHeight

    property string title: "Section"

    property int minHeight: 200

    readonly property int openedHeight: Math.max(contentFlickable.contentHeight + sectionHeader.height + STYLE.defaultMargin * 2, minHeight)

    default property alias contentContainer: contentFlickable.contentContainer

    property alias titleBgColor: titleBGRect.color
    property string bgColor: "transparent"

    readonly property string stateOpen: "open"
    readonly property string stateClosed: "closed"
    readonly property string stateHidden: "hidden"

    property alias clipContent: contentFlickable.clip

    clip: false

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
        height: STYLE.headerHeight

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
            color: STYLE.colorFontDark
            border.color: "transparent"
            opacity: 0.2
        }

        Row {
            id: titleRow
            height: parent.height

            // Indicator
            DText {
                id: indicator
                width: STYLE.headerHeight
                height: STYLE.headerHeight
                horizontalAlignment: Text.AlignHCenter
                text: sectionRoot.state === sectionRoot.stateOpen ? "-" : "+"
                font.bold: true
                color: sectionHeader.pressed ? STYLE.colorBorder : STYLE.colorFontDark
            }

            // Title
            DText {
                id: titleText
                height: STYLE.headerHeight
                text: sectionRoot.title
                color: sectionHeader.pressed ? STYLE.colorBorder : STYLE.colorFontDark
            }
        }
    }

    // Content
    DFlickable {
        id: contentFlickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: sectionHeader.bottom
        anchors.topMargin: STYLE.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: STYLE.defaultMargin
        clip: true
    }

    states: [
        State {
            name: sectionRoot.stateHidden
            PropertyChanges { target: sectionRoot; height: 0 }
            PropertyChanges { target: sectionRoot; opacity: 0.0 }
        },

        State {
            name: sectionRoot.stateClosed
            PropertyChanges { target: sectionRoot; height: STYLE.headerHeight }
        },

        State {
            name: sectionRoot.stateOpen
            PropertyChanges { target: sectionRoot; height: sectionRoot.openedHeight }
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
