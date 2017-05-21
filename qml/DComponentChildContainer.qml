import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: cccRoot

    property ComponentInfo componentInfo: null

    property Connections componentInfoConnections: Connections {
        target: cccRoot.componentInfo

        onComponentIDChanged: {
            // Check Parent Container
            if (parentContainer !== null && parentContainer.setChildComponentID !== undefined) {
                // Set Child Component ID
                parentContainer.setChildComponentID(cccRoot, aID);
            }
        }

        onPosXChanged: {
            // Check Pos
            if (cccRoot.x !== Number(aPosX)) {
                // Set Pos X
                cccRoot.x = Number(aPosX);
            }
        }

        onPosYChanged: {
            // Check Pos Y
            if (cccRoot.y !== Number(aPosY)) {
                // Set Pos Y
                cccRoot.y = Number(aPosY);
            }
        }

        onWidthChanged: {
            // Check Width
            if (cccRoot.width !== Number(aWidth)) {
                // Set Width
                cccRoot.width = Number(aWidth);
            }

            // Check Live QML Component
            if (cccRoot.childLiveQMLComponent !== null) {
                // Set Width
                cccRoot.childLiveQMLComponent.width = cccRoot.width;
            }
        }

        onHeightChanged: {
            // Check Height
            if (cccRoot.height !== Number(aHeight)) {
                // Set Height
                cccRoot.height = Number(aHeight);
            }

            // Check Live QML Component
            if (cccRoot.childLiveQMLComponent !== null) {
                // Set Width
                cccRoot.childLiveQMLComponent.height = cccRoot.height;
            }
        }

        onAnchorsLeftChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsLeftChanged - aLeft: " + aLeft);
            // Set Anchors Left
            cccRoot.anchors.left = cccRoot.parseAnchors(aLeft, true);
            // ...
        }

        // Left Anchor Margin Changed
        onAnchorsLeftMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsLeftMarginChanged - aMargin: " + aMargin);
            // Set Left Margin
            cccRoot.anchors.leftMargin = aMargin;
        }

        // Right Anchor Changed
        onAnchorsRightChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsRightChanged - aRight: " + aRight);
            // Set Anchors Right
            cccRoot.anchors.right = cccRoot.parseAnchors(aRight, true);
            // ...
        }

        // Right Anchor Margin Changed
        onAnchorsRightMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsRightMarginChanged - aMargin: " + aMargin);
            // Set Right Margin
            cccRoot.anchors.rightMargin = aMargin;
        }

        // Top Anchor Changed
        onAnchorsTopChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsTopChanged - aTop: " + aTop);
            // Set Anchors Top
            cccRoot.anchors.top = cccRoot.parseAnchors(aTop, true);
        }

        // Top Anchor Margin Changed
        onAnchorsTopMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsTopMarginChanged - aMargin: " + aMargin);
            // Set Top Margin
            cccRoot.anchors.topMargin = aMargin;
        }

        // Bottom Anchor Changed
        onAnchorsBottomChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsBottomChanged - aBottom: " + aBottom);
            // Set Anchors Botom
            cccRoot.anchors.bottom = cccRoot.parseAnchors(aBottom, true);
        }

        // Bottom Anchor Margin Changed
        onAnchorsBottomMarginChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsBottomMarginChanged - aMargin: " + aMargin);
            // Set Bottom Margin
            cccRoot.anchors.bottomMargin = aMargin;
        }

        onAnchorsMarginsChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsMarginsChanged - aMargins: " + aMargins);
            // Set Margins
            cccRoot.anchors.margins = aMargins;
        }

        // Fill Anchor Changed
        onAnchorsFillChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsFillChanged - aFill: " + aFill);
            // Set Anchors Fill
            cccRoot.anchors.fill = cccRoot.parseAnchors(aFill, false);
        }

        // Center Anchor Changed
        onAnchorsCenterInChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsCenterInChanged - aCenterIn: " + aCenterIn);
            // Set Anchors Center In
            cccRoot.anchors.centerIn = cccRoot.parseAnchors(aCenterIn, false);
        }

        // Horizontal Center Anchor Changed
        onAnchorsHorizontalCenterChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsHorizontalCenterChanged - aHorizontalCenter: " + aHorizontalCenter);
            // Set Anchors Horizontal Center
            cccRoot.anchors.horizontalCenter = cccRoot.parseAnchors(aHorizontalCenter, true);
        }

        // Vertical Center Anchor Changed
        onAnchorsVerticalCenterChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsVerticalCenterChanged - aVerticalCenter: " + aVerticalCenter);
            // Set Anchors Vertical Center
            cccRoot.anchors.verticalCenter = cccRoot.parseAnchors(aVerticalCenter, true);
        }

        // Horizontal Center Anchor Offset Changed
        onAnchorsHorizontalOffsetChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsHorizontalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Horizontal Center Offset
            cccRoot.anchors.horizontalCenterOffset = aOffset;
        }

        // Vertical Center Anchor Offset Changed
        onAnchorsVerticalOffsetChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onAnchorsVerticalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Vertical Center Offset
            cccRoot.anchors.verticalCenterOffset = aOffset;
        }

        // Component Property Changed
        onComponentPropertyChanged: {
            //console.log("DComponentChildContainer.componentInfoConnections.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // Check Root Component
            if (cccRoot.childLiveQMLComponent !== null) {
                // Set Property
                cccRoot.childLiveQMLComponent.__setProperty(aName, aValue);
            } else {
                console.warn("DComponentChildContainer.componentInfoConnections.onComponentPropertyChanged - NO ROOT COMPONENT!!");
            }

            // ...
        }

        onLayerVisibleChanged: {
            // Check Root Component
            if (cccRoot.rootComponentContainer !== null) {
                // Set Visibility
                cccRoot.rootContainer.visible = cccRoot.componentInfo.layerVisible;
            }
        }

        onOwnPropertyAdded: {
            console.log("DComponentChildContainer.componentInfoConnections.onOwnPropertyAdded - aName: " + aName);
//            // Remove Root Component
//            removeRootComponent();
//            // Create Root Component
//            createRootComponent();
        }

        onOwnPropertyRemoved: {
            console.log("DComponentChildContainer.componentInfoConnections.onOwnPropertyRemoved - aName: " + aName);
//            // Remove Root Component
//            removeRootComponent();
//            // Create Root Component
//            createRootComponent();
        }

        // Child Component About To Be Removed
        onChildAboutToBeRemoved: {
            console.log("DComponentChildContainer.componentInfoConnections.onChildAboutToBeRemoved");
            // Reset Component Info
            cccRoot.componentInfo = null;
            // Destroy Component
            cccRoot.destroy();
        }

        // ...
    }

    property bool updateComponentInfoEnabled: false

    property bool selected: false

    // Root Component Container
    property QtObject rootComponentContainer: null

    // Child Root Component
    property QtObject childLiveQMLComponent: null

    // Root Component Created
    property bool rootComponentCreated: false
    // Children Created
    property bool childComponentsCreated: false

    // Drop Hovering
    property bool dropHovering: false

    borderColor: {
        // Check Component Info
        if (cccRoot.componentInfo !== null && cccRoot.componentInfo === propertiesController.focusedComponent) {
            return DStyle.colorBorder;
        }

        // Check If Drop Hovering
        if (cccRoot.dropHovering) {
            return "yellow";//DStyle.colorBorder;
        }

        // Check If Selected
        if (cccRoot.selected) {
            return DStyle.colorBorderSelected;
        }

        return DStyle.colorBorderNoFocus;
    }

    borderMargins: -1

    radius: 0

    enablePosOverlay: true
    enableSizeOverlay: true
    setFocusOnResize: true

    drag.minimumX: -cccRoot.width
    drag.maximumX: parent.width
    drag.minimumY: -cccRoot.height
    drag.maximumY: parent.height

