#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGlobal>

// Application Info
#define DEFAULT_APPLICATION_NAME                            "MaxDesigner"
#define DEFAULT_ORGANIZATION_NAME                           "MySoft"
#define DEFAULT_ORGANIZATION_DOMAIN                         "mysoft.com"

// Application Version
#define DEFAULT_APPLICATION_VERSION                         "0.1"

// Default Target Plugin IID Prefix
#define DEFAULT_TARGET_PLUGIN_IID_PREFIX                    "org.maxdesigner.targetplugin"
// Default Target Plugin Interface Name
#define DEFAULT_TARGET_PLUGIN_INTERFACE                     "org.maxdesigner.targetplugininterface"

#if defined(Q_OS_MACOS)
// Default Target Plugin Path
#define DEFAULT_TARGET_PLUGIN_PATH                          "%1/Library/MaxDesigner/targetplugins/%2"

#elif defined(Q_OS_LINUX)

#define DEFAULT_TARGET_PLUGIN_PATH                          "%1/.config/MaxDesigner/targetplugins/%2"

#else // Q_OS_UNIX

#define DEFAULT_TARGET_PLUGIN_PATH                          "%1/AppData/local/MaxDesigner/targetplugins/%2"

#endif

// Main Window QML Widget QML File
#define DEFAULT_MAIN_QMLFILE_URL                            "qrc:/qml/main.qml"
// Live Window QML Widget QML File
#define DEFAULT_LIVE_QMLFILE_URL                            "qrc:/qml/live/liveMain.qml"
// Flow Window QML Widget QML File
#define DEFAULT_FLOW_QMLFILE_URL                            "qrc:/qml/flow/flowMain.qml"
// Asset Browser Window QML Widget QML File
#define DEFAULT_ASSETBROWSER_QMLFILE_URL                    "qrc:/qml/assetbrowser/assetBrowserMain.qml"

// Main Window QML Widget Custom Components Import URI
#define DEFAULT_MAIN_QML_IMPORT_URI_ENGINE_COMPONENTS       "enginecomponents"

// Custom Component Name - Project Model
#define DEFAULT_MAIN_QML_COMPONENTS_PROJECT_MODEL           "ProjectModel"
// Custom Component Name - Component Info
#define DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO          "ComponentInfo"

// Custom Component Name - Base Components Model
#define DEFAULT_MAIN_QML_COMPONENTS_BASECOMPONENTS_MODEL    "BaseComponentsModel"
// Custom Component Name - Components Model
#define DEFAULT_MAIN_QML_COMPONENTS_COMPONENTS_MODEL        "ComponentsModel"
// Custom Compoents Name - Views List Model
#define DEFAULT_MAIN_QML_COMPONENTS_VIEWS_MODEL             "ViewsModel"
// Custom Compoents Name - Data Source List Model
#define DEFAULT_MAIN_QML_COMPONENTS_DATASOURCES_MODEL       "DataSourcesModel"

// File Sort Filter Proxy
#define DEFAULT_MAIN_QML_COMPONENTS_FILE_SORT_FILTER        "FileSortFilterProxy"

// Component Import Model
#define DEFAULT_MAIN_QML_COMPONENTS_IMPORTS_MODEL           "ComponentImportsModel"
// Component Own Properties Model
#define DEFAULT_MAIN_QML_COMPONENTS_OWN_PROPERTIES_MODEL    "ComponentOwnPropertiesModel"
// Component Properties Model
#define DEFAULT_MAIN_QML_COMPONENTS_PROPERTIES_MODEL        "ComponentPropertiesModel"
// Component Anchors Model
#define DEFAULT_MAIN_QML_COMPONENTS_ANCHORS_MODEL           "ComponentAnchorsModel"
// Component Signals Model
#define DEFAULT_MAIN_QML_COMPONENTS_SIGNALS_MODEL           "ComponentSignalsModel"
// Component Signal
#define DEFAULT_MAIN_QML_COMPONENT_SIGNAL                   "ComponentSignal"
// Component Slots Model
#define DEFAULT_MAIN_QML_COMPONENTS_SLOTS_MODEL             "ComponentSlotsModel"
// Component Slot
#define DEFAULT_MAIN_QML_COMPONENT_SLOT                     "ComponentSlot"
// Component Functions Model
#define DEFAULT_MAIN_QML_COMPONENTS_FUNCTIONS_MODEL         "ComponentFunctionsModel"
// Component Function
#define DEFAULT_MAIN_QML_COMPONENT_FUNCTION                 "ComponentFunction"
// Component States Model
#define DEFAULT_MAIN_QML_COMPONENTS_STATES_MODEL            "ComponentStatesModel"
// Component State
#define DEFAULT_MAIN_QML_COMPONENT_STATE                    "ComponentState"
// Component State
#define DEFAULT_MAIN_QML_COMPONENT_PROPERTY_CHANGE          "ComponentPropertyChange"
// Component Transitions Model
#define DEFAULT_MAIN_QML_COMPONENTS_TRANSITIONS_MODEL       "ComponentTransitionsModel"
// Component Transition
#define DEFAULT_MAIN_QML_COMPONENT_TRANSITION               "ComponentTransition"
// Animation Components Model
#define DEFAULT_MAIN_QML_ANIMATION_COMPONENTS_MODEL         "AnimationComponentsModel"


