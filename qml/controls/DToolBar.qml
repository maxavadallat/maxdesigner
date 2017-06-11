import QtQuick 2.0

import enginecomponents 0.1

import "../style"
import "../system/DConstants.js" as CONSTS
import "../animations"

DRectangle {
    id: toolBarRoot

    width: Math.max(CONSTS.defaultToolBarWidth, toolBarRow.width + DStyle.defaultMargin * 2);
    height: CONSTS.defaultToolBarHeight

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: toolBarTopMargin

    property int toolBarTopMargin: -toolBarRoot.height

    Behavior on toolBarTopMargin { DAnimation { easing.type: Easing.OutBack } }

    readonly property string stateShown: "shown"
    readonly property string stateClosed: "closed"
    readonly property string stateHidden: "hidden"

    property string previousState: ""

    property ComponentInfo componentInfo: propertiesController.focusedComponent

    property ComponentAnchorsModel anchorsModel: propertiesController.anchorsModel

    property Connections anchorsModelConnections: Connections {
        target: propertiesController.anchorsModel

    }

    state: stateHidden

    onComponentInfoChanged: {
        // Check Focused Component
        if (toolBarRoot.componentInfo !== null && !toolBarRoot.componentInfo.isRoot) {
            // Restore Toolbar
            restoreToolbar();
        } else {
            // Hide Toolbar
            hideToolbar();
        }
    }

    // Show Toolbar
    function showToolbar() {
        //console.log("DToolBar.showToolbar");
        // Set State
        toolBarRoot.state = stateShown;
    }

    // Close Toolbar
    function closeToolbar() {
        //console.log("DToolBar.closeToolbar");
        // Set State
        toolBarRoot.state = stateClosed;
    }

    // Hide Toolbar
    function hideToolbar() {
        // Check State
        if (toolBarRoot.state !== stateHidden) {
            //console.log("DToolBar.hideToolbar");
            // Save Previous State
            toolBarRoot.previousState = toolBarRoot.state;
            // Set State
            toolBarRoot.state = stateHidden;
        }
    }

    // Restore Toolbar
    function restoreToolbar() {
        //console.log("DToolBar.restoreToolbar - previousState: " + toolBarRoot.previousState);
        // Check Previous State
        if (toolBarRoot.previousState !== "") {
            // Set Previous State
            toolBarRoot.state = toolBarRoot.previousState;
            // Reset Previous State
            toolBarRoot.previousState = "";
        } else {
            // Set State
            toolBarRoot.state = stateShown;
        }
    }


    Row {
        id: toolBarRow
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        spacing: DStyle.defaultSpacing

        DToolButton {
            source: "qrc:/assets/icons/align.hleft.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsLeft !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Left Anchor
                    if (toolBarRoot.anchorsModel.anchorsLeft === "") {
                        // Set Left Anchor
                        toolBarRoot.anchorsModel.anchorsLeft = "parent.left";
                    } else {
                        // Clear Left Anchor
                        toolBarRoot.anchorsModel.anchorsLeft = "";
                    }
                }
            }
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hcenter.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.horizontalCenter !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Horizontal Center Anchor
                    if (toolBarRoot.anchorsModel.horizontalCenter === "") {
                        // Set Horizontal Center Anchor
                        toolBarRoot.anchorsModel.horizontalCenter = "parent.horizontalCenter";
                    } else {
                        // Clear Horizontal Center Anchor
                        toolBarRoot.anchorsModel.horizontalCenter = "";
                    }
                }
            }
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hright.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsRight !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Right Anchor
                    if (toolBarRoot.anchorsModel.anchorsRight === "") {
                        // Set Right Anchor
                        toolBarRoot.anchorsModel.anchorsRight = "parent.right";
                    } else {
                        // Clear Right Anchor
                        toolBarRoot.anchorsModel.anchorsRight = "";
                    }
                }
            }
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/align.vtop.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsTop !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Top Anchor
                    if (toolBarRoot.anchorsModel.anchorsTop === "") {
                        // Set Top Anchor
                        toolBarRoot.anchorsModel.anchorsTop = "parent.top";
                    } else {
                        // Clear Top Anchor
                        toolBarRoot.anchorsModel.anchorsTop = "";
                    }
                }
            }
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vcenter.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.verticalCenter !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Vertical Center Anchor
                    if (toolBarRoot.anchorsModel.verticalCenter === "") {
                        // Set Vertical Center Anchor
                        toolBarRoot.anchorsModel.verticalCenter = "parent.verticalCenter";
                    } else {
                        // Clear Vertical Center Anchor
                        toolBarRoot.anchorsModel.verticalCenter = "";
                    }
                }
            }
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vbottom.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsBottom !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Bottom Anchor
                    if (toolBarRoot.anchorsModel.anchorsBottom === "") {
                        // Set Bottom Anchor
                        toolBarRoot.anchorsModel.anchorsBottom = "parent.bottom";
                    } else {
                        // Clear Bottom Anchor
                        toolBarRoot.anchorsModel.anchorsBottom = "";
                    }
                }
            }
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/fill.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsFill !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Fill Anchor
                    if (toolBarRoot.anchorsModel.anchorsFill === "") {
                        // Set Fill Anchor
                        toolBarRoot.anchorsModel.anchorsFill = "parent";
                    } else {
                        // Clear Fill Anchor
                        toolBarRoot.anchorsModel.anchorsFill = "";
                    }
                }
            }
        }

        DToolButton {
            source: "qrc:/assets/icons/centerin.png"
            checked: toolBarRoot.anchorsModel ? toolBarRoot.anchorsModel.anchorsCenterIn !== "" : false
            onClicked: {
                // Check Anchors Model
                if (toolBarRoot.anchorsModel) {
                    // Check Center In Anchor
                    if (toolBarRoot.anchorsModel.anchorsCenterIn === "") {
                        // Set Center In Anchor
                        toolBarRoot.anchorsModel.anchorsCenterIn = "parent";
                    } else {
                        // Clear Center In Anchor
                        toolBarRoot.anchorsModel.anchorsCenterIn = "";
                    }
                }
            }
        }
    }

    DMouseArea {
        id: showHideButton
        width: CONSTS.defaultPaneHideButtonHeight
        height: CONSTS.defaultPaneHideButtonWidth
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.bottom

        DText {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            color: parent.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            text: "•••"
        }

        onClicked: {
            // Check Toolbar State
            if (toolBarRoot.state === stateClosed) {
                // Show Toolbar
                showToolbar();
            } else {
                // Close Toolbar
                closeToolbar();
            }
        }
    }

    states: [
        State {
            name: stateHidden
            PropertyChanges { target: toolBarRoot; toolBarTopMargin: -toolBarRoot.height - showHideButton.height }
        },

        State {
            name: stateClosed
            PropertyChanges { target: toolBarRoot; toolBarTopMargin: -toolBarRoot.height }
        },

        State {
            name: stateShown
            PropertyChanges { target: toolBarRoot; toolBarTopMargin: -DStyle.defaultRadius }
        }
    ]
}
