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
}

//------------------------------------------------------------------
void rectangle::drawLevel(){
    
    buttonRect.setFromCenter(pos, rectW, rectH);
    if (bTouchOver) {
        ofSetColor(125);
    }else{
        ofSetColor(255);
    }
    
    ofRect(buttonRect);

}

//------------------------------------------------------------------
void rectangle::draw() {
    
    bgRect.set(pos.x,pos.y, 300, ofGetHeight());
    buttonRect.setFromCenter(bgRect.getCenter(), rectW, rectH);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(bgRect.getCenter(),300,ofGetHeight());
    if (bTouchOver) {
        buttonTouchOver->draw(bgRect.getCenter()); 
    }else{
        button->draw(bgRect.getCenter());
    }
    ofSetRectMode(OF_RECTMODE_CORNER);

    
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






