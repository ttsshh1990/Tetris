//
//  Board.cpp
//  Tetris
//
//  Created by tian on 9/25/15.
//
//

#include "Board.hpp"
USING_NS_CC;


bool Board::init()
{
    if(!Sprite::init()){
        return false;
    }
    this->setAnchorPoint(Vec2(0,0));
    this->setPosition(Vec2(0,0));
    leftBottom = Vec2((SCREEN_WIDTH-BOARD_WIDTH) / 2,BOARD_BOTTOM);
    rightBottom = Vec2(leftBottom.x+BOARD_WIDTH,BOARD_BOTTOM);
    respawnPoint = getPositionByCR(4, 19);
    
//    blocks =(Block**) malloc(sizeof(Block*)*COL*ROW);
//    for (int row; row < ROW; row++) {
//        for (int col; col < COL; col++) {
//            blocks[col*COL+row] = nullptr;
//        }
//    }
    
    blocks.fill(nullptr);
    
    
    DrawNode* drawNode = DrawNode::create();
    drawNode->drawLine(leftBottom,rightBottom, Color4F(177, 174, 255, 0.5));
    drawNode->drawLine(leftBottom, Vec2(leftBottom.x,leftBottom.y+ROW*blockSize), Color4F(177, 174, 255, 0.5));
    drawNode->drawLine(rightBottom, Vec2(rightBottom.x , rightBottom.y + ROW*blockSize), Color4F(177, 174, 255, 0.5));
    drawNode->setLineWidth(5);
    
    this->addChild(drawNode);
    
    score = 0;
    scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 25);
    scoreLabel->setPosition(Vec2(250,850));
    scoreLabel->setColor(Color3B::BLACK);
    this->addChild(scoreLabel);
    
    return true;
}


Vec2 Board::getPositionByCR(int col, int row)
{
    Vec2 v = Vec2(col,row)*blockSize + leftBottom;
    return v;
}

Vec2 Board::getRespawnPoint()
{
    return respawnPoint;
}

bool Board::isBlocked(Shape *shape, Direction direction)
{
    std::vector<Block*> blocks = shape->getBlocks();
    Vec2 shapePosition = shape->getPosition();
    for(auto it = blocks.begin(); it != blocks.end(); it++){
        Vec2 position = (*it)->getPosition() + shapePosition;
//        Vec2 v = getCRByPosition(position);
        BoardPosition v = getCRByPosition(position);
        switch (direction) {
            case Left:
//                if(v.x == 0) return true;
//                if(hasBlock[(int)v.x-1][(int)v.y]) return true;
                if(v.col == 0) return true;
                if(hasBlock[v.col-1][v.row]) return true;
                break;
            case Right:
//                if(v.x == COL-1) return true;
//                if(hasBlock[(int)v.x+1][(int)v.y]) return true;
                if(v.col == COL-1) return true;
                if(hasBlock[v.col + 1][v.row]) return true;
                break;
            case Down:
//                if(v.y == 0) return true;
//                if (hasBlock[(int)v.x][(int)v.y-1]) return true;
                if(v.row == 0) return true;
                if(hasBlock[v.col][v.row -1 ]) return true;
                break;
            case Stay:
//                if(v.x < 0 || v.y < 0 || v.x > COL-1) return true;
                if(v.col < 0 || v.row < 0 || v.col > COL-1) return true;
//                if (hasBlock[(int)v.x][(int)v.y]) return true;
                if(hasBlock[v.col][v.row]) return true;
                break;
            default:
                break;
        }

    }
    return  false;
}

BoardPosition Board::getCRByPosition(Vec2 position)
{
    Vec2 v = (position - leftBottom)/blockSize;
    BoardPosition boardPosition;
    if(v.x < 0){
        boardPosition.col = -1;
    }else{
        boardPosition.col = MathMethod::round(v.x);
    }
    
    if (v.y < 0) {
        boardPosition.row = -1;
    }else{
        boardPosition.row = MathMethod::round(v.y);
    }
    
    return boardPosition;
//    return (position - leftBottom)/blockSize;
}

