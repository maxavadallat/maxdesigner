import QtQuick 2.0

//import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../system"
import "../controls"
import "../animations"

Item {
    id: assetBrowserRoot

    width: 800
    height: 600

    property bool showSelectContainer: false

    Rectangle {
        id: bgRectangle
        anchors.fill: parent
        color: "#FF222222"
    }

    Item {
        id: leftPaneContainer

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: selectButtonContainer.top
        anchors.bottomMargin: 0
        anchors.right: horizontalSeparator.left

        // Assets File System Tree
        Item {
            id: assetTreeContainer

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: leftPaneSeparator.top

            // Tree View
            DTreeView {
                id: assetsTreeView
                anchors.fill: parent
                anchors.margins: DStyle.defaultMargin

                model: assetsTreeModel
                rootIndex: assetsTreeModel.rootIndex

                delegate: DControl {
                    id: assetsTreeDelegateRoot
                    width: assetsTreeDelegateRow.width

                    Row {
                        id: assetsTreeDelegateRow
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
                    var itemFilePath = assetsTreeModel.getPathByIndex(index);

                    // Check Item File Path
                    if (itemFilePath !== "") {
                        //console.log("ProjectPane.projectTreeView.onItemDoubleClicked - itemFilePath: " + itemFilePath);

                        // Open File
                        //openFilesModel.openFile(itemFilePath);
                    }
                }
            }
        }

        DPaneSeparator {
            id: leftPaneSeparator
            y: parent.height * 0.6
            width: leftPaneContainer.width
        }

        // Preview
        Item {
            id: previewContainer

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: leftPaneSeparator.bottom
            anchors.bottom: parent.bottom

            // Preview Image
            DImage {
                id: previewImage
                anchors.fill: parent
                anchors.margins: DStyle.defaultMargin

            }

            // Name

            // Size

            // Dimension

        }
    }

    DPaneSeparator {
        id: horizontalSeparator
        x: 300
        height: assetGridContainer.height
        vertical: true
    }

    Item {
        id: assetGridContainer

        anchors.left: horizontalSeparator.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: selectButtonContainer.top

        focus: true

        Keys.onLeftPressed: assetsGridView.moveCurrentIndexLeft();
        Keys.onRightPressed: assetsGridView.moveCurrentIndexRight();
        Keys.onUpPressed: assetsGridView.moveCurrentIndexUp();
        Keys.onDownPressed: assetsGridView.moveCurrentIndexDown();
        Keys.onReleased: {
            // Switch Key
            switch (event.key) {
                case Qt.Key_Home:
                    assetsGridView.currentIndex = 0;
                break;

                case Qt.Key_End:
                    assetsGridView.currentIndex = assetsGridView.count - 1
                break;
            }
        }

        GridView {
            id: assetsGridView
            anchors.fill: parent
            anchors.margins: DStyle.defaultMargin

            model: assetsListModel

            cellWidth: 300
            cellHeight: 200

            highlightFollowsCurrentItem: true
            highlightMoveDuration: 10//DStyle.animDuration * 0.5

            snapMode: GridView.SnapPosition

            currentIndex: 0

            delegate: DAssetItemDelegate {
                width: assetsGridView.cellWidth
                height: assetsGridView.cellHeight

                itemIndex: index
                gridCurrentIndex: assetsGridView.currentIndex

                fileName: model.assetName
                filePath: model.assetPath
                fileSize: model.assetSize
                isDir:    model.isDir

                onClicked: {
                    // Set Focus
                    assetGridContainer.focus = true;
                    // Set Current Index
                    assetsGridView.currentIndex = index;
                }

                onDoubleClicked: {
                    // ...
                }
            }

            highlight: Rectangle {
                width: assetsGridView.cellWidth
                height: assetsGridView.cellHeight
                color: DStyle.colorSelectedHighLight
            }

            // ...
        }
    }

    Rectangle {
        id: selectButtonContainer
        width: parent.width
        height: 84
        anchors.bottom: parent.bottom
        anchors.bottomMargin: selectContainerBottomMargin
        property int selectContainerBottomMargin: assetBrowserRoot.showSelectContainer ? 0 : -height
        Behavior on selectContainerBottomMargin { DAnimation { } }
        color: "#77000000"


    }
}
