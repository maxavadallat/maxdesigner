import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQml.Models 2.2

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: demoContainerRoot

    width: 1200
    height: 800

    clip: true

    enablePosOverlay: false
    enableSizeOverlay: false

    drag.filterChildren: false

    minWidth: 1200
    minHeight: 800

    property int contentWidth: 400

    // Bring To Front
    function bringToFront(item) {
        // Check Item
        if (item === null || item === undefined) {
            return;
        }

        // Get Item Position
        var posX = item.x;
        var posY = item.y;

        // Set Item Parent To null To Remove From Children
        item.parent = null;
        // Set Item Parent To Bring To Front
        item.parent = demoContainerRoot;

        // Set Item Position
        item.x = posX;
        item.y = posY;
    }

    Component.onCompleted: {

    }

}
