import QtQuick 2.7
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"
import "system"

DRectangle {
    id: demoContainerRoot

    width: 800
    height: 800

    clip: true

    border.color: demoContainerRoot.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

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

    }

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
