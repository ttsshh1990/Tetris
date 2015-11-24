//
//  LRight.hpp
//  Tetris
//
//  Created by tian on 9/27/15.
//
//

#ifndef LRight_hpp
#define LRight_hpp

#include <stdio.h>
#include "Shape.hpp"

class LRight : public Shape::Shape
{
public:
    static LRight* createLRight();
    CREATE_FUNC(LRight);
    
protected:
    void initBlock();

    
};


#endif /* LRight_hpp */
