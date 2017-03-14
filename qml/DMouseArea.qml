import QtQuick 2.0

import "style"

MouseArea {
    id: mouseAreaRoot

    property bool hidden: false

    opacity: mouseAreaRoot.hidden ? 0.0 : (mouseAreaRoot.enabled ? 1.0 : DStyle.disabledOpacity)
    Behavior on opacity { NumberAnimation { duration: DStyle.animDuration } }
    visible: opacity > 0.0

    //propagateComposedEvents: true

    //signal pressedForParent()

//    onPressed: {
//        //console.log("DMouseArea.onPressed");
//        // Emit Pressed For Parent Signal
//        //mouseAreaRoot.pressedForParent();
//    }

//    onReleased: {
//        //console.log("DMouseArea.onReleased");
//    }

    DTracer { }
}
