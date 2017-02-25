import QtQuick 2.0

import enginecomponents 0.1

import "Constants.js" as CONSTS
import "Style.js" as STYLE

Item {
    id: mainRoot

    Rectangle {
        id: bgContainer
        anchors.fill: parent

        color: STYLE.colorMainBG

        Image {
            id: bgImage
            width: 1024
            height: 640
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -256
            source: "qrc:/assets/images/background02.png"
            fillMode: Image.PreserveAspectFit
        }
    }

    DWelcome {
        anchors.centerIn: parent
        opacity: mainController.currentProject ? 0.0 : 1.0
    }

//    DActivityIndicator {
//        width: 256
//        height: 256
//        anchors.centerIn: parent
//        running: true
//    }

    MainGrabArea {
        id: mainGrabArea

        property bool xInit: false
        property bool yInit: false

        opacity: mainController.currentProject ? 1.0 : 0.0

        Component.onCompleted: {
//            projectPane.x = STYLE.defaultMargin;
//            projectPane.y = (mainRoot.height - projectPane.height) / 2;

//            propertiesPane.x = mainRoot.width - width - STYLE.defaultMargin;
//            propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;
        }

        onWidthChanged: {
            if (width > 0 && !xInit) {
                xInit = true;
                projectPane.x = STYLE.defaultMargin;
                propertiesPane.x = mainGrabArea.width - propertiesPane.width - STYLE.defaultMargin;

                //demoPane.x = (mainGrabArea.width - demoPane.width) / 2

                //demoContainer.x = (mainGrabArea.width - demoContainer.width) / 2

                demoViewContainer.x = (mainGrabArea.width - demoViewContainer.width) / 2
            }
        }

        onHeightChanged: {
            if (height > 0 && !yInit) {
                yInit = true;
                projectPane.y = (mainRoot.height - projectPane.height) / 2;
                propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;

                //demoPane.y = (mainRoot.height - demoPane.height) / 2;

                //demoContainer.y = (mainRoot.height - demoContainer.height) / 2;

                demoViewContainer.y = (mainRoot.height - demoViewContainer.height) / 2;
            }
        }

        onClicked: {
            // Hide Popups
            //mainPopupArea.hidePopups();
        }

//        onClicked: {
//            if (mouse.button === Qt.RightButton) {
//                // Hide Sub Popup
//                subPopup.hide();
//                // Show Popup
//                mainPopup.show(mouse.x, mouse.y);
//            } else {
//                // Hide Sub Popup
//                subPopup.hide();
//                // Hide Popup
//                mainPopup.hide();
//            }
//        }


        // Project Pane
        ProjectPane {
            id: projectPane
            hideToSide: hideToLeft

            enablePaneContent: false

            //hidden: true
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight

            //enableContent: false
            enablePaneContent: false

            //hidden: true
        }

        DViewContainer {
            id: demoViewContainer

            //hidden: true

//            DFormulaEditor {
//                id: formulaEditor
//                x: 50
//                y: 50
//                //anchors.centerIn: parent
//            }

//            DFlipable {
//                id: flipable

//                width: STYLE.spinnerWidth
//                height: STYLE.spinnerHeight

//                anchors.centerIn: parent
//                anchors.verticalCenterOffset: -50

//                front: Rectangle {
//                    width: STYLE.spinnerWidth
//                    height: STYLE.spinnerHeight
//                    color: "orange"
//                }

//                back: Rectangle {
//                    width: STYLE.spinnerWidth
//                    height: STYLE.spinnerHeight
//                    color: "purple"
//                }
//            }
        }

//        DPopupArea {
//            id: mainPopupArea
//            anchors.fill: parent
//            //visible: false
//        }


//        DPopup {
//            id: mainPopup

//            model: [
//                DPopupItemObject { text: "Item 1" },
//                DPopupItemObject { text: "Item Test 2" },
//                DPopupItemObject { text: "-" },
//                DPopupItemObject { text: "Item 3"; disabled: true },
//                DPopupItemObject { text: "-" },
//                DPopupItemObject { text: "Item 4"; subMenuItem: true; subMenu: [
//                    DPopupItemObject { text: "SubItem 1" },
//                    DPopupItemObject { text: "SubItem 2" },
//                    DPopupItemObject { text: "SubItem 3" },
//                    DPopupItemObject { text: "SubItem 4" }
//                ] },
//                DPopupItemObject { text: "Item 5" }
//            ]

//            onItemHovered: {
//                //console.log("mainPopup.onItemHovered - itemIndex: " + itemIndex + " - subMenuItem: " + subMenuItem);
//                // Check If Sub Item
//                if (!subMenuItem) {
//                    // Hide Sub Popup
//                    subPopup.hide();
//                }
//            }

//            onItemSelected: {
//                console.log("mainPopup.onItemSelected - itemIndex: " + itemIndex);
//            }

//            onSubMenuItemSelected: {
//                console.log("mainPopup.onSubMenuItemSelected - itemIndex: " + itemIndex);
//                // Set Sub Menu Popup Model
//                subPopup.model = mainPopup.model[itemIndex].subMenu;
//                // Show Sub-Popup
//                subPopup.show(mainPopup.x + mainPopup.width, mainPopup.y + itemPosY);
//            }
//        }

//        DPopup {
//            id: subPopup

//            onItemSelected: {
//                console.log("subPopup.onItemSelected - itemIndex: " + itemIndex);
//                // Hide Main Popup
//                mainPopup.hide();
//            }
//        }

//        DContainer {
//            id: demoContainer

//            width: 300
//            height: 256


//            Column {
//                width: parent.width
//                anchors.centerIn: parent
//                spacing: 8

//                DTextInput {
//                    anchors.horizontalCenter: parent.horizontalCenter
//                }

//                DSpinner {
//                    anchors.horizontalCenter: parent.horizontalCenter

//                    value: 0

//                    onValueDecreased: {
//                        value = newValue;
//                    }

//                    onValueIncreased: {
//                        value = newValue;
//                    }

//                    onTextUpdated: {
//                        value = newValue;
//                    }
//                }
//            }
//        }

//        DPane {
//            id: demoPane
//            width: 400
//            height: 540
//            title: "Demo"

//            DSection {
//                width: demoPane.contentWidth
//                title: "Section 1"

//                DButton {
//                    onClicked: checked = !checked;
//                }

//                DCheckBox {
//                    onClicked: checked = !checked;
//                }

//                DCheckBox {
//                    rightAligned: true
//                    onClicked: checked = !checked;
//                }

//                DSwitch {
//                    onClicked: checked = !checked;
//                }

//                DSwitch {
//                    rightAligned: true
//                    onClicked: checked = !checked;
//                }

//                DRadioButtonGroup {
//                    model: [
//                        DRadioButtonGroupItem { title: "Item 1" },
//                        DRadioButtonGroupItem { title: "Item 2" },
//                        DRadioButtonGroupItem { title: "Item 3" },
//                        DRadioButtonGroupItem { title: "Item 4" }
//                    ]

//                    onButtonSelected: {
//                        //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
//                        // Set Current Index
//                        currentIndex = buttonIndex;
//                    }
//                }

//                DRadioButtonGroup {
//                    rightAligned: true
//                    model: [
//                        DRadioButtonGroupItem { title: "Item 1" },
//                        DRadioButtonGroupItem { title: "Item 2" },
//                        DRadioButtonGroupItem { title: "Item 3" },
//                        DRadioButtonGroupItem { title: "Item 4" }
//                    ]

//                    onButtonSelected: {
//                        //console.log("onButtonSelected - buttonIndex: " + buttonIndex);
//                        // Set Current Index
//                        currentIndex = buttonIndex;
//                    }
//                }

//            }

//            DSection {
//                width: demoPane.contentWidth
//                title: "Section 2"
//            }

//            DSection {
//                width: demoPane.contentWidth
//                title: "Section 3"
//            }
//        }

    }
}

