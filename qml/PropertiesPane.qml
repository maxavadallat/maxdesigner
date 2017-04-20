import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPane {
    id: propertiesPaneRoot

    width: 300
    height: 600

    property Connections propertiesControllerConnection: Connections {
        target: propertiesController

        onFocusedComponentChanged: {
            // Check Focused Component
            if (propertiesController.focusedComponent !== null) {
                // Check Focused Component
                if (propertiesController.focusedComponent.componentCategory === "NonVisual") {
                    // Hide Size And Pos Section
                    sizeAndPosSection.hide();
                    // Hide Anchors Section
                    anchorsSection.hide();
                } else {
                    // Check If Root Component
                    if (propertiesController.focusedComponent.isRoot) {
                        // Set Position Row Height
                        posRow.height = 0;
                        // Hide Anchors Section
                        anchorsSection.hide();
                    } else {
                        posRow.height = DStyle.spinnerHeight;
                        // Open Anchors Section
                        anchorsSection.open();
                    }

                    // Open Sections
                    sizeAndPosSection.open();
                }

                // Check Focused Component
                if (!propertiesController.focusedComponent.hasProperty("state")) {
                    statesSection.hide();
                    transitionsSection.hide();
                } else {
                    statesSection.close();
                    transitionsSection.close();
                }

            } else {
                // Close All Sections
                importsSection.close();
                sizeAndPosSection.close();
                anchorsSection.close();
                ownPropertiesSection.close();
                signalsSection.close();
                slotsSection.close();
                functionsSection.close();
                statesSection.close();
                transitionsSection.close();
            }
        }

        // ...
    }

    property Connections focusedComponentConnection: Connections {
        target: propertiesController.focusedComponent

        onWidthChanged: {
            console.log("PropertiesPane.focusedComponentConnection.onWidthChanged - width: " + propertiesController.focusedComponent.width);
        }

        onHeightChanged: {
            console.log("PropertiesPane.focusedComponentConnection.onHeightChanged - height: " + propertiesController.focusedComponent.height);
        }
    }

    property int namesColumnWidth: CONSTS.defaultNamesColumnWidth

    title: "Properties" + (propertiesController.focusedComponent ? (" - " + propertiesController.focusedComponent.componentName) : "")

    creationWidth: 300
    creationHeight: 600

    minWidth: 300
    minHeight: 400

    enablePaneContent: propertiesController.focusedComponent !== null

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToRight

    borderColor: DStyle.colorBorder

    state: stateCreate

    signal newImportLaunch()
    signal editImportsLaunch(var index)

    signal newPropertyLaunch()
    signal editPropertyLaunch(var index)

    signal newSignalLaunch()
    signal editSignalLaunch(var index)

    signal newSlotLaunch()
    signal editSlotLaunch(var index)

    signal newFunctionLaunch()
    signal editFunctionLaunch(var index)

    signal editFormulaLaunch()

    signal newStateLaunch()
    signal editStateLaunch(var index)

    signal newTransitionLaunch()
    signal editTransitionLaunch(var index)

    signal stateSelectionLaunch()

    // ID Row
    Row {
        id: idRow
        spacing: 2

        DText {
            id: idTitle
            anchors.verticalCenter: parent.verticalCenter
            text: "id:"
        }

        DTextInput {
            id: idEditor
            width: propertiesPaneRoot.contentWidth - idTitle.width - 2
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentID : ""
            onAccepted: {
                // Request ID
                propertiesController.requestCID(text);
                // Bind To Focused Component ID
                text = Qt.binding(function() {
                    return propertiesController.focusedComponent ? propertiesController.focusedComponent.componentID : "";
                })
            }
        }
    }

    // Object Name Row
    Row {
        id: objectNameRow
        spacing: 2

        DText {
            id: objectNameTitle
            //width: propertiesPaneRoot.contentWidth
            anchors.verticalCenter: parent.verticalCenter
            text: "objectName:"
        }

        DTextInput {
            id: objectNameEditor
            width: propertiesPaneRoot.contentWidth - objectNameTitle.width - 2
            text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentObjectName : ""
            onAccepted: {
                // Request Object Name
                propertiesController.requestCObjectName(text);
                // Bind To Focused Component Object Name
                text = Qt.binding(function() {
                    return propertiesController.focusedComponent ? propertiesController.focusedComponent.componentObjectName : "";
                })
            }
        }
    }

    // Spacer
    Item {
        width: propertiesPaneRoot.contentWidth
        height: DStyle.defaultSpacing
    }

    // Imports Section
    DSection {
        id: importsSection
        width: propertiesPaneRoot.contentWidth
        title: "Imports"
        state: stateClosed

        minHeight: importsFlow.height + addImportButton.height + DStyle.defaultMargin

        DFlow {
            id: importsFlow
            width: propertiesPaneRoot.contentWidth
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
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addImportButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Import"
            enabled: importEditor.state === importEditor.stateCreate

            onClicked: {
                // Emit New Import Launch
                propertiesPaneRoot.newImportLaunch();
            }
        }
    }

    // Size & Pos Section
    DSection {
        id: sizeAndPosSection
        width: propertiesPaneRoot.contentWidth
        title: "Size & Pos"
        minHeight: sizeAndPosFlow.height

        state: stateClosed

        DFlow {
            id: sizeAndPosFlow
            width: propertiesPaneRoot.contentWidth

            Row {
                id: posRow
                spacing: DStyle.defaultSpacing
                Behavior on height { DAnimation { } }
                clip: true

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "x: "
                }

                DSpinner {
                    id: xSpinner
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posX) : 0
                    onValueIncreased: {
                        propertiesController.requestCX(newValue);
                    }
                    onValueDecreased: {
                        propertiesController.requestCX(newValue);
                    }
                    onValueEntered: {
                        propertiesController.requestCX(newValue);
                    }
                }

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "y:"
                }

                DSpinner {
                    id: ySpinner
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.posY) : 0
                    onValueIncreased: {
                        propertiesController.requestCY(newValue);
                    }
                    onValueDecreased: {
                        propertiesController.requestCY(newValue);
                    }
                    onValueEntered: {
                        propertiesController.requestCY(newValue);
                    }
                }
            }

            Row {
                id: sizeRow
                Behavior on height { DAnimation { } }
                spacing: DStyle.defaultSpacing
                clip: true

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "w:"
                }

                DSpinner {
                    id: widthSpinner
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.width) : 0
                    minValue: 0
                    onValueIncreased: {
                        propertiesController.requestCWidth(newValue);
                    }
                    onValueDecreased: {
                        propertiesController.requestCWidth(newValue);
                    }
                    onValueEntered: {
                        propertiesController.requestCWidth(newValue);
                    }
                }

                DText {
                    width: 24
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignRight
                    text: "h:"
                }

                DSpinner {
                    id: heightSpinner
                    anchors.verticalCenter: parent.verticalCenter
                    value: propertiesController.focusedComponent ? Number(propertiesController.focusedComponent.height) : 0
                    minValue: 0
                    onValueIncreased: {
                        propertiesController.requestCHeight(newValue);
                    }
                    onValueDecreased: {
                        propertiesController.requestCHeight(newValue);
                    }
                    onValueEntered: {
                        propertiesController.requestCHeight(newValue);
                    }
                }
            }
        }
    }

    // Anchors Section
    DSection {
        id: anchorsSection
        width: propertiesPaneRoot.contentWidth
        title: "Anchors & Margins"

        state: stateClosed

        Row {
            //height: anchorTargetEditor.height
            spacing: DStyle.defaultMargin * 0.25

            DCheckBox {
                id: anchorFillCheckBox
                width: 40
                rightAligned: true
                text: "fill"
                onClicked: checked = !checked
            }

            Item {
                width: 8
                height: parent.height
            }

            DText {
                id: anchorTargetLabel
                anchors.verticalCenter: parent.verticalCenter
                text: "target:"

            }

            DTextInput {
                width: propertiesPaneRoot.contentWidth - anchorTargetLabel.width - anchorFillCheckBox.width - DStyle.defaultMargin * 0.5 - 12
                anchors.verticalCenter: parent.verticalCenter
                text: "parent"
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: 210

            DCheckBox {
                width: 52
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                rightAligned: true
                text: "Left"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 60
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: "Right"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 52
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                text: "Top"
                onClicked: checked = !checked;
            }

            DCheckBox {
                width: 78
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                text: "Bottom"
                onClicked: checked = !checked;
            }

            Column {
                anchors.centerIn: parent

                DCheckBox {
                    width: 152
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Horizontal Center"
                    onClicked: checked = !checked;
                }

                DCheckBox {
                    width: 78
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Center"
                    onClicked: checked = !checked;
                }

                DCheckBox {
                    width: 152
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Vertical Center"
                    onClicked: checked = !checked;
                }
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - leftMarginSpinner.width - DStyle.defaultMargin / 2
                text: "leftMargin: "
            }

            DSpinner {
                id: leftMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - rightMarginSpinner.width - DStyle.defaultMargin / 2
                text: "rightMargin: "
            }

            DSpinner {
                id: rightMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - topMarginSpinner.width - DStyle.defaultMargin / 2
                text: "topMargin: "
            }

            DSpinner {
                id: topMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - bottomMarginSpinner.width - DStyle.defaultMargin / 2
                text: "bottomMargin: "
            }

            DSpinner {
                id: bottomMarginSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - horizontalCenterOffsetSpinner.width - DStyle.defaultMargin / 2
                text: "horizontal center offs: "
            }

            DSpinner {
                id: horizontalCenterOffsetSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            DText {
                width: propertiesPaneRoot.contentWidth - verticalCenterOffsetSpinner.width - DStyle.defaultMargin / 2
                text: "vertical center offs: "
            }

            DSpinner {
                id: verticalCenterOffsetSpinner
                anchors.verticalCenter: parent.verticalCenter
            }
        }

    }

    // Own Properties Section
    DSection {
        id: ownPropertiesSection
        width: propertiesPaneRoot.contentWidth
        title: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentName : "NULL"
        minHeight: ownPropertiesContainer.height + addOwnPropertyButton.height
        state: stateHidden

//        property Connections proppertiesControllerConnection: Connections {
//            target: propertiesController

//            onFocusedComponentChanged: {
//                // Check Focused Component
//                if (propertiesController.focusedComponent !== null) {
//                    // Open
//                    ownPropertiesSection.open();
//                } else {
//                    // Hide Section
//                    ownPropertiesSection.hide();
//                }
//            }
//        }

        // Own Properties
        Item {
            id: ownPropertiesContainer
            width: propertiesPaneRoot.contentWidth
            height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultOwnPropertiesMax, ownPropertiesListView.count)
            Behavior on height { DAnimation { } }

            DListView {
                id: ownPropertiesListView
                anchors.fill: parent

                model: ComponentOwnPropertiesFilter {
                    filteredNames: propertiesController.filteredProperties
                    sourceModel: propertiesController.ownPropertiesModel
                }

                delegate: DPropertyItem {
                    id: opiDelegateRoot
                    width: ownPropertiesListView.width
                    namesColumnWidth: propertiesPaneRoot.namesColumnWidth

                    itemIndex: index

                    propertyName: pName
                    propertyType: pType
                    propertyValue: pValue

                    onItemActionClicked: {
                        console.log("ownPropertiesListView.delegate.onDeleteItemClicked - itemIndex: " + itemIndex);
                        //console.log("sourceIndex: " + ownPropertiesListView.opfilter.getSourceIndex(itemIndex));

                        // Remove Component Property
                        propertiesController.removeComponentProperty(propertyName);

                        // ...
                    }

                    onFormulaEditClicked: {
                        console.log("ownPropertiesListView.delegate.onDeleteItemClicked - itemIndex: " + itemIndex);

                        // Emit Edit Formula Launch Signal
                        propertiesPaneRoot.editFormulaLaunch();
                        // ...
                    }
                }
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addOwnPropertyButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Property"
            onClicked: {
                // Emit New Property Launch
                propertiesPaneRoot.newPropertyLaunch();
            }
        }
    }

    // Signals Section
    DSection {
        id: signalsSection
        width: propertiesPaneRoot.contentWidth
        title: "Signals"
        minHeight: signalsContainer.height + addSignalButton.height

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

    // Slots Section
    DSection {
        id: slotsSection

        width: propertiesPaneRoot.contentWidth
        title: "Slots"
        minHeight: slotsContainer.height + addSlotButton.height

        // Slots Container
        Item {
            id: slotsContainer
            width: propertiesPaneRoot.contentWidth
            height: CONSTS.defaultPaneItemHeight * Math.min(CONSTS.defaultSlotsMax, slotsListView.count)
            Behavior on height { DAnimation { } }

            DListView {
                id: slotsListView
                anchors.fill: parent
                currentIndex: -1

                model: propertiesController.slotsModel

                delegate: DSlotItemDelegate {
                    width: slotsListView.width
                    itemIndex: index
                    slotName: model.slName + ": {...}"
                    itemCurrent: index === slotsListView.currentIndex

                    onItemClicked: {
                        slotsListView.currentIndex = itemIndex;
                    }

                    onItemDoubleClicked: {
                        // Emit Edit Slot Launch Signal
                        propertiesPaneRoot.editSlotLaunch(itemIndex);
                    }

                    onItemActionClicked: {
                        propertiesController.slotsModel.removeSlot(itemIndex);
                    }
                }
            }
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addSlotButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Slot"
            enabled: slotEditor.state === slotEditor.stateCreate

            onClicked: {
                // Emit New Slot Launch
                propertiesPaneRoot.newSlotLaunch();
            }
        }
    }

    // Functions Section
    DSection {
        id: functionsSection
        width: propertiesPaneRoot.contentWidth
        title: "Functions"
        minHeight: functionsContainer.height + addSignalButton.height

        // Functions Container
        Item {
            id: functionsContainer
            width: propertiesPaneRoot.contentWidth
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
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addFunctionButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Function"
            enabled: functionEditor.state === functionEditor.stateCreate

            onClicked: {
                // Emit New Function Launch
                propertiesPaneRoot.newFunctionLaunch();
            }
        }
    }

    // States Section
    DSection {
        id: statesSection
        width: propertiesPaneRoot.contentWidth
        title: "States"
        minHeight: statesContainer.height + addStateButton.height

        state: stateClosed

        // States
        Item {
            id: statesContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addStateButton
            width: propertiesPaneRoot.contentWidth
            text: "Add State"
            enabled: stateEditor.state === stateEditor.stateCreate

            onClicked: {
                // Emit New State Launch
                propertiesPaneRoot.newStateLaunch();
            }
        }
    }

    // Transitions Section
    DSection {
        id: transitionsSection
        width: propertiesPaneRoot.contentWidth
        title: "Transitions"
        minHeight: transitionsContainer.height + addTransitionButton.height

        state: stateClosed

        // Transitions
        Item {
            id: transitionsContainer
            width: propertiesPaneRoot.contentWidth
            height: 0

            // ...
        }

        Item {
            width: propertiesPaneRoot.contentWidth
            height: DStyle.defaultMargin
        }

        DButton {
            id: addTransitionButton
            width: propertiesPaneRoot.contentWidth
            text: "Add Transition"
            enabled: transitionEditor.state === transitionEditor.stateCreate

            onClicked: {
                // Emit New Transition Launch
                propertiesPaneRoot.newTransitionLaunch();
            }
        }
    }

    // Base Properties Repeater
    Repeater {
        id: basePropertiesRepeater
        model: propertiesController.propertiesModel
        visible: false

        delegate: DSection {
            id: basePropertiesSection
            width: propertiesPaneRoot.contentWidth
            title: "Item"

            state: stateHidden

            // ...
        }
    }
}
