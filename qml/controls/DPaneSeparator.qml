import QtQuick 2.0

//import enginecomponents 0.1

import "../style"
import "../system/DConstants.js" as CONSTS
import "../controls"

DMouseArea {
    id: paneSeparatorRoot

    width: vertical ? DStyle.defaultPaneSeparatorWidth : 400
    height: vertical ? 400 : DStyle.defaultPaneSeparatorWidth

    property bool vertical: false

    property int minX: 0
    property int maxX: 0

    property int minY: 0
    property int maxY: 0

    drag.axis: vertical ? Drag.XAxis : Drag.YAxis

    drag.minimumX: 0
    drag.minimumY: 0
    drag.maximumX: parent && vertical ? parent.width - width : 0
    drag.maximumY: parent && !vertical ? parent.height - height : 0

    // ...

    onPressed: {
        // Set Drag Target
        drag.target = paneSeparatorRoot;
    }

    onReleased: {
        // Reset Drag Target
        drag.target = undefined;
    }


    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: DStyle.colorBorderTransparent
    }

    // ...

    DText {
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        color: paneSeparatorRoot.pressed ? DStyle.colorBorder : DStyle.colorFontDark
        font.pixelSize: DStyle.fontSizeS
        rotation: vertical ? 90 : 0
        visible: parent.width >= DStyle.defaultPaneSeparatorWidth && parent.height >= DStyle.defaultPaneSeparatorWidth
        text: "•••"
    }
}
