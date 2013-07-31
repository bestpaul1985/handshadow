//
//  inGameMenu.cpp
//  handShadow
//
//  Created by PengCheng on 7/23/13.
//
//

#include "inGameMenu.h"

void inGameMenu::setup(int *Coin , int *Level , float &GameTimer, int &FingerSize){
    
    coin = Coin;
    level = Level;
    gameTimer = &GameTimer;
    fingerSize = &FingerSize;
    font.loadFont("assets/fonts/Comfortaa_Regular.ttf", 30);
    bgImg.loadImage("assets/images/inGameMenu/bg.png");
    clockOutLine.loadImage("assets/images/inGameMenu/outline.png");
    wellDoneImg.loadImage("assets/images/inGameMenu/welldone.png");
    for (int i=0; i<6; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/"+ofToString(i)+".png");
        fingerImg.push_back(temp);
    }
    for (int i=0; i<8; i++) {
        ofImage temp;
        temp.loadImage("assets/images/inGameMenu/Dot"+ofToString(i)+"_Small.png");
        iconImg.push_back(temp);
    }
    
    bgRect.set(0, 0, bgImg.getWidth(),bgImg.getHeight());
    for (int i=0; i<3; i++) {
        ofRectangle temp;
        temp.set(140+220*i, 500, 40, 30);
        buttons.push_back(temp);
        
        ofColor tempColor;
        tempColor.set(200);
        buttonColor.push_back(tempColor);
    }
    
    reset();
        
};

//-----------------------------------------------------------------------
void inGameMenu::update(){
    
    
    angle = (int)ofMap((60-*gameTimer), 0, 60, 0, 360);
    
    if (angle-preAngle == 1) {
        lineColor[angle].set(255,30);
    }
    
    preAngle = angle;

}
//-----------------------------------------------------------------------
void inGameMenu::reset(){

    bLevelDone = false;
    bNextLevel = false;
    bTryAgin   = false;
    bHome      = false;
    bLevelFail = false;
    angle      = 0;
    preAngle   = 0;
    timer      = 0;
    
    linePos.clear();
    lineColor.clear();
    
    for (int i=0; i<360; i++) {
        ofPoint temp;
        temp.x = 20*cos(i*DEG_TO_RAD - PI/2);
        temp.y = 20*sin(i*DEG_TO_RAD - PI/2);
        linePos.push_back(temp);
        
        ofColor color(30);
        lineColor.push_back(color);
    }
    
}

//-----------------------------------------------------------------------
void inGameMenu::draw(){

    ofSetColor(255);
    bgImg.draw(bgRect);
    
    ofSetColor(255);
    fingerImg[*live].draw(166,-5,fingerImg[*live].getWidth()/4*3,fingerImg[*live].getHeight()/4*3);
    
    ofSetColor(30);
    font.drawString("LV: "+ofToString(*level), 880, 40);
    
    
    ofPushMatrix();
    ofTranslate(56, 27);
    for (int i=0; i<linePos.size(); i++) {
        ofSetColor(lineColor[i]);
        ofLine(0, 0, linePos[i].x, linePos[i].y);
    }
    ofPopMatrix();
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    clockOutLine.draw(56, 27);
    ofSetRectMode(OF_RECTMODE_CORNER);

    
    for (int i=0; i<8; i++) {
        ofSetColor(255);
        if (i<*fingerSize) {
            iconImg[i].draw(345+50*i,10);
        }else{
            iconImg[7].draw(345+50*i,10);
        }
    }
    
    if (bLevelDone) {
        timer++;
        if (timer>100) {
            bNextLevel = true;
        }
        ofSetColor(255);
        wellDoneImg.draw(ofGetWidth()/2-wellDoneImg.getWidth()/2, ofGetHeight()/2-wellDoneImg.getHeight()/2);
    }
    
    if(bLevelFail){
        timer++;
        if (timer>100) {
             bTryAgin = true;
        }
        ofSetColor(120);
        wellDoneImg.draw(ofGetWidth()/2-wellDoneImg.getWidth()/2, ofGetHeight()/2-wellDoneImg.getHeight()/2);
    }
    
}

//-----------------------------------------------------------------------
void inGameMenu::touchDown(int x, int y){

    if (bLevelDone) {
        for (int i=0; i<buttons.size(); i++) {
            if (buttons[i].inside(x, y)) {
                buttonColor[i].set(30);
            }
        }
    }
    

}

//-----------------------------------------------------------------------
void inGameMenu::touchMove(int x, int y){
    if (bLevelDone) {
        for (int i=0; i<buttons.size(); i++) {
            if (buttons[i].inside(x, y)) {
                buttonColor[i].set(30);
            }else{
                buttonColor[i].set(200);
            }
        }
    }

}

//-----------------------------------------------------------------------
void inGameMenu::touchUp(int x, int y){
    
    if (bLevelDone) {
        if (buttons[0].inside(x, y)) {
            buttonColor[0].set(200);
            bTryAgin = true;
        }
        
        if (buttons[1].inside(x, y)) {
            buttonColor[1].set(200);
            bHome = true;
        }
        
        if (buttons[2].inside(x, y)) {
            buttonColor[2].set(200);
            bNextLevel = true;
        }
        
    }
    

}









