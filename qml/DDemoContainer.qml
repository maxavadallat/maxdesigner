import QtQuick 2.7
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DContainer {
    id: demoContainerRoot

    width: 800
    height: 800

    clip: true

    enablePosOverlay: false
    enableSizeOverlay: false

    drag.filterChildren: false

    minWidth: 400
    minHeight: 400

    property int contentWidth: 400

    // Bring To Front
    function bringToFront(item) {
        // Check Item
        if (item === null || item === undefined) {
            return;
        }

        // Get Item Position
        var posX = item.x;
        var posY = item.y;

        // Set Item Parent To null To Remove From Children
        item.parent = null;
        // Set Item Parent To Bring To Front
        item.parent = demoContainerRoot;

        // Set Item Position
        item.x = posX;
        item.y = posY;
    }


    Component.onCompleted: {
        // Open Project
        //mainController.openProject("/Users/max/Dev/Temp/myproject/myproject.json");

        // Select Component
        //propertiesController.selectComponent("AppTile", 0);

        // Show Property Editor
        //propertyEditor.show();

        // Select Component
        //propertiesController.selectComponent("MyRectangle");

        // Set Component Info
        //demoPane.componentInfo = propertiesController.focusedComponent;

        // Set Root Component
        //demoNodeTree.rootComponent = propertiesController.focusedComponent;

        demoContainer.x = (demoContainerRoot.width - demoContainer.width) * 0.5;
        demoContainer.y = (demoContainerRoot.height - demoContainer.height) * 0.5;
    }

    DButton {
        width: 196
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin

        text: demoPane.state === demoPane.stateCreate ? "Create Node Pane" : "Reset Node Pane"

        onClicked: {
            if (demoPane.state === demoPane.stateCreate) {
                demoPane.show();
            } else {
                demoPane.reset(false);
            }
        }
    }

    DButton {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        text: "Add Child"

        onClicked: {

            // Previous Focused Component
            var lastFocused = propertiesController.focusedComponent;

            // Select Item
            propertiesController.selectComponent("Item");
            // Get New Item Clone
            var newItem = propertiesController.focusedComponent.clone();

            // Set Focused Component
            propertiesController.focusedComponent = lastFocused;

            // Check Focused Component

            // Add Child
            //propertiesController.focusedComponent.addChild(newItem);

            // Insert Child
            propertiesController.focusedComponent.insertChild(0, newItem);
        }
    }

    DContainer {
        id: demoContainer
        width: 200
        height: 300

        minWidth: 100
        minHeight: 100

        DNodePane {
            id: demoPane

            parent: demoContainer

            anchors.verticalCenter: parent.verticalCenter
        }
    }


/*
    DButton {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        text: "Add Child"

        onClicked: {

            // Previous Focused Component
            var lastFocused = propertiesController.focusedComponent;

            // Select Item
            propertiesController.selectComponent("Item");
            // Get New Item Clone
            var newItem = propertiesController.focusedComponent.clone();

            // Set Focused Component
            propertiesController.focusedComponent = lastFocused;

            // Check Focused Component

            // Add Child
            //propertiesController.focusedComponent.addChild(newItem);

            // Insert Child
            propertiesController.focusedComponent.insertChild(0, newItem);
        }
    }

    DNodeTree {
        id: demoNodeTree
        width: parent.width * 0.6
        height: parent.height * 0.8
        anchors.centerIn: parent

        DNodeTreeNode {
            width: parent.width * CONSTS.defaultNodeScaleRatio
            anchors.right: parent.right
            expanded: true

            DNodeTreeNode {
                width: parent.width * CONSTS.defaultNodeScaleRatio
                anchors.right: parent.right
            }

            DNodeTreeNode {
                width: parent.width * CONSTS.defaultNodeScaleRatio
                anchors.right: parent.right
            }

            DNodeTreeNode {
                width: parent.width * CONSTS.defaultNodeScaleRatio
                anchors.right: parent.right
                expanded: true

                DNodeTreeNode {
                    width: parent.width * CONSTS.defaultNodeScaleRatio
                    anchors.right: parent.right
                }

                DNodeTreeNode {
                    width: parent.width * CONSTS.defaultNodeScaleRatio
                    anchors.right: parent.right
                }

                DNodeTreeNode {
                    width: parent.width * CONSTS.defaultNodeScaleRatio
                    anchors.right: parent.right
                }
            }
        }

        DNodeTreeNode {
            width: parent.width * CONSTS.defaultNodeScaleRatio
            anchors.right: parent.right
        }

        DNodeTreeNode {
            width: parent.width * CONSTS.defaultNodeScaleRatio
            anchors.right: parent.right
        }

    }
*/

//    DPropertyItemValue {
//        anchors.centerIn: parent
//        propertyEnums: "Image.Stretch,Image.PreserveAspectFit,Image.PreserveAspectCrop,Image.Tile,Image.TileVertically,Image.TileHorizontally,Image.Pad"
//        propertyType: CONSTS.propertyTypes[8];
//    }


//    Image {
//        anchors.centerIn: parent
//        source: "file:///Users/max/Dev/Volvo/vcc-spa-ui-master/mid/assets/images/S1/Core/core_justincase.png"
//        fillMode: Image.Pad
//    }

/*
    DSlider {
        id: demoSlider
        //width: parent.width * 0.6
        anchors.centerIn: parent

        //vertical: true

        value: 50.0

        onNewValueChanged: {
//            if (value !== newValue) {
//                // Set Value
//                value = newValue;
//            }
        }
    }

    DText {
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.verticalCenter: parent.verticalCenter

        text: demoSlider.newValue
    }
*/
/*
    DButton {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        text: propertyEditor.state === propertyEditor.stateCreate ? "show" : "hide"
        onClicked: {
            if (propertyEditor.state === propertyEditor.stateCreate) {
                // Show
                propertyEditor.show();
            } else {
                // Reset
                propertyEditor.reset(false);
            }
        }
    }

    DPropertyEditor {
        id: propertyEditor

        childPane: propertyEnumValueEditor

        onNewEnumValue: {
            // Set New Enum Value
            propertyEnumValueEditor.newEnumValue = true;
            // Show Enum Value Editor
            propertyEnumValueEditor.show();
        }
    }

    DPropertyEnumValueEditor {
        id: propertyEnumValueEditor

        parentPane: propertyEditor

        initialX: parentPane.x + parentPane.width * 0.5
        initialY: parentPane.y + parentPane.height

        creationX: initialX - propertyEnumValueEditor.width * 0.5
        creationY: initialY + 32
    }
*/

/*
    DOption {
        id: demoOption
        anchors.centerIn: parent

//        model: [
//            { "text": "Option 1", "checked": false },
//            { "text": "Option 2" },
//            { "text": "Option 3", "disabled": false },
//            { "text": "Option 4" },
//        ]
    }

    DButton {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32
        text: "Add Item"
        onClicked: {
            demoOption.appendItem("Item " + demoOption.count);
        }
    }
*/

/*
    property var demoModel: []

    property int demoCount: demoModel.length

    function appendItem(newIndex) {
        demoModel.push({ title: ("Option " + newIndex)  });
        demoCount = demoModel.length;
    }

    function removeItem(index) {
        demoModel.splice(index, 1);
        demoCount = demoModel.length;
    }

    function clearItems() {
        demoModel.splice(0, demoModel.length);
        demoCount = demoModel.length;
    }

    DFlow {
        id: demoFlow
        width: parent.width * 0.4

        anchors.centerIn: parent
        spacing: DStyle.defaultSpacing

        Repeater {
            id: demoRepeater

            model: demoCount

            delegate: DTag {
                width: demoFlow.width
                //height: 80

                tagTitle: demoModel[index].title

                onRemoveClicked: {
                    removeItem(index);
                }
            }
        }
    }

    Row {
        height: 80
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        spacing: DStyle.defaultSpacing

        DButton {
            anchors.verticalCenter: parent.verticalCenter
            text: "Add"
            onClicked: {
                appendItem(demoCount + 1);
            }
        }

        DButton {
            anchors.verticalCenter: parent.verticalCenter
            text: "Clear"
            onClicked: {
                clearItems();
            }
        }
    }
*/

/*
    DComponentRootContainer {
        id: demoRootContainer

//        width: parent.width * 0.8
//        height: parent.height * 0.8

        creationWidth: parent.width * 0.8
        creationHeight: parent.height * 0.8

        anchors.centerIn: parent

        state: stateShown

        DComponentChildContainer {
            id: demoChildContainer1

            width: 200
            height: 200

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

        }

        DComponentChildContainer {
            id: demoChildContainer2

            width: 200
            height: 200

            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter

        }

    }
*/
/*
    MouseArea {
        id: mainDemoArea

        width: parent.width * 0.8
        height: parent.height * 0.8

        anchors.centerIn: parent

        drag.filterChildren: true

        onPressed: {
            console.log("mainDemoArea.onPressed");
        }

        onReleased: {
            console.log("mainDemoArea.onReleased");
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "teal"
        }

        MouseArea {
            id: demoArea1
            width: 200
            height: 200

            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            drag.filterChildren: true

            onPressed: {
                console.log("demoArea1.onPressed");
            }

            onReleased: {
                console.log("demoArea1.onReleased");
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "orange"
            }
        }

        MouseArea {
            id: demoArea2
            width: 200
            height: 200

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            drag.filterChildren: true

            onPressed: {
                console.log("demoArea2.onPressed");
            }

            onReleased: {
                console.log("demoArea2.onReleased");
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "orange"
            }
        }
    }
*/

/*
    Rectangle {
        anchors.fill: demoFlow
        color: "transparent"
        border.color: "purple"
    }

    DFlow {
        id: demoFlow
        width: parent.width * 0.25
        anchors.centerIn: parent

        move: Transition { }

        DRectangle {
            width: 128
            height: 96
            Behavior on height { DAnimation { } }
        }

        DRectangle {
            id: demoRect
            width: 128
            height: 96
            Behavior on height { DAnimation { } }
        }

        DRectangle {
            width: 128
            height: 96
            Behavior on height { DAnimation { } }
        }

        DRectangle {
            width: 128
            height: 96
            Behavior on height { DAnimation { } }
        }
    }

    DButton {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 200
        text: "Resize"
        onClicked: {
            if (demoRect.height === 10) {
                demoRect.height = 96;
            } else {
                demoRect.height = 10;
            }
        }
    }
*/
/*
    // Component Name
    DText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: anchorsSection.top
        anchors.bottomMargin: 16
        font.bold: true
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        text: propertiesController.focusedComponent ? propertiesController.focusedComponent.componentName : ""
    }

    // Anchors Section
    DAnchorsSection {
        id: anchorsSection
        width: 400
        anchors.centerIn: parent
        state: stateOpen
    }
*/
/*
    DAnchorTargetEditor {
        id: atEditor
        anchors.centerIn: parent
    }

    DButton {
        id: atEditorTestButton
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 200
        text: atEditor.showEditor ? "Hide" : "Show"
        onClicked: {
            if (atEditor.showEditor) {
                atEditor.hide();
            } else {
                atEditor.show(0, 0);
            }
        }
    }
*/
/*

    Component.onCompleted: {
        demoContainer1.x = (demoContainerRoot.width - demoContainer1.width) * 0.5 - 100;
        demoContainer1.y = (demoContainerRoot.height - demoContainer1.height) * 0.5 - 100;

        demoContainer2.x = (demoContainerRoot.width - demoContainer2.width) * 0.5 + 100;
        demoContainer2.y = (demoContainerRoot.height - demoContainer2.height) * 0.5 + 100;
    }

    Item {
        id: dragItem

        width: 200
        height: 300

        default property alias contentChildren: contentContainer.children

        Rectangle {
            anchors.fill: parent
            color: "#77000000"
            border.color: "purple"
        }

        DMouseArea {
            id: dragMouseArea
            anchors.fill: parent

            drag.target: dragItem
            drag.filterChildren: true
            drag.threshold: 0

            onPressed: {
                console.log("dragMouseArea.onPressed");
                demoContainerRoot.bringToFront(dragItem);
            }

            onReleased: {
                console.log("dragMouseArea.onReleased");
            }

            DMouseArea {
                anchors.fill: parent
            }

            Item {
                id: contentContainer
                anchors.fill: parent

                MouseArea {
                    id: demoMouseArea
                    anchors.fill: parent
                    anchors.margins: 16

                    onPressed: {
                        console.log("demoMouseArea.onPressed");
                    }

                    onReleased: {
                        console.log("demoMouseArea.onReleased");
                    }

                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "orange"
                    }
                }

                DButton {
                    id: demoButton
                    anchors.centerIn: parent

                    onPressed: {
                        console.log("demoButton.onPressed");
                    }

                    onReleased: {
                        console.log("demoButton.onReleased");
                    }

                    onClicked: {

                    }
                }



            }

        }
        // ...
    }

    DContainer {
        id: demoContainer1

        onPressed: {
            demoContainerRoot.bringToFront(demoContainer1);
        }
    }

    DContainer {
        id: demoContainer2

        onPressed: {
            demoContainerRoot.bringToFront(demoContainer2);
        }
    }
*/
/*
    function convertTextToRichText(sourceText) {
        // Get Text Length
        var stLength = sourceText.length;

        console.log("convertTextToRichText - sourceText: " + sourceText + " - length: " + stLength);

        // Init Result Text
        var resultText = "";
        // Iterate Thru Input Text
        for (var i=0; i<stLength; i++) {
            // Get Char Code
            var charCode = sourceText.charCodeAt(i);

            console.log("convertTextToRichText - charCode: " + charCode);

            // Switch Car Code
            switch (charCode) {
                // New Line
                case 10: resultText += "<br>";                      break;
                // Space Character
                case 32: resultText += "&nbsp;";                    break;
                // Tab Character
                case 9:  resultText += "&nbsp;&nbsp;&nbsp;&nbsp;";  break;
                // Default
                default: resultText += sourceText[i];               break;
            }
        }

        return resultText;
    }

    function convertUnicodeToPlainText(sourceText) {
        // Get Text Length
        var stLength = sourceText.length;

        console.log("convertUnicodeToPlainText - sourceText: " + sourceText + " - length: " + stLength);

        // Init Result Text
        var resultText = "";
        // Iterate Thru Input Text
        for (var i=0; i<stLength; i++) {
            // Get Char Code
            var charCode = sourceText.charCodeAt(i);

            console.log("convertUnicodeToPlainText - charCode: " + charCode);

            // Switch Car Code
            switch (charCode) {
                // New Line
                case 8232: resultText += "\n";          break;
                // Space Character
                case 160:  resultText += " ";           break;
                // Tab Character
                case 9:    resultText += "    ";        break;
                // Default
                default:   resultText += sourceText[i]; break;
            }
        }

        return resultText;
    }

    Rectangle {
        anchors.fill: demoTextEdit
        color: "transparent"
        border.color: "purple"
    }

    TextEdit {
        id: demoTextEdit
        width: 400
        height: 600
        anchors.centerIn: parent
        horizontalAlignment: TextEdit.AlignLeft
        verticalAlignment: TextEdit.AlignTop
        textFormat: TextEdit.RichText
        color: DStyle.colorFontDark
        activeFocusOnPress: true
        font.family: "Courier"
        font.pixelSize: DStyle.fontSizeM
        wrapMode: TextEdit.NoWrap
        focus: false
    }

    DButton {
        anchors.right: parent.right
        anchors.rightMargin: 64
        anchors.verticalCenter: parent.verticalCenter
        text: "Get Text"
        onClicked: {
            // Get Editor Text
            var editorText = convertUnicodeToPlainText(demoTextEdit.getText(0, demoTextEdit.length));

            console.log("getText: " + editorText);

            for (var i=0; i<editorText.length; i++) {
                var charCode = editorText.charCodeAt(i);
                console.log(i + ":" + charCode);
            }
        }
    }
*/
/*
    Rectangle {
        anchors.fill: demoTextEdit
        color: "transparent"
        border.color: "orange"
    }

    TextEdit {
        id: demoTextEdit
        width: 300
        height: 400
        anchors.centerIn: parent
        wrapMode: TextEdit.NoWrap
        horizontalAlignment: TextEdit.AlignLeft
        verticalAlignment: TextEdit.AlignTop
        textFormat: TextEdit.RichText
        color: DStyle.colorFontDark
        activeFocusOnPress: true
        font.pixelSize: DStyle.fontSizeL
        focus: false
    }
*/
/*
    Flow {
        anchors.centerIn: parent
        spacing: DStyle.defaultSpacing

        DTag {
            tagTitle: "Whatever"
            onRemoveClicked: {
                destroy();
            }
        }

        DTag {
            tagTitle: "Test"
            onRemoveClicked: {
                destroy();
            }
        }
    }
*/
/*
    Flow {
        anchors.left: parent.left
        anchors.leftMargin: 32
        anchors.right: parent.right
        anchors.rightMargin: 32
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 32

        layoutDirection: Qt.RightToLeft

        spacing: DStyle.defaultSpacing

        DButton {
            width: 196
            text: formulaEditor.state === formulaEditor.stateCreate ? "Create Formula Editor" : "Reset Formula Editor"

            onClicked: {
                if (formulaEditor.state === formulaEditor.stateCreate) {
                    formulaEditor.show();
                } else {
                    formulaEditor.reset(false);
                }
            }
        }

        DButton {
            width: 128
            text: propertyEditor.state === propertyEditor.stateCreate ? "Create Property" : "Reset Property"

            onClicked: {
                if (propertyEditor.state === propertyEditor.stateCreate) {
                    propertyEditor.show();
                } else {
                    propertyEditor.reset(false);
                }
            }
        }

        DButton {
            width: 128
            text: signalEditor.state === signalEditor.stateCreate ? "Create Signal" : "Reset Signal"

            onClicked: {
                if (signalEditor.state === signalEditor.stateCreate) {
                    signalEditor.show();
                } else {
                    signalEditor.reset(false);
                }
            }
        }

        DButton {
            width: 196
            text: signalParameterEditor.state === signalParameterEditor.stateCreate ? "Create Signal Parameter" : "Reset Signal Parameter"

            onClicked: {
                if (signalParameterEditor.state === signalParameterEditor.stateCreate) {
                    signalParameterEditor.show();
                } else {
                    signalParameterEditor.reset(false);
                }
            }
        }

        DButton {
            width: 128
            text: stateEditor.state === stateEditor.stateCreate ? "Create State" : "Reset State"

            onClicked: {
                if (stateEditor.state === stateEditor.stateCreate) {
                    stateEditor.show();
                } else {
                    stateEditor.reset(false);
                }
            }
        }

        DButton {
            width: 196
            text: propertyChangesEditor.state === propertyChangesEditor.stateCreate ? "Create Property Changes" : "Reset Property Changes"

            onClicked: {
                if (propertyChangesEditor.state === propertyChangesEditor.stateCreate) {
                    propertyChangesEditor.show();
                } else {
                    propertyChangesEditor.reset(false);
                }
            }
        }

        DButton {
            width: 168
            text: transitionEditor.state === transitionEditor.stateCreate ? "Create Transition" : "Reset Transition"

            onClicked: {
                if (transitionEditor.state === transitionEditor.stateCreate) {
                    transitionEditor.show();
                } else {
                    transitionEditor.reset(false);
                }
            }
        }

        DButton {
            width: 196
            text: transitionNodeEditor.state === transitionNodeEditor.stateCreate ? "Create Transition Node" : "Reset Transition Node"

            onClicked: {
                if (transitionNodeEditor.state === transitionNodeEditor.stateCreate) {
                    transitionNodeEditor.show();
                } else {
                    transitionNodeEditor.reset(false);
                }
            }
        }

        DButton {
            width: 168
            text: importEditor.state === importEditor.stateCreate ? "Add Imports" : "Close Imports"

            onClicked: {
                if (importEditor.state === importEditor.stateCreate) {
                    importEditor.show();
                } else {
                    importEditor.reset(false);
                }
            }
        }

        DButton {
            width: 168
            text: slotEditor.state === slotEditor.stateCreate ? "Create Slot" : "Reset Slot"

            onClicked: {
                if (slotEditor.state === slotEditor.stateCreate) {
                    slotEditor.show();
                } else {
                    slotEditor.reset(false);
                }
            }
        }

        DButton {
            width: 168
            text: functionEditor.state === functionEditor.stateCreate ? "Create Function" : "Reset Function"

            onClicked: {
                if (functionEditor.state === functionEditor.stateCreate) {
                    functionEditor.show();
                } else {
                    functionEditor.reset(false);
                }
            }
        }

        // ...

    }

//    DImportsEditor {
//        id: importsEditor

//        childPane: importEditor

//        onNewImport: {
//            // Show Import Editor
//            childPane.show();
//        }
//    }

    DImportEditor {
        id: importEditor

//        parentPane: importsEditor

//        initialX: parentPane.x + parentPane.width * 0.5
//        initialY: parentPane.y + parentPane.height

    }

    // Formula Editor
    DFormulaEditor {
        id: formulaEditor

//        initialX: parent.width - 32
//        initialY: parent.height * 0.5

//        creationX: initialX - formulaEditor.width - 32
//        creationY: initialY - formulaEditor.height * 0.5

        // ...
    }

    // Property Editor
    DPropertyEditor {
        id: propertyEditor
    }

    // Signal Editor
    DSignalEditor {
        id: signalEditor

        childPane: signalParameterEditor

        onNewParameter: {
            // Show Signal Parameter Editor
            signalParameterEditor.show();
        }
    }

    // Signal Parameter Editor
    DSignalParameterEditor {
        id: signalParameterEditor

        parentPane: signalEditor

        initialX: signalEditor.x + signalEditor.width * 0.5
        initialY: signalEditor.y + signalEditor.height

//        creationX: initialX - signalParameterEditor.width * 0.5
//        creationY: initialY + 32
    }

    DSlotEditor {
        id: slotEditor

    }

    DFunctionEditor {
        id: functionEditor

    }

    // State Editor
    DStateEditor {
        id: stateEditor

        childPane: propertyChangesEditor

        onNewPropertyChange: {
            // Show Property Changes Editor
            propertyChangesEditor.show();
        }
    }

    // Property Changes Editor
    DPropertyChangesEditor {
        id: propertyChangesEditor

        parentPane: stateEditor

        initialX: stateEditor.x + stateEditor.width * 0.5
        initialY: stateEditor.y + stateEditor.height

        creationX: initialX - propertyChangesEditor.width * 0.5
        creationY: initialY + 32
    }

    // Transition Editor
    DTransitionEditor {
        id: transitionEditor

        childPane: transitionNodeEditor

        onNewTransitionNode: {
            // Set Node Type
            transitionNodeEditor.nodeType = nodeType;
            // Check Node Type
            if (nodeType > 2) {
                // Show Transition Node Editor
                transitionNodeEditor.show();
            }
        }
    }

    // Transition Node Editor
    DTransitionNodeEditor {
        id: transitionNodeEditor

        state: stateCreate

        parentPane: transitionEditor

        initialX: transitionEditor.x + transitionEditor.width * 0.5
        initialY: transitionEditor.y + transitionEditor.height

        creationX: initialX - transitionNodeEditor.width * 0.5
        creationY: initialY + 32
    }
*/
/*
//    MouseArea {
//        id: demoArea1
//        width: 400
//        height: 400
//        anchors.centerIn: parent

//        drag.filterChildren: true

//        propagateComposedEvents: true

//        onPressed: {
//            console.log("demoArea1.onPressed");

//            DSystemModel.lastMousePressOwner = "demoArea1";

//        }

//        onReleased: {
//            console.log("demoArea1.onReleased");

//            // Check Last Mouse Press Owner
//            if (DSystemModel.lastMousePressOwner === "demoArea1") {
//                // Reset Last Mouse Press Owner
//                DSystemModel.lastMousePressOwner = "";
//            }
//        }

//        onClicked: {
//            console.log("demoArea1.onClicked");
//        }

//        Rectangle {
//            anchors.fill: parent
//            color: "transparent"
//            border.color: parent.pressed ? "red" : "purple"
//        }

//        MouseArea {
//            id: demoArea2
//            width: 300
//            height: 300
//            anchors.centerIn: parent

//            //preventStealing: true

//            onPressed: {
//                console.log("demoArea2.onPressed");

//                DSystemModel.lastMousePressOwner = "demoArea2";
//            }

//            onReleased: {
//                console.log("demoArea2.onReleased");

//                // Check Last Mouse Press Owner
//                if (DSystemModel.lastMousePressOwner === "demoArea2") {
//                    // Reset Last Mouse Press Owner
//                    DSystemModel.lastMousePressOwner = "";
//                }
//            }

//            onClicked: {
//                console.log("demoArea2.onClicked");
//            }

//            Rectangle {
//                anchors.fill: parent
//                color: "transparent"
//                border.color: parent.pressed ? "red" : "orange"
//            }
//        }
//    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            demoContainerRoot.focus = true;
//        }
//    }

//    DDisc {
//        anchors.centerIn: parent
//        width: 512
//        height: 512
//    }


//    DPropertyItem {
//        id: opiDelegateRoot
//        width: 300
//        anchors.centerIn: parent
//    }


//    DContainer {
//        id: demoContainer
//        Component.onCompleted: {
//            x = (parent.width - width) * 0.5;
//            y = (parent.height - height) * 0.5;
//        }
//    }
*/
/*
    Column {
        anchors.centerIn: parent
        spacing: DStyle.defaultSpacing

        DButton {
            //onClicked: checked = !checked;
            //enabled: propertiesPaneRoot.parent.enabled
            enabled: parent.enabled
        }

        DButton {
            //onClicked: checked = !checked;
            checked: true
            enabled: parent.enabled
        }

        DCheckBox {
            text: "CheckBox"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DCheckBox {
            rightAligned: true
            text: "CheckBox"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DSwitch {
            text: "Switch"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DSwitch {
            rightAligned: true
            text: "Switch"
            onClicked: checked = !checked;
            enabled: parent.enabled
        }

        DRadioButtonGroup {
            model: [
                DRadioButtonGroupItem { title: "Item 1" },
                DRadioButtonGroupItem { title: "Item 2" },
                DRadioButtonGroupItem { title: "Item 3" },
                DRadioButtonGroupItem { title: "Item 4" }
            ]

            onButtonSelected: {
                //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
                // Set Current Index
                currentIndex = buttonIndex;
            }
        }

        DRadioButtonGroup {
            rightAligned: true
            model: [
                DRadioButtonGroupItem { title: "Item 1" },
                DRadioButtonGroupItem { title: "Item 2" },
                DRadioButtonGroupItem { title: "Item 3" },
                DRadioButtonGroupItem { title: "Item 4" }
            ]

            onButtonSelected: {
                //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
                // Set Current Index
                currentIndex = buttonIndex;
            }
        }

    }
*/
/*
    DCarousel {
        id: carouselDemo

        width: 400
        height: 300

        itemScale: 0.4
        delegateScale: 0.3
        visibleItems: 5
        showTitle: false

        anchors.centerIn: parent

        model: ListModel {
            ListElement {
                demoTitle: "Title 1"
            }
            ListElement {
                demoTitle: "Title 2"
            }
            ListElement {
                demoTitle: "Title 3"
            }
            ListElement {
                demoTitle: "Title 4"
            }
            ListElement {
                demoTitle: "Title 5"
            }
            ListElement {
                demoTitle: "Title 6"
            }
            ListElement {
                demoTitle: "Title 7"
            }
        }

        contentDelegate: DCarouselDelegate {
            itemTitle: itemData ? itemData.demoTitle : ""

            DRectangle {
                anchors.fill: parent
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
            }

            DText {
                anchors.centerIn: parent
                text: itemData ? itemData.demoTitle : ""
            }
        }
    }
*/
/*
    Component {
        id: demoComponent

        DRectangle {
            width: 128
            height: 96
        }
    }

    DButton {
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        text: "Test"
        onClicked: {
            var newObject = demoComponent.createObject(demoFlow.flowItem);
        }
    }

    Rectangle {
        anchors.fill: demoFlow
        color: "transparent"
        border.color: "purple"
    }

    DFlow {
        id: demoFlow
        width: 400
        anchors.centerIn: parent
    }
*/
/*
    DSourceContainer {
        id: sourceContainerDemo
        width: 600
        height: 500
        anchors.centerIn: parent
    }
*/
/*
    DActivityIndicator {
        width: 420
        height: 420
        anchors.centerIn: parent
        running: true
    }
*/
/*
    DColorTest {
        id: colorTest
    }
*/
}
