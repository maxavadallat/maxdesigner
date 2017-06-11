import QtQuick 2.0

import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../controls"

DPaneBase {
    id: sourceContainerRoot

    property string filePath: ""

    property Connections openfilesConnection: Connections {
        target: openFilesModel

        onFileSelected: {
            console.log("DSourceContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Bring To Front
                parent.bringToFront(sourceContainerRoot);
            }
        }

        onFileClosed: {
            console.log("DSourceContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Reset
                sourceContainerRoot.reset(true);
            }
        }
    }

    title: "Source"

    enablePosOverlay: false
    enableSizeOverlay: false

    enableScaling: false

    hideToSide: hideToBottom

    showTitle: true
    showBackground: false

    clipContent: true

    isRootContainer: true

    focusOnShow: true

    titleLabel.opacity: 1.0

    DSourceCodeEditor {
        id: sourceCodeEditor
        anchors.fill: parent
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.leftMargin: DStyle.defaultMargin
        anchors.rightMargin: DStyle.defaultMargin
        anchors.bottomMargin: DStyle.defaultMargin
    }
}
