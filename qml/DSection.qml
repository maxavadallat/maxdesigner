import QtQuick 2.0

import "Style.js" as STYLE

Item {
    id: sectionRoot

    width: 200
    height: STYLE.headerHeight

    property string title: "Section"

    readonly property int openedHeight: Math.max(contentFlickable.contentHeight + sectionHeader.height + STYLE.defaultMargin * 2, 200)

    default property alias contentContainer: contentFlickable.contentContainer

    readonly property string stateOpen: "open"
    readonly property string stateClosed: "closed"

    clip: true

    function open() {
        // Set State
        sectionRoot.state = sectionRoot.stateOpen;
    }

    function close() {
        // Set State
        sectionRoot.state = sectionRoot.stateClosed;
    }

    DMouseArea {
        id: sectionHeader
        width: parent.width
        height: STYLE.headerHeight

        onClicked: {
            if (sectionRoot.state === sectionRoot.stateOpen) {
                close();
            } else {
                open();
            }
        }

        DRectangle {
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

//    Rectangle {
//        anchors.fill: parent
//        color: "transparent"
//        border.color: "orange"
//    }

    // Content
    DFlickable {
        id: contentFlickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: sectionHeader.bottom
        anchors.topMargin: STYLE.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: STYLE.defaultMargin
    }

    states: [
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
            to: sectionRoot.stateClosed

            SequentialAnimation {
                DAnimation { target: sectionRoot; properties: "height" }
            }
        },

        Transition {
            to: sectionRoot.stateOpen

            SequentialAnimation {
                DAnimation { target: sectionRoot; properties: "height" }
            }
        }
    ]
}
