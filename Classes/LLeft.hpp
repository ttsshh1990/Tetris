//
//  LLeft.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef LLeft_hpp
#define LLeft_hpp

#include <stdio.h>
#include "Shape.hpp"

class LLeft : public Shape::Shape
{
public:
    static LLeft* createLLeft();
    CREATE_FUNC(LLeft);
    
protected:
    void initBlock();
    
    
};


#endif /* LLeft_hpp */
