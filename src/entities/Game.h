
#pragma once

#include <ArduboyFX.h>  
#include "../utils/Constants.h"
#include "../utils/Enums.h"

struct Game {

    public:

        uint8_t puzzle[9][10];
        uint8_t solution[9][10];
        
    private:

        uint8_t widths[3] = { 6, 8, 10 };
        uint8_t heights[3] = { 5, 7, 9 };
        uint8_t spacings[3] = { 9, 6, 6 };

        uint16_t frameCount = 0;
        uint8_t x = 1;
        uint8_t y = 1;
        GameSize gameSize = GameSize::Small;
        GameHard gameHard = GameHard::Easy;
        GameState prevGameState = GameState::SplashScreen_Start;

    public:

        uint16_t getFrameCount()                        { return this->frameCount; }
        uint8_t getWidth()                              { return this->widths[this->gameSize]; }
        uint8_t getHeight()                             { return this->heights[this->gameSize]; }
        uint8_t getX()                                  { return this->x; }
        uint8_t getY()                                  { return this->y; }
        uint8_t getSpacing()                            { return this->spacings[this->gameSize]; }
        GameSize getGameSize()                          { return this->gameSize; }
        GameHard getGameHard()                          { return this->gameHard; }
        GameState getPrevGameState()                    { return this->prevGameState; }

        void setFrameCount(uint16_t val)                { this->frameCount = val; }
        void setX(uint8_t val)                          { this->x = val; }
        void setY(uint8_t val)                          { this->y = val; }
        void setGameSize(GameSize val)                  { this->gameSize = val; }
        void setGameHard(GameHard val)                  { this->gameHard = val; }
        void setPrevGameState(GameState val)            { this->prevGameState = val; }

        void incFrameCount() {

            this->frameCount++;

        }

        void resetFrameCount() {

            this->frameCount = 0;
            
        }

        void setup() {

        }

        void loadPuzzle() {

            this->setGameSize(GameSize::Medium);


            // Retrieve template count ..

            FX::seekData(Constants::temp_Count);
            uint8_t levelCount = FX::readPendingUInt8();
            FX::readEnd();

            #ifndef DEBUG_FIXED_PUZZLE

                uint8_t randomLevel = random(levelCount) + (this->getGameSize() * levelCount);

                #ifdef DEBUG
                    DEBUG_PRINT("Level :");
                    DEBUG_PRINT(randomLevel + 1);
                    DEBUG_PRINT(" of ");
                    DEBUG_PRINTLN(levelCount * 2);
                #endif

            #else
                
                uint8_t randomLevel = (this->getGameSize() * levelCount);

                #ifdef DEBUG
                    DEBUG_PRINT("Level :");
                    DEBUG_PRINT(randomLevel + 1);
                    DEBUG_PRINT(" of ");
                    DEBUG_PRINTLN(levelCount * 2);
                #endif

            #endif

            uint24_t startPos = FX::readIndexedUInt24(Constants::temp_Levels, randomLevel);

            for (uint8_t y = 0; y < this->getHeight(); y++) {

                FX::seekData(startPos);
                FX::readBytes((uint8_t*)&puzzle[y + 1][1], this->getWidth());
                FX::readEnd();

                startPos = startPos + this->getWidth();

            }

            #ifdef DEBUG
                printPuzzle();
            #endif
           
            #ifndef DEBUG_FIXED_PUZZLE

                if (random(2) == 0) {
                    #ifdef DEBUG
                    DEBUG_PRINTLN("flipHorizontal()");
                    #endif
                    flipHorizontal();
                }

                if (random(2) == 0) {
                    #ifdef DEBUG
                    DEBUG_PRINTLN("flipVertical()");
                    #endif
                    flipVertical();
                }

                #ifdef DEBUG
                    printPuzzle();
                #endif
            
            #endif

            this->fillPuzzle();
            this->printPuzzle();

            this->updateNumbers();

        }


