import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "Style.js" as STYLE

DControl {
    id: activityIndicatorRoot

    width: STYLE.activityIndicatorWidth
    height: STYLE.activityIndicatorHeight

    property alias running: activityIndicatorTimer.running

    property int angle: 0
    property int step: 5

//    smooth: true
//    antialiasing: true

//    Rectangle {
//        id: activityIndicatorBase
//        anchors.fill: parent
//        radius: width * 0.5
//        visible: false
//    }

    Canvas {
        id: activityIndicatorBase
        anchors.fill: parent

        property real radius: Math.min(width, height) * 0.5 - STYLE.activityIndicatorLineWidth
        property int centreX: width * 0.5
        property int centreY: height * 0.5

        visible: false

        //visible: false
        onPaint: {
            var ctx = getContext("2d");


            ctx.beginPath();

            ctx.lineWidth = STYLE.activityIndicatorLineWidth;
            ctx.strokeStyle = "white";

            ctx.arc(centreX, centreY, radius, 0, 2 * Math.PI);

            ctx.stroke();
        }
    }

    ConicalGradient {
        id: activityIndicatorGradient
        anchors.fill: parent
        source: activityIndicatorBase
        angle: activityIndicatorRoot.angle
        visible: false

        gradient: Gradient {
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 0.2; color: "transparent" }
            GradientStop { position: 1.0; color: STYLE.colorBorder }
        }
    }

    Timer {
        id: activityIndicatorTimer
        interval: STYLE.activityIndicatorInterval
        repeat: true
        onTriggered: {
            activityIndicatorGradient.visible = true;

            // Check Angle
            if (activityIndicatorRoot.angle < 360) {
                // Inc Angle
                activityIndicatorRoot.angle += activityIndicatorRoot.step;
            } else {
                // Reset Angle
                activityIndicatorRoot.angle = 0;
            }

            // Request Paint
            //activityIndicatorCanvas.requestPaint();
        }
    }

//    BusyIndicator {
//        id: busyIndicator
//        anchors.fill: parent
//    }
}
