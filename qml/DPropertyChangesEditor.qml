import QtQuick 2.0

import enginecomponents 0.1

import "style"

DPaneBase {
    id: propertyChangesEditorRoot

    title: "Property Change"

    hideToSide: hideToTop

    creationWidth: 290
    creationHeight: 152

    minWidth: 290
    minHeight: 152

    enableResize: false
    enableHideButton: false

    property ComponentInfo componentInfo: null

    state: stateCreate

    onTransitionFinished: {
        if (newState === stateShown) {
            targetEditor.setEditorFocus(true, true);
        }
    }

    DDisc {
        anchors.right: parent.right
        anchors.rightMargin: DStyle.defaultMargin * 2
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            // Emit Accepted Signal
            propertyChangesEditorRoot.accepted();

            // ...
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: titleLabel.height + DStyle.defaultMargin * 2
        spacing: DStyle.defaultSpacing

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: targetLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "target:"
            }

            DTextInput {
                id: targetEditor
                width: 120
                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            propertyEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: propertyLabel
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "property:"
            }

            DTextInput {
                id: propertyEditor
                width: 120
                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            valueEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }

        Row {
            spacing: DStyle.defaultSpacing

            DText {
                id: valueLabel
                width: propertyLabel.width
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
                text: "value:"
            }

            DTextInput {
                id: valueEditor
                width: 120
                onKeyEvent: {
                    switch (event.key) {
                        case Qt.Key_Escape:
                            // Dismiss Pane
                            propertyChangesEditorRoot.dismissPane(true);
                        break;

                        case Qt.Key_Tab:
                            targetEditor.setEditorFocus(true, true);
                        break;
                    }
                }
            }
        }
    }
}
