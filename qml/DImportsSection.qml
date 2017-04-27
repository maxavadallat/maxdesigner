import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DSection {
    id: importsSectionRoot
    width: 300
    title: "Imports"
    state: stateClosed

    minHeight: importsFlow.height + addImportButton.height + DStyle.defaultMargin

    DFlow {
        id: importsFlow
        width: importsSectionRoot.contentWidth
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

    Item {
        width: importsSectionRoot.contentWidth
        height: DStyle.defaultMargin
    }

    DButton {
        id: addImportButton
        width: importsSectionRoot.contentWidth
        text: "Add Import"
        enabled: importEditor.state === importEditor.stateCreate

        onClicked: {
            // Emit New Import Launch
            propertiesPaneRoot.newImportLaunch();
        }
    }
}
