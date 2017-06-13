import QtQuick 2.0

import enginecomponents 0.1

import "qrc:/qml/style"
import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/controls"

DRectangle {
    id: stateSelectorRoot

    width: 400
    height: 96

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: stateSelectorShown ? 0 : -height

    Behavior on anchors.bottomMargin { PropertyAnimation { easing.type: Easing.InOutBack; duration: 200 } }

    property bool stateSelectorShown: false

    property ComponentInfo componentInfo: liveController.currentComponent

    property string selectedState: ""

    onComponentInfoChanged: {
        //console.log("DStateSelector.onComponentInfoChanged - componentInfo: " + (componentInfo !== null ? componentInfo.componentName : "NULL"));

        // Clear States
        clearStates();
        // Build States
        buildStates();

        // ...
    }

    // Build States
    function buildStates() {
        // Check Component Info
        if (stateSelectorRoot.componentInfo !== null) {
            // Get States Count
            var sCount = propertiesController.statesModel.rowCount();

            // Add Empty State
            statesModel.append({ "stateName": "" });


            console.log("DStateSelector.buildStates - sCount: " + sCount);

            // Iterate Through States
            for (var i=0; i<sCount; i++) {
                // Get Component State
                var componentState = propertiesController.statesModel.getState(i);

                // Add To States Model
                statesModel.append({ "stateName": componentState.stateName });

                // ...
            }

            // Get Current State
            var currentState = stateSelectorRoot.componentInfo.componentState;

            // Get States Model Count
            var smCount = statesModel.count;

            // Iterate Through States Model
            for (var n=0; n<smCount; n++) {
                // Get Model Data
                var smData = statesModel.get(n);
                // Check State Name
                if (smData.stateName === currentState) {
                    // Set Carousel Current Index
                    stateCarousel.currentIndex = n;

                    return;
                }
            }
        }
    }

    // Clear States
    function clearStates() {
        // Clear States Model
        statesModel.clear();
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
        anchors.leftMargin: DStyle.defaultMargin * 4
        anchors.rightMargin: DStyle.defaultMargin * 4

        itemScale: 0.3
        delegateScale: 0.3
        visibleItems: 5
        showTitle: false

        model: statesModel

        visible: statesModel.count > 1

        contentDelegate: DCarouselDelegate {
            itemTitle: itemData ? itemData.stateName : ""

            DRectangle {
                anchors.fill: parent
                anchors.topMargin: DStyle.defaultMargin
                anchors.bottomMargin: DStyle.defaultMargin
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.2)
            }

            DText {
                anchors.centerIn: parent
                text: itemData ? itemData.stateName.length > 0 ? itemData.stateName : "Default"  : ""
            }
        }

        onCurrentItemChanged: {
            // Set Selected State
            stateSelectorRoot.selectedState = currentItem.itemData.stateName;
        }
    }

    DText {
        anchors.centerIn: parent
        text: "No States Defined"
        visible: statesModel.count <= 1
    }
}
