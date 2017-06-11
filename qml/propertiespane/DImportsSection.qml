import QtQuick 2.0

import enginecomponents 0.1

import "../system/DConstants.js" as CONSTS
import "../style"
import "../system"
import "../controls"
import "../animations"

DSection {
    id: importsSectionRoot
    width: 300
    title: "Imports"
    state: stateClosed

    minHeight: importsContainer.height + addImportButton.height + DStyle.defaultMargin

    Item {
        id: importsContainer
        width: importsSectionRoot.width
        height: importsFlow.height
        Behavior on height { DAnimation { } }
        clip: true

        DFlow {
            id: importsFlow
            width: importsSectionRoot.width
            spacing: DStyle.defaultSpacing

            Repeater {
                id: importsRepeater
                model: propertiesController ? propertiesController.importsModel : undefined

                delegate: DTag {
                    tagTitle: importName
                    onRemoveClicked: {
                        // Remove Import
                        propertiesController.importsModel.removeImport(index);
                    }
                }
            }
        }
    }

    Item {
        width: importsSectionRoot.width
        height: DStyle.defaultMargin
    }

    DButton {
        id: addImportButton
        width: importsSectionRoot.width
        text: "Add Import"
        enabled: importEditor.state === importEditor.stateCreate

        onClicked: {
            // Emit New Import Launch
            propertiesPaneRoot.newImportLaunch();
        }
    }
}
