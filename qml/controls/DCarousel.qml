import QtQuick 2.0
import QtGraphicalEffects 1.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"

Item {
    id: carouselRoot

    width: 600
    height: 400

    property alias model: pathView.model
    property alias currentIndex: pathView.currentIndex
    property alias currentTitle: titleLabel.text
    property alias currentItem: pathView.currentItem
    property int titleSize: DStyle.fontSizeXL
    property bool showTitle: true
    property Component contentDelegate

    property real delegateScale: 0.5
    property int visibleItems: 3
    property real itemScale: 0.6
    readonly property real bounds: 0.2
    property bool asyncLoad: true
    readonly property real sideOpacity: 0.3

    signal decrement()
    signal increment()
    signal itemSelected(int index)

    clip: true

    onDecrement: pathView.decrementCurrentIndex()
    onIncrement: pathView.incrementCurrentIndex()

    PathView {
        id: pathView
        objectName: "pathView"
        anchors.fill: parent
        snapMode: PathView.SnapOneItem
        pathItemCount: carouselRoot.visibleItems
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        opacity: 0.0
        interactive: model.count > 1

        onCurrentItemChanged: {
            if (moving) {
                carouselRoot.itemSelected(carouselRoot.currentIndex);
            }
        }

        delegate: Item {
            id: itemDelegate
            width: pathView.width * carouselRoot.delegateScale
            height: width
            scale: PathView.itemScale
            z: PathView.itemZ

            property string itemTitle: contentLoader.item ? contentLoader.item.itemTitle : ""
            property var itemData: model

            DMouseArea {
                anchors.fill: parent
                onClicked: {
                    carouselRoot.itemSelected(index);
                    pathView.currentIndex = index;
                }
            }

            Loader {
                id: contentLoader
                anchors.fill: parent
                sourceComponent: carouselRoot.contentDelegate
                asynchronous: carouselRoot.asyncLoad
                onLoaded: {
                    // Bind Item Data
                    item.itemData = Qt.binding(function() { return model; });
                }
            }
        }

        path: Path {
            id: carouselPath
            objectName: "carouselPath"
            startX: -pathView.width * carouselRoot.bounds
            startY: pathView.height * 0.5

            PathAttribute { name: "itemScale"; value: carouselRoot.itemScale }
            PathAttribute { name: "itemZ"; value: 0.0 }

            PathLine { x: pathView.width * 0.5; y: pathView.height * 0.5 }

            PathAttribute { name: "itemScale"; value: 1.0 }
            PathAttribute { name: "itemZ"; value: 1.0 }

            PathLine { x: pathView.width * (1.0 + carouselRoot.bounds);  y: pathView.height * 0.5 }

            PathAttribute { name: "itemZ"; value: 0.0 }
            PathAttribute { name: "itemScale"; value: carouselRoot.itemScale }
        }
    }

    Item {
        id: maskItem
        objectName: "maskItem"
        anchors.fill: parent
        visible: false

        Image {
            id: maskImageLeft
            objectName: "maskImageLeft"
            width: parent.width * Math.min(carouselRoot.sideOpacity, 0.5)
            height: parent.height
            source: "qrc:/assets/images/carousel_mask.png"
            fillMode: Image.TileVertically
        }

        Rectangle {
            height: parent.height
            anchors.left: maskImageLeft.right
            anchors.right: maskImageRight.left
        }

        Image {
            id: maskImageRight
            objectName: "maskImageRight"
            width: parent.width * Math.min(carouselRoot.sideOpacity, 0.5)
            height: parent.height
            anchors.right: parent.right
            source: "qrc:/assets/images/carousel_mask.png"
            fillMode: Image.TileVertically
            rotation: 180
        }
    }

    OpacityMask {
        id: opacityMask
        objectName: "opacityMask"
        anchors.fill: pathView
        source: pathView
        maskSource: maskItem
    }

    DText {
        id: titleLabel
        objectName: "titleLabel"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        font.pixelSize: carouselRoot.titleSize
        maximumLineCount: 2
        visible: carouselRoot.showTitle
        text: {
            return pathView.currentItem ? pathView.currentItem.itemTitle : "";
        }
    }
}
