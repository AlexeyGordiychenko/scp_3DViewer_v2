QT       += core gui opengl openglwidgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fmax-errors=1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    s21_main.cc \
    thirdparty/gifanim/gifanim.cpp \
    view/command/s21_affinesavecmd.cc \
    view/command/s21_command.cc \
    view/command/s21_commandstack.cc \
    view/command/s21_projectiontypechangecmd.cc \
    view/command/s21_setbackgroundcolorcmd.cc \
    view/command/s21_setlinecolorcmd.cc \
    view/command/s21_setlinethicknesscmd.cc \
    view/command/s21_setlinetypecmd.cc \
    view/command/s21_setverticecolorcmd.cc \
    view/command/s21_setverticesizecmd.cc \
    view/command/s21_setverticetypecmd.cc \
    view/s21_view.cc \
    view/s21_gifcreator.cc \
    view/s21_glwidget.cc \
    model/s21_model.cc \
    controller/s21_controller.cc \
    utils/s21_affinedata.cc

HEADERS += \
    thirdparty/gifanim/gifanim.h \
    view/command/s21_affinesave.h \
    view/command/s21_command.h \
    view/command/s21_commandstack.h \
    view/command/s21_projectiontypechangecmd.h \
    view/command/s21_setbackgroundcolorcmd.h \
    view/command/s21_setlinecolorcmd.h \
    view/command/s21_setlinethicknesscmd.h \
    view/command/s21_setlinetypecmd.h \
    view/command/s21_setverticecolorcmd.h \
    view/command/s21_setverticesizecmd.h \
    view/command/s21_setverticetypecmd.h \
    view/s21_view.h \
    view/s21_gifcreator.h \
    view/s21_glwidget.h \
    model/s21_model.h \
    controller/s21_controller.h \
    utils/s21_affinedata.h \
    utils/s21_vertex3d.h \
    utils/s21_enums.h \
    utils/s21_observer.h

FORMS += \
    view/s21_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    thirdparty/gifanim/LICENSE \
    thirdparty/gifanim/README.md