        void updateNumbers() {

            // Rows

            for (uint8_t y = 1; y < this->getHeight() + 1; y++) {

                uint8_t minus = 0;
                uint8_t plus = 0;
                
                for (uint8_t x = 1; x < this->getWidth() + 1; x++) {

                    if (this->isPlus(x, y)) plus++;
                    if (this->isMinus(x, y)) minus++;

                }

                this->puzzle[y][0] = plus;
                this->puzzle[y][this->getWidth() + 1] = minus;

            }

            // Cols

            for (uint8_t x = 1; x < this->getWidth() + 1; x++) {

                uint8_t minus = 0;
                uint8_t plus = 0;
                
                for (uint8_t y = 1; y < this->getHeight() + 1; y++) {

                    if (this->isPlus(x, y)) plus++;
                    if (this->isMinus(x, y)) minus++;

                }

                this->puzzle[0][x] = plus;
                this->puzzle[this->getHeight() + 1][x] = minus;

            }

        }


        void flipHorizontal() {

            for (uint8_t y = 1; y < this->getHeight() + 1; y++) {

                for (uint8_t x = 1; x < (this->getWidth() / 2) + 1; x++) {
                    
                    uint8_t x2 = this->getWidth() - x + 1;

                    uint8_t l = this->puzzle[y][x];
                    uint8_t r = this->puzzle[y][x2];

                    switch (l) {

                        case Tiles::Horizontal_Blank_Start:
                            l = Tiles::Horizontal_Blank_End;
                            break;

                        case Tiles::Horizontal_Blank_End:
                            l = Tiles::Horizontal_Blank_Start;
                            break;

                        default:
                            break;
                            
                    }

                    switch (r) {

                        case Tiles::Horizontal_Blank_Start:
                            r = Tiles::Horizontal_Blank_End;
                            break;

                        case Tiles::Horizontal_Blank_End:
                            r = Tiles::Horizontal_Blank_Start;
                            break;

                        default:
                            break;
                            
                    }

                    this->puzzle[y][x] = r;
                    this->puzzle[y][x2] = l;

                }

            }

        }


        void flipVertical() {

            for (uint8_t x = 1; x < this->getWidth() + 1; x++) {

                for (uint8_t y = 1; y < (this->getHeight() / 2) + 1; y++) {
                    
                    uint8_t y2 = this->getHeight() - y + 1;

                    uint8_t u = this->puzzle[y][x];
                    uint8_t d = this->puzzle[y2][x];

                    switch (u) {

                        case Tiles::Vertical_Blank_Start:
                            u = Tiles::Vertical_Blank_End;
                            break;

                        case Tiles::Vertical_Blank_End:
                            u = Tiles::Vertical_Blank_Start;
                            break;

                        default:
                            break;
                            
                    }

                    switch (d) {

                        case Tiles::Vertical_Blank_Start:
                            d = Tiles::Vertical_Blank_End;
                            break;

                        case Tiles::Vertical_Blank_End:
                            d = Tiles::Vertical_Blank_Start;
                            break;

                        default:
                            break;
                            
                    }

                    this->puzzle[y][x] = d;
                    this->puzzle[y2][x] = u;

                }

            }

            // Fix centre line ..

            for (uint8_t x = 1; x < this->getWidth() + 1; x++) {

                uint8_t y = (this->getHeight() / 2) + 1;
                uint8_t u = this->puzzle[y][x];

                switch (u) {

                    case Tiles::Vertical_Blank_Start:
                        u = Tiles::Vertical_Blank_End;
                        break;

                    case Tiles::Vertical_Blank_End:
                        u = Tiles::Vertical_Blank_Start;
                        break;

                    default:
                        break;
                        
                }

                this->puzzle[y][x] = u;


            }

        }

