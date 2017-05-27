import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: cccRoot

    // Root Component Container
    property QtObject rootComponentContainer: null
    // Parent Component Container
    property QtObject parentComponentContainer: null
    // Component Info
    property ComponentInfo componentInfo: null

    // Component Container Alias
    property alias componentContainer: componentContainer

    property bool parentDrop: false

    backgroundColor: {
        // Check If Borders Visible
        if (!settingsController.borderVisible) {
            return "transparent";
        }

        return DStyle.colorBG;
    }

    borderColor: {
        // Check If Drop Hovering
        if (componentContainer.dropHovering) {
            return componentContainer.dropHoverOK ? DStyle.colorBorderHoverOK : DStyle.colorBorderHoverNOK;
        }

        // Check If Selected
        if (cccRoot.selected) {
            return DStyle.colorBorderSelected;
        }

        // Check If Borders Visible
        if (!settingsController.borderVisible) {
            return "transparent";
        }

        // Check Component Info
        if (cccRoot.componentInfo !== null && cccRoot.componentInfo === propertiesController.focusedComponent) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    borderMargins: -1

    radius: 0

    enablePosOverlay:  true
    enableSizeOverlay: true
    setFocusOnResize: true
    enablePanByKeys: true

    resizeLeftEnabled: true
    resizeRightEnabled: true
    resizeTopEnabled: true
    resizeBottomEnabled: true

    drag.minimumX: -cccRoot.width
    drag.maximumX: parent ? parent.width : 0
    drag.minimumY: -cccRoot.height
    drag.maximumY: parent ? parent.height : 0

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_Backspace:
            case Qt.Key_Delete:
                // Check Parent Container
                if (cccRoot.componentInfo !== null) {
                    // Remove Child Component
                    cccRoot.componentContainer.removeChildComponent(cccRoot, true);
                } else {
                    // Destroy
                    cccRoot.destroy();
                }
            break;

            case Qt.Key_N:
                // Check Root Component Container
                if (cccRoot.rootComponentContainer !== null) {
                    // Toggle Nodes
                    cccRoot.rootComponentContainer.toggleNodePane();
                }
            break;

            case Qt.Key_Escape:
                // Check Compontn Info Parent
                if (cccRoot.componentInfo !== null && cccRoot.componentInfo.componentParent !== null) {
                    // Set Focused Component
                    propertiesController.focusedComponent = cccRoot.componentInfo.componentParent;
                }

            break;

            default:
                //console.log("DComponentChildContainer.Keys.onReleased - key: " + event.key);
            break;
        }
    }

    onFocusChanged: {
        //console.log("DComponentChildContainer.onFocusChanged - focus: " + focus);
        // Check Focus
        if (cccRoot.focus) {
            // Set Focused Componrnt
            propertiesController.focusedComponent = cccRoot.componentInfo;
        }
    }

    onXChanged: componentContainer.updatePosX(cccRoot.x)

    onYChanged: componentContainer.updatePosY(cccRoot.y)

    // Component Container
    DComponentContainer {
        id: componentContainer
        anchors.fill: parent
        componentInfo: cccRoot.componentInfo
        rootComponentContainer: cccRoot.rootComponentContainer
        parentComponentContainer: cccRoot

        onComponentInfoChanged: {
            //console.log("DComponentChildContainer.componentContainer.onComponentInfoChanged - path: " + (componentContainer.componentInfo !== null ? componentContainer.componentInfo.componentPath : "NULL" ));

            // Check Component Info
            if (componentContainer.componentInfo !== null) {
                // Create Content
                componentContainer.createContent();
            } else {
                // Remove Content
                componentContainer.removeContent();
            }

            // ...

        }

        onImplicitSizeChanged: {
            console.log("DComponentChildContainer.componentContainer.onImplicitSizeChanged - [" + iWidth + "x" + iHeight + "]");

            // Resize

            // Check Width
            if (cccRoot.width !== iWidth) {
                // Set Implicit Width
                cccRoot.width = iWidth;
            }

            // Check Height
            if (cccRoot.height !== iHeight) {
                // Set Implicit Height
                cccRoot.height = iHeight;
            }

            // ...
        }
    }
}
