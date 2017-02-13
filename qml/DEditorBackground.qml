import QtQuick 2.0
import QtGraphicalEffects 1.0

import "Style.js" as STYLE

Item {
    id: editorBGRoot

    width: 240
    height: 48

    property bool editorFocus: false

//    property bool highLight: false

//    color: STYLE.colorEditorBG
//    border.color: STYLE.colorBG
//    color: "transparent"

    property int radius: STYLE.defaultRadius

//    smooth: true
//    antialiasing: true
/*
    Rectangle {
        id: shadowRectangle
        anchors.fill: parent
        anchors.margins: 1
        color: STYLE.colorEditorBG
        radius: parent.radius
        visible: false
//        smooth: true
//        antialiasing: true
    }

    InnerShadow {
        id: normalShadow
        anchors.fill: parent
        radius: 8.0
        samples: 16
        horizontalOffset: 3
        verticalOffset: 3
        color: STYLE.colorShadow
        source: shadowRectangle
        visible: !editorBGRoot.highLight
//        smooth: true
//        antialiasing: true
    }
*/

//    Rectangle {
//        id: highlightShadowRectangle
//        anchors.fill: parent
//        anchors.margins: 1
//        color: STYLE.colorBorder
//        radius: parent.radius
//        visible: false
////        smooth: true
////        antialiasing: true
//    }

//    InnerShadow {
//        id: highLightShadow
//        anchors.fill: parent
//        radius: 8.0
//        samples: 16
//        horizontalOffset: 3
//        verticalOffset: 3
//        color: STYLE.colorShadow
//        source: highlightShadowRectangle
//        visible: editorBGRoot.highLight
////        smooth: true
////        antialiasing: true
//    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: editorBGRoot.editorFocus ? STYLE.colorBorder : STYLE.colorBorderNoFocus
        radius: editorBGRoot.radius
        smooth: true
        antialiasing: true
    }
}
