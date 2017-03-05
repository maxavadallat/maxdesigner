import QtQuick 2.0

import "style"

DPaneBase {
    id: formulaEditorRoot

    width: Style.formulaEdiorWidth
    height: Style.formulaEditorHeight

    property alias title: label.text

    enablePosOverlay: false
    enableSizeOverlay: false

    minWidth: Style.formulaEdiorWidth
    minHeight: Style.formulaEditorHeight

    enablePaneContent: true

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToRight

    state: stateShown

    clipContent: true

    //border.color: textInput.editor.focus ? Style.colorBorder : Style.colorBorderNoFocus
    border.color: Style.colorBorderNoFocus

    DText {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: Style.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: Style.defaultMargin
        text: "Formula:"
        opacity: formulaEditorRoot.state === formulaEditorRoot.stateShown ? 1.0 : 0.0
    }

    DTextInput {
        id: textInput
        anchors.fill: parent
        anchors {
            leftMargin: Style.defaultMargin
            topMargin: label.height + Style.defaultMargin * 2
            rightMargin: Style.defaultMargin
            bottomMargin: Style.defaultMargin
        }

        fixTextSize: true
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        editor.font.family: "Courier New"
    }
}
