//
//  menu.h
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#ifndef __handShadow__menu__
#define __handShadow__menu__

#include "ofMain.h"
#include "baseScene.h"
#include "rectangle.h"
#include "particle.h"

#define MAIN_MENU_BUTTON 5


class menu : public baseScene{
public:
    void setup();
    void update();
    void snapIn();
    void drag();
    void reset();
    void draw();
    void hiden();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    void subMenu(int num);
    
    rectangle mainMenuRect[MAIN_MENU_BUTTON];
    float pct[MAIN_MENU_BUTTON];    
    float speed;

    ofTrueTypeFont *font;
    string situation;
    int *currentScene;
    bool bSnapIn;
    int counter;
    
    ofImage button[MAIN_MENU_BUTTON];
    ofImage buttonOver[MAIN_MENU_BUTTON];
    ofImage background[MAIN_MENU_BUTTON];
    ofImage hidenLogo;
    
    ofPoint touch;
    ofPoint preTouch;
    ofPoint orgTouch;

    particle mParticle;
    float preParticleX;

    float frc;
    bool bHidenLogo;
    bool bShowHidenLogo;
    bool bDrag;
    int timer;
    bool bStartTime;
    
    vector<float> tempRectPos;
    //-------sub menu----------------
    int subMenuNum;
    int subStep;
    bool bSubMenu;
   
};

#endif /* defined(__handShadow__menu__) */
