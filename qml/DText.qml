import QtQuick 2.0

import "Style.js" as STYLE

Text {
    id: textRoot
    verticalAlignment: Text.AlignVCenter
    color: STYLE.colorFontDark
    font.pixelSize: STYLE.fontSizeM
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere

    opacity: enabled ? 1.0 : STYLE.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: STYLE.animDuration } }
    visible: opacity > 0.0
}
