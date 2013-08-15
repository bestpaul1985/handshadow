#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "ofxiOSExternalDisplay.h"

#include "baseScene.h"
#include "handDetector.h"
#include "Mode01.h"
#include "ofxXmlSettings.h"
#include "xmlPointer.h"
#include "ofxInAppProduct.h"
#include "menu.h"
#import "AVSoundPlayer.h"

class testApp : public ofxiOSApp, public ofxiOSExternalDisplay{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void save();
    void purchase();
    void purchasePopup();
    void popupDismissed();
    void soundSetup();
    void soundTouchDown();
    void soundUpdate();

    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    void windowResized(int w, int h);
    void rotateToPortrait();
    void rotateToPortraitUpSideDown();
    void rotateToLandscapeLeft();
    void rotateToLandscapeRight();
    void toggleAutoRotation();
    bool bAuto;

    menu mMenu;
    baseScene * scenes[5];
    int currentScene;
    int preScene;
    ofPoint *accFrc;
    
    //-----XML-----------------------------------
    ofxXmlSettings XML;
    vector<xmlPointer> points;
    vector<xmlPointer> upGradePrices;
    string xmlStructure;
    string message;
    int live;
    int preLive;
    int level;
    int unLockedLevel;
    int firstPlay;
    int unixTime;
    int preUnixTime;
    string systemTime;
    
    //-----subGame------------------------------
    int timeSlowerChance;
    int dotExtenderChance;
    int dotFreezerChance;
    int coinChance;
    int coin;
    
    //---handDetector--------------------------
    float scale;
    int touchNum;
    
    
    //----purchase------------------------------
    ofxInAppProduct * coins00;
    ofxInAppProduct * coins01;
    ofxInAppProduct * coins02;
    
    //----sound---------------------------------
    AVSoundPlayer * sDotPressed;
    AVSoundPlayer * sDead;



};

