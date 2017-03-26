import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

Item {
    id: mainRoot

    focus: true

    property bool openRecentFilesOnShowFinished: false

    // Array For Root Components
    property var rootComponents: []

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

        // Push Object To Root Components
        //mainRoot.rootComponents.push(object);

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

    // Close All Root Components
    function closeRootComponents() {
//        // Get Root Components Count
//        var rcCount = mainRoot.rootComponents.length;
//        // Iterate Through Root Component
//        for (var i=0; i<rcCount; i++) {
//            // Get Root Component
//            var rComponent = mainRoot.rootComponents[i];
//            // Close Root Component
//            rComponent.reset(true);
//        }
    }

    // Keys Handling
    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_T:
                settingsController.tracerVisible = !settingsController.tracerVisible;
            break;

            case Qt.Key_F8:
                settingsController.slowMotion = !settingsController.slowMotion;
            break;
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

                // Close Root Components
                closeRootComponents();

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

    Connections {
        target: openFilesModel

        onFileOpened: {
            // Check Current Project Absolute File Path
            if (mainController.currentProject !== null && mainController.currentProject.projectFilePath === aFilePath) {
                //console.log("openFilesModel.onFileOpened - aFilePath: " + aFilePath + " - Current Project File Selected");

                // Project File Opened
                return;
            }

            console.log("openFilesModel.onFileOpened - aFilePath: " + aFilePath);

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

    Component {
        id: formulaEditorRootFactory

        DFormulaEditor {
            id: newFormulaEditorRootContainer

        }
    }

    MainGrabArea {
        id: mainGrabArea

        anchors.fill: parent

        // Project Pane
        ProjectPane {
            id: projectPane

            state: stateCreate

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

            state: stateCreate

            onNewPropertyLaunch: {
                // Show Property Editor
                propertyEditor.show();
            }

            onEditPropertyLaunch: {
                // Show Property Editor
                propertyEditor.show();
            }

            onNewSignalLaunch: {
                // Show Signal Editor
                signalEditor.show();
            }

            onEditSignalLaunch: {
                // Show Signal Editor
                signalEditor.show();
            }

            onNewStateLaunch: {
                // Show State Editor
                stateEditor.show();
            }

            onEditStateLaunch: {
                // Show State Editor
                stateEditor.show();
            }

            onNewTransitionLaunch: {
                // Show Transition Editor
                transitionEditor.show();
            }

            onEditTransitionLaunch: {
                // Show Transition Editor
                transitionEditor.show();
            }

            // ...

        }

        // Property Editor
        DPropertyEditor {
            id: propertyEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationX: initialX - propertyEditor.width - 32
            creationY: initialY - propertyEditor.height * 0.5

            // ...

            state: stateCreate
        }

        // Signal Editor
        DSignalEditor {
            id: signalEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationX: initialX - signalEditor.width - 32
            creationY: initialY - signalEditor.height * 0.5

            childPane: signalParameterEditor

            // ...

            state: stateCreate

            onNewParameter: {
                // Show Signal Parameter Editor
                signalParameterEditor.show();
            }

        }

        // Signal Parameter Editor
        DSignalParameterEditor {
            id: signalParameterEditor

            initialX: signalEditor.x + signalEditor.width * 0.5
            initialY: signalEditor.y + signalEditor.height

            creationX: initialX - signalParameterEditor.width * 0.5
            creationY: initialY + 32

            parentPane: signalEditor

            state: stateCreate
        }

        // Formula Editor
        DFormulaEditor {
            id: formulaEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationX: initialX - formulaEditor.width - 32
            creationY: initialY - formulaEditor.height * 0.5

            // ...

            state: stateCreate
            //state: stateShown
        }

        // State Editor
        DStateEditor {
            id: stateEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationX: initialX - stateEditor.width - 32
            creationY: initialY - stateEditor.height * 0.5

            childPane: propertyChangesEditor

            // ...

            state: stateCreate

            onNewPropertyChange: {
                // Show Property Changes Editor
                propertyChangesEditor.show();
            }
        }

        DPropertyChangesEditor {
            id: propertyChangesEditor

            initialX: stateEditor.x + stateEditor.width * 0.5
            initialY: stateEditor.y + stateEditor.height

            creationX: initialX - propertyChangesEditor.width * 0.5
            creationY: initialY + 32

            parentPane: stateEditor

            state: stateCreate

            // ...

        }

        // State Selector
        DStateSelector {
            id: stateSelector

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)


            state: stateCreate

            // ...

        }

        // Transition Editor
        DTransitionEditor {
            id: transitionEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationX: initialX - transitionEditor.width - 32
            creationY: initialY - transitionEditor.height * 0.5

            childPane: transitionNodeEditor

            state: stateCreate

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

            state: stateCreate

            // ...

        }

        // ...

    }

    DWelcome {
        id: welcomScreen
        anchors.centerIn: parent
        state: stateShown
    }

    DMinimizedComponents {
        id: minimzedComponents
        anchors.horizontalCenter: parent.horizontalCenter
    }

    DDemoContainer {
        id: demoContainer
        anchors.centerIn: parent
        visible: false
    }
}

