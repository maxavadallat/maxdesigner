import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DMouseArea {
    id: assetBrowserLauncherRoot

    width: DStyle.liveLauncherWidth
    height: DStyle.liveLauncherHeight

    property bool showLauncherButton: false

    hoverEnabled: true

    //visible: propertiesController.focusedComponent !== null && propertiesController.focusedComponent.isRoot
    visible: mainController.currentProject !== null && DSystemModel.currentTextInput !== null

    onEntered: {
        // Set Show Live Button
        assetBrowserLauncherRoot.showLauncherButton = true;
    }

    onExited: {
        // Reset Show Live Button
        assetBrowserLauncherRoot.showLauncherButton = false;
    }

    Item {
        id: buttonContainer
        width: DStyle.liveLauncherWidth
        height: DStyle.liveLauncherHeight

        anchors.bottom: parent.bottom
        anchors.bottomMargin: assetBrowserLauncherRoot.showLauncherButton ? 0 : -buttonContainer.height

        Behavior on anchors.bottomMargin { DAnimation { } }

        DDisc {
            id: liveDisc
            width: parent.width * 0.5
            height: parent.height * 0.5
            anchors.centerIn: parent

            onClicked: {
                // Launch Asset Browser Window
                mainController.launchAssetBrowser();
            }
        }

        DText {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: DStyle.defaultMargin
            text: "Assets"
        }
    }
}
