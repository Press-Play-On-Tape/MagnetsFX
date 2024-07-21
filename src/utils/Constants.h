#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define DEBUG_PRINT    Serial.print
#define DEBUG_PRINTLN  Serial.println

#define DEBUG
#define DEBUG_FIXED_PUZZLE
#define _DEBUG_FIXED_RAND
#define _DEBUG_SOUND


namespace Music {

    constexpr uint24_t Songs[] = { Music::Song_MainTheme };

    constexpr uint24_t SFXs[] =  { Music::SFX_Death, 
                                   Music::SFX_Victory,
                                   Music::SFX_XPGain,
                                   Music::SFX_Three_Inc,
                                   Music::SFX_Three_Dec,
                                   Music::SFX_PlayerBlip,
                                   Music::SFX_EnemyBlip,
                                   Music::SFX_Explosion,
                                   Music::SFX_DoubleBeep,
                                   Music::SFX_DoubleBeepDown,
                                   Music::SFX_Bet1,
                                   Music::SFX_Bet2,
                                   Music::SFX_Bet3,
                                   Music::SFX_Bet4,
                                   Music::SFX_Bet5,
                                   Music::SFX_Bet6,
                                   Music::SFX_Click,
                                   Music::SFX_SmallBlind,
                                   Music::SFX_BigBlind,
                                };

}




namespace Constants {

    const int8_t Bounce[] PROGMEM = { -36, -30, -24, -16, -12, -6, 0, 4, 8, 12, 16, 20, 24, 28, 32, 28, 25, 22, 21, 21, 22, 25, 28, 32, 29, 27, 26, 26, 27, 28, 32, 30, 29, 30, 32, 31, 32 };

    constexpr uint8_t Title_Start_Action = 60;
    constexpr uint8_t Fill_MaxRand = 22;
    constexpr uint8_t Fill_Orient_1 = 10;
    constexpr uint8_t Fill_Orient_2 = 20;

};
