import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

Repeater {
    id: basePropertiesRepeaterRoot
    width: 300

    property int namesColumnWidth: width * 0.35

    model: propertiesController.propertiesModel

    // Base Property Section Delegate
    delegate: DSection {
        id: basePropertiesSectionDelegate
        width: basePropertiesRepeaterRoot.width
        title: baseName

        minHeight: basePropertiesContainer.height + 1

        state: basePropertiesListView.count > 0 ? stateClosed : stateHidden

        property int sectionIndex: index

        // Base Properties Container
        Item {
            id: basePropertiesContainer
            width: basePropertiesRepeaterRoot.width
            height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultPropertiesMax, basePropertiesListView.count)
            Behavior on height { DAnimation { } }

            // Base Properties List View
            DListView {
                id: basePropertiesListView
                anchors.fill: parent

                model: ComponentOwnPropertiesFilter {
                    filteredNames: propertiesController.filteredProperties
                    sourceModel: propertiesController.propertiesModel ? propertiesController.propertiesModel.componentPropertyList(sectionIndex) : undefined
                }

                delegate: DPropertyItem {
                    id: propertyItemDelegate
                    width: basePropertiesRepeaterRoot.width
                    namesColumnWidth: basePropertiesRepeaterRoot.namesColumnWidth

                    itemIndex: index

                    propertyName: model.pName
                    propertyType: model.pType
                    propertyValue: model.pValue
                    showFormula: model.pIsFormula
                    enableSwipe: !model.pIsBase
                    opacity: !model.pIsBase ? 1.0 : 0.6
                    actionButtonText: "Clear"

                    onItemActionClicked: {
                        // Clear Component Property
                        propertiesController.clearComponentProperty(propertyName);
                    }

                    onFormulaEditClicked: {
                        // Emit Edit Formula Launch Signal
                        propertiesPaneRoot.editFormulaLaunch(propertyName, false);
                    }

                    onItemValueChanged: {
                        console.log("PropertiesPane.propertyItemDelegate.onItemValueChanged - propertyName: " + propertyName + " - newValue: " + newValue);
                        // Set Property Value
                        propertiesController.setComponentProperty(propertyName, newValue);
                    }
                }
            }
        }
    }
}
