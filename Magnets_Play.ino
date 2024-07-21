#include <ArduboyFX.h>  
 


void play_Init() { 

    gameState = GameState::Play;
    game.setup();
    game.loadPuzzle();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();

    game.incFrameCount();

    if (gameState == GameState::Play) {

        if (justPressed & RIGHT_BUTTON) {

            if (game.getX() < game.getWidth()) {
                game.setX(game.getX() + 1);
                game.setFrameCount(0);
            }
            else {

                gameState = GameState::Play_Menu1;

            }
            
        }

        if (justPressed & LEFT_BUTTON) {

            if (game.getX() > 1) {
                game.setX(game.getX() - 1);
                game.setFrameCount(0);
            }
            
        }

        if (justPressed & DOWN_BUTTON) {

            if (game.getY() < game.getHeight()) {
                game.setY(game.getY() + 1);
                game.setFrameCount(0);
            }
            
        }

        if (justPressed & UP_BUTTON) {

            if (game.getY() > 1) {
                game.setY(game.getY() - 1);
                game.setFrameCount(0);
            }
            
        }

        if (justPressed & A_BUTTON) {
    gameState = GameState::Play_Init;
    return;
            game.setFrameCount(0);

            switch (game.puzzle[game.getY()][game.getX()]) {

                // Horizontal ..

                // case Tiles::Horizontal_MinusPlus_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_Start;
                //     game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_PlusMinus_End;
                //     break;

                // case Tiles::Horizontal_MinusPlus_End:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_End;
                //     game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_PlusMinus_Start;
                //     break;
        
                // case Tiles::Horizontal_PlusMinus_End:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;
                //     game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
                //     break;

                // case Tiles::Horizontal_PlusMinus_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_Start;
                //     game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Neutral_End;            
                //     break;

                // case Tiles::Horizontal_Neutral_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_Start;
                //     game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Blank_End;                  
                //     break;

                // case Tiles::Horizontal_Neutral_End:
                //     game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Blank_Start;
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_End;                  
                //     break;

                // case Tiles::Horizontal_Blank_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_Start;
                //     game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_MinusPlus_End;                  
                //     break;

                // case Tiles::Horizontal_Blank_End:
                //     game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_MinusPlus_Start;
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_End;                  
                //     break;

                // // Vertical ..

                // case Tiles::Vertical_MinusPlus_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_Start;
                //     game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_PlusMinus_End;            
                //     break;

                // case Tiles::Vertical_MinusPlus_End:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_End;
                //     game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_PlusMinus_Start;                  
                //     break;

                // case Tiles::Vertical_PlusMinus_End:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;
                //     game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;                  
                //     break;

                // case Tiles::Vertical_PlusMinus_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_Start;
                //     game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Neutral_End;                  
                //     break;

                // case Tiles::Vertical_Neutral_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_Start;
                //     game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Blank_End;                  
                //     break;

                // case Tiles::Vertical_Neutral_End:
                //     game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Blank_Start;
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_End;                  
                //     break;

                // case Tiles::Vertical_Blank_Start:
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                //     game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                //     break;

                // case Tiles::Vertical_Blank_End:
                //     game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                //     game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                //     break;

                case Tiles::Horizontal_MinusPlus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_PlusMinus_End;
                    break;

                case Tiles::Horizontal_MinusPlus_End:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_End;
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_PlusMinus_Start;
                    break;
        
                case Tiles::Horizontal_PlusMinus_End:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_End;
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Blank_Start;
                    break;

                case Tiles::Horizontal_PlusMinus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Blank_End;            
                    break;

                case Tiles::Horizontal_Neutral_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_PlusMinus_End;                  
                    break;

                case Tiles::Horizontal_Neutral_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_PlusMinus_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_End;                  
                    break;

                case Tiles::Horizontal_Blank_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_MinusPlus_End;                  
                    break;

                case Tiles::Horizontal_Blank_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_MinusPlus_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_End;                  
                    break;

                // Vertical ..

                case Tiles::Vertical_MinusPlus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_PlusMinus_End;            
                    break;

                case Tiles::Vertical_MinusPlus_End:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_End;
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_PlusMinus_Start;                  
                    break;

                case Tiles::Vertical_PlusMinus_End:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_End;
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Blank_Start;                  
                    break;

                case Tiles::Vertical_PlusMinus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Blank_End;                  
                    break;

                case Tiles::Vertical_Neutral_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_PlusMinus_End;                  
                    break;

                case Tiles::Vertical_Neutral_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_PlusMinus_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_PlusMinus_End;                  
                    break;

                case Tiles::Vertical_Blank_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                    break;

                case Tiles::Vertical_Blank_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                    break;
            }

            game.updateNumbers_Puzzle();
            Serial.println(game.gameComplete());
            
        }

        if (justPressed & B_BUTTON) {

            game.setFrameCount(0);

            switch (game.puzzle[game.getY()][game.getX()]) {

                // Horizontal ..

                case Tiles::Horizontal_MinusPlus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Neutral_End;
                    break;

                case Tiles::Horizontal_MinusPlus_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;
                    break;
        
                case Tiles::Horizontal_PlusMinus_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;
                    break;

                case Tiles::Horizontal_PlusMinus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Neutral_End;            
                    break;

                case Tiles::Horizontal_Neutral_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Blank_End;                  
                    break;

                case Tiles::Horizontal_Neutral_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Blank_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_End;                  
                    break;

                case Tiles::Horizontal_Blank_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Neutral_End;                  
                    break;

                case Tiles::Horizontal_Blank_End:
                    game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;                  
                    break;

                // Vertical ..

                case Tiles::Vertical_MinusPlus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Neutral_End;            
                    break;

                case Tiles::Vertical_MinusPlus_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;                  
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;
                    break;

                case Tiles::Vertical_PlusMinus_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;                  
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;
                    break;

                case Tiles::Vertical_PlusMinus_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Neutral_End;                  
                    break;

                case Tiles::Vertical_Neutral_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Blank_End;                  
                    break;

                case Tiles::Vertical_Neutral_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Blank_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_End;                  
                    break;

                case Tiles::Vertical_Blank_Start:
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_Start;
                    game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Neutral_End;                  
                    break;

                case Tiles::Vertical_Blank_End:
                    game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;
                    game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;                  
                    break;

            }

            game.updateNumbers_Puzzle();
            Serial.println(game.gameComplete());

        }

    }
    else {

        // Menu ..

        if (justPressed & LEFT_BUTTON || justPressed & B_BUTTON) {

            gameState = GameState::Play;
            
        }

        if (justPressed & UP_BUTTON && gameState > GameState::Play_Menu1) {

            gameState--;
            
        }

        if (justPressed & DOWN_BUTTON && gameState < GameState::Play_Menu4) {

            gameState++;
            
        }

        if (justPressed & A_BUTTON) {

            switch (gameState) {

                case GameState::Play_Menu1:
                    game.clearPuzzle();
                    game.setX(1);
                    game.setY(1);
                    gameState = GameState::Play;
                    break;

                case GameState::Play_Menu2:
                    // game.clearPuzzle();
                    // game.setX(1);
                    // game.setY(1);
                    // gameState = GameState::Play;
                    break;

                case GameState::Play_Menu3:
                    game.copy_SolutionToPuzzle();
                    game.setX(1);
                    game.setY(1);
                    gameState = GameState::Play;
                    break;

                case GameState::Play_Menu4:
                    saveCookie(true);
                    game.setFrameCount(400);
                    gameState = GameState::Title_OptResume;
                    break;

            }
            
        }

    }

}

void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) play_Update();

    if (game.getFrameCount() % 4 == 0) {

        xBot = xBot - 1;        if (xBot == -200) xBot = 0;

    }

    if (game.getFrameCount() % 5 == 0) {

        xTop = xTop + 1;        if (xTop == 200) xTop = 0;

    }
   
    SpritesU::drawOverwriteFX(88, xTop, Images::Wave_Left, currentPlane);
    SpritesU::drawOverwriteFX(88, xTop - 200, Images::Wave_Left, currentPlane);
    SpritesU::drawOverwriteFX(108, xBot, Images::Wave_Right, currentPlane);
    SpritesU::drawOverwriteFX(108, xBot + 200, Images::Wave_Right, currentPlane);

    if (gameState == GameState::Play) {
        SpritesU::drawPlusMaskFX(92, 3, Images::InGame, currentPlane);
    }
    else {
        SpritesU::drawPlusMaskFX(92, 3, Images::InGame, ((static_cast<uint8_t>(gameState) - static_cast<uint8_t>(GameState::Play_Menu0)) * 3) + currentPlane);
    }

    renderGrid(currentPlane);

}
