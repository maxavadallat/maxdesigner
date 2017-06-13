import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "qrc:/qml/style"

DControl {
    id: treeRoot

    width: 400
    height: 300

    property alias model: treeView.model
    property alias delegate: treeView.itemDelegate
    property alias rootIndex: treeView.rootIndex
    property alias treeFocus: treeView.focus
    property alias currentIndex: treeView.currentIndex

    signal itemDoubleClicked(var index)
    signal itemClicked(var index)

    // Collapse All Items
    function collapseAll() {

        // ...

    }

    TreeView {
        id: treeView
        anchors.fill: parent

        alternatingRowColors: false
        backgroundVisible: false
        headerVisible: false

        horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
        verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
        selectionMode: SelectionMode.SingleSelection

        style: TreeViewStyle {
            backgroundColor: "transparent"
            transientScrollBars: true

            frame: Item { }

            rowDelegate: Rectangle {
                height: DStyle.listItemHeight
                color: styleData.selected ? DStyle.colorSelectedHighLight : "transparent"
            }

            highlightedTextColor: DStyle.colorBorder
        }

        onCurrentIndexChanged: {
            //console.log("DTreeView.treeView.onCurrentIndexChanged - currentIndex: " + currentIndex);

        }

        onClicked: {
            treeRoot.itemClicked(index);
        }

        onDoubleClicked: {
            if (isExpanded(index)) {
                collapse(index);
            } else {
                expand(index);
                // Check Expanded
                if (!expanded(index)) {
                    //console.log("DTreeView.treeView.onDoubleClicked - index: " + index);
                    // Emit Item Double Clicked Signal
                    treeRoot.itemDoubleClicked(index);
                }
            }
        }

        TableViewColumn {
            role: "filePath"
            width: treeView.contentItem.width
            elideMode: Text.ElideMiddle
        }
    }

//    DNoContent {
//        anchors.fill: parent
//    }
}
