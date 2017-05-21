import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DPaneBase {
    id: crcRoot

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
            rootComponentContainer: crcRoot
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

    // Component Info Connections
    property Connections componentInfoConnection: Connections {
        target: crcRoot.componentInfo

        onRequestContainerClose: {
            console.log("DComponentRootContainer.componentInfoConnection.onRequestContainerClose");

            // Save & Close
            crcRoot.reset(true);
            // Reset Focused Component
            propertiesController.focusedComponent = null;

            // ...
        }

        onWidthChanged: {
            // Check Width
            if (crcRoot.width !== Number(aWidth)) {
                // Calculate Center X
                var centerX = crcRoot.x + crcRoot.width * 0.5;
                // Set Pos X
                crcRoot.x = centerX - aWidth * 0.5;
                // Set Width
                crcRoot.width = Number(aWidth);
            }

            // Check QML Component
            if (crcRoot.rootLiveQMLComponent !== null) {
                // Set Width
                crcRoot.rootLiveQMLComponent.width = crcRoot.width;
            }
        }

        onHeightChanged: {
            // Check Height
            if (crcRoot.height !== Number(aHeight)) {
                // Calculate Center Y
                var centerY = crcRoot.y + crcRoot.height * 0.5;
                // Set Pos Y
                crcRoot.y = centerY - aHeight * 0.5;
                // Set Height
                crcRoot.height = Number(aHeight);
            }

            // Check QML Component
            if (crcRoot.rootLiveQMLComponent !== null) {
                // Set Width
                crcRoot.rootLiveQMLComponent.height = crcRoot.height;
            }
        }

        // On Component Property Changed
        onComponentPropertyChanged: {
            //console.log("DComponentRootContainer.componentInfoConnection.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // Check Root Component
            if (crcRoot.rootLiveQMLComponent !== null) {
                // Set Property
                crcRoot.rootLiveQMLComponent.__setProperty(aName, aValue);
            } else {
                console.warn("DComponentRootContainer.componentInfoConnection.onComponentPropertyChanged - NO ROOT COMPONENT!!");
            }
        }

        onLayerVisibleChanged: {
            // Check Root Component
            if (crcRoot.rootLiveQMLComponent !== null) {
                // Set Root Container Visibility
                crcRoot.rootContainer.visible = crcRoot.componentInfo.layerVisible;
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
    property QtObject rootLiveQMLComponent: null

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
        if (crcRoot.componentInfo !== null) {
            // Set Container
            crcRoot.componentInfo.componentContainer = null;
        }

        // Reset Update Component Info Enabled
        crcRoot.updateComponentInfoEnabled = false;
        // Reset Component Info
        crcRoot.componentInfo = null;
    }

    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_N:
                // Toggle Nodes
                toggleNodePane();
            break;
        }
    }

    onComponentInfoChanged: {
        // Check Component Info
        if (crcRoot.componentInfo !== null) {
            // Set Container
            crcRoot.componentInfo.componentContainer = crcRoot;
        }

        // ...
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
            // Set Focused Component
            propertiesController.focusedComponent = crcRoot.componentInfo;
            // Set Focused File
            openFilesModel.focusedFile = crcRoot.componentInfo ? crcRoot.componentInfo.infoPath : "";

        } else {
            // Set Scale Duration
            crcRoot.scaleDuration = 100;
            // Reset Scale Level
            crcRoot.scale = 1.0;
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
            crcRoot.focus = true;
        }

        // ...
    }

    onWidthChanged: {
        // Check Update Component Info Enabled
        if (crcRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === crcRoot.componentInfo) {
            // Check Width
            if (Number(propertiesController.cWidth) !== crcRoot.width) {
                //console.log("DComponentRootContaienr.onWidthChanged - width: " + crcRoot.width + " - cWidth: " + propertiesController.cWidth);
                // Request Width Change
                propertiesController.requestCWidth(crcRoot.width);
            }
        }
    }

    onHeightChanged: {
        // Check Update Component Info Enabled
        if (crcRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === crcRoot.componentInfo) {
            // Check Height
            if (Number(propertiesController.cHeight) !== crcRoot.height) {
                //console.log("DComponentRootContaienr.onHeightChanged - height: " + crcRoot.height + " - cHeight: " + propertiesController.cHeight);
                // Request Height Change
                propertiesController.requestCHeight(crcRoot.height);
            }
        }
    }

    onTransitionStarted: {
        //console.log("DComponentRootContainer.onTransitionStarted - newState: " + newState);

        // Check State
        if (newState === crcRoot.stateHidden) {
            // Close Node Pane
            nodePaneLoader.item.hideNodes();
        } else if (newState === crcRoot.stateCreate) {
            // Close Node Pane
            nodePaneLoader.item.hideNodes();
            // Set Node Pane Loader Opacity
            nodePaneLoader.opacity = 0.0;
        }
    }

    onTransitionFinished: {
        //console.log("DComponentRootContainer.onTransitionFinished - newState: " + newState);

        // Check State
        if (newState === crcRoot.stateShown) {
            // Create Main Component
            crcRoot.createRootComponent();
            // Create Child Components
            crcRoot.createChildComponents();
            // Set Focus
            crcRoot.focus = true;
            // Set Update Component Info Enabled
            crcRoot.updateComponentInfoEnabled = true;
            // Set Node Pane Loader Active
            nodePaneLoader.active = true;
            // Set Node Pane opacity
            nodePaneLoader.opacity = 1.0;
        } else {
            // Reset Update Component Info Enabled
            crcRoot.updateComponentInfoEnabled = false;
        }
    }

    onStateChanged: {
        // Check State
        if (crcRoot.state !== crcRoot.stateShown) {
            // Reset Update Component Info Enabled
            crcRoot.updateComponentInfoEnabled = false;
        }
    }

    // Create Main Component
    function createRootComponent() {
        // Check Component Info
        if (crcRoot.componentInfo !== null && !crcRoot.rootComponentCreated) {
            console.log("DComponentRootContainer.createRootComponent - componentName: " + crcRoot.componentInfo.componentName);
            // Set Root Component Created
            crcRoot.rootComponentCreated = true;

            // Create New Root Object
            crcRoot.rootLiveQMLComponent = Qt.createQmlObject(crcRoot.componentInfo.generateLiveCode(true, false),  crcRoot.rootContainer);

            // Check New Root Object
            if (crcRoot.rootLiveQMLComponent === null) {
                console.warn("DComponentRootContainer.createRootComponent - ERROR CREATING ROOT COMPONENT!!");
            }

            // ...

        }
    }

    // Remove Root Component
    function removeRootComponent() {
        // Check New Root Object
        if (crcRoot.rootLiveQMLComponent !== null) {
            // Destroy Root Component
            crcRoot.rootLiveQMLComponent.destroy();
            // Reset Root Component
            crcRoot.rootLiveQMLComponent = null;
            // Reset Root Component Created Flag
            crcRoot.rootComponentCreated = false;
        }
    }

    // Create Child Components
    function createChildComponents() {
        // Get Number Of Child Components
        var cCount = crcRoot.componentInfo !== null ? crcRoot.componentInfo.childCount : 0;
        // Check Component Info
        if (cCount > 0 && !crcRoot.childComponentsCreated) {
            // Set Child Components Created
            crcRoot.childComponentsCreated = true;

            console.log("DComponentRootContainer.createChildComponents - cCount: " + cCount);

            // Iterate Through Child Components
            for (var i=0; i<cCount; i++) {
                // Get Child Component Info
                var ccInfo = crcRoot.componentInfo.childInfo(i);

                console.log("DComponentRootContainer.createChildComponents - child[" + i + "]: " + ccInfo.componentName);

                // Create Child Container Object
                var newObject = newChildComponent.createObject(contentContainer, { "parentContainer": crcRoot });

                // Check New Object
                if (newObject) {
                    // Update Child Component Container Object
                    crcRoot.updateChildContainerObject(newObject, ccInfo, false);

                } else {
                    console.error("DComponentRootContainer.createChildComponents - ccInfo: " + ccInfo.componentName + " - ERROR CREATING CHILD OBJECT!!");
                }
            }
        }
    }

    // Add Child Component Info
    function addChildComponent(newChildInfo) {
        // Check Root Container Component Info
        if (crcRoot.componentInfo !== null) {
            // Add Child Component Info
            crcRoot.componentInfo.addChild(newChildInfo);

        } else {
            console.error("DComponentRootContainer.addChildComponent - NO PARENT COMPONENT INFO!!");
        }
    }

    // Remove Child Component
    function removeChildComponent(childComponentObject) {
        console.log("DComponentRootContainer.removeChildComponent - childComponentObject: " + childComponentObject);

        // Set Root Container Focus
        crcRoot.focus = true;

        // Check ComponentInfo
        if (crcRoot.componentInfo) {
            // Remove Child
            crcRoot.componentInfo.removeChild(childComponentObject.componentInfo);
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
        crcRoot.componentInfo.setChildObjectID(aChild, aID);
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
            //console.log("#### delta: " + wheel.angleDelta.y);

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

    // No Content Placeholder
    DNoContent {
        id: baseCanvas
        anchors.fill: parent
        visible: {
//            if (crcRoot.componentInfo && crcRoot.componentInfo.childCount > 0) {
//                return false;
//            }
            if (crcRoot.rootComponentCreated && crcRoot.rootLiveQMLComponent !== null) {
                return false;
            }

            return true;
        }
    }

    // Drop Area For Child Components
    DropArea {
        id: dropArea
        anchors.fill: parent

        onEntered: {
            // Set Hovering
            dropHovering = true;

            // Check Drag Keys
            if (drag.keys[0] === CONSTS.newComponentDragKey) {
                //console.log("DComponentRootContainer.dropArea.onEntered - keys: " + drag.keys);
                // Accept Drag
                drag.accept();
            }
        }

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
            if (drop.source === crcRoot.componentInfo) {
                console.warn("DComponentRootContainer.dropArea.onDropped - RECURSIVE!!!");
                return;
            }

            console.log("DComponentRootContainer.dropArea.onDropped - source: " + drop.source);

            // Reset Previous Scale Level
            crcRoot.previousScale = 1.0;

            // Create New Object
            var newObject = newChildComponent.createObject(paneContainer, { "parentContainer": crcRoot });

            // Check New Object
            if (newObject) {
                // Update Child Component Container Object
                crcRoot.updateChildContainerObject(newObject, drop.source.clone(), true);

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

        parent: crcRoot

        anchors.right: parent.left
        anchors.verticalCenter: parent.verticalCenter

        opacity: 0.0
        Behavior on opacity { DFadeAnimation { } }
        visible: opacity > 0.0

        sourceComponent: DNodePane {

            //anchors.verticalCenter: parent.verticalCenter

            componentInfo: crcRoot.componentInfo

//            onTransitionStarted: {
//                // ...
//            }

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
