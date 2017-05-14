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

    property int toolBarTopMargin: toolBarHidden ? -toolBarRoot.height - showHideButton.height : showToolBar ? -DStyle.defaultRadius : -toolBarRoot.height
    Behavior on toolBarTopMargin { DAnimation { easing.type: Easing.OutBack } }

    property bool showToolBar: true
    property bool toolBarHidden: false

    Row {
        id: toolBarRow
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.verticalCenter: parent.verticalCenter
        spacing: DStyle.defaultSpacing

        DToolButton {
            source: "qrc:/assets/icons/align.hleft.png"
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hcenter.png"
        }

        DToolButton {
            source: "qrc:/assets/icons/align.hright.png"
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/align.vtop.png"
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vcenter.png"
        }

        DToolButton {
            source: "qrc:/assets/icons/align.vbottom.png"
        }

        DToolBarSeparator { }

        DToolButton {
            source: "qrc:/assets/icons/fill.png"
        }

        DToolButton {
            source: "qrc:/assets/icons/centerin.png"
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
            // Toggle Show Tool Bar
            toolBarRoot.showToolBar = !toolBarRoot.showToolBar;
        }
    }
}
