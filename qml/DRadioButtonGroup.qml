import QtQuick 2.0

import "style"
import "Constants.js" as CONSTS

DControl {
    id: radioButtonGroupRoot

    width: CONSTS.defaultButtonGroupWidth
    height: buttonsColumn.height

    property list<QtObject> model

    property int currentIndex: -1

    property bool rightAligned: false

    signal buttonSelected(var buttonIndex)

    onCurrentIndexChanged: {
        // Get Model Count
        var mCount = model.length
        // Iterate Through Model
        for (var i=0; i<mCount; i++) {
            // Set Selected
            radioButtonGroupRoot.model[i].selected = (i === radioButtonGroupRoot.currentIndex);
        }
    }

    Column {
        id: buttonsColumn
        width: parent.width

        Repeater {
            id: buttonsRepeater

            model: radioButtonGroupRoot.model

            delegate: DRadioButton {
                id: delegateRoot
                width: radioButtonGroupRoot.width
                buttonIndex: index
                text: model.title
                checked: model.selected
                rightAligned: radioButtonGroupRoot.rightAligned
                onButtonClicked: {
                    //console.log("DRadioButtonGroup.buttonsRepeater.delegate.onButtonClicked - index: " + index);
                    // Set Current Index
                    //radioButtonGroupRoot.currentIndex = buttonIndex;
                    // Emit Button Selected Signal
                    radioButtonGroupRoot.buttonSelected(index);
                }
            }
        }
    }
}
