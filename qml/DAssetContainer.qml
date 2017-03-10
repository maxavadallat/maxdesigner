import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "style"

DPaneBase {
    id: sourceContainerRoot

    property string filePath: ""

    enablePosOverlay: false
    enableSizeOverlay: false

    hideToSide: hideToBottom

    showTitle: false
    showBackground: false

    clipContent: true

    rootContainer: true

    focusOnShow: true

    property Connections openfilesConnection: Connections {
        target: openFilesModel

        onFileSelected: {
            console.log("DAssetContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Bring To Front
                parent.bringToFront(sourceContainerRoot);
            }
        }

        onFileClosed: {
            console.log("DAssetContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Reset
                sourceContainerRoot.reset(true);
            }
        }
    }

    // ...

}
