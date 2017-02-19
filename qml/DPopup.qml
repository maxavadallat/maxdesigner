import QtQuick 2.0

import "Style.js" as STYLE

DRectangle {
    id: popupRoot

    width: 0
    height: 0

    Behavior on width { DAnimation { } }
    Behavior on height { DAnimation { } }

    property int popupWidth: popupRoot.maxItemWidth
    property int popupHeight: popupColumn.height + STYLE.defaultMargin * 2

    property list<QtObject> model

    property int maxItemWidth: STYLE.defaultPopupWidth

    property int currentIndex: -1

    property bool subPopup: false

    property bool hiding: false

    visible: popupRoot.width > 0 && popupRoot.height > 0

    clip: true

    signal itemSelected(var itemIndex)
    signal subMenuItemSelected(var itemIndex, var itemPosY)
    signal itemHovered(var itemIndex, var subMenuItem)
    signal subPopupHidden()

    onModelChanged: {
        maxItemWidth = STYLE.defaultPopupWidth;
        currentIndex = 0;
    }

    onPopupHeightChanged: {
        //console.log("DPopup.onPopupHeightChanged - popupHeight: " + popupHeight);
    }

    onHeightChanged: {
        if (height === 0) {
            // Reset Hiding
            popupRoot.hiding = false;
        }
    }

    // Show Popup
    function show(posX, posY) {
        // Reset Current Index
        popupRoot.currentIndex = -1;

        // Set Pos
        popupRoot.x = posX;
        popupRoot.y = posY;

        // Set Width & Height
        popupRoot.width = popupRoot.popupWidth;
        popupRoot.height = Qt.binding(function() { return popupRoot.popupHeight; } );

        // Set Focus
        popupRoot.focus = true;
    }

    // Hide Popup
    function hide() {
        // Set Hiding
        popupRoot.hiding = true;

        // Reset Width & Height
        popupRoot.width = 0;
        popupRoot.height = 0;
        // Reset Focus
        popupRoot.focus = false;

        // Check If SubPopup
        if (popupRoot.subPopup) {
            // Emit Popup Hidden Signal
            popupRoot.subPopupHidden();
        }
    }

    // Items Column
    Column {
        id: popupColumn
        width: parent.width

        anchors.verticalCenter: parent.verticalCenter

        onHeightChanged: {
            //console.log("DPopup.popupColumn.onHeightChanged - height: " + height);
        }

        Repeater {
            id: popupRepeated

            model: popupRoot.model

            delegate: DPopupItem {
                id: delegateRoot
                width: popupRoot.width
                itemIndex: index
                text: model.text
                enabled: !model.disabled
                subMenuItem: model.subMenuItem
                selected: itemIndex === popupRoot.currentIndex
                preventStealing: true

                Component.onCompleted: {
                    // Set Max Item Width
                    popupRoot.maxItemWidth = Math.max(popupRoot.maxItemWidth, delegateRoot.textWidth);
                    //console.log("DPopup.delegateRoot.onCompleted - text: " + delegateRoot.text + " - textWidth: " + textWidth);
                    //console.log("DPopup.delegateRoot.onCompleted - text: " + delegateRoot.text + " - y: " + y);
                }

                onEntered: {
                    // Set Current Index
                    popupRoot.currentIndex = itemIndex;
                    // Emit Item Hovered Signal
                    popupRoot.itemHovered(itemIndex, subMenuItem);
                }

                onExited: {
                    popupRoot.currentIndex = -1;
                }

                onClicked: {
                    // Check If Sub Menu Item
                    if (subMenuItem) {
                        // Emit Submenu Item Selected Signal
                        popupRoot.subMenuItemSelected(itemIndex, y);
                    } else {
                        // Emit Item Selected Signal
                        popupRoot.itemSelected(itemIndex);
                        // Hide Popup
                        popupRoot.hide();
                    }
                }

                onSubMenuItemSelected: {
                    //console.log("DPopup.delegateRoot.onSubMenuItemSelected - text: " + delegateRoot.text + " - y: " + y);
                    // Emit Submenu Item Selected Signal
                    popupRoot.subMenuItemSelected(itemIndex, y);
                }
            }
        }
    }

    Keys.onReleased:  {
        switch (event.key) {
            case Qt.Key_Escape:
                popupRoot.hide();
            break;
        }
    }
}
