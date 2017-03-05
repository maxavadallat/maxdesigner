import QtQuick 2.0

import "Constants.js" as CONSTS
import "style"

Row {
    id: minimizedComponentsRoot

    height: Style.minimizedComponentsHeight

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
                color: delegateRoot.pressed ? Style.colorBorder : Style.colorFontDark
            }

            onClicked: {
                minimizedComponentsRoot.itemClicked(model.componentName);
                //removeItem(model.componentName);
            }
        }
    }
}
