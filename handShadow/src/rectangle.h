//
//  rectangle.h
//  handShadow
//
//  Created by PengCheng on 7/17/13.
//
//

#ifndef __handShadow__rectangle__
#define __handShadow__rectangle__

#include "ofMain.h"

class rectangle {
    
public:
	
    rectangle();
	
    void draw();
    void update();
    void interpolateByPct(float myPct);
    void interpolateByPct2(float myPct);
    
    ofPoint		pos;
    ofPoint		posa;
    ofPoint		posb;
    ofPoint		posc;
    float		pct;	// what pct are we between "a" and "b"
    float		shaper;
    ofRectangle bgRect;
    ofRectangle buttonRect;

    float rectW;
    float rectH;
    
    ofImage *button;
    ofImage *buttonTouchOver;
    ofImage *background;
    
    bool bTouchOver;
        
};

#endif /* defined(__handShadow__rectangle__) */
