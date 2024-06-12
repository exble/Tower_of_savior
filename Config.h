#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <array>

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
    inline constexpr int AttackSepTime = 200;
    inline constexpr int BulletupdateCount = AttackSepTime / (1000 / TickPerSec);
    inline constexpr int BattleSwapDelay = 500;
    inline constexpr int Healingdelay = 500;

    inline constexpr int ButtonWidth = 300;
    inline constexpr int ButtonHeight = 80;

    inline constexpr int NotifyWindowWidth = GameWidth;
    inline constexpr int NotifyWindowHeight = GameHeight/3;

    inline constexpr int DamageFloatingTime = 1500;
    inline constexpr int DamageFloatingSpeed = 1;

    inline constexpr int MonsterAttackDelay = 600;

    inline constexpr int MonsterBackingTime = 600;
    inline constexpr float MonsterBackingSpeed = 0.5;
    inline constexpr int MonsterForwardTime = 100;
    inline constexpr float MonsterForwardSpeed = 3;

    inline constexpr int CDTextBoxY = 180;
    inline constexpr int HealthBarHeight = 8;
    inline constexpr double PI = 3.141592653589793238;

    // default to 1
    inline constexpr float Multiplier = 1;

}

// debug settings
#define DEBUG_REMOVE 0
#define DEBUG_MOUSE 0
#define DEBUG_SCREEN 0

#endif // CONFIG_H
