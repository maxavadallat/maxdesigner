import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

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

    state: stateShown

    // Show Toolbar
    function showToolbar() {
        // Set State
        toolBarRoot.state = stateShown;
    }

    // Close Toolbar
    function closeToolbar() {
        // Set State
        toolBarRoot.state = stateClosed;
    }

    // Hide Toolbar
    function hideToolbar() {
        // Save Previous State
        toolBarRoot.previousState = toolBarRoot.state;
        // Set State
        toolBarRoot.state = stateHidden;
    }

    // Restore Toolbar
    function restoreToolbar() {
        // Check Previous State
        if (toolBarRoot.previousState !== "") {
            // Set Previous State
            toolBarRoot.state = toolBarRoot.previousState;
            // Reset Previous State
            toolBarRoot.previousState = "";
        } else {
            // Set State
            toolBarRoot.state = stateClosed;
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
            onClicked: checked = !checked;
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hcenter.png"
            onClicked: checked = !checked;
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hright.png"
            onClicked: checked = !checked;
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/align.vtop.png"
            onClicked: checked = !checked;
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vcenter.png"
            onClicked: checked = !checked;
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vbottom.png"
            onClicked: checked = !checked;
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/fill.png"
            onClicked: checked = !checked;
        }

        DToolButton {
            source: "qrc:/assets/icons/centerin.png"
            onClicked: checked = !checked;
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
