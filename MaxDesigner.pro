
# Target
TARGET              = MaxDesigner

# Template
TEMPLATE            = app

# Qt
QT                  += core gui widgets quickwidgets qml quick

# Sources
SOURCES             += src/main.cpp \
                    src/mainwindow.cpp \
                    src/settingscontroler.cpp \
                    src/preferencesdialog.cpp \
                    src/aboutdialog.cpp \
                    src/confirmdialog.cpp \
                    src/infodialog.cpp \
                    src/newprojectdialog.cpp \
                    src/projectpropertiesdialog.cpp \
                    src/componentpropertiesdialog.cpp \
                    src/qmlprojectparser.cpp \
                    src/qmleditorwindow.cpp \
                    src/basecomponentsmodel.cpp \
                    src/openfilesmodel.cpp \
                    src/componentslistmodel.cpp \
                    src/projectlistmodel.cpp \
                    src/viewslistmodel.cpp

# Headers
HEADERS             += src/mainwindow.h \
                    src/constants.h \
                    src/settingscontroler.h \
                    src/settingskeys.h \
                    src/defaultsettings.h \
                    src/preferencesdialog.h \
                    src/aboutdialog.h \
                    src/confirmdialog.h \
                    src/infodialog.h \
                    src/newprojectdialog.h \
                    src/projectpropertiesdialog.h \
                    src/componentpropertiesdialog.h \
                    src/qmlprojectparser.h \
                    src/qmleditorwindow.h \
                    src/basecomponentsmodel.h \
                    src/openfilesmodel.h \
                    src/componentslistmodel.h \
                    src/projectlistmodel.h \
                    src/viewslistmodel.h

# Forms
FORMS               += ui/mainwindow.ui \
                    ui/preferencesdialog.ui \
                    ui/aboutdialog.ui \
                    ui/confirmdialog.ui \
                    ui/infodialog.ui \
                    ui/newprojectdialog.ui \
                    ui/projectpropertiesdialog.ui \
                    ui/componentpropertiesdialog.ui \
                    ui/qmleditorwindow.ui

# Resources
RESOURCES           += maxdesigner.qrc

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

