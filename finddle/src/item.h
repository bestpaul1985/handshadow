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
static animation_t itemAnimation0 = { 0,  0,  9,  1,  1,  75, 0,  -1, -1, 1 };
static animation_t itemAnimation1 = { 0,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };
struct basicSprite {
	animation_t animation;
	ofPoint pos;
};

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

    void setup(float x, float y, ofxSpriteSheetRenderer *Render);
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
    bool bAnimation;
    //timer
    int timer;
    
    //animation
    ofxSpriteSheetRenderer *render;
    vector <basicSprite * > sprites;
    
};


#endif /* defined(__handShadow__item__) */
