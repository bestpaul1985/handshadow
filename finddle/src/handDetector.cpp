//
//  handDetector.cpp
//  handShadow
//
//  Created by PengCheng on 7/28/13.
//
//

#include "handDetector.h"

void handDetector::setup(){

    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 40);
    bgImg.loadImage("assets/images/handDetector/bg.jpg");
    reset();
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
                
                if (dis>=850)
                {
                    message = "Your hand's is big size";
                    *scale = -0.09;
                }
                else if (dis>=700 && dis<850)
                {
                    message = "Your hand's is medium size";
                    *scale = 0.0;

                }else if(dis < 700 && dis>0)
                {
                    message = "Your hand's is small size";
                    *scale = 0.09;

                }else
                {
                    message = "Can't get result";
                }
                
                myType = RESULT;
            }
        }break;
        case RESULT:
            break;
    }

}
//---------------------------------------------------
void handDetector::reset(){
    
    button[0].set(20, 650, 100,75);
    button[1].set(900, 650, 100,75);
    buttonColor[0].set(255);
    buttonColor[1].set(255);
    myType = READY;
    linePos.set(ofGetWidth(),0);
    max.set(0,0);
    min.set(0,0);
    touchs.clear();
    message = "Put your hand on";
}

//---------------------------------------------------
void handDetector::draw(){

    ofSetColor(255);
    bgImg.draw(0, 0);
    
    ofSetColor(255,30, 200);
    ofLine(linePos.x,linePos.y, linePos.x, linePos.y+ofGetHeight());
    
    for (int i=0; i<touchs.size(); i++) {
        if (touchs[i].x == linePos.x) {
            ofSetColor((int)ofRandom(30), 255, 200);
            ofCircle(touchs[i], 50);
        }
    }
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()-150);
    ofSetColor(255);
    font.drawString(message, -font.stringWidth(message)/2, -font.stringHeight(message)/2);
    ofPopMatrix();
    
    
    
    ofSetColor(buttonColor[1]);
    ofRect(button[1]);
    
    
    
    if (myType == RESULT) {
        
        ofSetColor(buttonColor[0]);
        ofRect(button[0]);

    }
}


//---------------------------------------------------
void handDetector::touchDown(int x, int y, int touchId){
    
  
    if (myType == READY) {
        if (*touchNum > 3) {
            myType = GO;
        }
        
        if (button[0].inside(x, y)) {
            buttonColor[0].set(30);
        }
    }
    
    
    if (myType == GO) {
        ofPoint touch(x,y);
        touchs.push_back(touch);
        
        if (button[0].inside(x, y)) {
            buttonColor[0].set(30);
        }
    }
    
    if (myType == RESULT) {
        if (button[0].inside(x, y)) {
            buttonColor[0].set(30);
        }
        
        if(button[1].inside(x, y)) {
            buttonColor[1].set(30);
        }
    }
    
    
}

//---------------------------------------------------
void handDetector::touchMove(int x, int y, int touchId){
   
    if(button[1].inside(x, y)) {
        buttonColor[1].set(30);
    }else{
        buttonColor[1].set(255);
    }
    
    if (myType == GO) {
        ofPoint touch(x,y);
        touchs.push_back(touch);
        
        if (button[1].inside(x, y)) {
            buttonColor[1].set(30);
        }
    }
    
    if (myType == RESULT) {
        if (button[0].inside(x, y)) {
            buttonColor[0].set(30);
        }else{
            buttonColor[0].set(255);
        }
    }

}

//---------------------------------------------------
void handDetector::touchUp(int x, int y, int touchId){
   
    if(button[1].inside(x, y)) {
        buttonColor[1].set(255);
        if (*firstPlay == 0) {
            *scene = 2;
            *firstPlay =1;
        }else{
            *scene = 0;
        }
        reset();
    }
    
    if (myType == GO) {
        if (*touchNum == 0) {
            reset();
        }
    }
    
    if (myType == RESULT) {
        
        if (button[0].inside(x, y)) {
            buttonColor[0].set(255);
            reset();
        }
    }
}
















