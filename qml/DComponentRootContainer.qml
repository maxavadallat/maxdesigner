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
                // Set Update Component Info Enabled
                //componentContainer.updateComponentInfoEnabled = false;
                // Reset
                crcRoot.reset(true);
            }
        }

        onFileClosed: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onFileClosed - aFilePath: " + aFilePath);

            // Check File Path
            if (crcRoot.componentInfo && crcRoot.componentInfo.infoPath === aFilePath) {
                // Set Update Component Info Enabled
                //componentContainer.updateComponentInfoEnabled = false;
                // Reset
                crcRoot.reset(true);
            }
        }
    }

//    // New Child Component Child Container
//    property Component newComponentChildContainer: Component {
//        DComponentChildContainer {
//            width: CONSTS.componentItemWidth
//            height: CONSTS.componentItemHeight
//            rootComponentContainer: crcRoot
//            parentComponentContainer: crcRoot
//        }
//    }

    // Component Handler Factory
    property Component componentHandlerFactory: Component {
        DComponentHandler {
            width: CONSTS.componentItemWidth
            height: CONSTS.componentItemHeight
            rootContainer: crcRoot
        }
    }

    // Wait For Nodes To Close
    property bool waitForNodesToClose: false

    // Component Content Created
    property bool componentContentCreated: false

