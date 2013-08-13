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
#include "ofxSpriteSheetRenderer.h"

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

    void setup(ofPoint *Org);
    void typeDefinder();
    void reset();
    void update();
    void draw();
    void touchDown(int x, int y, int touchId);
    void touchMove(int x, int y, int touchId);

    
    //defult
    ofPoint pos;
    float raduis;
    float angle;
    bool bCovered;
    bool bFixed;
    ofPoint *org;
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
