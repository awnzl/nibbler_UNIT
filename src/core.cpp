#include <iostream>
#include <functional>
#include <unistd.h>
#include "core.h"
#include "minilibxwrapper.h"

GameCore::GameCore() {
    fillPixelBlock(background_pxls, 0);
    //add here new blocks
    initBlocks();
}

GameCore::~GameCore() {
}

void    GameCore::fillPixelBlock(uint8_t *px, int color) {
    for (int y = 0; y < BLOCK_SIZE; y++) {
        for (int x = 0; x < BLOCK_SIZE; x++) {
            setPixel(x, y, px, color);
        }
    }
}

void    GameCore::initBlocks() {
    for (int i = 0, x = 0, y = 0; i < BLOCKS_QUANTITY; i++) {
        blocks[i] = new Block(x, y, true, background_pxls);
        x++;
        if (!(x % BLOCKS_QUANTITY / 2)) {
            x = 0;
            y++;
            std::cout << "initBlocks Debug: y = " << y << std::endl;//TODO: remove
        }
    }
}

void    GameCore::setBlocks() {

}

void    GameCore::setPixel(int x, int y, uint8_t *pixels, int color = 0) {
    int idx = (y * WIDTH_HEIGTH + x) * 4;
    // pixels[idx + 3] = color >> 24; //a
    // pixels[idx + 2] = color >> 16; //r
    // pixels[idx + 1] = color >> 8;  //g
    // pixels[idx + 0] = color;       //b
    //next works for sfml (becouse alpha [3] and red [2])
    pixels[idx + 0] = color >> 24; //b
    pixels[idx + 1] = color >> 16; //g
    pixels[idx + 2] = color >> 8;  //r
    pixels[idx + 3] = color;       //a
}

void    GameCore::fillImage(uint8_t *pixels) {
    if (pixels)
        ;
    //replece with block oriented logic
    //
    // for (int i = 0; i < BLOCKS_QUANTITY; i++)
    //     blocks[i].toString();

    // for (int y = 0; y < WIDTH_HEIGTH; y++) {
    //     for (int x = 0; x < WIDTH_HEIGTH; x++) {
    //         setPixel(x, y, pixels);
    //     }
    // }
}

void    GameCore::insertSnake(uint8_t *pixels) {
    for (int y = snake.y - BLOCK_SIZE / 2; y < snake.y + BLOCK_SIZE / 2; y++)
        for (int x = snake.x - BLOCK_SIZE / 2; x < snake.x + BLOCK_SIZE / 2; x++)
            setPixel(x, y, pixels, 0x30D5C8);
}

//		1
//	2	0	3
//		4
//a w s d
uint8_t    *GameCore::getImage(int event, uint8_t *pixels) {
    switch (event) {
        case (1):
            snake.y -= (snake.y - 10 - BLOCK_SIZE / 2  <= 0) ? 0 : 10;
            break;
        case (2):
            snake.x -= (snake.x - 10 - BLOCK_SIZE / 2 <= 0) ? 0 : 10;
            break;
        case (3):
            snake.x += (snake.x + 10 + BLOCK_SIZE / 2 >= WIDTH_HEIGTH) ? 0 : 10;
            break;
        case (4):
            snake.y += (snake.y + 10 + BLOCK_SIZE / 2 >= WIDTH_HEIGTH) ? 0 : 10;
            break;
    }
    //TODO: add frame to window
    fillImage(pixels);
    insertSnake(pixels);
    return pixels;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// Debug functions																			    //
//////////////////////////////////////////////////////////////////////////////////////////////////

int GameCore::pixToInt(int x, int y, uint8_t *pixels) {
    int idx = (y * WIDTH_HEIGTH + x) * 4;
    // return ((pixels[idx + 3] << 24) +
    //         (pixels[idx + 2] << 16) +
    //         (pixels[idx + 1] << 8) + (pixels[idx]));
    //for sfml:
    return ((pixels[idx] << 24) +
            (pixels[idx + 1] << 16) +
            (pixels[idx + 2] << 8) +
            (pixels[idx + 3]));
}

void	GameCore::run() { 
    GUIDisplay disp;

    int isRun = 0;
    uint8_t pixels[ARRAY_SIZE];
    
    while (isRun > -1) {
        isRun = disp.run(getImage(isRun, pixels));
        std::cout << "debug: libreturn: " << isRun << std::endl;
    }
    exit(1);
}
