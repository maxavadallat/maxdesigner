import QtQuick 2.0

import "qrc:/qml/system/DConstants.js" as CONSTS
import "qrc:/qml/style"

DMouseArea {
    id: sliderRoot

    width: vertical ? CONSTS.defaultSliderHeight : CONSTS.defaultSliderWidth
    height: vertical ? CONSTS.defaultSliderWidth : CONSTS.defaultSliderHeight

    property bool vertical: false

    property bool inverted: false

    property double valueMin: 0.0

    property double valueCenter: sliderRoot.valueMin

    property double valueMax: 100.0

    property double value: 0

    property double valueRange: valueMax - valueMin

    property int visualRange: (vertical ? (sliderRoot.height - sliderPointer.height) : (sliderRoot.width - sliderPointer.width)) + 1

    property int sliderHalfWidth: sliderPointer.width * 0.5
    property int sliderHalfHeight: sliderPointer.height * 0.5

    property int visualRangeOffset: (vertical ? sliderHalfHeight : sliderHalfWidth) + 1

    property int visualRangeCenter: 0

    property double newValue: 0.0

    property bool scribble: false

    property int precisiion: 2

    preventStealing: true

    rotation: sliderRoot.vertical ? (sliderRoot.inverted ? 0 : 180) : (sliderRoot.inverted ? 180 : 0)

    signal sliderValueChanged(var newSliderValue)

    Component.onCompleted: {
        // Set New Value
        sliderRoot.newValue = sliderRoot.value;
    }

    onValueChanged: {
        // Check New Value
        if (sliderRoot.newValue !== sliderRoot.value) {
            // Set New Value
            sliderRoot.newValue = sliderRoot.value;
        }
    }

    onValueMinChanged: {
        // Calculate Slider Pos
        calculateSliderPos();
    }

    onValueCenterChanged: {
        // Calculate Slider Pos
        calculateSliderPos();
    }

    onValueMaxChanged: {
        // Calculate Slider Pos
        calculateSliderPos();
    }

    onNewValueChanged: {
        //console.log("DSlider.onNewValueChanged - newValue: " + sliderRoot.newValue);

        // Calculate Slider Pos
        calculateSliderPos();

        // Check Scribble
        if (sliderRoot.scribble) {
            // Emit Slider Value Changed Signal
            sliderRoot.sliderValueChanged(sliderRoot.newValue);
        }
    }

    onMouseXChanged: {
        // Check If Vertical
        if (!sliderRoot.vertical) {
            // Calculate New Value
            sliderRoot.newValue = calculateNewValue(mouse.x - sliderRoot.visualRangeOffset);
        }
    }

    onMouseYChanged: {
        // Check If Vertical
        if (sliderRoot.vertical) {
            // Calculate New Value
            sliderRoot.newValue = calculateNewValue(mouse.y - sliderRoot.visualRangeOffset);
        }
    }

    onReleased: {
        // Check Scribble
        if (!sliderRoot.scribble) {
            // Emit Slider Value Changed Signal
            sliderRoot.sliderValueChanged(sliderRoot.newValue);
        }
    }

    // Calculate Slider Pos
    function calculateSliderPos() {
        // Get Value Diff
        var valueDiff = sliderRoot.newValue - sliderRoot.valueMin;
        //console.log("DSlider.calculateSliderPos - valueDiff: " + valueDiff);
        return valueDiff * sliderRoot.visualRange / sliderRoot.valueRange;
    }

    // Calculate New Value
    function calculateNewValue(newPos) {
        // Check Vertical Layout
        if (sliderRoot.vertical) {
            // For Some Reason Mouse Position is OFF... So fucking tired of this shit... X (
            newPos += 3;
        }

        // Calculate New Value
        var newValueTemp = (sliderRoot.valueCenter !== sliderRoot.valueMin) ? (newPos - visualRange) * sliderRoot.valueRange / sliderRoot.visualRange + (sliderRoot.valueCenter - sliderRoot.valueMin)
                                                                            : newPos * sliderRoot.valueRange / sliderRoot.visualRange + sliderRoot.valueMin;

        //console.log("DSlider.calculateNewValue - newValueTemp: " + newValueTemp);

        return Math.min(Math.max(newValueTemp, sliderRoot.valueMin), sliderRoot.valueMax).toFixed(sliderRoot.precisiion);
    }

    Rectangle {
        id: sliderBar

        width: vertical ? DStyle.defaultSpacing * 0.5 : sliderRoot.width - sliderPointer.width
        height: vertical ? sliderRoot.height - sliderPointer.height : DStyle.defaultSpacing * 0.5

        anchors.left: sliderRoot.vertical ? undefined : parent.left
        anchors.top: sliderRoot.vertical  ? parent.top : undefined

        anchors.leftMargin: sliderRoot.vertical ? 0 : sliderRoot.sliderHalfWidth
        anchors.topMargin: sliderRoot.vertical ? sliderRoot.sliderHalfHeight : 0

        anchors.horizontalCenter: sliderRoot.vertical ? parent.horizontalCenter : undefined
        anchors.verticalCenter: sliderRoot.vertical ? undefined : parent.verticalCenter

        radius: height * 0.4

        color: sliderRoot.pressed ? DStyle.colorBorder : DStyle.colorBorderNoFocus
    }


    Rectangle {
        id: sliderPointer

        x: calculateSliderPos()
        y: calculateSliderPos()

        width: Math.min(sliderRoot.width, sliderRoot.height) * 0.6
        height: sliderPointer.width

        anchors.horizontalCenter: sliderRoot.vertical ? parent.horizontalCenter : undefined
        anchors.horizontalCenterOffset: sliderRoot.vertical ? 0 : 0
        anchors.verticalCenter: sliderRoot.vertical ? undefined : parent.verticalCenter

        radius: width * 0.5

        color: sliderRoot.pressed ? DStyle.colorBorder : DStyle.colorBorderNoFocus

        border.color: DStyle.colorFontDark
    }
}
