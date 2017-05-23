import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

Item {
    id: mainRoot

    // Open Recent Files When Panes Are Shown
    property bool openRecentFilesOnShowFinished: false

    // Create New Component Root
    function createNewComponentRoot(componentInfo, width, height) {
        // Incubate Object
        var incubator = componentRootFactory.incubateObject(mainGrabArea);
        // Check Status
        if (incubator.status !== Component.Ready) {
            // Connect To Status Changed
            incubator.onStatusChanged = function(status) {
                // Check Status
                if (status === Component.Ready) {
                    //console.log("componentRootFactory - object: ", incubator.object, " ready!");
                    // Launch Root Component
                    launchComponentRoot(incubator.object, componentInfo, width, height);

                } else if (status === Component.Error) {
                    console.log("componentRootFactory - object: ", incubator.object, " ERROR: " + componentRootFactory.errorString());
                }
            }
        } else {
            //console.log("componentRootFactory - object: ", incubator.object, " immediately ready!");
            // Launch Root Component
            launchComponentRoot(incubator.object, componentInfo, width, height);
        }
    }

    // Launch Component Root
    function launchComponentRoot(object, componentInfo, width, height) {
        //console.log("launchComponentRoot - componentName: " + componentInfo.componentName + " - width: " + width + " - height: " + height);
        // Set Component Info
        object.componentInfo = componentInfo;

        // Set Creation Width & Height
        object.creationWidth = width > 0 ? width : CONSTS.defaultNonVisualComponentWidth;
        object.creationHeight = height > 0 ? height : CONSTS.defaultNonVisualComponentHeight;

        // Show
        object.show();
    }

    // Create New Asset Root Container
    function createNewAssetRoot(fileName) {

    }

    // Launch Asset Root Container
    function launchAssetRoot(object, fileName, width, height) {

    }

    // Create New Source Root Container
    function createNewSourceRoot(fileName) {

    }

    // Launch Source Container Root
    function launchSourceRoot(object, fileName, width, height) {

    }

    // Background Container
    Rectangle {
        id: bgContainer
        anchors.fill: parent

        color: DStyle.colorMainBG

        Image {
            id: bgImage
            anchors.fill: parent
            source: settingsController.designerMode === "Developer" ? "qrc:/assets/images/tron-wallpaper-23.jpeg"
                                                                    : "qrc:/assets/images/tron-wallpaper-27.jpeg"
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            opacity: 0.1
        }
    }

    // Connections - Main Controller
    Connections {
        target: mainController

        onCurrentProjectChanged: {
            //console.log("main.Connections.mainController.onCurrentProjectChanged - currentProject: " + mainController.currentProject);
            // Check Current Project
            if (mainController.currentProject !== null) {
                // Set Open Recent Files On Show Finished
                openRecentFilesOnShowFinished = true;

                // Hide Welcome Screen
                welcomScreen.hide();
                // Show Project Pane
                projectPane.show();
                // Show Properties Pane
                propertiesPane.show();

                //

            } else {
                // Set Open Recent Files On Show Finished
                openRecentFilesOnShowFinished = false;

                // Reset Project Pane
                projectPane.reset(false);
                // Reset Properties Pane
                propertiesPane.reset(false);
                // Show Welcome Screen
                welcomScreen.show();
            }
        }
    }

    // Connections - Current Project
    Connections {
        target: mainController.currentProject

        onBaseComponentCreated: {
            //console.log("mainController.currentProject.onBaseComponentCreated - aComponent: " + aComponent);
            // Show Project Pane
            projectPane.show();
            // Create New Component Root
            //createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        onComponentCreated: {
            //console.log("mainController.currentProject.onComponentCreated - aComponent: " + aComponent);
            // Show Project Pane
            projectPane.show();
            // Create New Component Root
            //createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        onViewCreated: {
            //console.log("mainController.currentProject.onViewCreated - aComponent: " + aComponent);
            // Show Project Pane
            projectPane.show();
            // Create New Component Root
            //createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        // ...
    }

    // Connections - Open Files Model
    Connections {
        target: openFilesModel

        onFileOpened: {
            // Check Current Project Absolute File Path
            if (mainController.currentProject !== null && mainController.currentProject.projectFilePath === aFilePath) {
                //console.log("openFilesModel.onFileOpened - aFilePath: " + aFilePath + " - Current Project File Selected");

                // Project File Opened
                return;
            }

            //console.log("openFilesModel.onFileOpened - aFilePath: " + aFilePath);

            // Check Current Project
            if (mainController.currentProject !== null) {
                // Get Component
                var component = mainController.currentProject.getComponentByPath(aFilePath);
                // Check Component
                if (component !== null) {
                    // Open Component
                    createNewComponentRoot(component, component.width, component.height);
                } else {
                    // Open Other Files

                    // ...

                }
            }
        }

        onComponentOpened: {
            //console.log("openFilesModel.onComponentOpened - aComponent: " + aComponent);
            // Check Component
            if (aComponent !== null) {
                // Open Component
                createNewComponentRoot(aComponent, aComponent.width, aComponent.height);
            }
        }
    }

//    DPopupArea {
//        id: mainPopupArea
//        anchors.fill: parent
//        // ...
//    }

    Component {
        id: componentRootFactory

        DComponentRootContainer {
            id: newComponentRootContainer

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            initialX: projectPane.x + projectPane.width
            initialY: Math.max(Math.min(mainGrabArea.height / 2, projectPane.y + projectPane.height - DStyle.defaultMargin), projectPane.y + DStyle.defaultMargin)

            creationX: parentWidth * 0.5 - creationWidth * 0.5
            creationY: parentHeight * 0.5 - creationHeight * 0.5

            state: stateCreate
        }
    }

    Component {
        id: assetRootFactory

        DAssetContainer {
            id: newAssetRootContainer

            // ...
        }
    }

    Component {
        id: sourceRootFactory

        DSourceContainer {
            id: newSourceRootContainer

            // ...
        }
    }

    // Main Grab Area
    MainGrabArea {
        id: mainGrabArea

        anchors.fill: parent

        // Project Pane
        ProjectPane {
            id: projectPane

            onTransitionFinished: {
                // Check New State
                if (newState === stateShown) {
                    // Check Open Recent Files On Show Finished
                    if (mainRoot.openRecentFilesOnShowFinished) {
                        // reset Open Recent Files On Show Finished
                        mainRoot.openRecentFilesOnShowFinished = false;
                        // Open Recent Files
                        openFilesModel.openRecentFiles();
                    }
                }
            }
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane

            onNewImportLaunch: {
                // Check Imports Model
                if (propertiesController.importsModel !== null && importEditor.state === importEditor.stateCreate) {
                    // Set New Import
                    importEditor.newImport = true;
                    // Show Imports Editor
                    importEditor.show();
                }
            }

            onEditImportsLaunch: {
                // Check Imports Model
                if (propertiesController.importsModel !== null && importEditor.state === importEditor.stateCreate) {
                    // Set New Import
                    importEditor.newImport = false;
                    // Show Imports Editor
                    importEditor.show();
                }
            }

            onNewPropertyLaunch: {
                // Check Own Properties Model
                if (propertiesController.ownPropertiesModel !== null) {
                    // Set New Property
                    propertyEditor.newProperty = true;
                    // Show Property Editor
                    propertyEditor.show();
                }
            }

            onEditPropertyLaunch: {
                // Check Own Properties Model
                if (propertiesController.ownPropertiesModel !== null) {
                    // Set New Property
                    propertyEditor.newProperty = false;
                    // Show Property Editor
                    propertyEditor.show();
                }
            }

            onEditFormulaLaunch: {
                // Set Own Property
                formulaEditor.ownProperty = ownProperty;
                // Set Proprty Name
                formulaEditor.propertyName = propertyName;
                // Show Formula Editor
                formulaEditor.show();
            }

            onNewSignalLaunch: {
                // Check Signals Model
                if (propertiesController.signalsModel !== null && signalEditor.state === signalEditor.stateCreate) {
                    // Set New Signal
                    signalEditor.newSignal = true;
                    // Set Component Signal
                    signalEditor.componentSignal = propertiesController.signalsModel.createNewSignal();
                    // Show Signal Editor
                    signalEditor.show();
                }
            }

            onEditSignalLaunch: {
                // Check Signals Model
                if (propertiesController.signalsModel !== null && signalEditor.state === signalEditor.stateCreate) {
                    // Reset New Signal
                    signalEditor.newSignal = false;
                    // Set Component Signal
                    signalEditor.componentSignal = propertiesController.signalsModel.selectSignal(index);
                    // Show Signal Editor
                    signalEditor.show();
                }
            }

            onNewSlotLaunch: {
                // Check Slots Model
                if (propertiesController.slotsModel !== null && slotEditor.state === slotEditor.stateCreate) {
                    // Set New Slot
                    slotEditor.newSlot = true;
                    // Set Component Slot
                    slotEditor.componentSlot = propertiesController.slotsModel.createNewSlot();
                    // Show Slot Editor
                    slotEditor.show();
                }
            }

            onEditSlotLaunch: {
                // Check Slots Model
                if (propertiesController.slotsModel !== null && slotEditor.state === slotEditor.stateCreate) {
                    // Set New Slot
                    slotEditor.newSlot = false;
                    // Set Component Slot
                    slotEditor.componentSlot = propertiesController.slotsModel.selectSlot(index);
                    // Show Slot Editor
                    slotEditor.show();
                }
            }

            onNewFunctionLaunch: {
                // Check Functions Model
                if (propertiesController.functionsModel !== null && functionEditor.state === functionEditor.stateCreate) {
                    // Set New Function
                    functionEditor.newFunction = true;
                    // Set Component Function
                    functionEditor.componentFunction = propertiesController.functionsModel.createNewFunction();
                    // Show Function Editor
                    functionEditor.show();
                }
            }

            onEditFunctionLaunch: {
                // Check Functions Model
                if (propertiesController.functionsModel !== null && functionEditor.state === functionEditor.stateCreate) {
                    // Set New Function
                    functionEditor.newFunction = false;
                    // Set Component Function
                    functionEditor.componentFunction = propertiesController.functionsModel.selectFunction(index);
                    // Show Function Editor
                    functionEditor.show();
                }
            }

            onNewStateLaunch: {
                // Check States Model
                if (propertiesController.statesModel !== null && stateEditor.state === stateEditor.stateCreate) {
                    // Set New State
                    stateEditor.newState = true;

                    // Set Component State
                    //stateEditor.componentState = propertiesController.statesModel.createNewState();

                    // Show State Editor
                    stateEditor.show();
                }
            }

            onEditStateLaunch: {
                // Check States Model
                if (propertiesController.statesModel !== null && stateEditor.state === stateEditor.stateCreate) {
                    // Set New State
                    stateEditor.newState = false;

                    // Set Component State

                    // Show State Editor
                    stateEditor.show();
                }
            }

            onNewTransitionLaunch: {
                // Check Transitions Model
                if (propertiesController.transitionsModel !== null && transitionEditor.state === transitionEditor.stateCreate) {
                    // Set New Transition
                    transitionEditor.newTransition = true;

                    // Set Component Transition

                    // Show Transition Editor
                    transitionEditor.show();
                }
            }

            onEditTransitionLaunch: {
                // Check Transitions Model
                if (propertiesController.transitionsModel !== null && transitionEditor.state === transitionEditor.stateCreate) {
                    // Set New Transition
                    transitionEditor.newTransition = false;

                    // Set Component Transition

                    // Show Transition Editor
                    transitionEditor.show();
                }
            }
        }

        // Import Editor
        DImportEditor {
            id: importEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            onAccepted: {
                // Check Imports Model
                if (propertiesController.importsModel !== null) {
                    // Add Import
                    propertiesController.importsModel.addImport(importEditor.importName);
                }
            }
        }

        // Property Editor
        DPropertyEditor {
            id: propertyEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            childPane: propertyEnumValueEditor

            onAccepted: {
                // Check New Property
                if (propertyEditor.newProperty) {
                    // Add Property
                    propertiesController.addOwnComponentProperty(propertyEditor.propertyName,
                                                                 propertyEditor.propertyType,
                                                                 propertyEditor.propertyMin,
                                                                 propertyEditor.propertyMax,
                                                                 propertyEditor.propertyEnums,
                                                                 propertyEditor.propertyDefault);
                    // Reset New Property
                    propertyEditor.newProperty = false;
                } else {
//                    // Update Property
//                    propertiesController.ownPropertiesModel.updateComponentProperty(propertyEditor.propertyName,
//                                                                                    propertyEditor.propertyType,
//                                                                                    propertyEditor.propertyDefault);
                }
            }
        }

        DPropertyEnumValueEditor {
            id: propertyEnumValueEditor

            parentPane: propertyEditor

            initialX: propertyEditor.x + propertyEditor.width * 0.5
            initialY: propertyEditor.y + propertyEditor.height

            creationX: initialX - propertyEnumValueEditor.width * 0.5
            creationY: initialY + 32

        }

        // Formula Editor
        DFormulaEditor {
            id: formulaEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            onAccepted: {
                // Check Own Property
                if (formulaEditor.ownProperty) {
                    // Set Compoennt Own Property Value
                    propertiesController.ownPropertiesModel.setComponentProperty(formulaEditor.propertyName, formulaEditor.propertyFormula);
                } else {
                    // Set Component Property Value
                    propertiesController.propertiesModel.setComponentProperty(formulaEditor.propertyName, formulaEditor.propertyFormula);
                }
            }
        }

        // Signal Editor
        DSignalEditor {
            id: signalEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            childPane: signalParameterEditor

            onNewParameter: {
                // Set New Parameter
                signalParameterEditor.newParameter = true;
                // Set Component Signal
                signalParameterEditor.componentSignal = signalEditor.componentSignal;
                // Show Signal Parameter Editor
                signalParameterEditor.show();
            }

            onEditParameter: {
                // Set New Parameter
                signalParameterEditor.newParameter = false;
                // Set Component Signal
                signalParameterEditor.componentSignal = signalEditor.componentSignal;
                // Show Signal Parameter Editor
                signalParameterEditor.show();
            }

            onAccepted: {
                // Check New Signal
                if (signalEditor.newSignal) {
                    // Append Component Signal
                    propertiesController.signalsModel.appendSignal(signalEditor.componentSignal);
                    // Reset Component Signal
                    signalEditor.componentSignal = null;
                    // Reset New Signal
                    signalEditor.newSignal = false;
                } else {
                    // Update Component Signal
                    propertiesController.signalsModel.updateSelectedSignal();

                    // ...
                }
            }

            onRejected: {
                // Check New Signal
                if (signalEditor.newSignal) {
                    // Discard Signal
                    propertiesController.signalsModel.discardNewSignal(signalEditor.componentSignal);
                    // Reset Component Signal
                    signalEditor.componentSignal = null;
                    // Reset New Signal
                    signalEditor.newSignal = false;
                } else {
                    // ...
                }
            }
        }

        // Signal Parameter Editor
        DSignalParameterEditor {
            id: signalParameterEditor

            parentPane: signalEditor

            initialX: signalEditor.x + signalEditor.width * 0.5
            initialY: signalEditor.y + signalEditor.height

            creationX: initialX - signalParameterEditor.width * 0.5
            creationY: initialY + 32
        }

        // Slot Editor
        DSlotEditor {
            id: slotEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            onAccepted: {
                // Check If New Slot
                if (slotEditor.newSlot) {
                    // Append Component Slot
                    propertiesController.slotsModel.appendSlot(slotEditor.componentSlot);
                    // Reset Component Slot
                    slotEditor.componentSlot = null;
                    // Reset New Slot
                    slotEditor.newSlot = false;
                } else {
                    // Update Component Slot
                    propertiesController.slotsModel.updateSelectedSlot();

                    // ...
                }
            }

            onRejected: {
                // Check If New Slot
                if (slotEditor.newSlot) {
                    // Discard New Slot
                    propertiesController.slotsModel.discardNewSlot(slotEditor.componentSlot);
                    // Reset Component Slot
                    slotEditor.componentSlot = null;
                    // Reset New Slot
                    slotEditor.newSlot = false;
                }
            }
        }

        // Function Editor
        DFunctionEditor {
            id: functionEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            onAccepted: {
                // Check If New Function
                if (functionEditor.newFunction) {
                    // Append New Function
                    propertiesController.functionsModel.appendFunction(functionEditor.componentFunction);
                    // Reset Component Function
                    functionEditor.componentFunction = null;
                    // Reset New Function
                    functionEditor.newFunction = false;
                } else {
                    // Update Component Function
                    propertiesController.functionsModel.updateSelectedFunction();

                    // ...
                }
            }

            onRejected: {
                // Check If New Function
                if (functionEditor.newFunction) {
                    // Discard New Function
                    propertiesController.functionsModel.discardNewFunction(functionEditor.componentFunction);
                    // Reset Component Function
                    functionEditor.componentFunction = null;
                    // Reset New Function
                    functionEditor.newFunction = false;
                }
            }
        }

        // State Editor
        DStateEditor {
            id: stateEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            childPane: propertyChangesEditor

            // ...

            onNewPropertyChange: {
                // Show Property Changes Editor
                propertyChangesEditor.show();
            }
        }

        // Property Changes Editor
        DPropertyChangesEditor {
            id: propertyChangesEditor

            parentPane: stateEditor

            initialX: stateEditor.x + stateEditor.width * 0.5
            initialY: stateEditor.y + stateEditor.height

            creationX: initialX - propertyChangesEditor.width * 0.5
            creationY: initialY + 32

            // ...

        }

        // Transition Editor
        DTransitionEditor {
            id: transitionEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            childPane: transitionNodeEditor

            // ...

            onNewTransitionNode: {
                // Show Transition Node Editor
                transitionNodeEditor.show();
            }
        }

        // Transition Node Editor
        DTransitionNodeEditor {
            id: transitionNodeEditor

            initialX: transitionEditor.x + transitionEditor.width * 0.5
            initialY: transitionEditor.y + transitionEditor.height

            creationX: initialX - transitionNodeEditor.width * 0.5
            creationY: initialY + 32

            parentPane: transitionEditor

            // ...

        }
    }

    // Live Launcher
    DLiveLauncher {
        id: liveLauncher
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    // Welcome Screen
    DWelcome {
        id: welcomScreen
        anchors.centerIn: parent
        state: stateShown
        //visible: false
    }

    // Minimized Components
    DMinimizedComponents {
        id: minimzedComponents
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }

    // Demo Container
    DDemoContainer {
        id: demoContainer
        anchors.centerIn: parent
        visible: false
    }

    DActivityIndicator {
        id: systemBusyIndicator
        width: 256
        height: 256
        anchors.centerIn: parent
        running: DSystemModel.systemBusy
    }

    // Toolbar
    DToolBar {
        id: toolBar
    }
}

