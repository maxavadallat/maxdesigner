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

        height: {
            // Get Default Height
            var defaultHeight = CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultOwnPropertiesMax, ownPropertiesListView.count);
            // Check If Item Expanded
            if (itemExpanded) {
                return Math.max(itemExpandedPosY + itemExpandedHeight, defaultHeight);
            }

            return defaultHeight;
        }

        property bool itemExpanded: false
        property int itemExpandedHeight: CONSTS.defaultPaneItemHeight
        property int itemExpandedPosY: 0

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
                id: propertyItemDelegate
                width: ownPropertiesListView.width

                namesColumnWidth: ownPropertiesSectionRoot.namesColumnWidth

                itemIndex: index
                propertyName: model.pName
                propertyType: model.pType
                propertyValue: model.pValue
                propertyEnums: model.pEnums
                propertyReadOnly: model.pReadOnly

                showFormula: model.pIsFormula || model.pIsBind
                actionButtonText: !model.pIsProto && !model.pUseProto ? "Reset" : "Delete"

                enableSwipe: model.pIsProto || (!model.pIsProto && !model.pUseProto)

                property int sourceIndex: ownPropertiesListView.opFilter.getSourceIndex(itemIndex)

                onItemActionClicked: {
                    if (model.pIsProto) {
                        // Remove Property
                        propertiesController.removeComponentProperty(propertyName);
                    } else {
                        // Reset Property
                        propertiesController.clearComponentProperty(propertyName);
                    }
                }

                onItemEditClicked: propertiesPaneRoot.editPropertyLaunch(sourceIndex);
                onFormulaEditClicked: propertiesPaneRoot.editFormulaLaunch(propertyName, true);
                onItemValueChanged: propertiesController.setComponentProperty(propertyName, newValue);

                onItemExpandedChanged: {
                    // Set Expanded Item Pos Y
                    ownPropertiesContainer.itemExpandedPosY = propertyItemDelegate.y;
                    // Set Item Expanded Height
                    ownPropertiesContainer.itemExpandedHeight = expandedHeight;
                    // Set Item Expanded
                    ownPropertiesContainer.itemExpanded = itemExpanded;
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
