#-------------------------------------------------
#
# Project created by QtCreator 2017-01-31T21:04:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLabel_mouseEvents
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    matdisplay.cpp

HEADERS  += mainwindow.h \
    matdisplay.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\opencv\build_qt_release\install\include

LIBS += C:\opencv\build_qt_release\bin\libopencv_calib3d2413.dll \
        C:\opencv\build_qt_release\bin\libopencv_contrib2413.dll \
        C:\opencv\build_qt_release\bin\libopencv_core2413.dll \
        C:\opencv\build_qt_release\bin\libopencv_features2d2413.dll \
        C:\opencv\build_qt_release\bin\libopencv_highgui2413.dll \
        C:\opencv\build_qt_release\bin\libopencv_imgproc2413.dll \

