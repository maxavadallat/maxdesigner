import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/controls"

DPaneBase {
    id: sourceContainerRoot

    property string filePath: ""

    enablePosOverlay: false
    enableSizeOverlay: false

    hideToSide: hideToBottom

    showTitle: false
    showBackground: false

    clipContent: true

    isRootContainer: true

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
