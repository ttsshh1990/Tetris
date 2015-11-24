//
//  Shape.hpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#include "GameParameter.h"
#include "cocos2d.h"
#include "Block.hpp"

class Shape : public cocos2d::Sprite
{
public:
    virtual void spin();
    virtual void rollBack();
    bool init();
    cocos2d::Vec2 getOriginPoint();
    std::vector<Block*> getBlocks();
protected:
    cocos2d::Vec2 origin;
    std::vector<Block*> blocks;
    cocos2d::Vec2* positions;
    virtual void initBlock();
    virtual void setBlock();
    std::string fileName;
    int state;
    int blockSize;
};

#endif /* Shape_hpp */
