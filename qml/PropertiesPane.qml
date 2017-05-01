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
                // Reset Editors
                idEditor.text = "";
                objectNameEditor.text = "";

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

                // ...

            } else {
                // Set ID Editor Text
                idEditor.text = propertiesController.focusedComponent.componentID;
                // Set Object Name Editor Text
                objectNameEditor.text = propertiesController.focusedComponent.componentObjectName;

                // Check Focused Component
                if (propertiesController.focusedComponent.componentCategory === "NonVisual") {
                    // Hide Size And Pos Section
                    sizeAndPosSection.hide();
                    // Hide Anchors Section
                    anchorsSection.hide();
                } else {
                    // Check Section State
                    if (sizeAndPosSection.state === sizeAndPosSection.stateHidden) {
                        // Set Closed State
                        sizeAndPosSection.close();
                    }
                }

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

                // Set Section Open State
                ownPropertiesSection.open();

                // ...
            }
        }
    }

    property Connections focusedComponentConnection: Connections {
        target: propertiesController.focusedComponent

    }

    property int namesColumnWidth: propertiesPaneRoot.width * CONSTS.defaultNamesColumnWidth

    title: "Properties" + (propertiesController.focusedComponent ? (" - " + propertiesController.focusedComponent.componentName) : "")

    creationWidth: settingsController ? settingsController.propertiesPaneWidth : 300
    creationHeight: settingsController ? settingsController.propertiesPaneHeight : 600

    minWidth: 300
    minHeight: parent ? parent.height * 0.6 : 600

    maxWidth: parent ? parent.width * 0.5 : 2000
    maxHeight: parent ? parent.height / DStyle.defaultMargin * 2 : 2000

    enablePaneContent: propertiesController.focusedComponent !== null

    setFocusOnResize: false

    //topMouseAreaVisible: true

    hideToSide: hideToRight

    borderColor: DStyle.colorBorder

    state: stateCreate

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

    // ID Row
    Row {
        id: idRow
        spacing: 2

        DText {
            id: idTitle
            width: objectNameTitle.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "id:"
        }

        DTextInput {
            id: idEditor
            width: propertiesPaneRoot.contentWidth - idTitle.width - 2
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentID : ""

            onAccepted: {
                // Check Current Component ID
                if (propertiesController.cID !== newText) {
                    // Request New Component ID
                    propertiesController.requestCID(newText);
                }
            }
        }
    }

    // Object Name Row
    Row {
        id: objectNameRow
        spacing: 2

        DText {
            id: objectNameTitle
            //width: propertiesPaneRoot.contentWidth
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "objectName:"
        }

        DTextInput {
            id: objectNameEditor
            width: propertiesPaneRoot.contentWidth - objectNameTitle.width - 2
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentObjectName : ""

            onAccepted: {
                // Check Component Object Name
                if (propertiesController.cObjectName !== newText) {
                    // Request New Object Name
                    propertiesController.requestCObjectName(newText);
                }
            }
        }
    }

    // Spacer
    Item {
        width: propertiesPaneRoot.contentWidth
        height: DStyle.defaultSpacing
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
}
