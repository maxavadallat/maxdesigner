import QtQuick 2.0

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

    MainGrabArea {
        id: mainGrabArea

        property bool xInit: false
        property bool yInit: false

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

                demoContainer.x = (mainGrabArea.width - demoContainer.width) / 2
            }
        }

        onHeightChanged: {
            if (height > 0 && !yInit) {
                yInit = true;
                projectPane.y = (mainRoot.height - projectPane.height) / 2;
                propertiesPane.y = (mainRoot.height - propertiesPane.height) / 2;

                //demoPane.y = (mainRoot.height - demoPane.height) / 2;

                demoContainer.y = (mainRoot.height - demoContainer.height) / 2;
            }
        }

        // Project Pane
        ProjectPane {
            id: projectPane
//            x: STYLE.defaultMargin
//            y: (mainRoot.height - height) / 2

            hideToSide: hideToLeft
        }

        // Properties Pane
        PropertiesPane {
            id: propertiesPane
            hideToSide: hideToRight
        }

        DContainer {
            id: demoContainer

            width: 300
            height: 128


        }

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

//    // Main Container
//    Item {
//        id: mainContainer
//        anchors.fill: parent
//        //anchors.margins:
//    }
}

