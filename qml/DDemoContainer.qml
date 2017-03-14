import QtQuick 2.0
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "DConstants.js" as CONSTS
import "style"

DRectangle {
    id: demoContainerRoot

    width: 800
    height: 800

    DCarousel {
        id: carouselDemo

        width: 400
        height: 300

        itemScale: 0.4
        delegateScale: 0.3
        visibleItems: 5
        showTitle: false

        anchors.centerIn: parent

        model: ListModel {
            ListElement {
                demoTitle: "Title 1"
            }
            ListElement {
                demoTitle: "Title 2"
            }
            ListElement {
                demoTitle: "Title 3"
            }
            ListElement {
                demoTitle: "Title 4"
            }
            ListElement {
                demoTitle: "Title 5"
            }
            ListElement {
                demoTitle: "Title 6"
            }
            ListElement {
                demoTitle: "Title 7"
            }
        }

        contentDelegate: DCarouselDelegate {
            itemTitle: itemData ? itemData.demoTitle : ""

            DRectangle {
                anchors.fill: parent
                color: Qt.hsla(Math.random(), Math.random(), 0.5, 0.5)
            }

            DText {
                anchors.centerIn: parent
                text: itemData ? itemData.demoTitle : ""
            }
        }
    }

/*
    Component {
        id: demoComponent

        DRectangle {
            width: 128
            height: 96
        }
    }

    DButton {
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        text: "Test"
        onClicked: {
            var newObject = demoComponent.createObject(demoFlow.flowItem);
        }
    }

    Rectangle {
        anchors.fill: demoFlow
        color: "transparent"
        border.color: "purple"
    }

    DFlow {
        id: demoFlow
        width: 400
        anchors.centerIn: parent
    }
*/
//    DSourceContainer {
//        id: sourceContainerDemo
//        width: 600
//        height: 500
//        anchors.centerIn: parent
//    }

//    DActivityIndicator {
//        width: 420
//        height: 420
//        anchors.centerIn: parent
//        running: true
//    }

//    DColorTest {
//        id: colorTest
//    }

}
