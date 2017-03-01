import QtQuick 2.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DPaneBase {
    id: paneRoot

    default property alias paneContainer: paneContent.contentContainer

    readonly property int contentWidth: paneContent.width

    property bool clipPaneContnet: true

    // Content Flickable
    DFlickable {
        id: paneContent
        anchors.fill: parent
        anchors {
            leftMargin: STYLE.defaultMargin
            topMargin: titleLabel.height + STYLE.defaultMargin * 2
            rightMargin: STYLE.defaultMargin
            bottomMargin: STYLE.defaultMargin
        }

        clip: paneRoot.clipPaneContnet
    }
}

