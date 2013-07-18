//
//  menu.cpp
//  handShadow
//
//  Created by PengCheng on 7/14/13.
//
//

#include "menu.h"

//-------------------------------------------------------
void menu::setup(){

    button[0].loadImage("assets/images/buttons/Tutorial.png");
    buttonOver[0].loadImage("assets/images/buttons/Tutorial_B.png");
    background[0].loadImage("assets/images/mainMenuBg.png");
    
    button[1].loadImage("assets/images/buttons/play.png");
    buttonOver[1].loadImage("assets/images/buttons/Play_B.png");
    background[1].loadImage("assets/images/mainMenuBg.png");
    
    button[2].loadImage("assets/images/buttons/Levels.png");
    buttonOver[2].loadImage("assets/images/buttons/Levels_B.png");
    background[2].loadImage("assets/images/mainMenuBg.png");
    
    button[3].loadImage("assets/images/buttons/Theme.png");
    buttonOver[3].loadImage("assets/images/buttons/Theme_B.png");
    background[3].loadImage("assets/images/mainMenuBg.png");
    
    button[4].loadImage("assets/images/buttons/Credit.png");
    buttonOver[4].loadImage("assets/images/buttons/Credit_B.png");
    background[4].loadImage("assets/images/mainMenuBg.png");
    
    hidenLogo.loadImage("assets/images/hidenLogo.png");
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].button = &button[i];
        mainMenuRect[i].buttonTouchOver = &buttonOver[i];
        mainMenuRect[i].background = &background[i];
        
        mainMenuRect[i].rectW = button[i].getWidth();
        mainMenuRect[i].rectH = button[i].getHeight();

    }
    
    
    reset();
    
}

//-------------------------------------------------------
void menu::update(){
    
    if(bSnapIn){
        snapIn();
    }if (bSubMenu) {
        subMenu(subMenuNum);
    }
    else{
        drag();
    }
    
    
}

//-------------------------------------------------------
void menu::drag(){

    
    mParticle.resetForce();
    mParticle.addForce(frc, 0);
    mParticle.addDampingForce();
    mParticle.update();
    
    if (mParticle.pos.x>512) {
        mParticle.pos.x = 512;
        
    }
    else if(mParticle.pos.x < -132){
        
        mParticle.pos.x = -132;
    }
    
   
    hiden();
    
    float diff = mParticle.pos.x -preParticleX;
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].pos.x += diff;
    }
    
    preParticleX = mParticle.pos.x;
    
}

//-------------------------------------------------------
void menu::snapIn(){
    
    for (int i=0; i<counter; i++) {
        pct[i] += speed;
        if (pct[i]>1) pct[i] = 1;
        
        
        if (pct[i]>0.3) {
            if (i == counter-1 && counter< MAIN_MENU_BUTTON) {
                counter++;
            }
        }
        
        mainMenuRect[i].interpolateByPct(pct[i]);
    }
    
 
    if (pct[MAIN_MENU_BUTTON-1] == 1) {
        bSnapIn = false;
        for (int i=0; i<counter; i++) pct[i] =0;
        counter = 1;
    }
   
    
}

//-------------------------------------------------------
void menu::subMenu(int num){

    if (num ==0) {
        
        if (subStep == 0){
            for (int i=0; i<5; i++) pct[i] =0;
            for (int i=0; i<MAIN_MENU_BUTTON; i++)mainMenuRect[i].posc.x = -30+300*i;
            subStep = 1;
        }
        else if (subStep == 1) {
            for (int i=0; i<MAIN_MENU_BUTTON; i++) {
                pct[i] += speed;
                if (pct[i]>1) pct[i] = 1;
                mainMenuRect[i].interpolateByPct2(pct[i]);
            }
            
            if (pct[MAIN_MENU_BUTTON-1] == 1) {
                for (int i=1; i<5; i++) pct[i] =0;
                subStep = 2;
            }
        }
        
       else if(subStep == 2) {
           mainMenuRect[1].posc.x = ofGetWidth()+300;
           mainMenuRect[2].posc.x = ofGetWidth()+300*2;
           mainMenuRect[3].posc.x = ofGetWidth()+300*3;
           mainMenuRect[4].posc.x = ofGetWidth()+300*4;
           subStep = 3;
        }
        
       else if(subStep == 3){
           for (int i=1; i<MAIN_MENU_BUTTON; i++) {
               pct[i] += speed;
               if (pct[i]>1) pct[i] = 1;
               mainMenuRect[i].interpolateByPct2(pct[i]);
           }
           
       }
       
       else if(subStep == 4){
           for (int i=0; i<5; i++) pct[i] =0;
           mainMenuRect[0].posc.x = 0;
           mainMenuRect[1].posc.x = 300;
           mainMenuRect[2].posc.x = 300*2;
           mainMenuRect[3].posc.x = 300*3;
           mainMenuRect[4].posc.x = 300*4;
           subStep = 5;
       }
        
       else if(subStep == 5){
           for (int i=0; i<MAIN_MENU_BUTTON; i++) {
               pct[i] += speed;
               if (pct[i]>1) pct[i] = 1;
               mainMenuRect[i].interpolateByPct2(pct[i]);
           }
           
           if (pct[MAIN_MENU_BUTTON-1] == 1) {
               for (int i=0; i<counter; i++) pct[i] =0;
               bSubMenu = false;
               subStep = 0;
           }
       }
        
    }
    
    cout<<subStep<<endl;

}

