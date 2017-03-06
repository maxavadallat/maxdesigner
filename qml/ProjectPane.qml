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

    DSection {
        id: baseComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Base Components"
        state: stateClosed

        Flow {
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: baseComponentsRepeater.count > 0 ? 1.0 : 0.0
            Repeater {
                id: baseComponentsRepeater
                delegate: DComponentItem {
                    id: baseComponentItemDelegateRoot
                    title: model.componentName //"QtObject"
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
            opacity: openFilesListView.count === 0 ? 0.2 : 0.0

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
        state: stateClosed

        Flow {
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: componentsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: componentsRepeater
                delegate: DComponentItem {
                    id: componentItemDelegateRoot
                    title: model.componentName //"Label"
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
            opacity: openFilesListView.count === 0 ? 0.2 : 0.0

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
        state: stateClosed

        Flow {
            width: projectPaneRoot.contentWidth
            spacing: Style.defaultSpacing
            opacity: viewsRepeater.count > 0 ? 1.0 : 0.0

            Repeater {
                id: viewsRepeater
                delegate: DComponentItem {
                    id: viewItemDelegateRoot
                    title: model.viewName//"TopStatusBar"
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
            opacity: openFilesListView.count === 0 ? 0.2 : 0.0

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

        ListView {
            id: openFilesListView
            width: projectPaneRoot.contentWidth
            opacity: count > 0 ? 1.0 : 0.0
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
