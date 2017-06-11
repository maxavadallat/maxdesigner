import QtQuick 2.0

import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../controls"
import "../animations"

Row {
    id: minimizedComponentsRoot

    height: DStyle.minimizedComponentsHeight

    property var itemModel: null

    signal itemClicked(var componentName)

//    // Add Item
//    function addItem(item) {
//        itemModel.append({ "componentName": item });
//    }

//    // Remove Item By Name
//    function removeItem(item) {
//        // Get Item Count
//        var iCount = itemModel.count;
//        // Iterate Through Items
//        for (var i=0; i<iCount; i++) {
//            // Get Item Data
//            var iData = itemModel.get(i);
//            // Check Component Name
//            if (iData.componentName === item) {
//                itemModel.remove(i, 1);
//                return;
//            }
//        }
//    }

    Repeater {
        id: minimizedComponentsRepeated
        height: parent.height

        model: minimizedComponentsRoot.model

        delegate: DMouseArea {
            id: delegateRoot

            width: delegateText.width
            height: minimizedComponentsRoot.height

            DText {
                id: delegateText
                height: parent.height
                text: model.componentName
                color: delegateRoot.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            }

            onClicked: {
                minimizedComponentsRoot.itemClicked(model.componentName);
                //removeItem(model.componentName);
            }
        }
    }
}
