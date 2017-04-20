import QtQuick 2.0

import "style"

DPaneBase {
    id: formulaEditorRoot

    property string propertyName: "property"

    title: propertyName + ":"

    hideToSide: hideToRight

    creationWidth: 358
    creationHeight: 118

    minWidth: 358
    minHeight: 118

    enablePosOverlay: false
    enableSizeOverlay: false

    //borderColor: formulaEditor.editorFocus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

    onTransitionStarted: {
        if (newState === stateHidden) {
            // Reset Focus
            formulaEditor.setEditorFocus(false);
        }
    }

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Editor Focus
            formulaEditor.setEditorFocus(true, true);
        }
    }

    DSourceCodeEditor {
        id: formulaEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: formulaEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: discButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            formulaEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            formulaEditorRoot.rejected();
        }
    }

    DDisc {
        id: discButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            formulaEditorRoot.accepted();
        }
    }
}
