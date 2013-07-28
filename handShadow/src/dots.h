//
//  dots.h
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#ifndef __handShadow__dots__
#define __handShadow__dots__

#include "ofMain.h"

class dots{

public:
    void setup(float x, float y,ofImage *A, ofImage *B);
    void update();
    void radiusExtend();
    void radiusExtendReset();
    void touchDown(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    
    void reset();
    void draw();
    
    ofPoint pos;
    vector<int> myId;
    vector<int> notMyId;
    float angle;
    ofColor color;
    float radius;
    bool    bCovered;
    bool    bFixed;
    //-----button image---------
    ofImage *dot_normal;
    ofImage *dot_pressed;
    
    //-----Effect --------------
    bool bRadiusExtend;
    bool bFreezed;
    float goalRaduis;
    float radiusPct;
    float radiusPctOrg;
    
};


#endif /* defined(__handShadow__dots__) */
