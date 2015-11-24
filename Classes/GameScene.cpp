//
//  GameScene.cpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#include "GameScene.hpp"
USING_NS_CC;



Scene* GameScene::createGameScene(){
    auto scene = Scene::create();
    auto gameScene = GameScene::create();
    
    scene->addChild(gameScene);
    
    return scene;
}

bool GameScene::init(){
    if(!Layer::init()){
        return false;
    }
    //
    // Load frames
    //
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("lightening2.plist");
    
    //
    // Load background
    //
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2(0,0));
    background->setPosition(Vec2(0,0));
    this->addChild(background);
    
    //
    // Init Parameters
    //
    blockSize = BOARD_WIDTH/COL;
    float interval = Director::getInstance()->getAnimationInterval();
    dropSpeed = blockSize * interval * N_BLOCK_PS;
    moveCount = 0;
    touchEnable = true;
    moveEnable = true;
    onTouch = false;
    touchMoved = false;
    
    //
    // Init Board
    //
    board = Board::create();
    this->addChild(board);
    respawnPoint = board->getRespawnPoint();
    
    //
    // Init Shape
    //
    activeShape = generate();
    Vec2 origin = activeShape->getOriginPoint()*blockSize;
    activeShape->setPosition(respawnPoint-origin);
    this->addChild((activeShape));
    activeShape->retain();
    nextShape = generate();
    origin = nextShape->getOriginPoint()*blockSize;
    nextShape->setPosition(respawnPoint-origin);
    nextShape->retain();
    
    
    //
    // Set listener
    //
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    return true;
}


void GameScene::update(float dt)
{
    if(isAnimate()){
        
    }else{
        if(moveCount < 20 && moveEnable) {
            moveCount++;
        }else{
            touchEnable = false;
            move();
            moveCount = 0;
            touchEnable = true;
        }
    }
}

void GameScene::move()
{
    if(board->isBlocked(activeShape,Direction::Down)){
        onTouch = false;
        //endCheck
        board->addBlocks(activeShape);
        newShape();
        
    }else{
        //move
        Vec2 v = activeShape->getPosition();
        v.y -= blockSize;
        activeShape->setPosition(v);
    }
    
}

void GameScene::newShape()
{
    activeShape->removeFromParent();
    activeShape->release();
    activeShape = nextShape;
    this->addChild(activeShape);
    nextShape = generate();
    Vec2 origin = nextShape->getOriginPoint()*blockSize;
    nextShape->setPosition(respawnPoint-origin);
    nextShape->retain();

}

void GameScene::blockCheck()
{
    
}

void GameScene::endCheck()
{
    
}

Shape* GameScene::generate()
{
    int i = arc4random()%7;
    Shape* s;
    switch (i) {
        case 0:
            s = LRight::createLRight();
            break;
        case 1:
            s = LLeft::createLLeft();
            break;
        case 2:
            s = Square::createSquare();
            break;
        case 3:
            s = SShape::createSShape();
            break;
        case 4:
            s = ZShape::createZShape();
            break;
        case 5:
            s = TShape::createTShape();
            break;
        case 6:
            s = Stick::createStick();
            break;
            
        default:
            break;
    }
    return s;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(onTouch){
        previousPoint = currentPoint;
        currentPoint = touch->getLocation();
        Direction tempDirection = getDirection(currentPoint, previousPoint);
        if(tempDirection != slideDirection ){
            slideDirection = tempDirection;
            touchStartPoint = previousPoint;
        }
        Vec2 sub = currentPoint - touchStartPoint;
        switch (slideDirection) {
            case Left:
                if (sub.x <  -(blockSize * MOVE_SENSITIVITY)) {
                    moveEnable = false;
                    board->moveShape(activeShape, Left);
                    touchStartPoint = currentPoint;
                    touchMoved = true;
                    moveEnable = true;
                }
                break;
            case Right:
                if (sub.x > blockSize * MOVE_SENSITIVITY) {
                    moveEnable = false;
                    board->moveShape(activeShape, Right);
                    touchStartPoint = currentPoint;
                    touchMoved = true;
                    moveEnable = true;
                }
                break;
            case Down:
                if (sub.y < -blockSize * MOVE_SENSITIVITY) {
                    moveEnable = false;
                    board->moveDown(activeShape);
                    board->addBlocks(activeShape);
                    newShape();
                    touchMoved = true;
                    moveEnable = true;
                    onTouch = false;
                    moveCount = 0;
                }
                break;
            default:
                break;
        }

    }
    
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    touchStartPoint = touch->getLocation();
    currentPoint = touch->getLocation();
    slideDirection = Up;
    touchMoved = false;
    onTouch = true;
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    onTouch = false;
    if (!touchMoved) {
        moveEnable = false;
        board->spinShape(activeShape);
        moveEnable = true;
    }
}

Direction GameScene::getDirection(cocos2d::Vec2 v1, cocos2d::Vec2 v2)
{
    cocos2d::Vec2 sub = v1-v2;
    float radius = atan2f(sub.y, sub.x);
    float degree = radius * (180.0 / M_PI);
    
    if(degree < 45 && degree > -45){
        return Right;
    }else if(degree > 45 && degree < 135){
        return Up;
    }else if(degree >135 || degree < -135){
        return Left;
    }else{
        return Down;
    }
    
}

bool GameScene::isAnimate()
{
    return board->isAnimate();
//    return false;
}