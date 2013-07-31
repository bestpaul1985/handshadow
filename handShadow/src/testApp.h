#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "menu.h"

#include "baseScene.h"
#include "handDetector.h"
#include "Mode01.h"
#include "ofxXmlSettings.h"
#include "xmlPointer.h"

class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

        menu mMenu;
        baseScene * scenes[5];
        int currentScene;
        ofImage pattern;
    
    //-----XML-----------------------------------
    ofxXmlSettings XML;
    vector<xmlPointer> points;
    string xmlStructure;
    string message;
    
    int level;
    int unLockedLevel;
    int firstPlay;
    string systemTime;
    
    //-----subGame------------------------------
    int timeSlowerChance;
    int dotExtenderChance;
    int dotFreezerChance;
    int coinChance;
    
    int coin;
    
    //---handDetector--------------------------
    float scale;

};



