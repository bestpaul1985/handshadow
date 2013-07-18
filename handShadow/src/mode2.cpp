//
//  mode2.cpp
//  handShadow
//
//  Created by PengCheng on 7/15/13.
//
//

#include "mode2.h"

void mode2::setup(){

    dot[0].setup(338, 556);
    dot[1].setup(679, 504);
    dot[2].setup(671, 241);
    dot[3].setup(382, 265);
    dot[4].setup(512, 387);

    order = 1;
    counter = 0;
    timer = 0;
    fingers = 5;
    
    for (int i=0; i<fingers; i++) {
        if (i!=0) {
            dot[i].zoomIn = false;
        }
    }
    
    ending = false;
}

//----------------------------------------------------------
void mode2::update(){
    
    checkWinStatus();
    
    for (int i=0; i<fingers; i++) {
        dot[i].update();
    }
    
}

//----------------------------------------------------------
void mode2::draw(){

    ofSetColor(255*0.8);
    pattern->draw(0,0);
    
    for (int i=0; i< order; i++) {
        dot[i].draw();
    }
}

//-------------------------------------------------------
void mode2::checkWinStatus(){
    
    for (int i=0; i<order; i++) {
        if (i!=0) {
            dot[i].zoomIn = true;
        }
    }
    
    if (counter>=fingers) {
        for (int i=0; i<fingers; i++) {
            dot[i].effect = true;
        }
        order = fingers;
        timer ++;
    }
    else{
        for (int i=0; i<fingers; i++) {
            dot[i].effect = false;
        }
        timer = 0;
    }
    
    if (timer>100 && ending == false) {
        ending = true;
    }
    
    if (ending) {
        int counter = 0;
        for (int i=0; i<fingers; i++) {
            if (!dot[i].zoomOut) {
                counter++;
            }
        }
        
        if (counter == fingers) {
            *currentScene = 0;
            reset();
        }
    }
}

//----------------------------------------------------------
void mode2::reset(){
    
    for (int i=0; i<fingers; i++) {
        dot[i].resetModeTwo();
    }
    
    dot[0].zoomIn = true;
    
    ending =false;
    timer = 0;
    fingers = 5;
    order = 1;
    counter = 0;
    
}

//----------------------------------------------------------
void mode2::touchDown(int x, int y, int touchID){

    ofPoint touchPos(x,y);
    for (int i=0; i<order; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && !dot[i].bCovered) {
            dot[i].bCovered = true;
            dot[i].touchID = touchID;
            order ++;
            counter++;
        }
    }
}

//----------------------------------------------------------
void mode2::touchMove(int x, int y, int touchID){
    
    ofPoint touchPos(x,y);
    for (int i=0; i<order; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && !dot[i].bCovered) {
            dot[i].bCovered = true;
            dot[i].touchID = touchID;
            order ++;
            counter++;
            
        }
        
        else if(dot[i].pos.distance(touchPos) > dot[i].radius0 && dot[i].bCovered &&  dot[i].touchID == touchID){

            reset();            
        }
    }
}

//----------------------------------------------------------
void mode2::touchUp(int x, int y, int touchID){

    ofPoint touchPos(x,y);
    for (int i=0; i<order; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && dot[i].bCovered) {
            reset();
        }
    }



}















