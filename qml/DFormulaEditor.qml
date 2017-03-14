import QtQuick 2.0

import "style"

DPaneBase {
    id: formulaEditorRoot

//    width: DStyle.formulaEdiorWidth
//    height: DStyle.formulaEditorHeight

    title: "Formula" // Id

    enablePosOverlay: false
    enableSizeOverlay: false

    minWidth: DStyle.formulaEdiorWidth
    minHeight: DStyle.formulaEditorHeight

    enablePaneContent: true

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToRight

    clipContent: true

    //border.color: textInput.editor.focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus

    DText {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: DStyle.defaultMargin
        text: formulaEditorRoot.title
        opacity: formulaEditorRoot.state === formulaEditorRoot.stateShown ? 1.0 : 0.0
    }

    DTextInput {
        id: textInput
        anchors.fill: parent
        anchors {
            leftMargin: DStyle.defaultMargin
            topMargin: label.height + DStyle.defaultMargin * 2
            rightMargin: DStyle.defaultMargin
            bottomMargin: DStyle.defaultMargin
        }

        fixTextSize: true
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        editor.font.family: "Courier New"
    }
}
