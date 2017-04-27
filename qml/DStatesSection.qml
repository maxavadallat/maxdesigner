import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: statesSectionRoot
    width: 300
    title: "States"
    minHeight: statesContainer.height + addStateButton.height

    state: stateClosed

    // States
    Item {
        id: statesContainer
        width: statesSectionRoot.width
        height: 0

        // ...
    }

    Item {
        width: statesSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addStateButton
        width: statesSectionRoot.width
        text: "Add State"
        enabled: stateEditor.state === stateEditor.stateCreate

        onClicked: {
            // Emit New State Launch
            propertiesPaneRoot.newStateLaunch();
        }
    }
}
