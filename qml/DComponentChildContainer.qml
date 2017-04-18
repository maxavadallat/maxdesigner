import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: cccRoot

    property bool grabbed: false

    property ComponentInfo componentInfo: null

    property Connections componentInfoConnections: Connections {
        target: componentInfo

        // ...
    }

    property bool selected: false

    backgroundColor: Qt.hsla(Math.random(), 0.5, 0.4, 0.2)

    borderColor: {
        if (cccRoot.selected) {
            return DStyle.colorBorderSelected;
        }

        if (cccRoot.componentInfo === propertiesController.focusedComponent) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    radius: 0

    enablePosOverlay: true
    enableSizeOverlay: true
    setFocusOnResize: true

    Component.onDestruction: {
        // Reset Component Info
        cccRoot.componentInfo = null;
    }

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_Backspace:
            case Qt.Key_Delete:

                // Check Parent Container
                if (cccRoot.parentContainer && cccRoot.parentContainer.removeChildComponent !== undefined) {
                    // Remove Child Component
                    cccRoot.parentContainer.removeChildComponent(cccRoot);
                } else {
                    // Destroy
                    cccRoot.destroy();
                }
            break;
        }
    }

    onPressed: {
        console.log("DComponentChildContainer.onPressed");
        // Set Last Mouse Press Owner
        DSystemModel.lastMousePressOwner = "cccRoot";

        // ...
    }

    onReleased: {
        console.log("DComponentChildContainer.onReleased");

        // Check Last Mouse Press Owner
        if (DSystemModel.lastMousePressOwner === "cccRoot") {
            // Reset Last Mouse Press Owner
            DSystemModel.lastMousePressOwner = "";
            // Set Focus
            cccRoot.focus = true;
        }
    }

    onFocusChanged: {
        console.log("DComponentChildContainer.onFocusChanged - focus: " + focus);

        // Check Focus
        if (cccRoot.focus) {
            // Set Focused Componrnt
            propertiesController.focusedComponent = cccRoot.componentInfo;
        }

        // ...
    }

    Loader {
        id: componentLoader
        anchors.fill: parent
        asynchronous: true
        active: false
    }

    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: 0.05
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }
}
