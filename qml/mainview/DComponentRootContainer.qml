import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DPaneBase {
    id: crcRoot

    width: 600
    height: 400

    // Component Info
    property ComponentInfo componentInfo: null
    // Component Yype
    property string componentType: componentInfo ? componentInfo.componentType : ""
    // Component Category
    property string componentCategory: componentInfo ? componentInfo.componentCategory : ""

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

    // Current Hover Handler
    property QtObject hoverHandler: null
    // Hover Pos X
    property int hoverPosX: 0
    // Hover Pos Y
    property int hoverPosY: 0

    // Drag Source
    property ComponentInfo dragSource: null
    // Drag Key
    property string dragKey: ""

    // Root Component Handler
    property alias rootComponentHandler: rootComponentHandler

    // Show Animations Manager
    property bool showAnimManager: false
    // Animations Manager Visible
    property bool animManagerPaneVisible: animPaneLoader.item !== null && animPaneLoader.item.state === animPaneLoader.item.stateShown

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

    // Focused Child
    property ComponentInfo focusedChild: null

    // Properties Controller Connection
    property Connections propertiesControllerConnections: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Check Focused Component
            if (propertiesController.focusedComponent !== null) {
                // Check Category
                if (propertiesController.focusedComponent.componentCategory !== "Animation" &&
                    propertiesController.focusedComponent.componentCategory !== "Behavior") {
                    // Set Focused Child
                    crcRoot.focusedChild = propertiesController.focusedComponent;
                }
            }
        }
    }

    title: "Component" + (crcRoot.componentInfo !== null ? (" - " + crcRoot.componentInfo.componentName) : "")

    hideToSide: hideToBottom

    enablePosOverlay: false
    enableSizeOverlay: false

    enableResize: {
        // Check Component Info
        if (crcRoot.componentInfo !== null && crcRoot.componentInfo.componentCategory === "Animation") {
            return false;
        }

        return true;
    }

    showTitle: false
    showBackground: false

    clipContent: false

    isRootContainer: true

    focusOnShow: true

    setFocusOnResize: true

    enableSizeOverlayOnShow: false

    enableScaling: true

    radius: 0

    enableDragByPaneButton: true

    signal componentWidthChanged(var newWidth)
    signal componentHeightChanged(var newHeight)
    signal rebuildContent()

    Keys.onReleased: {
        // Switch Key
        switch (event.key) {
            case Qt.Key_N:
                // Toggle Nodes
                toggleNodePane();
            break;

            case Qt.Key_A:
                // Check Focused Child
                if (crcRoot.focusedChild !== null && crcRoot.focusedChild.animsCount > 0) {
                    // Toggle Animations
                    toggleAnimationsPane();
                }
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

    onStateChanged: {
        //console.log("DComponentRootContainer.onStateChanged - state: " + crcRoot.state);

        // Check State
        if (crcRoot.state !== crcRoot.stateShown && crcRoot.state !== crcRoot.stateHidden) {
            // Reset Update Compoennt Info Enabled
            rootComponentHandler.disableComponentInfoUpdates();
        }
    }

    onTransitionStarted: {
        //console.log("DComponentRootContainer.onTransitionStarted - newState: " + newState);

        // Check State
        if (newState === crcRoot.stateHidden) {
            // Reset Root Container Border Color
            crcRoot.borderColor = DStyle.colorBorderNoFocus;
            // Set Border
            // Check Node Pane Loader Item
            if (nodePaneLoader.item) {
                // Close Node Pane
                nodePaneLoader.item.hideNodes();
            }

        } else if (newState === crcRoot.stateCreate) {
            // Hide Anim Manager
            crcRoot.showAnimManager = false;

            // Check Destroy
            if (destroyOnResetFinished) {
                // Remove Handlers
                crcRoot.removeComponentHandlers();
                // Destroy Content
                crcRoot.removeComponentQMLContent();
            }

            // Reset Root Container Border Color
            crcRoot.borderColor = DStyle.colorBorderNoFocus;

            // Check Node Pane Loader Item
            if (nodePaneLoader.item) {
                // Close Node Pane
                nodePaneLoader.item.hideNodes();
            }

            // Check Anim Pane Loaded
            if (animPaneLoader.item) {
                // Close
                animPaneLoader.item.hideNodes();
            }

            // Set Node Pane Loader Opacity
            nodePaneLoader.opacity = 0.0;
            // Set ANim Pane Loader Opacity
            animPaneLoader.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        //console.log("DComponentRootContainer.onTransitionFinished - newState: " + newState);

        // Check State
        if (newState === crcRoot.stateShown) {
            // Set Root Container Border Color
            crcRoot.borderColor = "transparent";
            // Set Root Component Handler Visibility
            rootComponentHandler.visible = true;
            // Create Component Content
            crcRoot.createComponentQMLContent();
            // Create Handlers
            crcRoot.createComponentHandlers(rootComponentHandler);
            // Set Focus
            crcRoot.focus = true;

            // Set Update Component Info Enabled
            crcRoot.rootComponentHandler.updateComponentInfoEnabled = (crcRoot.componentInfo !== null);

            // Check Component Info
            if (crcRoot.componentInfo !== null) {
                // Check Type
                if (crcRoot.componentInfo.componentType !== "DataSource" && crcRoot.componentInfo.componentCategory !== "Animation") {
                    // Set Node Pane Loader Active
                    nodePaneLoader.active = true;
                    // Set Node Pane opacity
                    nodePaneLoader.opacity = 1.0;

                    // Set Anim Pane Loaded Active
                    animPaneLoader.active = true;
                    // Set Anim Pane Loader Opacity
                    animPaneLoader.opacity = 1.0;
                }
            }

            // Show Anim Manager
            crcRoot.showAnimManager = true;

        } else {
//            // Reset Update Component Info Enabled
//            componentContainer.updateComponentInfoEnabled = false;
        }
    }

    onWidthChanged: {
        // Check Component Object
        if (rootComponentHandler.componentObject === null || crcRoot.componentType === "DataSource") {
            // Check State
            if (crcRoot.state === crcRoot.stateShown) {
                //console.warn("DComponentRootContainer.onWidthChanged - NO COMPONENT OBJECT!!");
                // Just Set Width
                rootComponentHandler.width = crcRoot.width;
            }

            return;
        }

        // Check Component Category
        if (crcRoot.componentCategory !== "" && crcRoot.componentCategory !== "NonVisual" && crcRoot.componentCategory !== "Animation") {
            // Check Width
            if (rootComponentHandler.componentObject.width !== crcRoot.width) {
                // Set Width
                rootComponentHandler.componentObject.width = crcRoot.width;
            }
        }
    }

    onHeightChanged: {
        // Check Component Object
        if (rootComponentHandler.componentObject === null || crcRoot.componentType === "DataSource") {
            // Check State
            if (crcRoot.state === crcRoot.stateShown) {
                //console.warn("DComponentRootContainer.onHeightChanged - NO COMPONENT OBJECT!!");
                // Just Set Height
                rootComponentHandler.height = crcRoot.height;
            }

            return;
        }

        // Check Component Category
        if (crcRoot.componentCategory !== "" && crcRoot.componentCategory !== "NonVisual" && crcRoot.componentCategory !== "Animation") {
            // Check Height
            if (rootComponentHandler.componentObject.height !== crcRoot.height) {
                // Set Height
                rootComponentHandler.componentObject.height = crcRoot.height;
            }
        }
    }

    onComponentWidthChanged: updateContainerWidth(newWidth);
    onComponentHeightChanged: updateContainerHeight(newHeight);

    onRebuildContent: {
        console.log("DComponentRootContainer.onRebuildContent");

        // Remove Component Handlers
        removeComponentHandlers();

        // Remove Component QML Content
        removeComponentQMLContent();

        // Trim Component Cache
        mainController.trimQMLComponentCache();

        // Create Component QML Content
        createComponentQMLContent();

        // Create Component Handlers
        createComponentHandlers(rootComponentHandler);

        // Set Update Component Info Enabled
        rootComponentHandler.updateComponentInfoEnabled = (crcRoot.componentInfo !== null);

        // ...
    }

    onFocusedChildChanged: {
        // Hide Animation Manager Pane
        hideAnimManagerPane();
    }

    onComponentInfoChanged: {
        // Check Component Info
        if (crcRoot.componentInfo) {

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

    // Toggle Animations Pane
    function toggleAnimationsPane() {
        // Check Animation Pane Loader
        if (animPaneLoader.item) {
            // Check State
            if (animPaneLoader.item.state === animPaneLoader.item.stateShown) {
                // Hide Animations
                animPaneLoader.item.hideNodes();
            } else {
                // Show Animations
                animPaneLoader.item.showNodes();
            }
        }
    }

    // Create Component QML Content
    function createComponentQMLContent() {
        // Check If Component Content Created
        if (!crcRoot.componentContentCreated) {
            // Set Compoennt Content Created
            crcRoot.componentContentCreated = true;

            // Check Component Category
            if (crcRoot.componentCategory !== "NonVisual" && crcRoot.componentCategory !== "Animation") {
                // Set Root Handler Width
                rootComponentHandler.width = crcRoot.componentInfo.width;
                // Set Root Component Handler Height
                rootComponentHandler.height = crcRoot.componentInfo.height;
            }

            // Create New Root Object
            rootComponentHandler.componentObject = rootComponentHandler.createComponentObject(crcRoot.componentInfo, rootComponentHandler.rootContentContainer, true);

            // Check New Root Object
            if (rootComponentHandler.componentObject === null) {
                console.error("DComponentRootContainer.createComponentQMLContent - ERROR CREATING ROOT OBJECT!!");
                // Set Error State
                rootComponentHandler.chError = true;
                return;
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

        // Reset Error State
        rootComponentHandler.chError = false;
        // Reset Component Content Created
        crcRoot.componentContentCreated = false;
    }

    // Create Component Handlers
    function createComponentHandlers(parentHandler) {
        // Check Parent Handler Content Object
        if (parentHandler.componentObject !== null) {

            // Get Children Count
            var cCount = parentHandler.componentObject.children !== undefined ? parentHandler.componentObject.children.length : 0;

            //console.log("DComponentRootContainer.createComponentHandlers - cCount: " + cCount);

            for (var i=0; i<cCount; i++) {
                // Get Child`Object
                var childObject = parentHandler.componentObject.children[i];

                //console.log("DComponentRootContainer.createComponentHandlers - childObject[" + i + "]: " + childObject);

                // Check If Has Property
                if (childObject.hasOwnProperty("__childMap")) {
                    //console.log("DComponentRootContainer.createComponentHandlers - __childMap: " + childObject.__childMap);

                    // Get Child Component Info
                    var childInfo = crcRoot.componentInfo.childInfo(childObject.__childMap);

                    // Check Child Info
                    if (childInfo !== null) {
                        //console.log("DComponentRootContainer.createComponentHandlers - childInfo: " + childInfo.componentPath);

                        // Create Handler For Child
                        var newComponentHandler = componentHandlerFactory.createObject(parentHandler.childHandlersContainer);

                        // Check New Component Handler
                        if (newComponentHandler !== null) {
                            // Set Parent Handler
                            //newComponentHandler.rootContainer = crcRoot;
                            // Set Parent Handler
                            newComponentHandler.parentHandler = parentHandler;
                            // Set Index Map
                            newComponentHandler.childIndexMap = childObject.__childMap;
                            // Set Component Info
                            newComponentHandler.componentInfo = childInfo;
                            // Set Component Object
                            newComponentHandler.componentObject = childObject;

                            // Set Pos X
                            newComponentHandler.x = childObject.x;
                            // Set Pos Y
                            newComponentHandler.y = childObject.y;

                            // Set Width
                            newComponentHandler.width = childObject.width;
                            // Set Height
                            newComponentHandler.height = childObject.height;

                            // Check Component Info If Using Implicit Width
                            if (childInfo.useIWidth) {
                                // Check Component Info Implicit Width
                                if (childInfo.implicitWidth !== childObject.width) {
                                    // Set Implicit Width
                                    childInfo.implicitWidth = childObject.width;
                                }
                            }

                            // Check Component Info If Using Implicit Height
                            if (childInfo.useIHeight) {
                                // Check Component Info Implicit Height
                                if (childInfo.implicitHeight !== childObject.height) {
                                    // Set Implicit Height
                                    childInfo.implicitHeight = childObject.height;
                                }
                            }

                            // ...

                            // Create Handlers For Children
                            createComponentHandlers(newComponentHandler);

                            // Set Update Component Info Enabled
                            newComponentHandler.updateComponentInfoEnabled = true;

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
        // Reset Update Component Info Enabled
        rootComponentHandler.updateComponentInfoEnabled = false;

        // Get Component Handlers Count
        var chCount = rootComponentHandler.childHandlersContainer.children.length;

        //console.log("DComponentRootContainer.removeComponentHandlers - chCount: " + chCount);

        // Remove Component Handlers
        for (var i=chCount-1; i>=0; i--) {
            // Reset Update Component Info Enabled
            rootComponentHandler.childHandlersContainer.children[i].updateComponentInfoEnabled = false;
            // Destroy Children
            rootComponentHandler.childHandlersContainer.children[i].destroy();
        }

        // ...

    }

    // Show Anim Manager Pane
    function showAnimManagerPane() {
        // Check Anim Pane Loader Item
        if (animPaneLoader.item) {
            // Show Pane/Nodes
            animPaneLoader.item.showNodes();
        }
    }

    // Hide Anim Manager Pane
    function hideAnimManagerPane() {
        // Check Anim Pane Loader Item
        if (animPaneLoader.item) {
            // Hide Pane/Nodes
            animPaneLoader.item.hideNodes();
        }

        // Set Focused Component
        propertiesController.focusedComponent = crcRoot.focusedChild;
    }

    // Update Container Width
    function updateContainerWidth(newWidth) {
        // Check Width & State
        if (crcRoot.width !== newWidth && crcRoot.state === crcRoot.stateShown) {
            console.log("DComponentRootContainer.updateContainerWidth - newWidth: " + newWidth);
            // Get Center Pos X
            var centerPosX = crcRoot.x + crcRoot.width * 0.5;
            // Set New Pos X
            crcRoot.x = centerPosX - newWidth * 0.5;
            // Set New Width
            crcRoot.width = newWidth;
        }
    }

    // Update Container Height
    function updateContainerHeight(newHeight) {
        // Check Height & State
        if (crcRoot.height !== newHeight && crcRoot.state === crcRoot.stateShown) {
            console.log("DComponentRootContainer.updateContainerHeight - newHeight: " + newHeight);
            // Get Center Pos Y
            var centerPosY = crcRoot.y + crcRoot.height * 0.5;
            // Set New Pos Y
            crcRoot.y = centerPosY - newHeight * 0.5;
            // Set New Height
            crcRoot.height = newHeight;
        }
    }

//    Rectangle {
//        anchors.fill: parent
//        color: "#22FF0000"
//    }

    // Zoom Area
    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: rootComponentHandler.focus

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
        width: crcRoot.width
        height: crcRoot.height
        rootContainer: crcRoot
        componentInfo: crcRoot.componentInfo
        enablePosOverlay: false
        enableSizeOverlay: false
        enableDrag: false
        enableResize: false
        enablePanByKeys: false
        borderMargins: -1
        borderVisible: true
        visible: false
    }

    // No Content Placeholder
    DNoContent {
        id: noContentCanvas
        anchors.fill: parent
        opacity: 0.0
        //opacity: rootComponentHandler.componentObject !== null ? 0.0 : 0.2
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

    // Anim Pane/Manager Loader
    DLoader {
        id: animPaneLoader

        parent: crcRoot

        anchors.left: parent.right
        anchors.verticalCenter: parent.verticalCenter

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        sourceComponent: DAnimationPane {
            componentInfo: crcRoot.focusedChild

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
                    console.warn("DComponentRootContainer.animPaneLoader.onStatusChanged - status: " + status + " - ERROR LOADING NODE PANE!");
                break;
            }
        }
    }
}
