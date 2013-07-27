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
    ofImage *pattern;
    vector<dots> myDot;
    vector<xmlPointer>  xmlPos;
    vector<ofPoint> dotPos;
    vector<ofImage> dotImgA;
    vector<ofImage> dotImgB;
    int *scene;
    int *level;
    int live;
    bool bSave;
    float bgWidth;
    float bgHight;
    //*****game start******
    bool bGameStart;
    int gameStartTimer;
    ofTrueTypeFont font;
    ofTrueTypeFont fontSmaill;
    int gameStartNumber;
    
    //*******game timer********
    float gameTimerStart;
    float gameTimer;
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
    vector<item> items;
    int *timeSlowerChance;
    int *dotExtenderChance;
    int *dotFreezerChance;
    int *coinChance;

    int *coin;
    float timeSpeed;
    
    //*******subGame********
    float timeSlowerTimer;
    float timeSlowerDuration;
};


#endif








