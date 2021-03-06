import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DMouseArea {
    id: liveLauncherRoot

    width: DStyle.liveLauncherWidth
    height: DStyle.liveLauncherHeight

    property bool showLauncherButton: false

    hoverEnabled: true

    visible: propertiesController.focusedComponent !== null && propertiesController.focusedComponent.isRoot

    onEntered: {
        // Set Show Live Button
        liveLauncherRoot.showLauncherButton = true;
    }

    onExited: {
        // Reset Show Live Button
        liveLauncherRoot.showLauncherButton = false;
    }

    Item {
        id: buttonContainer
        width: DStyle.liveLauncherWidth
        height: DStyle.liveLauncherHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: liveLauncherRoot.showLauncherButton ? 0 : -buttonContainer.height

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

        DText {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: DStyle.defaultMargin
            text: "Live"
        }
    }
}
