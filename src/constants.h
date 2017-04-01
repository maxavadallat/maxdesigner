#ifndef CONSTANTS_H
#define CONSTANTS_H


// Application Info
#define DEFAULT_APPLICATION_NAME                            "MaxDesigner"
#define DEFAULT_ORGANIZATION_NAME                           "MySoft"
#define DEFAULT_ORGANIZATION_DOMAIN                         "mysoft.com"

// Main Window QML Widget QML File
#define DEFAULT_MAIN_QMLFILE_URL                            "qrc:/qml/main.qml"

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

// File Sort Filter Proxy
#define DEFAULT_MAIN_QML_COMPONENTS_FILE_SORT_FILTER        "FileSortFilterProxy"

// Component Own Properties Model
#define DEFAULT_MAIN_QML_COMPONENTS_OWN_PROPERTIES_MODEL    "ComponentOwnPropertiesModel"
// Component Properties Model
#define DEFAULT_MAIN_QML_COMPONENTS_PROPERTIES_MODEL        "ComponentPropertiesModel"
// Component Anchors Model
#define DEFAULT_MAIN_QML_COMPONENTS_ANCHORS_MODEL           "ComponentAnchorsModel"
// Component Signals Model
#define DEFAULT_MAIN_QML_COMPONENTS_SIGNALS_MODEL           "ComponentSignalsModel"
// Component States Model
#define DEFAULT_MAIN_QML_COMPONENTS_STATES_MODEL            "ComponentStatesModel"
// Component Transitions Model
#define DEFAULT_MAIN_QML_COMPONENTS_TRANSITIONS_MODEL       "ComponentTransitionsModel"
// Component Functions Model
#define DEFAULT_MAIN_QML_COMPONENTS_FUNCTIONS_MODEL         "ComponentFunctionsModel"


// Own Properties Filter Proxy
#define DEFAULT_MAIN_QML_COMPONENTS_OWN_COMPONENTS_FILTER   "ComponentOwnPropertiesFilter"


// Main Controller Name
#define DEFAULT_MAIN_CONTROLLER_NAME                        "mainController"
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
// Open Files List Model Name
#define MODEL_NAME_OPEN_FILES                               "openFilesModel"
// Open Files List Model Name
#define MODEL_NAME_MINIMIZED_COMPONENTS                     "minimizedCompoenntsModel"
// Open Project Model Name
#define MODEL_NAME_RECENT_PROJECTS                          "recentProjectsModel"

// JSON File Extension
#define DEFAULT_JSON_SUFFIX                                 "json"
// AML File Extension
#define DEFAULT_QML_PROJECT_SUFFIX                          "qmlproject"
// IMAGE File Extensions
#define DEFAULT_IMAGE_SUFFIXES                              "jpg jpeg png bmp gif tiff"
// QML File Extension
#define DEFAULT_QML_SUFFIX                                  "qml"
// JS File Extension
#define DEFAULT_JS_SUFFIX                                   "js"
// File Name Mask
#define DEFAULT_FILE_NAME_MASK                              "."

// Default Recent Open Projects List
#define DEFAULT_RECENTPROJECTLIST_FILE_NAME                 ".designerrecent.list"
// Max Recent Project File
#define DEFAULT_RECENTPROJECTS_MAX                          10
// Default Recent File List
#define DEFAULT_RECENTFILESLIST_FILE_NAME                   ".recentfiles.list"

// Image Provider ID
#define DEFAULT_IMAGE_PROVIDER_ID                           "fileIcon"
#define DEFAULT_IMAGE_PROVIDER_PREFIX                       "image://fileIcon/"
// Default Icon File
#define DEFAULT_IMAGE_PROVIDER_ICON                         ":/assets/images/default_file.png"

// Default Dirs & File Names
#define DEFAULT_PROJECT_NAME                                "myproject"
#define DEFAULT_PROJECT_MAIN_QML_FILE_NAME                  "main.qml"
#define DEFAULT_PROJECT_QML_DIR_NAME                        "qml"
#define DEFAULT_PROJECT_JS_DIR_NAME                         "qml"
#define DEFAULT_PROJECT_IMAGES_DIR_NAME                     "qml"
#define DEFAULT_PROJECT_BASECOMPONENTS_DIR_NAME             "basecomponents"
#define DEFAULT_PROJECT_COMPONENTS_DIR_NAME                 "components"
#define DEFAULT_PROJECT_VIEWS_DIR_NAME                      "views"

