import QtQuick 2.0

import "style"

DPaneBase {
    id: functionEditorRoot

    property string functionName: "function"
    property var functionParameters: []
    property string functionSource: ""

    title: "Function"

    hideToSide: hideToRight

    creationWidth: 500
    creationHeight: 360

    minWidth: 500
    minHeight: 360

    enablePosOverlay: false
    enableSizeOverlay: false

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set EDitor Focus
            funtionSourceEditor.setEditorFocus(true, false);
        }
    }

    // ...

    DSourceCodeEditor {
        id: funtionSourceEditor
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: functionEditorRoot.titleHeight + DStyle.defaultMargin * 2
            rightMargin: diskButton.width + DStyle.defaultMargin * 4
            bottomMargin: DStyle.defaultMargin
        }

        onSourceEditorActivated: {
            // Bring To Front
            functionEditorRoot.bringToFront();
        }

        onEscapeClicked: {
            // Reject
            functionEditorRoot.rejected();
        }
    }

    DDisc {
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            functionEditorRoot.accepted();
        }
    }
}
