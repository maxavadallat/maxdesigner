import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/system"
import "qrc:/qml/controls"
import "qrc:/qml/animations"

DSection {
    id: sizeAndPosSectionRoot
    width: 300

    // Component Info
    property ComponentInfo componentInfo: propertiesController.focusedComponent

    readonly property int labelWidth: 32
    readonly property int editButtonWidth: 48

    title: "Size & Pos"
    minHeight: sizeAndPosColumn.height
    state: stateClosed

    // Flip Pos X Editor
    function flipPosXEditor(flipState) {
        // Set Flipped State
        posXItemDelegate.setFlipX(flipState);
    }

    // Flip Pos Y Editor
    function flipPosYEditor(flipState) {
        // Set Flipped State
        posYItemDelegate.setFlipY(flipState);
    }

    // Flip Wisth Editor
    function flipWidthEditor(flipState) {
        // Set Flipped State
        widthItemDelegate.setFlipWidth(flipState);
    }

    // Flip Height Editor
    function flipHeightEditor(flipState) {
        // Set Flipped State
        heightItemDelegate.setFlipHeight(flipState);
    }

    Column {
        id: sizeAndPosColumn
        width: sizeAndPosSectionRoot.width
        spacing: DStyle.defaultSpacing
        move: Transition { }

        Row {
            id: posRow
            height: {
                // Check Focused Component
                if (sizeAndPosSectionRoot.componentInfo && sizeAndPosSectionRoot.componentInfo.isRoot) {
                    return 0;
                }

                return DStyle.spinnerHeight;
            }

            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            visible: height > 0
            clip: true

            DPosXItemDelegate {
                id: posXItemDelegate
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
                height: DStyle.spinnerHeight
                onTabKeyPressed: {
                    // Set Editor Focus
                    posYItemDelegate.setEditorFocus(true);
                }
            }

            DPosYItemDelegate {
                id: posYItemDelegate
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
                height: DStyle.spinnerHeight
                onTabKeyPressed: {
                    // Set Editor Focus
                    widthItemDelegate.setEditorFocus(true);
                }
            }
        }

        Row {
            id: sizeRow
            height: sizeAndPosSectionRoot.componentInfo ? DStyle.spinnerHeight : 0
            Behavior on height { DAnimation { } }
            spacing: DStyle.defaultSpacing
            visible: height > 0
            clip: true

            DWidthItemDelegate {
                id: widthItemDelegate
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
                height: DStyle.spinnerHeight
                onTabKeyPressed: {
                    // Set Editor Focus
                    heightItemDelegate.setEditorFocus(true);
                }
            }

            DHeightItemDelegate {
                id: heightItemDelegate
                width: (sizeAndPosColumn.width - DStyle.defaultSpacing) * 0.5
                height: DStyle.spinnerHeight
                onTabKeyPressed: {
                    // Check If Pod Row Visible
                    if (posRow.visible) {
                        // Set Editor Focus
                        posXItemDelegate.setEditorFocus(true);
                    } else {
                        // Set Editor Focus
                        widthItemDelegate.setEditorFocus(true);
                    }
                }
            }
        }
    }
}
