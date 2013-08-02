#ifndef __handShadow__Mode01__
#define __handShadow__Mode01__

#include "ofMain.h"
#include "baseScene.h"
#include "dots.h"
#include "xmlPointer.h"
#include "inGameMenu.h"
#include "item.h"

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
    int live;
    
    ofImage *pattern;
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
    
    //*******subGame********
    float timeSlowerTimer;
    float timeSlowerDuration;
    
    
    //*******handDetector******
    float *scale;
};


#endif