// Own Properties Filter Proxy
#define DEFAULT_MAIN_QML_COMPONENTS_OWN_COMPONENTS_FILTER   "ComponentOwnPropertiesFilter"
// Components Filter Proxy
#define DEFAULT_MAIN_QML_COMPONENTS_FILTER                  "ComponentsFilter"

// Main Controller Name
#define DEFAULT_MAIN_CONTROLLER_NAME                        "mainController"
// Live Window Controller Name
#define DEFAULT_LIVE_CONTROLLER_NAME                        "liveController"
// Asset Browser Controller
#define DEFAULT_ASSET_BROWSER_CONTROLLER_NAME               "assetBrowserController"
// Flow Window Controller Name
#define DEFAULT_FLOW_CONTROLLER_NAME                        "flowController"
// Settings Controller Name
#define DEFAULT_GLOBAL_SETTINGS_CONTROLLER                  "settingsController"
// Properties Controller Name
#define DEFAULT_PROPERTIES_CONTROLLER                       "propertiesController"

// Base Components Model
#define MODEL_NAME_BASE_COMPONENTS                          "baseComponentsModel"
// Components Model
#define MODEL_NAME_COMPONENTS                               "componentsModel"
// Views Model
#define MODEL_NAME_VIEWS                                    "viewsModel"
// Project Tree Item Model Name
#define MODEL_NAME_PROJECT_TREE                             "projectTreeModel"
// Assets Tree Item Model Name
#define MODEL_NAME_ASSETS_TREE                              "assetsTreeModel"
// Open Files List Model Name
#define MODEL_NAME_OPEN_FILES                               "openFilesModel"
// Open Files List Model Name
#define MODEL_NAME_MINIMIZED_COMPONENTS                     "minimizedComponentsModel"
// Open Project Model Name
#define MODEL_NAME_RECENT_PROJECTS                          "recentProjectsModel"
// Assets List Model Name
#define MODEL_NAME_ASSETS_LIST                              "assetsListModel"

// JSON File Extension
#define DEFAULT_JSON_SUFFIX                                 "json"
// IMAGE File Extensions
#define DEFAULT_IMAGE_SUFFIXES                              "jpg jpeg png bmp gif tiff"
// QML File Extension
#define DEFAULT_QML_SUFFIX                                  "qml"
// JS File Extension
#define DEFAULT_JS_SUFFIX                                   "js"
// File Name Mask
#define DEFAULT_FILE_NAME_MASK                              "."

// Default Component Child Info Map Name
#define DEFAULT_COMPONENT_CHILD_MAP                         "__childMap"

// Default Source Indent
#define DEFAULT_SOURCE_INDENT                               "    "

// Default Recent Open Projects List
#define DEFAULT_RECENTPROJECTLIST_FILE_NAME                 ".designerrecent.list"
// Max Recent Project File
#define DEFAULT_RECENTPROJECTS_MAX                          10
// Default Recent File List
#define DEFAULT_RECENTFILESLIST_FILE_NAME                   ".recentfiles.list"

// Default File URL Prefix
#define DEFAULT_FILE_URL_PREFIX                             "file://"

// Image Provider ID
#define DEFAULT_IMAGE_PROVIDER_ID                           "fileIcon"
#define DEFAULT_IMAGE_PROVIDER_PREFIX                       "image://fileIcon/"
// Default Icon File
#define DEFAULT_IMAGE_PROVIDER_ICON                         ":/assets/images/default_file.png"

// Default Live File Name Pattern
#define DEFAULT_LIVE_FILE_NAME_PATTERN                      "%1/%2_live.%3"
// Default Component File Name Pattern
#define DEFAULT_COMPONENT_FILE_NAME_PATTERN                 "%1/%2.%3"

// Default Dirs & File Names
#define DEFAULT_PROJECT_NAME                                "myproject"

#define DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME             "basecomponents"
#define DEFAULT_PROJECT_COMPONENTS_DIR_NAME                 "components"
#define DEFAULT_PROJECT_VIEWS_DIR_NAME                      "views"
#define DEFAULT_PROJECT_DATASOURCES_DIR_NAME                "datasources"

#define DEFAULT_PROJECT_ASSETS_DIR_NAME                     "assets"
#define DEFAULT_PROJECT_LIVE_TEMP_DIR_NAME                  "livetemp"
#define DEFAULT_PROJECT_LIVE_SOURCE_DIR_NAME                "livesource"

