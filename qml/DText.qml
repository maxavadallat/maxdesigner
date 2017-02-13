import QtQuick 2.0

import "Style.js" as STYLE

Text {
    id: textRoot
    verticalAlignment: Text.AlignVCenter
    color: STYLE.colorFontDark
    font.pixelSize: STYLE.fontSizeM
    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
}
