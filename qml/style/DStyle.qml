pragma Singleton

import QtQuick 2.0

import "Designer.js" as DESIGNERSTYLE
import "Developer.js" as DEVELOPERSTYLE

QtObject {
    id: styleRoot

    // Style Configuration Map
    property var configMap: {
        "Designer" : 0,
        "Developer": 1
    }

    // Style Index
    property int styleIndex: configMap[settingsController.designerMode];

    // Config Array
    property var configArray: [ DESIGNERSTYLE, DEVELOPERSTYLE ]

    onStyleIndexChanged: {
        //console.log("Style.onStyleIndexChanged - styleIndex: " + styleIndex + " - mode: " + settingsController.designerMode);
    }

    // Main View Background Color
    readonly property string colorMainBG:                   configArray[styleIndex].colorMainBG             //"#FF171717"

    // Font Color Light
    readonly property string colorFontLight:                configArray[styleIndex].colorFontLight          //"#FF76ACB7"
    // Font Color Dark
    readonly property string colorFontDark:                 configArray[styleIndex].colorFontDark           //"#FF57787F"
    // Default Background Color
    readonly property string colorBG:                       configArray[styleIndex].colorBG                 //"#AA000000"
    // Default Border Color
    readonly property string colorBorder:                   configArray[styleIndex].colorBorder             //"#FF8ED5E1"
    // Default Unfocused Border Color
    readonly property string colorBorderNoFocus:            configArray[styleIndex].colorBorderNoFocus      //"#FF57787F"
    // Default Focused Border Color
    readonly property string colorBorderSelected:           configArray[styleIndex].colorBorderSelected     //"#FFEC6302"
    // Default Unfocused Transparent Border Color
    readonly property string colorBorderTransparent:        configArray[styleIndex].colorBorderTransparent  //"#7757787F"
    // Default Hover Ok
    readonly property string colorBorderHoverOK:            configArray[styleIndex].colorBorderHoverOK      // "yellow";
    // Default Hover Not Ok
    readonly property string colorBorderHoverNOK:           configArray[styleIndex].colorBorderHoverNOK     // "red";

    // Defaukt Shadow Color
    readonly property string colorShadow:                   configArray[styleIndex].colorShadow             //"#EE000000"
    // Default HighLight Color
    readonly property string colorHighLight:                configArray[styleIndex].colorHighLight          //"#7776ACB7"
    // Default Selected/Checked Color
    readonly property string colorSelected:                 configArray[styleIndex].colorSelected           //"#7757787F"

    // Default Editor Bacground Color
    readonly property string colorEditorBG:                 configArray[styleIndex].colorEditorBG           //"#FFFFFFFF"

    // Default Radio Button Mark Color
    readonly property string colorRadioButton:              configArray[styleIndex].colorRadioButton        //"#FF57787F"

    // Default Trace Color
    readonly property string colorTrace:                    configArray[styleIndex].colorTrace              //"#AA770077"

    // View Contaienr BG Gradient Colors
    readonly property string colorViewBG1:                  configArray[styleIndex].colorViewBG1            //"#11FFFFFF"
    readonly property string colorViewBG2:                  configArray[styleIndex].colorViewBG2            //"#11FFFFFF"

    // Default Selection Highlight Color
    readonly property string colorSelectedHighLight:        configArray[styleIndex].colorSelectedHighLight  //"#22FFFFFF"

    // Default Colors For Accept/OK
    readonly property string colorOK:                       configArray[styleIndex].colorOK                 //"#77007700"
    readonly property string colorOKHighLight:              configArray[styleIndex].colorOKHighLight        //"#AA00AA00"
    readonly property string colorOKSelected:               configArray[styleIndex].colorOKSelected         //"#7700AA00"

    // Default Colors for Decline/Cancel
    readonly property string colorCancel:                   configArray[styleIndex].colorCancel             //"#77770000"
    readonly property string colorCancelHighLight:          configArray[styleIndex].colorCancelHighLight    //"#AAAA0000"
    readonly property string colorCancelSelected:           configArray[styleIndex].colorCancelSelected     //"#77AA0000"

    // Default Radius
    readonly property int defaultRadius:                    4
    // Default Margin
    readonly property int defaultMargin:                    8
    // Default Spacing
    readonly property int defaultSpacing:                   8
    // Default Glow Radius
    readonly property int defaultGlowRadius:                24
    // Default Glow Samples
    readonly property int defaultGlowSamples:               16
    // Default Glow Spread
    readonly property real defaultGlowSpread:               0.6

    // Font Sizes
    readonly property int fontSizeXS:                       10
    readonly property int fontSizeS:                        12
    readonly property int fontSizeM:                        16
    readonly property int fontSizeL:                        20
    readonly property int fontSizeXL:                       28

    // Default Anim Duration
    readonly property int animDuration:                     200 * (settingsController.slowMotion ? 10 : 1)

    // Disabled Opacity
    readonly property real disabledOpacity:                 0.7

    // Pressed Scale
    readonly property real pressedScale:                    0.9

    // Default Scroll Indicator Width
    readonly property int scrollIndicatorWidth:             4

    // Default Radio Button Item Radius
    readonly property int radioButtonRadius:                10

    // Default Switch Width
    readonly property int switchWidth:                      42

    // Default List Item Height
    readonly property int listItemHeight:                   28

    // Default Header Height
    readonly property int headerHeight:                     28

    // Default Icon Size Small
    readonly property int iconWidthSmall:                   24
    readonly property int iconHeightSmall:                  24

    // Default Text Input Width
    readonly property int textInputWidth:                   240
    // Default Text Input Height
    readonly property int textInputHeight:                  32

    // Default Spinner Width
    readonly property int spinnerWidth:                     84
    // Default Spinner Height
    readonly property int spinnerHeight:                    32

    // Default Spinner Button Width
    readonly property int spinnerButtonWidth:               20
    // Default Spinner Button Height
    readonly property int spinnerButtonHeight:              spinnerButtonWidth

    // Default Timeout for Spinner Button Repeater
    readonly property int spinnerButtonTimer:               50

    // Default Hide Timer
    readonly property int defaultHideTimeout:               1500

    // Default Scroll Indicator Auto hide Timer Interval
    readonly property int scrollIndicatorTimeout:           defaultHideTimeout

    // Default Resize Area Size
    readonly property int resizeAreaSize:                   8

    // Default Popup Width
    readonly property int defaultPopupWidth:                128

    // Default Popup Item Height
    readonly property int popupItemHeight:                  listItemHeight

    // Default Popup Submenu Item Hover Timerout
    readonly property int popupItemHoverTimeout:            700

    // Default Flipable Flip Duration
    readonly property int flipDuration:                     700

    // Default Size Indicator Width
    readonly property int sizeIndicatorWidth:               96
    // Default Size Indicator Height
    readonly property int sizeIndicatorHeight:              24

    // Default Position Indicator Width
    readonly property int posIndicatorWidth:                sizeIndicatorWidth
    // Default Position Indicator Height
    readonly property int posIndicatorHeight:               sizeIndicatorHeight

    // Default Activity Indicator Width
    readonly property int activityIndicatorWidth:           56
    // Default Activity Indicator Height
    readonly property int activityIndicatorHeight:          56
    // Default Activity Indicator Line Width
    readonly property int activityIndicatorLineWidth:       8
    // Default Activity Indicator Interval
    readonly property int activityIndicatorInterval:        32

    // Live Launcher Width
    readonly property int liveLauncherWidth:                160
    readonly property int liveLauncherHeight:               160

    // ...

    readonly property string instrument101FontName:         "Instrument 101"
    readonly property string instrument103FontName:         "Instrument 103"

    Component.onCompleted: {
        //console.log("Style.onCompleted");
    }

    property FontLoader instrument101Font: FontLoader {
        source: "qrc:/assets/fonts/instrument101.ttf"
    }

    property FontLoader instrument103Font: FontLoader {
        source: "qrc:/assets/fonts/instrument103.ttf"
    }
}
