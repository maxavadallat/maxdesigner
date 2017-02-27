import QtQuick 2.0

import "Style.js" as STYLE

DPane {
    id: projectPaneRoot

    width: 300
    height: 600

    title: "Project"

    minWidth: 300
    minHeight: 200

    state: stateShown

    DSection {
        width: projectPaneRoot.contentWidth
        title: "Base Components"

        state: stateOpen

        Flow {
            width: contentWidth
            spacing: STYLE.defaultSpacing
//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "QtObject"
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }

            DRectangle {
                width: 84
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "Item"
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            DRectangle {
                width: 84
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "Rectangle"
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            DRectangle {
                width: 84
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "Image"
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            DRectangle {
                width: 84
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "BorderImage"
                    font.pixelSize: STYLE.fontSizeS
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            DRectangle {
                width: 84
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "AnimatedImage"
                    font.pixelSize: STYLE.fontSizeXS
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    DSection {
        id: ownComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Own Components"

        state: stateOpen

        property int buttonWidth: 90

        Flow {
            width: contentWidth
            spacing: STYLE.defaultSpacing
            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "Label"
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "Button"
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "CheckBox"
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "TextInputField"
                    font.pixelSize: STYLE.fontSizeS
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    width: parent.width
                    anchors.centerIn: parent
                    text: "RadioButtonGroup"
                    font.pixelSize: STYLE.fontSizeXS
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "Slider"
                    //font.pixelSize: STYLE.fontSizeXS
                }
            }

            DRectangle {
                width: ownComponentsSection.buttonWidth
                height: 64
                DText {
                    anchors.centerIn: parent
                    text: "Spiner"
                    //font.pixelSize: STYLE.fontSizeXS
                }
            }
        }
    }

    DSection {
        width: projectPaneRoot.contentWidth
        title: "Views"

        // ...
    }

    DSection {
        width: projectPaneRoot.contentWidth
        title: "Files"

        // ...
    }

    DSection {
        width: projectPaneRoot.contentWidth
        title: "Open Documents"

        // ...
    }
}
