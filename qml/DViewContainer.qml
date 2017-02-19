import QtQuick 2.0

import "Constants.js" as CONSTS
import "Style.js" as STYLE

DContainer {
    id: viewContainerRoot

    width: 500
    height: 600

    //default property alias mainContainer: contentContainer.children

    showBackground: false
    enableSizeOverlay: true

//    DText {
//        id: titleText
//        anchors.left: parent.left
//        anchors.leftMargin: STYLE.defaultMargin
//        anchors.top: parent.top
//        anchors.topMargin: STYLE.defaultMargin

//        text: "DemoView"
//    }

    Rectangle {
        anchors.fill: parent
        color: STYLE.colorViewBG1
        border.color: STYLE.colorBorderNoFocus

        Canvas {
            anchors.fill: parent
            onPaint: {
                // Get 2D Context
                var ctx = getContext('2d');

                ctx.lineWidth = 1;
                ctx.strokeStyle = STYLE.colorBorderNoFocus;
                ctx.beginPath();
                ctx.moveTo(0, 0);
                ctx.lineTo(viewContainerRoot.width, viewContainerRoot.height);
                ctx.moveTo(viewContainerRoot.width, 0);
                ctx.lineTo(0, viewContainerRoot.height);
                ctx.closePath();
                ctx.stroke();
            }
        }
    }

//    Item {
//        id: contentContainer
//        anchors.fill: parent
//    }

//    DText {
//        id: sizeOverlay
//        anchors.centerIn: parent
//        text: "[" + viewContainerRoot.width + "x" + viewContainerRoot.height + "]"

//    }


}
