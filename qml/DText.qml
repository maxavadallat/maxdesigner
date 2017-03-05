import QtQuick 2.0

import "style"

Text {
    id: textRoot
    verticalAlignment: Text.AlignVCenter
    color: Style.colorFontDark
    font.pixelSize: Style.fontSizeM
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere

    opacity: enabled ? 1.0 : Style.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: Style.animDuration } }
    visible: opacity > 0.0
}
