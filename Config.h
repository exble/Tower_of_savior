#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>

namespace Constants{
    inline constexpr int TickPerSec = 100;
    inline constexpr int PlayerMaxHP = 2000;

    inline constexpr int GameHeight = 960;
    inline constexpr int GameWidth = 540;

    inline constexpr int RuneTypeCount = 6;
    inline constexpr int RuneCountX = 6;
    inline constexpr int RuneCountY = 5;
    inline constexpr int RuneAreaHeight= 450;
    inline constexpr int RuneAreaWidth = 540;
    inline constexpr int RuneAreaX = 0;
    inline constexpr int RuneAreaY = GameHeight - RuneAreaHeight;

    inline constexpr int RuneHeight = 90;
    inline constexpr int RuneWidth = 90;

    inline constexpr int CharacterHeight = 90;
    inline constexpr int CharacterWidth = 90;

    inline constexpr int RuneGarvityAcceleration = 300 / TickPerSec;
    inline constexpr float RuneOpacity = 0.3;

    inline constexpr float DummyOpacity = 0.7;
    inline constexpr float DummyInactiveOpacity = 0;

    inline constexpr float InactiveOpacity = 0.5;

    //300ms
    inline constexpr int LinkingCD = 300;

    inline constexpr int BoardZValue = -100;

    inline constexpr int PlayerBarWidth = GameWidth;
    inline constexpr int PlayerBarHeight = 24;

    inline constexpr int SpiningTime = 10000;

    inline constexpr int AccumulateTime = 500;
    inline constexpr int AttackSepTime = 100;

    inline constexpr int CDTextBoxY = 200;
    inline constexpr int HealthBarHeight = 8;

}

// debug settings
#define DEBUG_REMOVE 0
#define DEBUG_MOUSE 0

#endif // CONFIG_H
