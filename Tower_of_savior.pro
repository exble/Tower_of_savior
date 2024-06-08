QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Character.cpp \
    CharacterSlot.cpp \
    CheckBoard.cpp \
    Enemy.cpp \
    Game.cpp \
    MouseListener.cpp \
    MouseMove.cpp \
    Object.cpp \
    PlayerStatusBar.cpp \
    Rune.cpp \
    RuneBoard.cpp \
    StatusBar.cpp \
    TickListener.cpp \
    TitleScreen.cpp \
    main.cpp

HEADERS += \
    Character.h \
    CharacterSlot.h \
    CheckBoard.h \
    Config.h \
    Enemy.h \
    Game.h \
    MouseListener.h \
    MouseMove.h \
    Object.h \
    PlayerStatusBar.h \
    Rune.h \
    RuneBoard.h \
    StatusBar.h \
    TickListener.h \
    TitleScreen.h \
    enum.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=


RESOURCES += \
    dataset.qrc
