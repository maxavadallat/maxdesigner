import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPane {
    id: projectPaneRoot

    width: 360
    height: 600

    title: "Project" + (mainController.currentProject ? (" - " + mainController.currentProject.projectName) : "")

    minWidth: 300
    minHeight: 200

    enablePaneContent: true

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToLeft

    borderColor: Style.colorBorder

    property QtObject currentProjectConnection: Connections {
        target: mainController.currentProject

        onBaseComponentCreated: {
            console.log("ProjectPane.currentProjectConnection.onBaseComponentCreated - aComponent: " + aComponent);

            // Open Base Compoennts Section
            baseComponentsSection.open();
        }

        onComponentCreated: {
            console.log("ProjectPane.currentProjectConnection.onComponentCreated - aComponent: " + aComponent);

            // Open Components Section
            ownComponentsSection.open();
        }

        onViewCreated: {
            console.log("ProjectPane.currentProjectConnection.onViewCreated - aComponent: " + aComponent);

            // Open Views Section
            viewsSection.open();
        }
    }

    DSection {
        id: baseComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Base Components"
        //state: stateClosed
        minHeight: baseComponentsRepeater.count > 0 ? baseComponentsFlow.height : 200

        DFlow {
            id: baseComponentsFlow
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: baseComponentsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: baseComponentsRepeater
                model: mainController.currentProject ? mainController.currentProject.baseComponentsModel : undefined
                delegate: DComponentItem {
                    id: baseComponentItemDelegateRoot
                    title: componentName
                    onGrabbedChanged: {
                        // Bring Section To Top
                        baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                        // Disable Content Clip
                        baseComponentsSection.clipContent = !grabbed;
                    }
                }
            }
        }

        DNoContent {
            width: projectPaneRoot.contentWidth
            height: baseComponentsSection.minHeight
            opacity: baseComponentsRepeater.count === 0 ? 0.2 : 0.0

            DText {
                id: noBaseComponentsLabel
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                text: "No Base Components"
            }
        }
    }

    DSection {
        id: ownComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Components"
        //state: stateOpen
        minHeight: componentsRepeater.count > 0 ? componentsFlow.height : 200

        DFlow {
            id: componentsFlow
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: componentsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: componentsRepeater
                model: mainController.currentProject ? mainController.currentProject.componentsModel : undefined
                delegate: DComponentItem {
                    id: componentItemDelegateRoot
                    title: componentName
                    onGrabbedChanged: {
                        // Bring Section To Top
                        ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                        // Disable Content Clip
                        ownComponentsSection.clipContent = !grabbed;
                    }
                }
            }
        }

        DNoContent {
            width: projectPaneRoot.contentWidth
            height: ownComponentsSection.minHeight
            opacity: componentsRepeater.count === 0 ? 0.2 : 0.0

            DText {
                id: noComponentsLabel
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                text: "No Components"
            }
        }
    }

    DSection {
        id: viewsSection
        width: projectPaneRoot.contentWidth
        title: "Views"
        //state: stateClosed
        minHeight: viewsRepeater.count > 0 ? viewsFlow.height : 200

        DFlow {
            id: viewsFlow
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: viewsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: viewsRepeater
                model: mainController.currentProject ? mainController.currentProject.viewsModel : undefined
                delegate: DComponentItem {
                    id: viewItemDelegateRoot
                    title: viewName
                    onGrabbedChanged: {
                        // Bring Section To Top
                        viewsSection.z = grabbed ? 0.1 : 0.0;
                        // Disable Content Clip
                        viewsSection.clipContent = !grabbed;
                    }
                }
            }
        }

        DNoContent {
            width: projectPaneRoot.contentWidth
            height: viewsSection.minHeight
            opacity: viewsRepeater.count === 0 ? 0.2 : 0.0

            DText {
                id: noViewsLabel
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                text: "No Views"
            }
        }
    }

    DSection {
        id: projectTreeSection
        width: projectPaneRoot.contentWidth
        title: "Project Tree"
        state: stateOpen

        DTreeView {
            id: projectTreeView
            width: projectPaneRoot.contentWidth

            model: projectTreeModel
            rootIndex: projectTreeModel.rootIndex

//            property QtObject filterProxy: FileSortFilterProxy {
//                sourceModel: projectTreeModel
//            }

//            model: filterProxy
//            rootIndex: filterProxy.mapFromSource(projectTreeModel.rootIndex);

            delegate: DControl {
                id: projectTreeDelegateRoot
                width: projectTreeDelegateRow.width

//                onDoubleClicked: {
//                    if (model && model.fileIsDir) {
//                        //if (projectTreeView.expand())
//                    }
//                }

                Row {
                    id: projectTreeDelegateRow
                    height: parent.height
                    spacing: Style.defaultSpacing

                    Image {
                        width: Style.iconWidthSmall
                        height: Style.iconHeightSmall
                        anchors.verticalCenter: parent.verticalCenter
                        fillMode: Image.PreserveAspectFit
                        source: model ? model.fileIcon : ""
                        asynchronous: true
                    }

                    DText {
                        text: model ? model.fileName : ""
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    DSection {
        id: openFilesSection
        width: projectPaneRoot.contentWidth
        title: "Open Documents"
        state: stateClosed

        property Connections openFilesModelConnection: Connections {
            target: openFilesModel
            onFileOpened: {
                openFilesSection.open();
            }
        }

        ListView {
            id: openFilesListView
            width: projectPaneRoot.contentWidth
            height: count > 0 ? 300 : 0

            opacity: count > 0 ? 1.0 : 0.0
            visible: opacity > 0.0

            model: openFilesModel
            highlightFollowsCurrentItem: true

            delegate: Rectangle {
                width: openFilesListView
                height: Style.listItemHeight
                color: index === openFilesListView.currentIndex ? Style.colorHighLight : "transparent"
                DMouseArea {
                    anchors.fill: parent

                    onClicked: {
                        // Set Current Index
                        openFilesListView.currentIndex = index;
                    }

                    onDoubleClicked: {
                        // Set Current Index
                        openFilesListView.currentIndex = index;
                        // Select File
                        openFilesModel.selectFile(index);
                    }
                }

                DText {
                    anchors.fill: parent
                    text: fileName
                }
            }
        }

        DNoContent {
            width: projectPaneRoot.contentWidth
            height: openFilesSection.minHeight
            opacity: openFilesListView.count === 0 ? 0.2 : 0.0

            DText {
                id: noOpenDocumentsLabel
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                text: "No Open Files"
            }
        }
    }
}
