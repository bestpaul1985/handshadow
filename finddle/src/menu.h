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
    void draw();

    void reset();
    void snapIn();

    void drag();
    void dragDown(int x, int y, int touchID);
    void dragMove(int x, int y, int touchID);
    void dragUp(int x, int y, int touchID);
    
    void levelSetup();
    void levelUpdate();
    void levelDraw();
    void levelDown(int x, int y, int touchID);
    void levelMove(int x, int y, int touchID);
    void levelUp(int x, int y, int touchID);
    void levelReset();

    void hiden();
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    
    void subMenu(int num);
    void subMenuUp(int x, int y, int touchID);
    
    void purchaseSetup();
    void purchaseUpdate();
    void purchaseDraw();
    void purchaseTouchDown(int x, int y);
    void purchaseTouchMove(int x, int y);
    void purchaseTouchUp(int x, int y);
    
    void setSetup();
    void setUpdate();
    void setDraw();
    void setTouchDown(int x, int y);
    void setTouchMove(int x, int y);
    void setTouchUp(int x, int y);
    
    
    ofTrueTypeFont font;
    
    rectangle mainMenuRect[MAIN_MENU_BUTTON];
    float pct[MAIN_MENU_BUTTON];    
    float speed;

    string situation;
    int *scene;
    bool bSnapIn;
    int counter;
    
    ofImage button[MAIN_MENU_BUTTON];
    ofImage buttonOver[MAIN_MENU_BUTTON];
    ofImage background[MAIN_MENU_BUTTON];
    ofImage hidenLogo;
    ofImage mainMenuBg;
    ofPoint mainMenuBgPos;
    ofPoint touch;
    ofPoint preTouch;

    particle mParticle;
    ofPoint preParticlePos;

    ofPoint frc;
    bool bHidenLogo;
    bool bShowHidenLogo;
    bool bDrag;
    int  timer;
    bool bStartTime;
    bool bSave;
    vector<float> tempRectPos;
    //-------sub menu----------------
    int subMenuNum;
    int subStep;
    bool bSubMenu;
    //--------levels-----------------
    ofImage imgLockedLevel;
    vector<rectangle> levelRect;
    vector<float> levelPct;

    
    int *unLockedLevel;
    int *level;
    
    int levelCounter;
    int levelTimer;
    ofPoint levelTouch;
    ofPoint levelPreTouch;
    int axisX;
    int axisY;
    bool bLevelSnapIn;
    
    //-------Purchase-------------
    int *coin;
    int *timeSlowerChance;
    int *dotExtenderChance;
    int *dotFreezerChance;
    int *coinChance;
   
    vector<rectangle> coinRects;
    vector<rectangle> timeSlowerRects;
    vector<rectangle> dotExtenderRects;
    vector<rectangle> dotFreezerRects;
    vector<rectangle> purchaseButtons;
    
    int timeSlowerCounter;
    int coinCounter;
    int dotExtenderCounter;
    int dotFreezerCounter;
    
    bool bNoCoin;
    
    int *firstPlay;
    
    //---setting--------------------
    vector<rectangle> settingButton;
    
};

#endif /* defined(__handShadow__menu__) */