import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

DControl {
    id: optionRoot

    width: CONSTS.defaultOptionWidth
    height: CONSTS.defaultOptionHeight

    property var model: []

    property int currentIndex: -1
    property int count: 0//optionRoot.model.length

    readonly property string stateOpen: "open"
    readonly property string stateClosed: "closed"

    property real unCheckedOpacity: 0.0
    property int unCheckedHeight: 0

    property bool optionInitCompleted: false

    state: stateClosed

    signal itemSelected(var itemIndex)
    signal keyEvent(var event)

    Component.onCompleted: {
        //console.log("DOption.onCompleted");

        // Build Item Model
        buildItemModel();

        // Set Option Init Completed
        optionRoot.optionInitCompleted = true;

        // Chekc Current Index
        if (currentIndex === -1) {
            // Set Current Index
            optionRoot.currentIndex = (optionRoot.model.length > 0 ? 0 : -1)
        }
    }

    onModelChanged: {
        // Check If Init Completed
        if (optionRoot.optionInitCompleted) {
            //console.log("DOption.onModelChanged - model: " + optionRoot.model + " - length: " + optionRoot.model.length);

            // Build Item Model
            buildItemModel();
        }
    }

    onCurrentIndexChanged: {
        // Check If Init Completed
        if (optionRoot.optionInitCompleted) {
            // Set Item Checked
            setItemChecked(optionRoot.currentIndex);
        }
    }

    onItemSelected: {
        // Set State
        optionRoot.state = optionRoot.stateClosed;
    }

    // Build Item Model
    function buildItemModel() {
        //console.log("DOption.buildItemModel - length: " + optionRoot.model.length);

        // Iterate Through Initial Model
        for (var i=0; i<optionRoot.model.length; i++) {
            // Get Model Item Data
            var mData = optionRoot.model[i];
            //console.log("DOption.buildItemModel - mData[" + i + "]: " + mData)
            // Get Item Text
            var itemText = mData.text;
            // Get Item Checked State
            var itemChecked = mData.hasOwnProperty("checked") ? mData.checked : false;
            // Get Item Disabled State
            var itemDisabled = mData.hasOwnProperty("disabled") ? mData.disabled : false;
            // Create New Item Object
            var newObject = newItemComponent.createObject(optionRoot, { "text": itemText, "checked": itemChecked, "disabled": itemDisabled});
            // Replace Item
            optionRoot.model.splice(i, 1, newObject);
        }

        // Set Count
        optionRoot.count = optionRoot.model.length;
    }

    // Clear Item Model
    function clearItemModel() {
        // Clear Item Model
        optionRoot.model.splice(0, optionRoot.model.length);
        // Set Count
        optionRoot.count = optionRoot.model.length;
        // Reset Current Index
        optionRoot.currentIndex = -1;
    }

    // Append Item
    function appendItem(newItemText, disabled) {
        //console.log("DOption.appendItem - newItemText: " + newItemText);
        // Create New Item Object
        var newObject = newItemComponent.createObject(optionRoot, { "text": newItemText, "checked": false, "disabled": disabled});
        // Append To Item Model
        optionRoot.model.push(newObject);
        // Set Count
        optionRoot.count = optionRoot.model.length;

        // Check Current Index
        if (optionRoot.currentIndex === -1 && optionRoot.count > 0) {
            // Set Current Index
            optionRoot.currentIndex = 0;
        }
    }

    // Remove Item
    function removeItem(index) {
        // Remove Item
        optionRoot.model.splice(index, 1);
        // Set Count
        optionRoot.count = optionRoot.model.length;

        // Check Count
        if (optionRoot.count === 0) {
            // Reset Current Index
            optionRoot.currentIndex = -1;
        } else if (optionRoot.currentIndex >= (optionRoot.count - 1)) {
            // Set Current Index
            optionRoot.currentIndex = optionRoot.count - 1;
        }
    }

    // Set Option Focus
    function setOptionFocus(aFocus) {
        // Set Focus
        optionPopup.focus = aFocus;
    }

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
        }
    }

    // Set Item Checked
    function setItemChecked(checkedIndex) {
        //console.log("DOption.setItemChecked - checkedIndex: " + checkedIndex);
        // Iterate Thru Model
        for (var i=0; i<optionRoot.model.length; i++) {
            // Check Checked Index
            optionRoot.model[i].checked = (i === checkedIndex);
        }
    }

    // Export Items
    function exportItems() {
        // Init Item Values
        var itemValues = [];
        // Iterate Thru Model
        for (var i=0; i<optionRoot.model.length; i++) {
            // Append Item Text Value
            itemValues.push(optionRoot.model[i].text);
        }

        // Check Item Values
        if (itemValues.length > 0) {
            return itemValues.join(",");
        }

        return "";
    }

    // New Item Component
    Component {
        id: newItemComponent
        DPopupItemObject { }
    }

    // Option Popup
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
            // Switch Key
            switch (event.key) {
                case Qt.Key_Escape:
                    // Reset Focus
                    optionPopup.focus = false;
                break;

                case Qt.Key_Up:
                    if (optionRoot.currentIndex > 0) {
                        optionRoot.currentIndex--;
                    }
                break;

                case Qt.Key_Down:
                    if (optionRoot.currentIndex < optionRoot.model.length - 1) {
                        optionRoot.currentIndex++;
                    }
                break;

                case Qt.Key_Space:
                    if (optionRoot.state === optionRoot.stateClosed) {
                        optionRoot.state = optionRoot.stateOpen;
                    } else {
                        optionRoot.state = optionRoot.stateClosed;
                    }
                break;

                case Qt.Key_Return:
                    optionRoot.itemSelected(optionRoot.currentIndex);
                break;
            }

            // Emit Key Event
            optionRoot.keyEvent(event);
        }

        Behavior on y { DAnimation { } }

        Column {
            id: optionColumn
            width: parent.width

            Repeater {
                id: optionRepeater

                model: optionRoot.count

//                delegate: Rectangle {
//                    width: optionColumn.width
//                    height: DStyle.popupItemHeight
//                    color: "transparent"
//                    border.color: "orange"
//                }

                delegate: DPopupItem {
                    id: delegateRoot

                    width: optionColumn.width
                    height: checked ? optionRoot.height : optionRoot.unCheckedHeight

                    itemIndex: index

                    property var itemData: optionRoot.model[index]

                    text: optionRoot.model[index].text
                    checked: optionRoot.model[index].checked
                    opacity: checked ? 1.0 : optionRoot.unCheckedOpacity

                    preventStealing: true

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
            //PropertyChanges { target: optionRoot; z: 0.0 }
            PropertyChanges { target: optionPopup; y: 0 }
            PropertyChanges { target: optionPopup; height: optionRoot.height }
        },

        State {
            name: stateOpen

            PropertyChanges { target: optionRoot; unCheckedOpacity: 1.0 }
            PropertyChanges { target: optionRoot; unCheckedHeight: optionRoot.height }
            //PropertyChanges { target: optionRoot; z: 1.0 }
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

                ScriptAction {
                    script: {
                        optionRoot.z = 0.0;
                    }
                }
            }
        },

        Transition {
            to: stateOpen

            SequentialAnimation {
                ScriptAction {
                    script: {
                        optionRoot.z = 1.0;
                    }
                }

                ParallelAnimation {
                    DAnimation { target: optionRoot; properties: "unCheckedOpacity, unCheckedHeight"; easing.type: Easing.Linear }
                    DAnimation { target: optionPopup; properties: "y, height"; easing.type: Easing.Linear }
                }
            }
        }
    ]
}

