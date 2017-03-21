
# Target
TARGET              = MaxDesigner

# Template
TEMPLATE            = app

# Qt
QT                  += core gui widgets quickwidgets qml quick

# Sources
SOURCES             += src/main.cpp \
                    src/designerapplication.cpp \
                    src/qmlprojectparser.cpp \
                    src/qmlparser.cpp \
                    src/qmlgenerator.cpp \
                    src/designereventfilter.cpp \
                    src/designerimageprovider.cpp

# Model Sources
SOURCES             += src/settingscontroller.cpp \
                    src/minimizedcomponents.cpp \
                    src/propertiescontroller.cpp \
                    src/basecomponentsmodel.cpp \
                    src/openfilesmodel.cpp \
                    src/projectmodel.cpp \
                    src/componentinfo.cpp \
                    src/recentprojectsmodel.cpp \
                    src/projectitemmodel.cpp \
                    src/componentsmodel.cpp \
                    src/viewsmodel.cpp \
                    src/designerfilesortproxy.cpp \
                    src/componentcategorymodel.cpp \
                    src/componentstatesmodel.cpp \
                    src/componenttransitionsmodel.cpp \
                    src/componentanchorsmodel.cpp \
                    src/componentsignalsmodel.cpp \
                    src/componentpropertiesmodel.cpp

# Views/Dialog Sources
SOURCES             += src/mainwindow.cpp \
                    src/livewindow.cpp \
                    src/preferencesdialog.cpp \
                    src/aboutdialog.cpp \
                    src/confirmdialog.cpp \
                    src/infodialog.cpp \
                    src/projectpropertiesdialog.cpp \
                    src/createcomponentdialog.cpp \
                    src/createviewdialog.cpp \
                    src/qmleditorwindow.cpp \
                    src/resourceviewerdialog.cpp

# Headers
HEADERS             += src/designerapplication.h \
                    src/constants.h \
                    src/settingskeys.h \
                    src/defaultsettings.h \
                    src/qmlprojectparser.h \
                    src/qmlparser.h \
                    src/qmlgenerator.h \
                    src/propertiescontroller.h \
                    src/designereventfilter.h \
                    src/designerimageprovider.h \
                    src/designerfilesortproxy.h \
                    src/uiengineinterface.h

# Model Headers
HEADERS             += src/settingscontroller.h \
                    src/basecomponentsmodel.h \
                    src/openfilesmodel.h \
                    src/projectmodel.h \
                    src/componentinfo.h \
                    src/recentprojectsmodel.h \
                    src/projectitemmodel.h \
                    src/componentsmodel.h \
                    src/viewsmodel.h \
                    src/minimizedcomponents.h \
                    src/componentcategorymodel.h \
                    src/componentstatesmodel.h \
                    src/componenttransitionsmodel.h \
                    src/componentanchorsmodel.h \
                    src/componentsignalsmodel.h \
                    src/componentpropertiesmodel.h

# View/Dialog Headers
HEADERS             += src/mainwindow.h \
                    src/livewindow.h \
                    src/preferencesdialog.h \
                    src/aboutdialog.h \
                    src/confirmdialog.h \
                    src/infodialog.h \
                    src/projectpropertiesdialog.h \
                    src/createcomponentdialog.h \
                    src/createviewdialog.h \
                    src/qmleditorwindow.h \
                    src/resourceviewerdialog.h

# Forms
FORMS               += ui/mainwindow.ui \
                    ui/preferencesdialog.ui \
                    ui/aboutdialog.ui \
                    ui/confirmdialog.ui \
                    ui/infodialog.ui \
                    ui/qmleditorwindow.ui \
                    ui/projectpropertiesdialog.ui \
                    ui/createcomponentdialog.ui \
                    ui/createviewdialog.ui \
                    ui/resourceviewerdialog.ui \
                    ui/livewindow.ui

# Resources
RESOURCES           += maxdesigner.qrc \
                    maxdesignerimages.qrc

macx: {
# Icon
ICON                = assets/icons/designer.03.icns
} else {

}

# Other Files
OTHER_FILES         += README.md

# Output Dirs
OBJECTS_DIR         = ./objs
MOC_DIR             = ./objs
UI_DIR              = ./objs
RCC_DIR             = ./objs

