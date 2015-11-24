//
//  Board.hpp
//  Tetris
//
//  Created by tian on 9/25/15.
//
//

#ifndef Board_hpp
#define Board_hpp


#include <stdio.h>
#include "GameParameter.h"
#include "Shape.hpp"
#include "Block.hpp"
#include <array>
#include "MathMethod.hpp"

class BoardPosition
{
public:
    int col;
    int row;
};


class Board : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Board);
    virtual bool init();
    cocos2d::Vec2 getRespawnPoint();
    bool isBlocked(Shape* shape, Direction direction);
    bool isAnimate();
    void addBlocks(Shape* shape);
    void moveShape(Shape* shape, Direction direction);
    void spinShape(Shape* shape);
    void moveDown(Shape* shape);
    
private:
    //
    // Methods
    //
    cocos2d::Vec2 getPositionByCR(int col, int row);
//    cocos2d::Vec2 getCRByPosition(cocos2d::Vec2 position);
    BoardPosition getCRByPosition(cocos2d::Vec2 position);
    void removeBlocks();
    void removeAnimate(cocos2d::Vec2 position);
    
    //
    // Members
    //
    cocos2d::Vec2 respawnPoint;
    cocos2d::Vec2 leftBottom;
    cocos2d::Vec2 rightBottom;
    int blockSize = BOARD_WIDTH/COL;
//    Block** blocks;
    
    bool hasBlock[COL][ROW];
    cocos2d::Label* scoreLabel;
    int score;
    std::array<Block*, COL*ROW> blocks;
    
    
    
};



#endif /* Board_hpp */
