#include <ArduboyFX.h>  



void renderGrid(uint8_t currentPlane, bool renderGuides) {

    bool flash = false;

    uint8_t xOffset_Cols[] = { 11, 10 };
    uint8_t yOffset_Rows[] = { 10, 9 };

    if (frameCount % 64 < 32 && gameState == GameState::Play) {

        flash = true;

    }

    uint8_t xOffset = xOffset_Cols[game.getGameSize()];
    uint8_t yOffset = yOffset_Rows[game.getGameSize()];


    // + Cols

    for (uint8_t i = 1; i <= game.getWidth(); i++) {

        uint8_t val = game.puzzle[0][i];
        uint8_t sol = game.solution[0][i];

        if (val == sol) {

            SpritesU::drawOverwrite(xOffset + ((i - 1) * game.getSpacing()), 0, Images::Numbers_5x3_1D_W, (sol * 3) + currentPlane);

        }
        else {

            SpritesU::drawOverwrite(xOffset + ((i - 1) * game.getSpacing()), 0, Images::Numbers_5x3_1D_G, (sol * 3) + currentPlane);

        }

    }


    // + Rows

    for (uint8_t i = 1; i <= game.getHeight(); i++) {

        uint8_t val = game.puzzle[i][0];
        uint8_t sol = game.solution[i][0];

        if (val == sol) {

            SpritesU::drawOverwrite(2, yOffset + ((i - 1) * game.getSpacing()), Images::Numbers_5x3_1D_W, (sol * 3) + currentPlane);

        }
        else {

            SpritesU::drawOverwrite(2, yOffset + ((i - 1) * game.getSpacing()), Images::Numbers_5x3_1D_G, (sol * 3) + currentPlane);

        }

    }


    // - Cols
        
    for (uint8_t i = 1; i <= game.getWidth(); i++) {

        uint8_t val = game.puzzle[game.getHeight() + 1][i];
        uint8_t sol = game.solution[game.getHeight() + 1][i];

        if (val == sol) {

            SpritesU::drawOverwrite(xOffset + ((i - 1) * game.getSpacing()), 11 + (game.getHeight() * game.getSpacing()), Images::Numbers_5x3_1D_W, (sol * 3) + currentPlane);

        }
        else {

            SpritesU::drawOverwrite(xOffset + ((i - 1) * game.getSpacing()), 11 + (game.getHeight() * game.getSpacing()), Images::Numbers_5x3_1D_G, (sol * 3) + currentPlane);

        }

    }


    // - Rows

    for (uint8_t i = 1; i <= game.getHeight(); i++) {

        uint8_t val = game.puzzle[i][game.getWidth() + 1];
        uint8_t sol = game.solution[i][game.getWidth() + 1];
        
        if (val == sol) {

            SpritesU::drawOverwrite(12 + (game.getWidth() * game.getSpacing()), yOffset + ((i - 1) * game.getSpacing()), Images::Numbers_5x3_1D_W, (sol * 3) + currentPlane);

        }
        else {

            SpritesU::drawOverwrite(12 + (game.getWidth() * game.getSpacing()), yOffset + ((i - 1) * game.getSpacing()), Images::Numbers_5x3_1D_G, (sol * 3) + currentPlane);

        }

    }

    SpritesU::drawOverwriteFX(0, 0, Images::Plus, currentPlane);
    SpritesU::drawOverwriteFX(9 + (game.getWidth() * game.getSpacing()), 9 + (game.getHeight() * game.getSpacing()), Images::Minus, currentPlane);



    for (uint8_t y = 1; y < game.getHeight() + 1; y++) {

        for (uint8_t x = 1; x < game.getWidth() + 1; x++) {

            uint8_t i = game.puzzle[y][x];
            uint8_t tileSet = game.getGameSize() == GameSize::Small ? 0 : 6;

            switch (i) {

                case 1:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() - 1 == x && game.getY() == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_0102, tileSet + currentPlane);
                    x++;
                    break;

                case 4:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() - 1 == x && game.getY() == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_0403, tileSet + currentPlane);
                    x++;
                    break;

                case 11:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() == x && game.getY() - 1 == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_1112, tileSet + currentPlane);
                    break;

                case 22:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() == x && game.getY() - 1 == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_2221, tileSet + currentPlane);
                    break;

                case 31:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() - 1 == x && game.getY() == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_3132, tileSet + currentPlane);
                    x++;
                    break;

                case 41:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() == x && game.getY() - 1 == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_4142, tileSet + currentPlane);
                    break;

                case 51:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() - 1 == x && game.getY() == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_5152, tileSet + currentPlane);
                    x++;
                    break;

                case 61:
                    if (flash && ((game.getX() == x && game.getY() == y) || (game.getX() == x && game.getY() - 1 == y))) { tileSet = tileSet + 3; }
                    SpritesU::drawPlusMaskFX(9 + ((x - 1) * game.getSpacing()), 9 + ((y - 1) * game.getSpacing()), Images::Tile_6162, tileSet + currentPlane);
                    break;

            }

        }

    }

    if (renderGuides) {

        uint8_t tileSet = game.getGameSize() == GameSize::Small ? 0 : 3;

        SpritesU::drawPlusMaskFX(7, game.getY() * game.getSpacing(), Images::Cursor_Y, tileSet + currentPlane);
        SpritesU::drawPlusMaskFX(9 + (game.getWidth() * game.getSpacing()), game.getY() * game.getSpacing(), Images::Cursor_Y, tileSet + currentPlane);

        SpritesU::drawPlusMaskFX(game.getX() * game.getSpacing(), 7, Images::Cursor_X, tileSet + currentPlane);
        SpritesU::drawPlusMaskFX(game.getX() * game.getSpacing(), 9 + (game.getHeight() * game.getSpacing()), Images::Cursor_X, tileSet + currentPlane);

    }

}