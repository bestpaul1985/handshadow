//
//  item.h
//  handShadow
//
//  Created by PengCheng on 7/25/13.
//
//

#ifndef __handShadow__item__
#define __handShadow__item__

#include "ofMain.h"

enum effect_type{
    NONE,
    COIN_MAKER,
    TIME_SLOWER,
    DOT_EXTENDER,
    DOT_FREEZER,
};

class item
{

public:
    item();
    void setup(float x, float y);
    void typeDefinder();
    void reset();
    void update();
    void draw();
    void touchDown(int x, int y, int touchId);
    void touchMove(int x, int y, int touchId);

    
    ofImage *itemImages[4];
    //defult
    ofPoint pos;
    float raduis;
    bool bCovered;
    bool bFixed;
    ofPoint org;
    //type
    effect_type myType;
    
    int timeSlowerChance;
    int dotExtenderChance;
    int dotFreezerChance;
    int coinChance;
    
    bool bTimeSlower;
    bool bDotExtender;
    bool bDotFreezer;
    bool bCoin;
    
    //timer
    int timer;
};


#endif /* defined(__handShadow__item__) */
