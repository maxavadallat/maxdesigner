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

    property Connections assetBrowserControllerConnections: Connections {
        target: assetBrowserController

        onCurrentDirChanged: {
            console.log("assetBrowserMain.assetBrowserControllerConnections.onCurrentDirChanged - currentDir: " + assetBrowserController.currentDir);
            // Get Index
            var tmIndex = assetsTreeModel.getIndexByPath(assetBrowserController.currentDir);

            // Check Current Index
            if (assetsTreeView.currentIndex !== tmIndex) {
                // Set Current Index
                //assetsTreeView.currentIndex = tmIndex;
            }

            // Reset Current Index to -1 To Get The Current File Correct
            assetsGridView.currentIndex = -1;
            // Set Current Index For The Grid View
            assetsGridView.currentIndex = assetsListModel.getIndexByName(assetBrowserController.lastDirName);
        }
    }

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
        DRectangle {
            id: assetTreeContainer

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: leftPaneSeparator.top

            anchors.margins: DStyle.defaultMargin

            border.color: assetsTreeView.treeFocus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

            // Mouse Area to Set Focus
            DMouseArea {
                anchors.fill: parent
                onClicked: {
                    // Set Focus
                    assetsTreeView.treeFocus = true;
                }
            }

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

                onItemClicked: {
                    // Get Item File Path
                    var itemFilePath = assetsTreeModel.getPathByIndex(index);

                    // Set Current Dir
                    assetBrowserController.currentDir = itemFilePath;
                }
            }
        }

        // Vertical Separator
        DPaneSeparator {
            id: leftPaneSeparator
            y: parent.height * 0.6
            width: leftPaneContainer.width
        }

        // Preview
        DRectangle {
            id: previewContainer

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: leftPaneSeparator.bottom
            anchors.bottom: parent.bottom

            anchors.margins: DStyle.defaultMargin

            // Preview Image
            DImage {
                id: previewImage
                anchors.fill: parent
                anchors.margins: DStyle.defaultMargin
                fillMode: Image.PreserveAspectFit
                source: {
                    // Check If Is Dir
                    if (assetBrowserController.currentIsDir || assetBrowserController.currentFile === "/") {
                        return "";
                    }

                    return "file://" + assetBrowserController.currentFile;
                }
            }

            Column {
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: DStyle.defaultMargin
                spacing: DStyle.defaultSpacing

                DText {
                    id: previewNameLabel
                    width: parent.width - DStyle.defaultMargin * 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.NoWrap
                    elide: Text.ElideMiddle
                    text: {
                        // Check If Is Dir
                        if (assetBrowserController.currentIsDir) {
                            return "";
                        }

                        return assetBrowserController.currentName;
                    }
                }

                DText {
                    id: previewSizeLabel
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: {
                        // Check If Is Dir
                        if (assetBrowserController.currentIsDir) {
                            return "";
                        }

                        return previewImage.sourceSize.width + "x" + previewImage.sourceSize.height + " (" + assetBrowserController.currentSize + " KB)";
                    }
                }
            }
        }
    }

    // Horizontal Separator
    DPaneSeparator {
        id: horizontalSeparator
        x: 300
        height: assetGridContainer.height
        vertical: true
    }

    // Asset Grid Container
    DRectangle {
        id: assetGridContainer

        anchors.left: horizontalSeparator.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: selectButtonContainer.top

        anchors.margins: DStyle.defaultMargin

        property int maxRowsPerPage: Math.floor(assetsGridView.height / assetsGridView.cellHeight)
        property int maxColPerPage: Math.floor(assetsGridView.width / assetsGridView.cellWidth)

        focus: true

        border.color: focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

        Keys.onLeftPressed: assetsGridView.moveCurrentIndexLeft();
        Keys.onRightPressed: assetsGridView.moveCurrentIndexRight();
        Keys.onUpPressed: assetsGridView.moveCurrentIndexUp();
        Keys.onDownPressed: assetsGridView.moveCurrentIndexDown();

        function pageUp() {
            // Set Current Index
            assetsGridView.currentIndex = Math.max(0, assetsGridView.currentIndex - (assetGridContainer.maxRowsPerPage * assetGridContainer.maxColPerPage));
        }

        function pageDown() {
            // Set Current Index
            assetsGridView.currentIndex = Math.min(assetsGridView.count - 1, assetsGridView.currentIndex + (assetGridContainer.maxRowsPerPage * assetGridContainer.maxColPerPage));
        }

        Keys.onPressed: {
            // Switch Key
            switch (event.key) {
                case Qt.Key_PageUp:
                    // Check Auto Repeat
                    if (event.isAutoRepeat) {
                        pageUp();
                    }
                break;

                case Qt.Key_PageDown:
                    // Check Auto Repeat
                    if (event.isAutoRepeat) {
                        pageDown();
                    }
                break;
            }
        }

        Keys.onReleased: {
            // Switch Key
            switch (event.key) {
                case Qt.Key_Home:
                    assetsGridView.currentIndex = 0;
                break;

                case Qt.Key_End:
                    assetsGridView.currentIndex = assetsGridView.count - 1
                break;

                case Qt.Key_PageUp:
                    pageUp();
                break;

                case Qt.Key_PageDown:
                    pageDown();
                break;

                case Qt.Key_Backspace:
                    // Set Current Dir
                    assetBrowserController.currentDir = assetBrowserController.currentDir + "/..";
                break;

                case Qt.Key_Enter:
                case Qt.Key_Return:
                    // Check If Dir
                    if (assetBrowserController.currentIsDir) {
                        // Set Current Dir
                        assetBrowserController.currentDir = assetBrowserController.currentFile;
                    } else {
                        // Set Selected Asset
                        assetBrowserController.assetItemSelected(assetBrowserController.currentFile);

                        // ...
                    }
                break;
            }
        }

        // Mouse Area To Set Focus
        DMouseArea {
            anchors.fill: parent
            onClicked: {
                // Set Focus
                assetGridContainer.focus = true;
            }
        }

        // Browser Grid View
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

            clip: true

            delegate: DAssetItemDelegate {
                id: assetItemDelegate
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
                    // Check If Is Dir
                    if (isDir) {
                        // Set Current Dir
                        assetBrowserController.currentDir = filePath;
                    } else {

                        // Set Selected Asset
                        assetBrowserController.assetItemSelected(filePath);

                        // ...

                    }
                }
            }

            highlight: Rectangle {
                width: assetsGridView.cellWidth
                height: assetsGridView.cellHeight
                color: DStyle.colorSelectedHighLight
            }

//            add: Transition {
//                NumberAnimation { properties: "x,y"; duration: DStyle.animDuration }
//            }

//            addDisplaced: Transition {
//                NumberAnimation { properties: "x,y"; duration: DStyle.animDuration }
//            }

//            displaced: Transition {
//                NumberAnimation { properties: "x,y"; duration: DStyle.animDuration }
//            }

//            move: Transition {
//                NumberAnimation { properties: "x,y"; duration: DStyle.animDuration }
//            }

//            moveDisplaced: Transition {
//                NumberAnimation { properties: "x,y"; duration: DStyle.animDuration }
//            }

//            populate: Transition {
//                NumberAnimation { duration: DStyle.animDuration }
//            }

            onCurrentIndexChanged: {
                // Set Current File - Get File Path By Index
                assetBrowserController.currentFile = assetsListModel.getPathByIndex(assetsGridView.currentIndex);
            }

            DScrollIndicator {
                id: gridScrollIndicator
                x: parent.width - width
                viewSize: assetsGridView.height
                viewContentSize: assetsGridView.contentHeight
                viewContentPos: assetsGridView.contentY
            }

            // ...
        }
    }

    // Select Button Container
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
