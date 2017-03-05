import QtQuick 2.0

import "style"

DMouseArea {
    id: flipableRoot

    property alias front: flipable.front
    property alias back: flipable.back

    property bool flipped: false

    onDoubleClicked: {
        // Toggle Flipped
        flipableRoot.flipped = !flipableRoot.flipped;
    }

    // Flipable
    Flipable {
        id: flipable

        anchors.fill: parent

        readonly property string stateFront: "front"
        readonly property string stateBack: "back"

        state: stateFront

        transform: Rotation {
            id: rotation
            origin.x: flipable.width * 0.5
            origin.y: flipable.height * 0.5
            axis { x: 0; y: 1; z: 0 }
            angle: 0
        }

        states: [
            State {
                name: flipable.stateFront
                when: !flipableRoot.flipped
                PropertyChanges { target: rotation; angle: 0 }
            },

            State {
                name: flipable.stateBack
                when: flipableRoot.flipped
                PropertyChanges { target: rotation; angle: 180 }
            }
        ]

        transitions: Transition {
            DAnimation { target: rotation; property: "angle"; duration: Style.flipDuration }
        }
    }
}
