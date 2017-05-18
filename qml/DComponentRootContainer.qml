import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DPaneBase {
    id: componentRootContainerRoot

    width: 600
    height: 400

    property bool explodingMode: false

    property ComponentInfo componentInfo: null

    property bool updateComponentInfoEnabled: false

    property bool rootComponentCreated: false
    property bool childComponentsCreated: false

    property bool dropHovering: false

    // New Child Component
    property Component newChildComponent: Component {
        DComponentChildContainer {
            width: CONSTS.componentItemWidth
            height: CONSTS.componentItemHeight
            rootComponent: componentRootContainerRoot
        }
    }

    // Properties Controller Connection
    property Connections propertiesControllerConnection: Connections {
        target: propertiesController

    }

    // Open Files Model Connection
    property Connections openFilesModelConnection: Connections {
        target: openFilesModel

        onComponentSelected: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onComponentSelected - aComponent: " + aComponent);

            // Check Component Info
            if (componentRootContainerRoot.componentInfo === aComponent) {
                // Check State
                if (componentRootContainerRoot.state === componentRootContainerRoot.stateHidden) {
                    // Show
                    componentRootContainerRoot.show();
                } else {
                    // Set Focus
                    componentRootContainerRoot.focus = true;
                    // Bring To Front
                    componentRootContainerRoot.parent.bringToFront(componentRootContainerRoot);
                }
            }

            // ...
        }

        onFileSelected: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.infoPath === aFilePath) {
                // Check State
                if (componentRootContainerRoot.state === componentRootContainerRoot.stateHidden) {
                    // Show
                    componentRootContainerRoot.show();
                } else {
                    // Set Focus
                    componentRootContainerRoot.focus = true;
                    // Bring To Front
                    componentRootContainerRoot.parent.bringToFront(componentRootContainerRoot);
                }
            }

            // ...
        }

        onComponentClosed: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onComponentClosed - aComponent: " + aComponent);

            // Check Component Info
            if (componentRootContainerRoot.componentInfo === aComponent) {
                // Reset
                componentRootContainerRoot.reset(true);
            }
        }

        onFileClosed: {
            //console.log("DComponentRootContainer.openFilesModelConnection.onFileClosed - aFilePath: " + aFilePath);

            // Check File Path
            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.infoPath === aFilePath) {
                // Reset
                componentRootContainerRoot.reset(true);
            }
        }
    }

    // Component Info Connections
    property Connections componentInfoConnection: Connections {
        target: componentRootContainerRoot.componentInfo

        onRequestContainerClose: {
            console.log("DComponentRootContainer.componentInfoConnection.onRequestContainerClose");

            // Save & Close
            componentRootContainerRoot.reset(true);
            // Reset Focused Component
            propertiesController.focusedComponent = null;

            // ...
        }

        onWidthChanged: {
            // Check Width
            if (componentRootContainerRoot.width !== Number(aWidth)) {
                // Calculate Center X
                var centerX = componentRootContainerRoot.x + componentRootContainerRoot.width * 0.5;
                // Set Pos X
                componentRootContainerRoot.x = centerX - aWidth * 0.5;
                // Set Width
                componentRootContainerRoot.width = Number(aWidth);
            }
        }

        onHeightChanged: {
            // Check Height
            if (componentRootContainerRoot.height !== Number(aHeight)) {
                // Calculate Center Y
                var centerY = componentRootContainerRoot.y + componentRootContainerRoot.height * 0.5;
                // Set Pos Y
                componentRootContainerRoot.y = centerY - aHeight * 0.5;
                // Set Height
                componentRootContainerRoot.height = Number(aHeight);
            }
        }

        // On Component Property Changed
        onComponentPropertyChanged: {
            //console.log("DComponentRootContainer.componentInfoConnection.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // Check Root Component
            if (componentRootContainerRoot.rootQMLComponent !== null) {
                // Set Property
                componentRootContainerRoot.rootQMLComponent.__setProperty(aName, aValue);
            } else {
                console.warn("DComponentRootContainer.componentInfoConnection.onComponentPropertyChanged - NO ROOT COMPONENT!!");
            }
        }

        onLayerVisibleChanged: {
            // Check Root Component
            if (componentRootContainerRoot.rootQMLComponent !== null) {
                // Set Root Container Visibility
                componentRootContainerRoot.rootContainer.visible = componentRootContainerRoot.componentInfo.layerVisible;
            }
        }

        onOwnPropertyAdded: {
            // Remove Root Component
            removeRootComponent();
            // Create Root Component
            createRootComponent();
        }

        onOwnPropertyRemoved: {
            // Remove Root Component
            removeRootComponent();
            // Create Root Component
            createRootComponent();
        }

        onPropertyUpdated: {

        }

        // ...
    }

    // Root Component
    property QtObject rootQMLComponent: null

    property bool waitForNodesToClose: false

    title: "Component" + (componentInfo ? (" - " + componentInfo.componentName  ) : "")

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
        if (dropHovering) {
            return "yellow";//DStyle.colorBorder;
        }

        // Check Focused Component
        if (propertiesController.focusedComponent === componentInfo && componentInfo !== null) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    borderMargins: -1

    radius: 0

    enableDragByPaneButton: true

    Component.onDestruction: {
        // Check Component Info
        if (componentRootContainerRoot.componentInfo !== null) {
            // Set Container
            componentRootContainerRoot.componentInfo.componentContainer = null;
        }

        // Reset Update Component Info Enabled
        componentRootContainerRoot.updateComponentInfoEnabled = false;
        // Reset Component Info
        componentRootContainerRoot.componentInfo = null;
    }

    onComponentInfoChanged: {
        // Check Component Info
        if (componentRootContainerRoot.componentInfo !== null) {
            // Set Container
            componentRootContainerRoot.componentInfo.componentContainer = componentRootContainerRoot;
        }

        // ...
    }

    onFocusChanged: {
        //console.log("DComponentRootContainer.onFocusChanged - focus: " + focus);

        // Check Focus & Component Info
        if (focus) {
//            // Check Previous Scale Level
//            if (componentRootContainerRoot.previousScale !== componentRootContainerRoot.scale) {
//                // Set Scale Duration
//                componentRootContainerRoot.scaleDuration = 100;
//                // Reset Scale
//                componentRootContainerRoot.scale = componentRootContainerRoot.previousScale;
//            } else {
//                // Reset Scale Duration
//                componentRootContainerRoot.scaleDuration = 0;
//            }

            // Reset Scale Duration
            componentRootContainerRoot.scaleDuration = 0;
            // Set Focused Component
            propertiesController.focusedComponent = componentRootContainerRoot.componentInfo;
            // Set Focused File
            openFilesModel.focusedFile = componentRootContainerRoot.componentInfo ? componentRootContainerRoot.componentInfo.infoPath : "";

        } else {
            // Set Scale Duration
            componentRootContainerRoot.scaleDuration = 100;
            // Reset Scale Level
            componentRootContainerRoot.scale = 1.0;
        }
    }

    onPressed: {
        //console.log("DComponentRootContainer.onPressed");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "crcRoot";
        }

        // ...
    }

    onReleased: {
        //console.log("DComponentRootContainer.onReleased");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "crcRoot") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "";
            // Set Focus
            componentRootContainerRoot.focus = true;
        }

        // ...
    }

    onWidthChanged: {
        // Check Update Component Info Enabled
        if (componentRootContainerRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === componentRootContainerRoot.componentInfo) {
            // Check Width
            if (propertiesController.cWidth !== componentRootContainerRoot.width) {
                // Request Width Change
                propertiesController.requestCWidth(componentRootContainerRoot.width);
            }
        }
    }

    onHeightChanged: {
        // Check Update Component Info Enabled
        if (componentRootContainerRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === componentRootContainerRoot.componentInfo) {
            // Check Height
            if (propertiesController.cHeight !== componentRootContainerRoot.height) {
                // Request Height Change
                propertiesController.requestCHeight(componentRootContainerRoot.height);
            }
        }
    }

    onTransitionStarted: {
        console.log("DComponentRootContainer.onTransitionStarted - newState: " + newState);

        // Check State
        if (newState === componentRootContainerRoot.stateHidden) {
            // Close Node Pane
            nodePaneLoader.item.hideNodes();
        } else if (newState === componentRootContainerRoot.stateCreate) {
            // Close Node Pane
            nodePaneLoader.item.hideNodes();
            // Set Node Pane Loader Opacity
            nodePaneLoader.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        console.log("DComponentRootContainer.onTransitionFinished - newState: " + newState);

        // Check State
        if (newState === componentRootContainerRoot.stateShown) {
            // Create Main Component
            componentRootContainerRoot.createRootComponent();
            // Create Child Components
            componentRootContainerRoot.createChildComponents();
            // Set Focus
            componentRootContainerRoot.focus = true;
            // Set Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = true;
            // Set Node Pane Loader Active
            nodePaneLoader.active = true;
            // Set Node Pane opacity
            nodePaneLoader.opacity = 1.0;
        } else {
            // Reset Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = false;
        }
    }

    onStateChanged: {
        // Check State
        if (componentRootContainerRoot.state !== componentRootContainerRoot.stateShown) {
            // Reset Update Component Info Enabled
            componentRootContainerRoot.updateComponentInfoEnabled = false;
        }
    }

    // Create Main Component
    function createRootComponent() {
        // Check Component Info
        if (componentRootContainerRoot.componentInfo !== null && !componentRootContainerRoot.rootComponentCreated) {
            console.log("DComponentRootContainer.createRootComponent - componentName: " + componentRootContainerRoot.componentInfo.componentName);
            // Set Root Component Created
            componentRootContainerRoot.rootComponentCreated = true;

            // Create New Root Object
            componentRootContainerRoot.rootQMLComponent = Qt.createQmlObject(componentRootContainerRoot.componentInfo.generateLiveCode(true, false),  componentRootContainerRoot.rootContainer);

            // Check New Root Object
            if (componentRootContainerRoot.rootQMLComponent === null) {
                console.warn("DComponentRootContainer.createRootComponent - ERROR CREATING ROOT COMPONENT!!");
            }

            // ...

        }
    }

    // Remove Root Component
    function removeRootComponent() {
        // Check New Root Object
        if (componentRootContainerRoot.rootQMLComponent !== null) {
            // Destroy Root Component
            componentRootContainerRoot.rootQMLComponent.destroy();
            // Reset Root Component
            componentRootContainerRoot.rootQMLComponent = null;
            // Reset Root Component Created Flag
            componentRootContainerRoot.rootComponentCreated = false;
        }
    }

    // Create Child Components
    function createChildComponents() {
        // Get Number Of Child Components
        var cCount = componentRootContainerRoot.componentInfo !== null ? componentRootContainerRoot.componentInfo.childCount : 0;
        // Check Component Info
        if (cCount > 0 && !componentRootContainerRoot.childComponentsCreated) {
            // Set Child Components Created
            componentRootContainerRoot.childComponentsCreated = true;

            console.log("DComponentRootContainer.createChildComponents - cCount: " + cCount);

            // Iterate Through Child Components
            for (var i=0; i<cCount; i++) {
                // Get Child Component Info
                var ccInfo = componentRootContainerRoot.componentInfo.childInfo(i);

                console.log("DComponentRootContainer.createChildComponents - child[" + i + "]: " + ccInfo.componentName);

                // Create Child Container Object
                var newObject = newChildComponent.createObject(contentContainer, { "parentContainer": componentRootContainerRoot });

                // Check New Object
                if (newObject) {
                    // Update Child Component Container Object
                    componentRootContainerRoot.updateChildContainerObject(newObject, ccInfo, false);

                } else {
                    console.error("DComponentRootContainer.createChildComponents - ccInfo: " + ccInfo.componentName + " - ERROR CREATING CHILD OBJECT!!");
                }
            }
        }
    }

    // Add Child Component Info
    function addChildComponent(newChildInfo) {
        // Check Root Container Component Info
        if (componentRootContainerRoot.componentInfo !== null) {
            // Add Child Component Info
            componentRootContainerRoot.componentInfo.addChild(newChildInfo);

        } else {
            console.error("DComponentRootContainer.addChildComponent - NO PARENT COMPONENT INFO!!");
        }
    }

    // Remove Child Component
    function removeChildComponent(childComponentObject) {
        console.log("DComponentRootContainer.removeChildComponent - childComponentObject: " + childComponentObject);

        // Set Root Container Focus
        componentRootContainerRoot.focus = true;

        // Check ComponentInfo
        if (componentRootContainerRoot.componentInfo) {
            // Remove Child
            componentRootContainerRoot.componentInfo.removeChild(childComponentObject.componentInfo);
        }

        // Check Child Object
        if (childComponentObject) {
            // Reset Component Info
            childComponentObject.componentInfo = null;
            // Destroy Child Component Object
            childComponentObject.destroy();
        }
    }

    // Update Child Component Container Object
    function updateChildContainerObject(aChildObject, aComponentInfo, aFocus) {
        // Check Child Object & Component Info
        if (aChildObject && aComponentInfo) {
            console.log("DComponentRootContainer.updateChildContainerObject - componentName: " + aComponentInfo.componentName);

            // Set Component Info
            aChildObject.componentInfo = aComponentInfo;
            // Set Focus
            aChildObject.focus = aFocus;

            // Set Pos X
            aChildObject.x = aComponentInfo.posX;
            // Set Pos Y
            aChildObject.y = aComponentInfo.posY;

            // Set Width
            aChildObject.width = aComponentInfo.width;
            // Set Height
            aChildObject.height = aComponentInfo.height;

            // Set Anchors
            aChildObject.setAnchoring();

            // Enable Component Info Update
            aChildObject.updateComponentInfoEnabled = true;

            // ...
        }
    }

    // Set Child Component ID
    function setChildComponentID(aChild, aID) {
        // Store Child Component ID
        componentRootContainerRoot.componentInfo.setChildObjectID(aChild, aID);
    }

    // Hide/Show/Pane Button Function
    function paneButtonFunction() {
        // Check State
        if (componentRootContainerRoot.state !== stateHidden) {
            // Check Node Pane State
            if (nodePaneLoader.item && nodePaneLoader.item.state === "shown") {
                // Set Wait For Nodes To Hide
                componentRootContainerRoot.waitForNodesToClose = true;
                // Hide Nodes
                nodePaneLoader.item.hideNodes();
            } else {
                // Dismiss Pane
                componentRootContainerRoot.dismissPane(false);
            }
        } else {
            // Reset Waiting For Nodes To Close
            componentRootContainerRoot.waitForNodesToClose = false;
            // Set State
            componentRootContainerRoot.show();
        }
    }


    // Zoom Area
    DMouseArea {
        id: wheelArea
        anchors.fill: parent
        visible: componentRootContainerRoot.focus

        property real scaleMin: 1.0
        property real scaleMax: 2.0
        property real scaleSpeed: 0.05

        onWheel: {
            //console.log("#### delta: " + wheel.angleDelta.y);

            // Check Wheel Delta
            if (wheel.angleDelta.y > 2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale < wheelArea.scaleMax) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Inc Scale Level
                    componentRootContainerRoot.scale += wheelArea.scaleSpeed;
                }
            } else if (wheel.angleDelta.y < -2) {
                // Check Enable Scaling & Scale level
                if (componentRootContainerRoot.enableScaling && componentRootContainerRoot.scale > wheelArea.scaleMin) {
                    // Reset Scale Duration
                    componentRootContainerRoot.scaleDuration = 0;
                    // Dec Scale Level
                    componentRootContainerRoot.scale -= wheelArea.scaleSpeed;
                }
            }
        }
    }

    // No Content Placeholder
    DNoContent {
        id: baseCanvas
        anchors.fill: parent
        visible: {
//            if (componentRootContainerRoot.componentInfo && componentRootContainerRoot.componentInfo.childCount > 0) {
//                return false;
//            }
            if (componentRootContainerRoot.rootComponentCreated && componentRootContainerRoot.rootQMLComponent !== null) {
                return false;
            }

            return true;
        }
    }

    // Drop Area For Child Components
    DropArea {
        id: dropArea
        anchors.fill: parent

//        property int hoverX: 0
//        property int hoverY: 0

        onEntered: {
            // Set Hovering
            dropHovering = true;

            //hoverX = drag.x;
            //hoverY = drag.y;

            // Check Drag Keys
            if (drag.keys[0] === CONSTS.newComponentDragKey) {
                //console.log("DComponentRootContainer.dropArea.onEntered - keys: " + drag.keys);
                // Accept Drag
                drag.accept();
            }
        }

//        onPositionChanged: {
//            hoverX = drag.x;
//            hoverY = drag.y;

//            //console.log("DComponentRootContainer.dropArea.onPositionChanged - drag:[" + hoverX + ":" + hoverY + "]");

//            debugCanvas.requestPaint();
//        }

        onExited: {
            // Reset Hovering
            dropHovering = false;
        }

        onDropped: {
            // Reset Hovering
            dropHovering = false;

            // Check Source
            if (drop.source === null) {
                console.warn("DComponentRootContainer.dropArea.onDropped - NULL SOURCE!!");
                return;
            }

            // Check Source
            if (drop.source === componentRootContainerRoot.componentInfo) {
                console.warn("DComponentRootContainer.dropArea.onDropped - RECURSIVE!!!");
                return;
            }

            console.log("DComponentRootContainer.dropArea.onDropped - source: " + drop.source);
            //console.log("DComponentRootContainer.dropArea.onDropped - dynamicProperties: " + drop.source.dynamicProperties);

            // Reset Previous Scale Level
            componentRootContainerRoot.previousScale = 1.0;

            // Create New Object
            var newObject = newChildComponent.createObject(paneContainer, { "parentContainer": componentRootContainerRoot });
            // Check New Object
            if (newObject) {
                // Update Child Component Container Object
                componentRootContainerRoot.updateChildContainerObject(newObject, drop.source.clone(), true);

                // Set Pos X
                newObject.x = drop.x - CONSTS.componentItemWidth * 0.5;
                // Set Pos Y
                newObject.y = drop.y - CONSTS.componentItemHeight * 0.5;

                // Add Child Component Info
                addChildComponent(newObject.componentInfo);

            } else {
                console.error("DComponentRootContainer.dropArea.onDropped - ERROR CREATING NEW OBJECT!");
            }
        }

        Canvas {
            id: debugCanvas
            anchors.fill: parent
            visible: settingsController.tracerVisible && dropArea.hovering
            onPaint: {
                // Get 2D Context
                var ctx = getContext("2d");

                ctx.reset();

                ctx.lineWidth = 1;
                ctx.strokeStyle = "lime";

                ctx.beginPath();
                ctx.moveTo(dropArea.hoverX, 0);
                ctx.lineTo(dropArea.hoverX, dropArea.height);
                ctx.closePath();
                ctx.stroke();

                ctx.beginPath();
                ctx.moveTo(0, dropArea.hoverY);
                ctx.lineTo(dropArea.width, dropArea.hoverY);
                ctx.closePath();
                ctx.stroke();
            }
        }
    }

    // Component Name Label
    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: CONSTS.componentNamesOpacity
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }

    // Node Pane Loader
    DLoader {
        id: nodePaneLoader

        parent: componentRootContainerRoot

        anchors.right: parent.left
        anchors.verticalCenter: parent.verticalCenter

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        sourceComponent: DNodePane {

            //anchors.verticalCenter: parent.verticalCenter

            componentInfo: componentRootContainerRoot.componentInfo

//            onTransitionStarted: {
//                // ...
//            }

            onTransitionFinished: {
                // Check If Waiting For Nodes To Close
                if (componentRootContainerRoot.waitForNodesToClose) {
                    // Reset Waiting For Nodes To Close
                    componentRootContainerRoot.waitForNodesToClose = false;
                    // Dismiss Pane
                    componentRootContainerRoot.dismissPane(false);
                }
            }
        }

        onStatusChanged: {
            // Switch Status
            switch (status) {
                case Loader.Ready:
                    // Set Component Root Container Child Pane
                    //componentRootContainerRoot.childPane = nodePaneLoader.item;
                break;

                case Loader.Error:
                    console.warn("DComponentRootContainer.nodePaneLoader.onStatusChanged - status: " + status + " - ERROR LOADING NODE PANE!");
                break;
            }
        }
    }
}
