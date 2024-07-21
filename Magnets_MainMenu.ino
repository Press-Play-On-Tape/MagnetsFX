#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

int16_t xTop = 0;
int16_t xBot = 0;

void title_Init() {

    if (!cookie.hasSavedGame) {
        gameState = GameState::Title_OptPlay;
    }
    else {
        gameState = GameState::Title_OptResume;
    }

    game.resetFrameCount();

}

void title_Update() {

    game.incFrameCount();

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    switch (gameState) {

        #ifndef DEBUG        

            case GameState::Title_ShowInstructions:

                if (justPressed & B_BUTTON || justPressed & A_BUTTON) {

                    gameState = GameState::Title_OptCredits;

                }

                if (justPressed & DOWN_BUTTON || pressed & DOWN_BUTTON) {

                    if (instructions_Y > -284) {

                        instructions_Y--;

                    }

                }

                if (justPressed & UP_BUTTON || pressed & UP_BUTTON) {

                    if (instructions_Y < 0) {

                        instructions_Y++;

                    }

                }

                break;

        #endif
        
        case GameState::Title_OptPlay:

            if (justPressed & DOWN_BUTTON) {
                gameState = GameState::Title_OptSound;
            }

            if (justPressed & A_BUTTON) {
                
                cookie.hasSavedGame = false;
                saveCookie(true);
                game.setFrameCount(300);
                gameState = GameState::Title_SelectSize;

            }

            break;
        
        case GameState::Title_OptResume:

            if (justPressed & DOWN_BUTTON) {
                gameState = GameState::Title_OptPlay2;
            }

            if (justPressed & A_BUTTON) {
                gameState = game.getPrevGameState();
            }

            break;
          
        case GameState::Title_OptPlay2:

            if (justPressed & UP_BUTTON) {
                gameState = GameState::Title_OptResume;
            }

            if (justPressed & DOWN_BUTTON) {
                gameState = GameState::Title_OptSound2;
            }

            if (justPressed & A_BUTTON) {

                cookie.hasSavedGame = false;
                saveCookie(true);
                gameState = GameState::Title_SelectSize;

            }

            break;

        case GameState::Title_OptSound:

            if (justPressed & UP_BUTTON) {
                gameState = GameState::Title_OptPlay;
            }

            if (justPressed & DOWN_BUTTON) {
                gameState = GameState::Title_OptCredits;
            }

            if (justPressed & A_BUTTON) {

                gameState = GameState::Title_OptSound_Music;

            }

            break;

        case GameState::Title_OptSound2:

            if (justPressed & UP_BUTTON) {
                gameState = GameState::Title_OptPlay2;
            }

            if (justPressed & DOWN_BUTTON) {
                gameState = GameState::Title_OptCredits;
            }

            if (justPressed & A_BUTTON) {

                gameState = GameState::Title_OptSound_Music2;

            }

            break;
        
        case GameState::Title_OptCredits:

            if (justPressed & UP_BUTTON) {
                gameState = GameState::Title_OptSound;
            }

            if (justPressed & A_BUTTON) {
                gameState = GameState::Title_ShowInstructions;
                instructions_Y = 0;
            }

            break;

        case GameState::Title_SelectSize:

            if (justPressed & UP_BUTTON) {
                if (game.getGameSize() > GameSize::Small) {
                    game.setGameSize(game.getGameSize() - 1);
                }
            }

            if (justPressed & DOWN_BUTTON) {
                if (game.getGameSize() < GameSize::Large) {
                    game.setGameSize(game.getGameSize() + 1);
                }
            }

            if (justPressed & A_BUTTON) {

                gameState = GameState::Title_SelectHardness;

            }

            if (justPressed & B_BUTTON) {

                gameState = GameState::Title_OptPlay;

            }

            break;

        case GameState::Title_SelectHardness:

            if (justPressed & UP_BUTTON) {
                game.setGameHard(GameHard::Easy);
            }

            if (justPressed & DOWN_BUTTON) {
                game.setGameHard(GameHard::Hard);
            }

            if (justPressed & A_BUTTON) {
                gameState = GameState::Play_Init;
            }

            if (justPressed & B_BUTTON) {
                gameState = GameState::Title_SelectSize;
            }
            break;

        #ifndef DEBUG_SOUND

            case GameState::Title_OptSound_Music:
            case GameState::Title_OptSound_Music2:
                
                if (justPressed & A_BUTTON) {

                    soundSettings.setMusic(!soundSettings.getMusic());
                    if (soundSettings.getMusic()) {
                        playMusic();
                    }
                    else {
                        SynthU::stop();
                    }

                }
                
                if (justPressed & B_BUTTON) {

                    switch (gameState) {

                        case GameState::Title_OptSound_Music:
                            gameState = GameState::Title_OptSound;
                            break;

                        case GameState::Title_OptSound_Music2:
                            gameState = GameState::Title_OptSound2;
                            break;
                
                    }

                    saveCookie(true);
                    
                }
                
                if (justPressed & DOWN_BUTTON) {

                    gameState++;

                }

                break;
                        
            case GameState::Title_OptSound_SFX:
            case GameState::Title_OptSound_SFX2:
                
                if (justPressed & A_BUTTON) {

                    soundSettings.setSFX(!soundSettings.getSFX());

                }
                
                if (justPressed & B_BUTTON) {

                    switch (gameState) {

                        case GameState::Title_OptSound_SFX:
                            gameState = GameState::Title_OptSound;
                            break;

                        case GameState::Title_OptSound_SFX2:
                            gameState = GameState::Title_OptSound2;
                            break;
                
                    }

                    saveCookie(true);

                }
                
                if (justPressed & UP_BUTTON) {

                    gameState = static_cast<GameState>(static_cast<uint8_t>(gameState) - 1);

                }
                
                if (justPressed & DOWN_BUTTON) {

                    gameState++;

                }

                break;

            case GameState::Title_OptSound_Volume:
            case GameState::Title_OptSound_Volume2:
                
                if (justPressed & LEFT_BUTTON) {

                    if (soundSettings.getVolume() > 0) {

                        soundSettings.setVolume(soundSettings.getVolume() - 1);
                        SynthU::setVolume(soundSettings.getVolume() * 2);

                    }

                }
                
                if (justPressed & RIGHT_BUTTON) {

                    if (soundSettings.getVolume() < 7) {

                        soundSettings.setVolume(soundSettings.getVolume() + 1);
                        SynthU::setVolume(soundSettings.getVolume() * 2);

                    }

                }

                if (justPressed & B_BUTTON) {

                    switch (gameState) {

                        case GameState::Title_OptSound_Volume:
                            gameState = GameState::Title_OptSound;
                            break;

                        case GameState::Title_OptSound_Volume2:
                            gameState = GameState::Title_OptSound2;
                            break;
                
                    }

                    saveCookie(true);

                }
                
                if (justPressed & UP_BUTTON) {

                    gameState = static_cast<GameState>(static_cast<uint8_t>(gameState) - 1);

                }

                break;

        #endif
        
    }

    if (titleCounter < 72) titleCounter++;
      
}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (game.getFrameCount() % 4 == 0) {

        xBot = xBot - 1;        if (xBot == -204) xBot = 0;

    }

    if (game.getFrameCount() % 5 == 0) {

        xTop = xTop + 1;        if (xTop == 204) xTop = 0;

    }

    if (a.needsUpdate()) title_Update();

    uint8_t currentPlane = a.currentPlane();

    switch (gameState) {
        
        case GameState::Title_OptSound_Music ... GameState::Title_OptSound_SFX:
        case GameState::Title_OptSound_Music2 ... GameState::Title_OptSound_SFX2:
            {
                renderCommon(currentPlane);

                if (soundSettings.getMusic())    SpritesU::drawPlusMaskFX(88, 30, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getSFX())      SpritesU::drawPlusMaskFX(88, 40, Images::Sound_Checkbox, currentPlane);

                uint8_t volume = (soundSettings.getMusic() || soundSettings.getSFX()) ? soundSettings.getVolume() : 0;

                if (soundSettings.getMusic() || soundSettings.getSFX()) {
                    SpritesU::drawPlusMaskFX(92, 47, Images::Sound_Volume_Grey, (soundSettings.getVolume() * 3) + currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(92, 47, Images::Sound_Volume_Grey, currentPlane);
                }

            }

            break;     
        
        case GameState::Title_OptSound_Volume:
        case GameState::Title_OptSound_Volume2:
            {
                renderCommon(currentPlane);

                if (soundSettings.getMusic())    SpritesU::drawPlusMaskFX(88, 30, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getSFX())      SpritesU::drawPlusMaskFX(88, 40, Images::Sound_Checkbox, currentPlane);

                uint8_t volume = (soundSettings.getMusic() || soundSettings.getSFX()) ? soundSettings.getVolume() : 0;

                if (soundSettings.getMusic() || soundSettings.getSFX()) {
                    SpritesU::drawPlusMaskFX(92, 47, Images::Sound_Volume_White, (soundSettings.getVolume() * 3) + currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(92, 47, Images::Sound_Volume_White, currentPlane);
                }

            }

            break;    

        case GameState::Title_ShowInstructions: 
            // SpritesU::drawOverwriteFX(0, 0 + instructions_Y, Images::Instructions_01, currentPlane);
            // SpritesU::drawOverwriteFX(0, 0 + 180 + instructions_Y, Images::Instructions_02, currentPlane);

            // if (instructions_Y < 0 && game.getFrameCount() % 64 < 32) {

            //     SpritesU::drawPlusMaskFX(120, 0, Images::Instructions_Arrows, currentPlane);

            // }

            // if (instructions_Y > -284 && game.getFrameCount() % 64 < 32) {

            //     SpritesU::drawPlusMaskFX(120, 55, Images::Instructions_Arrows, 3 + currentPlane);

            // }

            break;

        case GameState::Title_SelectSize: 
            renderWaves(currentPlane);
            SpritesU::drawPlusMaskFX(80, 21, Images::Select, (game.getGameSize() * 3) + currentPlane);
            break;

        case GameState::Title_SelectHardness: 
            renderWaves(currentPlane);
            SpritesU::drawPlusMaskFX(80, 21, Images::Select, 9 + (game.getGameHard() * 3) + currentPlane);
            break;

        default:
            renderCommon(currentPlane);
            break;    

    }

}

void renderWaves(uint8_t currentPlane) {
    
    SpritesU::drawOverwriteFX(xTop, -1, Images::Wave_Top, currentPlane);
    SpritesU::drawOverwriteFX(xTop - 204, -1, Images::Wave_Top, currentPlane);
    SpritesU::drawOverwriteFX(xBot, 43, Images::Wave_Bot, currentPlane);
    SpritesU::drawOverwriteFX(xBot + 204, 43, Images::Wave_Bot, currentPlane);

}

void renderCommon(uint8_t currentPlane) {

    renderWaves(currentPlane);

    switch (game.getFrameCount()) {

        case 0 ... Constants::Title_Start_Action - 1:

            SpritesU::drawPlusMaskFX(4, 0, Images::Magnets, currentPlane);
            break;

        case Constants::Title_Start_Action ... Constants::Title_Start_Action + 150:

            SpritesU::drawPlusMaskFX(4, static_cast<int16_t>(-( static_cast<int16_t>(game.getFrameCount()) - Constants::Title_Start_Action) / 4), Images::Magnets, currentPlane);
            SpritesU::drawPlusMaskFX(80, 64 - static_cast<int16_t>((static_cast<int16_t>(game.getFrameCount()) - Constants::Title_Start_Action) / 4), Images::Title, (3 * (static_cast<uint8_t>(gameState) - 6)) + currentPlane);
            break;

        default:

            SpritesU::drawPlusMaskFX(80, 27, Images::Title, (3 * (static_cast<uint8_t>(gameState) - 6)) + currentPlane);
            break;

    }

}
