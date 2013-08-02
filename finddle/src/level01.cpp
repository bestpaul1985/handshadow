//
//  level01.cpp
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#include "level01.h"

//-------------------------------------------------------
void level01::setup(){

    dot[0].setup(230, 580);
    dot[1].setup(346, 93);
    dot[2].setup(721,85);
    dot[3].setup(893, 310);
    dot[4].setup(887, 630);
    
    timer = 0;
    fingers = 5;
    ending = false;
}

//-------------------------------------------------------
void level01::update(){
    
    
    checkWinStatus();
        
    for (int i=0; i<fingers; i++) {
        dot[i].update();
    }
    
//    cout<<"one: "<<dot[0].bCovered<<" two: "<<dot[1].bCovered<<" three: "<<dot[2].bCovered<<" four: "<<dot[3].bCovered<<" five: "<<dot[4].bCovered<<endl;
    
    
}

//-------------------------------------------------------
void level01::draw(){
    
    ofSetColor(255*0.8);
    pattern->draw(0,0);
    
    
    for (int i=0; i<fingers; i++) {
        dot[i].draw();
    }
}

//-------------------------------------------------------
void level01::checkWinStatus(){
    
    int counter =0;
    
    for (int i=0; i<fingers; i++) {
        if (dot[i].bCovered) {
            counter++;
        }
    }
    
    if (counter ==5) {
        for (int i=0; i<fingers; i++) {
            dot[i].effect = true;
        }
        timer ++;
    }else{
        timer = 0;
        for (int i=0; i<fingers; i++) {
            dot[i].effect = false;
        }
    }
    
    if (timer>100 && !ending) {
        ending = true;
        for (int i=0; i<fingers; i++) {
            dot[i].zoomOut = true;
        }
    }
    
    if (ending) {
        int counter = 0;
        for (int i=0; i<fingers; i++) {
            if (!dot[i].zoomOut) {
                counter++;
            }
        }
        
        if (counter == fingers) {
            *currentScene = 2;
            reset();
        }
    }
  
}

//-------------------------------------------------------

void level01::reset(){

    for (int i=0; i<fingers; i++) {
        dot[i].resetModeOne();
    }

    ending =false;
    timer = 0;
    fingers = 5;
    
}

//-------------------------------------------------------
void level01::touchDown(int x, int y, int touchID){
    
    ofPoint touchPos(x,y);
    for (int i=0; i<fingers; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && !dot[i].bCovered) {
            dot[i].bCovered = true;
            dot[i].touchID = touchID;
        }
    }
    
}

//-------------------------------------------------------
void level01::touchMove(int x, int y, int touchID){
    
    ofPoint touchPos(x,y);
    for (int i=0; i<fingers; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && !dot[i].bCovered) {
            dot[i].bCovered = true;
            dot[i].touchID = touchID;
        }
        
        else if(dot[i].pos.distance(touchPos) > dot[i].radius0 && dot[i].bCovered &&  dot[i].touchID == touchID){
            dot[i].bCovered = false;
            dot[i].touchID = -1;
        }
    }

}

//-------------------------------------------------------
void level01::touchUp(int x, int y, int touchID){
    ofPoint touchPos(x,y);

    for (int i=0; i<fingers; i++) {
        if (dot[i].pos.distance(touchPos) < dot[i].radius0 && dot[i].bCovered) {
            dot[i].bCovered = false;
            dot[i].touchID = -1;
        }
    }
    
}





