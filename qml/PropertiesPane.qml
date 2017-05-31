import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPane {
    id: propertiesPaneRoot

    width: 300
    height: 600

    property Connections propertiesControllerConnection: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Check Focused Component
            if (propertiesController.focusedComponent === null) {

                // Close All Sections
                importsSection.close();
                sizeAndPosSection.close();
                anchorsSection.close();
                ownPropertiesSection.close();
                signalsSection.close();
                slotsSection.close();
                functionsSection.close();
                statesSection.close();
                transitionsSection.close();

                // Set No Focused Component Container Opacity
                noFocusedComponentContainer.opacity = 1.0;

                // ...

            } else {
                // Set No Focused Component Container Opacity
                noFocusedComponentContainer.opacity = 0.0;

                // Check Focused Component
                if (propertiesController.focusedComponent.componentCategory === "NonVisual") {
                    // Hide Size And Pos Section
                    sizeAndPosSection.hide();
                    // Hide Anchors Section
                    anchorsSection.hide();

                } else {
                    // Show Size And Pos Section
                    sizeAndPosSection.open();

//                    // Check Section State
//                    if (sizeAndPosSection.state === sizeAndPosSection.stateHidden) {
//                        // Set Closed State
//                        sizeAndPosSection.close();
//                    }

                    // Check If Root
                    if (propertiesController.focusedComponent.isRoot) {
                        // Hide Anchors Section
                        anchorsSection.hide();
                    } else {
                        // Check Section State
                        if (anchorsSection.state === anchorsSection.stateHidden) {
                            // Set Closed State
                            anchorsSection.close();
                        }
                    }
                }

                // Check Focused Component
                checkFocusedComponent();

                // Set Section Open State
                ownPropertiesSection.open();

                // ...
            }
        }
    }

    property Connections focusedComponentConnection: Connections {
        target: propertiesController.focusedComponent

        onOwnPropertyAdded: {
            // Check Focused Component
            checkFocusedComponent();
        }

        onOwnPropertyRemoved: {
            // Check Focused Component
            checkFocusedComponent();
        }
    }

    property int namesColumnWidth: propertiesPaneRoot.width * CONSTS.defaultNamesColumnWidth

    title: "Properties" + (propertiesController.focusedComponent ? (" - " + propertiesController.focusedComponent.componentName) : "")

    creationWidth: settingsController ? settingsController.propertiesPaneWidth : 300
    creationHeight: settingsController ? settingsController.propertiesPaneHeight : 600

    minWidth: 360
    minHeight: parent ? parent.height * 0.6 : 600

    maxWidth: parent ? parent.width * 0.5 : 2000
    maxHeight: parent ? parent.height / DStyle.defaultMargin * 2 : 2000

    enablePaneContent: propertiesController.focusedComponent !== null

    setFocusOnResize: false

    hideToSide: hideToRight

    borderColor: DStyle.colorBorder

    state: stateCreate

    signal posXEditLaunch()
    signal posYEditLaunch()
    signal widthEditLaunch()
    signal heightEditLaunch()

    signal newImportLaunch()
    signal editImportsLaunch(var index)

    signal newPropertyLaunch()
    signal editPropertyLaunch(var index)

    signal editFormulaLaunch(var propertyName, var ownProperty)

    signal newSignalLaunch()
    signal editSignalLaunch(var index)

    signal newSlotLaunch()
    signal editSlotLaunch(var index)

    signal newFunctionLaunch()
    signal editFunctionLaunch(var index)

    signal newStateLaunch()
    signal editStateLaunch(var index)

    signal newTransitionLaunch()
    signal editTransitionLaunch(var index)

    signal stateSelectionLaunch()

    onWidthChanged: {
        // Check State
        if (propertiesPaneRoot.state === propertiesPaneRoot.stateShown) {
            // Store Properties Pane Width
            settingsController.propertiesPaneWidth = propertiesPaneRoot.width;
        }
    }

    onHeightChanged: {
        // Check State
        if (propertiesPaneRoot.state === propertiesPaneRoot.stateShown) {
            // Store Properties Pane Height
            settingsController.propertiesPaneHeight = propertiesPaneRoot.height;
        }
    }

    // Check Focused Component Properties
    function checkFocusedComponent() {
//        // Check If Has ID
//        if (propertiesController.focusedComponent.hasProperty("id")) {
//            // Set ID Editor Text
//            //idEditor.text = propertiesController.focusedComponent.componentID;
//            // Set ID Row height
//            idRow.height = idEditor.height;
//        } else {
//            // Reset Text
//            //idEditor.text = "";
//        }

//        // Check If Has Object Name
//        if (propertiesController.focusedComponent.hasProperty("objectName")) {
//            // Set Object Name Editor Text
//            //objectNameEditor.text = propertiesController.focusedComponent.componentObjectName;
//            // Set Object Name Row Height
//            objectNameRow.height = objectNameEditor.height;
//        } else {
//            // Reset Text
//            //objectNameEditor.text = "";
//        }

        // Check Focused Component
        if (!propertiesController.focusedComponent.hasProperty("state")) {
            // Hide Section
            statesSection.hide();
            // Hide Section
            transitionsSection.hide();
        } else {
            // Check Section State
            if (statesSection.state === statesSection.stateHidden) {
                // Set Section Closed State
                statesSection.close();
            }

            // Check Section State
            if (transitionsSection.state === transitionsSection.stateHidden) {
                // Set Section Closed State
                transitionsSection.close();
            }
        }
    }

    // ID Row
    Row {
        id: idRow
        height: propertiesController.focusedComponent && propertiesController.focusedComponent.hasProperty("id") ? idEditor.height : 0
        Behavior on height { DAnimation { } }
        visible: height > 0 && opacity > 0.0
        clip: true
        spacing: DStyle.defaultSpacing

        DText {
            id: idTitle
            width: objectNameTitle.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "id:"
        }

        DTextInput {
            id: idEditor
            width: propertiesPaneRoot.contentWidth - idTitle.width - DStyle.defaultSpacing
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentID : ""

            onAccepted: {
                // Request New Component ID
                propertiesController.requestCID(newText);
            }
        }
    }

    // Object Name Row
    Row {
        id: objectNameRow
        height: propertiesController.focusedComponent && propertiesController.focusedComponent.hasProperty("objectName") ? objectNameEditor.height : 0
        Behavior on height { DAnimation { } }
        visible: height > 0 && opacity > 0.0
        clip: true
        spacing: DStyle.defaultSpacing

        DText {
            id: objectNameTitle
            //width: propertiesPaneRoot.contentWidth
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "objectName:"
        }

        DTextInput {
            id: objectNameEditor
            width: propertiesPaneRoot.contentWidth - objectNameTitle.width - DStyle.defaultSpacing
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentObjectName : ""

            onAccepted: {
                // Request New Object Name
                propertiesController.requestCObjectName(newText);
            }
        }
    }

    // Tag Row
    Row {
        id: componentTagRow
        height: propertiesController.focusedComponent !== null ? componentTagEditor.height : 0
        Behavior on height { DAnimation { } }
        visible: height > 0 && opacity > 0.0
        clip: true
        spacing: DStyle.defaultSpacing

        DText {
            id: tagTitle
            width: objectNameTitle.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "tags:"
        }

        DTextInput {
            id: componentTagEditor
            width: propertiesPaneRoot.contentWidth - tagTitle.width - DStyle.defaultSpacing
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentTag : ""

            onAccepted: {
                // Set Component Tag
                propertiesController.setComponentTag(newText);
            }
        }
    }

    // Spacer
    Item {
        width: propertiesPaneRoot.contentWidth
        height: DStyle.defaultSpacing * 0.5
    }

    // Imports Section
    DImportsSection {
        id: importsSection
        width: propertiesPaneRoot.contentWidth
    }

    // Size & Pos Section
    DSizeAndPosSection {
        id: sizeAndPosSection
        width: propertiesPaneRoot.contentWidth
    }

    // Anchors Section
    DAnchorsSection {
        id: anchorsSection
        width: propertiesPaneRoot.contentWidth
    }

    // Own Properties Section
    DOwnPropertiesSection {
        id: ownPropertiesSection
        width: propertiesPaneRoot.contentWidth
        namesColumnWidth: propertiesPaneRoot.namesColumnWidth
    }

    // Signals Section
    DSignalsSection {
        id: signalsSection
        width: propertiesPaneRoot.contentWidth
    }

    // Slots Section
    DSlotsSection {
        id: slotsSection
        width: propertiesPaneRoot.contentWidth
    }

    // Functions Section
    DFunctionsSection {
        id: functionsSection
        width: propertiesPaneRoot.contentWidth
    }

    // States Section
    DStatesSection {
        id: statesSection
        width: propertiesPaneRoot.contentWidth
    }

    // Transitions Section
    DTransitionsSection {
        id: transitionsSection
        width: propertiesPaneRoot.contentWidth
    }

    // Base Properties Repeater
    DPropertiesSection {
        id: propertiesSection
        width: propertiesPaneRoot.contentWidth
        namesColumnWidth: propertiesPaneRoot.namesColumnWidth
    }

    DControl {
        id: noFocusedComponentContainer
        width: propertiesPaneRoot.width
        height: propertiesPaneRoot.height * 0.7 - propertiesPaneRoot.titleHeight

        DText {
            anchors.centerIn: parent
            text: "No Component Selected"
            font.pixelSize: DStyle.fontSizeXL
            opacity: 0.7
        }
    }
}
