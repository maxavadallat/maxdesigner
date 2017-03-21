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
        mainRoot.rootComponents.push(object);

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
            initialX: projectPane.x + projectPane.width
            initialY: Math.max(Math.min(mainGrabArea.height / 2, projectPane.y + projectPane.height - DStyle.defaultMargin), projectPane.y + DStyle.defaultMargin)

            creationWidth: 400
            creationHeight: 600

            creationX: parentWidth / 2 - creationWidth / 2
            creationY: initialY - creationHeight / 2

            lastShownX: newComponentRootContainer.creationX
            lastShownY: newComponentRootContainer.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

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
        //visible: false

        // Project Pane
        ProjectPane {
            id: projectPane

            initialX: 0
            initialY: mainGrabArea.height / 2

            creationWidth: 360
            creationHeight: 600

            creationX: DStyle.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: projectPane.creationX
            lastShownY: projectPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown

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

            initialX: mainGrabArea.width
            initialY: mainGrabArea.height / 2

            creationWidth: 300
            creationHeight: 600

            creationX: parentWidth - creationWidth - DStyle.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: propertiesPane.creationX
            lastShownY: propertiesPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown

            onNewPropertyLaunch: {
                // Show Property Editor
                propertyEditor.show();
            }
        }

        // Property Editor
        DPropertyEditor {
            id: propertyEditor

//            creationWidth: 320
//            creationHeight: 200

            initialX: propertiesPane.x
//            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)
            initialY: propertiesPane.y + propertiesPane.height / 2

//            creationX: propertiesPane.x - creationWidth - 32
//            creationY: initialY - creationHeight / 2

//            lastShownX: formulaEditor.creationX
//            lastShownY: formulaEditor.creationY

//            parentWidth: mainGrabArea.width
//            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // Formula Editor
        DFormulaEditor {
            id: formulaEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(parentHeight / 2, propertiesPane.y + propertiesPane.height - DStyle.defaultMargin), propertiesPane.y + DStyle.defaultMargin)

            creationWidth: 320
            creationHeight: 200

            creationX: propertiesPane.x - creationWidth - 32
            creationY: initialY - creationHeight / 2

            lastShownX: formulaEditor.creationX
            lastShownY: formulaEditor.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown
        }

        // State Editor
        DStateEditor {
            id: stateEditor

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // State Selector
        DStateSelector {
            id: stateSelector

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // Transition Editor
        DTransitionEditor {
            id: transitionEditor

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
        }

        // ...

    }

    DWelcome {
        id: welcomScreen
        anchors.centerIn: parent
        state: stateShown
        //state: stateHidden
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

