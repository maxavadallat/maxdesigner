import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DPaneBase {
    id: crcRoot

    width: 600
    height: 400

    // Component Info
    property ComponentInfo componentInfo: null

    // Open Files Model Connection
    property Connections openFilesModelConnection: Connections {
        target: openFilesModel

        onComponentSelected: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onComponentSelected - aComponent: " + aComponent);

            // Check Component Info
            if (crcRoot.componentInfo === aComponent) {
                // Check State
                if (crcRoot.state === crcRoot.stateHidden) {
                    // Show
                    crcRoot.show();
                } else {
                    // Set Focus
                    crcRoot.focus = true;
                    // Bring To Front
                    crcRoot.parent.bringToFront(crcRoot);
                }
            }

            // ...
        }

        onFileSelected: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (crcRoot.componentInfo && crcRoot.componentInfo.infoPath === aFilePath) {
                // Check State
                if (crcRoot.state === crcRoot.stateHidden) {
                    // Show
                    crcRoot.show();
                } else {
                    // Set Focus
                    crcRoot.focus = true;
                    // Bring To Front
                    crcRoot.parent.bringToFront(crcRoot);
                }
            }

            // ...
        }

        onComponentClosed: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onComponentClosed - aComponent: " + aComponent);

            // Check Component Info
            if (crcRoot.componentInfo === aComponent) {
                // Reset
                crcRoot.reset(true);
            }
        }

        onFileClosed: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onFileClosed - aFilePath: " + aFilePath);

            // Check File Path
            if (crcRoot.componentInfo && crcRoot.componentInfo.infoPath === aFilePath) {
                // Reset
                crcRoot.reset(true);
            }
        }
    }

    // New Child Component Child Container
    property Component newComponentChildContainer: Component {
        DComponentChildContainer {
            width: CONSTS.componentItemWidth
            height: CONSTS.componentItemHeight
            rootComponentContainer: crcRoot
            parentComponentContainer: crcRoot
        }
    }

    // Wait For Nodes To Close
    property bool waitForNodesToClose: false

    // Content Container Alias
    property alias componentContainer: componentContainer

    // Current Hover Container
    property QtObject hoverContainer: null
    // Hover Pos X
    property int hoverPosX: 0
    // Hover Pos Y
    property int hoverPosY: 0

