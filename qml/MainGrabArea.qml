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

    onPressed: {
        //console.log("#### MainGrabArea.onPressed");
    }

    onReleased: {
        //console.log("#### MaingrabArea.onReleased");

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

    // Bring To Front
    function bringToFront(item) {
        // Set Item Parent To null To Remove From Children
        item.parent = null;
        // Set Item Parent To Bring To Front
        item.parent = mainGrabAreaRoot;
    }

    // Set Drag Target
    function setDragTarget(item) {
        //console.log("#### MaingrabArea.setDragTarget");
        // Set Drag Target
        mainGrabAreaRoot.dragTarget = item;
        // Set Drag Active
        mainGrabAreaRoot.dragTarget.dragActive = true;
        // Bring To Front
        bringToFront(item);
    }

    // Clear Drag Target
    function clearDragTarget() {
        // Check Drag Target
        if (mainGrabAreaRoot.dragTarget !== undefined) {
            //console.log("#### MaingrabArea.clearDragTarget");
            // Reset Drag Active
            mainGrabAreaRoot.dragTarget.dragActive = false;
            // Clear Drag Target
            mainGrabAreaRoot.dragTarget = undefined;
        }
    }

    // ...
}
