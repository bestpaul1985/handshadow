//
//  handDetector.h
//  handShadow
//
//  Created by PengCheng on 7/28/13.
//
//

#ifndef __handShadow__handDetector__
#define __handShadow__handDetector__

#include "ofMain.h"
#include "baseScene.h"

enum handDetectorType{
    
    READY,
    GO,
    RESULT,
};

class handDetector:public baseScene{
public:
    void setup();
    void update();
    void draw();
    void reset();
    void touchDown(int x, int y, int touchId);
    void touchMove(int x, int y, int touchId);
    void touchUp(int x, int y, int touchId);
    
    int *scene;
    int *firstPlay;
    int *touchNum;
    
    
    vector<ofPoint> touchs;
    ofPoint linePos;
    ofPoint max;
    ofPoint min;
    
    ofTrueTypeFont  font;
    handDetectorType myType;
    bool bStart;
    bool bSave;
    string message;
    ofImage bgImg;
    
    ofRectangle button;
    ofImage skipImg[2];
    ofImage reScanImg[2];

    
    float *scale;
    bool bButtonCoverd;

    float timer;
    int timerNum;
    
};

#endif /* defined(__handShadow__handDetector__) */
