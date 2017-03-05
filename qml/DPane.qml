import QtQuick 2.0

import "Constants.js" as CONSTS
import "style"

DPaneBase {
    id: paneRoot

    default property alias paneContainer: paneContent.contentContainer

    readonly property int contentWidth: paneContent.width

    property alias clipPaneContnet: paneContent.clip

    // Content Flickable
    DFlickable {
        id: paneContent
        anchors.fill: parent
        anchors {
            leftMargin: Style.defaultMargin
            topMargin: titleLabel.height + Style.defaultMargin * 2
            rightMargin: Style.defaultMargin
            bottomMargin: Style.defaultMargin
        }

        clip: true
    }
}