//-------------------------------------------------------
void menu::hiden(){
    float catchUpSpeed = 0.08f;
    float catchX = 36;
    
    if (!bHidenLogo) {
         if(mParticle.pos.x < 36){
            
            mParticle.pos.x = 36;
        }
    }
    
    if(!bDrag && bHidenLogo){
        frc = 0;
        mParticle.pos.x = (1-catchUpSpeed)*mParticle.pos.x + catchUpSpeed * catchX;
        if (mParticle.pos.x >35) {
            bHidenLogo = false;
        }
    }

}

//-------------------------------------------------------
void menu::reset(){
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        mainMenuRect[i].posa.x = 1000+ 100*i;
        mainMenuRect[i].posa.y = 0;
        mainMenuRect[i].posb.x = 300*i;
        mainMenuRect[i].posb.y = 0;
        mainMenuRect[i].posc.x = 0;
        mainMenuRect[i].posc.y = 0;
        mainMenuRect[i].shaper = 1.5;
        mainMenuRect[i].interpolateByPct(0);
        mainMenuRect[i].pct = 0;
        mainMenuRect[i].pos =  mainMenuRect[i].posa;
        pct[i] = 0;
    }
    
    
    speed = 0.05f;
    counter = 1;
    bSnapIn = true;
    bHidenLogo = false;
    bDrag = false;
    bSubMenu = false;
    touch.set(0, 0);
    preTouch = touch;
    frc = 0;

    mParticle.setInitialCondition(512, 384, 0, 0);
    preParticleX = mParticle.pos.x;
    
    subMenuNum = 0;
    subStep = 0;
}

//-------------------------------------------------------
void menu::draw(){
    
    if (mainMenuRect[MAIN_MENU_BUTTON-1].pct == 1) {
        ofSetColor(255);
        hidenLogo.draw(ofGetWidth()-168,0);
    }
    
    if (bSubMenu) {
        ofSetColor(150);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        ofSetColor(255);
        mainMenuRect[i].draw();
    }
    
    ofSetColor(30);
//    mParticle.draw();
    
    
    
}

//-------------------------------------------------------
void menu::touchDown(int x, int y, int touchID){

    if (bSubMenu) {
        if (!bSnapIn) {
            touch.set(x, y);
            preTouch = touch;
            frc = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
        }
    }
    
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        if (mainMenuRect[i].buttonRect.inside(x, y)) {
            mainMenuRect[i].bTouchOver = true;
        }
    }
    
    
   
}
//-------------------------------------------------------
void menu::touchMove(int x, int y, int touchID){
    
    if (!bSubMenu) {
        if (!bSnapIn){
            bDrag = true;
            frc = 0;
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            
            touch.set(x, y);
            int diff = touch.x - preTouch.x;
            int speed = 2;
            if (diff>3) {
                for (int i=0; i<MAIN_MENU_BUTTON; i++) {
                    mParticle.pos.x+=speed;
                }
            }
            else if (diff<-3) {
                for (int i=0; i<MAIN_MENU_BUTTON; i++) {
                    mParticle.pos.x-=speed;
                    if (mParticle.pos.x<36) {
                        bHidenLogo = true;
                    }
                }
                
                
            }
            
            preTouch.x = touch.x;
        }
    }
   
    for (int i=0; i<MAIN_MENU_BUTTON; i++) {
        if (mainMenuRect[i].buttonRect.inside(x, y)) {
            mainMenuRect[i].bTouchOver = true;
        }else{
            mainMenuRect[i].bTouchOver = false;
        }
    }
    
}
//-------------------------------------------------------
void menu::touchUp(int x, int y, int touchID){
    
    
    if (!bSubMenu) {
        
        if (subStep == 0) {
            if (mainMenuRect[0].buttonRect.inside(x, y)) {
                bSubMenu = true;
                subMenuNum = 0;
                mainMenuRect[0].bTouchOver = false;
                
            }
            
            if (mainMenuRect[1].buttonRect.inside(x, y)) {
                *currentScene = 1;
                mainMenuRect[1].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[2].buttonRect.inside(x, y)) {
                mainMenuRect[2].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[3].buttonRect.inside(x, y)) {
                mainMenuRect[3].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[4].buttonRect.inside(x, y)) {
                mainMenuRect[4].bTouchOver = false;
                reset();
            }
        }
        
        
        touch.set(x, y);
        float speed = 3;
        float diff = touch.x - preTouch.x;
        if (diff >1 ) {
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            frc = speed;
        }
        else if (diff < -1){
            mParticle.frc.set(0,0);
            mParticle.vel.set(0,0);
            frc = -speed;
        }else{
            frc = 0;
        }
        
        bDrag = false;
    }else{
    
        if (subStep == 3) {
            if (mainMenuRect[0].buttonRect.inside(x, y)) {
                subStep = 4;
                mainMenuRect[0].bTouchOver = false;
            }
            
            if (mainMenuRect[1].buttonRect.inside(x, y)) {
                *currentScene = 1;
                mainMenuRect[1].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[2].buttonRect.inside(x, y)) {
                mainMenuRect[2].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[3].buttonRect.inside(x, y)) {
                mainMenuRect[3].bTouchOver = false;
                reset();
            }
            
            if (mainMenuRect[4].buttonRect.inside(x, y)) {
                mainMenuRect[4].bTouchOver = false;
                reset();
            }
        }
    
    }
  
    
}







