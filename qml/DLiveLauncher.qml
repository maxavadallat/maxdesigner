import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DMouseArea {
    id: liveLauncherRoot

    width: DStyle.liveLauncherWidth
    height: DStyle.liveLauncherHeight

    property bool showLiveButton: false

    hoverEnabled: true

    visible: propertiesController.focusedComponent !== null && propertiesController.focusedComponent.isRoot

    onEntered: {
        // Set Show Live Button
        liveLauncherRoot.showLiveButton = true;
    }

    onExited: {
        // Reset Show Live Button
        liveLauncherRoot.showLiveButton = false;
    }

    Item {
        id: buttonContainer
        width: DStyle.liveLauncherWidth
        height: DStyle.liveLauncherHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: liveLauncherRoot.showLiveButton ? 0 : -buttonContainer.height

        Behavior on anchors.bottomMargin { DAnimation { } }

        DDisc {
            id: liveDisc
            width: parent.width * 0.5
            height: parent.height * 0.5
            anchors.centerIn: parent

            onClicked: {
                // Launch Live Window
                mainController.launchLiveWindow();
            }
        }
    }
}
