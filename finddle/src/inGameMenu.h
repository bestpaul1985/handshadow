//
//  inGameMenu.h
//  handShadow
//
//  Created by PengCheng on 7/23/13.
//
//

#ifndef __handShadow__inGameMenu__
#define __handShadow__inGameMenu__

#include "ofMain.h"
#include "rectangle.h"

enum LevelDoneType{
    BG_FADE,
    ICON_SHOW,
    ICON_FADE,
    BG_BACK,
};


class inGameMenu{
public:

    
    
    void setup(int *Coin, int *Level, float &GameTimer, int &FingerSize, float &BGScale, ofPoint *AccFrc);
    void update();
    void reset();
    void starter();
    void scoreUpdate();
    void draw();
    void pause();
    void levelDoneDraw();
    void touchDown(int x, int y);
    void touchMove(int x, int y);
    void touchUp(int x, int y);

    ofTrueTypeFont  font;
    ofTrueTypeFont  fontBig;

    vector<ofImage> fingerImg;
    vector<ofImage> iconImg;
    vector<ofPoint> linePos;
    vector<ofColor> lineColor;
    ofImage         bgImg;
    ofImage         clockOutLine;
    ofRectangle     bgRect;
    vector<ofRectangle>    buttons;
    vector<ofColor>    buttonColor;
    
    int *live;
    int *level;
    int *coin;
    int preCoin;
    float *gameTimer;
    int *fingerSize;
    float *bgScale;
    float *bgH;
    int angle;
    int preAngle;
    int timer;
    
    bool bLevelDone;
    bool bLevelFail;
    bool bNextLevel;
    bool bTryAgin;
    bool bHome;
    
    bool bTouchOverMenu;
    bool bTouchOverResume;
    
    ofPoint *accFrc;
    
    //starter
    bool bGameStart;
    int gameStartTimer;
    int gameStartCounter;
    float gameStartAlpha;
    float gameStartSpeed;
    vector<ofImage> readyImg;
    ofPoint gameStartOffset;
    float gameStartScale;
    float gameStartPct;
    //level done
    ofImage LDBackgroudImg[2];
    float LDAlpha;
    LevelDoneType LDType;
    ofPoint LDVelocity;
    float LDGravity;
    float LDFriction;
    ofPoint LDPos;
    float LDRadius;
    
    //score
    int score;
    ofImage coinBag;
    ofImage coinImg;
    
    //poused;
    bool bPauseL,bPauseR;
    
    ofImage resumeImgA,resumeImgB;
    ofImage homeImgA,homeImgB;
    rectangle resumeRect;
    rectangle homeRect;
    float pausePct;

};

#endif /* defined(__handShadow__inGameMenu__) */






