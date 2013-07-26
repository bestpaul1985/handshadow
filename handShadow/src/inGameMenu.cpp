//
//  inGameMenu.cpp
//  handShadow
//
//  Created by PengCheng on 7/23/13.
//
//

#include "inGameMenu.h"

void inGameMenu::setup(){
    
    wellDown.loadImage("assets/images/inGameMenu/welldone.png");
    fingerBG.loadImage("assets/images/liveSystem/background_small.png");
    imgMenu.loadImage("assets/images/inGameMenu/menu.png");
    imgMenu_b.loadImage("assets/images/inGameMenu/menu_b.png");
    imgResume.loadImage("assets/images/inGameMenu/resume.png");
    imgResume_b.loadImage("assets/images/inGameMenu/resume_b.png");
    
    menuRect.set(ofGetWidth()/2-imgMenu.getWidth()-50, ofGetHeight()/2-imgMenu.getHeight()/2, imgMenu.getWidth(),imgMenu.getHeight());
    resumeRect.set(ofGetWidth()/2+50, ofGetHeight()/2-imgResume.getHeight()/2, imgResume.getWidth(),imgResume.getHeight());

    bwellDone = false;
    bPause = false;
    bTouchOverMenu = false;
    bTouchOverResume = false;
    bBackToMainMenu = false;
    wellDoneTimer = 0;
    liveSystemSetup();

    
};

//-----------------------------------------------------------------------
void inGameMenu::update(){
    

    liveSystemUpdate();

}

//-----------------------------------------------------------------------
void inGameMenu::draw(){

    if (bwellDone) {
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255);
        wellDown.draw(ofGetWidth()/2, ofGetHeight()/2);
        ofSetRectMode(OF_RECTMODE_CORNER);
        
    }
    
    if (bPause) {
        
        ofSetColor(255, 200);
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        
        if (bTouchOverMenu) imgMenu_b.draw(ofGetWidth()/2-imgMenu.getWidth()-50, ofGetHeight()/2-imgMenu.getHeight()/2);
        else imgMenu.draw(ofGetWidth()/2-imgMenu.getWidth()-50, ofGetHeight()/2-imgMenu.getHeight()/2);
        
        if (bTouchOverResume) imgResume_b.draw(ofGetWidth()/2+50, ofGetHeight()/2-imgResume.getHeight()/2);
        else imgResume.draw(ofGetWidth()/2+50, ofGetHeight()/2-imgResume.getHeight()/2);
        
    }else{
        liveSystemDraw();
    }

}

//----------------------------------------------------------
void inGameMenu::liveSystemSetup(){
    
    spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 56);
	spriteRenderer->loadTexture("assets/images/liveSystem/spriteSheetExample2.png", 512, GL_NEAREST);
    
    basicSprite * newSprite = new basicSprite();
    newSprite->pos.set(68,80);
    newSprite->animation = fingerAnimation;
    sprites.push_back(newSprite);
    imgRect.set(70-fingerBG.getWidth()/2, 80-fingerBG.getHeight()/2, fingerBG.getWidth(), fingerBG.getHeight());

}

//----------------------------------------------------------
void inGameMenu::liveSystemUpdate(){
    
    spriteRenderer->clear();
	spriteRenderer->update(ofGetElapsedTimeMillis());
    sprites[0]->animation.frame = *live;
	spriteRenderer->addCenteredTile(&sprites[0]->animation, sprites[0]->pos.x, sprites[0]->pos.y);
	
}

//----------------------------------------------------------
void inGameMenu::liveSystemDraw(){
    
    if (bliveTouchOver) {
        ofSetColor(120);
    }else{
        ofSetColor(255);
    }
    
    fingerBG.draw(imgRect);
    spriteRenderer->draw();
    
}

//----------------------------------------------------------
void inGameMenu::liveSystemTouchDown(int x, int y, int touchID){
    
    if (imgRect.inside(x, y)) {
        bliveTouchOver = true;
    }
}

//----------------------------------------------------------
void inGameMenu::liveSystemTouchMove(int x, int y, int touchID){
    
    ofRectangle rect;
    if (!imgRect.inside(x, y)) {
        bliveTouchOver = false;
    }else{
        bliveTouchOver = true;
    }
}


//----------------------------------------------------------
void inGameMenu::liveSystemTouchUp(int x, int y, int touchID){
    
    ofRectangle rect;
    rect.set(70-fingerBG.getWidth()/2, 80-fingerBG.getHeight()/2, fingerBG.getWidth(), fingerBG.getHeight());
    if (imgRect.inside(x, y)) {
        bliveTouchOver = false;
        bPause = true;
    }
}

//-----------------------------------------------------------------------
void inGameMenu::touchDown(int x, int y, int touchID){
    
    
    if(!bPause){
        liveSystemTouchDown(x,y,touchID);
    }
    else{
        
        if (menuRect.inside(x, y)) {
            bTouchOverMenu = true;
        }
        
        if(resumeRect.inside(x, y)){
            bTouchOverResume = true;
        }
    }
}

//-----------------------------------------------------------------------
void inGameMenu::touchMove(int x, int y, int touchID){
    
    if(!bPause){
        liveSystemTouchMove(x, y, touchID);
    }else{
        
        if (menuRect.inside(x, y)) {
            bTouchOverMenu = true;
        }else{
            bTouchOverMenu = false;
        }
        
        if(resumeRect.inside(x, y)){
            bTouchOverResume = true;
        }else{
            bTouchOverResume = false;
        }
    }
}

//-----------------------------------------------------------------------
void inGameMenu::touchUp(int x, int y, int touchID){
    
    if(!bPause){
        liveSystemTouchUp(x, y, touchID);
    }else{
        
        if (menuRect.inside(x, y)) {
            bTouchOverMenu = false;
            bPause = false;
            bBackToMainMenu = true;
        }
        
        if(resumeRect.inside(x, y)){
            bTouchOverResume = false;
            bPause = false;
        }
        
    }
}

