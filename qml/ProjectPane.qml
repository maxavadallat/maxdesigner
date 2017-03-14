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

    borderColor: DStyle.colorBorder

    property Connections currentProjectConnection: Connections {
        target: mainController.currentProject

        onBaseComponentCreated: {
            //console.log("ProjectPane.currentProjectConnection.onBaseComponentCreated - aComponent: " + aComponent);

            // Open Base Compoennts Section
            baseComponentsSection.open();
        }

        onComponentCreated: {
            //console.log("ProjectPane.currentProjectConnection.onComponentCreated - aComponent: " + aComponent);

            // Open Components Section
            ownComponentsSection.open();
        }

        onViewCreated: {
            //console.log("ProjectPane.currentProjectConnection.onViewCreated - aComponent: " + aComponent);

            // Open Views Section
            viewsSection.open();
        }
    }

    property Connections openFilesModelConnection: Connections {
        target: openFilesModel

        onCurrentIndexChanged: {
            //console.log("ProjectPane.openFilesModelConnection.onCurrentIndexChanged - currentIndex: " + openFilesModel.currentIndex);

            // Check Open Files List View Current Index
            if (openFilesListView.currentIndex !== openFilesModel.currentIndex) {
                // Set Open Files List View Current Index
                openFilesListView.currentIndex = openFilesModel.currentIndex;
            }
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
            spacing: DStyle.defaultSpacing
            opacity: baseComponentsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: baseComponentsRepeater
                model: mainController.currentProject ? mainController.currentProject.baseComponentsModel : undefined
                delegate: DComponentItem {
                    id: baseComponentItemDelegateRoot
                    title: componentName
                    componentInfo: mainController.currentProject.baseComponentsModel.getComponentByIndex(index);
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
            height: baseComponentsRepeater.count === 0 ? baseComponentsSection.minHeight : 0
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
            spacing: DStyle.defaultSpacing
            opacity: componentsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: componentsRepeater
                model: mainController.currentProject ? mainController.currentProject.componentsModel : undefined
                delegate: DComponentItem {
                    id: componentItemDelegateRoot
                    title: componentName
                    componentInfo: mainController.currentProject.componentsModel.getComponentByIndex(index);
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
            height: componentsRepeater.count === 0 ? ownComponentsSection.minHeight : 0
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
            spacing: DStyle.defaultSpacing
            opacity: viewsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: viewsRepeater
                model: mainController.currentProject ? mainController.currentProject.viewsModel : undefined
                delegate: DComponentItem {
                    id: viewItemDelegateRoot
                    title: viewName
                    componentInfo: mainController.currentProject.viewsModel.getViewByIndex(index);
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
            height: viewsRepeater.count === 0 ? viewsSection.minHeight : 0
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

                Row {
                    id: projectTreeDelegateRow
                    height: parent.height
                    spacing: DStyle.defaultSpacing

                    Image {
                        width: DStyle.iconWidthSmall
                        height: DStyle.iconHeightSmall
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

            onItemDoubleClicked: {
                // Get Item File Path
                var itemFilePath = projectTreeModel.getPathByIndex(index);

                // Check Item File Path
                if (itemFilePath !== "") {
                    //console.log("ProjectPane.projectTreeView.onItemDoubleClicked - itemFilePath: " + itemFilePath);

                    // Open File
                    openFilesModel.openFile(itemFilePath);
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
                width: openFilesListView.width
                height: DStyle.listItemHeight

                color: index === openFilesListView.currentIndex ? DStyle.colorSelectedHighLight : "transparent"

                DMouseArea {
                    anchors.fill: parent

                    onClicked: {
                        // Set Current Index
                        openFilesListView.currentIndex = index;
                        // Select File
                        openFilesModel.selectFile(index);
                    }

                    onDoubleClicked: {

                    }
                }

                Image {
                    id: iconImage
                    width: DStyle.iconWidthSmall
                    height: DStyle.iconHeightSmall
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectFit
                    source: fileIcon
                    asynchronous: true
                }

                DText {
                    anchors.fill: parent
                    anchors.leftMargin: iconImage.source !== "" ? iconImage.width + DStyle.defaultMargin : 0
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