// JSON Keys for Project Info
#define JSON_KEY_PROJECT_NAME                               "projectName"
#define JSON_KEY_PROJECT_DIR                                "projectDir"
#define JSON_KEY_PROJECT_MAIN_QML                           "projectMainQML"
#define JSON_KEY_PROJECT_QML_DIR                            "projectQMLDir"
#define JSON_KEY_PROJECT_JS_DIR                             "projectJSDir"
#define JSON_KEY_PROJECT_IMAGES_DIR                         "projectImagesDir"
#define JSON_KEY_PROJECT_BASECOMPONENTS_DIR                 "projectBaseComponentsDir"
#define JSON_KEY_PROJECT_COMPONENTS_DIR                     "projectComponentsDir"
#define JSON_KEY_PROJECT_VIEWS_DIR                          "projectViewsDir"
#define JSON_KEY_PROJECT_IMPORT_PATHS                       "projectImportPaths"
#define JSON_KEY_PROJECT_PLUGIN_PATHS                       "projectPluginPaths"

// Component Types
#define COMPONENT_TYPE_BASECOMPONENT                        "BaseComponent"
#define COMPONENT_TYPE_COMPONENT                            "Component"
#define COMPONENT_TYPE_VIEW                                 "View"

// Component Categories
#define COMPONENT_CATEGORY_VISUAL                           "Visual"
#define COMPONENT_CATEGORY_NONVISUAL                        "NonVisual"
#define COMPONENT_CATEGORY_LAYOUT                           "Layout"
#define COMPONENT_CATEGORY_CONTAINER                        "Container"
#define COMPONENT_CATEGORY_DELEGATE                         "Delegate"

#define DEFAULT_COMPONENT_WIDTH                             320
#define DEFAULT_COMPONENT_HEIGHT                            200

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
#define JSON_KEY_COMPONENT_BUILTIN                          "componentBuiltIn"
#define JSON_KEY_COMPONENT_BASE                             "componentBase"
#define JSON_KEY_COMPONENT_OWN_PROPERTIES                   "componentOwnProperties"
#define JSON_KEY_COMPONENT_PROPERTIES                       "componentProperties"
#define JSON_KEY_COMPONENT_PARENT                           "componentParent"
#define JSON_KEY_COMPONENT_CHILDREN                         "componentChildren"
#define JSON_KEY_COMPONENT_ANCHORS                          "componentAnchors"
#define JSON_KEY_COMPONENT_SIGNALS                          "componentSignals"
#define JSON_KEY_COMPONENT_STATES                           "componentStates"
#define JSON_KEY_COMPONENT_TRANSITIONS                      "componentTransitions"
#define JSON_KEY_COMPONENT_SOURCE                           "componentSource"
#define JSON_KEY_COMPONENT_IMPORTS                          "componentImports"

#define JSON_KEY_COMPONENT_SIGNAL_NAME                      "componentSignalName"
#define JSON_KEY_COMPONENT_SIGNAL_PARAMETERS                "componentSignalParameters"

#define JSON_KEY_COMPONENT_STATE_NAME                       "componentStateName"
#define JSON_KEY_COMPONENT_STATE_WHEN                       "componentStateWhen"
#define JSON_KEY_COMPONENT_STATE_PROPERTY_CHANGES           "componentStatePropertyChanges"

#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_TARGET           "componentPropertyChangeTarget"
#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_PROPERTY         "componentPropertyChangeProperty"
#define JSON_KEY_COMPONENT_PROPERTY_CHANGE_VALUE            "componentPropertyChangeValue"

#define JSON_KEY_COMPONENT_TRANSITION_FROM                  "componentTransitionFrom"
#define JSON_KEY_COMPONENT_TRANSITION_TO                    "componentTransitionTo"

#define JSON_KEY_COMPONENT_TRANSITION_ROOT                  "componentTransitionRoot"

#define JSON_KEY_COMPONENT_TRANSITION_NODE_TYPE             "componentTransitionNodeType"
#define JSON_KEY_COMPONENT_TRANSITION_NODE_CHILDREN         "componentTransitionNodeChildren"

#define JSON_KEY_COMPONENT_TRANSITION_PAUSE_DURATION        "componentTransitionPauseDuration"

