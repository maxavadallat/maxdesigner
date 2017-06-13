import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"
import "qrc:/qml/animations"

DControl {
    id: scrollIndicatorRoot

    width: vertical ? DStyle.scrollIndicatorWidth : viewSize
    height: vertical ? viewSize : DStyle.scrollIndicatorWidth

    property bool vertical: true

    property int viewSize: 0
    property int viewContentSize: 0
    property int viewContentPos: 0

    property bool autoHide: true

    opacity: (viewContentSize > viewSize) && (viewSize > 0) && enabled && !autoHide ? 1.0 : 0.0
    Behavior on opacity { DFadeAnimation { } }
    visible: opacity > 0.0

    onViewSizeChanged: {
        showIndicator();
    }

    onViewContentSizeChanged: {
        showIndicator();
    }

    onViewContentPosChanged: {
        showIndicator();
    }

    // Show Scroll Indicator
    function showIndicator() {
        if (scrollIndicatorRoot.viewContentSize > scrollIndicatorRoot.viewSize) {
            scrollIndicatorRoot.autoHide = false;
            hideTimer.restart();
        }
    }

    Rectangle {
        id: bgRect

        width: vertical ? parent.width : viewSize
        height: vertical ? viewSize : parent.height

        color: "transparent"
        //border.color: "orange"
        radius:  DStyle.scrollIndicatorWidth / 2
        //smooth: true

        Rectangle {
            id: posRect

            x: scrollIndicatorRoot.vertical ? 0 : (scrollIndicatorRoot.viewSize - width) * scrollIndicatorRoot.viewContentPos / (scrollIndicatorRoot.viewContentSize - scrollIndicatorRoot.viewSize)
            y: scrollIndicatorRoot.vertical ? (scrollIndicatorRoot.viewSize - height) * scrollIndicatorRoot.viewContentPos  / (scrollIndicatorRoot.viewContentSize - scrollIndicatorRoot.viewSize) : 0

            color: DStyle.colorFontDark //DStyle.colorBorder
            radius:  DStyle.scrollIndicatorWidth / 2
            smooth: true

            width: {
                if (vertical) {
                    return parent.width;
                }

                if (parent.viewContentSize <= 0) {
                    return 0;
                }

                return scrollIndicatorRoot.viewSize * scrollIndicatorRoot.viewSize / scrollIndicatorRoot.viewContentSize;
            }

            height: {
                if (!vertical) {
                    return parent.height;
                }

                if (parent.viewContentSize <= 0) {
                    return 0;
                }

                return scrollIndicatorRoot.viewSize * scrollIndicatorRoot.viewSize / scrollIndicatorRoot.viewContentSize;
            }
        }
    }

    Timer {
        id: hideTimer
        interval: DStyle.scrollIndicatorTimeout
        onTriggered: {
            // Set Auto Hide
            scrollIndicatorRoot.autoHide = true;
        }
    }
}
