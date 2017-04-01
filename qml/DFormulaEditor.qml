import QtQuick 2.0

import "style"

DPaneBase {
    id: formulaEditorRoot

    property string propertyName: "name"

    title: propertyName + " - Formula"

    hideToSide: hideToRight

    creationWidth: DStyle.formulaEdiorWidth
    creationHeight: DStyle.formulaEditorHeight

    minWidth: DStyle.formulaEdiorWidth
    minHeight: DStyle.formulaEditorHeight

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

    DText {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: DStyle.defaultMargin
        text: formulaEditorRoot.title
        opacity: formulaEditorRoot.state === formulaEditorRoot.stateShown ? 1.0 : 0.0
    }

    DSourceCodeEditor {
        id: formulaEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: label.height + DStyle.defaultMargin * 2
            rightMargin: diskButton.width + DStyle.defaultMargin * 4
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
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            formulaEditorRoot.accepted();
        }
    }
}
