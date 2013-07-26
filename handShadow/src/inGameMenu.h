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
#include "ofxSpriteSheetRenderer.h"

static animation_t fingerAnimation = {  0,  0,  1,  1,  1,  75, 0,  -1, -1, 1 };

struct basicSprite {
	animation_t animation;
	ofPoint pos;
	float speed;
};

class inGameMenu{
public:
    void setup();
    void update();
    void draw();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    void liveSystemSetup();
    void liveSystemUpdate();
    void liveSystemDraw();
    void liveSystemTouchDown(int x, int y, int touchID);
    void liveSystemTouchMove(int x, int y, int touchID);
    void liveSystemTouchUp(int x, int y, int touchID);
        
    ofImage wellDown;
    ofRectangle imgRect;
    bool bwellDone;
    bool bTouchOverMenu;
    bool bTouchOverResume;
    int wellDoneTimer;
    ofImage imgResume;
    ofImage imgResume_b;
    ofImage imgMenu;
    ofImage imgMenu_b;
    ofRectangle menuRect;
    ofRectangle resumeRect;
    
    ofxSpriteSheetRenderer *spriteRenderer;
    vector <basicSprite * > sprites;
    ofImage fingerBG;
    int *live;
    bool bliveTouchOver;
    bool bPause;
    bool bBackToMainMenu;

};

#endif /* defined(__handShadow__inGameMenu__) */