// JSON Keys for Project Info
#define JSON_KEY_PROJECT_NAME                               "projectName"
#define JSON_KEY_PROJECT_DIR                                "projectDir"
#define JSON_KEY_PROJECT_SCREEN_WIDTH                       "projectScreenWidth"
#define JSON_KEY_PROJECT_SCREEN_HEIGHT                      "projectScreenHeight"
#define JSON_KEY_PROJECT_DASHBOARD                          "projectDashboard"
#define JSON_KEY_PROJECT_ASSETS_DIR                         "projectAssetsDir"
#define JSON_KEY_PROJECT_BASECOMPONENTS_DIR                 "projectBaseComponentsDir"
#define JSON_KEY_PROJECT_COMPONENTS_DIR                     "projectComponentsDir"
#define JSON_KEY_PROJECT_VIEWS_DIR                          "projectViewsDir"
#define JSON_KEY_PROJECT_DATASOURCES_DIR                    "projectDataSourcesDir"
#define JSON_KEY_PROJECT_IMPORT_PATHS                       "projectImportPaths"
#define JSON_KEY_PROJECT_PLUGIN_PATHS                       "projectPluginPaths"

// Component Types
#define COMPONENT_TYPE_BASECOMPONENT                        "BaseComponent"
#define COMPONENT_TYPE_COMPONENT                            "Component"
#define COMPONENT_TYPE_VIEW                                 "View"
#define COMPONENT_TYPE_DATASOURCE                           "DataSource"

// Component Categories
#define COMPONENT_CATEGORY_VISUAL                           "Visual"
#define COMPONENT_CATEGORY_NONVISUAL                        "NonVisual"
#define COMPONENT_CATEGORY_LAYOUT                           "Layout"
#define COMPONENT_CATEGORY_CONTAINER                        "Container"
#define COMPONENT_CATEGORY_DELEGATE                         "Delegate"
#define COMPONENT_CATEGORY_ANIMATION                        "Animation"
#define COMPONENT_CATEGORY_BEHAVIOR                         "Behavior"
#define COMPONENT_CATEGORY_IMAGE                            "Image"
#define COMPONENT_CATEGORY_VIEW                             "View"

// Default Component Size
#define DEFAULT_COMPONENT_WIDTH                             320
#define DEFAULT_COMPONENT_HEIGHT                            200

// Default View Size
#define DEFAULT_VIEW_WIDTH                                  640
#define DEFAULT_VIEW_HEIGHT                                 480

// Default Animation Size
#define DEFAULT_ANIMATION_WIDTH                             168
#define DEFAULT_ANIMATION_HEIGHT                            168

// Initial Component JSON File Path
#define DEFAULT_INITIAL_COMPONENTS_JSON_FILE                ":/assets/json/builtincomponents.json"

// Filtered Properties
#define DEFAULT_FILTERED_PROPERTIES                         "id,objectName,x,y,z,width,height,state,states,transitions,children"

// Transition Types
#define JSON_VALUE_TRANSITION_NODE_TYPE_PARALLEL            "parallel"
#define JSON_VALUE_TRANSITION_NODE_TYPE_SQUENTIAL           "sequential"
#define JSON_VALUE_TRANSITION_NODE_TYPE_PAUSE               "pause"
#define JSON_VALUE_TRANSITION_NODE_TYPE_ACTION              "action"
#define JSON_VALUE_TRANSITION_NODE_TYPE_SCRIPT              "script"
#define JSON_VALUE_TRANSITION_NODE_TYPE_ANIMATION           "animation"

// JSON Keys for Component Info
#define JSON_KEY_COMPONENT_NAME                             "componentName"
#define JSON_KEY_COMPONENT_TYPE                             "componentType"
#define JSON_KEY_COMPONENT_CATEGORY                         "componentCategory"
#define JSON_KEY_COMPONENT_TAG                              "componentTag"
#define JSON_KEY_COMPONENT_BUILTIN                          "componentBuiltIn"
#define JSON_KEY_COMPONENT_USE_IMPLICIT_POSX                "componentImplicitPosX"
#define JSON_KEY_COMPONENT_USE_IMPLICIT_POSY                "componentImplicitPosY"
#define JSON_KEY_COMPONENT_USE_IMPLICIT_WIDTH               "componentImplicitWidth"
#define JSON_KEY_COMPONENT_USE_IMPLICIT_HEIGHT              "componentImplicitHeight"
#define JSON_KEY_COMPONENT_LOCKED                           "componentLocked"
#define JSON_KEY_COMPONENT_BASE                             "componentBase"
#define JSON_KEY_COMPONENT_OWN_PROPERTIES                   "componentOwnProperties"
#define JSON_KEY_COMPONENT_PROPERTIES                       "componentProperties"
#define JSON_KEY_COMPONENT_BEHAVIORS                        "componentBehaviors"
#define JSON_KEY_COMPONENT_PARENT                           "componentParent"
#define JSON_KEY_COMPONENT_CHILDREN                         "componentChildren"
#define JSON_KEY_COMPONENT_ANIMATIONS                       "componentAnimations"
#define JSON_KEY_COMPONENT_ANCHORS                          "componentAnchors"
#define JSON_KEY_COMPONENT_SIGNALS                          "componentSignals"
#define JSON_KEY_COMPONENT_SLOTS                            "componentSlots"
#define JSON_KEY_COMPONENT_FUNCTIONS                        "componentFunctions"
#define JSON_KEY_COMPONENT_STATES                           "componentStates"
#define JSON_KEY_COMPONENT_TRANSITIONS                      "componentTransitions"
#define JSON_KEY_COMPONENT_SOURCE                           "componentSource"
#define JSON_KEY_COMPONENT_IMPORTS                          "componentImports"

