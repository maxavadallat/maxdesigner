import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: transitionEditorRoot

    title: "Edit Transition"

    hideToSide: hideToRight

    creationWidth: 440
    creationHeight: 128

    minWidth: 440
    minHeight: 128

    property ComponentInfo componentInfo: null

    signal accepted()
    signal rejected()

    onAccepted: {
        // Reset
        transitionEditorRoot.reset(false);
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            transitionEditorRoot.accepted();

            // ...
        }
    }

    Row {
        id: fromToRow
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        property int optionWidth: 132

        DText {
            id: fromLabel
            //width: 48
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "From:"
        }

        DOption {
            id: fromOption
            width: fromToRow.optionWidth
            anchors.verticalCenter: parent.verticalCenter
            model: [
                DPopupItemObject { text: "Option 1" },
                DPopupItemObject { text: "Option 2" },
                DPopupItemObject { text: "Option 3" },
                DPopupItemObject { text: "Option 4" },
                DPopupItemObject { text: "Option 5" }
            ]
        }

        DText {
            id: toLabel
            //width: 48
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignRight
            text: "To:"
        }

        DOption {
            id: toOption
            width: fromToRow.optionWidth
            anchors.verticalCenter: parent.verticalCenter
            model: [
                DPopupItemObject { text: "Option 1" },
                DPopupItemObject { text: "Option 2" },
                DPopupItemObject { text: "Option 3" },
                DPopupItemObject { text: "Option 4" },
                DPopupItemObject { text: "Option 5" }
            ]
        }

    }

    DOption {
        id: addTransitionRow
        width: fromToRow.width
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        currentIndex: 0
        model: [
            DPopupItemObject { text: "Add Sequential Animation" },
            DPopupItemObject { text: "Add Parallel Animation" },
            DPopupItemObject { text: "Add Property Animation" },
            DPopupItemObject { text: "Add Property Action" },
            DPopupItemObject { text: "Add Script Action" },
            DPopupItemObject { text: "Add Pause Animation" }
        ]
    }


}
