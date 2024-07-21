#include <ArduboyFX.h>  
#include "src/utils/ArduboyG.h"
#include "src/utils/Constants.h"
#include "src/utils/Enums.h"
#include "fxdata/fxdata.h"
#include "src/entities/Entities.h"
#include "src/utils/SpritesU.hpp"



uint8_t getJustPressedButtons() {

    a.pollButtons();

    return a.justPressedButtons();

}

uint8_t getPressedButtons() {

    return a.pressedButtons();

}

void saveCookie(bool enableLEDs) {

    #ifdef USE_LED
    if (enableLEDs) {
        #ifndef MICROCADE
            a.setRGBled(RED_LED, 32);
        #else
            a.setRGBledGreenOff();
            a.setRGBledBlueOff();
        #endif
    }
    #endif

    FX::saveGameState(cookie);

    #ifdef USE_LED
    if (enableLEDs) {
        #ifndef MICROCADE
            a.setRGBled(RED_LED, 0);
            a.setRGBled(GREEN_LED, 32);
        #else
            a.setRGBledRedOff();
            a.setRGBledGreenOn();
        #endif
    }
    #endif

}

void deactivateLEDs() {

    #ifdef USE_LED
        #ifndef MICROCADE
            a.setRGBled(0, 0, 0);
        #else
            a.setRGBledRedOff();
            a.setRGBledGreenOff();
            a.setRGBledBlueOff();
        #endif
    #endif

}

void printPuzzle() {

    #ifdef DEBUG

    DEBUG_PRINTLN(F("Puzzle ----------------------"));

    for (uint8_t y = 1; y < game.getHeight() + 1; y++) {

        for (uint8_t x = 1; x < game.getWidth() + 1; x++) {
        
            DEBUG_PRINT(game.puzzle[y][x]);
            DEBUG_PRINT(" ");

        }

        DEBUG_PRINTLN();
    }
    #endif

}

void printSolution() {

    #ifdef DEBUG

    DEBUG_PRINTLN(F("Solution ----------------------"));

    for (uint8_t y = 1; y < game.getHeight() + 1; y++) {

        for (uint8_t x = 1; x < game.getWidth() + 1; x++) {
        
            DEBUG_PRINT(game.solution[y][x]);
            DEBUG_PRINT(" ");

        }

        DEBUG_PRINTLN();
    }
    #endif

}