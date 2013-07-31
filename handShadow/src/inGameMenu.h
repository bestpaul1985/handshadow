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



class inGameMenu{
public:
    void setup(int *Coin, int *Level, float &GameTimer, int &FingerSize);
    void update();
    void reset();
    void draw();
    void touchDown(int x, int y);
    void touchMove(int x, int y);
    void touchUp(int x, int y);

    ofTrueTypeFont  font;
    vector<ofImage> fingerImg;
    vector<ofImage> iconImg;
    vector<ofPoint> linePos;
    vector<ofColor> lineColor;
    ofImage         bgImg;
    ofImage         clockOutLine;
    ofImage         wellDoneImg;
    ofRectangle     bgRect;
    vector<ofRectangle>    buttons;
    vector<ofColor>    buttonColor;
    int *live;
    int *level;
    int *coin;
    float *gameTimer;
    int *fingerSize;
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
    
};

#endif /* defined(__handShadow__inGameMenu__) */