//    Component.onCompleted: {
//    }

    Component.onDestruction: {
        // Check Component Info
        if (cccRoot.componentInfo !== null) {
            // Set Container
            cccRoot.componentInfo.componentContainer = null;
        }

        // Reset Update Component Info Enabled
        cccRoot.updateComponentInfoEnabled = false;
        // Reset Component Info
        cccRoot.componentInfo = null;
    }

    onComponentInfoChanged: {
        // Check Component Info
        if (cccRoot.componentInfo !== null) {
            // Set Container
            cccRoot.componentInfo.componentContainer = cccRoot;

            // Create Content
            createContent();

            // ...

        } else {

            // Clear Content
            clearContent();

            // ...

        }
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

            case Qt.Key_N:
                // Check Root Component Container
                if (cccRoot.rootComponentContainer !== null) {
                    // Toggle Nodes
                    cccRoot.rootComponentContainer.toggleNodePane();
                }
            break;
        }
    }

    onPressed: {
        //console.log("DComponentChildContainer.onPressed");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "cccRoot";
        }

        // ...
    }

    onReleased: {
        //console.log("DComponentChildContainer.onReleased");

        // Check First Mouse Press Owner
        if (DSystemModel.firstMousePressOwner === "cccRoot") {
            // Set First Mouse Press Owner
            DSystemModel.firstMousePressOwner = "";
            // Set Focus
            cccRoot.focus = true;
        }

        // ...
    }

    onFocusChanged: {
        //console.log("DComponentChildContainer.onFocusChanged - focus: " + focus);
        // Check Focus
        if (cccRoot.focus) {
            // Set Focused Componrnt
            propertiesController.focusedComponent = cccRoot.componentInfo;
        }
    }

    onXChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Position
            if (propertiesController.cX !== cccRoot.x) {
                // Request Component Pos X
                propertiesController.requestCX(cccRoot.x);
            }
        }
    }

    onYChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Position
            if (propertiesController.cY !== cccRoot.y) {
                // Request Component Pos Y
                propertiesController.requestCY(cccRoot.y);
            }
        }
    }

    onWidthChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Width
            if (Number(propertiesController.cWidth) !== cccRoot.width) {
                // Request Component Width
                propertiesController.requestCWidth(cccRoot.width);
            }
        }
    }

    onHeightChanged: {
        // Check If Update Component Info Enabled
        if (cccRoot.updateComponentInfoEnabled && propertiesController.focusedComponent === cccRoot.componentInfo) {
            // Check Height
            if (Number(propertiesController.cHeight) !== cccRoot.height) {
                // Request Component Height
                propertiesController.requestCHeight(cccRoot.height);
            }
        }
    }

    // Set Anchoring
    function setAnchoring() {
        // Check Component Info
        if (cccRoot.componentInfo !== null) {
            // Set Anchor Fill
            if (cccRoot.componentInfo.anchorsFill !== "") {
                // Set Fill Anchor
                cccRoot.anchors.fill = parseAnchors(cccRoot.componentInfo.anchorsFill, false);
            } else if (cccRoot.componentInfo.anchorsCenterIn !== "") {
                // Set Center In Anchor
                cccRoot.anchors.centerIn = parseAnchors(cccRoot.componentInfo.anchorsCenterIn, false);
            } else {

                // Check Anchor Horizotal Center
                if (cccRoot.componentInfo.horizontalCenter !== "") {
                    // Set Horizontal Center
                    cccRoot.anchors.horizontalCenter = parseAnchors(cccRoot.componentInfo.horizontalCenter, true);
                } else {
                    // Set Left Anchor
                    cccRoot.anchors.left = parseAnchors(cccRoot.componentInfo.anchorsLeft, true);
                    // Set Right Anchor
                    cccRoot.anchors.right = parseAnchors(cccRoot.componentInfo.anchorsRight, true);
                }

                // Check Anchor Vertical Center
                if (cccRoot.componentInfo.verticalCenter !== "") {
                    // Set Vertical Center
                    cccRoot.anchors.verticalCenter = parseAnchors(cccRoot.componentInfo.verticalCenter, true);
                } else {
                    // Set Top Anchor
                    cccRoot.anchors.top = parseAnchors(cccRoot.componentInfo.anchorsTop, true);
                    // Set Bottom Anchor
                    cccRoot.anchors.bottom = parseAnchors(cccRoot.componentInfo.anchorsBottom, true);
                }
            }

            // Check Margins
            if (cccRoot.componentInfo.anchorsMargins !== "") {
                // Set Margins
                cccRoot.anchors.margins = Number(cccRoot.componentInfo.anchorsMargins);
            } else {
                // Set Left, Right, Top, Botton Margin
                cccRoot.anchors.leftMargin = Number(cccRoot.componentInfo.anchorsLeftMargin);
                cccRoot.anchors.rightMargin = Number(cccRoot.componentInfo.anchorsRightMargin);
                cccRoot.anchors.topMargin = Number(cccRoot.componentInfo.anchorsTopMargin);
                cccRoot.anchors.bottomMargin = Number(cccRoot.componentInfo.anchorsBottomMargin);
            }

            // Set Horizontal Center Ofset
            cccRoot.anchors.horizontalCenterOffset = Number(cccRoot.componentInfo.anchorsHorizontalOffset);
            // Set Vertical Center Offset
            cccRoot.anchors.verticalCenterOffset = Number(cccRoot.componentInfo.anchorsVerticalOffset);
        }
    }

    // Parse Anchors
    function parseAnchors(anchorString, needPoint) {
        // Get Anchor Elements
        var anchorElements = anchorString.split(".");

        //console.log("DComponentChildContainer.parseAnchors - anchorElements: " + anchorElements);

        // Get Anchor Target
        var anchorTarget = anchorElements[0];

        // Check Anchor Target
        if (anchorTarget === "") {
            //console.log("DComponentChildContainer.parseAnchors - Clearing Anchor");
            return undefined;
        }

        // Get Anchoring Point
        var anchorPoint = anchorElements[1];

        // Check Anchor Target
        if (anchorTarget === "parent") {
            // Set Anchor Target - Morph To Object
            anchorTarget = parentContainer.paneContainer;
        } else {
            // Get Component By ID
            var targetComponent = cccRoot.componentInfo.getChildObject(anchorTarget);
            // Get Anchor Target
            anchorTarget = targetComponent !== null ? targetComponent.componentContainer.mainContainerObject : undefined;
        }

        // Check Anchor Target
        if (anchorTarget === null || anchorTarget === undefined) {
            console.warn("DComponentChildContainer.componentInfoConnections.onAnchorRightChanged - NO SUCH TARGET!");
            return undefined;
        }

        //console.log("DComponentChildContainer.parseAnchors - anchorTarget: " + anchorTarget);

        // Check Anchor Point
        if (anchorPoint === "" || anchorPoint === undefined) {
            // Check If Need Anchoring Point
            if (needPoint) {
                console.warn("DComponentChildContainer.parseAnchors - NO ANCHOR POINT DEFINED!");
                return undefined;
            }

            return anchorTarget;
        }

        // Switch Anchor Point
        switch (anchorPoint) {
            case "left":                anchorPoint = anchorTarget.left;                break;
            case "right":               anchorPoint = anchorTarget.right;               break;
            case "top":                 anchorPoint = anchorTarget.top;                 break;
            case "bottom":              anchorPoint = anchorTarget.bottom;              break;
            case "horizontalCenter":    anchorPoint = anchorTarget.horizontalCenter;    break;
            case "verticalCenter":      anchorPoint = anchorTarget.verticalCenter;      break;

            default:
                console.warn("DComponentChildContainer.parseAnchors - anchorPoint: " + anchorPoint + " - INVALID ANCHOR POINT!");
            return undefined;
        }

        return anchorPoint;
    }

    // Create Content
    function createContent() {
        console.log("DComponentChildContainer.createContent");
        // Create Root Component
        createRootComponent();
        // Create Child Components
        //createChildren();
    }

    // Cler Content
    function clearContent() {
        console.log("DComponentChildContainer.clearContent");
        // Remove Children
        //removeChildren();
        // Remove Root Component
        removeRootComponent();
    }

    // Create Root Component
    function createRootComponent() {
        // Check Component Info
        if (cccRoot.componentInfo !== null && !cccRoot.rootComponentCreated) {
            console.log("DComponentChildContainer.createContent - name: " + cccRoot.componentInfo.componentName);
            // Set Root Component Created
            cccRoot.rootComponentCreated = true;
            // Create Root Component Object
            cccRoot.childLiveQMLComponent = Qt.createQmlObject(cccRoot.componentInfo.generateLiveCode(false, false),  cccRoot.rootContainer);
            // Check Root Component
            if (cccRoot.childLiveQMLComponent !== null) {
                // Set Fill Anchor
                //cccRoot.rootComponentContainer.anchors.fill = cccRoot;
                // Set Update Component Info Enabled
                cccRoot.updateComponentInfoEnabled = true;
            } else {
                console.warn("DComponentChildContainer.createRootComponent - ERROR CREATING ROOT COMPONENT!!");
            }

            // ...
        }
    }

    // Remove Root Component
    function removeRootComponent() {
        // Check New Root Object
        if (cccRoot.childLiveQMLComponent !== null) {
            console.log("DComponentChildContainer.removeRootComponent");
            // Destroy Root Component
            cccRoot.childLiveQMLComponent.destroy();
            // Reset Root Component
            cccRoot.childLiveQMLComponent = null;
            // Reset Root Component Created Flag
            cccRoot.rootComponentCreated = false;
            // Reset Update Component Info Enabled
            cccRoot.updateComponentInfoEnabled = false;
        }
    }

    // Create Children
    function createChildren() {
        // Check Component Info
        if (cccRoot.componentInfo !== null && !cccRoot.childComponentsCreated && cccRoot.rootComponentContainer !== null) {
            console.log("DComponentChildContainer.createChildren - count: " + cccRoot.componentInfo.childCount);
            // Set Child Components Created
            cccRoot.childComponentsCreated = true;
            // Get Child Count
            var cCount = cccRoot.componentInfo.childCount;
            // Iterate Through Children
            for (var i=0; i<cCount; i++) {
                // Create New Child Container Object
                createChild(cccRoot.componentInfo.childInfo(i));
            }
        }
    }

    // Remove Children
    function removeChildren() {
        // Get Content Container Child Count
        var ccCount = cccRoot.contentContainer.children.length;

        console.log("DComponentChildContainer.removeChildren - count: " + ccCount);

        // Iterate Through Children
        for (var i=ccCount-1; i>=0; i--) {
            // Destroy Child
            cccRoot.contentContainer.children[i].destroy();
        }
    }

    // Create Child
    function createChild(componentInfo) {
        // Check Root Container
        if (cccRoot.rootContainer !== null) {
            // Create New Child Container
            var newChildContainer = cccRoot.rootContainer.newChildComponent.createObject(cccRoot.contentContainer, { "parentContainer": cccRoot });
            // Check New Child Container
            if (newChildContainer !== null) {
                // Update Child Component Container Object
                updateChildContainerObject(newChildContainer, componentInfo, false);
            }

            return newChildContainer;

        } else {
            console.warn("DComponentChildContainer.createChild - NO ROOT CONTAINER!!!");
        }
    }

    // Add Child Component
    function addChildComponent(newChildComponent) {
        // Check Root Container Component Info
        if (cccRoot.componentInfo !== null) {
            // Add Child Component Info
            cccRoot.componentInfo.addChild(newChildComponent);

        } else {
            console.error("DComponentChildContainer.addChildComponent - NO PARENT COMPONENT INFO!!");
        }
    }

    // Remove Child
    function removeChildComponent(childComponentObject) {
        // Set Root Container Focus
        cccRoot.focus = true;

        // Check ComponentInfo
        if (cccRoot.componentInfo) {
            // Remove Child
            cccRoot.componentInfo.removeChild(childComponentObject.componentInfo);
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
            console.log("DComponentChildContainer.updateChildContainerObject - componentName: " + aComponentInfo.componentName);

            // Set Component Info
            aChildObject.componentInfo = aComponentInfo;
            // Set Focus
            aChildObject.focus = aFocus;
            // Enable Component Info Update
            aChildObject.updateComponentInfoEnabled = true;

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

            // ...
        }
    }

    // Drop Area
    DropArea {
        id: dropArea
        anchors.fill: parent

//        property int hoverX: 0
//        property int hoverY: 0

        onEntered: {
            // Set Hovering
            cccRoot.dropHovering = true;

            // Check Drag Keys
            if (drag.keys[0] === CONSTS.newComponentDragKey) {
                //console.log("DComponentRootContainer.dropArea.onEntered - keys: " + drag.keys);
                // Accept Drag
                drag.accept();
            }
        }

//        onPositionChanged: {
//            // Update Hover Positions
//            hoverX = drag.x;
//            hoverY = drag.y;

//            // ...
//        }

        onExited: {
            // Reset Hovering
            cccRoot.dropHovering = false;

        }

        onDropped: {
            // Reset Hovering
            cccRoot.dropHovering = false;

            // Check Source
            if (drop.source === null) {
                console.warn("DComponentChildContainer.dropArea.onDropped - NULL SOURCE!!");
                return;
            }

            // Check Source
            if (drop.source === cccRoot.componentInfo) {
                console.warn("DComponentChildContainer.dropArea.onDropped - RECURSIVE!!!");
                return;
            }

            if (cccRoot.rootContainer === null) {
                console.warn("DComponentChildContainer.dropArea.onDropped - NO ROOT CONTAINER!!!");
                return;
            }

            console.log("DComponentChildContainer.dropArea.onDropped - source: " + drop.source);

            // Create New Child Component
            var newChildObject = cccRoot.rootContainer.newChildComponent.createObject(contentContainer, { "parentContainer": cccRoot });

            // Check New Child Object
            if (newChildObject) {
                // Update Child Object
                cccRoot.updateChildContainerObject(newChildObject, drop.source.clone(), true);

                // Set Pos X
                newChildObject.x = drop.x - CONSTS.componentItemWidth * 0.5;
                // Set Pos Y
                newChildObject.y = drop.y - CONSTS.componentItemHeight * 0.5;

                // Add Child Component Info
                addChildComponent(newChildObject.componentInfo);
            }
        }
    }

    // Component Label
    DText {
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: CONSTS.componentNamesOpacity
        font.pixelSize: 48
        text: componentInfo ? componentInfo.componentName : ""
    }
}
