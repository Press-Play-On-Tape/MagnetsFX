#pragma once

enum class MusicSong : uint8_t {
    MainTheme
};

enum class MusicSFX : uint8_t {
    SFX_Death,
    SFX_Victory,
    SFX_XPGain,
    SFX_Three_Inc,
    SFX_Three_Dec,
    SFX_PlayerBlip,
    SFX_EnemyBlip,
    SFX_Explosion,
    SFX_DoubleBeep,
    SFX_DoubleBeepDown,
    SFX_Bet1,
    SFX_Bet2,
    SFX_Bet3,
    SFX_Bet4,
    SFX_Bet5,
    SFX_Bet6,
    SFX_Click,
    SFX_SmallBlind,
    SFX_BigBlind,
};

enum class GameState : uint8_t {

    SplashScreen_Start,
        SplashScreen_00 = SplashScreen_Start,
        SplashScreen_01,
        SplashScreen_02,
        SplashScreen_03,
    SplashScreen_End,

    Title_Init,
    Title_Start,
        Title_OptPlay = Title_Start,
        Title_OptSound,
        Title_OptCredits,
        Title_OptResume,
        Title_OptPlay2,
        Title_OptSound2,
        Title_OptSound_Music,
        Title_OptSound_SFX,
        Title_OptSound_Volume,
        Title_OptSound_Music2,
        Title_OptSound_SFX2,
        Title_OptSound_Volume2,
        Title_ShowInstructions,
        Title_SelectSize,
        Title_SelectHardness,
    Title_End,

    Play_Init,
    Play_Start,
        Play = Play_Start,
        Play_Menu0,
        Play_Menu1,
        Play_Menu2,
        Play_Menu3,
        Play_Menu4,
    Play_End,
    
};

inline GameState &operator++(GameState &c) {
  c = static_cast<GameState>( static_cast<uint8_t>(c) + 1 );
  return c;
}

inline GameState operator++(GameState &c, int) {
  GameState result = c;
  ++c;
  return result;
}

inline GameState &operator--(GameState &c) {
  c = static_cast<GameState>( static_cast<uint8_t>(c) - 1 );
  return c;
}

inline GameState operator--(GameState &c, int) {
  GameState result = c;
  --c;
  return result;
}

enum GameSize : uint8_t { 
    Small,
    Medium,
    Large
};

enum GameHard : uint8_t { 
    Easy,
    Hard
};

enum Tiles : uint8_t {

    Horizontal_Blank_Start = 51,
    Horizontal_Blank_End = 52,
    Horizontal_MinusPlus_Start = 1,
    Horizontal_MinusPlus_End = 2,
    Horizontal_PlusMinus_Start = 4,
    Horizontal_PlusMinus_End = 3,
    Horizontal_Neutral_Start = 31,
    Horizontal_Neutral_End = 32,
    
    Vertical_Blank_Start = 61,
    Vertical_Blank_End = 62,
    Vertical_MinusPlus_Start = 11,
    Vertical_MinusPlus_End = 12,
    Vertical_PlusMinus_Start = 22,
    Vertical_PlusMinus_End = 21,
    Vertical_Neutral_Start = 41,
    Vertical_Neutral_End = 42,

};