void Board::addBlocks(Shape *shape)
{
    std::vector<Block*> shapeBlocks = shape->getBlocks();

    for (auto it = shapeBlocks.begin(); it != shapeBlocks.end(); it++) {
        Block* block = *it;
        Vec2 blockPosition = block->getPosition() + shape->getPosition();
        block->retain();
        block->removeFromParent();
        this->addChild(block);
        block->release();
        block->setPosition(blockPosition);
        
        BoardPosition v = getCRByPosition(blockPosition);
        int col = v.col;
        int row = v.row;
        
        hasBlock[col][row] = true;
        blocks[col*ROW+row] = block;
    }
    removeBlocks();
    
    
}

void Board::removeBlocks()
{
    
    int moveDownCount = 0;
    for (int row = 0; row < ROW; row++) {
        bool full = true;
        for (int col = 0; col < COL; col++) {
            if(!hasBlock[col][row]){
                full = false;
                break;
            }
            
        }
        if(full){
            for (int col = 0; col < COL; col++) {
                if(blocks[col*ROW + row] != nullptr) {
                    Vec2 animatePosition = blocks[col*ROW + row]->getPosition();
//                    removeAnimate(animatePosition);
                    blocks[col*ROW + row]->runAction(Sequence::create(ScaleTo::create(0.2, 0),
                                                                      CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent,blocks[col*ROW + row])),
                                                                      NULL));
//                    blocks[col*ROW + row]->removeFromParent();
                    blocks[col*ROW + row] = nullptr;
                    hasBlock[col][row] = false;
                }
            }
            
            moveDownCount++;
        }else{
            if(moveDownCount > 0){
                for (int col = 0; col < COL; col++) {
                    if(hasBlock[col][row]){
//                        blocks[col*ROW + row] -> setPosition(getPositionByCR(col, row - moveDownCount));
                        blocks[col*ROW + row]->runAction(MoveTo::create(0.15f, getPositionByCR(col, row - moveDownCount)));
                        blocks[col*ROW+ (row - moveDownCount)] = blocks[col*ROW + row];
                        blocks[col*ROW + row] = nullptr;
                        hasBlock[col][row] = false;
                        hasBlock[col][row-moveDownCount] = true;
                    }
                }
            }
        }
    }
    if(moveDownCount > 0){
        switch (moveDownCount) {
            case 1:
                score += 40;
                break;
            case 2:
                score += 100;
                break;
            case 3:
                score += 300;
                break;
            case 4:
                score += 1200;
                break;
            default:
                break;
        }
        char text[256];
        sprintf(text, "%d", score);
        scoreLabel->setString(text);
        
    }
}

void Board::moveShape(Shape *shape, Direction direction)
{
    switch (direction) {
        case Left:
            if (!isBlocked(shape, direction)) {
                Vec2 v = shape->getPosition();
                v.x -= blockSize;
                shape->setPosition(v);
            }
            break;
            
        case Right:
            if(!isBlocked(shape, direction)){
                Vec2 v = shape->getPosition();
                v.x += blockSize;
                shape->setPosition(v);
            }
            
        default:
            break;
    }
    
}

void Board::spinShape(Shape *shape)
{
    shape->spin();
    if(isBlocked(shape, Stay)){
        shape->rollBack();
    }
}

void Board::moveDown(Shape *shape)
{
    while (!isBlocked(shape, Down)) {
        Vec2 v = shape->getPosition();
        v.y -= blockSize;
        shape->setPosition(v);
    }
}

bool Board::isAnimate()
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if(blocks[col*COL + row] != nullptr){
                if(blocks[col*COL + row]->numberOfRunningActions() != 0)
                    return true;
            }
        }
    }
    return  false;
}

void Board::removeAnimate(cocos2d::Vec2 position)
{
    auto sprite = Sprite::create();
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(position);
    
    this->addChild(sprite);
    Vector<SpriteFrame*> frames(12);
    char str[100] = {0};
    for(int i = 1; i < 12; i++){
        sprintf(str, "light%d.png",i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        frames.pushBack(frame);
    }
    auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("light1.png");
    auto size1 = frame1->getOriginalSize();
    sprite->setScale(blockSize/size1.width);
    
    
    auto animation = Animation::createWithSpriteFrames(frames,0.05f);
    auto lightening = Animate::create(animation);
    sprite->runAction(Sequence::create(lightening,
                                       CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent,sprite)),
                                       NULL));

}
