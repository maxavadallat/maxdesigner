import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: posYEditorRoot

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    title: "Edit Y:"

    hideToSide: hideToRight

    creationWidth: 358
    creationHeight: 122

    minWidth: 358
    minHeight: 122

    enablePosOverlay: false
    enableSizeOverlay: false

    enableHideButton: false

    enableDrag: false

    resizeRightEnabled: false

    // ...
}
