import QtQuick 2.0

import "Style.js" as STYLE
import "Constants.js" as CONSTS

DPane {
    id: propertiesPaneRoot

    width: 280
    height: 400

    title: "Properties"

    Row {
        id: posRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "x:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "y:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }
    }

    Row {
        id: sizeRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "w:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }

        DText {
            width: 18
            anchors.verticalCenter: parent.verticalCenter
            text: "h:"
        }

        DTextInput {
            width: 84
            editor.inputMethodHints: Qt.ImhDigitsOnly
            editor.horizontalAlignment: TextInput.AlignHCenter
            editor.validator: IntValidator { }
        }
    }

    Row {
        id: horizontalAnchoringRow
        height: CONSTS.defaultPaneItemHeight
        spacing: STYLE.defaultSpacing


    }

}
