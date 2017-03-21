import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

DControl {
    id: optionRoot

    width: CONSTS.defaultOptionWidth
    height: CONSTS.defaultOptionHeight

    property list<QtObject> model

    property int currentIndex: -1

    readonly property string stateOpen: "open"
    readonly property string stateClosed: "closed"

    property real unCheckedOpacity: 0.0
    property int unCheckedHeight: 0

    state: stateClosed

    onModelChanged: {
        // Set Current Index
        optionRoot.currentIndex = (optionRoot.model.length > 0 ? 0 : -1)
    }

    onCurrentIndexChanged: {
        // Set Item Checked
        setItemChecked(optionRoot.currentIndex);
    }

    signal itemSelected(var itemIndex)

    // Item Clicked
    function itemClicked(itemIndex) {
        // Check State
        if (optionRoot.state === optionRoot.stateClosed) {
            // Set State
            optionRoot.state = optionRoot.stateOpen;
        } else {
            // Set Item Checked
            optionRoot.currentIndex = itemIndex;
            // Emit Item Selected Signal
            optionRoot.itemSelected(optionRoot.currentIndex);
            // Set State
            optionRoot.state = optionRoot.stateClosed;
        }
    }

    // Set Item Checked
    function setItemChecked(checkedIndex) {
        // Get Count
        var mCount = optionRoot.model.length;
        // Iterate Thru Model
        for (var i=0; i<mCount; i++) {
            // Check Checked Index
            optionRoot.model[i].checked = (i === checkedIndex);
        }
    }

    DRectangle {
        id: optionPopup
        width: optionRoot.width
        height: optionRoot.height
        border.color: focus ? DStyle.colorBorder : DStyle.colorBorderNoFocus
        onFocusChanged: {
            if (!optionPopup.focus) {
                // Set State
                optionRoot.state = optionRoot.stateClosed;
            }
        }

        Keys.onReleased: {
            if (event.key === Qt.Key_Escape) {
                // Reset Focus
                optionPopup.focus = false;
            }
        }

        Behavior on y { DAnimation { } }

        Column {
            id: optionColumn
            width: parent.width

            Repeater {
                id: optionRepeater
                model: optionRoot.model

                delegate: DPopupItem {
                    id: delegateRoot
                    width: optionPopup.width
                    height: checked ? optionRoot.height : optionRoot.unCheckedHeight
                    itemIndex: index
                    text: model.text
                    checked: model.checked
                    opacity: checked ? 1.0 : optionRoot.unCheckedOpacity
                    preventStealing: true

                    onEntered: {

                    }

                    onExited: {

                    }

                    onClicked: {
                        optionPopup.focus = true;
                        optionRoot.itemClicked(itemIndex);
                    }

                    onCanceled: {
                        // Set State
                        optionRoot.state = optionRoot.stateClosed;
                    }
                }
            }
        }
    }

    states: [
        State {
            name: stateClosed

            PropertyChanges { target: optionRoot; unCheckedOpacity: 0.0 }
            PropertyChanges { target: optionRoot; unCheckedHeight: 0 }
            PropertyChanges { target: optionPopup; y: 0 }
            PropertyChanges { target: optionPopup; height: optionRoot.height }
        },

        State {
            name: stateOpen

            PropertyChanges { target: optionRoot; unCheckedOpacity: 1.0 }
            PropertyChanges { target: optionRoot; unCheckedHeight: optionRoot.height }
            PropertyChanges { target: optionPopup; y: -optionRoot.height * optionRoot.currentIndex }
            PropertyChanges { target: optionPopup; height: optionRoot.height * optionRepeater.count }
        }
    ]

    transitions: [
        Transition {
            to: stateClosed

            SequentialAnimation {
                ParallelAnimation {
                    DAnimation { target: optionRoot; properties: "unCheckedOpacity, unCheckedHeight"; easing.type: Easing.Linear }
                    DAnimation { target: optionPopup; properties: "y, height"; easing.type: Easing.Linear }
                }
            }
        },

        Transition {
            to: stateOpen

            SequentialAnimation {
                ParallelAnimation {
                    DAnimation { target: optionRoot; properties: "unCheckedOpacity, unCheckedHeight"; easing.type: Easing.Linear }
                    DAnimation { target: optionPopup; properties: "y, height"; easing.type: Easing.Linear }
                }
            }
        }
    ]
}

