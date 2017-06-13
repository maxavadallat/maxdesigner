import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"

DSection {
    id: transitionsSectionRoot
    width: 300
    title: "Transitions"
    minHeight: transitionsContainer.height + addTransitionButton.height

    state: stateClosed

    // Transitions
    Item {
        id: transitionsContainer
        width: transitionsSectionRoot.width
        height: 0

        // ...
    }

    Item {
        width: transitionsSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addTransitionButton
        width: transitionsSectionRoot.width
        text: "Add Transition"
        enabled: transitionEditor.state === transitionEditor.stateCreate

        onClicked: {
            // Emit New Transition Launch
            propertiesPaneRoot.newTransitionLaunch();
        }
    }
}