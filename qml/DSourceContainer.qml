import QtQuick 2.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DPaneBase {
    id: sourceContainerRoot

    title: "Source"

    enablePosOverlay: false
    enableSizeOverlay: false

    enableScaling: false

    hideToSide: hideToBottom

    showTitle: true
    showBackground: false

    clipContent: true

    rootContainer: true

    focusOnShow: true

    titleLabel.opacity: 1.0

    property string filePath: ""

    property string fontFamily: "Courier"
    property int fontSize: 16
    property int lineHeight: fontSize
    property bool showLineNumbers: true
    property bool highlightCurrentLine: true
    property alias wrapMode: sourceTextInput.wrapMode

    property Connections openfilesConnection: Connections {
        target: openFilesModel

        onFileSelected: {
            console.log("DSourceContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Bring To Front
                parent.bringToFront(sourceContainerRoot);
            }
        }

        onFileClosed: {
            console.log("DSourceContainer.openfilesConnection.onFileSelected - aFilePath: " + aFilePath);

            // Check File Path
            if (sourceContainerRoot.filePath === aFilePath) {
                // Reset
                sourceContainerRoot.reset(true);
            }
        }
    }

    DFlickable {
        id: sourceContainerFlickable
        anchors.fill: parent
        //anchors.margins: DStyle.defaultMargin
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        anchors.leftMargin: DStyle.defaultMargin
        anchors.rightMargin: DStyle.defaultMargin
        anchors.bottomMargin: DStyle.defaultMargin

        Item {
            id: textInputContainer
            width: sourceContainerFlickable.width
            height: sourceTextInput.height

//            Rectangle {
//                anchors.fill: parent
//                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
//                border.color: "purple"
//            }

            Item {
                id: lineNumbers
                width: 32
                height: sourceTextInput.height

                Column {
                    Repeater {
                        model: Math.ceil(sourceTextInput.contentHeight / sourceContainerRoot.lineHeight)
                        delegate: Item {
                            width: lineNumbers.width
                            height: sourceContainerRoot.lineHeight
                            DText {
                                height: sourceContainerRoot.lineHeight
                                anchors.right: parent.right

                                font.pixelSize:  sourceContainerRoot.fontSize - 2
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
                height: Math.max(sourceContainerFlickable.height, contentHeight)
                anchors.left: lineNumbers.right
                anchors.leftMargin:DStyle.defaultMargin
                font.family: sourceContainerRoot.fontFamily
                font.pixelSize: sourceContainerRoot.fontSize
                wrapMode: TextEdit.NoWrap
                horizontalAlignment: TextEdit.AlignLeft
                verticalAlignment: TextEdit.AlignTop
                textFormat: TextEdit.RichText
                color: DStyle.colorFontDark

                // TODO: Syntax Highlighting, line numbers

                // ...
            }
        }
    }
}
