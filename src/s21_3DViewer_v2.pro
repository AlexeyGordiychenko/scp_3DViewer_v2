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
    view/s21_view.cc \
    view/s21_gifcreator.cc \
    view/s21_glwidget.cc \
    model/s21_model.cc \
    controller/s21_controller.cc

HEADERS += \
    thirdparty/gifanim/gifanim.h \
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
