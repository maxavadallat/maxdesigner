import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: signalsSectionRoot

    width: 300
    title: "Signals"
    minHeight: signalsContainer.height + addSignalButton.height

    state: stateClosed

    // Signals Container
    Item {
        id: signalsContainer
        width: propertiesPaneRoot.contentWidth
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultSignalsMax, signalsListView.count)
        Behavior on height { DAnimation { } }

        DListView {
            id: signalsListView
            anchors.fill: parent
            currentIndex: -1

            model: propertiesController.signalsModel

            delegate: DSignalItemDelegate {
                width: signalsListView.width
                itemIndex: index
                signalName: model.signalName + "(" + signalParameters + ")";
                itemCurrent: index === signalsListView.currentIndex

                onItemClicked: {
                    signalsListView.currentIndex = itemIndex;
                }

                onItemDoubleClicked: {
                    // Emit Edit Signal Launch Signal
                    propertiesPaneRoot.editSignalLaunch(itemIndex);
                }

                onItemActionClicked: {
                    propertiesController.signalsModel.removeSignal(itemIndex);
                }
            }
        }
    }

    Item {
        width: propertiesPaneRoot.contentWidth
        height: DStyle.defaultMargin
    }

    DButton {
        id: addSignalButton
        width: propertiesPaneRoot.contentWidth
        text: "Add Signal"
        enabled: signalEditor.state === signalEditor.stateCreate

        onClicked: {
            // Emit New Signal Launch Signal
            propertiesPaneRoot.newSignalLaunch();
        }
    }
}
