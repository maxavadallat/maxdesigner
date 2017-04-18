import QtQuick 2.0

import "style"

DPaneBase {
    id: importsEditorRoot

    property var componentImports: []

    title: "Imports"

    hideToSide: hideToRight

    creationWidth: 358
    creationHeight: 118

    minWidth: 358
    minHeight: 118

    enablePosOverlay: false
    enableSizeOverlay: false

    signal newImport()
    signal editImport()

    // ...


    DDisc {
        id: diskButton
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            importsEditorRoot.accepted();
        }
    }

    // ...

    DButton {
        width: parent.width - 16 - diskButton.width - DStyle.defaultMargin * 3
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        text: "Add Import"

        onClicked: {
            importsEditorRoot.newImport();
        }
    }
}
