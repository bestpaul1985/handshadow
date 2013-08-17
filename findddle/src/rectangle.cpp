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
    bIsEnoughMoney = true;
    itemNumber = 0;
    purchaseAnimationPct = 0;
    bPurchaseAnimation = false;
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
    purchaseRect.set(pos.x+rectW-40, pos.y+rectH-40, 36, 36);
    ofSetColor(255);
    purchaseImg->draw(buttonRect.getPosition());
    
    if (bTouchOver || !bIsEnoughMoney) {
        ofSetColor(125,100);
    }else{
        ofSetColor(255);
    }
    
    purchasePlusImg->draw(purchaseRect);

    
    // plus animation;
    
    if (bPurchaseAnimation) {
        float speed = 0.03f;
        purchaseAnimationPct+=speed;
        
        if (purchaseAnimationPct >1) {
            purchaseAnimationPct = 1;
            bPurchaseAnimation = false;
        }
        
        float y = (1-purchaseAnimationPct)*purchaseRect.getCenter().y + purchaseAnimationPct*(purchaseRect.getCenter().y-80);
        float alpha = (1-purchaseAnimationPct)*255;
     
        string message;
        
        if (itemNumber == 0) {
           message = "+1";
        }else if(itemNumber == 1){
            message = "+3";

        }else if(itemNumber == 2){
            message = "+5";

        }else if(itemNumber == 3){
            message = "+UP";
            
        }
        
        ofSetColor(alpha);
        purchaseAnimationfont->drawString(message, purchaseRect.getCenter().x-purchaseAnimationfont->stringWidth(message)/2, y);
    }
    
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
void rectangle::drawInGameMenu(){
    
    bgRect.setFromCenter(pos, button->getWidth(), button->getHeight());
    ofPushMatrix();
    ofTranslate(pos);
    if (bTouchOver) {
        ofSetColor(125);
    }else{
        ofSetColor(255);
    }
    button->draw(-button->getWidth()/2, -button->getHeight()/2);
    
    ofPopMatrix();
    
}

//------------------------------------------------------------------
void rectangle::draw(){
    
    int offset = 270;
    
    bgRect.set(pos.x,pos.y, 300, ofGetHeight());
    buttonRect.setFromCenter(bgRect.getCenter(), rectW, rectH);
    ofSetColor(255);
    
    if (bTouchOver) {
        fingerImg[0]->draw(bgRect.getCenter().x-fingerImg[1]->getWidth()/2,bgRect.getCenter().y-fingerImg[1]->getHeight()/2-offset+60);
        fingerImg[1]->draw(bgRect.getCenter().x-fingerImg[1]->getWidth()/2,bgRect.getCenter().y-fingerImg[1]->getHeight()/2+offset-60);
        buttonTouchOver->draw(buttonRect.position); 
    }else{
        fingerImg[0]->draw(bgRect.getCenter().x-fingerImg[1]->getWidth()/2,bgRect.getCenter().y-fingerImg[1]->getHeight()/2-offset);
        fingerImg[1]->draw(bgRect.getCenter().x-fingerImg[1]->getWidth()/2,bgRect.getCenter().y-fingerImg[1]->getHeight()/2+offset);
        button->draw(buttonRect.position);
    }
    
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






