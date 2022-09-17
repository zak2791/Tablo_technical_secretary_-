QMAKE_CXXFLAGS_RELEASE -= -O3
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O0

RC_ICONS = appico.ico

QT       += core gui network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JSTools.cpp \
    camera.cpp \
    cameraconnection.cpp \
    cameraviewer.cpp \
    category.cpp \
    fam_reg.cpp \
    lcdstopwatch.cpp \
    lcdtimer.cpp \
    main.cpp \
    narusheniya_pravil.cpp \
    narusheniya_vyhod.cpp \
    pcscreen.cpp \
    player.cpp \
    playerviewer.cpp \
    plus.cpp \
    protocolwindow.cpp \
    rate.cpp \
    tvscreen.cpp

HEADERS += \
    JSTools.h \
    camera.h \
    cameraconnection.h \
    cameraviewer.h \
    category.h \
    fam_reg.h \
    lcdstopwatch.h \
    lcdtimer.h \
    narusheniya_pravil.h \
    narusheniya_vyhod.h \
    pcscreen.h \
    player.h \
    playerviewer.h \
    plus.h \
    protocolwindow.h \
    rate.h \
    tvscreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    FormView.ui \
    frmTime.ui

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lavformat

INCLUDEPATH += $$PWD/ffmpeg/include
DEPENDPATH += $$PWD/ffmpeg/include

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lavutil

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lavcodec

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lavdevice

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lavfilter

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lswscale

win32: LIBS += -L$$PWD/ffmpeg/lib/ -lswresample

RESOURCES += \
    res.qrc
