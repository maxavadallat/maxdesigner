import QtQuick 2.0

import "style"

DPaneBase {
    id: slotEditorRoot

    property string slotName: "slot"
    property string slotSource: ""

    title: "Slot"

    hideToSide: hideToRight

    creationWidth: 500
    creationHeight: 320

    minWidth: 500
    minHeight: 320

    enablePosOverlay: false
    enableSizeOverlay: false

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set EDitor Focus
            slotSourceEditor.setEditorFocus(true, false);
        }
    }

    // ...

    DSourceCodeEditor {
        id: slotSourceEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: slotEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: diskButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            slotEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            slotEditorRoot.rejected();
        }
    }

    DDisc {
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            slotEditorRoot.accepted();
        }
    }
}
