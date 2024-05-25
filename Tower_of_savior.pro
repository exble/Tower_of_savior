QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game.cpp \
    TitleScreen.cpp \
    main.cpp

HEADERS += \
    Game.h \
    TitleScreen.h \
    param.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dataset/dataset/bullet.png \
    dataset/dataset/character/ID1.png \
    dataset/dataset/character/ID2.png \
    dataset/dataset/character/ID3.png \
    dataset/dataset/character/ID4.png \
    dataset/dataset/character/ID5.png \
    dataset/dataset/enemy/100n.png \
    dataset/dataset/enemy/102n.png \
    dataset/dataset/enemy/104n.png \
    dataset/dataset/enemy/180n.png \
    dataset/dataset/enemy/267n.png \
    dataset/dataset/enemy/96n.png \
    dataset/dataset/enemy/98n.png \
    dataset/dataset/runestone/burnibg_earth_stone.png \
    dataset/dataset/runestone/burning_dark_stone.png \
    dataset/dataset/runestone/burning_fire_stone.png \
    dataset/dataset/runestone/burning_heart_stone.png \
    dataset/dataset/runestone/burning_light_stone.png \
    dataset/dataset/runestone/burning_water_stone.png \
    dataset/dataset/runestone/dark_stone.png \
    dataset/dataset/runestone/earth_stone.png \
    dataset/dataset/runestone/fire_stone.png \
    dataset/dataset/runestone/heart_stone.png \
    dataset/dataset/runestone/light_stone.png \
    dataset/dataset/runestone/water_stone.png \
    dataset/dataset/runestone/weathered_dark_stone.png \
    dataset/dataset/runestone/weathered_earth_stone.png \
    dataset/dataset/runestone/weathered_fire_stone.png \
    dataset/dataset/runestone/weathered_heart_stone.png \
    dataset/dataset/runestone/weathered_light_stone.png \
    dataset/dataset/runestone/weathered_water_stone.png
