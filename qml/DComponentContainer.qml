import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

Item {
    id: ccRoot

    // Component Info
    property ComponentInfo componentInfo: null

    // Root Component
    property bool componentIsRoot: componentInfo !== null ? componentInfo.isRoot : false

    // Root Compoennt Container
    property alias rootContainer: rootContainer
    // Child Components Container
    property alias childContainer: childContainer

    // Default Parent
    default property alias childContent: childContainer.children

    // Clip Root Container
    property alias clipRoot: rootContainer.clip
    // Clip Children Container
    property alias clipChildren: childContainer.clip

    // Root Component Container
    property QtObject rootComponentContainer: null

    // Parent Container
    property QtObject parentComponentContainer: null

    // Root Component
    property QtObject rootLiveQMLComponent: null

    // Drop Hovering
    property bool dropHovering: rootComponentContainer && parentComponentContainer ? rootComponentContainer.hoverContainer === parentComponentContainer : false
    // Drop Hover OK
    property bool dropHoverOK: false

    // Update Component Info Enabled
    property bool updateComponentInfoEnabled: false

    // Root Component Created
    property bool rootComponentCreated: false
    // Child Components Created
    property bool childComponentsCreated: false

    // Component Selected
    property bool selected: false

    // Drop Area Enabled
    property bool dropAreaEnabled: true

    // Child Was Dropped
    property bool childWasDropped: false

    // Child Was Deleted By Child Contaoner Delete
    property bool childWasDeleted: false

    // Child Count
    property int count: childContainer.children.length // componentInfo ? componentInfo.childCount : 0

    // Component Layout
    property string componentLayout: ""

    // Layout Width
    property int layoutWidth: updateHorizontalLayout()
    // Layout Height
    property int layoutHeight: updateVerticalLayout()
    // Layout Spacing
    property int layoutSpacing: updateLayoutSpacing()

    // Component Info Connections
    property Connections componentInfoConnections: Connections {
        target: ccRoot.componentInfo

        // Request Container Close
        onRequestContainerClose: {
            console.log("DComponentRootContainer.componentInfoConnection.onRequestContainerClose");

            // Reset - Save & Close
            ccRoot.rootComponentContainer.reset(true);
            // Reset Focused Component
            propertiesController.focusedComponent = null;

            // ...
        }

        // Component ID Changed
        onComponentIDChanged: {
            // Set Child Component ID
            ccRoot.setChildComponentID(ccRoot.parentComponentContainer, aID);
//            // Check Parent Container
//            if (parentComponentContainer !== null && parentComponentContainer.setChildComponentID !== undefined) {
//                // Set Child Component ID
//                parentComponentContainer.setChildComponentID(ccRoot, aID);
//            }
        }

        // Pos X Changed
        onPosXChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onPosXChanged - aPosX: " + aPosX);

            // Check Pos
            if (ccRoot.parentComponentContainer.x !== Number(aPosX)) {
                // Set Pos X
                ccRoot.parentComponentContainer.x = Number(aPosX);
            }

            // TODO: Handle Bindings & Formulas!
        }

        // Pos Y Changed
        onPosYChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onPosYChanged - aPosY: " + aPosY);

            // Check Pos Y
            if (ccRoot.parentComponentContainer.y !== Number(aPosY)) {
                // Set Pos Y
                ccRoot.parentComponentContainer.y = Number(aPosY);
            }

            // TODO: Handle Bindings & Formulas!
        }

        // Width Changed
        onWidthChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onWidthChanged - aWidth: " + aWidth);
            // Update Width
            updateWidth(aWidth);
        }

        // Height Changed
        onHeightChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onHeightChanged - aHeight: " + aHeight);
            // Update Height
            updateHeight(aHeight);
        }

        // Left Anchor Changed
        onAnchorsLeftChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsLeftChanged - aLeft: " + aLeft);
            // Set Anchors Left
            ccRoot.parentComponentContainer.anchors.left = ccRoot.parseAnchors(aLeft, true);
            // ...
        }

        // Left Anchor Margin Changed
        onAnchorsLeftMarginChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsLeftMarginChanged - aMargin: " + aMargin);
            // Set Left Margin
            ccRoot.parentComponentContainer.anchors.leftMargin = aMargin;
        }

        // Right Anchor Changed
        onAnchorsRightChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsRightChanged - aRight: " + aRight);
            // Set Anchors Right
            ccRoot.parentComponentContainer.anchors.right = ccRoot.parseAnchors(aRight, true);
            // ...
        }

        // Right Anchor Margin Changed
        onAnchorsRightMarginChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsRightMarginChanged - aMargin: " + aMargin);
            // Set Right Margin
            ccRoot.parentComponentContainer.anchors.rightMargin = aMargin;
        }

        // Top Anchor Changed
        onAnchorsTopChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsTopChanged - aTop: " + aTop);
            // Set Anchors Top
            ccRoot.parentComponentContainer.anchors.top = ccRoot.parseAnchors(aTop, true);
        }

        // Top Anchor Margin Changed
        onAnchorsTopMarginChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsTopMarginChanged - aMargin: " + aMargin);
            // Set Top Margin
            ccRoot.parentComponentContainer.anchors.topMargin = aMargin;
        }

        // Bottom Anchor Changed
        onAnchorsBottomChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsBottomChanged - aBottom: " + aBottom);
            // Set Anchors Botom
            ccRoot.parentComponentContainer.anchors.bottom = ccRoot.parseAnchors(aBottom, true);
        }

        // Bottom Anchor Margin Changed
        onAnchorsBottomMarginChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsBottomMarginChanged - aMargin: " + aMargin);
            // Set Bottom Margin
            ccRoot.parentComponentContainer.anchors.bottomMargin = aMargin;
        }

        // Anchor Margins Changed
        onAnchorsMarginsChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsMarginsChanged - aMargins: " + aMargins);
            // Set Margins
            ccRoot.parentComponentContainer.anchors.margins = aMargins;
        }

        // Fill Anchor Changed
        onAnchorsFillChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsFillChanged - aFill: " + aFill);
            // Set Anchors Fill
            ccRoot.parentComponentContainer.anchors.fill = ccRoot.parseAnchors(aFill, false);
        }

        // Center Anchor Changed
        onAnchorsCenterInChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsCenterInChanged - aCenterIn: " + aCenterIn);
            // Set Anchors Center In
            ccRoot.parentComponentContainer.anchors.centerIn = ccRoot.parseAnchors(aCenterIn, false);
        }

        // Horizontal Center Anchor Changed
        onAnchorsHorizontalCenterChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsHorizontalCenterChanged - aHorizontalCenter: " + aHorizontalCenter);
            // Set Anchors Horizontal Center
            ccRoot.parentComponentContainer.anchors.horizontalCenter = ccRoot.parseAnchors(aHorizontalCenter, true);
        }

        // Vertical Center Anchor Changed
        onAnchorsVerticalCenterChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsVerticalCenterChanged - aVerticalCenter: " + aVerticalCenter);
            // Set Anchors Vertical Center
            ccRoot.parentComponentContainer.anchors.verticalCenter = ccRoot.parseAnchors(aVerticalCenter, true);
        }

        // Horizontal Center Anchor Offset Changed
        onAnchorsHorizontalOffsetChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsHorizontalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Horizontal Center Offset
            ccRoot.parentComponentContainer.anchors.horizontalCenterOffset = aOffset;
        }

        // Vertical Center Anchor Offset Changed
        onAnchorsVerticalOffsetChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onAnchorsVerticalCenterOffsetChanged - aOffset: " + aOffset);
            // Set Vertical Center Offset
            ccRoot.parentComponentContainer.anchors.verticalCenterOffset = aOffset;
        }

        // Component Property Changed
        onComponentPropertyChanged: {
            //console.log("DComponentContainer.componentInfoConnections.onComponentPropertyChanged - aName: " + aName + " - aValue: " + aValue);

            // Switch Property Name
            switch (aName) {
                case "spacing":
                    // Update Layout Spacing
                    ccRoot.layoutSpacing = updateLayoutSpacing();
                // Fall Through
                case "layoutDirection":
                    // Update Horizontal Layout
                    updateHorizontalLayout();
                    // Update Vertical Layout
                    updateVerticalLayout();
                break;
            }

            // Check Root Component
            if (ccRoot.rootLiveQMLComponent !== null) {
                // Set Property
                ccRoot.rootLiveQMLComponent.__setProperty(aName, aValue);
            } else {
                console.warn("DComponentContainer.componentInfoConnections.onComponentPropertyChanged - NO ROOT COMPONENT!!");
            }

            // ...
        }

        // Layout Visible Changed
        onLayerVisibleChanged: {
            // Check Root Component
            if (ccRoot.rootComponentContainer !== null) {
                // Set Visibility
                ccRoot.rootContainer.visible = ccRoot.componentInfo.layerVisible;
            }
        }

        // Own Property Added
        onOwnPropertyAdded: {
            console.log("DComponentContainer.componentInfoConnections.onOwnPropertyAdded - aName: " + aName);
            // Remove Root Component
            removeRootComponent();
            // Create Root Component
            createRootComponent();
        }

        // Own Property Removed
        onOwnPropertyRemoved: {
            console.log("DComponentContainer.componentInfoConnections.onOwnPropertyRemoved - aName: " + aName);
            // Remove Root Component
            removeRootComponent();
            // Create Root Component
            createRootComponent();
        }

        // Child Component About To Be Removed
        onChildAboutToBeRemoved: {
            console.log("DComponentContainer.componentInfoConnections.onChildAboutToBeRemoved");
            // Reset Parent
            ccRoot.parentComponentContainer.parent = null;
            // Set Update Component Info Enabled
            ccRoot.updateComponentInfoEnabled = false;
            // Reset Component Info
            ccRoot.parentComponentContainer.componentInfo = null;
            // Destroy Component
            ccRoot.parentComponentContainer.destroy();
        }

        // Child Added Slot
        onChildAdded: {
            // Check If Child Was Dropped
            if (ccRoot.childWasDropped) {
                //console.log("DComponentContainer.componentInfoConnection.onChildAdded - WAS DROPPED!");

                // Reset Child Was Dropped
                ccRoot.childWasDropped = false;

                return;
            }

            //console.log("DComponentContainer.componentInfoConnection.onChildAdded - aIndex: " + aIndex);

            // Create Child Component Container
            var newContainer = createChildComponent(aIndex, newContainerDummyParent);
            // Insert Child Container
            insertChildContainer(aIndex, newContainer);

            // Update Layout Size
            updateLayoutSize();
        }

        // Child Moved Slot
        onChildMoved: {
            //console.log("DComponentContainer.componentInfoConnection.onChildMoved - aIndex: " + aIndex + " - aTarget: " + aTarget);
            // Move Child Container
            moveChildContainer(aIndex, aTarget);
        }

        onChildRemoved: {
            // Update Layout Size
            updateLayoutSize();
        }

        // ...
    }
    // Properties Controller Connection
    property Connections propertiesControllerConnections: Connections {

        target: propertiesController

        onFocusedComponentChanged: {
            // Check Focused Component
            if (propertiesController.focusedComponent === ccRoot.componentInfo) {
                // Set Focus To Parent Container
                ccRoot.parentComponentContainer.focus = true;
            }
        }
    }

    // Hovering Child Item
    property QtObject childItem: getHoveringContainer(dropArea.drag.x, dropArea.drag.y, rootComponentContainer);
    // Drag Source
    property ComponentInfo dragSource: null
    // Drag Keys
    property string dragKey: ""

    // Root Container State
    property string rootContainerState: rootComponentContainer ? rootComponentContainer.state : ""

    // New Component Dropped Signal
    signal newComponentDropped(var dropSource, var posX, var posY)
    // Component Need Destroy Signal
    signal componentNeedDestroy()
    // Implicit Size Changed Signal
    signal implicitSizeChanged(var iWidth, var iHeight);

    // On Destruction Slot
    Component.onDestruction: {
        // Reset Update Component Info Enabled
        ccRoot.updateComponentInfoEnabled = false;

        // Check Component Info
        if (ccRoot.componentInfo !== null) {
            // Set Container
            ccRoot.componentInfo.componentContainer = null;
        }

        // Reset Component Info
        ccRoot.componentInfo = null;
    }

    // Component Info Changed Slot
    onComponentInfoChanged: {
        // Check Component Info
        if (ccRoot.componentInfo !== null) {
            // Set Component Container For Anchoring!
            ccRoot.componentInfo.componentContainer = ccRoot.parentComponentContainer;
            // Set Component Layout
            ccRoot.componentLayout = ccRoot.componentInfo.layoutBase();
        } else {
            // Reset Component Layout
            ccRoot.componentLayout = "";
        }
    }

    // Width Changed
    onWidthChanged: {
        // Check ComponentInfo
        if (ccRoot.componentInfo !== null && ccRoot.updateComponentInfoEnabled && Number(ccRoot.componentInfo.width) !== ccRoot.width) {
            //console.log("DComponentContainer.onWidthChanged - width: " + ccRoot.width);
            // Set Width
            ccRoot.componentInfo.setWidth(ccRoot.width);
        }
    }

    // Height Changed
    onHeightChanged: {
        // Check ComponentInfo
        if (ccRoot.componentInfo !== null && ccRoot.updateComponentInfoEnabled && Number(ccRoot.componentInfo.height) !== ccRoot.height) {
            //console.log("DComponentContainer.onHeightChanged - height: " + ccRoot.height);
            // Set Width
            ccRoot.componentInfo.setHeight(ccRoot.height);
        }
    }

    // On Hover Child Item Changed
    onChildItemChanged: {
        // Check Child Item
        if (ccRoot.childItem !== null) {
            // Set Hover Container
            ccRoot.rootComponentContainer.hoverContainer = ccRoot.childItem;

        } else if (dropArea.containsDrag) {
            // Set Hover Container
            ccRoot.rootComponentContainer.hoverContainer = ccRoot.parentComponentContainer;
        }

        // Get Hover Container Component Info Path
        var hPath = ccRoot.rootComponentContainer.hoverContainer ? ccRoot.rootComponentContainer.hoverContainer.componentInfo.componentPath : "NULL";

        //console.log("DComponentContainer.dropArea.onChildItemChanged - hoverContainer: " + hPath);
        //console.log("DComponentContainer.dropArea.onChildItemChanged - dragSource: " + ccRoot.dragSource);

        // Check Hover Container
        if (ccRoot.rootComponentContainer.hoverContainer !== null) {
            // Check Drag Source by Current Hovered Container
            ccRoot.rootComponentContainer.hoverContainer.componentContainer.checkDragSource(ccRoot.dragSource, ccRoot.dragKey);
        }
    }

    // On Root Container State Changed Slot
    onRootContainerStateChanged: {
        //console.log("DComponentContainer.onRootContainerStateChanged - rootContainerState: " + rootContainerState);
        // Check Root Container State
        if (ccRoot.rootContainerState === ccRoot.rootComponentContainer.stateCreate) {
            // Disable Update Component Info
            ccRoot.updateComponentInfoEnabled = false;
        }
    }

    // Update Pos X
    function updatePosX(posX) {
        // Check If Update Component Info Enabled
        if (ccRoot.componentInfo !== null && ccRoot.updateComponentInfoEnabled && !ccRoot.componentInfo.isRoot && ccRoot.componentInfo.posX !== posX) {
            //console.log("DComponentContainer.updatePosX - posX: " + posX);
            // Set Component Pos X
            ccRoot.componentInfo.setPosX(posX);
        }
    }

    // Update Pos Y
    function updatePosY(posY) {
        // Check If Update Component Info Enabled
        if (ccRoot.componentInfo !== null && ccRoot.updateComponentInfoEnabled && !ccRoot.componentInfo.isRoot && ccRoot.componentInfo.posY !== posY) {
            //console.log("DComponentContainer.updatePosY - posY: " + posY);
            // Set Component Pos Y
            ccRoot.componentInfo.setPosY(posY);
        }
    }

    // Update Parent Component Container Width
    function updateWidth(newWidth) {
        // Check Width
        if (ccRoot.parentComponentContainer.width !== Number(newWidth)) {

            // Check If Root
            if (ccRoot.componentInfo.isRoot) {
                // Calculate Center X
                var centerX = ccRoot.parentComponentContainer.x + ccRoot.parentComponentContainer.width * 0.5;
                // Set Pos X
                ccRoot.parentComponentContainer.x = centerX - newWidth * 0.5;
            }

            // Set Width
            ccRoot.parentComponentContainer.width = Number(newWidth);
        }

        // Check Live QML Component
        if (ccRoot.rootLiveQMLComponent !== null) {
            // Set Width
            ccRoot.rootLiveQMLComponent.width = ccRoot.width;
        }

        // TODO: Handle Bindings & Formulas!

    }

    // Update Parent Component Container Height
    function updateHeight(newHeight) {
        // Check Height
        if (ccRoot.parentComponentContainer.height !== Number(newHeight)) {
            // Check If Root
            if (ccRoot.componentInfo.isRoot) {
                // Calculate Center Y
                var centerY = ccRoot.parentComponentContainer.y + ccRoot.parentComponentContainer.height * 0.5;
                // Set Pos X
                ccRoot.parentComponentContainer.y = centerY - newHeight * 0.5;
            }

            // Set Height
            ccRoot.parentComponentContainer.height = Number(newHeight);
        }

        // Check Live QML Component
        if (ccRoot.rootLiveQMLComponent !== null) {
            // Set Width
            ccRoot.rootLiveQMLComponent.height = ccRoot.height;
        }

        // TODO: Handle Bindings & Formulas!

    }

    // Array Move
    function arrayMove(ref, from, to) {
        var element = ref.array[from];
        ref.array.splice(from, 1);
        ref.array.splice(to, 0, element);
    }

    // Create Content
    function createContent() {
        // Create Root Component
        createRootComponent();
        // Create Child Components
        createChildComponents();
        // Update Layout Size
        updateLayoutSize();
    }

    // Remove Content
    function removeContent() {
        // Remove Child Components
        removeChildComponents();
        // Remove Root Component
        removeRootComponent();
    }

    // Create Main Component
    function createRootComponent() {
        // Check Component Info
        if (ccRoot.componentInfo !== null && !ccRoot.rootComponentCreated) {
            console.log("DComponentContainer.createRootComponent - path: " + ccRoot.componentInfo.componentPath);
            // Set Root Component Created
            ccRoot.rootComponentCreated = true;

            // Generate Live Code
            var cFileName = propertiesController.currentProject.generateLiveCode(ccRoot.componentInfo, false);

            // Create Component
            var component  = Qt.createComponent("file://" + cFileName);
            // Check Status
            if (component.status === Component.Ready) {
                // Create New Root Object
                ccRoot.rootLiveQMLComponent = component.createObject(ccRoot.rootContainer);

                // Remove Live Temp File
                propertiesController.currentProject.removeLiveTempFile(cFileName);

            } else {
                console.error("DComponentContainer.createRootComponent - ERROR CREATING ROOT COMPONENT!! - error: " + component.errorString());
                return;
            }

            // Check New Root Object
            if (ccRoot.rootLiveQMLComponent === null) {
                console.error("DComponentContainer.createRootComponent - ERROR CREATING ROOT OBJECT!!");
            }
        }
    }

    // Remove Root Component
    function removeRootComponent() {
        // Check New Root Object
        if (ccRoot.rootLiveQMLComponent !== null) {
            console.log("DComponentContainer.removeRootComponent");
            // Destroy Root Component
            ccRoot.rootLiveQMLComponent.destroy();
            // Reset Root Component
            ccRoot.rootLiveQMLComponent = null;
            // Reset Root Component Created Flag
            ccRoot.rootComponentCreated = false;
        }
    }

    // Create Child Component Containe
    function createChildComponent(childIndex, containerParent) {
        // Check Root Component Container
        if (ccRoot.rootComponentContainer === undefined || ccRoot.rootComponentContainer.newComponentChildContainer === undefined) {
            console.error("DComponentContainer.createChildComponent - INVALID ROOT COMPONENT CONTAINER!!!");
            return;
        }

        // Check Compoennt Info
        if (ccRoot.componentInfo !== null) {
            console.log("DComponentContainer.createChildComponent - path: " + ccRoot.componentInfo.componentPath + " - childIndex: " + childIndex);

            // Get Child Component Info
            var ccInfo = ccRoot.componentInfo.childInfo(childIndex);
            // Create New Child Container Object
            var newObject = ccRoot.rootComponentContainer.newComponentChildContainer.createObject(containerParent, { "parentComponentContainer": ccRoot.parentComponentContainer });

            // Check New Object
            if (newObject) {
                // Update Child Component Container Object
                ccRoot.updateChildContainerObject(newObject, ccInfo, ccRoot.parentComponentContainer, false);

            } else {
                console.error("DComponentContainer.createChildComponent - ccInfo: " + ccInfo.componentName + " - ERROR CREATING CHILD OBJECT!!");
            }

            // ...

            return newObject;
        }
    }

    // Move Child Container
    function moveChildContainer(childIndex, targetIndex) {
        console.log("DComponentContainer.moveChildContainer - childIndex: " + childIndex + " - targetIndex: " + targetIndex);

        // Get Child Count
        var cCount = componentInfo.childCount;
        // Get Child Container Count
        var ccCount = childContainer.children.length;
        // Calculate Child Comntainers Offset
        var ccOffset = ccCount - cCount;

        // Get Bottom Index
        var bottomIndex = Math.min(childIndex, targetIndex) + ccOffset;

//        console.log("DComponentContainer.moveChildContainer -      cCount : " + cCount);
//        console.log("DComponentContainer.moveChildContainer -     ccCount : " + ccCount);
//        console.log("DComponentContainer.moveChildContainer -    ccOffset : " + ccOffset);
//        console.log("DComponentContainer.moveChildContainer - bottomIndex : " + bottomIndex);

        // Init Temp Array For Child Containers
        var ccTemp = { "array": [] };

        // Move Child Containers To Dummy Parent
        for (var i=bottomIndex; i<ccCount; i++) {
            // Push To Temp Array
            ccTemp.array.push(childContainer.children[bottomIndex]);
            // Set Item\s Parent to Dummy Parent
            childContainer.children[bottomIndex].parent = containersDummyParent;
        }

        // Dec Bottom Index
        bottomIndex -= ccOffset;

        // Move Items
        arrayMove(ccTemp, childIndex - bottomIndex, targetIndex - bottomIndex);

        // Move Back Rearranged Items To ContentContainer
        for (var n=0; n<ccTemp.array.length; n++) {
            // Set Parent
            ccTemp.array[n].parent = childContainer;
        }

        // Clear Temp Array
        ccTemp.array.splice(0, ccTemp.array.length);
    }

    // Insert Child Container
    function insertChildContainer(childIndex, newChildContainer) {
        console.log("DComponentContainer.insertChildContainer - childIndex: " + childIndex);

        // Get Child Count
        var cCount = componentInfo.childCount;
        // Get Initial Child Container Count
        var ccCount = childContainer.children.length;
        // Calculate Child Comntainers Offset
        var ccOffset = 0;

        console.log("DComponentContainer.insertChildContainer - ccCount: " + ccCount + " - ccOffset: " + ccOffset);

        // TODO: There seems to be an issue with DPaneBase paneContainer, that is the first element in DContainer's childContainer
        // Have to investigate. First Item in the DContainer's childContainer is the paneContainer!!!

        // Init Temp Array For Child Containers
        var ccTemp = [];

        // Iterate Through Children Above
        for (var i=childIndex + ccOffset; i<ccCount; i++) {
            // Push To Temp Array
            ccTemp.push(childContainer.children[childIndex + ccOffset]);
            // Set Item\s Parent to Dummy Parent
            childContainer.children[childIndex + ccOffset].parent = containersDummyParent;
        }

        // Set Child Container Parent
        newChildContainer.parent = childContainer;

        // Get Dummy Container Parent Count
        var dccCount = ccTemp.length;

        //console.log("DComponentContainer.insertChildContainer - dccCount: " + dccCount);

        // Iterate Through Dummy Parent's Children
        for (var n=0; n<dccCount; n++) {
            //console.log("DComponentContainer.insertChildContainer - c: " + ccTemp[n]);
            // Set Container Item Parent
            ccTemp[n].parent = childContainer;
        }

        // Clear Temp Array
        ccTemp.splice(0, ccTemp.length);
    }

    // Create Children Components
    function createChildComponents() {
        // Get Number Of Child Components
        var cCount = ccRoot.componentInfo !== null ? ccRoot.componentInfo.childCount : 0;
        // Check Component Info
        if (cCount > 0 && !ccRoot.childComponentsCreated) {
            // Set Child Components Created
            ccRoot.childComponentsCreated = true;

            //console.log("DComponentContainer.createChildComponents - cCount: " + cCount);

            // Iterate Through Child Components
            for (var i=0; i<cCount; i++) {
                // Create Child Component Container
                createChildComponent(i, childContainer);
            }
        }
    }

    // Add Child Component Info
    function addChildComponent(newChildInfo) {
        // Check Root Container Component Info
        if (ccRoot.componentInfo !== null) {
            // Add Child Component Info
            ccRoot.componentInfo.addChild(newChildInfo);

        } else {
            console.error("DComponentContainer.addChildComponent - NULL COMPONENT INFO!!");
        }
    }

    // Remove Child Component Container
    function removeChildComponent(childComponentContainerObject, deleteFromContainer) {
        console.log("DComponentContainer.removeChildComponent - childComponentContainerObject: " + childComponentContainerObject);

        // Check Child Object
        if (childComponentContainerObject) {
            // Set Root Container Focus
            ccRoot.focus = true;

            // Set Child Deleted
            ccRoot.childWasDeleted = deleteFromContainer;

            // Check ComponentInfo
            if (ccRoot.componentInfo && deleteFromContainer) {
                // Remove Child From Parent
                ccRoot.componentInfo.removeFromParent();
            }

            // No Need To Destroy, Child Container Listening to childAboutToBeRemoved signal
        }
    }

    // Remove Children Containers
    function removeChildComponents() {
        // Check If Child Components Created
        if (ccRoot.childComponentsCreated) {
            console.log("DComponentContainer.removeChildComponents");

            // Get Child Container Count
            var ccCount = childContainer.children.length;
            // Iterate Through Child Component Containers
            for (var i=ccCount-1; i>=0; i--) {
                // Destroy
                childContainer.children[i].destroy();
            }

            // ...
        }
    }

    // Update Child Component Container Object
    function updateChildContainerObject(aChildContainerObject, aComponentInfo, aParentComponentContainer, aFocus) {
        // Check Child Object & Component Info
        if (aChildContainerObject && aComponentInfo) {
            console.log("DComponentContainer.updateChildContainerObject - path: " + aComponentInfo.componentPath);

            // Set Parent Component Container
            aChildContainerObject.parentComponentContainer = aParentComponentContainer;//ccRoot.parentComponentContainer;

            // Set Focus
            aChildContainerObject.focus = aFocus;

            // Check Component Layout
            if (ccRoot.componentLayout === "") {
                // Set Pos X
                aChildContainerObject.x = aComponentInfo.posX;
                // Set Pos Y
                aChildContainerObject.y = aComponentInfo.posY;
            }

            // Set Width
            aChildContainerObject.width = aComponentInfo.width;
            // Set Height
            aChildContainerObject.height = aComponentInfo.height;

            // Set Parent Component Container
            aChildContainerObject.componentContainer.parentComponentContainer = aChildContainerObject;

            // Set Component Info
            aChildContainerObject.componentInfo = aComponentInfo;

            // Set Anchors
            aChildContainerObject.componentContainer.setAnchoring();

            // Enable Component Info Update
            aChildContainerObject.componentContainer.updateComponentInfoEnabled = true;

            // ...
        }
    }

    // Set Child Component ID
    function setChildComponentID(aChild, aID) {
        // Store Child Component ID
        ccRoot.componentInfo.setChildObjectID(aChild, aID);
    }

    // Set Anchoring
    function setAnchoring() {
        // Check Component Info
        if (ccRoot.componentInfo !== null && !ccRoot.componentIsRoot) {
            console.log("DComponentContainer.setAnchoring - path: " + ccRoot.componentInfo.componentPath);
            // Set Anchor Fill
            if (ccRoot.componentInfo.anchorsFill !== "") {
                // Set Fill Anchor
                ccRoot.parentComponentContainer.anchors.fill = parseAnchors(ccRoot.componentInfo.anchorsFill, false);
            } else if (ccRoot.componentInfo.anchorsCenterIn !== "") {
                // Set Center In Anchor
                ccRoot.parentComponentContainer.anchors.centerIn = parseAnchors(ccRoot.componentInfo.anchorsCenterIn, false);
            } else {

                // Check Anchor Horizotal Center
                if (ccRoot.componentInfo.horizontalCenter !== "") {
                    // Set Horizontal Center
                    ccRoot.parentComponentContainer.anchors.horizontalCenter = parseAnchors(ccRoot.componentInfo.horizontalCenter, true);
                } else {
                    // Set Left Anchor
                    ccRoot.parentComponentContainer.anchors.left = parseAnchors(ccRoot.componentInfo.anchorsLeft, true);
                    // Set Right Anchor
                    ccRoot.parentComponentContainer.anchors.right = parseAnchors(ccRoot.componentInfo.anchorsRight, true);
                }

                // Check Anchor Vertical Center
                if (ccRoot.componentInfo.verticalCenter !== "") {
                    // Set Vertical Center
                    ccRoot.parentComponentContainer.anchors.verticalCenter = parseAnchors(ccRoot.componentInfo.verticalCenter, true);
                } else {
                    // Set Top Anchor
                    ccRoot.parentComponentContainer.anchors.top = parseAnchors(ccRoot.componentInfo.anchorsTop, true);
                    // Set Bottom Anchor
                    ccRoot.parentComponentContainer.anchors.bottom = parseAnchors(ccRoot.componentInfo.anchorsBottom, true);
                }
            }

            // Check Margins
            if (ccRoot.componentInfo.anchorsMargins !== "") {
                // Set Margins
                ccRoot.parentComponentContainer.anchors.margins = Number(ccRoot.componentInfo.anchorsMargins);
            } else {
                // Set Left, Right, Top, Botton Margin
                ccRoot.parentComponentContainer.anchors.leftMargin = Number(ccRoot.componentInfo.anchorsLeftMargin);
                ccRoot.parentComponentContainer.anchors.rightMargin = Number(ccRoot.componentInfo.anchorsRightMargin);
                ccRoot.parentComponentContainer.anchors.topMargin = Number(ccRoot.componentInfo.anchorsTopMargin);
                ccRoot.parentComponentContainer.anchors.bottomMargin = Number(ccRoot.componentInfo.anchorsBottomMargin);
            }

            // Set Horizontal Center Ofset
            ccRoot.parentComponentContainer.anchors.horizontalCenterOffset = Number(ccRoot.componentInfo.anchorsHorizontalOffset);
            // Set Vertical Center Offset
            ccRoot.parentComponentContainer.anchors.verticalCenterOffset = Number(ccRoot.componentInfo.anchorsVerticalOffset);
        }
    }

    // Parse Anchors
    function parseAnchors(anchorString, needPoint) {
        // Get Anchor Elements
        var anchorElements = anchorString.split(".");

        //console.log("DComponentContainer.parseAnchors - anchorElements: " + anchorElements);

        // Get Anchor Target
        var anchorTarget = anchorElements[0];

        // Check Anchor Target
        if (anchorTarget === "") {
            //console.log("DComponentContainer.parseAnchors - Clearing Anchor");
            return undefined;
        }

        // Get Anchoring Point
        var anchorPoint = anchorElements[1];

        // Check Anchor Target
        if (anchorTarget === "parent") {
            // Set Anchor Target - Morph To Object
            anchorTarget = ccRoot.parentComponentContainer.parent;
        } else {
            // Get Component By ID
            var targetComponent = ccRoot.componentInfo.getChildObject(anchorTarget);

            // TODO: Double Check!!

            // Get Anchor Target
            anchorTarget = targetComponent !== null ? targetComponent.componentContainer : undefined;
        }

        // Check Anchor Target
        if (anchorTarget === null || anchorTarget === undefined) {
            console.warn("DComponentContainer.componentInfoConnections.onAnchorRightChanged - NO SUCH TARGET!");
            return undefined;
        }

        //console.log("DComponentContainer.parseAnchors - anchorTarget: " + anchorTarget);

        // Check Anchor Point
        if (anchorPoint === "" || anchorPoint === undefined) {
            // Check If Need Anchoring Point
            if (needPoint) {
                console.warn("DComponentContainer.parseAnchors - NO ANCHOR POINT DEFINED!");
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
                console.warn("DComponentContainer.parseAnchors - anchorPoint: " + anchorPoint + " - INVALID ANCHOR POINT!");
            return undefined;
        }

        return anchorPoint;
    }

    // Get Hovering Container
    function getHoveringContainer(posX, posY, parentContainer) {
        // Check If Contains Drag
        if (!dropArea.containsDrag) {
            return null;
        }

        // Set Drop Pos X
        ccRoot.rootComponentContainer.hoverPosX = posX;
        // Set Drop Pos Y
        ccRoot.rootComponentContainer.hoverPosY = posY;

        //console.log("DComponentContainer.dropArea.getHoveringContainer - parentContainer: " + (parentContainer.componentInfo ? parentContainer.componentInfo.componentPath : "NULL") + " - pos: " + posX + ":" + posY);

        // Check Parent Container
        if (parentContainer === undefined || parentContainer === null) {
            //console.log("DComponentContainer.dropArea.getHoveringContainer - INVALID PARENT CONTAINER!!!");
            return null;
        }

        // Check Component Container
        if (parentContainer.componentContainer === undefined) {
            //console.log("DComponentContainer.dropArea.getHoveringContainer - UNDEFINED COMPONENT CONTAINER!!!");
            return null;
        }

        // Int Child Found
        var childFound = parentContainer.componentContainer.childContainer.childAt(posX, posY);
        // Init Next Child Found
        var nextChildFound = null;
        // Check For Children
        if (childFound && childFound.componentContainer.count > 0) {
            // Test For Child Hit
            nextChildFound = getHoveringContainer(posX - childFound.x, posY - childFound.y, childFound);
        }

        return nextChildFound !== null ? nextChildFound : childFound;
    }

    // Check Drag Source
    function checkDragSource(dragSource, dragKey) {
        //console.log("DComponentContainer.checkDragSource - path: " + ccRoot.componentInfo.componentPath);
        //console.log("DComponentContainer.checkDragSource - dragSource: " + dragSource);
        //console.log("DComponentContainer.checkDragSource - dragKey: " + dragKey);

        // Check Source
        if (dragSource === null) {
            console.warn("DComponentContainer.checkDragSource - NULL SOURCE!!");
            // Reset Drop Hover OK
            ccRoot.dropHoverOK = false;
            return;
        }

        // Check Source
        if (dragSource === ccRoot.componentInfo) {
            console.warn("DComponentContainer.checkDragSource - RECURSIVE!!!");
            // Reset Drop Hover OK
            ccRoot.dropHoverOK = false;
            return;
        }

        // TODO: More Checking!!!

        // Check Drag Keys
        if (dragKey === CONSTS.newComponentDragKey) {
            //console.log("DComponentContainer.checkDragSource - dragKey: " + dragKey);

            // Accept Drag
            //drag.accept();

            // Set Drop Hover OK
            ccRoot.dropHoverOK = true;
        } else {
            // Reset Drop Hover OK
            ccRoot.dropHoverOK = false;
        }

        // ...
    }

    // Make The Drop
    function makeDrop(drop) {
        // Check Drop OK
        if (!ccRoot.dropHoverOK) {
            console.warn("DComponentContainer.dropArea.onDropped - NOT ACCEPTED!!");
            return;
        }

        //console.log("DComponentContainer.makeDrop - source: " + drop.source.componentName + " - childItem: " + (childItem ? childItem.componentInfo : "NULL"));

        // Create New Object
        var newObject = rootComponentContainer.newComponentChildContainer.createObject(childContainer, { "parentComponentContainer": ccRoot });

        // Check New Object
        if (newObject) {
            // Update Child Component Container Object
            ccRoot.updateChildContainerObject(newObject, drop.source.clone(), ccRoot.parentComponentContainer, true);

            // Check Component Layout
            if (ccRoot.componentLayout === "") {
                // Set Pos X
                newObject.x = rootComponentContainer.hoverPosX - CONSTS.componentItemWidth * 0.5;
                // Set Pos Y
                newObject.y = rootComponentContainer.hoverPosY - CONSTS.componentItemHeight * 0.5;
            }

            // Set Child Was Dropped
            ccRoot.childWasDropped = true;

            // Add Child Component Info
            addChildComponent(newObject.componentInfo);

            // Update Layout Size
            updateLayoutSize();

        } else {
            console.error("DComponentContainer.makeDrop - ERROR CREATING NEW OBJECT!");
        }
    }

    // Update Layout Spacing
    function updateLayoutSpacing() {
        // Check Component Layout
        if (ccRoot.componentLayout === "") {
            return 0;
        }

        console.log("DComponentContainer.updateLayoutSpacing - componentLayout: " + ccRoot.componentLayout);

        return ccRoot.componentInfo.propertyValue("spacing");
    }

    // Update Horizontal Layout
    function updateHorizontalLayout() {
        // Check Component Layout
        if (ccRoot.componentLayout === "" || ccRoot.count === 0 || ccRoot.parentComponentContainer.width === 0) {
            return 0;
        }

        //console.log("DComponentContainer.updateHorizontalLayout - componentLayout: " + ccRoot.componentLayout + " - layoutSpacing: " + ccRoot.layoutSpacing);

        // Init New Layout Width
        var newLayoutWidth = 0;

        // Check Component Layout
        if (ccRoot.componentLayout === "Row") {
            // Get Layout Direction
            var rlDirection = ccRoot.componentInfo.propertyValue("layoutDirection");

            // Iterate Through Children
            for (var i=0; i<ccRoot.count; i++) {

                // Check Layout Direction
                if (rlDirection === "Qt.LeftToRight") {
                    // Set Child Pos X
                    childContainer.children[i].x = newLayoutWidth;
                } else {
                    // Set Child Position
                    childContainer.children[i].x = ccRoot.parentComponentContainer.width - newLayoutWidth - childContainer.children[i].width;
                }

                // Inc New Layout Width
                newLayoutWidth += childContainer.children[i].width;

                // Check Index
                if (ccRoot.count > 1 && (i < (ccRoot.count - 1))) {
                    // Inc New Layout Width
                    newLayoutWidth += ccRoot.layoutSpacing;
                }
            }
        } else if (ccRoot.componentLayout === "Column") {
            // Iterate Through Children
            for (var j=0; j<ccRoot.count; j++) {
                // Set New Layout Width
                newLayoutWidth = Math.max(newLayoutWidth, childContainer.children[j].width);
            }

        } else if (ccRoot.componentLayout === "Flow") {
            // Get Layout Direction
            var flDirection = ccRoot.componentInfo.propertyValue("layoutDirection");

            // Check Layout Direction

            // ...

        } else {
            console.warn("DComponentContainer.updateHorizontalLayout - componentLayout: " + ccRoot.componentLayout + " - UNSUPPORTED LAYOUT");
        }

        // ...

        return newLayoutWidth;
    }

    // Update Vertical Layout
    function updateVerticalLayout() {
        // Check Component Layout
        if (ccRoot.componentLayout === "" || ccRoot.count === 0) {
            return 0;
        }

        //console.log("DComponentContainer.updateVerticalLayout - componentLayout: " + ccRoot.componentLayout + " - layoutSpacing: " + ccRoot.layoutSpacing);

        // Init New Layout Height
        var newLayoutHeight = 0;

        // Check Component Layout
        if (ccRoot.componentLayout === "Row") {
            // Iterate Through Children
            for (var i=0; i<ccRoot.count; i++) {
                // Set New Layout Height
                newLayoutHeight = Math.max(newLayoutHeight, childContainer.children[i].height);
            }
        // Check Component Layout
        } else if (ccRoot.componentLayout === "Column") {
            // Iterate Through Children
            for (var j=0; j<ccRoot.count; j++) {
                // Set Child Pos Y
                childContainer.children[j].y = newLayoutHeight;
                // Inc New Layout Height
                newLayoutHeight += childContainer.children[j].height;
                // Check Index
                if (ccRoot.count > 1 && (j < (ccRoot.count - 1))) {
                    // Inc New Layout Height
                    newLayoutHeight += ccRoot.layoutSpacing;
                }
            }
        // Check Component Layout
        } else if (ccRoot.componentLayout === "Flow") {
            // Get Layout Direction
            var flDirection = ccRoot.componentInfo.propertyValue("layoutDirection");

            // Check Layout Direction

            // ...

        } else {
            console.warn("DComponentContainer.updateVerticalLayout - componentLayout: " + ccRoot.componentLayout + " - UNSUPPORTED LAYOUT");
        }

        // ...

        return newLayoutHeight;
    }

    // Update Layout Size
    function updateLayoutSize() {
/*
        // Check Component Info
        if (ccRoot.componentLayout !== "") {
            console.log("DComponentContainer.updateLayoutSize - count: " + ccRoot.count + " - componentLayout: " + ccRoot.componentLayout);

            // Init New Width
            var newWidth = 0;
            // Init New Height
            var newHeight = 0;

            // TODO: Handle Different Layout Directions

            // TODO: Handle Child Size Changes

            // Iterate Through Children
            for (var i=0; i<ccRoot.count; i++) {

                // Check Component
                if (ccRoot.componentLayout === "Row" && ccRoot.componentInfo.useIWidth) {
                    // Get Child Object
                    var childObject = childContainer.children[i];

                    //console.log("DComponentContainer.updateLayoutSize - childObject: " + childObject);

                    // Set Child Object Pos X
                    childObject.x = newWidth;
                    // Reset Child Object  Pos Y
                    childObject.y = 0;
                    // Set New Width
                    newWidth += childObject.width;

                    // Check Use Implicit Height
                    if (ccRoot.componentInfo.useIHeight) {
                        // Set New Height
                        newHeight = Math.max(newHeight, childObject.height);
                    }

                } else if (ccRoot.componentLayout === "Column" && ccRoot.componentInfo.useIHeight) {

                    // ...

                } else if (ccRoot.componentLayout === "Flow" && (ccRoot.componentInfo.useIWidth || ccRoot.componentInfo.useIHeight)) {

                    // ...

                } else {
                    console.warn("DComponentContainer.updateLayoutSize - UNSUPPORTED LAYOUT COMPONENT!");
                    return;
                }

                // ...

            }

            // Check Use Implicit Width
            if (ccRoot.componentInfo.useIWidth && ccRoot.count > 0) {
                // Update Width
                updateWidth(newWidth);
//                // Set Parent Container Width
//                ccRoot.parentComponentContainer.width = newWidth;

                // TODO: Set Default Value if New Width is 0
            }

            // Check New Height
            if (ccRoot.componentInfo.useIHeight && ccRoot.count > 0) {
                // Update Height
                updateHeight(newHeight);
//                // Set Parent Container Height
//                ccRoot.parentComponentContainer.height = newHeight;

                // TODO: Set Default Value If New Height is 0
            }
        }
*/
    }

    // Dummy Parent For New Container
    Item {
        id: newContainerDummyParent
        visible: false
    }

    // Dummy Parent For Containers
    Item {
        id: containersDummyParent
        visible: false
    }

    // Root Component Container
    Item {
        id: rootContainer
        anchors.fill: parent
        clip: true

//        Rectangle {
//            anchors.fill: parent
//            color: "#44FF0000"
//        }
    }

    // Helper Mouse Area - This Seems to Work OK
    DMouseArea {
        anchors.fill: parent
        onClicked: {
            // Set Focus -> Focused Component
            ccRoot.parentComponentContainer.focus = true;
        }
    }

    // Drop Area For Child Components
    DDropArea {
        id: dropArea
        anchors.fill: parent

        enabled: ccRoot.dropAreaEnabled

        onEntered: {
            //console.log("DComponentContainer.dropArea.onEntered - path: " + ccRoot.componentInfo.componentPath);

            // Set Drag Source
            ccRoot.dragSource = drag.source;
            // Set Drag Key
            ccRoot.dragKey = drag.keys[0];

            drag.accept();

            // Check Hover Container
            if (ccRoot.rootComponentContainer.hoverContainer === null) {
                // Set Initial Hover Container
                ccRoot.rootComponentContainer.hoverContainer = ccRoot.parentComponentContainer;
            }

            // Check Hover Container
            if (ccRoot.rootComponentContainer.hoverContainer !== null) {
                // Check Drag Source by Current Hovered Container
                ccRoot.rootComponentContainer.hoverContainer.componentContainer.checkDragSource(ccRoot.dragSource, ccRoot.dragKey);
            }

            // ...
        }

        onDropped: {
            // Check Hover Container
            if (ccRoot.rootComponentContainer.hoverContainer !== null) {
                // Make The Drop
                ccRoot.rootComponentContainer.hoverContainer.componentContainer.makeDrop(drop);
                // Reset Hover Container
                ccRoot.rootComponentContainer.hoverContainer = null;
            }
        }

        onExited: {
            //console.log("DComponentContainer.dropArea.onExited - path: " + ccRoot.componentInfo.componentPath);

            // Reset Drop Hover OK
            ccRoot.dropHoverOK = false;
            // Reset Hover Container
            ccRoot.rootComponentContainer.hoverContainer = null;
            // Reset Drag Source
            ccRoot.dragSource = null;
            // Reset Drag Key
            ccRoot.dragKey = "";
        }

//        Canvas {
//            id: debugCanvas
//            anchors.fill: parent
//            visible: settingsController.tracerVisible && dropArea.hovering
//            onPaint: {
//                // Get 2D Context
//                var ctx = getContext("2d");

//                ctx.reset();

//                ctx.lineWidth = 1;
//                ctx.strokeStyle = "lime";

//                ctx.beginPath();
//                ctx.moveTo(dropArea.hoverX, 0);
//                ctx.lineTo(dropArea.hoverX, dropArea.height);
//                ctx.closePath();
//                ctx.stroke();

//                ctx.beginPath();
//                ctx.moveTo(0, dropArea.hoverY);
//                ctx.lineTo(dropArea.width, dropArea.hoverY);
//                ctx.closePath();
//                ctx.stroke();
//            }
//        }
    }

    // Content/Children Container
    Item {
        id: childContainer
        anchors.fill: parent
        clip: true
    }

    // Component Label
    DText {
        parent: ccRoot
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible
        opacity: CONSTS.componentNamesOpacity
        font.pixelSize: 48 // TODO: Manage Size
        text: ccRoot.componentInfo ? ccRoot.componentInfo.componentName : ""
    }
}
