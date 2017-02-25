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
// Custom Component Name - Base Components Model
#define DEFAULT_MAIN_QML_COMPONENTS_BASECOMPONENTS_MODEL    "BaseComponentsModel"
// Custom Component Name - Components Model
#define DEFAULT_MAIN_QML_COMPONENTS_COMPONENTS_MODEL        "ComponentsModel"
// Custom Component Name - Component Info
#define DEFAULT_MAIN_QML_COMPONENTS_COMPONENT_INFO          "ComponentInfo"

// Main Controller Name
#define DEFAULT_MAIN_CONTROLLER_NAME                        "mainController"
// Settings Controller Name
#define DEFAULT_GLOBAL_SETTINGS_CONTROLLER                  "settingsController"
// Base Components List Model Name
#define DEFAULT_BASE_COMPONENTS_MODEL_NAME                  "baseComponentsModel"
// Project Tree Item Model Name
#define DEFAULT_PROJECT_TREE_MODEL_NAME                     "projectTreeModel"
// Components List Model Name
#define DEFAULT_COMPONENTS_MODEL_NAME                       "componentsModel"
// Views List Model Name
#define DEFAULT_VIEWS_MODEL_NAME                            "viewsModel"
// Open Files List Model Name
#define DEFAULT_OPEN_FILES_MODEL_NAME                       "openFilesModel"

// Open Project Model Name
#define DEFAULT_OPEN_RECENT_PROJECTS_MODEL_NAME             "recentProjectsModel"

// Current/Open Project Model Name
#define DEFAULT_OPEN_PROJECT_MODEL_NAME                     "projectModel"


// JSON File Extensions
#define DEFAULT_JSON_SUFFIX                                 "json"
#define DEFAULT_QML_PROJECT_SUFFIX                          "qmlproject"
#define DEFAULT_IMAGE_SUFFIXES                              "jpg jpeg png bmp gif tiff"
#define DEFAULT_QML_SUFFIX                                  "qml"
#define DEFAULT_JS_SUFFIX                                   "js"

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

// JSON Keys for Component Info
#define JSON_KEY_COMPONENT_NAME                             "compoenntName"
#define JSON_KEY_COMPONENT_TYPE                             "compoenntType"
#define JSON_KEY_COMPONENT_BASE                             "componentBase"
#define JSON_KEY_COMPONENT_OWN_PROPERTIES                   "componentOwnProperties"
#define JSON_KEY_COMPONENT_PROPERTIES                       "componentProperties"
#define JSON_KEY_COMPONENT_PARENT                           "componentParent"
#define JSON_KEY_COMPONENT_CHILDREN                         "componentChildren"




#endif // CONSTANTS_H
