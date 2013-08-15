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
    void drawLevel();
    void drawPurchase();
    void drawSetting();
    void drawPause();
    void update();
    void interpolateByPct(float myPct);
    void interpolateByPct2(float myPct);
    
    ofTrueTypeFont *font;
    
    ofPoint		pos;
    ofPoint		posa;
    ofPoint		posb;
    ofPoint		posc;
    float		pct;	// what pct are we between "a" and "b"
    float		shaper;
    ofRectangle bgRect;
    ofRectangle buttonRect;
    ofRectangle purchaseRect;
    
    float rectW;
    float rectH;
    
    ofImage *button;
    ofImage *buttonTouchOver;
    ofImage *background;
    
    ofImage *fingerImg[2];
    //level
    ofImage *imgLockedLevel;
    ofImage *imgUnlockedLevel;
    string message;
    bool bLocked;
    
    bool bTouchOver;
    bool bIsEnoughMoney;

    bool bFixed;
    float shadowWidth;

    //purchase
    ofImage *purchaseImg;
    ofImage *purchasePlusImg;
    bool bPurchaseAnimation;
    int itemNumber;
    ofTrueTypeFont *purchaseAnimationfont;
    float purchaseAnimationPct;
    //setting
    ofImage *setImg;
    
};

#endif /* defined(__handShadow__rectangle__) */
