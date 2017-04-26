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
                // Set ID Editor Text
                idEditor.text = propertiesController.focusedComponent.componentID;
                // Set Object Name Editor Text
                objectNameEditor.text = propertiesController.focusedComponent.componentObjectName;

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

                // Show Own Properties Section
                ownPropertiesSection.open();

                // Show Properties Section

                // ...

            } else {
                // Reset Editors
                idEditor.text = "";
                objectNameEditor.text = "";

                // ...

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
                // Properties section
            }
        }

        // ...
    }

    property Connections focusedComponentConnection: Connections {
        target: propertiesController.focusedComponent

    }

    property int namesColumnWidth: propertiesPaneRoot.width * 0.35 //CONSTS.defaultNamesColumnWidth

    title: "Properties" + (propertiesController.focusedComponent ? (" - " + propertiesController.focusedComponent.componentName) : "")

    creationWidth: settingsController ? settingsController.propertiesPaneWidth : 300
    creationHeight: settingsController ? settingsController.propertiesPaneHeight : 600

    minWidth: 300
    minHeight: parent ? parent.height * 0.6 : 600

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

    signal editFormulaLaunch(var propertyName, var ownProperty)

    signal newSignalLaunch()
    signal editSignalLaunch(var index)

    signal newSlotLaunch()
    signal editSlotLaunch(var index)

    signal newFunctionLaunch()
    signal editFunctionLaunch(var index)

    signal newStateLaunch()
    signal editStateLaunch(var index)

    signal newTransitionLaunch()
    signal editTransitionLaunch(var index)

    signal stateSelectionLaunch()

    onWidthChanged: {
        // Check State
        if (propertiesPaneRoot.state === propertiesPaneRoot.stateShown) {
            // Store Properties Pane Width
            settingsController.propertiesPaneWidth = propertiesPaneRoot.width;
        }
    }

    onHeightChanged: {
        // Check State
        if (propertiesPaneRoot.state === propertiesPaneRoot.stateShown) {
            // Store Properties Pane Height
            settingsController.propertiesPaneHeight = propertiesPaneRoot.height;
        }
    }

    // ID Row
    Row {
        id: idRow
        spacing: 2

        DText {
            id: idTitle
            width: objectNameTitle.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "id:"
        }

        DTextInput {
            id: idEditor
            width: propertiesPaneRoot.contentWidth - idTitle.width - 2
            text: ""

            onTextChanged: {
                // Check Current Component ID
                if (propertiesController.cID !== idEditor.text) {
                    // Request New Component ID
                    propertiesController.requestCID(idEditor.text);
                }
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
            horizontalAlignment: Text.AlignRight
            text: "objectName:"
        }

        DTextInput {
            id: objectNameEditor
            width: propertiesPaneRoot.contentWidth - objectNameTitle.width - 2
            text: ""

            onTextChanged: {
                // Check Component Object Name
                if (propertiesController.cObjectName !== objectNameEditor.text) {
                    // Request New Object Name
                    propertiesController.requestCObjectName(objectNameEditor.text);
                }
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

                    onKeyEvent: {
                        if (event.key === Qt.Key_Tab) {
                            // Set Y Spinner Focus
                            ySpinner.setSpinnerFocus(true, true);
                        }
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

                    onKeyEvent: {
                        if (event.key === Qt.Key_Tab) {
                            // Set Width Spinner Focus
                            widthSpinner.setSpinnerFocus(true, true);
                        }
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

                    onKeyEvent: {
                        if (event.key === Qt.Key_Tab) {
                            // Set Height Spinner Focus
                            heightSpinner.setSpinnerFocus(true, true);
                        }
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

                    onKeyEvent: {
                        if (event.key === Qt.Key_Tab) {
                            // Check Pos Row height
                            if (posRow.height > 0) {
                                // Set X Spinner Focus
                                xSpinner.setSpinnerFocus(true, true);
                            } else {
                                // Set Width Spinner Focus
                                widthSpinner.setSpinnerFocus(true, true);
                            }
                        }
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
                checked: propertiesController.anchorsModel ? propertiesController.anchorsModel.anchorsFill.length > 0 : false
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

        // Own Properties
        Item {
            id: ownPropertiesContainer
            width: propertiesPaneRoot.contentWidth
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

                    namesColumnWidth: propertiesPaneRoot.namesColumnWidth

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

        // Base Property Section Delegate
        delegate: DSection {
            id: basePropertiesSectionDelegate
            width: propertiesPaneRoot.contentWidth
            title: baseName

            minHeight: basePropertiesContainer.height + 1

            state: basePropertiesListView.count > 0 ? stateClosed : stateHidden

            property int sectionIndex: index

            // Base Properties Container
            Item {
                id: basePropertiesContainer
                width: propertiesPaneRoot.contentWidth
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
                        width: propertiesPaneRoot.contentWidth
                        namesColumnWidth: propertiesPaneRoot.namesColumnWidth

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
}
