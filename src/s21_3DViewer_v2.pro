QT       += core gui opengl openglwidgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    s21_main.cc \
    thirdparty/gifanim/gifanim.cpp \
    view/command/s21_affinecmd.cpp \
    view/command/s21_affinedata.cpp \
    view/command/s21_command.cpp \
    view/command/s21_commandstack.cpp \
    view/command/s21_projectiontypechangecommand.cpp \
    view/command/s21_setBackgroundColorCommand.cpp \
    view/command/s21_setpolygoncolorcommand.cpp \
    view/command/s21_setpolygontypecmd.cpp \
    view/command/setpolygonthicknesscmd.cpp \
    view/command/setverticecolorcmd.cpp \
    view/command/setverticesizecmd.cpp \
    view/command/setverticetypecmd.cpp \
    view/s21_view.cc \
    view/s21_gifcreator.cc \
    view/s21_glwidget.cc \
    model/s21_model.cc \
    controller/s21_controller.cc

HEADERS += \
    thirdparty/gifanim/gifanim.h \
    view/command/s21_affinecmd.h \
    view/command/s21_affinedata.h \
    view/command/s21_command.h \
    view/command/s21_commandstack.h \
    view/command/s21_projectiontypechangecommand.h \
    view/command/s21_setBackgroundColorCommand.h \
    view/command/s21_setpolygoncolorcommand.h \
    view/command/s21_setpolygontypecmd.h \
    view/command/setpolygonthicknesscmd.h \
    view/command/setverticecolorcmd.h \
    view/command/setverticesizecmd.h \
    view/command/setverticetypecmd.h \
    view/s21_view.h \
    view/s21_gifcreator.h \
    view/s21_glwidget.h \
    model/s21_model.h \
    controller/s21_controller.h

FORMS += \
    view/s21_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    thirdparty/gifanim/LICENSE \
    thirdparty/gifanim/README.md
