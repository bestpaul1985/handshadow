//
//  level01.h
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#ifndef __handShadow__level01__
#define __handShadow__level01__

#include "ofMain.h"
#include "baseScene.h"
#include "dots.h"

class level01 :public baseScene{
public:
    void setup();
    void update();
    void checkWinStatus();
    void draw();
    void reset();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);

    dots    dot[5];
    float touchSize;
    vector<ofPoint> pattern_pos;
    ofImage *pattern;
    int *currentScene;
    int timer;
    int fingers;
    bool ending;
};
#endif /* defined(__handShadow__level01__) */
