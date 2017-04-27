import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: ownPropertiesSectionRoot
    width: 300

    property int namesColumnWidth: width * 0.35

    title: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentName : "NULL"
    minHeight: ownPropertiesContainer.height + addOwnPropertyButton.height

    state: stateClosed

    // Own Properties
    Item {
        id: ownPropertiesContainer
        width: ownPropertiesSectionRoot.width
        height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultOwnPropertiesMax, ownPropertiesListView.count)
        Behavior on height { DAnimation { } }

        DListView {
            id: ownPropertiesListView
            anchors.fill: parent

            property ComponentOwnPropertiesFilter opFilter: ComponentOwnPropertiesFilter {
                filteredNames: propertiesController.filteredProperties
                sourceModel: propertiesController.ownPropertiesModel
            }

            model: opFilter

            delegate: DPropertyItem {
                id: opiDelegateRoot
                width: ownPropertiesListView.width

                namesColumnWidth: ownPropertiesSectionRoot.namesColumnWidth

                itemIndex: index

                propertyName: model.pName
                propertyType: model.pType
                propertyValue: model.pValue
                showFormula: model.pIsFormula

                property int sourceIndex: ownPropertiesListView.opFilter.getSourceIndex(itemIndex)

                onItemActionClicked: {
                    // Check Own Properties Model
                    if (propertiesController.ownPropertiesModel !== null) {
                        //console.log("ownPropertiesListView.delegate.onDeleteItemClicked - sourceIndex: " + ownPropertiesListView.opFilter.getSourceIndex(itemIndex));
                        // Remove Own Property
                        propertiesController.ownPropertiesModel.removeComponentProperty(sourceIndex);
                    }
                }

                onItemEditClicked: {
                    // Emit Edit Property Launch Signal
                    propertiesPaneRoot.editPropertyLaunch(sourceIndex);
                }

                onFormulaEditClicked: {
                    // Emit Edit Formula Launch Signal
                    propertiesPaneRoot.editFormulaLaunch(propertyName, true);
                }

                onItemValueChanged: {
                    // Set Own Property Value
                    propertiesController.setComponentProperty(propertyName, newValue);
                }
            }
        }
    }

    Item {
        width: ownPropertiesSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addOwnPropertyButton
        width: ownPropertiesSectionRoot.width
        text: "Add Property"
        onClicked: {
            // Emit New Property Launch
            propertiesPaneRoot.newPropertyLaunch();
        }
    }
}
