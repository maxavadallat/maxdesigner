import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: slotsSectionRoot

    width: 300

    title: "Slots"
    minHeight: slotsContainer.height + addSlotButton.height

    state: stateClosed

    // Slots Container
    Item {
        id: slotsContainer
        width: slotsSectionRoot.width
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultSlotsMax, slotsListView.count)
        Behavior on height { DAnimation { } }

        DListView {
            id: slotsListView
            anchors.fill: parent
            currentIndex: -1

            model: propertiesController.slotsModel

            delegate: DSlotItemDelegate {
                width: slotsListView.width
                itemIndex: index
                slotName: model.slName + ": {...}"
                itemCurrent: index === slotsListView.currentIndex

                onItemClicked: {
                    slotsListView.currentIndex = itemIndex;
                }

                onItemDoubleClicked: {
                    // Emit Edit Slot Launch Signal
                    propertiesPaneRoot.editSlotLaunch(itemIndex);
                }

                onItemActionClicked: {
                    propertiesController.slotsModel.removeSlot(itemIndex);
                }
            }
        }
    }

    Item {
        width: slotsSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addSlotButton
        width: slotsSectionRoot.width
        text: "Add Slot"
        enabled: slotEditor.state === slotEditor.stateCreate

        onClicked: {
            // Emit New Slot Launch
            propertiesPaneRoot.newSlotLaunch();
        }
    }
}
