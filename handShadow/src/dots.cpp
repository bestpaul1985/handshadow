//
//  dots.cpp
//  handShadow
//
//  Created by PengCheng on 7/15/13.
//
//

#include "dots.h"

//-------------------------------------------------------
void dots::setup(float x, float y,ofImage *A, ofImage *B){

    pos.set(x,y);
    radius = 83;
    dot_normal = A;
    dot_pressed = B;
    reset();
    angle = 0;
}

//-------------------------------------------------------
void dots::update(){
    

  
}

//-------------------------------------------------------
void dots::reset(){
    notMyId.clear();
    myId.clear();
    bCovered = false;
    bFixed = true;
}

//-------------------------------------------------------
void dots::draw(){
    
    if (!bFixed) {
        ofPushMatrix();
        ofSetColor(color);
        ofTranslate(pos.x, pos.y);
//        ofRotateZ(angle);
        if (bCovered) dot_pressed->draw(-dot_pressed->getWidth()/2, -dot_pressed->getHeight()/2);
        else dot_normal->draw(-dot_normal->getWidth()/2, -dot_normal->getHeight()/2);
        ofPopMatrix();
    }
}

//-------------------------------------------------------
void dots::touchDown(int x, int y, int touchID){
    
      
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (pos.distance(touchPos) < radius) {
            myId.push_back(touchID);
        }
        
        if (myId.size()>0) {
            bCovered = true;
        }
    }

}

//-------------------------------------------------------
void dots::touchMove(int x, int y, int touchID){

    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) > radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        
        
        if (myId.size()==0) {
            bCovered = false;
        }
    }
        
}

//-------------------------------------------------------
void dots::touchUp(int x, int y, int touchID){
  
    if (!bFixed) {
        ofPoint touchPos(x,y);
        if (myId.size()>0) {
            for (int i=0; i<myId.size(); i++) {
                if (myId[i] == touchID) {
                    if (pos.distance(touchPos) < radius) {
                        myId.erase(myId.begin()+i);
                    }
                }
            }
        }
        
        if (myId.size()==0) {
            bCovered = false;
        }
    }
    
}















