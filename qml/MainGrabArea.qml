import QtQuick 2.0

MouseArea {
    id: mainGrabAreaRoot

    anchors.fill: parent

    property var dragTarget: undefined

    drag.target: mainGrabAreaRoot.dragTarget

    drag.axis: Drag.XandYAxis
    drag.minimumX: 0
    drag.maximumX: width
    drag.minimumY: 0
    drag.maximumY: height

    drag.threshold: 0

    drag.filterChildren: true

    onReleased: {
        //console.log("MaingrabArea.onReleased");
        // Clear Drag Target
        clearDragTarget();
    }

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