//    // Exploding Mode
//    property bool explodingMode: false

    title: "Component" + (crcRoot.componentInfo !== null ? (" - " + crcRoot.componentInfo.componentName) : "")

    hideToSide: hideToBottom

    enablePosOverlay: false
    enableSizeOverlay: false

    showTitle: false
    showBackground: false

    clipContent: true

    isRootContainer: true

    focusOnShow: true

    setFocusOnResize: true

    enableSizeOverlayOnShow: true

    enableScaling: true

    borderColor: {
        // Check If Hovering
        if (componentContainer.dropHovering) {
            return componentContainer.dropHoverOK ? DStyle.colorBorderHoverOK : DStyle.colorBorderHoverNOK;
        }

        // Check Focused Component
        if (crcRoot.componentInfo !== null && propertiesController.focusedComponent === crcRoot.componentInfo) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    borderMargins: -1

    radius: 0

    enableDragByPaneButton: true

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_N:
                // Toggle Nodes
                toggleNodePane();
            break;
        }
    }

    onFocusChanged: {
        //console.log("DComponentRootContainer.onFocusChanged - focus: " + focus);

        // Check Focus & Component Info
        if (focus) {
//            // Check Previous Scale Level
//            if (crcRoot.previousScale !== crcRoot.scale) {
//                // Set Scale Duration
//                crcRoot.scaleDuration = 100;
//                // Reset Scale
//                crcRoot.scale = crcRoot.previousScale;
//            } else {
//                // Reset Scale Duration
//                crcRoot.scaleDuration = 0;
//            }

            // Reset Scale Duration
            crcRoot.scaleDuration = 0;

            // Check Component Info
            if (crcRoot.componentInfo !== null) {
                // Set Focused Component
                propertiesController.focusedComponent = crcRoot.componentInfo;
                // Set Focused File
                openFilesModel.focusedFile = crcRoot.componentInfo ? crcRoot.componentInfo.infoPath : "";
            }
        } else {
            // Set Scale Duration
            crcRoot.scaleDuration = 100;
            // Reset Scale Level
            crcRoot.scale = 1.0;
        }
    }

    onTransitionStarted: {
        //console.log("DComponentRootContainer.onTransitionStarted - newState: " + newState);
        if (destroyOnResetFinished) {
            // Destroy Content
            componentContainer.removeChildComponents();
            componentContainer.removeRootComponent();
        }

        // Check State
        if (newState === crcRoot.stateHidden) {
            // Check Node Pane Loader Item
            if (nodePaneLoader.item) {
                // Close Node Pane
                nodePaneLoader.item.hideNodes();
            }

        } else if (newState === crcRoot.stateCreate) {
            // Check If Destroy
            //if ()
            // Check Node Pane Loader Item
            if (nodePaneLoader.item) {
                // Close Node Pane
                nodePaneLoader.item.hideNodes();
            }

            // Set Node Pane Loader Opacity
            nodePaneLoader.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        //console.log("DComponentRootContainer.onTransitionFinished - newState: " + newState);

        // Check State
        if (newState === crcRoot.stateShown) {
            // Create Main Component
            componentContainer.createRootComponent();
            // Create Children Components
            componentContainer.createChildComponents();

            // Set Focus
            crcRoot.focus = true;

            // Set Update Component Info Enabled
            componentContainer.updateComponentInfoEnabled = (crcRoot.componentInfo !== null);

            // Check Component Info
            if (crcRoot.componentInfo !== null) {
                // Set Node Pane Loader Active
                nodePaneLoader.active = true;
                // Set Node Pane opacity
                nodePaneLoader.opacity = 1.0;
            }

        } else {
            // Reset Update Component Info Enabled
            componentContainer.updateComponentInfoEnabled = false;
        }
    }

    onStateChanged: {
        // Check State
        if (crcRoot.state !== crcRoot.stateShown) {
            // Reset Update Component Info Enabled
            componentContainer.updateComponentInfoEnabled = false;
        }
    }

    // Hide/Show/Pane Button Function
    function paneButtonFunction() {
        // Check State
        if (crcRoot.state !== stateHidden) {
            // Check Node Pane State
            if (nodePaneLoader.item && nodePaneLoader.item.state === "shown") {
                // Set Wait For Nodes To Hide
                crcRoot.waitForNodesToClose = true;
                // Hide Nodes
                nodePaneLoader.item.hideNodes();
            } else {
                // Dismiss Pane
                crcRoot.dismissPane(false);
            }
        } else {
            // Reset Waiting For Nodes To Close
            crcRoot.waitForNodesToClose = false;
            // Set State
            crcRoot.show();
        }
    }

    // Toggle Node Pane
    function toggleNodePane() {
        // Check If Loaded
        if (nodePaneLoader.item) {
            // Check State
            if (nodePaneLoader.item.state === nodePaneLoader.item.stateShown) {
                // Hide Nodes
                nodePaneLoader.item.hideNodes();
            } else {
                // Show Nodes
                nodePaneLoader.item.showNodes();
            }
        }
    }

    // Zoom Area
    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: crcRoot.focus

        property real scaleMin: 1.0
        property real scaleMax: 2.0
        property real scaleSpeed: 0.05

        onWheel: {
            //console.log("DComponentRootContiainer.wheelArea.onWheel - delta: " + wheel.angleDelta.y);

            // Check Wheel Delta
            if (wheel.angleDelta.y > 2) {
                // Check Enable Scaling & Scale level
                if (crcRoot.enableScaling && crcRoot.scale < wheelArea.scaleMax) {
                    // Reset Scale Duration
                    crcRoot.scaleDuration = 0;
                    // Inc Scale Level
                    crcRoot.scale += wheelArea.scaleSpeed;
                }
            } else if (wheel.angleDelta.y < -2) {
                // Check Enable Scaling & Scale level
                if (crcRoot.enableScaling && crcRoot.scale > wheelArea.scaleMin) {
                    // Reset Scale Duration
                    crcRoot.scaleDuration = 0;
                    // Dec Scale Level
                    crcRoot.scale -= wheelArea.scaleSpeed;
                }
            }
        }
    }

    // Component Container
    DComponentContainer {
        id: componentContainer
        anchors.fill: parent
        componentInfo: crcRoot.componentInfo
        rootComponentContainer: crcRoot
        parentComponentContainer: crcRoot

        onImplicitSizeChanged: {
            console.log("DComponentRootContainer.componentContainer.onImplicitSizeChanged - [" + iWidth + "x" + iHeight + "]");

            // Resize

            // Check Width
            if (crcRoot.width !== iWidth) {
                // Set Implicit Width
                crcRoot.width = iWidth;
            }

            // Check Height
            if (crcRoot.height !== iHeight) {
                // Set Implicit Height
                crcRoot.height = iHeight;
            }

            // ...
        }
    }

    // No Content Placeholder
    DNoContent {
        id: noContentCanvas
        anchors.fill: parent
        visible: {
            // Check If Root Component Created
            if (componentContainer.rootComponentCreated && componentContainer.rootLiveQMLComponent !== null) {
                return false;
            }

            return true;
        }
    }

    // Node Pane Loader
    DLoader {
        id: nodePaneLoader

        parent: crcRoot
        anchors.right: parent.left
        anchors.verticalCenter: parent.verticalCenter

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        sourceComponent: DNodePane {
            componentInfo: crcRoot.componentInfo

            onTransitionFinished: {
                // Check If Waiting For Nodes To Close
                if (crcRoot.waitForNodesToClose) {
                    // Reset Waiting For Nodes To Close
                    crcRoot.waitForNodesToClose = false;
                    // Dismiss Pane
                    crcRoot.dismissPane(false);
                }
            }
        }

        onStatusChanged: {
            // Switch Status
            switch (status) {
                case Loader.Ready:
                    // Set Component Root Container Child Pane
                    //crcRoot.childPane = nodePaneLoader.item;
                break;

                case Loader.Error:
                    console.warn("DComponentRootContainer.nodePaneLoader.onStatusChanged - status: " + status + " - ERROR LOADING NODE PANE!");
                break;
            }
        }
    }
}
