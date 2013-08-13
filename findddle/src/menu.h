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
#include "xmlPointer.h"

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
    void purchaseReset();
    void purchaseDraw();
    void purchaseTouchDown(int x, int y);
    void purchaseTouchMove(int x, int y);
    void purchaseTouchUp(int x, int y);

    
    void setSetup();
    void setUpdate();
    void setDraw();
    void setReset();
    void setTouchDown(int x, int y);
    void setTouchMove(int x, int y);
    void setTouchUp(int x, int y);
    
    void tutorialSetup();
    void tutorialUpdate();
    void tutorialReset();
    void tutorialDraw();
    void tutorialTouchDown(int x, int y);
    void tutorialTouchMove(int x, int y);
    
    vector<xmlPointer> upGradePrices;
    
    
    
    ofTrueTypeFont font;
    ofTrueTypeFont fontPrice;
    ofTrueTypeFont fontLevel;
    rectangle mainMenuRect[MAIN_MENU_BUTTON];
    float pct[MAIN_MENU_BUTTON];    
    float speed;

    string situation;
    int *scene;
    bool bSnapIn;
    int counter;
    
    ofImage button[MAIN_MENU_BUTTON];
    ofImage buttonOver[MAIN_MENU_BUTTON];
    ofImage fingerTop[MAIN_MENU_BUTTON];
    ofImage fingerBot[MAIN_MENU_BUTTON];
    ofImage buttonBackground;
    ofImage hidenLogo;
    ofImage mainMenuBg;
    ofPoint mainMenuBgPos;
    ofPoint touch;
    ofPoint preTouch;

    particle mParticle;
    ofPoint preParticlePos;
    int *firstPlay;
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
    bool bGoStore;
    //--------levels-----------------
    ofImage imgLockedLevel;
    ofImage imgUnlockedLevel;
    
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
    bool bLevelChosen;
    //-------Purchase-------------
    int *live;
    int *coin;
    int *timeSlowerChance;
    int *dotExtenderChance;
    int *dotFreezerChance;
    int *coinChance;
    
    ofPoint coinOffset;
    
    int livePrice[3];
    int upGradeLevel[4];
    vector<rectangle> liveButtons;
    vector<rectangle> coinButtons;
    vector<rectangle> itemButtons;
    vector<ofImage> purChaseImgCoins;
    vector<ofImage> purChaseImglives;
    vector<ofImage> purChaseImgItems;
       
    ofImage purChaseImglines[3];
    ofImage infoBarImg;
    ofRectangle prices01[3];
    ofRectangle prices02[3];
    ofRectangle prices03[4];
    ofRectangle purchaseline[3];
    ofPoint purchasePos;
    ofPoint purchasePrePos;
    ofRectangle infoRect;
    
    bool bNoCoin;
    bool bPurchaseWithCoin;
    bool bPurchaseWithMoney;

    bool bPurchaseCoin[3];
    bool bPurchaseLive[3];
    bool bPurchaseItem[4];
    bool bIsEnoughMoneyLive[3];
    bool bIsEnoughMoneyItem[4];
    
        
    //---setting--------------------
    vector<rectangle> settingButton;
    vector<ofImage> setImgs;
    bool bSound;
    
    //---tutorial-------------------
    vector<ofImage> tutorialImg;
    vector<ofPoint> tutorialPos;
    ofPoint tutorialTouch;
    ofPoint tutorialPreTouch;
    
};

#endif /* defined(__handShadow__menu__) */
