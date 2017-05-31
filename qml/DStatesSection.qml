import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: statesSectionRoot
    width: 360

    property ComponentStatesModel statesModel: propertiesController.statesModel

    title: "States"
    minHeight: statesContainer.height + addStateButton.height

    state: stateClosed

    signal newStateSignal()
    signal editStateSignal(var index)

    // States
    Item {
        id: statesContainer
        width: statesSectionRoot.width
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultStatesMax, statesListView.count);
        Behavior on height { DAnimation { } }

        DListView {
            id: statesListView
            anchors.fill: parent

            model: statesSectionRoot.statesModel

            delegate: DStateItem {
                width: statesListView.width

                itemIndex: index

                stateName: model.stateName
                stateWhen: model.stateWhen
                statePropertyChanges: model.stateChanges

                onItemActionClicked: {
                    // Remove State
                    statesSectionRoot.statesModel.removeState(index);
                }

                onItemDoubleClicked: {
                    // Emit Edit State Launch Signal
                    propertiesPaneRoot.editStateLaunch(index);
                    // Emit Edit State Signal
                    //statesSectionRoot.editStateSignal(index);
                }
            }
        }
    }

    Item {
        width: statesSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addStateButton
        width: statesSectionRoot.width
        text: "Add State"
        enabled: stateEditor.state === stateEditor.stateCreate

        onClicked: {
            // Emit New State Launch
            propertiesPaneRoot.newStateLaunch();
            // Emit New State Signal
            //statesSectionRoot.newStateSignal();
        }
    }
}
