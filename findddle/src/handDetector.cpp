//
//  handDetector.cpp
//  handShadow
//
//  Created by PengCheng on 7/28/13.
//
//

#include "handDetector.h"

void handDetector::setup(){

    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 22);
    bgImg.loadImage("assets/images/handDetector/bg.png");
    reScanImg[0].loadImage("assets/images/handDetector/rescan_normal.png");
    reScanImg[1].loadImage("assets/images/handDetector/rescan_pressed.png");
    skipImg[0].loadImage("assets/images/handDetector/skip_normal.png");
    skipImg[1].loadImage("assets/images/handDetector/skip_pressed.png");
    reset();
    bSave = false;

}

//---------------------------------------------------
void handDetector::update(){

    switch (myType) {
        case READY:
            break;
        case GO:{
            
            float speed = 1;
            linePos.x -=speed;
            if (linePos.x<0) {
                
                for (int i=0; i<touchs.size(); i++) {
                    max.x = MAX(max.x, touchs[i].x);
                    if (i==0) {
                        min.x = touchs[0].x;
                    }else{
                        min.x = MIN(min.x, touchs[i].x);
                    }
                }
                
                float dis = max.x-min.x;
//                cout<<dis<<"  "<<max.x<<" "<<min.x<<endl;
                
                if (dis>=800)
                {
                    message = "Your hand's size is large  ";
                    *scale = -0.12;
                }
                else if (dis>=700 && dis<800)
                {
                    message = "Your hand's size is medium  ";
                    *scale = 0.0;

                }else if(dis < 700 && dis>0)
                {
                    message = "Your hand's size is  small  ";
                    *scale = 0.12;

                }
                
                myType = RESULT;
                timer = ofGetElapsedTimeMillis();
            }
        }break;
        case RESULT:
            
            if(ofGetElapsedTimeMillis()-timer>1000){
                timerNum --;
                if (timerNum<0) {
                    timerNum = 0;
                    if (*firstPlay == 0) {
                        *scene = 2;
                        *firstPlay =1;
                    }else{
                        *scene = 0;
                    }
                    reset();
                }
                bSave = true;
                timer = ofGetElapsedTimeMillis();
            }
            
            break;
    }

}
//---------------------------------------------------
void handDetector::reset(){
    
    button.set(800, 650, 205,111);
    bButtonCoverd = false;
    myType = READY;
    linePos.set(ofGetWidth(),0);
    max.set(0,0);
    min.set(0,0);
    touchs.clear();
    message = "";
    timer = ofGetElapsedTimeMillis();
    timerNum = 3;
}

//---------------------------------------------------
void handDetector::draw(){

    ofSetColor(255);
    bgImg.draw(0, 0);
    
    ofSetColor(253,11, 11);
    ofSetLineWidth(3);
    ofLine(linePos.x,linePos.y, linePos.x, linePos.y+ofGetHeight());
    
    for (int i=0; i<touchs.size(); i++) {
        if (touchs[i].x == linePos.x) {
            ofSetColor((int)ofRandom(30), 255, 200);
            ofCircle(touchs[i], 50);
        }
    }
    
  
    
    
    if (myType == RESULT) {
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2-50, ofGetHeight()-80);
        ofSetColor(30);
        font.drawString(message+ofToString(timerNum),
                        -font.stringWidth(message)/2 -font.stringWidth(ofToString(timerNum))/2,
                        -font.stringHeight(message)/2 -font.stringHeight(ofToString(timerNum))/2);
        ofPopMatrix();
        
        ofSetColor(255);
        if (bButtonCoverd) {
            reScanImg[1].draw(button);
        }else{
            reScanImg[0].draw(button);
        }

    }else{
        ofSetColor(255);
        if (bButtonCoverd) {
            skipImg[1].draw(button);
        }else{
            skipImg[0].draw(button);
        }
    }
}


//---------------------------------------------------
void handDetector::touchDown(int x, int y, int touchId){
    
    if(button.inside(x, y)) {
        bButtonCoverd = true;
    }
    
    if (myType == READY) {
        if (*touchNum > 3) {
            myType = GO;
        }
        
    }
    
    
    if (myType == GO) {
        ofPoint touch(x,y);
        touchs.push_back(touch);
    }
    
    
}

//---------------------------------------------------
void handDetector::touchMove(int x, int y, int touchId){
   
    if(button.inside(x, y)) {
        bButtonCoverd = true;
    }else{
        bButtonCoverd = false;
    }
    
    if (myType == GO) {
        ofPoint touch(x,y);
        touchs.push_back(touch);
    }
    

}

//---------------------------------------------------
void handDetector::touchUp(int x, int y, int touchId){
    
    if (myType == RESULT) {
        
        if (button.inside(x, y)) {
            reset();
        }
    }else if(myType == GO){
        
        if (*touchNum == 0) {
            reset();
        }
        
        if (button.inside(x, y)) {
            bButtonCoverd = false;
            if (*firstPlay == 0) {
                *scene = 2;
                *firstPlay =1;
            }else{
                *scene = 0;
            }
            bSave = true;
            reset();
        }
    }else if(myType == READY){
    
        if (button.inside(x, y)) {
            bButtonCoverd = false;
            if (*firstPlay == 0) {
                *scene = 2;
                *firstPlay =1;
            }else{
                *scene = 0;
            }
            bSave = true;
            reset();
        }
    }
}
















