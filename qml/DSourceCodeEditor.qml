import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DRectangle {
    id: sourceCodeEditorRoot

    width: 600
    height: 400

    property alias formulaText: sourceTextInput.text

    property string fontFamily: "Courier"
    property int fontSize: 16
    property int lineHeight: fontSize
    property bool showLineNumbers: true
    property bool highlightCurrentLine: true
    property alias wrapMode: sourceTextInput.wrapMode
    property alias editorFocus: sourceTextInput.focus
    property bool showBorder: true

    border.color: showBorder ? (sourceTextInput.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus) : "transparent"

    signal escapeClicked()
    signal sourceEditorActivated()

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

    DMouseArea {
        anchors.fill: parent
        onClicked: {
            // Set Editor Focus
            sourceCodeEditorRoot.setEditorFocus(true);
            // Emit Source Editor Activated Signal
            sourceCodeEditorRoot.sourceEditorActivated();
        }
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
                width: 32
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
                                opacity: 0.8
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

                text: ""

                // TODO: Syntax Highlighting, line numbers

                // ...

                Keys.onReleased: {
                    if (event.key === Qt.Key_Escape) {
                        // Reset Focus
                        sourceTextInput.focus = false;
                        // Emit Escape Clicked Signal
                        sourceCodeEditorRoot.escapeClicked();
                    }
                }
            }
        }
    }
}

