pragma Singleton

import QtQuick 2.0

import "qrc:/qml/controls"

QtObject {
    id: systemmModelRoot

    property bool systemBusy: false

    // Current Text Input
    property QtObject currentTextInput: null

    property Connections mainControllerConnections: Connections {
        target: mainController

        onAssetSelected: {
            console.log("DSystemModel.mainControllerConnections.onAssetSelected - aAssetPath: " + aAssetPath);

            // ...

            // Check Current Text Input
            if (systemmModelRoot.currentTextInput !== null && systemmModelRoot.currentTextInput.insertText !== undefined) {
                // Set Text
                currentTextInput.insertText(aAssetPath);
                // Check Set Editor Focus
                if (currentTextInput.setEditorFocus !== undefined) {
                    // Set Focus
                    currentTextInput.setEditorFocus(true, false);
                }
                // Reset Current Text Input
                systemmModelRoot.currentTextInput = null;
            }
        }
    }

    signal cancelMarkForDeletion()

    // Currently Selected Root Container
    property QtObject currentRootContainer: null

    // ...

}
