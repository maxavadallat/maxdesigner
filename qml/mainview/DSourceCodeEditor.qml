import QtQuick 2.7

import enginecomponents 0.1

import "qrc:/qml/system"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/controls"

DRectangle {
    id: sourceCodeEditorRoot

    width: 600
    height: 400

    property string sourceText: sourceTextInput.getText(0, sourceTextInput.length)

    property string fontFamily: "Courier"
    property int fontSize: 16
    property int lineHeight: fontSize
    property bool showLineNumbers: true
    property bool highlightCurrentLine: true
    property alias wrapMode: sourceTextInput.wrapMode
    property alias editorFocus: sourceTextInput.focus
    property alias length: sourceTextInput.length
    property bool showBorder: true

    clip: true

    border.color: {
        if (invalidSource) {
            return "red";
        }

        return showBorder ? (sourceTextInput.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus) : "transparent";
    }

    property bool invalidSource: false

    signal escapeClicked()
    signal sourceEditorActivated()

    // Insert Text To The Current Cursor Position
    function insertText(plainText) {
        // Insert Text
        sourceTextInput.insert(sourceTextInput.cursorPosition, plainText);
    }

    // Set Text
    function setText(plainText) {
        //console.log("DSourceCodeEditor.setText - plainText: " + plainText);
        // Set Text
        sourceTextInput.text = convertTextToRichText(plainText);
    }

    // Get Text
    function getText() {
        // Set Source Text
        sourceCodeEditorRoot.sourceText = convertUnicodeToPlainText(sourceTextInput.getText(0, sourceTextInput.length));

        return sourceCodeEditorRoot.sourceText;
    }

    // Set Editor Focus
    function setEditorFocus(aFocus, aSelect) {
        // Set Focus
        sourceTextInput.focus = aFocus;
        // Check Select
        if (aSelect) {
            // Select All
            sourceTextInput.selectAll();
        }
    }

    // Convert PLain Text To Rich Text
    function convertTextToRichText(sourceText) {
        // Get Text Length
        var stLength = sourceText.length;

        //console.log("convertTextToRichText - sourceText: " + sourceText + " - length: " + stLength);

        // Init Result Text
        var resultText = "";
        // Iterate Thru Input Text
        for (var i=0; i<stLength; i++) {
            // Get Char Code
            var charCode = sourceText.charCodeAt(i);

            //console.log("convertTextToRichText - charCode: " + charCode + " - char: " + sourceText.charAt(i));

            // Switch Car Code
            switch (charCode) {
                // < Character
                case 60: resultText += "&lt;";                      break;
                // > Character
                case 62: resultText += "&gt;";                      break;
                // & Character
                case 38: resultText += "&amp;";                     break;
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

    // Convert Unicode To Plain Text
    function convertUnicodeToPlainText(sourceText) {
        // Get Text Length
        var stLength = sourceText.length;

        //console.log("convertUnicodeToPlainText - sourceText: " + sourceText + " - length: " + stLength);

        // Init Result Text
        var resultText = "";
        // Iterate Thru Input Text
        for (var i=0; i<stLength; i++) {
            // Get Char Code
            var charCode = sourceText.charCodeAt(i);

            //console.log("convertUnicodeToPlainText - charCode: " + charCode + " - char: " + sourceText.charAt(i));

            // Switch Car Code
            switch (charCode) {
                // New Line
                case 8233:
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

    // Set Cursor Pos
    function setCursorPos(newPos) {
        // Set Cursor Position
        sourceTextInput.cursorPosition = newPos;
    }

    DMouseArea {
        anchors.fill: parent
        onClicked: {
            // Set Editor Focus
            sourceCodeEditorRoot.setEditorFocus(true);
            // Emit Source Editor Activated Signal
            sourceCodeEditorRoot.sourceEditorActivated();
        }
    }

    Rectangle {
        id: lineNumbersBG
        width: lineNumbers.width + DStyle.defaultMargin
        height: parent.height
        color: "#11EEEEEE"
    }

    DFlickable {
        id: sourceCodeEditorFlickable

        anchors.fill: parent
        anchors.margins: DStyle.defaultMargin

        Item {
            id: textInputContainer
            width: sourceCodeEditorRoot.width
            height: sourceTextInput.height

            Item {
                id: lineNumbers
                width: 32  // TODO: Update
                height: sourceTextInput.height

                Column {
                    Repeater {
                        model: Math.ceil(sourceCodeEditorFlickable.contentHeight / sourceCodeEditorRoot.lineHeight)
                        delegate: Item {
                            width: lineNumbers.width
                            height: sourceCodeEditorRoot.lineHeight
                            DText {
                                height: sourceCodeEditorRoot.lineHeight
                                anchors.right: parent.right

                                font.pixelSize:  sourceCodeEditorRoot.fontSize - 2
                                font.family: "Courier"
                                text: index + ":"
                                //horizontalAlignment: Text.AlignRight
                                opacity: 0.7
                                onWidthChanged: {
                                    if (width > lineNumbers.width) {
                                        lineNumbers.width = width;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            TextEdit {
                id: sourceTextInput
                width: textInputContainer.width - lineNumbers.width - DStyle.defaultMargin
                //height: Math.max(sourceCodeEditorRoot.height, contentHeight)
                height: contentHeight
                anchors.left: lineNumbers.right
                anchors.leftMargin:DStyle.defaultMargin
                font.family: sourceCodeEditorRoot.fontFamily
                font.pixelSize: sourceCodeEditorRoot.fontSize
                wrapMode: TextEdit.NoWrap
                horizontalAlignment: TextEdit.AlignLeft
                verticalAlignment: TextEdit.AlignTop
                textFormat: TextEdit.RichText
                color: DStyle.colorFontDark
                activeFocusOnPress: true
                focus: false
                selectByMouse: true

                text: ""

                // TODO: Syntax Highlighting, line numbers

                // ...

                onActiveFocusChanged: {
                    // Check Active Focus
                    if (activeFocus) {
                        // Set Current Text Input
                        DSystemModel.currentTextInput = sourceCodeEditorRoot;
                    }
                }

                Keys.onReleased: {
                    if (event.key === Qt.Key_Escape) {
                        // Reset Focus
                        sourceTextInput.focus = false;
                        // Emit Escape Clicked Signal
                        sourceCodeEditorRoot.escapeClicked();
                    }
                }

                onCursorRectangleChanged: {
                    // Flick Content To Ensure Cursor Visibility
                    sourceCodeEditorFlickable.flick(sourceTextInput.cursorRectangle);
                }
            }
        }
    }
}

