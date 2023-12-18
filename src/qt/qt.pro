QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# https://github.com/dbzhang800/QtGifImage
include(QtGifImage-master/src/gifimage/qtgifimage.pri)

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    ../back/io_obj/read_obj.c \
    ../back/io_obj/write_obj.c \
    ../back/obj/obj.c \
    ../back/obj/transformation.c \
    ../back/gl_obj/gl_obj.c \
    settingsdialog.cpp

HEADERS += \
    defines.h \
    glview.h \
    mainwindow.h \
    ../back/io_obj/io_obj.h \
    ../back/obj/obj.h \
    ../back/obj/transformation.h \
    ../back/gl_obj/gl_obj.h \
    settingsdialog.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
