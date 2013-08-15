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
    void setup(float x, float y,ofImage *A, ofImage *B, ofImage *C, ofImage *D);
    void update();
    void radiusExtend();
    void radiusExtendReset();
    void touchDown(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void draw();
    
    string message;
    float   pct;
    ofPoint pos;
    ofPoint posA;
    ofPoint posB;
    float   speed;
    
    vector<int> myId;
    vector<int> notMyId;
    float angle;
    ofColor color;
    float radius;
    float frezzerRadiusX;
    float frezzerRadiusY;
    float frezzerGoalRadiusX;
    float frezzerGoalRadiusY;
    bool    bCovered;
    bool    bFixed;
    
    
    
    ofPoint fingerPos;
    float   fingerSpeed;
    float   fingerPct;

    //-----button image---------
    ofImage *dot_normal;
    ofImage *dot_pressed;
    ofImage *dot_freezed;
    ofImage *fingle;
    //-----Effect --------------
    bool bRadiusExtend;
    bool bFreezed;
    float goalRaduis;
    float radiusPct;
    float radiusPctOrg;
    
    //---sound-----------------
    bool bSondPlay;
    
};


#endif /* defined(__handShadow__dots__) */
