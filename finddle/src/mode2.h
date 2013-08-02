//
//  mode2.h
//  handShadow
//
//  Created by PengCheng on 7/15/13.
//
//

#ifndef __handShadow__mode2__
#define __handShadow__mode2__

#include "ofMain.h"
#include "baseScene.h"
#include "dots.h"

class mode2 : public baseScene{
public:
    void setup();
    void update();
    void draw();
    void checkWinStatus();
    void reset();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    
    dots dot[5];
    int order;
    int counter;
    float touchSize;
    
    int *currentScene;
    ofImage *pattern;
    
    int timer;
    int fingers;
    bool ending;
};

#endif /* defined(__handShadow__mode2__) */
