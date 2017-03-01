import QtQuick 2.0

import "Style.js" as STYLE

DPane {
    id: projectPaneRoot

    width: 360
    height: 600

    title: "Project"

    minWidth: 300
    minHeight: 200

    enablePaneContent: true

    setFocusOnResize: false

    topMouseAreaVisible: true

    state: stateShown

    DSection {
        id: baseComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Base Components"
        state: stateOpen

        Flow {
            width: contentWidth
            spacing: STYLE.defaultSpacing

            DComponentItem {
                //id: componentItemDemo
                title: "QtObject"
                onGrabbedChanged: {
                    // Bring Section To Top
                    baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    baseComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Item"
                onGrabbedChanged: {
                    // Bring Section To Top
                    baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    baseComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Rectangle"
                onGrabbedChanged: {
                    // Bring Section To Top
                    baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    baseComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Image"
                onGrabbedChanged: {
                    // Bring Section To Top
                    baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    baseComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "AnimatedImage"
                onGrabbedChanged: {
                    // Bring Section To Top
                    baseComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    baseComponentsSection.clipContent = !grabbed;
                }
            }



//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "Item"
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }

//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "Rectangle"
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }

//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "Image"
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }

//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "BorderImage"
//                    font.pixelSize: STYLE.fontSizeS
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }

//            DRectangle {
//                width: 84
//                height: 64
//                DText {
//                    width: parent.width
//                    anchors.centerIn: parent
//                    text: "AnimatedImage"
//                    font.pixelSize: STYLE.fontSizeXS
//                    horizontalAlignment: Text.AlignHCenter
//                }
//            }
        }
    }

    DSection {
        id: ownComponentsSection
        width: projectPaneRoot.contentWidth
        title: "Own Components"

        state: stateOpen

        Flow {
            width: contentWidth
            spacing: STYLE.defaultSpacing

            DComponentItem {
                title: "Label"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "FlatButton"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Button3D"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "CheckBox"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "TextInputField"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "RadioButtonGroup"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Slider"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "Spinner"
                onGrabbedChanged: {
                    // Bring Section To Top
                    ownComponentsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    ownComponentsSection.clipContent = !grabbed;
                }
            }

            // ...
        }
    }

    DSection {
        id: viewsSection
        width: projectPaneRoot.contentWidth
        title: "Views"

        Flow {
            width: contentWidth
            spacing: STYLE.defaultSpacing

            DComponentItem {
                title: "TopStatusBar"
                onGrabbedChanged: {
                    // Bring Section To Top
                    viewsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    viewsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "ApplicationBase"
                onGrabbedChanged: {
                    // Bring Section To Top
                    viewsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    viewsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "AppTile"
                onGrabbedChanged: {
                    // Bring Section To Top
                    viewsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    viewsSection.clipContent = !grabbed;
                }
            }

            DComponentItem {
                title: "ClimateBar"
                onGrabbedChanged: {
                    // Bring Section To Top
                    viewsSection.z = grabbed ? 0.1 : 0.0;
                    // Disable Content Clip
                    viewsSection.clipContent = !grabbed;
                }
            }

            // ...

        }
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
