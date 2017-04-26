import QtQuick 2.0

import "style"

DButtonBase {
    id: switchRoot

    property bool rightAligned: false

    DText {
        id: buttonText
        anchors.left: switchRoot.rightAligned ? undefined : parent.left
        anchors.right: switchRoot.rightAligned ? parent.right : undefined
        anchors.verticalCenter: parent.verticalCenter
        text: switchRoot.text
        color: switchRoot.highlight ? DStyle.colorBorder : DStyle.colorFontDark
    }

    DEditorBackground {
        id: buttonBG
        width: DStyle.switchWidth
        height: parent.height - DStyle.defaultMargin

        anchors.left: switchRoot.rightAligned ? parent.left : undefined
        anchors.right: switchRoot.rightAligned ? undefined : parent.right

        anchors.verticalCenter: parent.verticalCenter

        editorFocus: switchRoot.highlight
        radius: height / 2
    }

    DRectangle {
        anchors.fill: buttonBG
        anchors.margins: 2
        color: DStyle.colorBorderNoFocus
        border.color: "transparent"
        radius: height / 2
        opacity: switchRoot.checked ? 0.5 : 0.0
        Behavior on opacity { NumberAnimation { duration: DStyle.animDuration } }
        visible: opacity > 0.0
    }

    DRectangle {
        id: buttonSwitch
        width: buttonBG.height - 4
        height: width
        anchors.verticalCenter: buttonBG.verticalCenter
        radius: height / 2
        //border.color: switchRoot.highlight ? DStyle.colorBorder : DStyle.colorFontDark
        border.color: DStyle.colorFontDark

        states: [
            State {
                name: "off"
                when: !switchRoot.checked
                PropertyChanges { target: buttonSwitch; x: buttonBG.x + 2 }
            },

            State {
                name: "on"
                when: switchRoot.checked
                PropertyChanges { target: buttonSwitch; x: buttonBG.x + buttonBG.width - buttonSwitch.width - 2 }
            }
        ]

        transitions: [
            Transition {
                DAnimation { target: buttonSwitch; property: "x" }
            }
        ]
    }
}
