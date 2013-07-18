//
//  dots.cpp
//  handShadow
//
//  Created by PengCheng on 7/15/13.
//
//

#include "dots.h"

//-------------------------------------------------------
void dots::setup(float x, float y){

    pos.set(x,y);
    bCovered = false;
    effect = false;
    touchID = -1;
    color.set(255);
    radius0 = 83;
    radius1 = radius0*1.2;
    
    pct = 0;
    speed = 0.1f;
    
    button.loadImage("assets/images/dot4.png");
    
    zoomIn = true;
    zoomOut = false;
    size = 0;
    zoomPct = 0;
    zoomSpeed = 0.05f;
}

//-------------------------------------------------------
void dots::update(){
    
    if (effect) {
        
        pct+=speed;
        pct = pct+speed;
        
        if (pct >1) {
            speed *=-1;
        }else if(pct <0){
            speed *=-1;
        }
                
        radius1 = pct*radius0*1.2 + (1-pct)*radius0*1.4;
    }
    else{
        
        radius1 = radius0*1.2;

    }
    
    InAndOut();
  
}

//-------------------------------------------------------
void dots::resetModeOne(){
    
    zoomIn = true;
    zoomOut = false;
    size = 0;
    zoomPct = 0;
    zoomSpeed = 0.05f;
    
    bCovered = false;
    effect = false;
    touchID = -1;
    color.set(255);
    radius0 = 83;
    radius1 = radius0*1.2;
    
    pct = 0;
    speed = 0.1f;
    
}
//-------------------------------------------------------
void dots::resetModeTwo(){

    zoomIn = false;
    zoomOut = false;
    size = 0;
    zoomPct = 0;
    zoomSpeed = 0.05f;
    
    bCovered = false;
    effect = false;
    touchID = -1;
    color.set(255);
    radius0 = 83;
    radius1 = radius0*1.2;
    
    pct = 0;
    speed = 0.1f;

}

//-------------------------------------------------------
void dots::InAndOut(){
    
    if (zoomIn) {
        
        zoomPct += zoomSpeed;
        if (zoomPct>1) {
            zoomPct = 1;
            zoomIn = false;
            
        }
        
        float mPct;
        mPct = powf(zoomPct, 0.8);
        size = mPct*165;
    }
    
    if (zoomOut) {
        
        zoomPct -= zoomSpeed;
        if (zoomPct<0) {
            zoomPct = 0;
            zoomOut = false;
        }
        
        float mPct;
        mPct = powf(zoomPct, 0.8);
        size = mPct*165;
    }

}

//-------------------------------------------------------
void dots::draw(){
    
    if (bCovered) {
        ofSetColor(255,30,200,100);
        ofCircle(pos.x, pos.y, radius1);
    }
    

    ofPushMatrix();
        ofSetColor(color);
        ofTranslate(pos.x, pos.y);
        ofSetRectMode(OF_RECTMODE_CENTER);
        button.draw(0, 0, size, size);
        ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopMatrix();

}














