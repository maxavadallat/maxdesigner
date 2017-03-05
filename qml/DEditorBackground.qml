import QtQuick 2.0
import QtGraphicalEffects 1.0

import "style"

Item {
    id: editorBGRoot

    width: 240
    height: 48

    property bool editorFocus: false

//    property bool highLight: false

//    color: Style.colorEditorBG
//    border.color: Style.colorBG
//    color: "transparent"

    property int radius: Style.defaultRadius

//    smooth: true
//    antialiasing: true
/*
    Rectangle {
        id: shadowRectangle
        anchors.fill: parent
        anchors.margins: 1
        color: Style.colorEditorBG
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
        color: Style.colorShadow
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
//        color: Style.colorBorder
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
//        color: Style.colorShadow
//        source: highlightShadowRectangle
//        visible: editorBGRoot.highLight
////        smooth: true
////        antialiasing: true
//    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: editorBGRoot.editorFocus ? Style.colorBorder : Style.colorBorderNoFocus
        radius: editorBGRoot.radius
        smooth: true
        antialiasing: true
    }
}
