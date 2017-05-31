import QtQuick 2.0

import "style"

Text {
    id: textRoot
    verticalAlignment: Text.AlignVCenter
    color: DStyle.colorFontDark
    font.pixelSize: DStyle.fontSizeM
    //font.family: DStyle.zektonFontName
    //font.family: DStyle.instrument101FontName
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    opacity: enabled ? 1.0 : DStyle.disabledOpacity
    Behavior on opacity { NumberAnimation { duration: DStyle.animDuration } }
    visible: opacity > 0.0
}