#define JSON_KEY_COMPONENT_SIGNAL_NAME                      "componentSignalName"
#define JSON_KEY_COMPONENT_SIGNAL_PARAMETERS                "componentSignalParameters"

#define JSON_KEY_COMPONENT_SLOT_NAME                        "componentSlotName"
#define JSON_KEY_COMPONENT_SLOT_SOURCE                      "componentSlotSource"

#define JSON_KEY_COMPONENT_FUNCTION_NAME                    "componentFunctionName"
#define JSON_KEY_COMPONENT_FUNCTION_PARAMETERS              "componentFunctionParameters"
#define JSON_KEY_COMPONENT_FUNCTION_SOURCE                  "componentFunctionSource"

#define JSON_KEY_COMPONENT_STATE_NAME                       "componentStateName"
#define JSON_KEY_COMPONENT_STATE_WHEN                       "componentStateWhen"
#define JSON_KEY_COMPONENT_STATE_PROPERTY_CHANGES           "componentStatePropertyChanges"

#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET           "componentPropertyChangeTarget"
#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY         "componentPropertyChangeProperty"
#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE            "componentPropertyChangeValue"

#define JSON_KEY_COMPONENT_TRANSITION_FROM                  "componentTransitionFrom"
#define JSON_KEY_COMPONENT_TRANSITION_TO                    "componentTransitionTo"

#define JSON_KEY_COMPONENT_TRANSITION_NODES                 "componentTransitionNodes"

// Read Only Property Type Prefix
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_READONLY            "readonly"
// Default Alias Property Type Prefix
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_DEFAULT             "default"

// Supported Value Types
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING              "string"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL                "bool"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_INT                 "int"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE              "double"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL                "real"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR                 "var"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT              "QtObject"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST                "list<QtObject>"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_ENUM                "enum"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_ALIAS               "alias"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_DEFAULT             "default"

// Default/Basic JSON Keys For Component Properties
#define JSON_KEY_COMPONENT_PROPERTY_ID                      "id"
#define JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME             "objectName"
#define JSON_KEY_COMPONENT_PROPERTY_X                       "x"
#define JSON_KEY_COMPONENT_PROPERTY_Y                       "y"
#define JSON_KEY_COMPONENT_PROPERTY_Z                       "z"
#define JSON_KEY_COMPONENT_PROPERTY_WIDTH                   "width"
#define JSON_KEY_COMPONENT_PROPERTY_HEIGHT                  "height"

#define JSON_KEY_COMPONENT_PROPERTY_STATE                   "state"

#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_FILL            "anchors.fill"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_CENTERIN        "anchors.centerIn"

#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFT            "anchors.left"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHT           "anchors.right"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOP             "anchors.top"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOM          "anchors.bottom"

#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER         "anchors.horizontalCenter"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER         "anchors.verticalCenter"

#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_MARGINS         "anchors.margins"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_LEFTMARGIN      "anchors.leftMargin"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_RIGHTMARGIN     "anchors.rightMargin"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_TOPMARGIN       "anchors.topMargin"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_BOTTOMMARGIN    "anchors.bottomMargin"

#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_HCENTER_OFFS    "anchors.horizontalCenterOffset"
#define JSON_KEY_COMPONENT_PROPERTY_ANCHORS_VCENTER_OFFS    "anchors.verticalCenterOffset"

#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TARGET       "target"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTY     "property"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_PROPERTIES   "properties"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_FROM         "from"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_TO           "to"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_VALUE        "value"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_DURATION     "duration"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_TYPE  "easing.type"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_EASING_CURVE "easing.bezierCurve"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_SCRIPT       "script"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITION_SCRIPTNAME   "scriptName"

// ...

#endif // CONSTANTS_H
