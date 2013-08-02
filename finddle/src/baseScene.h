//
//  baseScene.h
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#ifndef __handShadow__baseScene__
#define __handShadow__baseScene__

#include "ofMain.h"

class baseScene{
public:
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void touchDown(int x, int y, int touchID){};
    virtual void touchUp(int x, int y, int touchID){};
    virtual void touchMove(int x, int y, int touchID){};
};

#endif /* defined(__handShadow__baseScene__) */
