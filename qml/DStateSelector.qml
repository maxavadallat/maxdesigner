import QtQuick 2.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

DRectangle {
    id: stateSelectorRoot

    width: 300
    height: 96

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: stateSelectorShown ? 0 : -height

    Behavior on anchors.bottomMargin { PropertyAnimation { easing.type: Easing.InOutBack } }

    property bool stateSelectorShown: false

    property ComponentInfo componentInfo: liveController.currentComponent

    property string selectedState: ""

    onComponentInfoChanged: {
        // ...
    }

    DMouseArea {
        id: hideButton
        width: 96
        height: 32
        anchors.bottom: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            // Toggle State Selector Show
            stateSelectorShown = !stateSelectorShown;
        }

        DText {
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            color: parent.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            text: stateSelectorShown ? "•••" : "State Selector"
        }
    }

    ListModel {
        id: statesModel

        ListElement {
            stateName: "State 1"
        }
        ListElement {
            stateName: "State 2"
        }
        ListElement {
            stateName: "State 3"
        }
        ListElement {
            stateName: "State 4"
        }
        ListElement {
            stateName: "State 5"
        }
        ListElement {
            stateName: "State 6"
        }
        ListElement {
            stateName: "State 7"
        }
    }

    DCarousel {
        id: stateCarousel

        anchors.fill: parent

        itemScale: 0.3
        delegateScale: 0.3
        visibleItems: 5
        showTitle: false

        model: statesModel

        contentDelegate: DCarouselDelegate {
            itemTitle: itemData ? itemData.stateName : ""

            DRectangle {
                anchors.fill: parent
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
            }

            DText {
                anchors.centerIn: parent
                text: itemData ? itemData.stateName : ""
            }
        }

        onCurrentItemChanged: {
            // Set Selected State
            stateSelectorRoot.selectedState = currentItem.itemData.stateName
        }
    }
}
