
# Target
TARGET              = MaxDesigner

# Template
TEMPLATE            = app

# Qt
QT                  += core gui widgets quickwidgets qml quick

# Sources
SOURCES             += src/main.cpp \
                    src/designerapplication.cpp \
                    src/mainwindow.cpp \
                    src/settingscontroler.cpp \
                    src/preferencesdialog.cpp \
                    src/aboutdialog.cpp \
                    src/confirmdialog.cpp \
                    src/infodialog.cpp \
                    src/projectpropertiesdialog.cpp \
                    src/qmlprojectparser.cpp \
                    src/qmleditorwindow.cpp \
                    src/basecomponentsmodel.cpp \
                    src/openfilesmodel.cpp \
                    src/projectmodel.cpp \
                    src/propertiesmodel.cpp \
                    src/componentinfo.cpp \
                    src/qmlparser.cpp \
                    src/qmlgenerator.cpp \
                    src/recentprojectsmodel.cpp \
                    src/projectitemmodel.cpp \
                    src/componentsmodel.cpp \
                    src/viewsmodel.cpp \
                    src/createcomponentdialog.cpp \
                    src/createviewdialog.cpp \
                    src/minimizedcomponents.cpp \
                    src/propertiescontroller.cpp \
                    src/designereventfilter.cpp

# Headers
HEADERS             += src/mainwindow.h \
                    src/designerapplication.h \
                    src/constants.h \
                    src/settingscontroler.h \
                    src/settingskeys.h \
                    src/defaultsettings.h \
                    src/preferencesdialog.h \
                    src/aboutdialog.h \
                    src/confirmdialog.h \
                    src/infodialog.h \
                    src/projectpropertiesdialog.h \
                    src/qmlprojectparser.h \
                    src/qmleditorwindow.h \
                    src/basecomponentsmodel.h \
                    src/openfilesmodel.h \
                    src/projectmodel.h \
                    src/propertiesmodel.h \
                    src/componentinfo.h \
                    src/qmlparser.h \
                    src/qmlgenerator.h \
                    src/recentprojectsmodel.h \
                    src/projectitemmodel.h \
                    src/componentsmodel.h \
                    src/viewsmodel.h \
                    src/createcomponentdialog.h \
                    src/createviewdialog.h \
                    src/minimizedcomponents.h \
                    src/propertiescontroller.h \
                    src/designereventfilter.h

# Forms
FORMS               += ui/mainwindow.ui \
                    ui/preferencesdialog.ui \
                    ui/aboutdialog.ui \
                    ui/confirmdialog.ui \
                    ui/infodialog.ui \
                    ui/qmleditorwindow.ui \
                    ui/projectpropertiesdialog.ui \
                    ui/createcomponentdialog.ui \
                    ui/createviewdialog.ui

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