#define JSON_KEY_COMPONENT_TRANSITION_PACTION_TARGET        "componentTransitionPActionTarget"
#define JSON_KEY_COMPONENT_TRANSITION_PACTION_PROPERTY      "componentTransitionPActionProperty"
#define JSON_KEY_COMPONENT_TRANSITION_PACTION_VALUE         "componentTransitionPActionValue"

#define JSON_KEY_COMPONENT_TRANSITION_SACTION_SCRIPT        "componentTransitionSActionScript"

#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_TARGET     "componentTransitionPAnimationTarget"
#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_PROPERTY   "componentTransitionPAnimationProperty"
#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_VALUEFROM  "componentTransitionPAnimationValueFrom"
#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_VALUETO    "componentTransitionPAnimationValueTo"
#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_DURATION   "componentTransitionPAnimationDuration"
#define JSON_KEY_COMPONENT_TRANSITION_PANIMATION_ETYPE      "componentTransitionPAnimationEType"


#define JSON_VALUE_PROPERTY_TYPE_PREFIX_STRING              "string"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_BOOL                "bool"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_INT                 "int"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_DOUBLE              "double"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_REAL                "real"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_VAR                 "var"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_OBJECT              "QtObject"
#define JSON_VALUE_PROPERTY_TYPE_PREFIX_LIST                "list<QtObject>"


// Default/Basec JSON Keys For Component Properties
#define JSON_KEY_COMPONENT_PROPERTY_ID                      "id"
#define JSON_KEY_COMPONENT_PROPERTY_OBJECT_NAME             "objectName"
#define JSON_KEY_COMPONENT_PROPERTY_X                       "x"
#define JSON_KEY_COMPONENT_PROPERTY_Y                       "y"
#define JSON_KEY_COMPONENT_PROPERTY_Z                       "z"
#define JSON_KEY_COMPONENT_PROPERTY_WIDTH                   "width"
#define JSON_KEY_COMPONENT_PROPERTY_HEIGHT                  "height"

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

#define JSON_KEY_COMPONENT_PROPERTY_STATE                   "state"

#define JSON_KEY_COMPONENT_PROPERTY_OPACITY                 "opacity"
#define JSON_KEY_COMPONENT_PROPERTY_VISIBLE                 "visible"

#define JSON_KEY_COMPONENT_PROPERTY_SCALE                   "scale"
#define JSON_KEY_COMPONENT_PROPERTY_ROTATION                "rotation"

#define JSON_KEY_COMPONENT_PROPERTY_FOCUS                   "focus"
#define JSON_KEY_COMPONENT_PROPERTY_CLIP                    "clip"

#define JSON_KEY_COMPONENT_PROPERTY_ENABLED                 "enabled"

#define JSON_KEY_COMPONENT_PROPERTY_STATES                  "states"
#define JSON_KEY_COMPONENT_PROPERTY_TRANSITIONS             "transitions"

/*
#define JSON_KEY_COMPONENT_PROPERTY_RADIUS                  "radius"
#define JSON_KEY_COMPONENT_PROPERTY_SPACING                 "spacing"
#define JSON_KEY_COMPONENT_PROPERTY_COLOR                   "color"
#define JSON_KEY_COMPONENT_PROPERTY_BORDER_COLOR            "border.color"
#define JSON_KEY_COMPONENT_PROPERTY_BORDER_WIDTH            "border.width"

#define JSON_KEY_COMPONENT_PROPERTY_FONT_COLOR              "font.color"
#define JSON_KEY_COMPONENT_PROPERTY_FONT_PIXELSIZE          "font.pixelSize"

#define JSON_KEY_COMPONENT_PROPERTY_BORDER_LEFT             "border.left"
#define JSON_KEY_COMPONENT_PROPERTY_BORDER_RIGHT            "border.right"
#define JSON_KEY_COMPONENT_PROPERTY_BORDER_TOP              "border.top"
#define JSON_KEY_COMPONENT_PROPERTY_BORDER_BOTTOM           "border.bottom"

#define JSON_KEY_COMPONENT_PROPERTY_TEXT                    "text"
#define JSON_KEY_COMPONENT_PROPERTY_TITLE                   "title"

#define JSON_KEY_COMPONENT_PROPERTY_HORIZONTAL_ALIGNMENT    "horizontalAlignment"
#define JSON_KEY_COMPONENT_PROPERTY_VERTICAL_ALIGNMENT      "verticalAlignment"
*/

// ...

#endif // CONSTANTS_H
