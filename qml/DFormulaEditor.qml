import QtQuick 2.0

import "Style.js" as STYLE

DPaneBase {
    id: formulaEditorRoot

    width: STYLE.formulaEdiorWidth
    height: STYLE.formulaEditorHeight

    property alias title: label.text

    enablePosOverlay: false
    enableSizeOverlay: false

    minWidth: STYLE.formulaEdiorWidth
    minHeight: STYLE.formulaEditorHeight

    enablePaneContent: true

    setFocusOnResize: false

    topMouseAreaVisible: true

    hideToSide: hideToRight

    state: stateShown

    clipContent: true

    //border.color: textInput.editor.focus ? STYLE.colorBorder : STYLE.colorBorderNoFocus
    border.color: STYLE.colorBorderNoFocus

    DText {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: STYLE.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: STYLE.defaultMargin
        text: "Formula:"
        opacity: formulaEditorRoot.state === formulaEditorRoot.stateShown ? 1.0 : 0.0
    }

    DTextInput {
        id: textInput
        anchors.fill: parent
        anchors {
            leftMargin: STYLE.defaultMargin
            topMargin: label.height + STYLE.defaultMargin * 2
            rightMargin: STYLE.defaultMargin
            bottomMargin: STYLE.defaultMargin
        }

        fixTextSize: true
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        editor.font.family: "Courier New"
    }
}
