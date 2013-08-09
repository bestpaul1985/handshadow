    //
//  rectangle.cpp
//  handShadow
//
//  Created by PengCheng on 7/17/13.
//
//

#include "rectangle.h"


//------------------------------------------------------------------
rectangle::rectangle(){
    
	shaper = 1.0;
    rectW = rectH = 50;
    bTouchOver = false;
    bFixed = false;
    bLocked = true;
    shadowWidth = 0;
}

//------------------------------------------------------------------
void rectangle::drawLevel(){
    
    buttonRect.setFromCenter(pos, rectW, rectH);
    
    if (bTouchOver) {
        ofSetColor(125);
    }else{
        ofSetColor(255);
    }
    
    if (bLocked) {
        imgLockedLevel->draw(buttonRect);
    }else{
        imgUnlockedLevel->draw(buttonRect);
        ofSetColor(255);
        font->drawString(message, buttonRect.getCenter().x - font->stringWidth(message)/2,buttonRect.getCenter().y +font->stringHeight(message)/2);
    }
    
}
//------------------------------------------------------------------
void rectangle::drawPurchase(){

    buttonRect.set(pos, rectW, rectH);
    if (bTouchOver) {
        ofSetColor(125);
    }else{
        ofSetColor(255);
    }
    purchaseImg->draw(buttonRect.getPosition());
    
}

//------------------------------------------------------------------
void rectangle::drawSetting(){

    buttonRect.setFromCenter(pos, rectW, rectH);
    if (bTouchOver) {
        ofSetColor(125);
    }else{
        ofSetColor(255);
    }
    
    setImg->draw(buttonRect);
    
}
//------------------------------------------------------------------
void rectangle::drawPause(){

    bgRect.setFromCenter(pos, button->getWidth(), button->getHeight());

    ofPushMatrix();
    ofTranslate(pos);
    if (bTouchOver) {
        buttonTouchOver->draw(-buttonTouchOver->getWidth()/2,-buttonTouchOver->getHeight()/2);
    }else{
        button->draw(-button->getWidth()/2, -button->getHeight()/2);
    }
    ofPopMatrix();
}

//------------------------------------------------------------------
void rectangle::draw() {
    
    int offset = 270;
    
    bgRect.set(pos.x,pos.y, 300, ofGetHeight());
    buttonRect.setFromCenter(bgRect.getCenter(), rectW, rectH);
    ofSetColor(255);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    if (bTouchOver) {
        fingerImg[0]->draw(bgRect.getCenter().x,bgRect.getCenter().y-offset+60);
        fingerImg[1]->draw(bgRect.getCenter().x,bgRect.getCenter().y+offset-60);
        buttonTouchOver->draw(bgRect.getCenter()); 
    }else{
        fingerImg[0]->draw(bgRect.getCenter().x,bgRect.getCenter().y-offset);
        fingerImg[1]->draw(bgRect.getCenter().x,bgRect.getCenter().y+offset);
        button->draw(bgRect.getCenter());
    }
    ofSetRectMode(OF_RECTMODE_CORNER);

    
    ofSetColor(30, 30);
    ofRect(bgRect.getPosition().x+bgRect.getWidth(),0,shadowWidth,768);
    
}


//------------------------------------------------------------------
void rectangle::interpolateByPct(float myPct){
	pct = powf(myPct, shaper);
	pos.x = (1-pct) * posa.x + (pct) * posb.x;
	pos.y = (1-pct) * posa.y + (pct) * posb.y;
}

//------------------------------------------------------------------
void rectangle::interpolateByPct2(float myPct){
	pct = powf(myPct, shaper);
	pos.x = (pct) * posc.x + (1-pct) * pos.x;
	pos.y = (pct) * posc.y + (1-pct) * pos.y;
}






