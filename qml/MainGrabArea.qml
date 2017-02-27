import QtQuick 2.0

MouseArea {
    id: mainGrabAreaRoot

    anchors.fill: parent

    property var dragTarget: undefined

    opacity: 1.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    drag.target: mainGrabAreaRoot.dragTarget

    drag.axis: Drag.XandYAxis
    drag.minimumX: 0
    drag.maximumX: width
    drag.minimumY: 0
    drag.maximumY: height

    drag.threshold: 10

    drag.filterChildren: true

    acceptedButtons: { Qt.LeftButton /*| Qt.RightButton*/ }

//    signal rightButtonClicked(var posX, var posY)

    onReleased: {
        //console.log("MaingrabArea.onReleased");
        if (mouse.button === Qt.LeftButton) {
            // Clear Drag Target
            clearDragTarget();
        }
    }

//    onClicked: {
//        if (mouse.button === Qt.RightButton) {
//            mainGrabAreaRoot.rightButtonClicked(mouse.x, mouse.y);
//        }
//    }

    // Set Drag Target
    function setDragTarget(item) {
        // Set Drag Target
        mainGrabAreaRoot.dragTarget = item;
        // Set Item Parent To null To Remove From Children
        item.parent = null;
        // Set Item Parent To Bring To Front
        item.parent = mainGrabAreaRoot;
    }

    // Clear Drag Target
    function clearDragTarget() {
        // Check Drag Target
        if (mainGrabAreaRoot.dragTarget !== undefined) {
            // Clear Drag Target
            mainGrabAreaRoot.dragTarget = undefined;
        }
    }

    // ...
}
