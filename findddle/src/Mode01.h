#ifndef __handShadow__Mode01__
#define __handShadow__Mode01__

#include "ofMain.h"
#include "baseScene.h"
#include "dots.h"
#include "xmlPointer.h"
#include "inGameMenu.h"
#include "item.h"
#include "ofxSpriteSheetRenderer.h"
static animation_t itemAnimation = { 0,  0,  7,  1,  1,  75, 0,  1, 7, 1 };


struct basicSprite {
	animation_t animation;
	ofPoint pos;
};

class Mode01 : public baseScene{
public:
    void setup();
    void xmlReader(vector<xmlPointer> pointer, int *CurrentLevel, int *CurrentScene);
    void update();
    void draw();
    void checkWin();
    void checkLose(int x, int y, int situation);
    void reset();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    
    void subGame();
    void inGameMenuDraw();
    void inGameMenuTouchDown(int x, int y, int touchID);
    void inGameMenuTouchMove(int x, int y, int touchID);
    void inGameMenuTouchUp(int x, int y, int touchID);
   
    
    inGameMenu myInGameMenu;
   

    //defult setting
    int *coin;
    int *live;
    int bgNum;
    
    vector<ofImage> patterns;
    vector<dots> myDot;
    vector<xmlPointer>  xmlPos;
    vector<ofPoint> dotPos;
    vector<ofImage> dotImgA;
    vector<ofImage> dotImgB;
    int *scene;
    int *level;
    int fingerSize;
    bool bSave;
    float bgWidth;
    float bgHight;
    float bgScale;

    ofTrueTypeFont font;
    ofTrueTypeFont fontSmaill;
    ofPoint *accFrc;
    
    //*******game timer********
    float gameTimerStart;
    float gameTimer;
    vector<ofImage> colorBg;
    bool bColorBg;
    int colorBgTimer;
    ofPoint bgOffSet;
    float bgOffSetSpeed;
    //*****check win*****
    int winTimer;
    bool bWinTimerStart;
    float winEffectSpeed;
    //******check lose*****
    bool bLoseTimerStart;
    int loseTimer;
    int PreCoverNum;
    ofPoint translate;
    
    //*******items*********
    vector<ofImage> itemImgs;
    vector<item> items;
    int *timeSlowerChance;
    int *dotExtenderChance;
    int *dotFreezerChance;
    int *coinChance;
    
    float timeSpeed;
    
    ofxSpriteSheetRenderer *itemSpriteRenderer;
    vector <basicSprite * > sprites;
    
    //*******subGame********
    float timeSlowerTimer;
    float timeSlowerDuration;
    ofImage dotFreezerIcon;
    
    //*******handDetector******
    float *scale;
};


#endif








