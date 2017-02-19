import QtQuick 2.0

QtObject {
    property string text: "Item"
    property bool disabled: false
    property bool subMenuItem: false
    property list<QtObject> subMenu
}
