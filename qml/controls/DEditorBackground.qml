import QtQuick 2.0
//import QtGraphicalEffects 1.0

import "qrc:/qml/style"

Item {
    id: editorBGRoot

    width: 240
    height: 48

    property bool editorFocus: false

    property bool invalidValue: false

    property string borderColor: {

        if (invalidValue) {
            return "red";
        }

        if (editorFocus) {
            return DStyle.colorBorder;
        }

        return DStyle.colorBorderNoFocus;
    }

    property int radius: DStyle.defaultRadius

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: editorBGRoot.borderColor
        radius: editorBGRoot.radius
        //smooth: true
        //antialiasing: true
    }
}
