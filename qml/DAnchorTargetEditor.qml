import QtQuick 2.0
import QtGraphicalEffects 1.0

import enginecomponents 0.1

import "style"
import "DConstants.js" as CONSTS

Item {
    id: anchorTargetEditorRoot

    width: CONSTS.defaultAnchorTargetEditorWidth
    height: CONSTS.defaultAnchorTargetEditorHeight

    property alias text: anchorTargetEditor.text

    property bool showEditor: true

    opacity: showEditor ? 1.0 : 0.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    signal rejected()
    signal accepted(var newTarget)

    onAccepted: {
        // Hide
        anchorTargetEditorRoot.hide();
    }

    onRejected: {
        // Hide
        anchorTargetEditorRoot.hide();
    }

    function show(aX, aY) {
        // Set Position
        anchorTargetEditorRoot.x = aX;
        anchorTargetEditorRoot.y = aY;
        // Set Show Editor
        anchorTargetEditorRoot.showEditor = true;
        // Set Editor Focus
        anchorTargetEditor.setEditorFocus(true, true);
    }

    function hide() {
        // Reset Show Editor
        anchorTargetEditorRoot.showEditor = false;
    }

    Rectangle {
        id: bgRect
        anchors.fill: parent
        radius: DStyle.defaultRadius
        color: "black"//DStyle.colorBG
        visible: false
    }

    Glow {
        anchors.fill: bgRect
        source: bgRect
        radius: 8
        samples: 20
        color: DStyle.colorBorder //"orange"
    }

    DTextInput {
        id: anchorTargetEditor
        anchors.fill: parent
        //anchors.margins: DStyle.defaultMargin

        onAccepted: {
            anchorTargetEditorRoot.accepted(anchorTargetEditor.text);
        }

        onKeyEvent: {
            if (event.key === Qt.Key_Escape) {
                anchorTargetEditorRoot.rejected();
            }
        }
    }
}
