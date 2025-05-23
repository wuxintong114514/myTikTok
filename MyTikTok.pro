QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += multimedia
QT += multimediawidgets
QT += sql

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
    commentdialog.cpp \
    graphicsdanmakutextitem.cpp \
    graphicsthread.cpp \
    main.cpp \
    TikTok.cpp \
    uploaddialog.cpp

HEADERS += \
    TikTok.h \
    commentdialog.h \
    graphicsdanmakutextitem.h \
    graphicsthread.h \
    uploaddialog.h

FORMS += \
    TikTok.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    image/comment.png \
    image/fabu.png \
    image/fullscreen.png \
    image/like.png \
    image/luzhi.png \
    image/next.png \
    image/offdanmaku.png \
    image/offlike.png \
    image/ondanmaku.png \
    image/onlike.png \
    image/prev.png \
    image/search.png \
    image/tiktok.png \
    image/tubiao.png \
    image/tuijian.png \
    video/temp.mp4 \
    video/zyntm.mp4