        void fillPuzzle() {

            // Fill one random spot ..

            bool placed = false;

            while (!placed) {

                uint8_t x = random(1, this->getWidth() + 1);
                uint8_t y = random(1, this->getHeight() + 1);
                uint8_t space = this->puzzle[y][x];

                switch (space) {
                    
                    case Tiles::Horizontal_Blank_Start: 
                        {
                            uint8_t r = random(2);

                            switch (r) {

                                case 0:
                                    this->puzzle[y][x] = Tiles::Horizontal_MinusPlus_Start;
                                    this->puzzle[y][x + 1] = Tiles::Horizontal_MinusPlus_End;
                                    break;

                                case 1:
                                    this->puzzle[y][x] = Tiles::Horizontal_PlusMinus_Start;
                                    this->puzzle[y][x + 1] = Tiles::Horizontal_PlusMinus_End;
                                    break;

                            }

                            placed = true;

                        }
                                    
                        break;
                        
                    case Tiles::Vertical_Blank_Start: 
                        {
                            uint8_t r = random(2);

                            switch (r) {


                                case 0:
                                    this->puzzle[y][x] = Tiles::Vertical_MinusPlus_Start;
                                    this->puzzle[y + 1][x] = Tiles::Vertical_MinusPlus_End;
                                    break;

                                case 1:
                                    this->puzzle[y][x] = Tiles::Vertical_PlusMinus_Start;
                                    this->puzzle[y + 1][x] = Tiles::Vertical_PlusMinus_End;
                                    break;

                            }

                            placed = true;

                        }

                        break;

                }

            }



            // Fill the rest ..

            for (uint8_t y = 1; y < this->getHeight() + 1; y++) {

                for (uint8_t x = 1; x < this->getWidth() + 1; x++) {
                
                    uint8_t space = this->puzzle[y][x];
                    uint8_t surroundingPlus = 0;
                    uint8_t surroundingMinus = 0;

                    if (this->isPlus(x, y - 1))      surroundingPlus++;
                    if (this->isPlus(x, y + 1))      surroundingPlus++;
                    if (this->isPlus(x - 1, y))      surroundingPlus++;
                    if (this->isPlus(x + 1, y))      surroundingPlus++;

                    if (this->isMinus(x, y - 1))     surroundingMinus++;
                    if (this->isMinus(x, y + 1))     surroundingMinus++;
                    if (this->isMinus(x - 1, y))     surroundingMinus++;
                    if (this->isMinus(x + 1, y))     surroundingMinus++;

                    switch (space) {
                        
                        case Tiles::Horizontal_Blank_Start: 
                            {
                                uint8_t r = random(16);
    // Serial.print("H ");
    // Serial.print(x);
    // Serial.print(",");
    // Serial.print(y);
    // Serial.print("=");
    // Serial.print(r);
    // Serial.print(" (+");
    // Serial.print(surroundingPlus);
    // Serial.print(" -");
    // Serial.print(surroundingMinus);
    // Serial.println(") ");
                                switch (r) {

                                    case 0 ... 14:
                                        {

                                            if (surroundingPlus > 0 && surroundingMinus > 0) {

                                                this->puzzle[y][x] = Tiles::Horizontal_Neutral_Start;
                                                this->puzzle[y][x + 1] = Tiles::Horizontal_Neutral_End;

                                            }
                                            else if (surroundingPlus > 0 && surroundingMinus == 0) {

                                                this->puzzle[y][x] = Tiles::Horizontal_MinusPlus_Start;
                                                this->puzzle[y][x + 1] = Tiles::Horizontal_MinusPlus_End;

                                            }
                                            else if (surroundingPlus == 0 && surroundingMinus > 0) {

                                                this->puzzle[y][x] = Tiles::Horizontal_PlusMinus_Start;
                                                this->puzzle[y][x + 1] = Tiles::Horizontal_PlusMinus_End;

                                            }
                                            else {

                                                switch (r) {

                                                    case 0 ... 7:
                                                        this->puzzle[y][x] = Tiles::Horizontal_MinusPlus_Start;
                                                        this->puzzle[y][x + 1] = Tiles::Horizontal_MinusPlus_End;
                                                        break;

                                                    case 8 ... 14:
                                                        this->puzzle[y][x] = Tiles::Horizontal_PlusMinus_Start;
                                                        this->puzzle[y][x + 1] = Tiles::Horizontal_PlusMinus_End;
                                                        break;

                                                    default:
                                                        this->puzzle[y][x] = Tiles::Horizontal_Neutral_Start;
                                                        this->puzzle[y][x + 1] = Tiles::Horizontal_Neutral_End;
                                                        break;

                                                }

                                            }

                                        }
                                        break;

                                    default:

                                        this->puzzle[y][x] = Tiles::Horizontal_Neutral_Start;
                                        this->puzzle[y][x + 1] = Tiles::Horizontal_Neutral_End;
                                        break;
                                        

                                }

                            }

                            break;
                            
                        case Tiles::Vertical_Blank_Start: 
                            {
                                uint8_t r = random(16);
    // Serial.print("V ");
    // Serial.print(x);
    // Serial.print(",");
    // Serial.print(y);
    // Serial.print("=");
    // Serial.print(r);
    // Serial.print(" (+");
    // Serial.print(surroundingPlus);
    // Serial.print(" -");
    // Serial.print(surroundingMinus);
    // Serial.println(")");
                            switch (r) {

                                    case 0 ... 14:
                                        {

                                            if (surroundingPlus > 0 && surroundingMinus > 0) {

                                                this->puzzle[y][x] = Tiles::Vertical_Neutral_Start;
                                                this->puzzle[y + 1][x] = Tiles::Vertical_Neutral_End;

                                            }
                                            else if (surroundingPlus > 0 && surroundingMinus == 0) {

                                                this->puzzle[y][x] = Tiles::Vertical_MinusPlus_Start;
                                                this->puzzle[y + 1][x] = Tiles::Vertical_MinusPlus_End;

                                            }
                                            else if (surroundingPlus == 0 && surroundingMinus > 0) {

                                                this->puzzle[y][x] = Tiles::Vertical_PlusMinus_Start;
                                                this->puzzle[y + 1][x] = Tiles::Vertical_PlusMinus_End;

                                            }
                                            else {

                                                switch (r) {

                                                    case 0 ... 7:
                                                        this->puzzle[y][x] = Tiles::Vertical_MinusPlus_Start;
                                                        this->puzzle[y + 1][x] = Tiles::Vertical_MinusPlus_End;
                                                        break;

                                                    case 8 ... 14:
                                                        this->puzzle[y][x] = Tiles::Vertical_PlusMinus_Start;
                                                        this->puzzle[y + 1][x] = Tiles::Vertical_PlusMinus_End;
                                                        break;

                                                    default:
                                                        this->puzzle[y][x] = Tiles::Vertical_Neutral_Start;
                                                        this->puzzle[y + 1][x] = Tiles::Vertical_Neutral_End;
                                                        break;

                                                }
                                            }
                                        }
                                        break;

                                    default:
                                        this->puzzle[y][x] = Tiles::Vertical_Neutral_Start;
                                        this->puzzle[y + 1][x] = Tiles::Vertical_Neutral_End;
                                        break;
                                        

                                }

                            }

                            break;

                    }
                            
                }

                //     DEBUG_PRINT(this->puzzle[y][x]);
                //     DEBUG_PRINT(" ");


                // DEBUG_PRINTLN();
            }

        }

