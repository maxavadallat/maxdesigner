import QtQuick 2.0

import "../animations"

MouseArea {
    id: mainGrabAreaRoot

    opacity: 1.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

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
        item.parent = mainGrabAreaRoot;

        // Set Item Position
        item.x = posX;
        item.y = posY;
    }

    // ...
}
