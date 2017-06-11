import QtQuick 2.0

import "../system/DConstants.js" as CONSTS
import "../style"

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
            leftMargin: DStyle.defaultMargin
            topMargin: titleLabel.height + DStyle.defaultMargin * 2
            rightMargin: DStyle.defaultMargin
            bottomMargin: DStyle.defaultMargin
        }
    }
}
