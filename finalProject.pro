QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    astar.cpp \
#    astarcontroller.cpp \
    controller.cpp \
    gamestring.cpp \
    gameworld.cpp \
    graphicsscene.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    protagonistview.cpp \
    textscene.cpp

HEADERS += \
#    astar.h \
#    astarcontroller.h \
    controller.h \
    gamestring.h \
    gameworld.h \
    graphicsscene.h \
    mainwindow.h \
    node.h \
    protagonistview.h \
    scene.h \
    textscene.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images

win32: LIBS += -L$$PWD/../build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Release/release/ -lworld

INCLUDEPATH += $$PWD/../build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Release/release
DEPENDPATH += $$PWD/../build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Release/release
