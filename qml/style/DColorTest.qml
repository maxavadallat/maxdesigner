import QtQuick 2.0

import "."

Column {
    width: 256
    anchors.centerIn: parent

    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorMainBG; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorFontLight; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorFontDark; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorBG; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorBorder; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorBorderNoFocus; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorBorderSelected; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorBorderTransparent; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorShadow; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorHighLight; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorSelected; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorEditorBG; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorRadioButton; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorTrace; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorViewBG1; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorViewBG2; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorSelectedHighLight; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorOK; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorOKHighLight; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorOKSelected; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorCancel; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorCancelHighLight; border.color: "darkgray" }
    Rectangle { width: parent.width; height: Style.listItemHeight; color: Style.colorCancelSelected; border.color: "darkgray" }
}
