import QtQuick 2.0

import "DConstants.js" as CONSTS
import "style"

DContainer {
    id: paneBaseRoot

    width: creationWidth
    height: creationHeight

    property string title: "Title"

    property string hideToSide: ""  // "", "left", "right", "top", "bottom"

    readonly property string hideToLeft: "left"
    readonly property string hideToRight: "right"
    readonly property string hideToTop: "top"
    readonly property string hideToBottom: "bottom"

    readonly property string stateCreate: "create"
    readonly property string stateShown: "shown"
    readonly property string stateHidden: "hidden"
    readonly property string stateClosed: "closed"

    property bool dragActive: false

    property QtObject parentPane: null
    property QtObject childPane: null

    property int lastShownX: creationX
    property int lastShownY: creationY

    property int lastShownWidth: creationWidth
    property int lastShownHeight: creationHeight

    property alias titleBottom: titleTextLabel.bottom
    property alias titleHeight: titleTextLabel.height

    property int initialX: {
        if (hideToSide === hideToRight) {
            return parentWidth;
        }

        if (hideToSide === hideToTop) {
            return parentWidth * 0.5;
        }

        return 0;
    }

    property int initialY: {
        if (hideToSide === hideToTop) {
            return 0;
        }

        return parentHeight * 0.5;
    }

    property int creationX: {
        if (hideToSide === hideToTop || hideToSide === hideToBottom) {
            return initialX - creationWidth * 0.5;
        }

        if (hideToSide === hideToRight) {
            return initialX - creationWidth - 32;
        }

        return initialX + 32;
    }

    property int creationY: {
        if (hideToSide === hideToTop) {
            return initialY + 32;
        }

        return initialY - creationHeight * 0.5;
    }

    property int creationWidth: 320
    property int creationHeight: 200

    property int parentWidth: parent ? parent.width : 320
    property int parentHeight: parent ? parent.height : 200

    property int resetWidth: 0
    property int resetHeight: 0

    property bool focusOnShow: false
    property bool enableSizeOverlayOnShow: false
    property bool enableScaling: false

    property bool transitioning: false

    property int hiddenX: {
        switch (hideToSide) {
            case hideToLeft:    return -paneBaseRoot.width;
            case hideToRight:   return paneBaseRoot.parent ? paneBaseRoot.parent.width : paneBaseRoot.x;
        }

        return paneBaseRoot.x;
    }

    property int hiddenY: {
        switch (hideToSide) {
            case hideToBottom:  return paneBaseRoot.parent ? paneBaseRoot.parent.height : paneBaseRoot.y;
            case hideToTop:     return -paneBaseRoot.height;
        }

        return paneBaseRoot.y;
    }

    readonly property int animDuration: DStyle.animDuration * 2.5

    property alias paneContainer: contentContainer

    default property alias paneContainerChildren: contentContainer.children

    property alias enablePaneContent: contentContainer.enabled

    property alias titleLabel: titleTextLabel

    property bool showBackground: true

    property bool showTitle: true

    //property alias topMouseAreaVisible: topMouseArea.visible

    property int scaleDuration: 0
    property real previousScale: 1.0

    Behavior on scale { DAnimation { duration: scaleDuration; easing.type: Easing.Linear } }

    property bool destroyOnResetFinished: false

    property bool enableHideButton: true

    property Connections parentConnections: Connections {
        target: parent

        onWidthChanged: {

        }

        onHeightChanged: {

        }
    }

    property bool hideWaitingForChildReset: false

    property bool resetWaitingForChildReset: false

    property Connections parentPaneConnections: Connections {
        target: parentPane

        onTransitionFinished: {
            // Emit Parent Transition Finished Signal
            paneBaseRoot.parentTransitionFinished(newState);
        }

        onResetChildRequest: {
            // Reset
            paneBaseRoot.reset(false);
        }
    }

    property Connections childPaneConnections: Connections {
        target: childPane

        onTransitionFinished: {
            if (newState === stateCreate) {
                // Check Hide Waiting For Child Reset
                if (paneBaseRoot.hideWaitingForChildReset) {
                    // Hide
                    paneBaseRoot.hide();
                }

                // Check Reset Waiting For Child Reset
                if (paneBaseRoot.resetWaitingForChildReset) {
                    // Reset
                    paneBaseRoot.reset(false);
                }
            }

            // Reset Hide Waiting For Reset
            paneBaseRoot.hideWaitingForChildReset = false;
            // Reset Reset Waiting For Child Reset
            paneBaseRoot.resetWaitingForChildReset = false;
            // Emit Child Transmition Finished Signal
            paneBaseRoot.childTransitionFinished(newState);
        }
    }

    readonly property string hideActionHide: "hide"
    readonly property string hideActionReset: "reset"

    property string hideAction: hideActionHide

    property bool hideButtonVisibleOnCreate: false

    enableSizeOverlay: false
    enablePosOverlay: false

    clipContent: true

    state: stateCreate

    signal accepted()
    signal rejected()

    signal transitionFinished(var newState)
    signal transitionStarted(var newState)

    signal resetChildRequest()

    signal childTransitionFinished(var newState)
    signal parentTransitionFinished(var newState)

    onWidthChanged: {
//        // Check State
//        if (paneBaseRoot.state === paneBaseRoot.stateShown) {
//            // Update Creation Width
//            paneBaseRoot.creationWidth = paneBaseRoot.width;
//        }
    }

    onHeightChanged: {
//        // Check State
//        if (paneBaseRoot.state === paneBaseRoot.stateShown) {
//            // Update Creation Height
//            paneBaseRoot.creationHeight = paneBaseRoot.height;
//        }
    }

    onPressed: {
        //console.log("DPaneBase.onPressed");
        // Check Set Drag Target
        if (paneBaseRoot.parent.bringToFront !== undefined) {
            // Set Drag Target - ASSUMING Parent is MainGrabArea
            paneBaseRoot.parent.bringToFront(paneBaseRoot);
        }
    }

    onReleased: {
        //console.log("DPaneBase.onReleased");
    }

    onResizePressed: {
        // Check Set Drag Target
        if (paneBaseRoot.parent.bringToFront !== undefined) {
            // Set Drag Target
            paneBaseRoot.parent.bringToFront(paneBaseRoot);
        }
    }

    onAccepted: {
        // Reset
        paneBaseRoot.reset(false);
    }

    onRejected: {
        // Reset
        paneBaseRoot.reset(false);
    }

    // Reset To Create State
    function reset(destroyOnFinished) {
        // Check Hide To Sie
        if (paneBaseRoot.hideToSide === paneBaseRoot.hideToLeft || paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom) {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.x + paneBaseRoot.width - paneBaseRoot.initialX;
        } else {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.initialX - paneBaseRoot.x;
            // Set Reset Height
            paneBaseRoot.resetHeight = paneBaseRoot.y + paneBaseRoot.height - paneBaseRoot.initialY;
        }

        // Set Destroy On Finished
        paneBaseRoot.destroyOnResetFinished = destroyOnFinished;

        //console.log("DPaneBase.reset - destroyOnFinished: " + destroyOnFinished);

        // Set State
        paneBaseRoot.state = stateCreate;
    }

    // Show
    function show() {
        // Check Parent Pane State
        if (parentPane && parentPane.state !== stateShown) {
            return;
        }

        // Set State
        paneBaseRoot.state = stateShown;
    }

    // Hide
    function hide() {
        // Set Last Shown X & Y
        paneBaseRoot.lastShownX = paneBaseRoot.x;
        paneBaseRoot.lastShownY = paneBaseRoot.y;

        // Set Creation Width
        paneBaseRoot.creationWidth = paneBaseRoot.width;
        paneBaseRoot.creationHeight = paneBaseRoot.height;

        // Set State
        paneBaseRoot.state = stateHidden;
    }

    // Close
    function close() {
        // Check Hide To Sie
        if (paneBaseRoot.hideToSide === paneBaseRoot.hideToLeft || paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom) {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.x + paneBaseRoot.width - paneBaseRoot.initialX;
        } else {
            // Set Reset Width
            paneBaseRoot.resetWidth = paneBaseRoot.initialX - paneBaseRoot.x;
            // Set Reset Height
            paneBaseRoot.resetHeight = paneBaseRoot.y + paneBaseRoot.height - paneBaseRoot.initialY;
        }

        // Set Destroy On Finished
        paneBaseRoot.destroyOnResetFinished = true;

        // Set State
        paneBaseRoot.state = stateClosed;
    }

    // Bring To Front
    function bringToFront() {
        if (paneBaseRoot.parent && paneBaseRoot.parent.bringToFront !== undefined) {
            paneBaseRoot.parent.bringToFront(paneBaseRoot);
        }
    }

    // Dismiss Pane
    function dismissPane(reset) {
        if (childPane && childPane.state === stateShown) {
            // Check Reset
            if (reset) {
                // Set Reset Waiting For Reset
                paneBaseRoot.resetWaitingForChildReset = true;
            } else {
                // Set Hide Waiting For Reset
                paneBaseRoot.hideWaitingForChildReset = true;
            }

            // Emit Reset Child Request Signal
            paneBaseRoot.resetChildRequest();
        } else {
            if (reset) {
                // Reset
                paneBaseRoot.rejected();
            } else {
                // Hide
                paneBaseRoot.hide();
            }
        }
    }

    // Title
    DText {
        id: titleTextLabel
        anchors.left: parent.left
        anchors.leftMargin: DStyle.defaultMargin
        anchors.top: parent.top
        anchors.topMargin: DStyle.defaultMargin
        text: paneBaseRoot.title
        Behavior on opacity { DFadeAnimation { } }
        opacity: 0.0
        visible: paneBaseRoot.showTitle && opacity > 0.0
    }

    // Content Container
    Item {
        id: contentContainer
        anchors.fill: parent
    }

//    MouseArea {
//        id: topMouseArea
//        anchors.fill: parent

//        visible: paneBaseRoot.focus

//        onPressed: {
//            //console.log("DPaneBase.topMouseArea.onPressed");
//            // Check Set Drag Target
//            if (paneBaseRoot.parent.bringToFront !== undefined) {
//                // Set Drag Target - ASSUMING Parent is MainGrabArea
//                paneBaseRoot.parent.bringToFront(paneBaseRoot);
//            }

//            // Set Mouse Event Accepted
//            mouse.accepted = false;
//        }

//        onReleased: {
//            //console.log("DPaneBase.topMouseArea.onReleased");
//            // Set Mouse Event Accepted
//            mouse.accepted = false;
//        }
//    }

    // Hide Indicator
    DControl {
        id: hideShowButton

        parent: paneBaseRoot

        width: {
            switch (paneBaseRoot.hideToSide) {
                case paneBaseRoot.hideToBottom:
                case paneBaseRoot.hideToTop:    return CONSTS.defaultPaneHideButtonHeight;
            }

            return CONSTS.defaultPaneHideButtonWidth;
        }

        height: {
            switch (paneBaseRoot.hideToSide) {
                case paneBaseRoot.hideToBottom:
                case paneBaseRoot.hideToTop:    return CONSTS.defaultPaneHideButtonWidth;
            }

            return CONSTS.defaultPaneHideButtonHeight;
        }

        anchors.left: paneBaseRoot.hideToSide === paneBaseRoot.hideToLeft ? parent.right : undefined
        anchors.right: paneBaseRoot.hideToSide === paneBaseRoot.hideToRight ? parent.left : undefined
        anchors.bottom: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.top : undefined
        anchors.top: paneBaseRoot.hideToSide === paneBaseRoot.hideToTop ? parent.bottom : undefined

        anchors.horizontalCenter: {
            switch (paneBaseRoot.hideToSide) {
                case paneBaseRoot.hideToBottom:
                case paneBaseRoot.hideToTop:    return parent.horizontalCenter;
            }

            return undefined;
        }

        anchors.verticalCenter: {
            switch (paneBaseRoot.hideToSide) {
                case paneBaseRoot.hideToLeft:
                case paneBaseRoot.hideToRight:  return parent.verticalCenter;
            }

            return undefined;
        }

        Behavior on opacity { DFadeAnimation { } }
        opacity: 0.0
        visible: paneBaseRoot.hideToSide !== "" && opacity > 0.0

        DText {
            id: hideButtonText
//            width: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.width : parent.height
//            height: paneBaseRoot.hideToSide === paneBaseRoot.hideToBottom ? parent.height : parent.width
            anchors.centerIn: parent
            rotation: {
                switch (paneBaseRoot.hideToSide) {
                    case paneBaseRoot.hideToLeft:   return -90;
                    case paneBaseRoot.hideToRight:  return 90;
                }

                return 0;
            }

            horizontalAlignment: Text.AlignHCenter
            color: buttonMouseArea.pressed ? DStyle.colorBorder : DStyle.colorFontDark
            text: "•••"
        }

        DMouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: {
                // Check Hide Action
                if (paneBaseRoot.hideAction === paneBaseRoot.hideActionReset && paneBaseRoot.state === stateShown) {
                    // Reset
                    paneBaseRoot.reset(false);

                } else if (paneBaseRoot.hideAction === paneBaseRoot.hideActionReset && paneBaseRoot.state !== stateShown) {
                    // Set State
                    paneBaseRoot.show();

                } else if (paneBaseRoot.state !== stateHidden) {
                    // Dismiss Pane
                    paneBaseRoot.dismissPane(false);

                } else {
                    // Set State
                    paneBaseRoot.show();
                }
            }
        }
    }

    Item {
        id: dummy
        visible: false
    }

    states: [
        State {
            name: ""
        },

        State {
            name: stateCreate

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.initialX; y: paneBaseRoot.initialY; width: 0; height: 0 }
            PropertyChanges { target: titleTextLabel; opacity: 0.0 }
            PropertyChanges { target: hideShowButton; opacity: paneBaseRoot.hideButtonVisibleOnCreate && paneBaseRoot.enableHideButton ? 1.0 : 0.0 }
        },

        State {
            name: stateShown

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.lastShownX; y: paneBaseRoot.lastShownY }
            PropertyChanges { target: paneBaseRoot; width: paneBaseRoot.creationWidth; height: paneBaseRoot.creationHeight }
            PropertyChanges { target: titleTextLabel; opacity: 1.0 }
            PropertyChanges { target: hideShowButton; opacity: paneBaseRoot.enableHideButton ? 1.0 : 0.0 }
        },

        State {
            name: stateHidden

            PropertyChanges { target: paneBaseRoot; x: paneBaseRoot.hiddenX; y: paneBaseRoot.hiddenY }
            PropertyChanges { target: paneBaseRoot; width: paneBaseRoot.creationWidth; height: paneBaseRoot.creationHeight }
            PropertyChanges { target: titleTextLabel; opacity: 1.0 }
            PropertyChanges { target: hideShowButton; opacity: paneBaseRoot.enableHideButton ? 1.0 : 0.0 }
        },

        State {
            name: stateClosed

            PropertyChanges { target: paneBaseRoot; width: 0; height: 0 }
            PropertyChanges { target: titleTextLabel; opacity: 0.0 }
            PropertyChanges { target: hideShowButton; opacity: 0.0 }
        }
    ]

    transitions: [
        // To Create
        Transition {
            //from: ""
            to: stateCreate

            SequentialAnimation {
                ParallelAnimation {
                    PropertyAction { target: paneBaseRoot; properties: "width, height"; value: 0 }
                    PropertyAction { target: paneBaseRoot; property: "x"; value: paneBaseRoot.initialX }
                    PropertyAction { target: paneBaseRoot; property: "y"; value: paneBaseRoot.initialY }
                    DFadeAnimation { target: titleTextLabel }
                    DFadeAnimation { target: hideShowButton }
                }
            }
        },

        // From Create To Shown
        Transition {
            from: stateCreate
            to: stateShown

            SequentialAnimation {

                ScriptAction {
                    script: {
                        // Emit Transition Started
                        paneBaseRoot.transitionStarted(stateShown);
                        // Bring To Font
                        paneBaseRoot.bringToFront();
                        // Set Hide Button Text
                        hideButtonText.text = "•••";
                    }
                }

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: true }

                PauseAnimation { duration: 200 }

                PropertyAction { target: (hideToSide !== hideToTop ? paneBaseRoot : dummy); property: "height"; value: 1 }
                PropertyAction { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "width"; value: 1 }

                PropertyAction { target: paneBaseRoot; property: "x"; value: paneBaseRoot.initialX }
                PropertyAction { target: paneBaseRoot; property: "y"; value: paneBaseRoot.initialY }

                ParallelAnimation {
                    DAnimation { target: (hideToSide === hideToLeft ? paneBaseRoot : dummy); property: "width"; to: paneBaseRoot.creationWidth + paneBaseRoot.creationX - paneBaseRoot.initialX }

                    DAnimation { target: (hideToSide === hideToRight ? paneBaseRoot : dummy); property: "x"; to: paneBaseRoot.creationX }
                    DAnimation { target: (hideToSide === hideToRight ? paneBaseRoot : dummy); property: "width"; to: paneBaseRoot.initialX - paneBaseRoot.creationX }

                    DAnimation { target: (hideToSide === hideToBottom ? paneBaseRoot : dummy); property: "width"; to: paneBaseRoot.creationWidth + paneBaseRoot.creationX - paneBaseRoot.initialX }

                    DAnimation { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "height"; to: paneBaseRoot.creationY + paneBaseRoot.creationHeight - paneBaseRoot.initialY }
                }

                ParallelAnimation {
                    DAnimation { target: (hideToSide !== hideToTop ? paneBaseRoot : dummy); property: "width" }
                    DAnimation { target: (hideToSide !== hideToTop ? paneBaseRoot : dummy); property: "x" }

                    DAnimation { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "height"; to: paneBaseRoot.creationHeight }
                    DAnimation { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "y"; to: paneBaseRoot.creationY }
                }

                ParallelAnimation {
                    DAnimation { target: (hideToSide !== hideToTop ? paneBaseRoot : dummy); property: "y" }
                    DAnimation { target: (hideToSide !== hideToTop ? paneBaseRoot : dummy); property: "height" }

                    DAnimation { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "x" }
                    DAnimation { target: (hideToSide === hideToTop ? paneBaseRoot : dummy); property: "width" }

                    DFadeAnimation { target: hideShowButton }
                }

                PropertyAction { target: titleTextLabel; property: "opacity"; value: 1.0 }

                PropertyAction { target: paneBaseRoot; property: "enableSizeOverlay"; value: paneBaseRoot.enableSizeOverlayOnShow }
                PropertyAction { target: paneBaseRoot; property: "focus"; value: paneBaseRoot.focusOnShow }

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: false }

                ScriptAction {
                    script: {
                        // Reset Cliping Content
                        paneBaseRoot.clipContent = true;
                        // Emit Transition Finished Signal
                        paneBaseRoot.transitionFinished(stateShown);
                    }
                }
            }
        },

        // From Shown To Create
        Transition {
            from: stateShown
            to: stateCreate

            SequentialAnimation {

                ScriptAction {
                    script: {
                        // Emit Transition Started
                        paneBaseRoot.transitionStarted(stateCreate);
                        // Set Cliping Content
                        paneBaseRoot.clipContent = true;
                    }
                }

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: true }

                PropertyAction { target: paneBaseRoot; property: "enableSizeOverlay"; value: false }
                PropertyAction { target: titleTextLabel; property: "opacity"; value: 0.0 }

                ParallelAnimation {
                    DAnimation { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "y"; to: paneBaseRoot.y + paneBaseRoot.height * 0.5 }
                    DAnimation { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "height"; to: 1 }

                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.x + paneBaseRoot.width * 0.5 }
                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "width"; to: 1 }

                    DFadeAnimation { target: hideShowButton }
                }

                ParallelAnimation {
                    DAnimation { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "width"; to: paneBaseRoot.resetWidth }
                    DAnimation { target: hideToSide === hideToLeft ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.initialX }
                    DAnimation { target: hideToSide === hideToBottom ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.initialX }

                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "y"; to: paneBaseRoot.initialY }
                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "height"; to: paneBaseRoot.resetHeight }
                }

                ParallelAnimation {
                    DAnimation { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "width"; to: 0 }
                    DAnimation { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "x"; to: paneBaseRoot.initialX }

                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "height"; to: 0 }
                    DAnimation { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "y"; to: paneBaseRoot.initialY }
                }

                ParallelAnimation {
                    PropertyAction { target: hideToSide !== hideToTop ? paneBaseRoot : dummy; property: "height"; value: 0 }
                    PropertyAction { target: hideToSide === hideToTop ? paneBaseRoot : dummy; property: "width"; value: 0 }
                }

                PropertyAction { target: paneBaseRoot; property: "transitioning"; value: false }

                ScriptAction {
                    script: {
                        // Emit Transition Finished Signal
                        paneBaseRoot.transitionFinished(stateCreate);
                        // Check Destroy On Finished
                        if (paneBaseRoot.destroyOnResetFinished) {
                            // Check Focused Component
                            if (propertiesController.focusedComponent === componentInfo) {
                                // Reset Focused
                                propertiesController.focusedComponent = null;
                            }

                            // Select Other File
                            openFilesModel.selectFile(openFilesModel.currentIndex);

                            // Destroy
                            paneBaseRoot.destroy();
                        }
                    }
                }
            }
        },

        // From Hidden To Shown
        Transition {
            from: stateHidden
            to: stateShown

            SequentialAnimation {
                ScriptAction {
                    script: {
                        // Emit Transition Started
                        paneBaseRoot.transitionStarted(stateShown);
                        // Bring To Font
                        paneBaseRoot.bringToFront();
                        // Set Hide Button Text
                        hideButtonText.text = "•••";
                    }
                }

                PropertyAnimation { target: paneBaseRoot; properties: "x, y"; easing.type: Easing.InOutBack; duration: paneBaseRoot.animDuration }

                ScriptAction {
                    script: {
                        // Reset Cliping Content
                        paneBaseRoot.clipContent = true;
                        // Emit Transition Finished Signal
                        paneBaseRoot.transitionFinished(stateShown);
                    }
                }
            }
        },

        // To Hidden
        Transition {
            //from: stateShown
            to: stateHidden

            SequentialAnimation {
                ScriptAction {
                    script: {
                        // Emit Transition Started
                        paneBaseRoot.transitionStarted(stateHidden);
                    }
                }

                PropertyAnimation { target: paneBaseRoot; properties: "x, y"; easing.type: Easing.InOutBack; duration: paneBaseRoot.animDuration }

                ScriptAction {
                    script: {
                        // Set Hide Button Text
                        hideButtonText.text = paneBaseRoot.title;
                        // Reset Cliping Content
                        paneBaseRoot.clipContent = true;
                        // Emit Transition Finished Signal
                        paneBaseRoot.transitionFinished(stateHidden);
                    }
                }
            }
        },

        // To Closed
        Transition {
            to: stateClosed

            SequentialAnimation {
                ScriptAction {
                    script: {
                        // Emit Transition Started
                        paneBaseRoot.transitionStarted(stateClosed);
                    }
                }

                // ...

                ScriptAction {
                    script: {
                        // Emit Transition Finished Signal
                        paneBaseRoot.transitionFinished(stateClosed);

                        // ...

                        // Destroy
                        paneBaseRoot.destroy();
                    }
                }
            }
        }
    ]
}
