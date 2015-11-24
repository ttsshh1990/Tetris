//
//  GameScene.hpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "GameParameter.h"
#include "Board.hpp"
#include "Block.hpp"
#include "LRight.hpp"
#include "LLeft.hpp"
#include "Square.hpp"
#include "SShape.hpp"
#include "ZShape.hpp"
#include "TShape.hpp"
#include "Stick.hpp"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createGameScene();
    CREATE_FUNC(GameScene);
    virtual bool init();
private:
    //
    // Methods
    //
    void update(float dt);
    void move();
    void blockCheck();
    void endCheck();
    void newShape();
    Shape* generate();
    Direction getDirection(cocos2d::Vec2 v1, cocos2d::Vec2 v2);
    bool isAnimate();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    //
    // Members
    //
    bool touchEnable;
    bool moveEnable;
    bool onTouch;
    bool touchMoved;
    
    int moveCount;
    int blockSize;
    float dropSpeed;
    Shape* activeShape;
    Shape* nextShape;
    
    Board* board;
    cocos2d::Vec2 respawnPoint;
    cocos2d::Vec2 touchStartPoint;
    cocos2d::Vec2 currentPoint;
    cocos2d::Vec2 previousPoint;
    Direction slideDirection;

};


#endif /* GameScene_hpp */