//    // Content Container Alias
//    property alias componentContainer: componentContainer

    // Current Hover Handler
    property QtObject hoverHandler: null
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

    clipContent: false

    isRootContainer: true

    focusOnShow: true

    setFocusOnResize: true

    enableSizeOverlayOnShow: true

    enableScaling: true

    borderColor: {
//        // Check If Hovering
//        if (componentContainer.dropHovering) {
//            return componentContainer.dropHoverOK ? DStyle.colorBorderHoverOK : DStyle.colorBorderHoverNOK;
//        }

//        // Check Focused Component
//        if (crcRoot.componentInfo !== null && propertiesController.focusedComponent === crcRoot.componentInfo) {
//            return DStyle.colorBorder;
//        }

//        return DStyle.colorBorderNoFocus;

        return "transparent";
    }

    borderMargins: -1

    radius: 0

    enableDragByPaneButton: true

    Component.onDestruction: {

    }

    Keys.onReleased: {
        // Switch Key
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
            // Remove Handlers
            crcRoot.removeComponentHandlers();
            // Destroy Content
            crcRoot.removeComponentQMLContent();
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
            // Create Component Content
            crcRoot.createComponentQMLContent();
            // Create Handlers
            crcRoot.createComponentHandlers(rootComponentHandler);

            // Set Focus
            crcRoot.focus = true;

//            // Set Update Component Info Enabled
//            componentContainer.updateComponentInfoEnabled = (crcRoot.componentInfo !== null);

            // Check Component Info
            if (crcRoot.componentInfo !== null) {
                // Set Node Pane Loader Active
                nodePaneLoader.active = true;
                // Set Node Pane opacity
                nodePaneLoader.opacity = 1.0;
            }

        } else {
//            // Reset Update Component Info Enabled
//            componentContainer.updateComponentInfoEnabled = false;
        }
    }

    onStateChanged: {
        // Check State
        if (crcRoot.state !== crcRoot.stateShown) {
            // Reset Update Component Info Enabled
            //componentContainer.updateComponentInfoEnabled = false;
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

    // Create Component QML Content
    function createComponentQMLContent() {
        // Check Component Info
        if (crcRoot.componentInfo !== null && !crcRoot.componentContentCreated) {
            console.log("DComponentRootContainer.createComponentQMLContent - name: " + crcRoot.componentInfo.componentName);

            // Set Component Content Created
            crcRoot.componentContentCreated = true;

            // Generate Live Code
            var cFileName = propertiesController.currentProject.generateLiveCode(crcRoot.componentInfo, true);

            // CLEAR THE FUCKING QML COMPONENT CACHE BECAUSE THEY FUCKED IT UP! BUT THIS WILL CAUSE A CRASH AT SHUTDOWN!!!
            //mainController.clearQMLComponentCache();

            // Create Component
            var component  = Qt.createComponent("file://" + cFileName);

            // Check Status
            if (component.status === Component.Ready) {
                // Create New Root Object
                rootComponentHandler.componentObject = component.createObject(rootComponentHandler.rootContentContainer);

                // Remove Live Temp File
                //propertiesController.currentProject.removeLiveTempFile(cFileName);

            } else {
                console.error("DComponentRootContainer.createComponentQMLContent - ERROR CREATING ROOT COMPONENT!! - error: " + component.errorString());
                return;
            }

            // Check New Root Object
            if (rootComponentHandler.componentObject === null) {
                console.error("DComponentRootContainer.createComponentQMLContent - ERROR CREATING ROOT OBJECT!!");
            }

            // ...
        }
    }

    // Remove Component QML Content
    function removeComponentQMLContent() {
        // Check Root Component Object
        if (rootComponentHandler.componentObject !== null) {
            // Destroy
            rootComponentHandler.componentObject.destroy();
        }

        // Reset Component Content Created
        crcRoot.componentContentCreated = false;
    }

    // Create Component Handlers
    function createComponentHandlers(parentHandler) {
        // Check Parent Handler Content Object
        if (parentHandler.componentObject !== null) {

            // Get Children Count
            var cCount = parentHandler.componentObject.children.length;

            console.log("DComponentRootContainer.createComponentHandlers - cCount: " + cCount);

            for (var i=0; i<cCount; i++) {
                // Get Child`Object
                var childObject = parentHandler.componentObject.children[i];

                //console.log("DComponentRootContainer.createComponentHandlers - childObject[" + i + "]: " + childObject);

                // Check If Has Property
                if (childObject.hasOwnProperty("__childMap")) {
                    console.log("DComponentRootContainer.createComponentHandlers - __childMap: " + childObject.__childMap);

                    // Get Child Component Info
                    var childInfo = crcRoot.componentInfo.childInfo(childObject.__childMap);

                    // Check Child Info
                    if (childInfo !== null) {
                        console.log("DComponentRootContainer.createComponentHandlers - componentName: " + childInfo.componentName);

                        // Create Handler For Child
                        var newComponentHandler = componentHandlerFactory.createObject(parentHandler.childHandlersContainer);

                        // Check New Component Handler
                        if (newComponentHandler !== null) {
                            // Set Parent Handler
                            newComponentHandler.rootContainer = crcRoot;
                            // Set Parent Handler
                            newComponentHandler.parentHandler = parentHandler;
                            // Set Index Map
                            newComponentHandler.childIndexMap = childObject.__childMap;
                            // Set Component Info
                            newComponentHandler.componentInfo = childInfo;
                            // Set Component Object
                            newComponentHandler.componentObject = childObject;

                            // Set Pos
                            newComponentHandler.x = childObject.x;
                            newComponentHandler.y = childObject.y;
                            // Set Size
                            newComponentHandler.width = childObject.width;
                            newComponentHandler.height = childObject.height;

                            // ...

                            // Create Handlers For Children
                            createComponentHandlers(newComponentHandler);

                            // ...

                        } else {

                            console.error("DComponentRootContainer.createComponentHandlers - ERROR CREATING NEW COMPONENT HANDLER!");

                        }
                    } else {

                        console.error("DComponentRootContainer.createComponentHandlers - NULL CHILD INFO FOR NEW COMPONENT HANDLER!");

                    }
                }
            }
        }
    }

    // Remove Component Handlers
    function removeComponentHandlers() {
        // Get Component Handlers Count
        var chCount = rootComponentHandler.childHandlersContainer.children.length;

        console.log("#### DComponentRootContainer.removeComponentHandlers - chCount: " + chCount);

        // Remove Component Handlers

        // ...

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

    // Root Component Handler
    DComponentHandler {
        id: rootComponentHandler
        anchors.fill: parent
        rootContainer: crcRoot
        componentInfo: crcRoot.componentInfo
        enablePosOverlay: false
        enableSizeOverlay: false
        enableDrag: false
        enableResize: false
    }

    // No Content Placeholder
    DNoContent {
        id: noContentCanvas
        anchors.fill: parent
        visible: {
            // Check Root Component Handler
            if (rootComponentHandler.componentObject !== null) {
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
