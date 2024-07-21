#include <ArduboyFX.h>  
 


void play_Init() { 

    gameState = GameState::Play;
    game.loadPuzzle();

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void play_Update() { 

    uint8_t justPressed = getJustPressedButtons();

    game.incFrameCount();

    if (justPressed & RIGHT_BUTTON) {

        if (game.getX() < game.getWidth()) {
            game.setX(game.getX() + 1);
            game.setFrameCount(0);
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

        game.setFrameCount(0);

        switch (game.puzzle[game.getY()][game.getX()]) {

            // Horizontal ..

            case Tiles::Horizontal_MinusPlus_Start:
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_Start;
                game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_PlusMinus_End;
                break;

            case Tiles::Horizontal_MinusPlus_End:
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_PlusMinus_End;
                game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_PlusMinus_Start;
                break;
    
            case Tiles::Horizontal_PlusMinus_End:
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;
                game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
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
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;
                game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;                  
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
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                break;

            case Tiles::Vertical_Blank_End:
                game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
                break;

        }

        game.updateNumbers();
        
    }

    if (justPressed & B_BUTTON) {

        game.setFrameCount(0);

        switch (game.puzzle[game.getY()][game.getX()]) {

            // Horizontal ..

            case Tiles::Horizontal_MinusPlus_Start:
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_Start;
                game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Blank_End;
                break;

            case Tiles::Horizontal_MinusPlus_End:
                game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Blank_Start;
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Blank_End;
                break;
    
            case Tiles::Horizontal_PlusMinus_End:
                game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_MinusPlus_Start;
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_End;
                break;

            case Tiles::Horizontal_PlusMinus_Start:
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_MinusPlus_Start;
                game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_MinusPlus_End;            
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
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_Start;
                game.puzzle[game.getY()][game.getX() + 1] = Tiles::Horizontal_Neutral_End;                  
                break;

            case Tiles::Horizontal_Blank_End:
                game.puzzle[game.getY()][game.getX() - 1] = Tiles::Horizontal_Neutral_Start;
                game.puzzle[game.getY()][game.getX()] = Tiles::Horizontal_Neutral_End;                  
                break;

            // Vertical ..

            case Tiles::Vertical_MinusPlus_Start:
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_Start;
                game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Blank_End;            
                break;

            case Tiles::Vertical_MinusPlus_End:
                game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Blank_Start;                  
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Blank_End;
                break;

            case Tiles::Vertical_PlusMinus_End:
                game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_MinusPlus_Start;                  
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_End;
                break;

            case Tiles::Vertical_PlusMinus_Start:
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_MinusPlus_Start;
                game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_MinusPlus_End;                  
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
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_Start;
                game.puzzle[game.getY() + 1][game.getX()] = Tiles::Vertical_Neutral_End;                  
                break;

            case Tiles::Vertical_Blank_End:
                game.puzzle[game.getY() - 1][game.getX()] = Tiles::Vertical_Neutral_Start;
                game.puzzle[game.getY()][game.getX()] = Tiles::Vertical_Neutral_End;                  
                break;

        }

        printPuzzle();
        game.updateNumbers();
        
    }

}

void play(ArduboyGBase_Config<ABG_Mode::L4_Triplane> &a) {

    uint8_t currentPlane = a.currentPlane();
    if (a.needsUpdate()) play_Update();

    // if (game.getFrameCount() % 4 == 0) {

    //     xBot = xBot - 1;        if (xBot == -204) xBot = 0;

    // }

    // if (game.getFrameCount() % 5 == 0) {

    //     xTop = xTop + 1;        if (xTop == 204) xTop = 0;

    // }
   
    // SpritesU::drawOverwriteFX(xTop, -1, Images::Wave_Top, currentPlane);
    // SpritesU::drawOverwriteFX(xTop - 204, -1, Images::Wave_Top, currentPlane);
    // SpritesU::drawOverwriteFX(xBot, 43, Images::Wave_Bot, currentPlane);
    // SpritesU::drawOverwriteFX(xBot + 204, 43, Images::Wave_Bot, currentPlane);

    renderGrid(currentPlane);

}
