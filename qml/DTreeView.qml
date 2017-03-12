import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "style"

DControl {
    id: treeRoot

    width: 400
    height: 300

    property alias model: treeView.model
    property alias delegate: treeView.itemDelegate
    property alias rootIndex: treeView.rootIndex

//    function isExpanded(x, y) {
//        var mi = treeView.indexAt(a, y);
//        return treeView.isExpanded(mi);
//    }

//    function expand(x, y) {
//        var mi = treeView.indexAt(a, y);
//        treeView.expand(mi);
//    }

//    function collapse(x, y) {
//        var mi = treeView.indexAt(a, y);
//        treeView.collapse(mi);
//    }

    signal itemDoubleClicked(var index)

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

        style: TreeViewStyle {
            backgroundColor: "transparent"
            transientScrollBars: true
            frame: Item { }
            rowDelegate: Rectangle {
                height: Style.listItemHeight
                color: styleData.selected ? Style.colorSelectedHighLight : "transparent"
            }
            highlightedTextColor: Style.colorBorder
        }

        onCurrentIndexChanged: {
            //console.log("DTreeView.treeView.onCurrentIndexChanged - currentIndex: " + currentIndex);
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
        }
    }

//    DNoContent {
//        anchors.fill: parent
//    }
}
