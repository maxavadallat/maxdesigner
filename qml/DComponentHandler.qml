import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DMouseArea {
    id: chRoot

    width: CONSTS.defaultPaneWidth
    height: CONSTS.defaultPaneHeight

    // Root Container
    property QtObject rootContainer: null
    // Parent Handler
    property QtObject parentHandler: null
    // Global Child Index Map
    property string childIndexMap: ""
    // Component Info
    property ComponentInfo componentInfo: null
    // Component Object
    property QtObject componentObject: null

    // Root Content Container
    property alias rootContentContainer: rootContentContainer

    // Child Handlers Container
    property alias childHandlersContainer: childHandlersContainer
    // Default Container
    default property alias defaultContainer: childHandlersContainer.children

    // Component Selected
    property bool selected: false

    // Min Size
    property int minWidth: 0
    property int minHeight: 0
    // MAx Size
    property int maxWidth: 8192
    property int maxHeight: 8192

    // Enable Size Overlay
    property bool enableSizeOverlay: true
    // Enable Pos Overlay
    property bool enablePosOverlay: true

    // Border Visibility
    property bool borderVisible: settingsController.borderVisible

    // Border Color
    property string borderColor: {
        // Check If Selected
        if (chRoot.selected) {
            return DStyle.colorBorderSelected;
        }

        // Check If Hovering
        if (chRoot.dropHovering) {
            // Check if Hover OK
            if (chRoot.dropHoverOK) {
                return DStyle.colorBorderHoverOK;
            }

            return DStyle.colorBorderHoverNOK;
        }

        // Check If Borders Visible
        if (!chRoot.borderVisible || !chRoot.updateComponentInfoEnabled) {
            return "transparent";
        }

        // Check If Focused
        if (chRoot.componentInfo !== null && propertiesController.focusedComponent === chRoot.componentInfo) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    // Border Margins
    property int borderMargins: 0

    property bool rootHandler: false
    property bool mainDrag: false

    // Enable Drag
    property bool enableDrag: true
    // Enable Pan By Keys
    property bool enablePanByKeys: true
    // Enable Resizd
    property bool enableResize: true
    // Set Focus On resize
    property bool setFocusOnResize: false

    // Resize Left Enabled
    property bool resizeLeftEnabled: true
    // Resize Top Enabled
    property bool resizeTopEnabled: true
    // Resize Right Enabled
    property bool resizeRightEnabled: true
    // Resize Bottom Enabled
    property bool resizeBottomEnabled: true

    // Manual Resize Flag
    property bool manualResize: false

    // Component Layout
    property string componentLayout: ""//componentInfo.layoutBase()  // Column, Row, Flow

//    // Layout Width
//    property int layoutWidth: updateHorizontalLayout()
//    // Layout Height
//    property int layoutHeight: updateVerticalLayout()
//    // Layout Spacing
//    property int layoutSpacing: updateLayoutSpacing()

    // Child Handlers Count
    property int count: childHandlersContainer.children.length

    // Hover Child Item
    property QtObject hoverChildItem: rootContainer ? getHoveringHandler(dropArea.drag.x, dropArea.drag.y, rootContainer.rootComponentHandler) : null

    // Drop Hovering
    property bool dropHovering: rootContainer ? (rootContainer.hoverHandler === chRoot) : false
    // Drop OK
    property bool dropHoverOK: false

    // Update Component Info Enabled
    property bool updateComponentInfoEnabled: false

    // Properties Controller Connections
    property Connections propertiesControllerConnections: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Check Component Info
            if (chRoot.componentInfo !== null && chRoot.componentInfo === propertiesController.focusedComponent) {
                // Set Focus
                chRoot.focus = true;
            }
        }

        // ...
    }

    // Component Info Connections
    property Connections componentInfoConnections: Connections {
        target: chRoot.componentInfo

        onOwnPropertyAdded: {
            console.log("#### DComponentHandler.componentInfoConnections.onOwnPropertyAdded - aName: " + aName);

            // ...

            // Emit Rebuild Content Signal
            chRoot.rootContainer.rebuildContent();
        }

        onOwnPropertyRemoved: {
            console.log("#### DComponentHandler.componentInfoConnections.onOwnPropertyRemoved - aName: " + aName);

            // ...

            // Emit Rebuild Content Signal
            chRoot.rootContainer.rebuildContent();
        }

        onNeedRefresh: {
            console.log("#### DComponentHandler.componentInfoConnections.onNeedRefresh");

            // ...

            // Emit Rebuild Content Signal
            chRoot.rootContainer.rebuildContent();
        }

        // On Child Added
        onChildAdded: {
            console.log("DComponentHandler.componentInfoConnections.onChildAdded - aIndex: " + aIndex);

            // Get Child Info
            var newChildInfo = chRoot.componentInfo.childInfo(aIndex);

            // Create Component Object
            var newComponentObject = createComponentObject(newChildInfo, newHandlerDummyParent, true);

            // Add Compoennt Object
            addComponentObject(aIndex, chRoot.componentObject, newComponentObject, newChildInfo.posX, newChildInfo.posY);

            // Create Component Handler
            var newComponentHandler = createComponentHandler(newComponentObject, newChildInfo, newHandlerDummyParent);

            // Add Compoennt Handler
            addComponentHandler(aIndex, chRoot, newComponentHandler);

            // ...
        }

        // On Child Moved Slot
        onChildMoved: {
            console.log("DComponentHandler.componentInfoConnections.onChildMoved - aParentComponent: " +  aParentComponent.componentPath + " - aIndex: " + aIndex + " - aTargetComponent: " + aTargetComponent.componentPath + " - aTargetIndex: " + aTargetIndex);

            // Check Parent & Target Component Info
            if (aParentComponent === aTargetComponent) {
                // Move Child Component Object
                moveComponentObject(aIndex, aTargetIndex);
                // Move Child Component Handler
                moveComponentHandler(aIndex, aTargetIndex);

            } else {
                // Get Target Component Handler From Target Component Info
                var targetComponentHandler = aTargetComponent.componentHandler;

                console.log("DComponentHandler.componentInfoConnections.onChildMoved - targetComponentHandler: " + targetComponentHandler.componentInfo.componentPath);

                // Get Target Component Object Parent
                var targetComponentObject = targetComponentHandler.componentObject;

                console.log("DComponentHandler.componentInfoConnections.onChildMoved - componentPath: " + chRoot.componentInfo.componentPath);

                // Remove Component Handler
                removeComponentHandler(aIndex);

                // Take Component Object
                var componentObject = takeComponentObject(aIndex);

                // Insert Component Object
                targetComponentHandler.addComponentObject(aTargetIndex, targetComponentObject, componentObject, 4, 4);

                // Get Target Component Child Info
                var targetComponentInfo = aTargetComponent.childInfo(aTargetIndex);

                // Create New Handler For The Moved Child Component Object
                var newComponentHandler = targetComponentHandler.createComponentHandler(componentObject, targetComponentInfo, null);

                // Add Component Handler
                targetComponentHandler.addComponentHandler(aTargetIndex, targetComponentHandler, newComponentHandler);

                // ...
            }
        }

        // On Child Removed Slot
        onChildRemoved: {
            //console.log("DComponentHandler.componentInfoConnections.onChildRemoved - aIndex: " + aIndex);

            // No Need, Taken Care By onChildAboutToBeRemoved

            // ...
        }

        // On Child About To Be Removed Slot
        onChildAboutToBeRemoved: {
            //console.log("DComponentHandler.componentInfoConnections.onChildAboutToBeRemoved");

            // Chek Component Object
            if (chRoot.componentObject) {
                // Destroy Component Object
                chRoot.componentObject.destroy();
            }

            // Destroy Handler
            chRoot.destroy();
        }

        // On Pos X Changed Slot
        onPosXChanged: {
            // Check Component Object Position
            if (chRoot.componentObject !== null && chRoot.componentObject.x !== aPosX && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.componentObject.x = aPosX;
            }
        }

        // On Pos Y Changed Slot
        onPosYChanged: {
            // Check Component Object Position
            if (chRoot.componentObject !== null && chRoot.componentObject.y !== aPosY && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.componentObject.y = aPosY;
            }
        }

        // On Pos Z Changed Slot
        onPosZChanged: {
            // Check Component Object Position
            if (chRoot.componentObject !== null && chRoot.componentObject.z !== aPosZ && chRoot.updateComponentInfoEnabled) {
                // Set Positin
                chRoot.componentObject.z = aPosZ;
            }
        }

        // On Width Changed Slot
        onWidthChanged: {
            // Check Component Object Width
            if (chRoot.componentObject !== null && chRoot.componentObject.width !== aWidth && chRoot.updateComponentInfoEnabled) {
                // Set Component Object Width
                chRoot.componentObject.width = aWidth;

                // Check If Root
                if (chRoot.componentInfo.isRoot) {
                    // Emit Component Width Changed Signal
                    chRoot.rootContainer.componentWidthChanged(aWidth);
                }
            }
        }

        // On Height Changed Slot
        onHeightChanged: {
            // Check Component Object Height
            if (chRoot.componentObject !== null && chRoot.componentObject.height !== aHeight && chRoot.updateComponentInfoEnabled) {
                // Set Component Object Height
                chRoot.componentObject.height = aHeight;

                // Check If Root
                if (chRoot.componentInfo.isRoot) {
                    // Emit Component Height Changed Signal
                    chRoot.rootContainer.componentHeightChanged(aHeight);
                }
            }
        }

        // On Layer VisibilityChanged Slot
        onLayerVisibleChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                //console.log("DComponentHandler.componentInfoConnections.onLayerVisibleChanged - aLayerVisible: " + aLayerVisible);
                // Set Component Object Visibility
                chRoot.componentObject.visible = aLayerVisible;
            }
        }

        // Left Anchor Changed Slot
        onAnchorsLeftChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Left Anchor
                chRoot.componentObject.anchors.left = parseAnchors(aLeft, true);
            }
        }

        // Left Anchor Margin Changed Slot
        onAnchorsLeftMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Left Anchor Margin
                chRoot.componentObject.anchors.leftMargin = aMargin;
            }
        }

        // Right Anchor Changed Slot
        onAnchorsRightChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Right Anchor
                chRoot.componentObject.anchors.right = parseAnchors(aRight, true);
            }
        }

        // Right Anchor Margin Changed Slot
        onAnchorsRightMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Right Margin
                chRoot.componentObject.anchors.rightMargin = aMargin;
            }
        }

        // Top Anchor Changed Slot
        onAnchorsTopChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Top
                chRoot.componentObject.anchors.top = parseAnchors(aTop, true);
            }
        }

        // Top Anchor Margin Changed Slot
        onAnchorsTopMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Top Margin
                chRoot.componentObject.anchors.topMargin = aMargin;
            }
        }

        // Bottom Anchor Changed Slot
        onAnchorsBottomChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Bottom
                chRoot.componentObject.anchors.bottom = parseAnchors(aBottom, true);
            }
        }

        // Bottom Anchor Margin Changed Slot
        onAnchorsBottomMarginChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Bottom Margin
                chRoot.componentObject.anchors.bottomMargin = aMargin;
            }
        }

        // Anchor Margin Changed Slot
        onAnchorsMarginsChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Margins
                chRoot.componentObject.anchors.margins = aMargins;
            }
        }

        // Fill Anchor Changed Slot
        onAnchorsFillChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Fill
                chRoot.componentObject.anchors.fill = parseAnchors(aFill, false);
            }
        }

        // Center Anchor Changed Slot
        onAnchorsCenterInChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Center In
                chRoot.componentObject.anchors.centerIn = parseAnchors(aCenterIn, false);
            }
        }

        // Horizontal Center Anchor Changed Slot
        onAnchorsHorizontalCenterChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Horizontal Center
                chRoot.componentObject.anchors.horizontalCenter = parseAnchors(aHorizontalCenter, true);
            }
        }

        // Vertical Center Anchor Changed Slot
        onAnchorsVerticalCenterChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Vertical Center
                chRoot.componentObject.anchors.verticalCenter = parseAnchors(aVerticalCenter, true);
            }
        }

        // Horizontal Center Anchor Offset Changed Slot
        onAnchorsHorizontalOffsetChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Horizontal Center Offset
                chRoot.componentObject.anchors.horizontalCenterOffset = aOffset;
            }
        }

        // Vertical Center Anchor Offset Changed Slot
        onAnchorsVerticalOffsetChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Anchors Vertical Center Offset
                chRoot.componentObject.anchors.verticalCenterOffset = aOffset;
            }
        }

        // Component Property Changed Slot
        onComponentPropertyChanged: {
            // Check If Update Component Info Enabled
            if (chRoot.updateComponentInfoEnabled) {
                // Set Component Property
                chRoot.componentObject.__setProperty(aName, aValue);
            }
        }


        // ...

    }

    // Component Object Connections
    property Connections componentObjectConnections: Connections {
        target: componentObject

        onXChanged: {
            // Set Handler Pos X
            chRoot.x = componentObject.x;

            // ...
        }

        onYChanged: {
            // Set Handler Pos Y
            chRoot.y = componentObject.y;

            // ...
        }

        onWidthChanged: {
            // Set Handler Width
            chRoot.width = componentObject.width;

            // ...
        }

        onHeightChanged: {
            // Set Handler Height
            chRoot.height = componentObject.height;

            // ...
        }

        // ...

    }

    // Drag Axis
    drag.axis: {
        // Check Component Info
        if (chRoot.componentInfo !== null) {

            // ...

        }

        return Drag.XandYAxis;
    }

    // Drag Threshold
    drag.threshold: CONSTS.defaultDragThreshold
    // Drag Filter Children
    drag.filterChildren: true

    clip: componentObject !== null ? componentObject.clip : false

    // Resize Pressed Signal
    signal resizePressed()

    Component.onDestruction: {
        // Set Update Component Info Enabled
        chRoot.updateComponentInfoEnabled = false;

        // ...

//        // Check Component Info
//        if (chRoot.componentInfo !== null) {
//            // Remove From Parent
//            chRoot.componentInfo.removeFromParent();
//        }
    }

    // On Component Info Changed Slot
    onComponentInfoChanged: {
        // Check Component Info
        if (chRoot.componentInfo !== null) {
            // Set Container/Handler
            chRoot.componentInfo.componentHandler = chRoot;
        }
    }

    // On Pressed Slot
    onPressed: {
        // Check If Drag Enabled
        if (chRoot.enableDrag) {
            // Set Drag Target
            drag.target = chRoot.componentObject;
        }
    }

    // On Released Slot
    onReleased: {
        // reset Drag Target
        drag.target = undefined;
    }

    // On Focus Changed Slot
    onFocusChanged: {
        //console.log("DComponentHandler.onFocusChanged - focus: " + chRoot.focus);

        // Check Focus
        if (chRoot.focus && chRoot.componentInfo !== null) {
            // Set Focused Compoenent
            propertiesController.focusedComponent = chRoot.componentInfo;
        }

        // ...
    }

    // Keys Pressed Slot
    Keys.onPressed: {
        // Switch Event Key
        switch (event.key) {
            case Qt.Key_Left:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (enablePanByKeys && event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.y += CONSTS.componentMoveStep;
                }
            break;
        }
    }

    // Keys Released Slot
    Keys.onReleased: {
        // Switch Event Key
        switch (event.key) {
            case Qt.Key_Backspace:
            case Qt.Key_Delete:
                // Check Parent Container
                if (chRoot.componentInfo !== null) {
                    // Remove Child Component
                    chRoot.componentInfo.removeFromParent();
                } else {
                    // Destroy
                    chRoot.destroy();
                }
            break;

            case Qt.Key_N:
                // Check Root Component Container
                if (chRoot.rootContainer !== null) {
                    // Toggle Nodes
                    chRoot.rootContainer.toggleNodePane();
                }
            break;

            case Qt.Key_Escape:
                // Check Compontn Info Parent
                if (chRoot.componentInfo !== null && chRoot.componentInfo.componentParent !== null) {
                    // Set Focused Component
                    propertiesController.focusedComponent = chRoot.componentInfo.componentParent;
                }
            break;

            case Qt.Key_Left:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.x -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Right:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.x += CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Up:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.y -= CONSTS.componentMoveStep;
                }
            break;

            case Qt.Key_Down:
                // Check Auto repeat
                if (enablePanByKeys && !event.isAutoRepeat) {
                    // Move Left
                    chRoot.componentObject.y += CONSTS.componentMoveStep;
                }
            break;

            default:
                //console.log("DComponentHandler.Keys.onReleased - key: " + event.key);
            break;
        }
    }

    // On Hover Child Item Changed
    onHoverChildItemChanged: {
        //console.log("DComponentHandler.onHoverChildItemChanged - hoverChildItem: " + chRoot.hoverChildItem);

        // Check Hover Child Item
        if (chRoot.hoverChildItem !== null) {
            //console.log("DComponentHandler.onHoverChildItemChanged - hoverChildItem: " + hoverChildItem.componentInfo.componentPath);

            // Set Hover Handler
            chRoot.rootContainer.hoverHandler = chRoot.hoverChildItem;

        // Check If Contains Drag
        } else if (dropArea.containsDrag) {
            // Set Hover Container
            chRoot.rootContainer.hoverHandler = chRoot;
        }

        // Check Hover Handler
        if (chRoot.rootContainer.hoverHandler !== null) {
            // Check Drag Source
            chRoot.rootContainer.hoverHandler.checkDragSource();
        }
    }

    // On Pos X Changed Slot
    onXChanged: updateComponentPosX(chRoot.x)

    // On Pos Y Changed Slot
    onYChanged: updateComponentPosY(chRoot.y)

    // On Width Changed Slot
    onWidthChanged: updateComponentWidth(chRoot.width)

    // On Height Changed Slot
    onHeightChanged: updateComponentHeight(chRoot.height)

    // Update Component Pos X
    function updateComponentPosX(posX) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled && chRoot.componentInfo !== null) {
            // Check If Root
            if (!chRoot.componentInfo.isRoot) {
                // Check Pos X
                if (chRoot.componentInfo.posX !== posX) {

                    // TODO: Check For Bindings

                    // Set Pos X
                    chRoot.componentInfo.setPosX(posX);
                }
            }
        }
    }

    // Update Component Pos Y
    function updateComponentPosY(posY) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled && chRoot.componentInfo !== null) {
            // Check If Root
            if (!chRoot.componentInfo.isRoot) {
                // Check Pos X
                if (chRoot.componentInfo.posY !== posY) {

                    // TODO: Check For Bindings

                    // Set Pos Y
                    chRoot.componentInfo.setPosY(posY);
                }
            }
        }
    }

    // Update Component Width
    function updateComponentWidth(width) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled && chRoot.componentInfo !== null) {
            // Check Width
            if (chRoot.componentInfo.width !== width) {

                // TODO: Check For Bindings

                // Set Width
                chRoot.componentInfo.setWidth(width);
            }
        }
    }

    // Update Component Height
    function updateComponentHeight(height) {
        // Check Upadte Component Info Enabled
        if (chRoot.updateComponentInfoEnabled && chRoot.componentInfo !== null) {
            // Check Height
            if (chRoot.componentInfo.height !== height) {

                // TODO: Check For Bindings

                // Set Width
                chRoot.componentInfo.setHeight(height);
            }
        }
    }

    // Array Move
    function arrayMove(ref, from, to) {
        var element = ref.array[from];
        ref.array.splice(from, 1);
        ref.array.splice(to, 0, element);
    }

    // Set Anchoring
    function setAnchoring() {
        // Check Component Info
        if (chRoot.componentInfo !== null && !chRoot.componentIsRoot) {
            console.log("DComponentHandler.setAnchoring - path: " + chRoot.componentInfo.componentPath);

            // Set Anchor Fill
            if (chRoot.componentInfo.anchorsFill !== "") {
                // Set Fill Anchor
                chRoot.anchors.fill = parseAnchors(chRoot.componentInfo.anchorsFill, false);
            } else if (chRoot.componentInfo.anchorsCenterIn !== "") {
                // Set Center In Anchor
                chRoot.anchors.centerIn = parseAnchors(chRoot.componentInfo.anchorsCenterIn, false);
            } else {

                // Check Anchor Horizotal Center
                if (chRoot.componentInfo.horizontalCenter !== "") {
                    // Set Horizontal Center
                    chRoot.anchors.horizontalCenter = parseAnchors(chRoot.componentInfo.horizontalCenter, true);
                } else {
                    // Set Left Anchor
                    chRoot.anchors.left = parseAnchors(chRoot.componentInfo.anchorsLeft, true);
                    // Set Right Anchor
                    chRoot.anchors.right = parseAnchors(chRoot.componentInfo.anchorsRight, true);
                }

                // Check Anchor Vertical Center
                if (chRoot.componentInfo.verticalCenter !== "") {
                    // Set Vertical Center
                    chRoot.anchors.verticalCenter = parseAnchors(chRoot.componentInfo.verticalCenter, true);
                } else {
                    // Set Top Anchor
                    chRoot.anchors.top = parseAnchors(chRoot.componentInfo.anchorsTop, true);
                    // Set Bottom Anchor
                    chRoot.anchors.bottom = parseAnchors(chRoot.componentInfo.anchorsBottom, true);
                }
            }

            // Check Margins
            if (chRoot.componentInfo.anchorsMargins !== "") {
                // Set Margins
                chRoot.anchors.margins = Number(chRoot.componentInfo.anchorsMargins);
            } else {
                // Set Left, Right, Top, Botton Margin
                chRoot.anchors.leftMargin = Number(chRoot.componentInfo.anchorsLeftMargin);
                chRoot.anchors.rightMargin = Number(chRoot.componentInfo.anchorsRightMargin);
                chRoot.anchors.topMargin = Number(chRoot.componentInfo.anchorsTopMargin);
                chRoot.anchors.bottomMargin = Number(chRoot.componentInfo.anchorsBottomMargin);
            }

            // Set Horizontal Center Ofset
            chRoot.anchors.horizontalCenterOffset = Number(chRoot.componentInfo.anchorsHorizontalOffset);
            // Set Vertical Center Offset
            chRoot.anchors.verticalCenterOffset = Number(chRoot.componentInfo.anchorsVerticalOffset);
        }
    }

    // Reset Anchoring
    function resetAnchoring() {
        // Check Component Info
        if (chRoot.componentInfo !== null) {
            // Reset Anchoring
            chRoot.componentInfo.resetAnchors();
        }
    }

    // Parse Anchors
    function parseAnchors(anchorString, needPoint) {
        // Get Anchor Elements
        var anchorElements = anchorString.split(".");

        //console.log("DComponentHandler.parseAnchors - anchorElements: " + anchorElements);

        // Get Anchor Target
        var anchorTarget = anchorElements[0];

        // Check Anchor Target
        if (anchorTarget === "") {
            //console.log("DComponentHandler.parseAnchors - Clearing Anchor");
            return undefined;
        }

        // Get Anchoring Point
        var anchorPoint = anchorElements[1];

        // Check Anchor Target
        if (anchorTarget === "parent") {

            // Set Anchor Target - Morph To Object
            anchorTarget = chRoot.parentHandler.componentObject;

        } else {

            // Get Component Info By ID
            var targetComponentInfo = chRoot.componentInfo.getChildObject(anchorTarget);

            // TODO: Double Check!!

            // Get Anchor Target
            anchorTarget = targetComponent !== null ? targetComponent.componentHandler.componentObject : undefined;
        }

        // Check Anchor Target
        if (anchorTarget === null || anchorTarget === undefined) {
            console.warn("DComponentHandler.parseAnchors - NO SUCH TARGET!");
            return undefined;
        }

        //console.log("DComponentHandler.parseAnchors - anchorTarget: " + anchorTarget);

        // Check Anchor Point
        if (anchorPoint === "" || anchorPoint === undefined) {
            // Check If Need Anchoring Point
            if (needPoint) {
                console.warn("DComponentHandler.parseAnchors - NO ANCHOR POINT DEFINED!");
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
                console.warn("DComponentHandler.parseAnchors - anchorPoint: " + anchorPoint + " - INVALID ANCHOR POINT!");
            return undefined;
        }

        return anchorPoint;
    }

    // Get Hovering Handler
    function getHoveringHandler(posX, posY, parentHandler) {
        // Check If Contains Drag
        if (!dropArea.containsDrag) {
            return null;
        }

        // Check Parent Container
        if (parentHandler === undefined) {
            console.log("DComponentHandler.dropArea.getHoveringContainer - INVALID PARENT CONTAINER!!!");
            return null;
        }

        // Set Drop Pos X
        chRoot.rootContainer.hoverPosX = posX;
        // Set Drop Pos Y
        chRoot.rootContainer.hoverPosY = posY;

        //console.log("DComponentHandler.getHoveringHandler - parentHandler: " + parentHandler.componentInfo.componentName + " - pos: " + posX + ":" + posY);

        // Init Handler Child Found
        var hChildFound = parentHandler.childHandlersContainer.childAt(posX, posY);
        // Init Parent Handler Next Child Found
        var hNextChildFound = null;

        //console.log("DComponentHandler.getHoveringHandler - phChildFound");

        // Check For Children
        if (hChildFound && hChildFound.count > 0) {
            // Test For Child Hit
            hNextChildFound = getHoveringHandler(posX - hChildFound.x, posY - hChildFound.y, hChildFound);
        }

        return hNextChildFound !== null ? hNextChildFound : hChildFound;
    }

    // Check Drag Source
    function checkDragSource() {

        // Check Drag Source
        if (chRoot.rootContainer.dragSource === null) {
            // Set Drop Hover OK
            chRoot.dropHoverOK = false;
        }

        // Check Drag Source Against Own Component Info
        if (chRoot.rootContainer.dragSource === chRoot.componentInfo) {
            // Set Drop Hover OK
            chRoot.dropHoverOK = false;
        }

        // TODO: More Checks!!

        // Check Drag Key
        if (chRoot.rootContainer.dragKey !== CONSTS.newComponentDragKey) {
            // Set Drop Hover OK
            chRoot.dropHoverOK = false;
        }

        // ...

        // Set Drop Hover OK
        chRoot.dropHoverOK = true;
    }

    // Make Drop
    function makeDrop(drop) {
        // Check Drop OK
        if (!chRoot.dropHoverOK) {
            console.warn("DComponentHandler.makeDrop - NOT ACCEPTED!!");
            return;
        }

        // Check Component Info
        if (chRoot.componentInfo) {
            // Clone New Object
            var newComponent = drop.source.clone();

            // Set Pos X
            newComponent.setPosX(rootContainer.hoverPosX - CONSTS.componentItemWidth * 0.5);
            // Set Pos Y
            newComponent.setPosY(rootContainer.hoverPosY - CONSTS.componentItemHeight * 0.5);

            // TODO: Update Set Pos According New Component Size

            // Append Child
            chRoot.componentInfo.addChild(newComponent);

            // Child Added Signal Will Be Called

            // ...
        }

        // ...

    }

    // Create Component Object
    function createComponentObject(componentInfo, parent, createChildren) {
        // Check Component Info
        if (componentInfo !== null) {
            // Generate Live Code
            var cFileName = propertiesController.currentProject.generateLiveCode(componentInfo, createChildren);

            // CLEAR THE FUCKING QML COMPONENT CACHE BECAUSE THEY FUCKED IT UP! BUT THIS WILL CAUSE A CRASH AT SHUTDOWN!!!
            //mainController.clearQMLComponentCache();

            // Create Component
            var component  = Qt.createComponent("file://" + cFileName);

            // Init New Component Object
            var newComponentObject = null;

            // Check Status
            if (component.status === Component.Ready) {
                // Create New Root Object
                newComponentObject = component.createObject(parent);

                // Remove Live Temp File
                //propertiesController.currentProject.removeLiveTempFile(cFileName);

            } else {
                console.error("DComponentHandler.createComponentObject - ERROR CREATING NEW COMPONENT!! - error: " + component.errorString());
                return null;
            }

            // Check New Component Object
            if (newComponentObject === null) {
                console.error("DComponentHandler.createComponentObject - ERROR CREATING NEW COMPONENT OBJECT!! - error: " + component.errorString());
                return null;
            }

            return newComponentObject;

        } else {
            console.warn("DComponentHandler.createComponentObject - NULL COMPONENT INFO");
        }
    }

    // Add Component Object
    function addComponentObject(childIndex, parentObject, componentObject, posX, posY) {
        // Check Parent Object
        if (parentObject === null) {
            return;
        }

        // Check Component Object
        if (componentObject === null) {
            return;
        }

        console.log("DComponentHandler.addComponentObject - __childMap: " + componentObject.__childMap);

        // Get Parent Object Child Count
        var pocCount = parentObject.children.length;

        console.log("DComponentHandler.addComponentObject - pocCount: " + pocCount);

        // Iterate Through Children
        for (var i=pocCount-1; i>=childIndex; i--) {
            // Set Parent
            parentObject.children[i].parent = handlersDummyParent;
        }

        // Set New Component Object Parent
        componentObject.parent = parentObject;

        // Set Pos
        componentObject.x = posX;
        componentObject.y = posY;

        // Get Taken Child Component Objects Count
        var tccoCount = handlersDummyParent.children.length;

        // Put Taken Chilren
        for (var j=tccoCount-1; j>=0; j--) {
            // Set Parent
            handlersDummyParent.children[j].parent = parentObject;
        }

        // ...
    }

    // Take Component Object
    function takeComponentObject(childIndex) {
        // Check Component Object
        if (chRoot.componentObject === null) {
            return;
        }

        // Get Componet Handlers Count
        var chCount = childHandlersContainer.children.length;

        // Check Child Index
        if (childIndex >= 0 && childIndex < chCount) {
            // Get Component Object
            var componentObject = childHandlersContainer.children[childIndex].componentObject;

            // Set Dummy Parent
            componentObject.parent = newHandlerDummyParent;

            return componentObject;
        }

        return null;
    }

    // Take Component Handler
    function takeComponentHandler(childIndex) {
        // Get Componet Handlers Count
        var chCount = childHandlersContainer.children.length;

        // Check Child Index
        if (childIndex >= 0 && childIndex < chCount) {

            // Get Component Handler
            var componentHandler = childHandlersContainer.children[childIndex];
            // Set Dummy Parent
            componentHandler.parent = newHandlerDummyParent;

            return componentHandler;
        }

        return null;
    }

    // Remove Component Handler
    function removeComponentHandler(childIndex) {
        // Get Componet Handlers Count
        var chCount = childHandlersContainer.children.length;

        // Check Child Index
        if (childIndex >= 0 && childIndex < chCount) {
            // Destroy
            childHandlersContainer.children[childIndex].destroy();
        }
    }

    // Create Component Handler
    function createComponentHandler(componentObject, componentInfo, parent) {
        // Check Component Object & Component Info
        if (componentObject === null) {
            console.warn("DComponentHandler.createComponentHandler - NULL COMPONENT OBJECT!!");
            return;
        }

        // Check Component Info
        if (componentInfo === null) {
            console.warn("DComponentHandler.createComponentHandler - NULL COMPONENT INFO!!");
            return;
        }

        console.log("DComponentHandler.createComponentHandler - path: " + componentInfo.componentPath);

        // Create New Component Handler
        var newComponentHandler = chRoot.rootContainer.componentHandlerFactory.createObject(newHandlerDummyParent);

        // Set Up Component Handler

        // Set Parent Handler
        newComponentHandler.parentHandler = chRoot;
        // Set Index Map
        newComponentHandler.childIndexMap = componentObject.__childMap;
        // Set Component Info
        newComponentHandler.componentInfo = componentInfo;
        // Set Component Object
        newComponentHandler.componentObject = componentObject;

        // Set Pos
        newComponentHandler.x = componentObject.x;
        newComponentHandler.y = componentObject.y;
        // Set Size
        newComponentHandler.width = componentObject.width;
        newComponentHandler.height = componentObject.height;

        // ...

        return newComponentHandler;
    }

    // Add Component Handler
    function addComponentHandler(childIndex, parentHandler, componentHandler) {
        // Check Component Handler
        if (componentHandler === null || componentHandler.componentInfo === null) {
            console.warn("DComponentHandler.addComponentHandler - INVALID COMPONENT HANDLER!!");
            return;
        }

        console.log("DComponentHandler.addComponentHandler - path: " + componentHandler.componentInfo.componentPath);

        // Get Component Handlers Count
        var chCount = parentHandler.childHandlersContainer.children.length;

        console.log("DComponentHandler.addComponentHandler - chCount: " + chCount);

        // Take Child Handlers
        for (var i=chCount-1; i>=childIndex; i--) {
            // Set Parent
            parentHandler.childHandlersContainer.children[i].parent = handlersDummyParent;
        }

        // Set Component Handler Parent
        componentHandler.parent = parentHandler.childHandlersContainer;

        // Set Update Component Info Enabled
        componentHandler.updateComponentInfoEnabled = true;

        // Get Taken Component Handlers Count
        var tchCount = handlersDummyParent.children.length;

        // Put Taken Child Handlers Back
        for (var j=tchCount-1; j>=0; j--) {
            // Set Parent For Child Handlers
            handlersDummyParent.children[j].parent = parentHandler.childHandlersContainer;
        }

        // ...
    }

    // Move Child Component Object
    function moveComponentObject(childIndex, targetIndex) {
        // Get Component Child Count
        var ccCount = chRoot.componentObject.children.length;

        // Get Bottom Index
        var bottomIndex = Math.min(childIndex, targetIndex);

//        console.log("DComponentHandler.moveComponentObject -     ccCount : " + ccCount);
//        console.log("DComponentHandler.moveComponentObject - bottomIndex : " + bottomIndex);

        // Init Temp Array For Child Containers
        var ccTemp = { "array": [] };

        // Move Child Containers To Dummy Parent
        for (var i=bottomIndex; i<ccCount; i++) {
            // Push To Temp Array
            ccTemp.array.push(chRoot.componentObject.children[bottomIndex]);
            // Set Item\s Parent to Dummy Parent
            chRoot.componentObject.children[bottomIndex].parent = handlersDummyParent;
        }

        // Move Items
        arrayMove(ccTemp, childIndex - bottomIndex, targetIndex - bottomIndex);

        // Move Back Rearranged Items To ContentContainer
        for (var n=0; n<ccTemp.array.length; n++) {
            // Set Parent
            ccTemp.array[n].parent = chRoot.componentObject;
        }

        // Clear Temp Array
        ccTemp.array.splice(0, ccTemp.array.length);
    }

    // Move Child Compoennt Handler
    function moveComponentHandler(childIndex, targetIndex) {
        // Get Component Handlers Count
        var chCount = chRoot.childHandlersContainer.children.length;

        // Get Bottom Index
        var bottomIndex = Math.min(childIndex, targetIndex);

//        console.log("DComponentHandler.moveComponentObject -     chCount : " + chCount);
//        console.log("DComponentHandler.moveComponentObject - bottomIndex : " + bottomIndex);

        // Init Temp Array For Child Containers
        var ccTemp = { "array": [] };

        // Move Child Containers To Dummy Parent
        for (var i=bottomIndex; i<chCount; i++) {
            // Push To Temp Array
            ccTemp.array.push(chRoot.childHandlersContainer.children[bottomIndex]);
            // Set Item\s Parent to Dummy Parent
            chRoot.childHandlersContainer.children[bottomIndex].parent = handlersDummyParent;
        }

        // Move Items
        arrayMove(ccTemp, childIndex - bottomIndex, targetIndex - bottomIndex);

        // Move Back Rearranged Items To ContentContainer
        for (var n=0; n<ccTemp.array.length; n++) {
            // Set Parent
            ccTemp.array[n].parent = chRoot.childHandlersContainer;
        }

        // Clear Temp Array
        ccTemp.array.splice(0, ccTemp.array.length);
    }

//    // Update Layout Spacing
//    function updateLayoutSpacing() {

//    }

//    // Update Horizontal Layout
//    function updateHorizontalLayout() {

//    }

//    // Update Vertical Layout
//    function updateVerticalLayout() {

//    }

    // Border Rectangle
    DRectangle {
        id: borderRectangle
        anchors.fill: parent
        anchors.margins: chRoot.borderMargins
        color: "transparent"
        //color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.1)
        border.color: chRoot.borderColor
        radius: 0
    }

    // Dummy Parent For New Handler Child
    Item {
        id: newHandlerDummyParent
        visible: false
    }

    // Dummy Parent For Child Handlers
    Item {
        id: handlersDummyParent
        visible: false
    }

    // Root
    Item {
        id: rootContentContainer
        anchors.fill: parent
        clip: settingsController.clipComponentRoot

        // ...
    }

    // THIS IS ONLY FOR THE drag.filterChildren to work
    MouseArea {
        id: dragHelper
        anchors.fill: parent
        onClicked: {
            // Set Focused Component
            propertiesController.focusedComponent = chRoot.componentInfo;
        }
    }

    // Drop Area For Child Components
    DDropArea {
        id: dropArea
        anchors.fill: parent

        onEntered: {
            // Set Drag Source
            chRoot.rootContainer.dragSource = drag.source;
            // Set Drag Key
            chRoot.rootContainer.dragKey = drag.keys[0];

            // Accept Drag
            drag.accept();

            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler === null) {
                // Set Initial Hover Container
                chRoot.rootContainer.hoverHandler = chRoot;
            }

            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler !== null) {
                // Check Drag Source by Current Hovered Container
                chRoot.rootContainer.hoverHandler.checkDragSource(chRoot.dragSource, chRoot.dragKey);
            }
        }

        onDropped: {
            // Check Hover Container
            if (chRoot.rootContainer.hoverHandler !== null) {
                // Make The Drop
                chRoot.rootContainer.hoverHandler.makeDrop(drop);
                // Reset Hover Container
                chRoot.rootContainer.hoverHandler = null;
            }
        }

        onExited: {
            // Reset Drop Hover OK
            chRoot.dropHoverOK = false;
            // Reset Hover Container
            chRoot.rootContainer.hoverHandler = null;
            // Reset Drag Source
            chRoot.rootContainer.dragSource = null;
            // Reset Drag Key
            chRoot.rootContainer.dragKey = "";
        }
    }

    // Child Handlers Container
    Item {
        id: childHandlersContainer
        anchors.fill: parent
        clip: settingsController.clipComponentRoot && chRoot.componentInfo !== null && chRoot.componentInfo.isRoot

        // ...
    }

    // Component Label
    DText {
        id: componentLabel
        anchors.centerIn: parent
        color: "white"
        visible: settingsController.componentNamesVisible && chRoot.updateComponentInfoEnabled
        opacity: CONSTS.componentNamesOpacity
        font.pixelSize: 48 // TODO: Manage Size
        text: chRoot.componentInfo ? chRoot.componentInfo.componentName : ""
    }

    // Position Indicator
    DPosIndicator {
        id: posIndicator
        anchors.left: parent.left
        anchors.top: parent.top
        enabled: enablePosOverlay
        posX: chRoot.x
        posY: chRoot.y
    }

    // Size Indicator
    DSizeIndicator {
        id: sizeIndicator
        anchors.centerIn: parent
        enabled: enableSizeOverlay
        sizeW: chRoot.width
        sizeH: chRoot.height
    }

    // Resize Area - Top Left
    DResizeArea {
        id: topLeftResizer
        resizePos: "topLeft"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeLeftEnabled && chRoot.resizeTopEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Top Center
    DResizeArea {
        id: topResizer
        resizePos: "top"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeTopEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Top Right
    DResizeArea {
        id: topRightResizer
        resizePos: "topRight"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeTopEnabled && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Left
    DResizeArea {
        id: leftResizer
        resizePos: "left"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeLeftEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Right
    DResizeArea {
        id: rightResizer
        resizePos: "right"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Left
    DResizeArea {
        id: bottomLeftResizer
        resizePos: "bottomLeft"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled && chRoot.resizeLeftEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Center
    DResizeArea {
        id: bottomResizer
        resizePos: "bottom"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }

    // Resize Area - Bottom Right
    DResizeArea {
        id: bottomRightResizer
        resizePos: "bottomRight"
        target: chRoot.componentObject
        enabled: chRoot.enableResize && chRoot.resizeBottomEnabled && chRoot.resizeRightEnabled

        onPressed: {
            // Check Main drag
            if (mainDrag) {
                // Emit Resize Pressed Signal
                chRoot.resizePressed();
            }

            // Check Set Focus On Resize
            if (chRoot.setFocusOnResize) {
                // Set Focus
                chRoot.focus = true;
            }
        }
    }
}
