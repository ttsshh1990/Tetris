//
//  Block.hpp
//  Tetris
//
//  Created by tian on 9/24/15.
//
//

#ifndef Block_hpp
#define Block_hpp

#include "GameParameter.h"
#include "cocos2d.h"

class Block : public cocos2d::Sprite
{
public:
    static Block* createBlock(const std::string picName);
    CREATE_FUNC(Block);
    int getBlockSize();
    void setBlockSize(int s);
    
private:
    int blockSize;
    
};

#endif /* Block_hpp */
