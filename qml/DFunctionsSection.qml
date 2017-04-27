import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: functionsSectionRoot
    width: 300
    title: "Functions"
    minHeight: functionsContainer.height + addFunctionButton.height
    state: stateClosed

    // Functions Container
    Item {
        id: functionsContainer
        width: functionsSectionRoot.width
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultFunctionsMax, functionsListView.count)
        Behavior on height { DAnimation { } }

        DListView {
            id: functionsListView
            anchors.fill: parent
            currentIndex: -1

            model: propertiesController.functionsModel

            delegate: DFunctionItemDelegate {
                width: functionsListView.width
                itemIndex: index
                functionName: model.fName + "(" + model.fParams + ") {...}"
                itemCurrent: index === functionsListView.currentIndex

                onItemClicked: {
                    functionsListView.currentIndex = itemIndex;
                }

                onItemDoubleClicked: {
                    // Emit Edit Function Launch Signal
                    propertiesPaneRoot.editFunctionLaunch(itemIndex);
                }

                onItemActionClicked: {
                    propertiesController.functionsModel.removeFunction(itemIndex);
                }
            }
        }
    }

    Item {
        width: functionsSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addFunctionButton
        width: functionsSectionRoot.width
        text: "Add Function"
        enabled: functionEditor.state === functionEditor.stateCreate

        onClicked: {
            // Emit New Function Launch
            propertiesPaneRoot.newFunctionLaunch();
        }
    }
}
