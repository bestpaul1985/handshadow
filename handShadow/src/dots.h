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
    void setup(float x, float y);
    void update();
    void InAndOut();

    void resetModeOne();
    void resetModeTwo();
    void draw();
    
    ofPoint pos;
    bool    bCovered;
    int     touchID;
    ofColor color;
    
    float radius0;
    float radius1;

    //-------effect--------------
    bool effect;
    bool zoomIn;
    bool zoomOut;
    
    float pct;
    float speed;
    
    float zoomPct;
    float zoomSpeed;
    
    //-----button image---------
    ofImage button;
    float size;
};


#endif /* defined(__handShadow__dots__) */
