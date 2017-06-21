import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DSection {
    id: transitionsSectionRoot
    width: 300

    property ComponentTransitionsModel transitionsModel: propertiesController.transitionsModel

    title: "Transitions"
    minHeight: transitionsContainer.height + addTransitionButton.height

    state: stateClosed

    signal newTransitionSignal()
    signal editTransitionSignal(var index)

    // Transitions Container
    Item {
        id: transitionsContainer
        width: transitionsSectionRoot.width
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultStatesMax, transitionsListView.count);
        Behavior on height { DAnimation { } }

        // Transitions List View
        DListView {
            id: transitionsListView
            anchors.fill: parent

            model: transitionsSectionRoot.transitionsModel

            delegate: DTransitionItemDelegate {
                width: transitionsListView.width

                itemIndex: index

                stateFrom: model.tmFrom
                stateTo: model.tmTo
                nodesCount: model.tmNodesCount

                onItemActionClicked: {
                    // Remove Transition
                    transitionsSectionRoot.transitionsModel.removeTransition(index);
                }

                onItemClicked: {
                    transitionsListView.currentIndex = index;
                }

                onItemDoubleClicked: {
                    // Emit Edit Transition Launch Signal
                    propertiesPaneRoot.editTransitionLaunch(index);
                }
            }

//            highlight: Rectangle {
//                width: transitionsListView.width
//                height: CONSTS.defaultPaneItemHeight
//                color: DStyle.colorSelectedHighLight
//            }
        }
    }

    Item {
        width: transitionsSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addTransitionButton
        width: transitionsSectionRoot.width
        text: "Add Transition"
        enabled: transitionEditor.state === transitionEditor.stateCreate

        onClicked: {
            // Emit New Transition Launch
            propertiesPaneRoot.newTransitionLaunch();
        }
    }
}
