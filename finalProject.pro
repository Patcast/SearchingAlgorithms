QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    astar.cpp \
    astarcontroller.cpp \
    gameworld.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    protagonistview.cpp

HEADERS += \
    astar.h \
    astarcontroller.h \
    gameworld.h \
    mainwindow.h \
    node.h \
    protagonistview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sharableLib/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sharableLib/debug/ -lworld
else:unix: LIBS += -L$$PWD/sharableLib/ -lworld

INCLUDEPATH += $$PWD/sharableLib
DEPENDPATH += $$PWD/sharableLib

RESOURCES += \
    images

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../final/build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../final/build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/debug/ -lworld

INCLUDEPATH += $$PWD/../../final/build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/release
DEPENDPATH += $$PWD/../../final/build-world-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/release
