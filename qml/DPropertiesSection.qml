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
            height: {
                // Get Default Height
                var defaultHeight = CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultPropertiesMax, basePropertiesListView.count);

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

            // Base Properties List View
            DListView {
                id: basePropertiesListView
                anchors.fill: parent

                model: ComponentOwnPropertiesFilter {
                    filteredNames: propertiesController.filteredProperties
                    sourceModel: propertiesController.propertiesModel ? propertiesController.propertiesModel.componentPropertyList(sectionIndex) : undefined
                }

                itemHeight: CONSTS.defaultPaneItemHeight

                delegate: DPropertyItem {
                    id: propertyItemDelegate
                    width: basePropertiesRepeaterRoot.width
                    namesColumnWidth: basePropertiesRepeaterRoot.namesColumnWidth
                    itemIndex: index
                    propertyName: model.pName
                    propertyType: model.pType
                    propertyValue: model.pValue
                    propertyEnums: model.pEnums
                    showFormula: model.pIsFormula || model.pIsBind
                    enableSwipe: !model.pIsBase
                    opacity: !model.pIsBase ? 1.0 : 0.6

                    actionButtonText: "Clear"

                    onItemActionClicked: propertiesController.clearComponentProperty(propertyName);
                    onFormulaEditClicked: propertiesPaneRoot.editFormulaLaunch(propertyName, false);
                    onItemValueChanged: propertiesController.setComponentProperty(propertyName, newValue);

                    onItemExpandedChanged: {
                        // Set Expanded Item Pos Y
                        basePropertiesContainer.itemExpandedPosY = propertyItemDelegate.y;
                        // Set Item Expanded Height
                        basePropertiesContainer.itemExpandedHeight = expandedHeight;
                        // Set Item Expanded
                        basePropertiesContainer.itemExpanded = itemExpanded;
                    }
                }
            }
        }
    }
}
