#ifndef __CORE_H
# define __CORE_H

//#include "minilibxwrapper.h"
#include <array>
#include <vector>
#include <functional>
#include "guidisplay.h"
#include "audiowrapper.h"

#define BLOCK_SIZE 48

class GameCore
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // x, y of the left top corner                                                              //
    //////////////////////////////////////////////////////////////////////////////////////////////
    struct Block
    {
        int     x;
        int     y;
        bool    isVisible;
        std::uint8_t    *pxls;

        Block(int x, int y, bool visible, std::uint8_t *px)
            :
            x(x),
            y(y),
            isVisible(visible),
            pxls(px)
        {
        }
    };

    int     gameMode;
    int     direction_1;
    int     direction_2;
    int     lastDirection_1;
    int     lastDirection_2;
    int     horizontBlocksNum;
    int     verticalBlocksNum;
    int     m_width;
    int     m_height;
    int     scoreBlockWidth;
    int     scoreBlockHeight;
    int     scoreCount;
    bool    increaseSpeed;
    int     currentLib;
    void    *lib_discr;

    Block           *target;
    Block           *bonusTarget;
    GUIDisplay      *disp;
    AudioWrapper    *sound;

    std::uint8_t *snake_body_pixels_map;
    std::uint8_t *snake_h_north_pixels_map;
    std::uint8_t *snake_h_south_pixels_map;
    std::uint8_t *snake_h_west_pixels_map;
    std::uint8_t *snake_h_east_pixels_map;
    std::uint8_t *snake_2_body_pixels_map;
    std::uint8_t *snake_2_h_north_pixels_map;
    std::uint8_t *snake_2_h_south_pixels_map;
    std::uint8_t *snake_2_h_west_pixels_map;
    std::uint8_t *snake_2_h_east_pixels_map;

    std::uint8_t *startGamePixelMap;
    std::uint8_t *endGamePixelMap;
    std::uint8_t *fieldPixelMap;
    std::uint8_t *scorePixelMap;

    std::array<std::uint8_t*, 10> numbersPixelMaps;
    std::array<std::uint8_t*, 5> obstaclePixelMaps;
    std::array<std::uint8_t*, 6> targetPixelMaps;

    std::vector<Block*> obstacles;
    std::vector<Block*> snake_1;
    std::vector<Block*> snake_2;

    void    initElements();
    Block   *getBlock(int rangeX, int rangeY, std::uint8_t *blockPxls, bool isVisible);
    void    getRandomCoordinates(int &x, int &y, int rangeX, int rangeY);
    bool    isCoordinatesFree(int &x, int &y);
    void    setPixelToPixelArray(int sceneX, int sceneY, std::uint8_t *pixels,
                                 int rowLength, std::uint32_t color = 0);
    void    fillBackground(std::uint8_t *pixels, int xFrom, int xTo,
                           int yFrom, int yTo, uint32_t color = 0);
    void    insertBlockToScene(int sceneX, int sceneY, int blockWidth,
                               int blockHeight, std::uint8_t *blockPxls, std::uint8_t *scene);
    void    insertElements(std::uint8_t *pixels);
    void    insertField(std::uint8_t *pixels);
    void    insertScore(std::uint8_t *pixels);
    void    insertScoreCount(std::uint8_t *pixels);
    void    increaseSnake(int nx, int ny, int snakeNumber);
    void    updateSnake(int nx, int ny, std::vector<Block*> snake, int snakeNumber);
    void    updateTarget(Block *target);
    void    showOpening(std::uint8_t *pixels);
    void    gameOver(std::uint8_t *pixels);
    void    showingLoop(float duration);
    void    getLib(int libNumber);
    bool    getDirection(std::uint8_t *pixels);
    void    checkDirection();

    bool    getImage(std::uint8_t *pixels);
    std::uint8_t    *getHeadPixels(int snakeNumber);

    bool    checkTarget(int x, int y, Block* target);
    bool    checkObstacles(int x, int y, std::vector<Block*> snake);

    void    *loadLib(std::string libname);

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Debug functions                                                                          //
    //////////////////////////////////////////////////////////////////////////////////////////////
    int     pixToInt(int x, int y, int rowWidth, std::uint8_t *pixels);

    GameCore() = delete;
    GameCore(const GameCore &) = delete;
    GameCore(GameCore &&) = delete;
    GameCore &operator=(const GameCore &) = delete;
    GameCore &operator=(GameCore &&) = delete;

public:
    GameCore(int w, int h, int mode);
    ~GameCore();

    void    run();

};

#endif
