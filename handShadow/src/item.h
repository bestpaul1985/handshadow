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
    void setup(ofPoint Pos);
    void typeDefinder();
    void reset();
    void update();
    void draw();
    void touchDown(int x, int y, int touchId);
    void touchMove(int x, int y, int touchId);

    //defult
    ofPoint pos;
    float raduis;
    bool bCovered;
    bool bFixed;
    //type
    effect_type myType;
    int timeSlowerChance;
    int dotExtenderChance;
    int dotFreezerChance;
    int coinChance;
    
    bool bTimeSlowerChance;
    bool bDotExtenderChance;
    bool bDotFreezerChance;
    bool bCoinChance;
    
    //timer
    int timer;
};


#endif /* defined(__handShadow__item__) */