        void printPuzzle() {

            #ifdef DEBUG

            DEBUG_PRINTLN(F("Puzzle ----------------------"));

            for (uint8_t y = 1; y < this->getHeight() + 1; y++) {

                for (uint8_t x = 1; x < this->getWidth() + 1; x++) {
                
                    DEBUG_PRINT(this->puzzle[y][x]);
                    DEBUG_PRINT(" ");

                }

                DEBUG_PRINTLN();
            }

            #endif

        }


        bool isPlus(uint8_t x, uint8_t y) {

            uint8_t i = this->puzzle[y][x];
            return isPlus(i);

        }


        bool isPlus(uint8_t i) {

            switch (i) {

                case Tiles::Horizontal_MinusPlus_End:
                case Tiles::Horizontal_PlusMinus_Start:
                case Tiles::Vertical_MinusPlus_End:
                case Tiles::Vertical_PlusMinus_Start:
                    return true;

                default:
                    return false;
                                
            }

        } 


        bool isMinus(uint8_t x, uint8_t y) {

            uint8_t i = this->puzzle[y][x];
            return isMinus(i);

        }


        bool isMinus(uint8_t i) {

            switch (i) {


                case Tiles::Horizontal_MinusPlus_Start:
                case Tiles::Horizontal_PlusMinus_End:
                case Tiles::Vertical_MinusPlus_Start:
                case Tiles::Vertical_PlusMinus_End:
                    return true;

                default:
                    return false;
                    
            }

        }

};









