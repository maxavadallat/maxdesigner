import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "style"

Item {
    id: mainRoot

    focus: true

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
                    console.log("componentRootFactory - object: ", incubator.object, " ready!");
                    // Launch Root Component
                    launchComponentRoot(incubator.object, componentInfo, width, height);

                } else if (status === Component.Error) {
                    console.log("componentRootFactory - object: ", incubator.object, " ERROR: " + componentRootFactory.errorString());
                }
            }
        } else {
            console.log("componentRootFactory - object: ", incubator.object, " immediately ready!");
            // Launch Root Component
            launchComponentRoot(incubator.object, componentInfo, width, height);
        }
    }

    // Launch Component Root
    function launchComponentRoot(object, componentInfo, width, height) {
        // Set Component Info
        object.componentInfo = componentInfo;
        // Set Creation Width & Height
        object.creationWidth = width;
        object.creationHeight = height;
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

    // Keys Handling
    Keys.onReleased: {
        switch (event.key) {
            case Qt.Key_T:
                settingsController.tracerVisible = !settingsController.tracerVisible;
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
                // Hide Welcome Screen
                welcomScreen.hide();
                // Show Project Pane
                projectPane.show();
                // Show Properties Pane
                propertiesPane.show();

            } else {
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
            createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        onComponentCreated: {
            //console.log("mainController.currentProject.onComponentCreated - aComponent: " + aComponent);
            // Show Project Pane
            projectPane.show();
            // Create New Component Root
            createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        onViewCreated: {
            //console.log("mainController.currentProject.onViewCreated - aComponent: " + aComponent);
            // Show Project Pane
            projectPane.show();
            // Create New Component Root
            createNewComponentRoot(aComponent, aWidth, aHeight);
        }

        // ...
    }

    Rectangle {
        id: bgContainer
        anchors.fill: parent

        color: Style.colorMainBG

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
            initialY: Math.max(Math.min(mainGrabArea.height / 2, projectPane.y + projectPane.height - Style.defaultMargin), projectPane.y + Style.defaultMargin)

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

            creationX: Style.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: projectPane.creationX
            lastShownY: projectPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane

            initialX: mainGrabArea.width
            initialY: mainGrabArea.height / 2

            creationWidth: 300
            creationHeight: 600

            creationX: parentWidth - creationWidth - Style.defaultMargin * 2
            creationY: parentHeight / 2 - creationHeight / 2

            lastShownX: propertiesPane.creationX
            lastShownY: propertiesPane.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown
        }

        DFormulaEditor {
            id: formulaEditor

            initialX: propertiesPane.x
            initialY: Math.max(Math.min(mainGrabArea.height / 2, propertiesPane.y + propertiesPane.height - Style.defaultMargin), propertiesPane.y + Style.defaultMargin)

            creationWidth: 320
            creationHeight: 200

            creationX: parentWidth / 2 - creationWidth / 2 + 100
            creationY: initialY - creationHeight / 2 + 150

            lastShownX: formulaEditor.creationX
            lastShownY: formulaEditor.creationY

            parentWidth: mainGrabArea.width
            parentHeight: mainGrabArea.height

            state: stateCreate
            //state: stateShown
        }
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
}

