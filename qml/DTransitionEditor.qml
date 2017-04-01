import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DPaneBase {
    id: transitionEditorRoot

    title: "Edit Transition"

    hideToSide: hideToRight

    creationWidth: 440
    creationHeight: 118

    minWidth: 440
    minHeight: 118

    enableResize: false

    //property ComponentInfo componentInfo: null

    //property var stateModel: []

    signal newTransitionNode(var nodeType)
    signal editTransitionNode()

    onTransitionFinished: {
        if (newState === stateShown) {
            // Set Option Focus
            fromOption.setOptionFocus(true);
        }
    }

    onChildTransitionFinished: {
        if (newState === stateCreate) {
            // Set Option Current Index
            addTransitionOption.currentIndex = 0;
            // Set Enabled
            addTransitionOption.enabled = true;
            // Set Option Focus
            addTransitionOption.setOptionFocus(true);
        }
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

            onZChanged: {
                parent.z = fromOption.z;
            }

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        toOption.setOptionFocus(true);
                    break;
                }
            }
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

            onZChanged: {
                parent.z = toOption.z;
            }

            onKeyEvent: {
                switch (event.key) {
                    case Qt.Key_Escape:
                        // Dismiss Pane
                        transitionEditorRoot.dismissPane(true);
                    break;

                    case Qt.Key_Tab:
                        addTransitionOption.setOptionFocus(true);
                    break;
                }
            }
        }
    }


    // ...


    DOption {
        id: addTransitionOption
        width: fromToRow.width
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: DStyle.defaultMargin
        currentIndex: 0
        model: [
            DPopupItemObject { text: "Add New Node" },
            DPopupItemObject { text: "Add Sequential Animation" },
            DPopupItemObject { text: "Add Parallel Animation" },
            DPopupItemObject { text: "Add Property Animation" },
            DPopupItemObject { text: "Add Property Action" },
            DPopupItemObject { text: "Add Script Action" },
            DPopupItemObject { text: "Add Pause Animation" }
        ]

        onKeyEvent: {
            switch (event.key) {
                case Qt.Key_Escape:
                    // Dismiss Pane
                    transitionEditorRoot.dismissPane(true);
                break;

                case Qt.Key_Tab:
                    fromOption.setOptionFocus(true);
                break;
            }
        }

        onItemSelected: {
            // Check Selected Item Index
            if (itemIndex === 0) {
                return;
            }

            // Check Selected Item Index
            if (itemIndex > 2) {
                // Set Enabled
                addTransitionOption.enabled = false;
            }

            // Signal New Transition Node
            transitionEditorRoot.newTransitionNode(itemIndex);
        }
    }
}
