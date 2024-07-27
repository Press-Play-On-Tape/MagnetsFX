#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"

int16_t xTop = 0;
int16_t xBot = 0;
uint16_t titleAnimations = 0;

void title_Init() {

    gameState = GameState::Title_Play;
    frameCount = 0;
    titleAnimations = 0;

}

void title_Update() {

    frameCount++;
    titleAnimations = titleAnimations + 1;

    uint8_t justPressed = getJustPressedButtons();
    uint8_t pressed = getPressedButtons();

    switch (gameState) {
        
        case GameState::Title_Play:

            if (justPressed & DOWN_BUTTON) {
                titleAnimations = 300;
                gameState = GameState::Title_Options;
            }

            if (justPressed & A_BUTTON) {                
                titleAnimations = 300;
                gameState = GameState::Title_SelectSize;
            }

            break;
        
        case GameState::Title_Options:

            if (justPressed & UP_BUTTON) {
                titleAnimations = 300;
                gameState = GameState::Title_Play;
            }

            if (justPressed & A_BUTTON) {
                gameState = GameState::Title_Options_LEDS;
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
                gameState = GameState::Title_Play;
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

            case GameState::Title_Options_LEDS:
                
                if (justPressed & A_BUTTON) {

                    soundSettings.setLED(!soundSettings.getLED());

                }
                
                if (justPressed & B_BUTTON) {

                    gameState = GameState::Title_Options;
                    saveCookie(true);
                    
                }
                
                if (justPressed & DOWN_BUTTON) {

                    gameState++;

                }

                break;

            case GameState::Title_Options_Music:
                
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

                    gameState = GameState::Title_Options;
                    saveCookie(true);
                    
                }
                
                if (justPressed & DOWN_BUTTON) {

                    gameState++;

                }
                
                if (justPressed & UP_BUTTON) {

                    gameState--;

                }

                break;
                        
            case GameState::Title_Options_SFX:
                
                if (justPressed & A_BUTTON) {

                    soundSettings.setSFX(!soundSettings.getSFX());

                }
                
                if (justPressed & B_BUTTON) {

                    gameState = GameState::Title_Options;
                    saveCookie(true);

                }
                
                if (justPressed & UP_BUTTON) {

                    gameState--;

                }
                
                if (justPressed & DOWN_BUTTON) {

                    gameState++;

                }

                break;

            case GameState::Title_Options_Volume:
                
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

                    gameState = GameState::Title_Options;
                    saveCookie(true);

                }
                
                if (justPressed & UP_BUTTON) {

                    gameState = static_cast<GameState>(static_cast<uint8_t>(gameState) - 1);

                }

                break;

        #endif
        
    }

    if (titleAnimations < 300) titleAnimations++;

}

void title(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    if (frameCount % 4 == 0) {

        xBot = xBot - 1;        if (xBot == -204) xBot = 0;

    }

    if (frameCount % 5 == 0) {

        xTop = xTop + 1;        if (xTop == 204) xTop = 0;

    }

    if (a.needsUpdate()) title_Update();

    uint8_t currentPlane = a.currentPlane();

    switch (gameState) {
        
        case GameState::Title_Options_LEDS ... GameState::Title_Options_SFX:
            {
                renderCommon(currentPlane);

                if (soundSettings.getLED())      SpritesU::drawPlusMaskFX(88, 19, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getMusic())    SpritesU::drawPlusMaskFX(88, 29, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getSFX())      SpritesU::drawPlusMaskFX(88, 39, Images::Sound_Checkbox, currentPlane);

                uint8_t volume = (soundSettings.getMusic() || soundSettings.getSFX()) ? soundSettings.getVolume() : 0;

                if (soundSettings.getMusic() || soundSettings.getSFX()) {
                    SpritesU::drawPlusMaskFX(92, 46, Images::Sound_Volume_Grey, (soundSettings.getVolume() * 3) + currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(92, 46, Images::Sound_Volume_Grey, currentPlane);
                }

            }

            break;     
        
        case GameState::Title_Options_Volume:
            {
                renderCommon(currentPlane);

                if (soundSettings.getLED())      SpritesU::drawPlusMaskFX(88, 19, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getMusic())    SpritesU::drawPlusMaskFX(88, 29, Images::Sound_Checkbox, currentPlane);
                if (soundSettings.getSFX())      SpritesU::drawPlusMaskFX(88, 39, Images::Sound_Checkbox, currentPlane);

                uint8_t volume = (soundSettings.getMusic() || soundSettings.getSFX()) ? soundSettings.getVolume() : 0;

                if (soundSettings.getMusic() || soundSettings.getSFX()) {
                    SpritesU::drawPlusMaskFX(92, 46, Images::Sound_Volume_White, (soundSettings.getVolume() * 3) + currentPlane);
                }
                else {
                    SpritesU::drawPlusMaskFX(92, 46, Images::Sound_Volume_White, currentPlane);
                }

            }

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
    
    SpritesU::drawOverwriteFX(xTop, -3, Images::Wave_Top, currentPlane);
    SpritesU::drawOverwriteFX(xTop - 204, -3, Images::Wave_Top, currentPlane);
    SpritesU::drawOverwriteFX(xBot, 43, Images::Wave_Bot, currentPlane);
    SpritesU::drawOverwriteFX(xBot + 204, 43, Images::Wave_Bot, currentPlane);

}

void renderCommon(uint8_t currentPlane) {

    renderWaves(currentPlane);

    switch (gameState) {

        case GameState::Title_Start ... GameState::Title_Options:

            switch (titleAnimations) {

                case 0 ... Constants::Title_Start_Action - 1:

                    SpritesU::drawPlusMaskFX(4, 0, Images::Magnets, currentPlane);
                    break;

                case Constants::Title_Start_Action ... Constants::Title_Start_Action + 150:

                    SpritesU::drawPlusMaskFX(4, static_cast<int16_t>(-( static_cast<int16_t>(titleAnimations) - Constants::Title_Start_Action) / 4), Images::Magnets, currentPlane);
                    SpritesU::drawPlusMaskFX(80, 64 - static_cast<int16_t>((static_cast<int16_t>(titleAnimations) - Constants::Title_Start_Action) / 4), Images::Title, (3 * (static_cast<uint8_t>(gameState) - 6)) + currentPlane);
                    break;

                default:

                    SpritesU::drawPlusMaskFX(80, 27, Images::Title, (3 * (static_cast<uint8_t>(gameState) - 6)) + currentPlane);
                    break;

            }

            break;

        case  GameState::Title_Options_LEDS ... GameState::Title_Options_Volume:

            SpritesU::drawPlusMaskFX(80, 16, Images::Title, (3 * (static_cast<uint8_t>(gameState) - 6)) + currentPlane);
            break;

    }

}
