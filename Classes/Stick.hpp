//
//  Stick.hpp
//  Tetris
//
//  Created by tian on 9/28/15.
//
//

#ifndef Stick_hpp
#define Stick_hpp

#include <stdio.h>
#include "Shape.hpp"

class Stick : public Shape::Shape
{
public:
    static Stick* createStick();
    CREATE_FUNC(Stick);
protected:
    void initBlock();
    
};

#endif /* Stick_hpp */
