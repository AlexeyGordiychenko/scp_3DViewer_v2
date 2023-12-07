QT       += core gui opengl openglwidgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fmax-errors=1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    scp_main.cc \
    thirdparty/gifanim/gifanim.cpp \
    view/command/scp_affinesavecmd.cc \
    view/command/scp_command.cc \
    view/command/scp_commandstack.cc \
    view/command/scp_projectiontypechangecmd.cc \
    view/command/scp_setbackgroundcolorcmd.cc \
    view/command/scp_setlinecolorcmd.cc \
    view/command/scp_setlinethicknesscmd.cc \
    view/command/scp_setlinetypecmd.cc \
    view/command/scp_setverticecolorcmd.cc \
    view/command/scp_setverticesizecmd.cc \
    view/command/scp_setverticetypecmd.cc \
    view/scp_view.cc \
    view/scp_gifcreator.cc \
    view/scp_glwidget.cc \
    model/scp_model.cc \
    controller/scp_controller.cc \
    utils/scp_affinedata.cc

HEADERS += \
    thirdparty/gifanim/gifanim.h \
    view/command/scp_affinesavecmd.h \
    view/command/scp_command.h \
    view/command/scp_commandstack.h \
    view/command/scp_projectiontypechangecmd.h \
    view/command/scp_setbackgroundcolorcmd.h \
    view/command/scp_setlinecolorcmd.h \
    view/command/scp_setlinethicknesscmd.h \
    view/command/scp_setlinetypecmd.h \
    view/command/scp_setverticecolorcmd.h \
    view/command/scp_setverticesizecmd.h \
    view/command/scp_setverticetypecmd.h \
    view/scp_view.h \
    view/scp_gifcreator.h \
    view/scp_glwidget.h \
    model/scp_model.h \
    controller/scp_controller.h \
    utils/scp_affinedata.h \
    utils/scp_vertex3d.h \
    utils/scp_enums.h \
    utils/scp_observer.h

FORMS += \
    view/scp_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    thirdparty/gifanim/LICENSE \
    thirdparty/gifanim/README.md
