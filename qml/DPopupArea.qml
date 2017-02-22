import QtQuick 2.0

DMouseArea {
    id: popupAreaRoot

    z: 0.1

    property alias model: mainPopup.model

    acceptedButtons: { Qt.RightButton }

//    hoverEnabled: false
//    drag.filterChildren: true

    signal itemSelected(var itemIndex)
    signal subItemSelected(var itemIndex)

    onClicked: {
        if (mouse.button === Qt.RightButton) {
            // Hide Sub Popup
            subPopup.hide();
            // Show Popup
            mainPopup.show(mouse.x, mouse.y);
        } else {
            // Hide Sub Popup
            subPopup.hide();
            // Hide Popup
            mainPopup.hide();
        }
    }

    // Hide Popups
    function hidePopups() {
        mainPopup.hide();
        subPopup.hide();
    }

    DPopup {
        id: mainPopup

        model: [
            DPopupItemObject { text: "Item 1" },
            DPopupItemObject { text: "Item Test 2" },
            DPopupItemObject { text: "-" },
            DPopupItemObject { text: "Item 3"; disabled: true },
            DPopupItemObject { text: "-" },
            DPopupItemObject { text: "Item 4"; subMenuItem: true; subMenu: [
                DPopupItemObject { text: "SubItem 1" },
                DPopupItemObject { text: "SubItem 2" },
                DPopupItemObject { text: "SubItem 3" },
                DPopupItemObject { text: "SubItem 4" }
            ] },
            DPopupItemObject { text: "Item 5" }
        ]

        onItemHovered: {
            //console.log("mainPopup.onItemHovered - itemIndex: " + itemIndex + " - subMenuItem: " + subMenuItem);
            // Check If Sub Item
            if (!subMenuItem) {
                // Hide Sub Popup
                subPopup.hide();
            }
        }

        onItemSelected: {
            //console.log("popupAreaRoot.mainPopup.onItemSelected - itemIndex: " + itemIndex);
            // Emit Item Selected Signal
            popupAreaRoot.itemSelected(itemIndex);
        }

        onSubMenuItemSelected: {
            //console.log("popupAreaRoot.mainPopup.onSubMenuItemSelected - itemIndex: " + itemIndex);
            // Set Sub Menu Popup Model
            subPopup.model = mainPopup.model[itemIndex].subMenu;
            // Show Sub-Popup
            subPopup.show(mainPopup.x + mainPopup.width, mainPopup.y + itemPosY);
        }
    }

    DPopup {
        id: subPopup
        subPopup: true

        onItemSelected: {
            //console.log("popupAreaRoot.subPopup.onItemSelected - itemIndex: " + itemIndex);
            // Hide Main Popup
            mainPopup.hide();
            // Emit Sub Item Selected Signal
            popupAreaRoot.subItemSelected(itemIndex);
        }

        onSubPopupHidden: {
            // Check If Hiding
            if (!mainPopup.hiding) {
                // Restore Focus
                mainPopup.focus = true;
            }
        }
    }
}
